/***************************************************************************/
/*                                                                         */
/*  Filename: vme_single_cycles.c								           */
/*                                                                         */
/*  FunCtion:  SIS1100/SIS310x Visual C TEST								*/
/*                                                                         */
/*  Autor:                Pythagore Guekam                                 */
/*  date:                 19.03.2021                                       */
/*  last modification:    20.03.2021                                       */
/*                                                                         */

/*  © 2021                                                                 */
/*                                                                         */
/***************************************************************************/

//#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "zVME_const.h"
#include "wingetopt.h" 
#include "sis3100_vme_calls.h"
#include "sis1100w.h"
#include "sis3302.h"
#include "sis3100.h"
#include "vmeInterruptConst.h"
#pragma comment (lib, "sis1100w.lib")

#define FFTRAM_SIZE_PER_AXIS				16384
#define MAX_NOF_ACCESS_MODE_DEFINES			11 
#define RET_SUCCESS							0
#define RET_FAILED							-1
#define LAMBDA								632.9911 //"Nominal Vacuum Wavelength: 632.9911 ± 0.0001 nm"
#define SINGLE_PASS_INT_POS_COEF			2048	// 0.31 nm resolution
#define DOUBLE_PASS_INT_POS_COEF			4096	// 0.15 nm resolution
#define SSI_MAX_SAT							2047
#define SINGLE_PASS_INT_VEL_COEF			2.946705 * (1e-9)
#define DOUBLE_PASS_INT_VEL_COEF			1.473352 * (1e-9)

#define NO_EXCEPTION_ERROR					0
#define EXCEPTION_ERROR						1
#define STACK_OVERFLOW						2
#define SWITCH_DEFAULT_ERROR				3
#define COMM_ERROR							4
#define AXIS1								1
#define AXIS2								2
#define AXIS3								3
#define AXIS4								4

#define BIAS_OFF_MODE						0
#define BIAS_CONSTANT_VOLT_MODE				1
#define BIAS_CONSTANT_GAIN_MODE				2
#define BIAS_CONSTANT_OPT_PWR_MODE			3
#define BIAS_SIG_RMS_ADJUST_MODE			4
#define BIAS_CTRL_MODE_NBR					5		


#define DESCRIPTOR_1_TEST
#define DESCRIPTOR_2_TEST
#define DESCRIPTOR_3_TEST
#define DESCRIPTOR_4_TEST
#define DESCRIPTOR_5_TEST
// get SIS3104 base address as argument at the process startup
#define SIS3104_BASE_ADDRESS				0x0

const char* const access_mode_Selection[MAX_NOF_ACCESS_MODE_DEFINES] = {
	"CRCSRD8",  // Configuration ROM/Control&Status Register (CR/CSR)
	"CRCSRD16", // Configuration ROM/Control&Status Register (CR/CSR)
	"A16D8",    // A16 non privileged access
	"A16D16",   // A16 non privileged access
	"A16D32",   // A16 non privileged access
	"A24D8",    // A24 non privileged data access
	"A24D16",   // A24 non privileged data access
	"A24D32",   // A24 non privileged data access
	"A32D8",    // A32 non privileged data access
	"A32D16",   // A32 non privileged data access
	"A32D32"    // A32 non privileged data access
};
const char* const biasControlModeString[BIAS_CTRL_MODE_NBR] = {
	"BIAS_OFF_MODE",
	"BIAS_CONSTANT_VOLTAGE_MODE",
	"BIAS_CONSTANT_GAIN_MODE",
	"BIAS_ACONSTANT_OPTICAL_POWER_MODE",
	"BIAS_SIG_RMS_ADJUST_MODE",
};

SIS1100W_STATUS stat;
struct SIS1100_Device_Struct dev;

unsigned int	BASE_ADDRESS[] = { 0x14000, 0x15000, 0x16000, 0x17000 }, // Base adresses 
return_code = 0,
comp_err = 0,
valid_flag = 0,
NbrBdAx = 0;
//uint32_t sis_irq_array[16]; // 16 IRQs
uint32_t vme_irq_level=0, vme_irq_vector=0;
uint8_t read_irq_vector=0;

unsigned short	IntVector[] = { 0x101, 0, 0x202, 0 },
SCLKDrive = 2,
Direction[] = { 0, 0, 0, 0 };

/**/
//GUID sis1100w_GUID = { 0x944adde8, 0x4f6d, 0x4bee, 0xa309, 0x7ad62ab0b4bb };

char sc_char[4];
FILE* fd;

double	SSICalMin[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} },    //( (Ax1SSI,Ax1uW),(Ax2SSI,Ax2uW), etc) 
SSICalNom[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} },
SSICalMax[4][2] = { {1, 1}, {1, 1}, {1, 1}, {1, 1} },     //1 all by default to prevent /0
SSICalValues[4][2] = { {1, 1}, {1, 1}, {1, 1}, {1, 1} },  //( (Ax1m,Ax1b),(Ax2m,Ax2b), etc) 
SSIsquelch[] = { 1, 1, 1, 1 },								//Squelch with default values in uW
SSIMax[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} },    //( (Ax1SSIMax,Ax1MaxuW),(Ax2MaxSSI,Ax2MaxuW), etc)
SSIMin[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} },    //( (Ax1SSIMin,Ax1MinuW),(Ax2SSIMin,Ax2MinuW), etc)
positionScale = (LAMBDA / DOUBLE_PASS_INT_POS_COEF) * (1e-6),    //Converts to mm as default
velocityScale = 0.001473352 * (1e-6),      //Converts to m/s
OpticalPower_uW[] = { 0, 0, 0, 0 };

bool	enableResetFindsVelocity[] = { false, false, false, false },
ZMIError[] = { false, false, false, false, false },  //Extra ZMIError is for reference
signal[] = { false, false, false, false, false }, //Extra signal is for ref
testMode[] = { false, false, false, false }; //Extra signal is for ref

// ZMI Scalars
const double	timeScale = 25 * (1e-9),                   //Converts to s as default				
TACI_Spacing_small = 7.19 * (1e-3),
TACI_Spacing_large = (7.19 * 2) * (1e-3);

int Read_Write(char*, struct SIS1100_Device_Struct*, unsigned int, unsigned int*, unsigned short);
int ReadVMEErrs(struct SIS1100_Device_Struct*, unsigned char);
int InitAxis(struct SIS1100_Device_Struct*);
int Init_SIS_boards(struct SIS1100_Device_Struct*);
int Init_ZMI_bd(struct SIS1100_Device_Struct*);
int ReadSamplePosition37(struct SIS1100_Device_Struct*, unsigned char, double*);
int ReadSamplePosition32(struct SIS1100_Device_Struct*, unsigned char, double*);
int ReadSamplePosition37_ForAllAxis(struct SIS1100_Device_Struct*, double*);
int ReadSamplePosition32_ForAllAxis(struct SIS1100_Device_Struct*, double*);
int ReadPosition37(struct SIS1100_Device_Struct*, unsigned char, double*);
int ReadPosition32(struct SIS1100_Device_Struct*, unsigned char, double*);
int ReadVelocity32(struct SIS1100_Device_Struct*, unsigned char, double*);
int ReadPosition37_ForAllAxis(struct SIS1100_Device_Struct*, double*);
int ReadPosition32_ForAllAxis(struct SIS1100_Device_Struct*, double*);
int ReadVelocity32_ForAllAxis(struct SIS1100_Device_Struct*, double*);
int ReadTime32(struct SIS1100_Device_Struct*, unsigned char, double*);
int ReadTime32_ForAllAxis(struct SIS1100_Device_Struct*, double*);
int ReadAllTime32(struct SIS1100_Device_Struct*, double*);
int ReadOpticalPowerUsingSSIav(struct SIS1100_Device_Struct*);
int ReadAPDGain(struct SIS1100_Device_Struct*, unsigned char, double*);
int EnableAuxRegisters(struct SIS1100_Device_Struct*, unsigned char);
int DisableAuxRegisters(struct SIS1100_Device_Struct*, unsigned char);
int Sclk_On(struct SIS1100_Device_Struct*);
int Sclk_Off(struct SIS1100_Device_Struct*);
int SetSampTimerFreq(struct SIS1100_Device_Struct*, unsigned short);
int SetHoldSampEnable(struct SIS1100_Device_Struct*);
int ResetHoldSampEnable(struct SIS1100_Device_Struct*);
int SetSampFlag(struct SIS1100_Device_Struct*, double);
int EnableSampleTimer(struct SIS1100_Device_Struct*);
int VMESysReset(struct SIS1100_Device_Struct*);
bool GetVMEExtSampFlag(struct SIS1100_Device_Struct*, unsigned char);
int Disable32bitsOverflow(struct SIS1100_Device_Struct*, unsigned char);
int Enable32bitsOverflow(struct SIS1100_Device_Struct*, unsigned char);
int Enable37bitsSignExtension(struct SIS1100_Device_Struct*, unsigned char);
int EnableSinglePassInterferometer(void);
int EnableDoublePassInterferometer(void);
int ReadAPDGain_ForAllAxis(struct SIS1100_Device_Struct*, double*);
int SampleVMEPosition(struct SIS1100_Device_Struct*, unsigned char);
int ParseVMEErrorStatus2(struct SIS1100_Device_Struct*, unsigned char, unsigned int*);
int ParseVMEPosErrs(struct SIS1100_Device_Struct*, unsigned char, unsigned int*);
int ParseVMEErrorStatus1(struct SIS1100_Device_Struct*, unsigned char, unsigned int*);
int ParseVMEErrorStatus0(struct SIS1100_Device_Struct*, unsigned char, unsigned int*);
int ParseAPDErrCode(struct SIS1100_Device_Struct*, unsigned char, unsigned int*);
int BoardControlMode(struct SIS1100_Device_Struct*, unsigned char, unsigned int);
int BiasControlMode(struct SIS1100_Device_Struct*, unsigned char, unsigned int);
int StartBiasCalculation(struct SIS1100_Device_Struct*, unsigned char);
int SetAPDGainL2(struct SIS1100_Device_Struct*, unsigned char, unsigned int);

int SetAPDSigRMSL2(struct SIS1100_Device_Struct*, unsigned char, unsigned int);
int SetAPDOptPwrL2(struct SIS1100_Device_Struct*, unsigned char, unsigned int);
int ResetAxis(struct SIS1100_Device_Struct*, unsigned char);
int WaitResetComplete(struct SIS1100_Device_Struct*, unsigned char);
int SetPositionOffset32(struct SIS1100_Device_Struct*, unsigned char, unsigned int);
int SetPositionOffset37(struct SIS1100_Device_Struct*, unsigned char, unsigned int, unsigned int);
int EnableVMEInterrupt_bit(struct SIS1100_Device_Struct*, unsigned char, unsigned short);
int DisableVMEInterrupt_bit(struct SIS1100_Device_Struct*, unsigned char, unsigned short);
int EnableVMEGlobalInterrupt(struct SIS1100_Device_Struct*, unsigned char);
int DisableGlobalInterrupt(struct SIS1100_Device_Struct*, unsigned char);
int DisableAllVMEInterrupts(struct SIS1100_Device_Struct*, unsigned char);
int SetKpAndKvCoeff(struct SIS1100_Device_Struct*, unsigned char, unsigned short, unsigned short);
int ReadAPDCtrlSoftErrs(struct SIS1100_Device_Struct*, unsigned char);
int ReadAllErrs(struct SIS1100_Device_Struct*, unsigned char);
int SetTimeDelayBetweenResAndCompleteBit(struct SIS1100_Device_Struct*, unsigned char, unsigned char);
int EnableAllVMEInterrupts(struct SIS1100_Device_Struct*, unsigned char );
int EnableVMEGlobalInterrupt(struct SIS1100_Device_Struct*, unsigned char );
int setVMEIntVector(struct SIS1100_Device_Struct* , unsigned char , unsigned char);
int setVMEIntLevel(struct SIS1100_Device_Struct*, unsigned char , unsigned char );
int sis3301w_Init(struct SIS1100_Device_Struct*, uint32_t, uint32_t, uint32_t);
int	AckForSis3100VME_Irq(struct SIS1100_Device_Struct*, uint32_t);
int EEPROMread(
	struct SIS1100_Device_Struct*,
	unsigned short,
	unsigned int*,
	unsigned short nBytes);


#define THREADCOUNT 4 

HANDLE vmeIrq6Event, lemoIN1Event;
HANDLE  hThreadArray[THREADCOUNT];
HANDLE vmeIntThread, lemoIN1Thread, fastReadThread, WaitForSis3100IrqThread, WaitForVmeIrqThread;
DWORD WINAPI vmeIntThreadFunc(LPVOID);
DWORD WINAPI lemoIN1ThreadFunc(LPVOID);
DWORD WINAPI readThreadFunc(LPVOID); 
DWORD WINAPI fastReadThreadFunc(LPVOID);
DWORD	WaitForVmeIrqThreadFunc(LPVOID);
DWORD	WaitForSis3100IrqThreadFunc(LPVOID);

UINT sisIrqMask = DOORBELL_DSP_IRQ |
DOORBELL_LEMO_IN1_IRQ |
DOORBELL_LEMO_IN2_IRQ |
DOORBELL_LEMO_IN3_IRQ |
DOORBELL_FLAT_IN4_IRQ |
DOORBELL_FLAT_IN3_IRQ |
DOORBELL_FLAT_IN2_IRQ |
DOORBELL_FLAT_IN1_IRQ ;
UINT vmeIrqMask = 
DOORBELL_VME_IRQ1 |
DOORBELL_VME_IRQ2 |
DOORBELL_VME_IRQ3 |
DOORBELL_VME_IRQ4 |
DOORBELL_VME_IRQ5 |
DOORBELL_VME_IRQ6;
void CreateEvents(void)
{

	// Create a manual-reset event object. The write thread sets this
	// object to the signaled state when it finishes writing to a 
	// shared buffer. 


	lemoIN1Event = CreateEvent(
		NULL,               // default security attributes
		TRUE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("lemoIN1Event")  // object name
	);

	if (lemoIN1Event == NULL)
	{
		printf("CreateEvent failed (%d)\n", GetLastError());
		return;
	}

	vmeIrq6Event = CreateEvent(
		NULL,               // default security attributes
		TRUE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("vmeIrq6Event")  // object name
	);
	if (vmeIrq6Event == NULL)
	{
		printf("CreateEvent failed (%d)\n", GetLastError());
		return;
	}

}
void CreateThreads(void)
{
	int i=0;
	DWORD dwThreadID;
	
	
	// Create  thread 
		// TODO: More complex scenarios may require use of a parameter
		//   to the thread procedure, such as an event per thread to  
		//   be used for synchronization.
	vmeIntThread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		vmeIntThreadFunc,        // name of the thread function
		NULL,              // no thread parameters
		0,                 // default startup flags
		&dwThreadID);

	if (vmeIntThread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return RET_FAILED;
	}
	else
		hThreadArray[0] = vmeIntThread;

	WaitForSis3100IrqThread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		WaitForSis3100IrqThreadFunc,        // name of the thread function
		NULL,              // no thread parameters
		0,                 // default startup flags
		&dwThreadID);
	if (WaitForSis3100IrqThread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return RET_FAILED;
	}
	else
		hThreadArray[1] = WaitForSis3100IrqThread;

	WaitForVmeIrqThread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		WaitForVmeIrqThreadFunc,        // name of the thread function
		NULL,              // no thread parameters
		0,                 // default startup flags
		&dwThreadID);
	if (WaitForVmeIrqThread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return RET_FAILED;
	}
	else
		hThreadArray[2] = WaitForVmeIrqThread;

	lemoIN1Thread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		lemoIN1ThreadFunc,        // name of the thread function
		NULL,              // no thread parameters
		0,                 // default startup flags
		&dwThreadID);
	if (lemoIN1Thread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return RET_FAILED;
	}
	else
		hThreadArray[3] = lemoIN1Thread;
	/**
	fastReadThread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		fastReadThreadFunc,        // name of the thread function
		NULL,              // no thread parameters
		0,                 // default startup flags
		&dwThreadID);

	if (fastReadThread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return;
	}*/
}
void CloseThreads()
{
	// Close all event handles (currently, only one global handle).
	CloseHandle(vmeIntThread);
	CloseHandle(lemoIN1Thread);
	CloseHandle(WaitForSis3100IrqThread);
	CloseHandle(WaitForVmeIrqThread);
}

void CloseEvents()
{
	// Close all event handles (currently, only one global handle).

	CloseHandle(vmeIrq6Event);
	CloseHandle(lemoIN1Event);
}
HANDLE hDevice = INVALID_HANDLE_VALUE;  // handle to the drive to be examined 
BOOL bResult = FALSE;                 // results flag
DWORD junk = 0;                     // discard results

unsigned int pdg[100];
#define wszDrive L"\\\\.\\PhysicalDrive0"
volatile int irq;
//int irqlevel=3;
//int irqvector=37;

unsigned int gl_vme_irq_level;
unsigned int gl_vme_irq_vector;
unsigned int gl_irq_loop_counter;
USHORT end_read = 0;
PUINT base_A24D32_FR_ptr, base_A24D32_ptr;
DWORD dwWaitResult;
struct sis1100_irq_ctl irqctl;
struct sis1100_irq_get irqget;
struct sis1100_irq_ack irqack;
HANDLE ghMutex;
int main(void)
{
	

	//======================================================================
	double position[] = { 0, 0, 0, 0 },
	time[] = { 0, 0, 0, 0 },
		velocity[] = { 0, 0, 0, 0 },
		Period = 1 / 3000;	//sample period in sec
	const unsigned short access_mode_AM_value[MAX_NOF_ACCESS_MODE_DEFINES] = {
		0x2F, // Configuration ROM/Control&Status Register (CR/CSR)
		0x2F, // Configuration ROM/Control&Status Register (CR/CSR)
		0x29, // A16 non privileged access
		0x29, // A16 non privileged access
		0x29, // A16 non privileged access
		0x39, // A24 non privileged data access
		0x39, // A24 non privileged data access
		0x39, // A24 non privileged data access
		0x9,  // A32 non privileged data access
		0x9,  // A32 non privileged data access
		0x9   // A32 non privileged data access
	};

	double unitScale[4][4] = { {positionScale * (10 ^ 3), positionScale * (10 ^ 6), positionScale * (10 ^ 9), 1} \
					   , {timeScale, timeScale * (10 ^ 3), timeScale * (10 ^ 6), 1} \
					   , {velocityScale, velocityScale * (10 ^ 3), velocityScale * (10 ^ 6), 1} \
					   , {1 * (10 ^ -3), 1, 1 * (10 ^ 3), 1} };
	
	// Create a mutex with no initial owner

	ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (ghMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}
	/*
		printf("Parsing arguments ... \n");

		strcpy_s(ch_arguments, sizeof(ch_arguments), ":hM:A:W:");
		if (argc > 1) {

			while ((int_ch = getopt(argc, argv, ch_arguments)) != -1)

				switch (int_ch) {
				case 'M':
					sscanf_s(optarg, "%s", ch_access_mode, (unsigned)_countof(ch_access_mode));
					//printf("-M %ADD    \n", ch_access_mode);
					//strcpy(sis3153_ip_addr_string, ch_string);
					break;
				case 'A':
					sscanf_s(optarg, "%X", &uint_vme_address);
					//printf("uint_vme_address = 0x%08X   \n", uint_vme_address);
					break;
				case 'W':
					sscanf_s(optarg, "%X", &uint_vme_data);
					uint_vme_write_flag = 1;
					//printf("uint_vme_data = 0x%08X   \n", uint_vme_data);

					break;
				case '?':
				case 'h':
					printf("   \n");
					printf("Usage: %s  [-?h]  [-M VME Access Mode (string)] [-A VME Address (hex)] [-W VME Write Data (hex)] ", argv[0]);
					printf("   \n\n");
					printf("   -M string     VME Access Mode       Default = %s\n", ch_access_mode);
					printf("   -A hex        VME Address           Default = 0x%08X\n", uint_vme_address);
					printf("   -W hex        VME Write Data	       Default = VME Read \n");
					printf("   \n");
					printf("   -h            Print this message\n");
					printf("   \n");
					for (i = 0; i < MAX_NOF_ACCESS_MODE_DEFINES; i++) {
						printf("   defined VME Access Mode %s   \tVME AM = %02X  \n", access_mode_Selection[i], access_mode_AM_value[i]);
					}
					printf("   \n");
					//printf("   28. Sept. 2020\n");
					break;
				default:
					printf(" print %s -h to get help", argv[0]);
					exit(EXIT_SUCCESS);
				}

		} // if (argc > 1)
		printf("\n Arguments Parsed\n");
	*/
	//_CRT_SECURE_NO_WARNINGS = 1;

	Init_SIS_boards(&dev);
	//Sleep(10);
	//Init_ZMI_bd(&dev);

	//InitAxis(&dev);
	EnableSinglePassInterferometer();
	//SetSampFlag(&dev, 1e-2);
	//EnableSampleTimer(&dev);

	// TODO: Create the shared buffer

	// Create events and THREADCOUNT threads to read from the buffer

	

	// At this point, the reader threads have started and are most
	// likely waiting for the global event to be signaled. However, 
	// it is safe to write to the buffer because the event is a 
	// manual-reset event.

	//WriteToBuffer();
	//GetDeviceHandle(wszDrive);

	vme_irq_level = INT_LEVEL6;
	vme_irq_vector = 12;
	CreateThreads();
	dwWaitResult = WaitForSingleObject( //wait for the main thread to sent an event
		ghMutex, // event handle
		INFINITE);    // indefinite wait*/
	while (1)
	{
		ReadOpticalPowerUsingSSIav(&dev);
		ReadSamplePosition32(&dev, AXIS3, position);
		//ReadPosition32(&dev, AXIS3, position);

		//ReadTime32_ForAllAxis(&dev, time);
		//ReadVelocity32_ForAllAxis(&dev, time);
		/*dwWaitResult = WaitForSingleObject( //wait for the main thread to sent an event
			ghMutex, // event handle
			INFINITE);    // indefinite wait*/
			//ReadAllErrs(&dev, AXIS3);
			/*if (!ReleaseMutex(ghMutex))
				printf("Error while releasing mutex\n");*/
		printf(" Press enter to sample data and read a new value \n");

		scanf_s("%c", sc_char, 2);
		if (!strncmp(sc_char, "q", 1))
			valid_flag = 1;
		printf("Sampling data... \n");
		if (valid_flag == 1)
			break;
		Sleep(1000);
		
		
	}
	//=================================================================
	printf("Main thread waiting for threads to exit...\n");

	// The handle for each thread is signaled when the thread is
	// terminated.
	dwWaitResult = WaitForMultipleObjects(
		3,
		hThreadArray,     //  thread handle
		TRUE,
		INFINITE);

	switch (dwWaitResult)
	{
		// All thread objects were signaled
	case WAIT_OBJECT_0:
		printf("All threads ended, cleaning up for application exit...\n");
		break;

		// An error occurred
	default:
		printf("WaitForMultipleObjects failed (%d)\n", GetLastError());
		return 1;
	}

	// Close the events to clean up
	
	CloseHandle(ghMutex);
	CloseThreads();
	return RET_SUCCESS;
}

DWORD WINAPI lemoIN1ThreadFunc(LPVOID lpParam)
{
	// lpParam not used 
	UNREFERENCED_PARAMETER(lpParam);

	uint32_t get_irq_level = 0;
	DWORD dwWaitResult = 0;
	unsigned int loop_cnt, error_cnt;
	//------------------------------------------------------------------------------------
	error_cnt = 0;
	loop_cnt = 0;
	printf("Thread lemoIN1 is running\n");
	do {
		dwWaitResult = WaitForSingleObject(
			lemoIN1Event,    // handle to mutex
			1000);  // 1s time-out interval

		switch (dwWaitResult)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
				printf("Interrupt Thread %d is using the dev structure...\n",
				GetCurrentThreadId());
				printf(" \n\n\n\tA LEMO INTERRUPT HAS OCCURED \n\n\n");
				loop_cnt++;
			break;
		case WAIT_ABANDONED:
			break;
		default:
			break;
		}
	} while (valid_flag != 1);
printf("==============================================================\n");
printf("nbr of LEMO interrupt %d\n", loop_cnt);
printf("==============================================================\n");
	//result = scanf("%s", line_in);

	//------------------------------------------------------------------------------------
	/*
	dwWaitResult = WaitForSingleObject( //wait for the main thread to sent an event
		ghMutex, // event handle
		INFINITE);    // indefinite wait

	switch (dwWaitResult)
	{
		// Event object was signaled
	case WAIT_OBJECT_0:
		printf("Closing Interrupt Handler \n");
		/* close VME environment
		sis1100w_Close(&dev);
		if (!ReleaseMutex(ghMutex))
			printf("Error while releasing mutex\n");
		break;

		// An error occurred
	default:
		printf("Wait error (%d)\n", GetLastError());

		return RET_SUCCESS;
	}
	*/
	// Now that we are done reading the buffer, we could use another
	// event to signal that this thread is no longer reading. This
	// example simply uses the thread handle for synchronization (the
	// handle is signaled when the thread terminates.)

	printf("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}
DWORD WINAPI vmeIntThreadFunc(LPVOID lpParam)
{
	// lpParam not used in this example.
	UNREFERENCED_PARAMETER(lpParam);
	uint32_t get_irq_level = 0x6;
	DWORD dwWaitResult=0;
	unsigned int loop_cnt, error_cnt;
	int rc;
	//------------------------------------------------------------------------------------
	error_cnt = 0;
	loop_cnt = 0;
	do {
		dwWaitResult = WaitForSingleObject(
			vmeIrq6Event,    // handle to mutex
			1000);  // 1s time-out interval

		switch (dwWaitResult)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
				// TODO: Write to the database
				printf("Interrupt Thread %d is using the dev structure...\n",
				GetCurrentThreadId());
				printf(" \n\n\n\tA VME INTERRUPT HAS OCCURED \n\n\n");
				rc = vme_IACK_D8_read(&dev, get_irq_level, &read_irq_vector);
				if (rc != 0) printf("IACK Cycle:  rc = 0x%08x\n", rc);
				printf(" read_irq_vector =  %x \r\n", read_irq_vector);
			break;
		case WAIT_ABANDONED:
			break;
		default:
			break;
		}
	} while (valid_flag != 1);
	//result = scanf("%s", line_in);

	//------------------------------------------------------------------------------------
	/*
	dwWaitResult = WaitForSingleObject( //wait for the main thread to sent an event
		ghMutex, // event handle
		INFINITE);    // indefinite wait
		
	switch (dwWaitResult)
	{
		// Event object was signaled
	case WAIT_OBJECT_0:
		printf("Closing Interrupt Handler \n");
		/* close VME environment 
		sis1100w_Close(&dev);
		if (!ReleaseMutex(ghMutex))
			printf("Error while releasing mutex\n");
		break;

		// An error occurred
	default:
		printf("Wait error (%d)\n", GetLastError());
		
		return RET_SUCCESS;
	}
	*/
	// Now that we are done reading the buffer, we could use another
	// event to signal that this thread is no longer reading. This
	// example simply uses the thread handle for synchronization (the
	// handle is signaled when the thread terminates.)

	printf("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}
/*********************************************************/
/*
DWORD WINAPI fastReadThreadFunc(LPVOID lpParam)
{
	// lpParam not used in this example.
	UNREFERENCED_PARAMETER(lpParam);

	DWORD dwWaitResult = 0;
	unsigned int position;
	printf(" Thread %d is running...\n",GetCurrentThreadId());
	do {
		//ReadSamplePosition32(&dev, AXIS3, &position);
	} while (0);//1
	printf("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}

DWORD WINAPI readThreadFunc(LPVOID lpParam)
{
	// lpParam not used in this example.
	UNREFERENCED_PARAMETER(lpParam);

	DWORD dwWaitResult = 0;
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0,
		get_lwords = 0,
		no_of_lwords=0;
	PUINT ptr = base_A24D32_ptr;
	printf(" Thread %d is running...\n", GetCurrentThreadId());
	do {
		for (USHORT i = 0; i < 0x1C7; i = i + 4) {
			uint_vme_address = BASE_ADDRESS + i;
			return_code = vme_A32DMA_D32_read(&dev, uint_vme_address, &uint_vme_data, no_of_lwords, &get_lwords);
			if (return_code != 0) {
				printf("return Error vme_A32DMA_D32_read:   return_code = 0x%08x  at address = 0x%08x\n", return_code, uint_vme_address);
				return RET_FAILED;
			}
			if (no_of_lwords != get_lwords) {
				printf("length Error vme_A32DMA_D32_read:   must length = 0x%08x  read length = 0x%08x\n", no_of_lwords, get_lwords);
				return RET_FAILED;
			}
			*(base_A24D32_ptr++) = uint_vme_data;
		}
		base_A24D32_ptr = ptr;
	} while (!end_read);
	printf("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}
*/
int allocateWinMemSpace(struct SIS1100_Device_Struct* dev, UCHAR *nof_windows) {

	UINT nof_vme_windows = 2;
	UINT mapParams[2 * 4] = {  // 2 descriptors (Address windows) each contains 4 32-bit entries 

		// 1.descriptor 
		0xff010800, /* protocol header */
		0x39,       /* A24 */
		0x00000000, /* VME Base Address              */
		0,

		// 2.descriptor 
		0xff010800, /* protocol header */
		0x39,       /* A24 */
		0x00400000, /* VME Base Address              */
		0,

	};

	// Map windows
	stat = sis1100w_vme_map(dev, mapParams, nof_vme_windows * 4);
	if (stat != Stat1100Success) {
		printf("Error in 'sis1100w_vme_map': %d\n", stat);
		printf("Note: Set mapping size from 256MiB to 64MiB on the SIS1100(-eCMC/-e2) device to reduce the mapping window \n");
		printf("      Use the program: mapwindow/mapwindow.exe \n");
		printf("      Reboot the PC after changing the mapping size \n\n");
		return RET_FAILED;
	}

	// get Map windows pointer
	PUINT mappedArea = NULL;
	stat = sis1100w_vme_map_get_ptr(dev, &mappedArea);
	if (stat != Stat1100Success) {
		printf("Error in 'sis1100w_vme_map_get_adr': %d\n", stat);
		return RET_FAILED;
	}
	printf("mapped area: %p\n", mappedArea);

	/* VME Windows pointer */
	PUCHAR vme_window1_ptr = (PUCHAR)mappedArea;                    // 1st 4MB block;
	PUCHAR vme_window2_ptr = (PUCHAR)mappedArea + (1 * 0x400000);    // 2st 4MB block;

	// VME Address Pointer definitons

		//1.descriptor 4MB block A24/D32-cycles ;
	base_A24D32_FR_ptr = (PUINT)(vme_window1_ptr);  // D32 cycle pointer with VME Base Address 0x00000000  
	//*(base_A24D32_0x000000_ptr + 0x0)      -> first VME address 0x00000000
	//*(base_A24D32_0x000000_ptr + 0xFFFFF)  -> last  VME address 0x003FFFFC
	// To use in fast position reading cycle

	//2.descriptor 4MB block A24/D32-cycles ;
	base_A24D32_ptr = (PUINT)(vme_window2_ptr);  // D32 cycle pointer with VME Base Address 0x00000000  
	//*(base_A24D32_0x000000_ptr + 0x0)      -> first VME address 0x00000000
	//*(base_A24D32_0x000000_ptr + 0xFFFFF)  -> last  VME address 0x003FFFFC
	//To use in central read thread

}

int releaseWinMemSpace(struct SIS1100_Device_Struct* dev, UCHAR nof_vme_windows) {
	// cleanup
	stat = sis1100w_vme_unmap(dev, nof_vme_windows * 4);
	if (stat != Stat1100Success) {
		printf("Error in 'sis1100w_vme_unmap': %d\n", stat);
		return RET_FAILED;
	}

	sis1100w_Close(dev);
	printf("Windows -vme map demo- finished \n");

}
int sis3301w_Init(
	struct SIS1100_Device_Struct* dev,
	uint32_t mod_base,
	uint32_t vme_irq_level,
	uint32_t vme_irq_vector
)
{
	int rc;
	uint32_t addr, data;

	/* reset  */
	addr = mod_base + SIS3302_KEY_RESET;
	rc = s3100_control_write(dev, addr, 0x0);
	if (rc != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}

	/* irq level  vector  */
	addr = mod_base + SIS3302_IRQ_CONFIG;
	//data =  (vme_irq_vector & 0xff) + (((vme_irq_level & 0x7) + 0x8) << 8) ;
	//data =  0x1b01 ;
	//data =  0x1A01 ;
	//data =  0x1801 + 0x300 ;
	data = (vme_irq_vector & 0xff) + (((vme_irq_level & 0x7) + 0x8) << 8);
	if (s3100_control_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}

	/* irq source  control  */
	addr = mod_base + SIS3302_IRQ_CONTROL;
	data = 0x2;
	if (s3100_control_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}


	/* max_nof_events  */
	addr = mod_base + SIS3302_MAX_NOF_EVENT;
	data = 0x100;
	if (s3100_control_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}

	// why ?
#ifdef not_used
	/* control  */
	addr = mod_base + SIS3302_CONTROL_STATUS;
	data = 0x0;
	if (vme_A32D32_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}
	// why ?
	/* control  */
	addr = mod_base + SIS3302_CONTROL_STATUS;
	data = 0x0;
	if (vme_A32D32_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}
#endif

	/* Acqconf  */
	addr = mod_base + SIS3302_ACQUISTION_CONTROL;
	data = 0x130; // SIS3302_ACQ_ENABLE_LEMO_START_STOP + SIS3302_ACQ_ENABLE_MULTIEVENT + SIS3302_ACQ_ENABLE_AUTOSTART
	if (s3100_control_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}

	/* Startdelay  */
	addr = mod_base + SIS3302_START_DELAY;
	data = 0x20; //  
	if (s3100_control_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}
	/* Stopdelay  */
	addr = mod_base + SIS3302_STOP_DELAY;
	data = 0x320; //  
	if (s3100_control_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}


	/* Event Config  */
	addr = mod_base + SIS3302_EVENT_CONFIG_ALL_ADC;
	data = 0x17; //  EVENT_CONF_ENABLE_WRAP_PAGE_MODE + EVENT_CONF_PAGE_SIZE_1K_WRAP
	if (s3100_control_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}

#ifdef not_used

	/* Acqconf  */
	addr = mod_base + SIS3302_ACQUISTION_CONTROL;
	data = 0x130; // SIS3302_ACQ_ENABLE_LEMO_START_STOP + SIS3302_ACQ_ENABLE_MULTIEVENT + SIS3302_ACQ_ENABLE_AUTOSTART
	if (vme_A32D32_write(dev, addr, data) != 0) {
		printf("vme_A32D32_write:  rc = 0x%08x  at address = 0x%08x\n", rc, addr);
	}
#endif


	return RET_SUCCESS;
}
	

	DWORD	WaitForVmeIrqThreadFunc(LPVOID lpParam)
	{
		int rc;
		uint32_t doorbell_value=0;
		UINT sis_get_irq_level=0;

		vmeIrq6Event = CreateEvent(
			NULL,               // default security attributes
			FALSE,               // Auto-reset event
			FALSE,              // initial state is nonsignaled
			TEXT("vmeIrq6Event")  // object name
		);
		if (vmeIrq6Event == NULL)
		{
			printf("CreateEvent failed (%d)\n", GetLastError());
			return RET_FAILED;
		}
		sis1100w_sis310x_Register_For_Irq(&dev, vmeIrqMask); //Register to listen to IRQ level interrupt
		//PLX_INTERRUPT intSrc;
		//CreateEvents();
		do {
			//IRQ update on SIS3100
			rc = s3100_control_write(&dev, SIS3100_OPT_IN_IRQ_LATCH, DOORBELL_IRQ_UPDATE);
			if (Stat1100Success != rc) {
				printf("\n\nError in 's3100_control_write' (Thread Running: %s, stopping)\n", __FUNCTION__);
				break;
			}
			rc = sis1100w_sis310x_Wait_For_Irq(&dev, 1000, &doorbell_value); //wait for 1s, use -1 for INFINITE
			if (doorbell_value) {
				printf("\n\n\nDoorbell value is %X \n\n\n", doorbell_value);
				sis_get_irq_level = 0;
				// VME IRQ7
				if ((doorbell_value & DOORBELL_VME_IRQ7) == DOORBELL_VME_IRQ7) {
					sis_get_irq_level = 0x7;
				}

				// VME IRQ6
				if ((doorbell_value & DOORBELL_VME_IRQ6) == DOORBELL_VME_IRQ6) {
					sis_get_irq_level = 0x6;
					printf("\n\n\nSending vmeIrq event to ISR..\n\n\n");
					if (!SetEvent(vmeIrq6Event))
					{
						printf("SetEvent failed (%d)\n", GetLastError());
						break;
					}
					rc = s3100_control_write(&dev, SIS3100_OPT_VME_IRQ_CTRL, VME_IRQ6_STA_CLR_BIT);
					if (Stat1100Success != rc) {
						printf("\n\nError in 's3100_control_write' (Thread Running: %s, stopping)\n", __FUNCTION__);
						break;
					}
				}
				// VME IRQ5
				if ((doorbell_value & DOORBELL_VME_IRQ5) == DOORBELL_VME_IRQ5) {
					sis_get_irq_level = 0x5;
				}

				// VME IRQ4
				if ((doorbell_value & DOORBELL_VME_IRQ4) == DOORBELL_VME_IRQ4) {
					sis_get_irq_level = 0x4;
				}

				// VME IRQ3
				if ((doorbell_value & DOORBELL_VME_IRQ3) == DOORBELL_VME_IRQ3) {
					sis_get_irq_level = 0x3;
				}

				// VME IRQ2
				if ((doorbell_value & DOORBELL_VME_IRQ2) == DOORBELL_VME_IRQ2) {
					sis_get_irq_level = 0x2;
				}

				// VME IRQ1
				if ((doorbell_value & DOORBELL_VME_IRQ1) == DOORBELL_VME_IRQ1) {
					sis_get_irq_level = 0x2;
				}


			}
			doorbell_value = 0;
		} while (valid_flag != 1);
		
		CloseHandle(vmeIrq6Event);
		printf("Terminating Thread %d..\n", GetCurrentThreadId());
		return RET_SUCCESS;
	}
	DWORD	WaitForSis3100IrqThreadFunc(LPVOID lpParam)
	{
		int rc;
		uint32_t doorbell_value;
		UINT sis_get_irq_level = 0;

		printf(" Thread %d is running...\n",
			GetCurrentThreadId());
		// Create a manual-reset event object. The write thread sets this
		// object to the signaled state when it finishes writing to a 
		// shared buffer. 
		lemoIN1Event = CreateEvent(
			NULL,               // default security attributes
			FALSE,               // Auto-reset event
			FALSE,              // initial state is nonsignaled
			TEXT("lemoIN1Event")  // object name
		);

		if (lemoIN1Event == NULL)
		{
			printf("CreateEvent failed (%d)\n", GetLastError());
			return RET_FAILED;
		}	

		sis1100w_sis310x_Register_For_Irq(&dev, sisIrqMask); //Register to listen to IRQ level interrupt
		//CreateEvents();
		do {
			//IRQ update on SIS3100
			rc = s3100_control_write(&dev, SIS3100_OPT_IN_IRQ_LATCH, DOORBELL_IRQ_UPDATE);
			if (Stat1100Success != rc) {
				printf("\n\nError in 's3100_control_write' (IRQ Running: %d, stopping)\n", rc);
				continue;
			}
			rc = sis1100w_sis310x_Wait_For_Irq(&dev, 1000, &doorbell_value); //wait for 1s, use -1 for INFINITE
			if (doorbell_value) {
				printf("\n\n\nDoorbell value is %X \n\n\n", doorbell_value);
				// LEMO IN1
				if ((doorbell_value & DOORBELL_FLAT_IN3_IRQ) == DOORBELL_FLAT_IN3_IRQ) {
					sis_get_irq_level = 0x8;
					printf("\n\n\nSending vmeIrq event to ISR..\n\n\n");
					if (!SetEvent(lemoIN1Event))
					{
						printf("SetEvent failed (%d)\n", GetLastError());
						break;
					}
					rc = s3100_control_write(&dev, SIS3100_OPT_IN_IRQ_LATCH, FLAT_IN3_IRQ_STA_CLR_BIT);
					if (Stat1100Success != rc) {
						printf("\n\nError in 's3100_control_write' (Thread Running: %s, stopping)\n", __FUNCTION__);
						break;
					}
				}
			}
			doorbell_value = 0;
		} while (valid_flag != 1);

		CloseHandle(lemoIN1Event);
		printf("Terminating Thread %d..\n", GetCurrentThreadId());
		return RET_SUCCESS;
	}

	int	AckForSis3100VME_Irq(
		struct SIS1100_Device_Struct* dev,
		uint32_t sis_get_irq_level
	)
	{
		int rc;
		uint32_t irq_level;

		//	#ifdef raus
		irq_level = sis_get_irq_level & 0x7;
		switch (irq_level) {
		case 0:
			rc = -1;
			break;
		case 1:
			rc = s3100_control_write(dev, SIS3100_OPT_VME_IRQ_CTRL, VME_IRQ1_STA_CLR_BIT);
			break;
		case 2:
			rc = s3100_control_write(dev, SIS3100_OPT_VME_IRQ_CTRL, VME_IRQ2_STA_CLR_BIT);
			break;
		case 3:
			rc = s3100_control_write(dev, SIS3100_OPT_VME_IRQ_CTRL, VME_IRQ3_STA_CLR_BIT);
			break;
		case 4:
			rc = s3100_control_write(dev, SIS3100_OPT_VME_IRQ_CTRL, VME_IRQ4_STA_CLR_BIT);
			break;
		case 5:
			rc = s3100_control_write(dev, SIS3100_OPT_VME_IRQ_CTRL, VME_IRQ5_STA_CLR_BIT);
			break;
		case 6:
			rc = s3100_control_write(dev, SIS3100_OPT_VME_IRQ_CTRL, VME_IRQ6_STA_CLR_BIT);
			break;
		case 7:
			rc = s3100_control_write(dev, SIS3100_OPT_IN_IRQ_LATCH, VME_IRQ7_STA_CLR_BIT);
			break;
		case 8:
			rc = s3100_control_write(dev, SIS3100_OPT_IN_IRQ_LATCH, FLAT_IN3_IRQ_STA_CLR_BIT);
			break;
		}
		//#endif
		/*dwWaitResult = WaitForSingleObject(
		ghMutex,    // handle to mutex
			INFINITE);  // no time-out interval
			*/
			//IRQ update on SIS3100
		rc = s3100_control_write(dev, SIS3100_OPT_VME_IRQ_CTRL, DOORBELL_IRQ_UPDATE);
		/*
		if (!ReleaseMutex(ghMutex))
			printf("Int: Error while releasing mutex\n");
			*/
		return rc;
	}


int EnableSinglePassInterferometer(void) {

	positionScale = (LAMBDA / DOUBLE_PASS_INT_POS_COEF) * (1e-6);    //Converts to mm as default
	velocityScale = SINGLE_PASS_INT_VEL_COEF * (1e-6);    //Converts to m/s as default
	return RET_SUCCESS;
}
int EnableDoublePassInterferometer(void) {

	positionScale = (LAMBDA / DOUBLE_PASS_INT_POS_COEF) * (1e-6);    //Converts to mm as default
	velocityScale = DOUBLE_PASS_INT_VEL_COEF * (1e-6);    //Converts to m/s as default
	return RET_SUCCESS;
}
int InitAxis(struct SIS1100_Device_Struct* dev) {
	/*************************Axis Initialization***********************************/
	char	ch_access_mode[16];
	unsigned int	vme_data = 0,
		uint_vme_address = 0,
		uint_vme_data = 0;


	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);

	SetTimeDelayBetweenResAndCompleteBit(dev, AXIS3, 0); 
	//sis1100w_sis310x_Register_For_Irq(dev, sis_irq_mask); //Register to listen to IRQ6 level interrupt
	setVMEIntLevel(dev, AXIS3, INT_LEVEL6);//3
	setVMEIntVector(dev, AXIS3, 0x12);
	EnableVMEGlobalInterrupt(dev, AXIS3);
	EnableAllVMEInterrupts(dev, AXIS3);
	for (int a = 1; a < 5; a++) {

		//DisableAllVMEInterrupts(dev, a);
	
		Disable32bitsOverflow(dev, a);
		Enable37bitsSignExtension(dev, a);				// enable sign extension of 32 bits to match 37 bits register size 
																			// when register data is written
		SetPositionOffset37(dev, a, 0, 0);
		SetKpAndKvCoeff(dev, a, 4, 4);					// Set Kp = -6 and Kv = -15		

		BoardControlMode(dev, a, BIAS_CONSTANT_VOLT_MODE);
		ResetAxis(dev, a);
	}

	uint_vme_data = 0;
	// Verifying reset complete for only 1 axis is sufficient
	if (WaitResetComplete(dev, 4) < 0)	// Wait for reset complete on the main axis
		exit(EXIT_FAILURE);
	//Sleep(10);

	return RET_SUCCESS;
}
int DisableAllVMEInterrupts(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis-1], zVMEIntEnab0);				// Disable VME interrupts 0
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);				// Disable VME interrupts 1
	uint_vme_data = 0x8000;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab2);				// Disable VME interrupts 2
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int EnableAllVMEInterrupts(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data =0xFFFF;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab0);				// VME interrupts 0

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);				// VME interrupts 1
	uint_vme_data |= 0x811F;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data = 0xF0FF;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab2);				//  VME interrupts 2
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int EnableVMEGlobalInterrupt(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);				// Disable VME interrupts 
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= 0x8000;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}

/// <summary>
/// This function configures the Flyscan mode to continuously acquire position data from all 4 axes
/// 
/// </summary>
/// <param name="dev"> device to be used</param>
/// <param name="nbrAxis">number of axis </param>
/// <param name="freqKHz">
/// flyscan frequency in KHz
/// </param>
/// /// <param name="trig">
/// 1: acquisition on transition from 1 to 0
/// 0: acquisition on transition from 0 to 1
/// </param>
/// <returns>
/// -1 if unsuccessful
/// 0 else
/// </returns>
int configureFlyscan(struct SIS1100_Device_Struct* dev, unsigned char nbrAxis, USHORT freqKHz, UCHAR trig) {
	/*'
		'4 X 8kSamples of 32 bit position values at FULL resolution of lambda/4096/8
		' returns false if unsuccessful
		' sample freq in mHz 10MHZ is max
		' trigger type: instant = 0
		'               P2D_In = 1*/
#define masterAxisAddr	0x2000

	short rdVal = 0, sclkVal = 0;
	UINT diagSrc = 0;
	UINT uint_vme_data = 0, uint_vme_address = 0;
	int ramAxisAddr = 0x0;

	/* Check if RAM is busy*/
	if (!isRAMbusy(dev)) 
		return RET_FAILED;
	if ((nbrAxis > 2) & (freqKHz > 8)) {
		freqKHz = 8;
		printf("Max freq is 8KHz for 4 axis\n");
	}

	SetSampFlag(dev, freqKHz);
	Sclk_On(dev);
	if (nbrAxis <= 2)
		diagSrc = 0x8000;
	else
		diagSrc = 0x9000;
	if (trig)
		diagSrc += 0x400;
	//Setup axis 1 and 2
	uint_vme_address = ADD(BASE_ADDRESS[AXIS1],zDiagFFTCtrl) ;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	//Setup axis 3 and 4
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3], zDiagFFTCtrl);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	//Option to start acquire immediately
	if (!trig) {
		//check if RAM is Busy
		if (!isRAMbusy(dev)) {
			printf("Can not start acquisition while RAM is busy\n");
			return RET_FAILED;
		}
		//Start acquisition on axis 1 and 2
		uint_vme_address = ADD(BASE_ADDRESS[AXIS1], zTestCmd1);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		//Start acquisition on axis 3 and 4
		uint_vme_address = ADD(BASE_ADDRESS[AXIS3], zTestCmd1);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	}
}
/// <summary>
/// The function allocate the specified memory space on Windows
/// </summary>
/// <param name="mem_size"> the size in Kbytes(max val is 10240)</param>
/// <returns>
/// -1 if unsuccessful
/// 0 else
/// </returns>
PUINT allocateMemSpace(UINT mem_size) {

	if (checkValues(mem_size, 0, 10240))
		return RET_FAILED;
	return (PUINT)calloc((UINT)(mem_size/4), sizeof(unsigned int));

}
/// <summary>
/// Reads a memory case, modify the contain and write back the result
/// </summary>
/// <param name="accessMode">
/// access mode to the VME Bus
/// </param>
/// <param name="dev">
/// deviice to be addressed
/// </param>
/// <param name="uint_vme_address">
/// memory case address to be read and modified
/// </param>
/// <param name="uint_vme_data">
/// data to be used to modified the read value
/// </param>
/// <param name="opCode">
/// modify operation to perform:
/// 0 -> logical AND
/// 1 -> logical OR
/// 2 -> addition
/// </param>
/// <returns>
/// 0 if success
/// -1 if failed 
/// </returns>
int readModifyWrite(char* accessMode, 
	struct SIS1100_Device_Struct* dev,
	unsigned int uint_vme_address, 
	unsigned int uint_vme_data,
	unsigned char opCode) {
	UINT vme_data = 0;
	if (Read_Write(accessMode, dev, uint_vme_address, &vme_data, 0) != RET_SUCCESS) {
		printf("Register %6X access Faillure !  \n", uint_vme_address);
		return RET_FAILED;
	}
	switch (opCode)
	{
	case 0:
		vme_data &= (unsigned int)uint_vme_data;
		break;
	case 1:
		vme_data |= (unsigned int)uint_vme_data;
		break;
	case 2:
		vme_data += (unsigned int)uint_vme_data;
		break;
	default:
		break;
	}
	if (Read_Write(accessMode, dev, uint_vme_address, &vme_data, 1) != RET_SUCCESS) {
		printf("Register %6X access Faillure !  \n", uint_vme_address);
		return RET_FAILED;
	}
	return RET_SUCCESS;
}
/// <summary>
/// acquire data after a flyscan setup.
/// The function get measured position from the RAM. It reads 4x8K samples of 16bits words 
/// </summary>
/// <param name="dev"> device</param>
/// <param name="startAdress_axis1">
/// the starting address of the location to store axis 1 and 2 measured position
/// </param>
/// <param name="startAdress_axis3">
/// the starting address of the location to store axis 3 and 4 measured position
/// </param>
/// <returns>
/// 0 if success
/// -1 if failed
/// </returns>
int acquireFlyscanData(struct SIS1100_Device_Struct* dev, unsigned char nbrAxis, PUINT startAddress_axis1, PUINT startAddress_axis3){
#define NBR_RAM_PAGES			64
#define NBR_SAMP_PER_PAGE		512

	USHORT ramPageAddr = 0, uint_vme_data, startAddress=0;
	UINT uint_vme_address=0, nbr_of_read=0;
	if (checkValues(nbrAxis, 1, 4))
		return RET_FAILED;
	switch (nbrAxis)
	{
	case 1:
			uint_vme_address = ADD(zDiagFFTRamData, BASE_ADDRESS[AXIS3]);
			startAddress = startAddress_axis3;
			for (int i = 0; i < 64; i++) {
				if (vme_A24DMA_D16_read(dev, uint_vme_address, startAddress, NBR_SAMP_PER_PAGE, &nbr_of_read) != RET_SUCCESS)
				{
					printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
				}
				else
					printf("%d 16bits words read from DMA  \n", nbr_of_read);
				nbr_of_read = 0;
				if (vme_A24DMA_D16_read(dev, uint_vme_address, startAddress, NBR_SAMP_PER_PAGE, &nbr_of_read) != RET_SUCCESS)
				{
					printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
				}
				else
					printf("%d 16bits words read from DMA  \n", nbr_of_read);
				// Shift to the next page
				readModifyWrite("A24D16", dev, ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS1]), (1 << 10), 2);
				//vme_data = uint_vme_data + (1 << 10);
			}
		break;

	default:

		startAddress = startAddress_axis3;
		for (int k = 0; k < 3; k += 2) {
			uint_vme_address = ADD(zDiagFFTRamData, BASE_ADDRESS[k]);
			for (int i = 0; i < 64; i++) {
				if (vme_A24DMA_D16_read(dev, uint_vme_address, startAddress_axis1, NBR_SAMP_PER_PAGE, &nbr_of_read) != RET_SUCCESS)
				{
					printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
				}
				else
					printf("%d 16bits words read from DMA  \n", nbr_of_read);
				nbr_of_read = 0;
				if (vme_A24DMA_D16_read(dev, uint_vme_address, startAddress_axis1, NBR_SAMP_PER_PAGE, &nbr_of_read) != RET_SUCCESS)
				{
					printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
				}
				else
					printf("%d 16bits words read from DMA  \n", nbr_of_read);
				// Shift to the next page
				readModifyWrite("A24D16", dev, ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS1]), (1 << 10), 2);
				//vme_data = uint_vme_data + (1 << 10);
				startAddress = startAddress_axis1;
			}

		}
		break;
	}
	
}
/// <summary>
/// This function checks whether the RAM is busy or not.
/// </summary>
/// <param name="dev"> device</param>
/// <returns>
/// TRUE if RAM is busy
/// FALSE else
/// </returns>
bool isRAMbusy(struct SIS1100_Device_Struct*  dev) {
	UINT uint_vme_data = 0, uint_vme_address = 0;
	/* Check if RAM is busy*/
	uint_vme_address = BASE_ADDRESS[AXIS3] + zTestStat1;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);
	return FALSE;
	}

	if (!(uint_vme_data & 0x400)) {
		printf("RAM is currently busy\n");
		return FALSE;
	}
	return TRUE;
}
/// <summary>
/// This function configures the interrupt vector on VME BUS for a specific axis
/// axis 1 and 2 used the same interrupt vector. It's similar with axis 3 and 4  
/// </summary>
/// <param name="dev"> device</param>
/// <param name="axis">
/// axis to configure interrupt vector on
/// </param>
/// <param name="IntVect">
/// value of the interrûpt vector to be set. range is 0 to 255
/// </param>
/// <returns>
/// 0 if success
/// -1 if failed 
/// </returns>
int setVMEIntVector(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned char IntVect) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zIntVector);				// Disable VME interrupts 
	if (checkValues(IntVect, 0, 255) < 0)
		return RET_FAILED;
	readModifyWrite("A24D16", dev, uint_vme_address, IntVect, 1);
	return RET_SUCCESS;
}
/// <summary>
/// Checks if a value is within a selected range
/// </summary>
/// <param name="num2check">
/// Value to check
/// </param>
/// <param name="minVal">
/// smallest acceptable value
/// </param>
/// <param name="maxVal">
/// Highest acceptable value
/// </param>
/// <returns>
/// 0 if the value is in the selected range
/// -1 else
/// </returns>
int checkValues(UINT num2check, UINT minVal, UINT maxVal) {
	if (num2check < minVal || num2check > maxVal) {
		pritnf("Bad Value\n");
		pritnf("the range allowed is %d to %d\n", minVal, maxVal);
		return RET_FAILED;
	}
	return RET_SUCCESS;
}
/// <summary>
/// sets interrupt level on VME Bus. Axis 1 and 2 share the same interrupt level, Axis 3 and 4 do the same.
/// </summary>
/// <param name="dev">device </param>
/// <param name="axis">
/// axis to apply configuration on
/// </param>
/// <param name="IntLevel">
/// Int level value. Range is 1 to 7
/// </param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setVMEIntLevel(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned char IntLevel) {
	unsigned int uint_vme_address = 0, uint_vme_data=0;
	if (checkValues(IntLevel, INT_LEVEL0, INT_LEVEL7) < 0)
		return RET_FAILED;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zIntVector);				// Disable VME interrupts 
	uint_vme_data = ((unsigned int)IntLevel) << 8;
	if(readModifyWrite("A24D16", dev, uint_vme_address, uint_vme_data, 1)<0)
		return RET_FAILED;
	return RET_SUCCESS;
}
/// <summary>
/// Disables all interupts on VME bus.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">
/// axis to disable interrupts on.
/// Axis 1 and 2 share the same disable interrupt bit. Axis 3 and 4 do the same
/// </param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int DisableGlobalInterrupt(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);				
	// Disable VME interrupts 
	readModifyWrite("A24D16", dev, uint_vme_address, 0x7FFF, 0);
	return RET_SUCCESS;
}
/// <summary>
/// Enables a specific interrupt bit on the VME Bus.
/// All interrupt bits are defined in the header file vmeInterruptConst.h
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">
/// axis on which interrupt should be set
/// </param>
/// <param name="intNumber">
/// The corresponding interrupt bit
/// </param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int EnableVMEInterrupt_bit(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned short intNumber){
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	if (checkValues(intNumber, MIN_INT_NBR, MAX_INT_NBR) < 0)
		return RET_FAILED;
	if (intNumber < VME_EXT_FLAG_SAMPLE_ERR_INT)
	{
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab0);				
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}return RET_FAILED;}
		switch (intNumber)
		{
		case CEC_ERR_INT:
			uint_vme_data |= 0x8000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}return RET_FAILED;}
			break;
		case PHASE_NOISE_ERR_INT:
			uint_vme_data |= 0x4000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case ACCELERATION_ERR_INT:
			uint_vme_data |= 0x2000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case MEAS_SIG_GLITCH_ERR_INT:
			uint_vme_data |= 0x1000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case MEAS_SIG_DROP_ERR_INT:
			uint_vme_data |= 0x800;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case SSI_MAX_LIM_ERR_INT:
			uint_vme_data |= 0x400;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case MEAS_SIG_SAT_ERR_INT:
			uint_vme_data |= 0x200;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case MEAS_SIG_MIS_ERR_INT:
			uint_vme_data |= 0x100;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case OV_TMP_ERR_INT:
			uint_vme_data |= 0x80;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case FPGA_SYNC_ERR_INT:
			uint_vme_data |= 0x40;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case RES_FAIL_ERR_INT:
			uint_vme_data |= 0x20;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case RES_COMP_ERR_INT:
			uint_vme_data |= 0x10;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case REF_PLL_ERR_INT:
			uint_vme_data |= 0x8;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case REF_SIG_MIS_ERR_INT:
			uint_vme_data |= 0x4;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case WRT_ERR_INT:
			uint_vme_data |= 0x2;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case PWR_ERR_INT:
			uint_vme_data |= 0x1;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		default:
			break;
		}
	}
	else if((intNumber >= VME_EXT_FLAG_SAMPLE_ERR_INT) && (intNumber < PROC_INIT_BSY_ERR_INT))
	{
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);				
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		switch (intNumber)
		{
		case VME_EXT_FLAG_SAMPLE_ERR_INT:
			uint_vme_data |= 0x100;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case P32_POS_OV_ERR_INT:
			uint_vme_data |= 0x10;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case VME32_POS_OV_ERR_INT:
			uint_vme_data |= 0x8;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case VME37_POS_OV_ERR_INT:
			uint_vme_data |= 0x4;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case USR_VEL_ERR_INT:
			uint_vme_data |= 0x2;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case VEL_ERR_INT:
			uint_vme_data |= 0x1;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		default:
			printf("[WARNING] Unknow interrupt number\n");
			break;
		}
	}
	else
	{
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab2);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		switch (intNumber)
		{
		case PROC_INIT_BSY_ERR_INT:
			uint_vme_data |= 0x8000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case PROC_FAIL_ERR_INT:
			uint_vme_data |= 0x4000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case BIAS_SUPPLY_ERR_INT:
			uint_vme_data |= 0x2000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case WRT_PROTECT_ERR_INT:
			uint_vme_data |= 0x1000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case SIG_MAX_ERR_INT:
			uint_vme_data |= 0x80;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case SIG_MIN_ERR_INT:
			uint_vme_data |= 0x40;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case BIAS_CALC_COMP_INT:
			uint_vme_data |= 0x20;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case BIAS_ERR_INT:
			uint_vme_data |= 0x10;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case APD_DC_ERR_INT:
			uint_vme_data |= 0x8;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case BIAS_SET_ERR_INT:
			uint_vme_data |= 0x4;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case APD_FAIL_ERR_INT:
			uint_vme_data |= 0x2;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case APD_TMP_ERR_INT:
			uint_vme_data |= 0x1;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		default:
			break;
		}
	}
	return RET_SUCCESS;
}
/// <summary>
/// Disables a specific interrupt bit on the VME Bus.
/// All interrupt bits are defined in the header file vmeInterruptConst.h
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">
/// axis on which interrupt should be reset
/// </param>
/// <param name="intNumber">
/// The corresponding interrupt bit
/// </param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int DisableVMEInterrupt_bit(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned short intNumber) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	if (intNumber < VME_EXT_FLAG_SAMPLE_ERR_INT)
	{
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab0);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		switch (intNumber)
		{
		case CEC_ERR_INT:
			uint_vme_data &= 0x7FFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case PHASE_NOISE_ERR_INT:
			uint_vme_data &= 0xBFFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case ACCELERATION_ERR_INT:
			uint_vme_data &= 0xDFFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case MEAS_SIG_GLITCH_ERR_INT:
			uint_vme_data &= 0xEFFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case MEAS_SIG_DROP_ERR_INT:
			uint_vme_data &= 0xF7FF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case SSI_MAX_LIM_ERR_INT:
			uint_vme_data &= 0xFBFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case MEAS_SIG_SAT_ERR_INT:
			uint_vme_data &= 0xFDFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case MEAS_SIG_MIS_ERR_INT:
			uint_vme_data &= 0xFEFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case OV_TMP_ERR_INT:
			uint_vme_data &= 0xFF7F;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case FPGA_SYNC_ERR_INT:
			uint_vme_data &= 0xFFBF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case RES_FAIL_ERR_INT:
			uint_vme_data &= 0xFFDF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case RES_COMP_ERR_INT:
			uint_vme_data &= 0xFFEF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case REF_PLL_ERR_INT:
			uint_vme_data &= 0xFFF7;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case REF_SIG_MIS_ERR_INT:
			uint_vme_data &= 0xFFFB;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case WRT_ERR_INT:
			uint_vme_data &= 0xFFFD;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case PWR_ERR_INT:
			uint_vme_data &= 0xFFFE;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		default:
			break;
		}
	}
	else if ((intNumber >= VME_EXT_FLAG_SAMPLE_ERR_INT) && (intNumber < PROC_INIT_BSY_ERR_INT))
	{
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		switch (intNumber)
		{
		case VME_EXT_FLAG_SAMPLE_ERR_INT:
			uint_vme_data &= 0xFEFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case P32_POS_OV_ERR_INT:
			uint_vme_data &= 0xFFEF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case VME32_POS_OV_ERR_INT:
			uint_vme_data &= 0xFFF7;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case VME37_POS_OV_ERR_INT:
			uint_vme_data &= 0xFFFB;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case USR_VEL_ERR_INT:
			uint_vme_data &= 0xFFFD;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case VEL_ERR_INT:
			uint_vme_data &= 0xFFFE;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		default:
			printf("[WARNING] Unknow interrupt number\n");
			break;
		}
	}
	else
	{
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab2);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		switch (intNumber)
		{
		case PROC_INIT_BSY_ERR_INT:
			uint_vme_data &= 0x7FFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case PROC_FAIL_ERR_INT:
			uint_vme_data &= 0xBFFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case BIAS_SUPPLY_ERR_INT:
			uint_vme_data &= 0xDFFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case WRT_PROTECT_ERR_INT:
			uint_vme_data &= 0xEFFF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case SIG_MAX_ERR_INT:
			uint_vme_data &= 0xFF7F;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case SIG_MIN_ERR_INT:
			uint_vme_data &= 0xFFBF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case BIAS_CALC_COMP_INT:
			uint_vme_data &= 0xFFDF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case BIAS_ERR_INT:
			uint_vme_data &= 0xFFEF;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case APD_DC_ERR_INT:
			uint_vme_data &= 0xFFF7;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case BIAS_SET_ERR_INT:
			uint_vme_data &= 0xFFFB;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case APD_FAIL_ERR_INT:
			uint_vme_data &= 0xFFFD;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		case APD_TMP_ERR_INT:
			uint_vme_data &= 0xFFFE;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
			break;
		default:
			break;
		}
	}
	return RET_SUCCESS;
}
/// <summary>
/// This function resets a specific axis on the ZMI 4104C
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">
/// axis to reset
/// </param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ResetAxis(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data =0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	uint_vme_data = 0x20;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return RET_FAILED;
	}
	return RET_SUCCESS;
}
/// <summary>
/// This function is used after an ResetAxis to wait for the reset to complete
/// </summary>
/// <param name="dev">axis</param>
/// <param name="axis">
/// axis to wait reset completion on
/// </param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int WaitResetComplete(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0, ct = 0;
	printf("Reseting Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zStat1);
	while (!(uint_vme_data & 0x0001))	// Wait for reset complete 
	{
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		ct++;
		if (ct > 0xFFFFFFF1) {

			printf("Failed to reset axis %d !  \n", axis);
			return RET_FAILED;
		}

	}
	//Sleep(10);
	return RET_SUCCESS;
}
/// <summary>
/// This function initializes both SIS100 and SIS3104 boards
/// </summary>
/// <param name="dev">device</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int Init_SIS_boards(struct SIS1100_Device_Struct* dev) {

	/******************************************************************************************************************************/
	/* VME Master Create, Open and Setup                                                                                          */
	/******************************************************************************************************************************/
	// device open, use the first device if present

	char short_data = 0;
	unsigned int  nof_found_sis1100_devices = 0;
	unsigned int sis3100_data = 0;
	short sis3100_add = 0;

	printf("Scanning connected SIS' PCIe card...\n");
	stat = sis1100w_Find_No_Of_sis1100(&nof_found_sis1100_devices);
	if (stat != Stat1100Success) {
		printf("Error while connected SIS' PCIe card\n");
		printf("\tNo valid device were suplied or a Null argument were suplied\n");
		printf("\tError in 'sis1100w_Find_No_Of_sis1100': %d\n", stat);
		return RET_FAILED;
	}

	if (nof_found_sis1100_devices == 0) {
		printf("No SIS' PCIe card found, exiting...\n");
		return RET_FAILED;
	}

	printf("%d SIS' PCIe card found\n", nof_found_sis1100_devices);
	printf("Connecting to the first device...\n");
	stat = sis1100w_Get_Handle_And_Open(0 /* first device */, dev); // 
	if (stat != Stat1100Success) {
		printf("Connection to SIS' PCIe card failed\n");
		printf("\tError in 'sis1100w_Get_Handle_And_Open': %d\n", stat);
		return RET_FAILED;
	}
	printf("Connection successful\n");
	/*
	printf("Getting SIS' PCIe card infos...\n");
	if ((stat = sis1100w_Get_IdentVersion(dev, &nof_found_sis1100_devices)) != Stat1100Success) {
		printf("Failed TO GET SIS' PCIe card\n");
		printf("\tError in 'sis1100w_Get_IdentVersion': %d\n", stat);
	}*/
	printf("Initializing the SIS' PCIe card...\n");
	stat = sis1100w_Init(dev, 0);
	if (stat != Stat1100Success) {
		printf("first SIS' PCIe card initialization failed...\n");
		printf("\tError in 'sis1100w_Init': %d\n", stat);
		return RET_FAILED;
	}
	printf("first SIS' PCIe card initialized\n");
	printf("Initializing VME/PCI gateway...\n");
	stat = sis1100w_Init_sis3100(dev, 0);
	if (stat != Stat1100Success) {
		printf("VME/PCI gateway initialization failed...\n");
		printf("\tError in 'sis1100w_Init_sis3100': %d\n", stat);
		return RET_FAILED;
	}

	printf("VME/PCI gateway initialized\n");

	printf("Reading VME/PCI card Identifier...\n");
	sis3100_add = 0x0;
	if ((stat = sis1100w_sis1100_Control_Read(dev, sis3100_add, &sis3100_data)) != Stat1100Success) {
		printf("\tReading address %X of sis3100 card failed\n", sis3100_add);
	}
	printf("\t 0x0 data: %010X\n", sis3100_data);
	short_data = sis3100_data;
	switch ((int)short_data)
	{
	case 1:
		printf("\t PLI/PLX Interface\n");
		break;
	case 2:
		printf("\tVME Controler\n");
		break;
	case 3:
		printf("\tCAMAC/FERA Controller\n");
		break;
	case 4:
		printf("\tReadoutsystem mit LVD SCSI\n");
		break;
	case 0x82:
		printf("\tVME Initiator\n");
		break;
	default:
		break;
	}
	short_data = sis3100_data >> 8;
	printf("\t Hardware Version: %d\n", (int)short_data);
	short_data = sis3100_data >> 16; // error to be corrected
	printf("\t Firmware type: %d\n", (int)short_data);
	short_data = sis3100_data >> 24; // error to be corrected
	printf("\t Firmware Version: %d\n", (int)short_data);

	printf("Reading VME/PCI card Firmware Register version...\n");
	sis3100_add = 0x4;
	if ((stat = sis1100w_sis1100_Control_Read(dev, sis3100_add, &sis3100_data)) != Stat1100Success) {
		printf("\tReading address %X of sis3100 card failed\n", sis3100_add);
	}

	printf("\t 0x4 data: %010X\n", sis3100_data);

	printf("sis3100 card Frirmware Register version:\n");
	short_data = sis3100_data;
	printf("\t Firmware Version: %d\n", (int)short_data);
	short_data = sis3100_data >> 8;
	printf("\t Firmware type: %d\n", (int)short_data);
	short_data = sis3100_data >> 16; // error to be corrected
	printf("\t Board type: %d\n", (int)short_data);
	VMESysReset(dev);
	Sleep(4000);
	/*/
		printf("Writing in SIS3100 Command register ...\n");
		sis3100_add = 0xc0;
		sis3100_data = 0x100FFFF;
		if ((stat = sis1100w_sis3100_Control_Write(dev, sis3100_add, &sis3100_data)) != Stat1100Success) {
			printf("\tReading address %X of sis3100 card failed\n", sis3100_add);
		}

		//sis3100_data = 0;
		printf("Reading SIS3100 Command register ...\n");
		sis3100_add = 0xc0;
		if ((stat = sis1100w_sis3100_Control_Read(dev, sis3100_add, &sis3100_data)) != Stat1100Success) {
			printf("\tReading address %X of sis3100 card failed\n", sis3100_add);
		}
		printf("\t SIS3100 CR: %X\n", sis3100_data);

		getchar();
		printf("================== Axis' Diagnostic===================== \n");
		printf("\t AXIS 1 \n");

		/*/
		/* ******************* Parsing Status Register 0 **********************/
	return RET_SUCCESS;
}
/// <summary>
/// This function initializes the ZMI4104C
/// </summary>
/// <param name="dev">device</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int Init_ZMI_bd(struct SIS1100_Device_Struct* dev) {
	short value = 0;
	char	ch_access_mode[16];
	unsigned int	vme_data = 0,
		uint_vme_address = 0,
		uint_vme_data = 0;
	unsigned int  uint_vme_data_buf[20];

	memset(uint_vme_data_buf, 0, _countof(uint_vme_data_buf));
	printf("************Initializing ZMI board*************** \n");
	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);

	printf("\n \n Base is ADDRESS is 0x%06X\n\n", BASE_ADDRESS[0]);

	if (Read_Write(ch_access_mode, dev, BASE_ADDRESS[2], &uint_vme_data, 0) != RET_SUCCESS)
		printf("\n\nNot defined/programmed VME Access Mode !  \n\n");
	//printf("%X\n", uint_vme_data_buf[1]);
	vme_data = uint_vme_data;
	uint_vme_data = vme_data >> 12;
	//printf("%d\n", uint_vme_data);
	switch (uint_vme_data)
	{
	case 0b1111:
		printf("\tZMI System type: ZMI 4004 / ZMI 1002 \n");
		break;
	case 0b0111:
		printf("\tZMI System type: ZMI 4104 \n");
		break;
	case 0b1011:
		printf("\tZMI System type: ZMI 4104C\n");
		break;
	default:
		if (uint_vme_data < 13) {
			printf("\tZMI System type: ZMI 2002 series \n");
		}
		else
			printf("\tZMI System type: UNKNOW \n");
		break;
	}
	uint_vme_data = vme_data;

	if (uint_vme_data & 0x00000001)
		printf("\t[Power Ok] All on-board analog power supplies are operating properly\n");
	else
		printf("\t[Power Warning] Some on-board analog power supplies are not operating properly\n");


	if (uint_vme_data & 0x00000002)
		printf("\t[Ref_Sig OK] The reference fiber signal is plugged or the reference signal tree is present \n");
	else
		printf("\t[Ref_Sig Warning] Either the fiber signal isn't plugged or the reference signal tree is missing");


	if (uint_vme_data & 0x00000004)
		printf("\t[Ref_Tree_sig OK] The electrical reference tree input is present \n");
	else
		printf("\t[Ref_Tree_sig Warning] The electrical reference tree input is missing \n");

	if (uint_vme_data & 0x00000008)
		printf("\t[Ref_Fib_sig OK] The Optical reference fiber signal is present \n");
	else
		printf("\t[Ref_Fib_sig Warning] The Optical reference fiber signal is missing \n");

	if (uint_vme_data & 0x00000010)
		printf("\t[Ref_PLL OK] The PLL that generates the on-board system clock is operating properly \n");
	else
		printf("\t[Ref_PLL Warning] The PLL that generates the on-board system clock\n\t is not operating properly\n");

	if (uint_vme_data & 0x00000020)
		printf("\t[FPGA_DLL Locked] The master and slave FPGA are properly synchronized \n\tand the"
			" DLL in the FPGA is operating properly \n");
	else
		printf("\t[FPGA_DLL Warning] The master and slave FPGA are not synchronized\n");

	if (uint_vme_data & 0x00000040)
		printf("\t[FPGA_Temp Warning] The FPGA temperature exceeds the preset limit (+85°C)");
	else
		printf("\t[FPGA_Temp Ok] The FPGA temperature is good at all\n");

	if (uint_vme_data & 0x00000100)
		printf("\t[VME_IRQ_PENDING] An error nit is asserted in the VME Error Status register");

	uint_vme_data = 0;
	if ((return_code = EEPROMread(dev, ADD(BASE_ADDRESS[2], zBdAxInf), &uint_vme_data, 1)) < 0)
		printf("EEprom access faillure ");
	printf("The number of axes is %d \n", uint_vme_data);

	memset(uint_vme_data_buf, 0, _countof(uint_vme_data_buf));
	for (int i = 0; i < 4; i++) {
		uint_vme_data = 0;
		if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zStat1), &uint_vme_data, 0) != RET_SUCCESS)
			printf("\n\nnot defined/programmed VME Access Mode !  \n\n");
		if (uint_vme_data & 0x00000002)
			printf("\t[Meas_Sig OK] The measurement signal is present on Axis %d\n", i + 1);
		else
			printf("\t[Meas_Sig Warning] The measurement signal is missing on Axis %d\n", i + 1);

	}

	if (uint_vme_data & 0x00000001)
		printf("\t[RST OK] Reset Complete\n");

	printf("\n************Board charracteristics*************** \n");
	for (int i = 0; i < 19; i++)
	{
		uint_vme_data = 0;
		if (EEPROMread(dev, i, &uint_vme_data, 1) != RET_SUCCESS)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		uint_vme_data_buf[i] = uint_vme_data;
	}

	printf("\tBoard data version format: %d \n", uint_vme_data_buf[0]);
	printf("\tSize of Board Data Block: %d \n", uint_vme_data_buf[1]);
	printf("\tDate of manufacture: %d/%d/%d \n", uint_vme_data_buf[2], uint_vme_data_buf[3], uint_vme_data_buf[4]);
	printf("\tBoard Assy Number: %d \n", uint_vme_data_buf[6] * (2 ^ 8) + uint_vme_data_buf[5]);
	printf("\tBoard Configuration: %d \n", uint_vme_data_buf[7]);
	printf("\tOriginal Board Revision: %c \n", uint_vme_data_buf[8]);
	printf("\tReworked Board Revision: %c \n", uint_vme_data_buf[9]);
	printf("\tNumber of axes: %d \n", uint_vme_data_buf[15]);
	printf("\tVendor code: %d \n", uint_vme_data_buf[18]);
	printf("\tBoard serial Number: %c%c%c%c%c \n", uint_vme_data_buf[10], \
		uint_vme_data_buf[11], \
		uint_vme_data_buf[12], \
		uint_vme_data_buf[13], \
		uint_vme_data_buf[14]);
	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);
	if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[2], zFWVer), &vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("\tFirmware Version: %d \n", uint_vme_data);

	if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[2], zFWRev), &vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("\tFirmware Revision: ");
	switch (uint_vme_data)
	{
	case 0x7401:
		printf(" 8020-9274-01\n");
		break;
	case 0x7402:
		printf(" 8020-9274-02\n");
		break;
	default:
		printf(" unknow\n");
		break;
	}

	int temp32 = 0,
		offset = 0;
	double m = 0.0, b = 0.0;
	/*Read SSI calibration data*/

	for (int i = 0; i < 4; i++)
	{
		/*SSI reading with minimum signal*/
		if (EEPROMread(dev, 50 + 9 + (100 * i), &uint_vme_data, 1) != RET_SUCCESS)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalMin[i][0] = uint_vme_data;
		if (EEPROMread(dev, 50 + 5 + (100 * i), &uint_vme_data, 1) != RET_SUCCESS) /*Read optical power L2*/
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalMin[i][1] = pow(2, uint_vme_data / 1024);

		if (EEPROMread(dev, 50 + 16 + (100 * i), &uint_vme_data, 1) != RET_SUCCESS)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalNom[i][0] = uint_vme_data;
		if (EEPROMread(dev, 50 + 12 + (100 * i), &uint_vme_data, 1) != RET_SUCCESS)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalNom[i][1] = pow(2, uint_vme_data / 1024);

		if (EEPROMread(dev, 50 + 23 + (100 * i), &uint_vme_data, 1) != RET_SUCCESS)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalMax[i][0] = uint_vme_data;
		if (EEPROMread(dev, 50 + 19 + (100 * i), &uint_vme_data, 1) != RET_SUCCESS)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalMax[i][1] = pow(2, uint_vme_data / 1024);

		m = (SSICalNom[i][1] - SSICalMin[i][1]) / (SSICalNom[i][0] - SSICalMin[i][0]);
		b = SSICalMin[i][1] - (m * SSICalMin[i][0]);
		SSICalValues[i][0] = m;
		SSICalValues[i][1] = b;
	}

	/*Enable reset finds velocity*/
	//EnableResetFindsVelocity(dev, axis);
	//Enable preset
/*
vme_data = 0x100;
if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zCtrl3), &vme_data, 1) != RET_SUCCESS)
	{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

*/
//Enable test mode
	for (int i = 0; i < 4; i++)
	{
		if (enableResetFindsVelocity[i])
		{
			vme_data = 0x10;
			if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zTestCtrl0), &vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		}
		else
		{
			vme_data = 0;
			if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zTestCtrl0), &vme_data, 1) != RET_SUCCESS)
				{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
		}
	}
	return RET_SUCCESS;
}
/// <summary>
/// This function sets the 32 bits position offset on a specific axis.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="offsetPos">the value of the offset on 32bits</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetPositionOffset32(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int offsetPos) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_data = offsetPos;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zOffsetMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 32 bits value of the compare register A on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="compAval32">The 32bits value to be set</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetCompARegVal32(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int compAval32) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_data = compAval32;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCompAMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// This function enables 37bits sign extension on a specific axis. It's usefull when 37 bits mode is set
/// </summary>
/// <param name="dev"> device</param>
/// <param name="axis">the axis' number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int Enable37bitsSignExtension(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl0);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= 0x40;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// This function disables 37bits sign extension on a specific axis. It's usefull when 37 bits mode is disable
/// </summary>
/// <param name="dev"> device</param>
/// <param name="axis">the axis' number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int Disable37bitsSignExtension(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl0);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data &= 0xFFBF;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function set the digital filter coefficients on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="Kp">Value of the Kp coefficient</param>
/// <param name="Kv">Value of the kv coefficient</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetKpAndKvCoeff(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned short Kp, unsigned short Kv) {
	
	if ((Kp > 7) || (Kv > 7))
	{
		printf("Bad Kp or Kv value. range is 0 to 7\n");
		return RET_FAILED;
	}
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl1);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (Kp << 4) + Kv;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// This function set the value of the glitch filter time ranged from 0 to 255
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="glitchFilterTime">value of the register</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int EnableGlitchFilter(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned short glitchFilterTime) {

	if (glitchFilterTime > 0xF)
	{
		printf("Bad Glitch filter time value. range is 0 to 255\n");
		return RET_FAILED;
	}
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl1);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (glitchFilterTime << 8);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 37bits value of the compare register A on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="compAval32">The 32bits packet</param>
/// <param name="compAvalExt">The 5bits packet</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetCompARegVal37(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int compAval32, unsigned int compAvalExt) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	SetCompARegVal32(dev, axis, compAval32);
	uint_vme_data = compAvalExt;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCompAExt);
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 32 bits value of the compare register B on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="compBval32">The 32bits value to be set</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetCompBRegVal32(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int compBval32) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_data = compBval32;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCompBMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 37bits value of the compare register B on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="compBval32">The 32bits packet</param>
/// <param name="compBvalExt">The 5bits packet</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetCompBRegVal37(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int compBval32, unsigned int compBvalExt) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	SetCompBRegVal32(dev, axis, compBval32);
	uint_vme_data = compBvalExt;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCompBExt);
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 37bits value of the offset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="offsetPos32">The 32bits packet</param>
/// <param name="offsetPosExt">The 5bits packet</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetPositionOffset37(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int offsetPos32, unsigned int offsetPosExt) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	SetPositionOffset32(dev, axis, offsetPos32);
	uint_vme_data = offsetPosExt;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zOffsetExt);
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 32bits value of the offset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="presetPos">The 32bits packet</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetPresetPosition32(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int presetPos) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_data = presetPos;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zPresPosMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 32bits value of the offset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="presetPos32">The 32bits packet</param>
/// <param name="presetPosExt">The 5bits packet</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetPresetPosition37(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int presetPos32, unsigned int presetPosExt) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	SetPositionOffset32(dev, axis, presetPos32);
	uint_vme_data = presetPosExt;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zPresPosExt);
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// The function reads and parses values of all VME Error registers on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ReadVMEErrs(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int
		uint_vme_address = 0,
		VMEErrorStatus0 = 0,
		VMEErrorStatus1 = 0,
		VMEErrorStatus2 = 0,
		TestStat1 = 0,
		APDError = 0,
		VMEPosError = 0,
		uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);		//Read VME errors

	printf("***************************VME Errors*******************************\n");
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	TestStat1 = uint_vme_data;
	if (TestStat1 & 0x800)
		printf("EEPROM Error has been detected\n");
	ParseVMEErrorStatus0(dev, axis, &VMEErrorStatus0);
	ParseVMEErrorStatus1(dev, axis, &VMEErrorStatus1);
	ParseVMEErrorStatus2(dev, axis, &VMEErrorStatus2);
	ParseVMEPosErrs(dev, axis, &VMEPosError);
	ParseAPDErrCode(dev, axis, &APDError);
	return RET_SUCCESS;
}
/// <summary>
/// The function reads and parses values of both VME Error registers and APD registers on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ReadAllErrs(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	ReadVMEErrs(dev, axis);
	ReadAPDCtrlSoftErrs(dev, axis);
	return RET_SUCCESS;
}
/// <summary>
/// The function clears all EEPROM errors
/// </summary>
/// <param name="dev">device</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ClearEEPROMErrs(struct SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zTestCmd1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	uint_vme_data |= 0x4;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);


	return RET_SUCCESS;
}
/// <summary>
/// The function configures the Board control Mode. It operates using BoardControlMode function.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="biasMode">the bias mode. There are 5 bias modes(from 0 to 4)</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int BoardControlMode(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int biasMode) {
	/*Activate APD Constant voltage mode*/
	unsigned int defaultAPDGAinL2Set = 0xB3B, defaultAPDOptPwrL2Set = 0,
		 defaultAPDSigRMSL2Set = 0x3390;
	BiasControlMode(dev, axis, biasMode);
	switch (biasMode)
	{

	case BIAS_CONSTANT_VOLT_MODE:
		break;
	case BIAS_CONSTANT_GAIN_MODE:
		SetAPDGainL2(dev, axis, defaultAPDGAinL2Set);
		break;
	case BIAS_SIG_RMS_ADJUST_MODE:
		SetAPDSigRMSL2(dev, axis, defaultAPDSigRMSL2Set);
		break;
	case BIAS_CONSTANT_OPT_PWR_MODE:
		SetAPDOptPwrL2(dev, axis, defaultAPDOptPwrL2Set);
		break;
	default:
		printf("Unknow Bias mode \n");
		return RET_FAILED;
		break;
	}
	/*Set APD GAIN L2 to 892*/
	//SetAPDGainL2(dev, axis,APDGain);
	/* Start bias calculation */
	StartBiasCalculation(dev, axis);
	Sleep(1000);
	return RET_SUCCESS;
}
/// <summary>
/// The function configures the Bias control Mode for a specific axis. See the documentation for the details of each mode
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param Mode="mode">
/// 0 -> Off: The APD bias is set to the minimum value i.e 55V
/// 1 -> Constant Voltage Mode(For Diagnostic use only)
/// 2 -> Constant Gain Mode
/// 3 -> Constant Optical Power Mode  
/// 4 -> Sig RMS Adjust Mode
/// </param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int BiasControlMode(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int mode) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	
	if (mode > 4)
	{
		printf("Unknow mode: mode is ranged 0 to 4 \n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl5);//rw
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	uint_vme_data &= ~(7);
	uint_vme_data |= mode;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Board switched to  %s\n", biasControlModeString[mode]);
	return RET_SUCCESS;
}
/// <summary>
/// The function triggers the bias calculation. It's used after setting up the bias mode 
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int StartBiasCalculation(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	printf("Starting Bias calculation...\n");
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	uint_vme_data = (1<<6);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat2); 
	uint_vme_data = 0;
	while (!(uint_vme_data & (1 << 5)))
	{
		// wait for Bias calc complete to be asserted
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			printf("Register %06X access Faillure !  \n", uint_vme_address);
	}
	printf("Bias calculation complete \n");
	return RET_SUCCESS;
}
/// <summary>
/// This function sets the value of APDGainL2 register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDGain">The APDGain value</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetAPDGainL2(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int APDGain) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	//APDGain: the default val is 7(2875 L2); range: 4(2048 L2) to 32(5120 L2)
	if (!checkValues(APDGain,0,0xFFF))
	{
		printf("Inapropriate value. range is 0 to 0xFFFF \n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDGainL2Set);
	uint_vme_data = APDGain;
	EnableAuxRegisters(dev, axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	DisableAuxRegisters(dev, axis);
	return RET_SUCCESS;
}
/// <summary>
/// This function sets the value of APDSigRMSL2 register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDSigRMSL2">The APDSigRMSL2 value</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetAPDSigRMSL2(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int APDSigRMSL2) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	if (checkValues(APDSigRMSL2, 0, 0xFFFF))
	{
		printf("Inapropriate value. range is 0 to 0xFFFF \n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDSigRMSL2);
	uint_vme_data = APDSigRMSL2;
	EnableAuxRegisters(dev, axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	DisableAuxRegisters(dev, axis);
	return RET_SUCCESS;
}
/// <summary>
/// This function sets the value of APD Opt Pwr L2 set register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDOptPwrL2">The APDOptPwrL2 value</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetAPDOptPwrL2(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int APDOptPwrL2) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	// the default value is 1uw(0 L2); range: 70nW(-3930 L2) to 10uW(3402 L2)
	if (checkValues(APDOptPwrL2, -3930, 3402))
	{
		printf("Inapropriate value. range is 0 to 0xFFFF \n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDOptPwrL2);
	uint_vme_data = APDOptPwrL2;
	EnableAuxRegisters(dev, axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	DisableAuxRegisters(dev, axis);
	return RET_SUCCESS;
}
/// <summary>
/// This function specifies the value of APD Bias DAC register
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDBiasDac">The APDBiasDAC value</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetAPDBiasDAC(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int APDBiasDac) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	if (APDBiasDac > 0xFFFF)
	{
		printf("Inapropriate value. range is 0 to 0xFFFF \n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDBiasDAC);
	uint_vme_data = APDBiasDac;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	return RET_SUCCESS;
}
/// <summary>
/// The function reads and parses VME Error Status 2 register
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="VMEErrorStatus2Reg">stores the contain of the register</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ParseVMEErrorStatus2(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* VMEErrorStatus2Reg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat2);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u VME Status Error 2: %X \n", axis, uint_vme_data);
	*VMEErrorStatus2Reg = uint_vme_data;

	if (uint_vme_data & (1 << 14))
		printf("Proc fail has been detected\n");
	if (uint_vme_data & (1 << 13))
		printf("Bias supply error has been detected\n");
	if (uint_vme_data & (1 << 12))
		printf("Write Protect error has been detected\n");
	if (uint_vme_data & 0x80) {
		printf("Sig max has been detected, The input signal's optical power is above the allowed range\n");
		printf("Fix: -Try to increase the max optical power in SSI MAX register\n ");
		printf("     -Reduce the input optical power using a neutral density filter\n ");
	}
	if (uint_vme_data & (1 << 6)) {
		printf("Sig min has been detected, The input signal's optical power is below the allowed range\n");
		printf("Fix: -Try to decrease the min optical power in SSI min register\n ");
		printf("     -Increase the input signal's optical power \n ");
	}
	if (uint_vme_data & (1 << 4))
		printf("Bias Error has been detected\n");
	if (uint_vme_data & (1 << 3))
		printf("APD DC Error has been detected\n");
	if (uint_vme_data & (1 << 2))
		printf("APD command Error has been detected\n");
	if (uint_vme_data & (1 << 1))
		printf("APD Fail Error has been detected\n");
	if (uint_vme_data & (1 << 0))
		printf("APD Temp Error has been detected\n");

	return RET_SUCCESS;
}
/// <summary>
/// The function reads and parses VME Position register
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="VMEPosErrReg">stores the contain of the register</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ParseVMEPosErrs(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* VMEPosErrReg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosErr);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u Position Errors: %X \n", axis, uint_vme_data);
	*VMEPosErrReg = uint_vme_data;
	if (uint_vme_data & (1 << 3))
		printf("Measurement Error has been detected\n");
	if (uint_vme_data & (1<<1))
		printf("Ref Error has been detected\n");
	return RET_SUCCESS;
}
/// <summary>
/// The function reads and parses VME Error Status 1 register
/// </summary>
/// <param name="dev"></param>
/// <param name="axis"></param>
/// <param name="VMEErrorStatus1Reg">stores the contain of the register</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ParseVMEErrorStatus1(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* VMEErrorStatus1Reg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u VME Status Error 1: %X \n", axis, uint_vme_data);
	*VMEErrorStatus1Reg = uint_vme_data;
	if (uint_vme_data & (1<<3))
		printf("VME 32bits postion register has overflowed\n");
	if (uint_vme_data & (1 << 2))
		printf("VME 37bits postion has overflowed\n");
	if (uint_vme_data & (1 << 1))
		printf("User velocity error has been detected\n");
	if (uint_vme_data & (1 << 0))
		printf("Velocity error has been detected\n");
	return RET_SUCCESS;
}
int ParseVMEErrorStatus0(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* VMEErrorStatus0Reg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat0);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u VME Status Error 0: %X \n", axis, uint_vme_data);
	*VMEErrorStatus0Reg = uint_vme_data;

	if (uint_vme_data & 0x8000)
		printf("CEC Error has been detected\n");
	if (uint_vme_data & 0x4000)
		printf("Phase noise Error has been detected\n");
	if (uint_vme_data & 0x2000)
		printf("Acceleration Error has been detected\n");
	if (uint_vme_data & 0x1000)
		printf("Measure signal glitch has been detected\n");
	if (uint_vme_data & 0x800)
		printf("Measure signal dropout has been detected\n");
	if (uint_vme_data & 0x400)
		printf("SSI Max limit has been detected\n");
	if (uint_vme_data & 0x200)
		printf("Measure signal is saturated\n");
	if (uint_vme_data & 0x100)
		printf("Measure signal is missing\n");
	if (uint_vme_data & 0x80)
		printf("Overtemp error has been detected\n");
	if (uint_vme_data & 0x40)
		printf("FPGA Sync error has been detected\n");
	if (uint_vme_data & 0x20)
		printf("Reset faillure has been detected\n");
	if (uint_vme_data & 0x8)
		printf("Reference PLL Error has been detected\n");
	if (uint_vme_data & 0x4)
		printf("Reference signal is missing\n");
	if (uint_vme_data & 0x2)
		printf("Write error has been detected\n");
	if (uint_vme_data & 0x1)
		printf("Power error has been detected\n");
	return RET_SUCCESS;
}
int ParseAPDErrCode(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* APDErrCode) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDErr);		//Read APD errors
	EnableAuxRegisters(dev, axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u APD Error Code: %X \n", axis, uint_vme_data);
	*APDErrCode = uint_vme_data;
	DisableAuxRegisters(dev, axis);

	switch (uint_vme_data & 0x00FF)
	{
	case 0:
		printf("No APD Axis error \n");
		break;
	case 1:
		printf("[FATAL BOARD] APD Temp Init Error  \n");
		break;
	case 2:
		printf("[FATAL BOARD] Bias range Init Error  \n");
		break;
	case 3:
		printf("DC Meas Low Init Error \n");
		break;
	case 7:
		printf("[FATAL BOARD] Bias Limit Init Error  \n");
		break;
	case 128:
		printf("APD Gain Set Error \n");
		break;
	case 129:
		printf("Sig RMS Set Error \n");
		break;
	case 130:
		printf("Optical Power Set error \n");
		break;
	case 8:
		printf("[FATAL BOARD] DC Meas High Init Error \n");
		break;
	case 9:
		printf("[FATAL BOARD] Bias Limit Op Error \n");
		break;
	case 133:
		printf("Sig RMS call max error \n");
		break;
	case 134:
		printf("Sig RMS call min error \n");
		break;
	case 135:
		printf("APD MATH GAIN error \n");
		printf("\t Invalid APD Gain, should be in the range 4 to 32 \n");
		break;
	case 136:
		printf("APD Math Poly error, Invalid APD bias equation coeffs(0) \n");
		break;
	case 137:
		printf("APD Math Temp error, Invalid APD temperature, range is 10 degreeC to 70 degreeC \n");
		break;
	case 138:
		printf("APD Math T0, Invalid APD bias equation T0, range is 10 degreeC to 50 degreeC \n");
		break;
	case 139:
		printf("APD Math TC, Invalid APD bias equation TC, range is 0.3 to 0.9V/degreeC \n");
		break;
	case 140:
		printf("APD Temp Op Error \n");
		break;
	case 141:
		printf("Bias range Op Error, \n\tAPD Bias failed range check after axis initialization (deviation > 10 V after 0.5 sec)\n");
		break;
	case 142:
		printf("DC Meas Low Op Error,  Meas DC failed low limit check (-4.5 V) after axis initialization\n\t \n");
		break;
	case 143:
		printf("DC Meas Hi Op Error,  Meas DC failed high limit check (-1.4 V) after axis initialization\n\t \n");
		break;
	default:
		printf("Unknow APD Axis error code \n");
		break;
	}


	switch ((uint_vme_data >> 8) & 0x00FF)
	{
	case 0:
		printf("No APD System error \n");
		break;
	case 1:
		printf("[FATAL BOARD] HV Init error: HV failed limit test during board initialization\n");
		break;
	case 2:
		printf("[FATAL BOARD] LV Init error: LV failed limit test during board initialization\n");
		break;
	case 3:
		printf("[FATAL BOARD] FOR Init Error: Fiber Optic Receiver not detected during board initialization (no APD temp)\n");
		break;
	case 4:
		printf("[FATAL BOARD] LV OK Timeout Error:  Slave did not detect LV_OK within allotted time\n");
		break;
	case 5:
		printf("[FATAL BOARD] Slave Act FOR Timeout: Master did not receive Slave response that FOR detected\n");
		break;
	case 6:
		printf("[FATAL BOARD] HV OK Timeout: Slave did not detect HV_OK within allotted time\n");
		break;
	case 7:
		printf("[FATAL BOARD]  EE Cal Read Error: Master unable to read EE calibration data\n");
		break;
	case 8:
		printf("[FATAL BOARD] EE Cal Xfer Error: EE Cal transfer to Slave failed or timeout\n");
		break;
	case 9:
		printf("[FATAL BOARD]  CEC Ver Timeout:  Slave failed to tell Master that CEC enabled\n");
		break;
	case 10:
		printf("[FATAL BOARD]  Ovr Ver Timeout: Master unable to verify that Override enabled on Slave\n");
		break;
	case 11:
		printf("[FATAL BOARD] Illegal Opcode Error: Hardware exception due to an attempt to execute an illegal opcode\n");
		break;
	case 12:
		printf("[MATH ERROR] Divide By Zero Error \n");
		break;
	case 128:
		printf("[FATAL BOARD] HV Operation error: HV Failed limits after board initialization \n");
		printf("\t Invalid APD Gain, should be in the range 4 to 32 \n");
		break;
	case 129:
		printf("[FATAL BOARD] LV Operation error:  LV reading failed limit test after board initialization\n");
		break;
	case 130:
		printf("[NOT FATAL] EEprom Checksum Error: EEprom Checksum Error during Board Initialization \n");
		break;
	case 131:
		printf("[FATAL BOARD] Slave Timeout Op: The Slave did not respond to the Master within the specified time\n");
		break;
	case 132:
		printf("[FATAL BOARD] Slave Req. Not Conf. Op error: Master unable to confirm the request for Slave status\n");
		break;
	case 133:
		printf("[FATAL BOARD] Master Rcvd Slave Fatal error: Master received fatal error status from Slave\n");
		break;

	default:
		printf("Unknow APD System error code \n");
		break;

		return RET_SUCCESS;
	}
	return RET_SUCCESS;
}
/*This fuction reads the ZMI "Sample position Register" on 37 bits
   - Reading this register latches data AND reads the full position value
Note: this is different than reading the "position Register" which does not latch data
*/
int ReadSamplePosition37(struct SIS1100_Device_Struct* dev, unsigned char axis, double* position) {
	int val;
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	int temp32 = 0;
	uint_vme_data = 0;
	printf("Reading Sample Position on Axis %d...  \n", axis);
	Disable32bitsOverflow(dev, axis);
	Enable37bitsSignExtension(dev, axis);
	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMESampPosMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	temp32 = (int)uint_vme_data;
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMESampPosExt);		//Read the Ext
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	val = (int)((short)uint_vme_data);
	/*
		if (((short)uint_vme_data & (short)(0x80)) != 0)	// If position is negative
		{
			/*
			//replaces bits 8-15 with 1's
			// we are interested on the 8 least bits
			position[axis - 1] = (double)((short)(0xFF00) + ((short)uint_vme_data & (short)(0xFF)));

			//Checks if temp32 appears negative, accounts for when full position
			//value is negative and the 32bit value needs to be 32bit unsigned

			if ((temp32 & 0x80000000) != 0) //check whether the 32 bits value is negative
			{
				temp32 = temp32 & 0x7FFFFFFF; // get the absolute value of the number
				// get back the bit droped above and convert the overall to double
				//position[axis - 1] = ((short)uint_vme_data * (2 ^ 32)) + (1 << 31) + temp32;


			}
			else
				position[axis - 1] = ((short)uint_vme_data * (2 ^ 32)) + temp32;


			position[axis - 1] = ((short)uint_vme_data * (2 ^ 32)) + (unsigned int)temp32;
		}
		else
		{
			/*
			//Not interessed by 8-15 bits
			position[axis - 1] = (double)((short)uint_vme_data & (short)(0xFF));
			if ((temp32 & 0x80000000) != 0)
			{
				temp32 = temp32 & 0x7FFFFFFF;
				position[axis - 1] = (position[axis - 1] * (2 ^ 32)) + (1 << 31) + temp32;
			}
			else
				position[axis - 1] = (position[axis - 1] * (2 ^ 32)) + temp32;


			position[axis - 1] = ((short)uint_vme_data * (2 ^ 32)) + (unsigned int)temp32;
		}

	*/
	* position = ((double)(val)) * (2 ^ 32) + (double)((unsigned int)temp32) * positionScale;

	printf("-------------------------------------------------------\n");
	printf("Measured Sample Position on axis %d: %f mm \n", axis, *position);
	printf("-------------------------------------------------------\n");
	return RET_SUCCESS;
}/*This fuction reads the ZMI "Sample position Register" on 32 bits
   - Reading this register latches data AND reads the full position value
Note: this is different than reading the "position Register" which does not latch data
*/
int ReadSamplePosition32(struct SIS1100_Device_Struct* dev, unsigned char axis, double* position) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_data = 0;
	Enable32bitsOverflow(dev, axis);
	Disable37bitsSignExtension(dev, axis);
	printf("Reading Sample Position on Axis %d...  \n", axis);
	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMESampPosMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	*position = (double)((int)(uint_vme_data) * (positionScale));

	printf("-------------------------------------------------------\n");
	printf("Measured Sample Position on axis %d: %f  mm \n", axis, *position);
	printf("-------------------------------------------------------\n");
	Disable32bitsOverflow(dev, axis);
	return RET_SUCCESS;
}/*This fuction reads the ZMI "Position Register" on 37 bits
   - Reading this register reads the full position value
Note: this is different than reading the "Sample position Register" which latch data before reading
*/
int ReadPosition37(struct SIS1100_Device_Struct* dev, unsigned char axis, double* position) {
	int val = 0, temp32 = 0;
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosMSB);
	printf("Reading Position on Axis %d...  \n", axis);
	Disable32bitsOverflow(dev, axis);
	Enable37bitsSignExtension(dev, axis);
	//EnableSampleTimer(dev);
	SampleVMEPosition(dev, axis);
	while (!GetVMEExtSampFlag(dev, axis)); // Wait for the VME external sample flag to be set before reading
	SetHoldSampEnable(dev);
	//clearVMEExtSampFlag(dev, axis); // Clear VME external sample flag before reading
	//Read the MSB and LSB	
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	val = (int)uint_vme_data;
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosExt);		//Read the Ext
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	ResetHoldSampEnable(dev);
	val = (int)((short)uint_vme_data);
	*position = ((double)(val)) * (2 ^ 32) + (double)((unsigned int)temp32) * positionScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Position on axis %d: %f mm \n", axis, *position);
	printf("-------------------------------------------------------\n");

	return RET_SUCCESS;
}/*This fuction reads the ZMI "Position Register" on 32 bits
   - Reading this register reads the full position value
Note: this is different than reading the "Sample position Register" which latch data before reading
*/
int ReadPosition32(struct SIS1100_Device_Struct* dev, unsigned char axis, double* position) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading Position on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosMSB);
	Enable32bitsOverflow(dev, axis);
	Disable37bitsSignExtension(dev, axis);
	//EnableSampleTimer(dev);	
	SampleVMEPosition(dev, axis);
	while (!GetVMEExtSampFlag(dev, axis)); // Wait for the VME external sample flag to be set before reading
	SetHoldSampEnable(dev); // value of the position register is held until its LSB is read 
	//clearVMEExtSampFlag(dev, axis); // Clear VME external sample flag before reading
	//Read the MSB and LSB	
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	ResetHoldSampEnable(dev);
	*position = (double)((int)uint_vme_data) * positionScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Position on axis %d: %f mm \n", axis, *position);
	printf("-------------------------------------------------------\n");
	Disable32bitsOverflow(dev, axis);

	return RET_SUCCESS;
}
int ReadVelocity32(struct SIS1100_Device_Struct* dev, unsigned char axis, double* position) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading Velocity on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosMSB);
	//EnableSampleTimer(dev);
	SampleVMEPosition(dev, axis); // the function both sample velocity and value
	//Read the MSB and LSB	
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	ResetHoldSampEnable(dev);
	*position = (double)((int)uint_vme_data) * velocityScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Velocity on axis %d: %f m/s \n", axis, *position);
	printf("-------------------------------------------------------\n");
	Disable32bitsOverflow(dev, axis);

	return RET_SUCCESS;
}
int ReadSamplePosition32_ForAllAxis(struct SIS1100_Device_Struct* dev, double* SamplePosition32_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadSamplePosition32(dev, i, &position);
		*(SamplePosition32_buf + i - 1) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
int ReadSamplePosition37_ForAllAxis(struct SIS1100_Device_Struct* dev, double* SamplePosition37_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadSamplePosition37(dev, i, &position);
		*(SamplePosition37_buf + i - 1) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
int ReadPosition32_ForAllAxis(struct SIS1100_Device_Struct* dev, double* Position32_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadPosition32(dev, i, &position);
		*(Position32_buf + i - 1) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
int ReadVelocity32_ForAllAxis(struct SIS1100_Device_Struct* dev, double* Velocity32_buf) {

	double Velocity = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadVelocity32(dev, i, &Velocity);
		*(Velocity32_buf + i - 1) = Velocity;
		Velocity = 0.0;
	}
	return RET_SUCCESS;
}
int ReadPosition37_ForAllAxis(struct SIS1100_Device_Struct* dev, double* Position37_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadPosition37(dev, i, &position);
		*(Position37_buf + i - 1) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
bool IsVMEPos32Overflow(struct SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data & 0x0008))
		return true;
	return false;
}
bool IsVMEPos37Overflow(struct SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data & 0x0004))
		return true;
	return false;
}
bool IsUserVelError(struct SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data & 0x0002))
		return true;
	return false;
}
bool IsVelError(struct SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data & 0x0001))
		return true;
	return false;
}
bool IsAccError(struct SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat0);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if (uint_vme_data & 0x2000)
		return true;
	return false;
}
int ClearPosAndVelErrs(struct SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0xF, uint_vme_address = 0;

	printf("Reseting Position and velocity errors on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	return RET_SUCCESS;
}
int ClearAllVMEErrs(struct SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0xFFFF,
		uint_vme_address = 0;

	printf("Reseting all VME errors on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr0);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data = 1;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// ClearPosAndVelErrs_ForAllAxis: 
/// Clear All position & velocity Errors on all axis(1 to 4).
/// </summary>
/// <param device="dev"></param>
/// <param measurement_axis="axis"></param>
/// <returns>
/// 0 if successful
/// </returns>
int ClearPosAndVelErrs_ForAllAxis(struct SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0xFFFF,
		uint_vme_address = 0;

	for (int i = 1; i < 5; i++)
	{
		ClearPosAndVelErrs(dev, i);
	}

	return RET_SUCCESS;
}
/// <summary>
/// ClearAllVMEErrs_ForAllAxis: 
/// Clear VME Errors for all axis(1 to 4).
/// Rmk: Doesn't clear FATAL Board errors
/// </summary>
/// <param device="dev"></param>
/// <param measurement_axis="axis"></param>
/// <returns>
/// 0 if successful
/// </returns>
int ClearAllVMEErrs_ForAllAxis(struct SIS1100_Device_Struct* dev) {

	for (int i = 1; i < 5; i++)
	{
		ClearAllVMEErrs(dev, i);
	}

	return RET_SUCCESS;
}
/*This fuction reads the ZMI "Time Register" on 32 bits
*/
int ReadTime32(struct SIS1100_Device_Struct* dev, unsigned char axis, double* time) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading Elapsed time on Axis %d...  \n", axis);
	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMETimeMSB);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	*time = uint_vme_data * timeScale;
	printf("-------------------------------------------------------\n");
	printf("Elapsed time is : %f s\n", *time);
	printf("-------------------------------------------------------\n");
	return RET_SUCCESS;
}
int ReadTime32_ForAllAxis(struct SIS1100_Device_Struct* dev, double* Time32_buf) {

	double time = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadTime32(dev, i, &time);
		*(Time32_buf + i - 1) = time;
		time = 0.0;
	}
	return RET_SUCCESS;
}
int ResetTime(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Reseting Time on Axis: %d  \n", axis);
	return RET_SUCCESS;

}
int ResetPositionQuick(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 4);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Quick position reset on Axis: %d  \n", axis);
	return RET_SUCCESS;

}
int ResetPosition(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Reseting Position on Axis: %d  \n", axis);
	return RET_SUCCESS;

}
int EnablePreset(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 8);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Reseting Position on Axis: %d  \n", axis);
	return RET_SUCCESS;

}
int EnableSCLKResetOnAxisReset(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 9);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Performing quick reset and time reset on Axis: %d  \n", axis);
	return RET_SUCCESS;

}
int DisableSCLKResetOnAxisReset(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data &= ~(1 << 9);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Performing quick reset and time reset on Axis: %d  \n", axis);
	return RET_SUCCESS;

}
int EnableResetFindsVelocity(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 11);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Enabling reset finds velocity  on Axis %d  \n", axis);
	return RET_SUCCESS;

}
int DisableResetFindsVelocity(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data &= ~(1 << 11);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Enabling reset finds velocity  on Axis %d  \n", axis);
	return RET_SUCCESS;

}
int SCLKSelectOnAxisReset(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned char SCLK)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	if (((int)SCLK) * 1 > 1)
	{
		printf("SCLK selection fatal error. unknow value passed to the function %s "\
			"file %s, line %d\n", __FUNCTION__, __FILE__, __LINE__);
		printf("SCLK value is ranged 0 to 1\n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (SCLK << 10);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Performing quick reset and time reset on Axis: %d  \n", axis);
	return RET_SUCCESS;

}
int SetTimeDelayBetweenResAndCompleteBit(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned char timeDelay)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	if (((int)timeDelay) > 7)
	{
		printf("Time delay selection fatal error. unknow value passed to the function %s "\
			"file %s, line %d\n", __FUNCTION__, __FILE__, __LINE__);
		printf("Time delay value is ranged 0 to 7\n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (timeDelay << 12);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	printf("Setting time delay between axis reset and and reset complete assertion on Axis: %d  \n", axis);
	return RET_SUCCESS;

}
int ReadOpticalPowerUsingSSIav(struct SIS1100_Device_Struct* dev) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_data = 0;
	double APD_Gain[] = { 0.0, 0.0, 0.0, 0.0 },
		SSI[] = { 0.0, 0.0, 0.0, 0.0 };
	//Read the MSB and LSB
	for (int i = 0; i < 4; i++)
	{
		// The max SSI Average value (0xFFFF) corresponds to 1.25V
		printf("Reading SSI average on Axis %u...  \n", i + 1);
		uint_vme_address = ADD(BASE_ADDRESS[i], zSSIAvg);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

		SSI[i] = (double)uint_vme_data;
	}

	ReadAPDGain_ForAllAxis(dev, APD_Gain);

	for (int i = 0; i < 4; i++)
	{
		OpticalPower_uW[i] = SSI[i] * 0.00218 / APD_Gain[i];
		if (OpticalPower_uW[i] < 0)
		{
			OpticalPower_uW[i] = 0;
			printf("-------------------------------------------------------\n");
			printf("[WARNING] SSI is negative on axis. Setting it to 0...%u\n", i + 1);
			printf("Optical Power on axis %d is %f uW\n", i + 1, OpticalPower_uW[i]);
			printf("-------------------------------------------------------\n");
		}
		else
		{
			printf("-------------------------------------------------------\n");
			printf("Optical Power on axis %d is %f uW\n", i + 1, OpticalPower_uW[i]);
			printf("-------------------------------------------------------\n");
		}
	}

	return RET_SUCCESS;
}
int SetSSISquelch(struct SIS1100_Device_Struct* dev, unsigned short axis, int squelchValue ) {

	//Set SSI Squelch(minimum AC optical signal that causes measurement signal ZMIError)
	// default value is 0x80
	//SSI Squelch is only 12bits, so max is 4095 (0x0FFF) or about __ uW
	unsigned int value = 0;
	unsigned int uint_vme_address = 0;
	squelchValue = (unsigned short)((SSIsquelch[axis - 1] - SSICalValues[axis - 1][1]) / SSICalValues[axis - 1][0]);
	if (squelchValue > 0xFFF)
	{
		printf("[SSI_Squelch] Value given is too large or negative, setting to default value(0x80)");
		value = 0x80; // Setting to default value
	}
	else
		value = (short)(squelchValue & 0xFFF);

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zSSISquelch);
	if (Read_Write("A24D16", dev, uint_vme_address, &value, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int GetSSIMaxVal(struct SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* SSIMax)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_data = 0;
	// The SSI max value (0xFFFF) corresponds to 1.25V

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zSSIMax);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	*SSIMax = uint_vme_data;
	printf("SSI Max val on Axis %u is : %d  \n", axis, uint_vme_data);
	return RET_SUCCESS;

}
int GetSSIMaxVal_ForAllAxis(struct SIS1100_Device_Struct* dev, unsigned int* SSIMax_Buf)
{
	unsigned int uint_vme_data = 0;
	for (int i = 1; i < 5; i++)
	{
		// The SSI max value (0xFFFF) corresponds to 1.25V
		GetSSIMaxVal(dev, i, &uint_vme_data);
		*(SSIMax_Buf + i - 1) = uint_vme_data;
	}

	return RET_SUCCESS;

}
int ResetSSIMinAndMax(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	// The SSI max value (0xFFFF) corresponds to 1.25V
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zTestCmd0);
	
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= 0x2;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;

}
int ResetPhaseNoisePeak(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zTestCmd0);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= 0x1;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;

}
int ResetSigRMSL2MinAndMax(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zTestCmd0);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data = (1 << 2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;

}
int setGainControlMax(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl5);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int setGainControlMin(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl5);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 4);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int AdjustGainControl(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl5);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 5);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int ResetOptPowL2MinAndMax(struct SIS1100_Device_Struct* dev, unsigned char axis)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	// The SSI max value (0xFFFF) corresponds to 1.25V
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zTestCmd0);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= (1 << 2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;

}
int CheckSaturation(struct SIS1100_Device_Struct* dev, unsigned char axis, bool* sat)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	// The SSI max value (0xFFFF) corresponds to 1.25V

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat0);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	if (uint_vme_data & (0x200))
	{
		printf("Measurement signal is saturated on Axis %u...  \n", axis);
		GetSSIMaxVal(dev, axis, &uint_vme_data);
		printf("The SSI max register on this axis has the value %u. ", uint_vme_data);
		printf("This value should be lesser than %u...  \n", SSI_MAX_SAT);
		*sat = true;
	}
	else
	{
		printf("Measurement signal is not saturated on Axis %u...  \n", axis);
		GetSSIMaxVal(dev, axis, &uint_vme_data);
		printf("The SSI max register on this axis has the value %u. ", uint_vme_data);
		*sat = false;
	}
	return RET_SUCCESS;

}
int CheckSaturation_ForAllAxis(struct SIS1100_Device_Struct* dev, bool* sat_Buf)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	bool sat = false;
	for (int i = 1; i < 5; i++)
	{
		CheckSaturation(dev, i, &sat);
		*(sat_Buf + i - 1) = sat;
	}

	return RET_SUCCESS;

}
int ReadAPDGain(struct SIS1100_Device_Struct* dev, unsigned char axis, double* APD_Gain) {
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_data = 0;
	double APD_Gain_L2 = 0.0;

	EnableAuxRegisters(dev, axis);
	printf("Reading APD GAIN L2 on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDGainL2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	APD_Gain_L2 = (double)uint_vme_data;
	*APD_Gain = pow(2, ((int)(APD_Gain_L2 / 1024)));
	printf("-------------------------------------------------------\n");
	printf("APD Gain on axis %u: %f \n", axis, *APD_Gain);
	printf("-------------------------------------------------------\n");
	DisableAuxRegisters(dev, axis);
	return RET_SUCCESS;
}
int ReadAPDGain_ForAllAxis(struct SIS1100_Device_Struct* dev, double* APD_Gain_Buf) {

	double APD_Gain = 0.0;

	for (int i = 1; i < 5; i++)
	{
		ReadAPDGain(dev, i, &APD_Gain);
		*(APD_Gain_Buf + i - 1) = APD_Gain;
		APD_Gain = 0.0;
	}
	return RET_SUCCESS;
}
int EnableAuxRegisters(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);//rw
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data |= 0x200;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	return RET_SUCCESS;
}
bool IsAPDCtrlSoftErrs(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if (uint_vme_data & 0x100)
		return true;
	return false;
}
int ReadAPDCtrlSoftErrs(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;

	printf("*************************APD Errors****************************\n");
	if (!IsAPDCtrlSoftErrs(dev, axis))
	{
		printf("No APD Controller software error detected\n");
		return RET_FAILED;
	}
	
	EnableAuxRegisters(dev, axis); // Enable auxiliary registers to read the register value
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zSoftErrID);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	switch (uint_vme_data >> 12)
	{
	case NO_EXCEPTION_ERROR:
		printf("No APD controller software error\n");
		break;
	case EXCEPTION_ERROR:
		printf("APD controller raises an EXCEPTION ERROR\n");
		switch (uint_vme_data & 0xFFF)
		{
		case 1:
			printf("\tUnaligned access exception\n");
			break;
		case 2:
			printf("\tTimeout from the IOPB bus exception\n");
			break;
		case 3:
			printf("\tIllegal op code execution exception\n");
			break;
		case 4:
			printf("\tTimeout on the DOPB bus exception\n");
			break;

		case 5:
			printf("\tDivide by zero exception\n");
			break;
		default:
			printf("\tUnknow exception error ID\n");
			break;
		}
		break;
	case STACK_OVERFLOW:
		printf("No APD controller software error\n");
		break;
	case SWITCH_DEFAULT_ERROR:
		printf("No APD controller software error\n");
		break;

	case COMM_ERROR:
		printf("No APD controller software error\n");
		if ((uint_vme_data & 0xFFF) == 1)
			printf("\tRecieve Overflow\n");
		break;
	default:
		printf("Unknow software error type\n");
		break;
	}
	DisableAuxRegisters(dev, axis); // Enable auxiliary registers
	return RET_SUCCESS;
}
int Enable32bitsOverflow(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	// Enable auxiliary registers

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data |= 0x800;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int Disable32bitsOverflow(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	// Enable auxiliary registers
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data &= 0xF7FF;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int DisableAuxRegisters(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	// Disable auxiliary registers
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data &= 0xFDFF;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int SampleVMEPosition(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	printf("Sampling velocity and position on axis %d...\n", axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data |= 0x200;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	while (!(uint_vme_data & 0x400))
	{
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	}

	return RET_SUCCESS;
}
int Sclk_On(struct SIS1100_Device_Struct* dev) {
	//Turn on bits 7 and 9 (SCLK Timer enable and SCLK0 output)
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl16);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data |= 0x280;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int VMESysReset(struct SIS1100_Device_Struct* dev) {
	printf("Hard reseting the system...\n");
	stat = sis1100w_VmeSysreset(dev);

	if (stat != Stat1100Success) {
		printf("Errors occured while hard reseting the card\n");
		return RET_FAILED;
	}
	printf("Reseting Zygo board...\n");
	return RET_SUCCESS;
}
int Sclk_Off(struct SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl16);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data &= 0xFD7F;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int SetSampTimerFreq(struct SIS1100_Device_Struct* dev, unsigned short sampFreq) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zSampleTimer);
	uint_vme_data = sampFreq;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int SetHoldSampEnable(struct SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);
	uint_vme_data |= 0x2000;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int ResetHoldSampEnable(struct SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);
	uint_vme_data &= 0xDFFF;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int SetSampFlag(struct SIS1100_Device_Struct* dev, double sampleFreq) {
	short rdVal = 0, sclkVal = 0;
	double minFreq = 0.001;

	if (sampleFreq <= 0 || sampleFreq > 10)
		sampleFreq = 10;
	printf("Sampling at %f Mhz\n", sampleFreq);
	if (sampleFreq < minFreq)
	{
		printf("ZMI sample rate minimum is %u\n Setting to min...\n", (unsigned int)(sampleFreq * 1000));
		sclkVal = (short)(1 / (minFreq * 0.05) - 1);
	}
	else
		sclkVal = (short)(1 / (sampleFreq * 0.05) - 1);

	//turn off sclk (turn off 7 and 9) and turn off divider (turn off 6)
	Sclk_Off(dev);
	//set sclk rate(only master axis needed)
	SetSampTimerFreq(dev, sclkVal);
	return RET_SUCCESS;
}
int EnableSampleTimer(struct SIS1100_Device_Struct* dev) {
	Sclk_On(dev);
	return RET_SUCCESS;
}
int DisableSampleTimer(struct SIS1100_Device_Struct* dev) {
	Sclk_Off(dev);
	return RET_SUCCESS;
}
bool GetVMEExtSampFlag(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis-1], zStat0);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data &= 0x400)) {
		return true;
	}
	return false;
}
bool clearVMEExtSampFlag(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_data = 0x100;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return true;
}
bool IsVMEIntReqPending(struct SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zStat0);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data &= 0x100)) {
		return true;
	}
	return false;
}
int EEPROMread(
	struct SIS1100_Device_Struct* dev,
	unsigned short offset,
	unsigned int* uint_vme_data,
	unsigned short nBytes) {
	unsigned int uint_vme_address = 0,
		vme_data = 0;
	char ch_access_mode[10];
	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);
	uint_vme_address = ADD(BASE_ADDRESS[2], zTestStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	// Verify the EEPROM is error-free 
	if ((vme_data & 0x800) != 0) {
		uint_vme_address = ADD(BASE_ADDRESS[2], zTestCmd1); // Clear the error 
		vme_data = 0x04;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &vme_data, 1) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	}
	// Wait until EEPROM Busy clears 
	vme_data = 0x0200;
	while (vme_data & 0x0200) {
		uint_vme_address = ADD(BASE_ADDRESS[2], zTestStat1);
		vme_data = 0;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	}; // Wait while EEPROM busy 
		// Start EEPROM Read 
	//First send the adress to read
	uint_vme_address = ADD(BASE_ADDRESS[2], zEEpromCtrl);
	vme_data = zEEReadCmd | (offset & 0x3ff); // keep the last 10 bits and add them to the eerdcmd
	if (Read_Write(ch_access_mode, dev, uint_vme_address, &vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	vme_data = 0x0200;
	uint_vme_address = ADD(BASE_ADDRESS[2], zTestStat1);
	while (vme_data & 0x0200) {

		if (Read_Write(ch_access_mode, dev, uint_vme_address, &vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	} // Wait while EEPROM busy 


	//Read the EEprom
	switch (nBytes)
	{
	case 1:
		strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[5]);
		break;
	case 2:
		strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);
		break;
	case 4:
		strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[7]);
		break;
	default:
		return RET_FAILED;
		break;
	}

	uint_vme_address = ADD(BASE_ADDRESS[2], zEEpromReadReg);
	*uint_vme_data = 0;
	if (Read_Write(ch_access_mode, dev, uint_vme_address, uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	return RET_SUCCESS;

}

int Read_Write(char* ch_access_mode,
	struct SIS1100_Device_Struct* dev,
	unsigned int uint_vme_address,
	unsigned int* uint_vme_data,
	unsigned short read_write) {

	/**************************************************************************/
	/***   "A24D32":   A24  privileged data access                       ***/
	/**************************************************************************/
	uint8_t comp_valid_flag=0;
	comp_err = strncmp(ch_access_mode, "A24D32P", 7);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D32P_read(dev, uint_vme_address, uint_vme_data);
			printf("vme_A24D32_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D32_write(dev, uint_vme_address, *uint_vme_data);
			printf("vme_A24D32_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;

	}

	/**************************************************************************/
	/***   "CRCSRD8":  Configuration ROM/Control&Status Register (CR/CSR)   ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[0], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_CRCSR_D8_read(dev, uint_vme_address, (unsigned char*)uint_vme_data);
			printf("vme_CRCSR_D8_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_CRCSR_D8_write(dev, uint_vme_address, *uint_vme_data);
			printf("vme_CRCSR_D8_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;

	}

	/**************************************************************************/
	/***   "CRCSR_D16": Configuration ROM/Control&Status Register (CR/CSR)  ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[1], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_CRCSR_D16_read(dev, uint_vme_address, (unsigned short*)uint_vme_data);
			printf("vme_CRCSR_D16_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
			*uint_vme_data = (unsigned int)*uint_vme_data;
		}
		else {
			return_code = vme_CRCSR_D16_write(dev, uint_vme_address, (unsigned short)*uint_vme_data);
			printf("vme_CRCSR_D16_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}


	/**************************************************************************/
	/***   "A16D8":    A16 non privileged access                            ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[2], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A16D8_read(dev, uint_vme_address, (unsigned char*)uint_vme_data);
			printf("vme_A16D8_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A16D8_write(dev, uint_vme_address, (unsigned char)*uint_vme_data);
			printf("vme_A16D8_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}

	/**************************************************************************/
	/***   "A16D16":   A16 non privileged access                            ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[3], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A16D16_read(dev, uint_vme_address, (unsigned short*)uint_vme_data);
			printf("vme_A16D16_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
			*uint_vme_data = (unsigned int)*uint_vme_data;
		}
		else {
			return_code = vme_A16D16_write(dev, uint_vme_address, (unsigned short)*uint_vme_data);
			printf("vme_A16D16_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}

	/**************************************************************************/
	/***   "A16D32":   A16 non privileged access                            ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[4], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A16D32_read(dev, uint_vme_address, uint_vme_data);
			printf("vme_A16D32_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A16D32_write(dev, uint_vme_address, *uint_vme_data);
			printf("vme_A16D32_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}

	/**************************************************************************/
	/***   "A24D8":    A24 non privileged data access                       ***/
	/**************************************************************************/

	comp_err = strncmp(ch_access_mode, access_mode_Selection[5], 16);
	if (comp_err == 0) {

		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D8_read(dev, uint_vme_address, (unsigned char*)uint_vme_data);
			printf("vme_A24D8_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D8_write(dev, uint_vme_address, (unsigned char)*uint_vme_data);
			printf("vme_A24D8_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}

	/**************************************************************************/
	/***   "A24D16":   A24 non privileged data access                       ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[6], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D16_read(dev, uint_vme_address, (unsigned short*)uint_vme_data);
			printf("vme_A24D16_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D16_write(dev, uint_vme_address, (unsigned short)*uint_vme_data);
			printf("vme_A24D16_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}


	/**************************************************************************/
	/***   "A24D16":   A24  privileged data access                       ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, "A24D16P", 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D16P_read(dev, uint_vme_address, (unsigned short*)uint_vme_data);
			printf("vme_A24D16_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D16P_write(dev, uint_vme_address, (unsigned short)*uint_vme_data);
			printf("vme_A24D16_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}

	/**************************************************************************/
	/***   "A24D32":   A24 non privileged data access                       ***/
	/**************************************************************************/

	comp_err = strncmp(ch_access_mode, access_mode_Selection[7], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D32_read(dev, uint_vme_address, uint_vme_data);
			printf("vme_A24D32_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D32_write(dev, uint_vme_address, *uint_vme_data);
			printf("vme_A24D32_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}

	/**************************************************************************/
	/***   "A32D8":    A32 non privileged data access                       ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[8], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A32D8_read(dev, uint_vme_address, (unsigned char*)uint_vme_data);
			printf("vme_A32D8_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A32D8_write(dev, uint_vme_address, (unsigned char)*uint_vme_data);
			printf("vme_A32D8_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}

	/**************************************************************************/
	/***   "A32D16":   A32 non privileged data access                       ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[9], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A32D16_read(dev, uint_vme_address, (unsigned short*)uint_vme_data);
			printf("vme_A32D16_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A32D16_write(dev, uint_vme_address, (unsigned short)*uint_vme_data);
			printf("vme_A32D16_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}

	/**************************************************************************/
	/***   "A32D32":   A32 non privileged data access                       ***/
	/**************************************************************************/

	comp_err = strncmp(ch_access_mode, access_mode_Selection[10], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A32D32_read(dev, uint_vme_address, uint_vme_data);
			printf("vme_A32D32_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A32D32_write(dev, uint_vme_address, *uint_vme_data);
			printf("vme_A32D32_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		return RET_SUCCESS;
	}



	/******************************************************************************************************************************/

	/******************************************************************************************************************************/
	comp_valid_flag = 0;
	return RET_FAILED;
}
