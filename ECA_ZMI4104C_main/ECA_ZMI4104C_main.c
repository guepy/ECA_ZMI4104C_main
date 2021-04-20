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
#pragma comment (lib, "sis1100w.lib")


#define MAX_NOF_ACCESS_MODE_DEFINES		11 
#define RET_SUCCESS						0
#define RET_FAILED						-1
#define LAMBDA  632.9911                   //"Nominal Vacuum Wavelength: 632.9911 ± 0.0001 nm"
#define SINGLE_PASS_INT_POS_COEF			2048	// 0.31 nm resolution
#define DOUBLE_PASS_INT_POS_COEF			4096	// 0.15 nm resolution
#define SSI_MAX_SAT							2047
#define SINGLE_PASS_INT_VEL_COEF			2.946705 * (1e-9)
#define DOUBLE_PASS_INT_VEL_COEF			1.473352 * (1e-9)
#define BIAS_OFF_MODE						0
#define BIAS_CONSTANT_VOLT_MODE				1
#define BIAS_CONSTANT_GAIN_MODE				2
#define BIAS_CONSTANT_OPT_PWR_MODE			3
#define BIAS_SIG_RMS_ADJUST_MODE			4
#define CEC_ERR_INT							0
#define PHASE_NOISE_ERR_INT					1
#define ACCELERATION_ERR_INT				2
#define MEAS_SIG_GLITCH_ERR_INT				3
#define MEAS_SIG_DROP_ERR_INT				4
#define SSI_MAX_LIM_ERR_INT					5
#define MEAS_SIG_SAT_ERR_INT				6
#define MEAS_SIG_MIS_ERR_INT				7
#define OV_TMP_ERR_INT						8
#define FPGA_SYNC_ERR_INT					9
#define RES_FAIL_ERR_INT					10
#define RES_COMP_ERR_INT					11
#define REF_PLL_ERR_INT						12
#define REF_SIG_MIS_ERR_INT					13
#define WRT_ERR_INT							14
#define PWR_ERR_INT							15
#define P32_POS_OV_ERR_INT					16
#define VME32_POS_OV_ERR_INT				17
#define VME37_POS_OV_ERR_INT				18
#define USR_VEL_ERR_INT						19
#define VEL_ERR_INT							20

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

SIS1100W_STATUS stat;


unsigned int	BASE_ADDRESS[] = { 0x14000, 0x15000, 0x16000, 0x17000 }, // Base adresses 
return_code = 0,
comp_err = 0,
comp_valid_flag = 0,
NbrBdAx = 0;

unsigned short	IntVector[] = { 0x101, 0, 0x202, 0 },
SCLKDrive = 2,
Direction[] = { 0, 0, 0, 0 };


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

int Read_Write(char*, struct SIS1100_Device_Struct*, unsigned int, unsigned int*, int read_write);
int ReadVMEErrors(struct SIS1100_Device_Struct*, unsigned int);
int InitAxis(struct SIS1100_Device_Struct*);
int Init_SIS_boards(struct SIS1100_Device_Struct*);
int Init_ZMI_bd(struct SIS1100_Device_Struct*);
int ReadSamplePosition37(struct SIS1100_Device_Struct*, unsigned int, double*);
int ReadSamplePosition32(struct SIS1100_Device_Struct*, unsigned int, double*);
int ReadAllSamplePosition37(struct SIS1100_Device_Struct*, double*);
int ReadAllSamplePosition32(struct SIS1100_Device_Struct*, double*);
int ReadPosition37(struct SIS1100_Device_Struct*, unsigned int, double*);
int ReadPosition32(struct SIS1100_Device_Struct*, unsigned int, double*);
int ReadVelocity32(struct SIS1100_Device_Struct*, unsigned int, double*);
int ReadAllPosition37(struct SIS1100_Device_Struct*, double*);
int ReadAllPosition32(struct SIS1100_Device_Struct*, double*);
int ReadAllVelocity32(struct SIS1100_Device_Struct*, double*);
int ReadTime32(struct SIS1100_Device_Struct*, unsigned int, double*);
int ReadAllTime32(struct SIS1100_Device_Struct*, double*);
int ReadOpticalPowerUsingSSIav(struct SIS1100_Device_Struct*);
int ReadAPD_Gain(struct SIS1100_Device_Struct*, unsigned int, double*);
int EnableAuxRegisters(struct SIS1100_Device_Struct*, unsigned int);
int DisableAuxRegisters(struct SIS1100_Device_Struct*, unsigned int);
int Sclk_On(struct SIS1100_Device_Struct*);
int Sclk_Off(struct SIS1100_Device_Struct*);
int SetSampTimerFreq(struct SIS1100_Device_Struct*, unsigned int);
int SetHoldSampEnable(struct SIS1100_Device_Struct*);
int ResetHoldSampEnable(struct SIS1100_Device_Struct*);
int SetSampFlag(struct SIS1100_Device_Struct*, double);
int EnableSampleTimer(struct SIS1100_Device_Struct*);
int VMESysReset(struct SIS1100_Device_Struct*);
int GetSampFlagState(struct SIS1100_Device_Struct* dev, unsigned int val);
int Disable32bitsOverflow(struct SIS1100_Device_Struct*, unsigned int);
int Enable32bitsOverflow(struct SIS1100_Device_Struct*, unsigned int);
int EnableSinglePassInterferometer(void);
int EnableDoublePassInterferometer(void);
int ReadAllAPD_Gain(struct SIS1100_Device_Struct*, double*);
int SampleVMEPosition(struct SIS1100_Device_Struct*, unsigned int);
int ParseVMEErrorStatus2(struct SIS1100_Device_Struct*, unsigned int, unsigned int*);
int ParseVMEPosErrs(struct SIS1100_Device_Struct*, unsigned int, unsigned int*);
int ParseVMEErrorStatus1(struct SIS1100_Device_Struct*, unsigned int, unsigned int*);
int ParseVMEErrorStatus0(struct SIS1100_Device_Struct*, unsigned int, unsigned int*);
int ParseAPDErrCode(struct SIS1100_Device_Struct*, unsigned int, unsigned int*);
int BoardControlMode(struct SIS1100_Device_Struct*, unsigned int, unsigned int, unsigned int);
int BiasControlMode(struct SIS1100_Device_Struct*, unsigned int, unsigned int);
int StartBiasCalculation(struct SIS1100_Device_Struct*, unsigned int);
int SetAPDGainL2(struct SIS1100_Device_Struct*, unsigned int, unsigned int);
int ResetAxis(struct SIS1100_Device_Struct* dev, unsigned int axis);
int WaitResetComplete(struct SIS1100_Device_Struct* dev, unsigned int axis);
int SetPositionOffset32(struct SIS1100_Device_Struct*, unsigned int, unsigned int);
int SetPositionOffset37(struct SIS1100_Device_Struct*, unsigned int, unsigned int, unsigned int);
int EnableInterrupt(struct SIS1100_Device_Struct*, unsigned int, unsigned int);
int EnableGlobalInterrupt(struct SIS1100_Device_Struct*, unsigned int);
int DisableGlobalInterrupt(struct SIS1100_Device_Struct*, unsigned int);
int DisableAllInterrupts(struct SIS1100_Device_Struct*, unsigned int);
int EEPROMread(
	struct SIS1100_Device_Struct*,
	unsigned int,
	unsigned int*,
	unsigned int nBytes);

int main(int argc, char* argv[])
{
	double position[] = { 0, 0, 0, 0 },
		time[] = { 0, 0, 0, 0 },
		velocity[] = { 0, 0, 0, 0 },
		Period = 1 / 3000;	//sample period in sec
	struct SIS1100_Device_Struct dev;
	const unsigned int access_mode_AM_value[MAX_NOF_ACCESS_MODE_DEFINES] = {
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
	Init_ZMI_bd(&dev);

	InitAxis(&dev);
	EnableSinglePassInterferometer();
	SetSampFlag(&dev, 1e-2);
	EnableSampleTimer(&dev);
	while (1)
	{
		//ReadOpticalPowerUsingSSIav(&dev);
		ReadSamplePosition32(&dev, 3, position);
		//ReadAllTime32(&dev, time);
		//ReadAllVelocity32(&dev, time);

		//ReadVMEErrors(&dev,3);
		printf(" Press enter to sample data and read a new value \n");

		scanf_s("%c", sc_char, 2);
		if (!strncmp(sc_char, "q", 1))
			exit(EXIT_SUCCESS);
		printf("Sampling data... \n");
	}

	sis1100w_Close(&dev);
	printf("   \n");
	printf("   \n");
	exit(0);
}
//*


int EnableSinglePassInterferometer(void) {

	positionScale = (LAMBDA / DOUBLE_PASS_INT_POS_COEF) * (1e-6);    //Converts to mm as default
	velocityScale = SINGLE_PASS_INT_VEL_COEF * (1e-6);    //Converts to m/s as default
	return 0;
}
int EnableDoublePassInterferometer(void) {

	positionScale = (LAMBDA / DOUBLE_PASS_INT_POS_COEF) * (1e-6);    //Converts to mm as default
	velocityScale = DOUBLE_PASS_INT_VEL_COEF * (1e-6);    //Converts to m/s as default
	return 0;
}
int InitAxis(struct SIS1100_Device_Struct* dev) {
	/*************************Axis Initialization***********************************/
	char	ch_access_mode[16];
	unsigned int	vme_data = 0,
		uint_vme_address = 0,
		uint_vme_data = 0;


	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);
	for (int a = 0; a < 4; a++) {

		uint_vme_address = ADD(BASE_ADDRESS[a], zVMEIntEnab0);				// Disable VME interrupts 
		uint_vme_data = 0;

		if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);

		uint_vme_address = ADD(BASE_ADDRESS[a], zIntVector);					// Interrupt are allowed to be raised for some axis
		uint_vme_data = IntVector[a];
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);

		uint_vme_address = ADD(BASE_ADDRESS[a], zCtrl0); 					// enable sign extension of 32 bits to match 37 bits register size 
																			// when register data is written
		uint_vme_data = (Direction[a] << 4) + 0x40;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);

		uint_vme_address = ADD(BASE_ADDRESS[a], zCtrl1);					// Set Kp = -6 and Kv = -15
		uint_vme_data = 0x44;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);

		Disable32bitsOverflow(dev, a + 1);

		uint_vme_address = ADD(BASE_ADDRESS[a], zCtrl3);					// Reset RT1 and RT0
		uint_vme_data = 0x3000;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);
		uint_vme_address = ADD(BASE_ADDRESS[a], zCtrl4);					// Relative to P2 Bus
		uint_vme_data = 0x00;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);
		Sleep(1000);

		for (int a = 0; a < 4; a++)
			BoardControlMode(dev, a + 1, BIAS_CONSTANT_VOLT_MODE, 0x892);
		/*

				if ((BASE_ADDRESS[a] & 0x1000) == 0)							//Axis 1 and 3 only
				{
					uint_vme_address = ADD(BASE_ADDRESS[a], zCtrl15);					// Relative to Axis 1 and 3 only
					uint_vme_data = 0;
					if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
						printf("Register %6X access Faillure !  \n", uint_vme_address);
					if (a == SCLKDrive)
					{
						uint_vme_address = ADD(BASE_ADDRESS[a], zCtrl16);				// Set SCLK0 Sample Time (SST01-SST00) to 11
						uint_vme_data = 0xe80;
						if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
							printf("Register %6X access Faillure !  \n", uint_vme_address);
						///
						SetSampTimerFreq(dev, 1);
						///

					}
					else
					{
						uint_vme_address = ADD(BASE_ADDRESS[a], zCtrl16);				// Set SCLK0 Sample Time (SST01-SST00) to 11
						uint_vme_data = 0xc00;
						if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
							printf("Register %6X access Faillure !  \n", uint_vme_address);
					}
				}
				*/
		uint_vme_address = ADD(BASE_ADDRESS[a], zCtrl17);
		uint_vme_data = 0;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);

		SetPositionOffset37(dev, a + 1, 0, 0);
	}

	for (int a = 0; a < 4; a++)
		ResetAxis(dev, a + 1);

	uint_vme_data = 0;
	// Verifying reset complete for only 1 axis is sufficient
	if (WaitResetComplete(dev, 3) < 0)	// Wait for reset complete on the main axis
		exit(EXIT_FAILURE);
	//Sleep(10);
	return 0;
}



int DisableAllInterrupts(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis-1], zVMEIntEnab0);				// Disable VME interrupts 
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	DisableGlobalInterrupt(dev, axis);
	return 0;
}
int EnableGlobalInterrupt(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);				// Disable VME interrupts 
	uint_vme_data = 0x8000;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int DisableGlobalInterrupt(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);				// Disable VME interrupts 
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int DisableCECErrInterrupt(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab0);				
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	uint_vme_data &= 0x7FFF;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int EnableInterrupt(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int intNumber){
	unsigned int uint_vme_address = 0, uint_vme_data;
	if (intNumber < 16)
	{
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab0);
		switch (intNumber)
		{
		case CEC_ERR_INT:

			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x8000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case PHASE_NOISE_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x4000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case ACCELERATION_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x2000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case MEAS_SIG_GLITCH_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x1000;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case MEAS_SIG_DROP_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x800;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case SSI_MAX_LIM_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x400;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case MEAS_SIG_SAT_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x200;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case MEAS_SIG_MIS_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x100;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case OV_TMP_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x80;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case FPGA_SYNC_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x40;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case RES_FAIL_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x20;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case RES_COMP_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x10;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case REF_PLL_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x8;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case REF_SIG_MIS_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x4;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case WRT_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x2;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case PWR_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x1;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		default:
			break;
		}
	}
	else
	{
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab1);
		switch (intNumber)
		{
		case P32_POS_OV_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x10;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case VME32_POS_OV_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x8;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case VME37_POS_OV_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x4;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case USR_VEL_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x2;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		case VEL_ERR_INT:
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			uint_vme_data |= 0x1;
			if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
			break;
		default:
			printf("[WARNING] Unknow interrupt number\n");
			break;
		}
	}
	return 0;
}

int ResetAxis(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_data = 0x20;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}
int WaitResetComplete(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0, ct = 0;
	printf("Reseting Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zStat1);
	while (!(uint_vme_data & 0x0001))	// Wait for reset complete 
	{
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);
		ct++;
		if (ct > 0xFFFFFFF1) {

			printf("Failed to reset axis %d !  \n", axis);
			return -1;
		}

	}
	//Sleep(10);
	return 0;
}
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
		return -1;
	}

	if (nof_found_sis1100_devices == 0) {
		printf("No SIS' PCIe card found, exiting...\n");
		return -1;
	}

	printf("%d SIS' PCIe card found\n", nof_found_sis1100_devices);
	printf("Connecting to the first device...\n");
	stat = sis1100w_Get_Handle_And_Open(0 /* first device */, dev); // 
	if (stat != Stat1100Success) {
		printf("Connection to SIS' PCIe card failed\n");
		printf("\tError in 'sis1100w_Get_Handle_And_Open': %d\n", stat);
		return -1;
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
		return -1;
	}
	printf("first SIS' PCIe card initialized\n");
	printf("Initializing VME/PCI gateway...\n");
	stat = sis1100w_Init_sis3100(dev, 0);
	if (stat != Stat1100Success) {
		printf("VME/PCI gateway initialization failed...\n");
		printf("\tError in 'sis1100w_Init_sis3100': %d\n", stat);
		return -1;
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
	short_data = sis3100_data >> 16;
	printf("\t Firmware type: %d\n", (int)short_data);
	short_data = sis3100_data >> 24;
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
	short_data = sis3100_data >> 16;
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
	return 0;
}
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

	if (Read_Write(ch_access_mode, dev, BASE_ADDRESS[2], &uint_vme_data, 0) == RET_FAILED)
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
		if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zStat1), &uint_vme_data, 0) == RET_FAILED)
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
	if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[2], zFWVer), &vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	printf("\tFirmware Version: %d \n", uint_vme_data);

	if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[2], zFWRev), &vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
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
		if (EEPROMread(dev, 50 + 9 + (100 * i), &uint_vme_data, 1) == RET_FAILED)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalMin[i][0] = uint_vme_data;
		if (EEPROMread(dev, 50 + 5 + (100 * i), &uint_vme_data, 1) == RET_FAILED) /*Read optical power L2*/
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalMin[i][1] = pow(2, uint_vme_data / 1024);

		if (EEPROMread(dev, 50 + 16 + (100 * i), &uint_vme_data, 1) == RET_FAILED)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalNom[i][0] = uint_vme_data;
		if (EEPROMread(dev, 50 + 12 + (100 * i), &uint_vme_data, 1) == RET_FAILED)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalNom[i][1] = pow(2, uint_vme_data / 1024);

		if (EEPROMread(dev, 50 + 23 + (100 * i), &uint_vme_data, 1) == RET_FAILED)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalMax[i][0] = uint_vme_data;
		if (EEPROMread(dev, 50 + 19 + (100 * i), &uint_vme_data, 1) == RET_FAILED)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		SSICalMax[i][1] = pow(2, uint_vme_data / 1024);

		m = (SSICalNom[i][1] - SSICalMin[i][1]) / (SSICalNom[i][0] - SSICalMin[i][0]);
		b = SSICalMin[i][1] - (m * SSICalMin[i][0]);
		SSICalValues[i][0] = m;
		SSICalValues[i][1] = b;
	}

	/*Enable reset finds velocity*/
	for (int i = 0; i < 4; i++)
	{
		if (enableResetFindsVelocity[i])
		{
			vme_data = 0x800;
			if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zCtrl3), &vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
		}
		else
		{
			vme_data = 0;
			if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zCtrl3), &vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
		}
	}
	//Enable preset
/*
vme_data = 0x100;
if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zCtrl3), &vme_data, 1) == RET_FAILED)
	printf("Register %6X access Faillure !  \n", uint_vme_address);

*/
//Enable test mode
	for (int i = 0; i < 4; i++)
	{
		if (enableResetFindsVelocity[i])
		{
			vme_data = 0x10;
			if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zTestCtrl0), &vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
		}
		else
		{
			vme_data = 0;
			if (Read_Write(ch_access_mode, dev, ADD(BASE_ADDRESS[i], zTestCtrl0), &vme_data, 1) == RET_FAILED)
				printf("Register %6X access Faillure !  \n", uint_vme_address);
		}
	}
	return 0;
}
int SetPositionOffset32(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int offsetPos) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_data = offsetPos;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zOffsetMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}
int SetPositionOffset37(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int offsetPos32, unsigned int offsetPosExt) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	SetPositionOffset32(dev, axis, offsetPos32);
	uint_vme_data = offsetPosExt;
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}
int ReadVMEErrors(struct SIS1100_Device_Struct* dev, unsigned int axis) {
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
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u VME Status Error 2: %X \n", axis, uint_vme_data);
	printf("***************************Errors*******************************\n");
	TestStat1 = uint_vme_data;
	if (TestStat1 & 0x800)
		printf("EEPROM Error has been detected\n");
	ParseVMEErrorStatus0(dev, axis, &VMEErrorStatus0);
	ParseVMEErrorStatus1(dev, axis, &VMEErrorStatus1);
	ParseVMEErrorStatus2(dev, axis, &VMEErrorStatus2);
	ParseVMEPosErrs(dev, axis, &VMEPosError);
	ParseAPDErrCode(dev, axis, &APDError);
	printf("**************************************************************\n");
	return 0;
}
int ClearEEPROMErrs(struct SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zTestCmd1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	uint_vme_data |= 0x4;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);


	return 0;
}
int BoardControlMode(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int biasControlMode, unsigned int APDGain) {
	/*Activate APD Constant voltage mode*/
	BiasControlMode(dev, axis, 1);
	/*Set APD GAIN L2 to 892*/
	SetAPDGainL2(dev, axis, APDGain);
	/* Start bias calculation */
	StartBiasCalculation(dev, axis);
	return 0;
}
/// <summary>
/// Configure Bias control mode for either axis.
/// </summary>
/// <param device="dev">
/// The device subjected to the change
/// </param>
/// <param axis="axis">
/// The targeted axis
/// </param>
/// <param Mode="mode">
/// 0 -> Off: The APD bias is set to the minimum value i.e 55V
/// 1 -> CONSTANT vOLTAGE Mode(For Diagnostic use only)
/// 2 -> Constant Gain Mode
/// 3 -> Constant Optical Power Mode  
/// 4 -> Sig RMS Adjust Mode
/// </param>
/// <returns>
/// 0 if successful
/// </returns>
int BiasControlMode(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int mode) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	if (mode > 4)
	{
		printf("Unknow mode: mode is ranged 0 to 4 \n");
		return -1;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl5);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	uint_vme_data |= mode;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	return 0;
}
int StartBiasCalculation(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	uint_vme_data = 0x40;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	return 0;
}
int SetAPDGainL2(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int APDGain) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	if (APDGain > 0xFFFF)
	{
		printf("Inapropriate value. range is 0 to 4 \n");
		return -1;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDGain_L2_set);
	uint_vme_data |= APDGain;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	return 0;
}
int ParseVMEErrorStatus2(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int* VMEErrorStatus2Reg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat2);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u VME Status Error 0: %X \n", axis, uint_vme_data);
	*VMEErrorStatus2Reg = uint_vme_data;

	if (uint_vme_data & 0x4000)
		printf("Proc fail has been detected\n");
	if (uint_vme_data & 0x2000)
		printf("Bias supply error has been detected\n");
	if (uint_vme_data & 0x1000)
		printf("Write Protect error has been detected\n");
	if (uint_vme_data & 0x80) {
		printf("Sig max has been detected, The input signal's optical power is above the allowed range\n");
		printf("Fix: -Try to increase the max optical power in SSI MAX register\n ");
		printf("     -Reduce the input optical power using a neutral density filter\n ");
	}
	if (uint_vme_data & 0x40) {
		printf("Sig min has been detected, The input signal's optical power is below the allowed range\n");
		printf("Fix: -Try to decrease the min optical power in SSI min register\n ");
		printf("     -Increase the input signal's optical power \n ");
	}
	if (uint_vme_data & 0x10)
		printf("Bias Error has been detected\n");
	if (uint_vme_data & 0x8)
		printf("APD DC Error has been detected\n");
	if (uint_vme_data & 0x4)
		printf("APD command Error has been detected\n");
	if (uint_vme_data & 0x2)
		printf("APD Fail Error has been detected\n");
	if (uint_vme_data & 0x1)
		printf("APD Temp Error has been detected\n");

	return 0;
}
int ParseVMEPosErrs(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int* VMEPosErrReg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosErr);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u VME Status Error 2: %X \n", axis, uint_vme_data);
	*VMEPosErrReg = uint_vme_data;
	if (uint_vme_data & 0x8)
		printf("Measurement Error has been detected\n");
	if (uint_vme_data & 0x4)
		printf("Ref Error has been detected\n");



	return 0;
}
int ParseVMEErrorStatus1(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int* VMEErrorStatus1Reg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	printf("Axis %u VME Status Error 1: %X \n", axis, uint_vme_data);
	*VMEErrorStatus1Reg = uint_vme_data;
	if (uint_vme_data & 0x8)
		printf("VME 32bits postion register has overflowed\n");
	if (uint_vme_data & 0x4)
		printf("VME 37bits postion has overflowed\n");
	if (uint_vme_data & 0x2)
		printf("User velocity error has been detected\n");
	if (uint_vme_data & 0x1)
		printf("Velocity error has been detected\n");
	return 0;
}
int ParseVMEErrorStatus0(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int* VMEErrorStatus0Reg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat0);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
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
	return 0;
}
int ParseAPDErrCode(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int* APDErrCode) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDErr);		//Read APD errors
	EnableAuxRegisters(dev, axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
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
		printf("APD Math Temp error, Invalid APD temperature, range is 10°C to 70°C \n");
		break;
	case 138:
		printf("APD Math T0, Invalid APD bias equation T0, range is 10°C to 50°C \n");
		break;
	case 139:
		printf("APD Math TC, Invalid APD bias equation TC, range is 0.3 to 0.9V/°C \n");
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

		return 0;
	}
	return 0;
}
/*This fuction reads the ZMI "Sample position Register" on 37 bits
   - Reading this register latches data AND reads the full position value
Note: this is different than reading the "position Register" which does not latch data
*/
int ReadSamplePosition37(struct SIS1100_Device_Struct* dev, unsigned int axis, double* position) {
	int val;
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	int temp32 = 0;
	uint_vme_data = 0;
	printf("Reading Sample Position on Axis %d...  \n", axis);
	Disable32bitsOverflow(dev, axis);
	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMESampPosMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	temp32 = (int)uint_vme_data;
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMESampPosExt);		//Read the Ext
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
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
	return 0;
}
/*This fuction reads the ZMI "Sample position Register" on 32 bits
   - Reading this register latches data AND reads the full position value
Note: this is different than reading the "position Register" which does not latch data
*/
int ReadSamplePosition32(struct SIS1100_Device_Struct* dev, unsigned int axis, double* position) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_data = 0;
	Enable32bitsOverflow(dev, axis);
	printf("Reading Sample Position on Axis %d...  \n", axis);
	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMESampPosMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	*position = (double)((int)(uint_vme_data) * (positionScale));

	printf("-------------------------------------------------------\n");
	printf("Measured Sample Position on axis %d: %f  mm \n", axis, *position);
	printf("-------------------------------------------------------\n");
	Disable32bitsOverflow(dev, axis);
	return 0;
}
/*This fuction reads the ZMI "Position Register" on 37 bits
   - Reading this register reads the full position value
Note: this is different than reading the "Sample position Register" which latch data before reading
*/
int ReadPosition37(struct SIS1100_Device_Struct* dev, unsigned int axis, double* position) {
	int val = 0, temp32 = 0;
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosMSB);
	printf("Reading Position on Axis %d...  \n", axis);
	Disable32bitsOverflow(dev, axis);
	//EnableSampleTimer(dev);
	SampleVMEPosition(dev, axis);
	SetHoldSampEnable(dev);
	//Read the MSB and LSB	
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	val = (int)uint_vme_data;
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosExt);		//Read the Ext
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %06X access Faillure !  \n", uint_vme_address);
	ResetHoldSampEnable(dev);
	val = (int)((short)uint_vme_data);
	*position = ((double)(val)) * (2 ^ 32) + (double)((unsigned int)temp32) * positionScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Position on axis %d: %f mm \n", axis, *position);
	printf("-------------------------------------------------------\n");

	return 0;
}
/*This fuction reads the ZMI "Position Register" on 32 bits
   - Reading this register reads the full position value
Note: this is different than reading the "Sample position Register" which latch data before reading
*/
int ReadPosition32(struct SIS1100_Device_Struct* dev, unsigned int axis, double* position) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading Position on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosMSB);
	Enable32bitsOverflow(dev, axis);
	//EnableSampleTimer(dev);	
	SampleVMEPosition(dev, axis);
	SetHoldSampEnable(dev); // value of the position register is held until its LSB is read 
	//Read the MSB and LSB	
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	ResetHoldSampEnable(dev);
	*position = (double)((int)uint_vme_data) * positionScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Position on axis %d: %f mm \n", axis, *position);
	printf("-------------------------------------------------------\n");
	Disable32bitsOverflow(dev, axis);

	return 0;
}

int ReadVelocity32(struct SIS1100_Device_Struct* dev, unsigned int axis, double* position) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading Velocity on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosMSB);
	//EnableSampleTimer(dev);
	SampleVMEPosition(dev, axis); // the function both sample velocity and value
	//Read the MSB and LSB	
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	ResetHoldSampEnable(dev);
	*position = (double)((int)uint_vme_data) * velocityScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Velocity on axis %d: %f m/s \n", axis, *position);
	printf("-------------------------------------------------------\n");
	Disable32bitsOverflow(dev, axis);

	return 0;
}
int ReadAllSamplePosition32(struct SIS1100_Device_Struct* dev, double* SamplePosition32_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadSamplePosition32(dev, i, &position);
		*(SamplePosition32_buf + i - 1) = position;
		position = 0.0;
	}
	return 0;
}

int ReadAllSamplePosition37(struct SIS1100_Device_Struct* dev, double* SamplePosition37_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadSamplePosition37(dev, i, &position);
		*(SamplePosition37_buf + i - 1) = position;
		position = 0.0;
	}
	return 0;
}

int ReadAllPosition32(struct SIS1100_Device_Struct* dev, double* Position32_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadPosition32(dev, i, &position);
		*(Position32_buf + i - 1) = position;
		position = 0.0;
	}
	return 0;
}

int ReadAllVelocity32(struct SIS1100_Device_Struct* dev, double* Velocity32_buf) {

	double Velocity = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadVelocity32(dev, i, &Velocity);
		*(Velocity32_buf + i - 1) = Velocity;
		Velocity = 0.0;
	}
	return 0;
}

int ReadAllPosition37(struct SIS1100_Device_Struct* dev, double* Position37_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadPosition37(dev, i, &position);
		*(Position37_buf + i - 1) = position;
		position = 0.0;
	}
	return 0;
}
bool IsVMEPos32Overflow(struct SIS1100_Device_Struct* dev, unsigned int axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	printf("Reading Elapsed time on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	if ((uint_vme_data & 0x0008))
		return true;
	return false;
}

bool IsVMEPos37Overflow(struct SIS1100_Device_Struct* dev, unsigned int axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	printf("Reading Elapsed time on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	if ((uint_vme_data & 0x0004))
		return true;
	return false;
}

bool IsUserVelError(struct SIS1100_Device_Struct* dev, unsigned int axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	printf("Reading Elapsed time on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	if ((uint_vme_data & 0x0002))
		return true;
	return false;
}

bool IsVelError(struct SIS1100_Device_Struct* dev, unsigned int axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	printf("Reading Elapsed time on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	if ((uint_vme_data & 0x0001))
		return true;
	return false;
}

bool IsAccError(struct SIS1100_Device_Struct* dev, unsigned int axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	printf("Reading Elapsed time on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat0);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	if (uint_vme_data & 0x2000)
		return true;
	return false;
}

int ClearPosAndVelErrs(struct SIS1100_Device_Struct* dev, unsigned int axis) {

	unsigned int uint_vme_data = 0xF,
		uint_vme_address = 0;

	printf("Reseting Position and velocity errors on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr1);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	return 0;
}
int ClearAllVMEErrs(struct SIS1100_Device_Struct* dev, unsigned int axis) {

	unsigned int uint_vme_data = 0xFFFF,
		uint_vme_address = 0;

	printf("Reseting all VME errors on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr0);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr1);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr2);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	uint_vme_data = 1;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
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
int ClearPosAndVelErrs_ForAllAxis(struct SIS1100_Device_Struct* dev, unsigned int axis) {

	unsigned int uint_vme_data = 0xFFFF,
		uint_vme_address = 0;

	for (int i = 1; i < 5; i++)
	{
		ClearPosAndVelErrs(dev, i);
	}

	return 0;
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

	return 0;
}
/*This fuction reads the ZMI "Time Register" on 32 bits
*/
int ReadTime32(struct SIS1100_Device_Struct* dev, unsigned int axis, double* time) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading Elapsed time on Axis %d...  \n", axis);
	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMETimeMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	*time = uint_vme_data * timeScale;
	printf("-------------------------------------------------------\n");
	printf("Elapsed time is : %f s\n", *time);
	printf("-------------------------------------------------------\n");
	return 0;
}
int ReadAllTime32(struct SIS1100_Device_Struct* dev, double* Time32_buf) {

	double time = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadTime32(dev, i, &time);
		*(Time32_buf + i - 1) = time;
		time = 0.0;
	}
	return 0;
}

/*This fuction reads the ZMI "Time Register" on 32 bits
*/
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
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);

		SSI[i] = (double)uint_vme_data;
	}

	ReadAllAPD_Gain(dev, APD_Gain);

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

	return 0;
}
int SetSSISquelch(int squelchValue, unsigned int axis, struct SIS1100_Device_Struct* dev) {

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
	if (Read_Write("A24D16", dev, uint_vme_address, &value, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}
int GetSSIMaxVal(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int* SSIMax)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_data = 0;
	// The SSI max value (0xFFFF) corresponds to 1.25V

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zSSIMax);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	*SSIMax = uint_vme_data;
	printf("SSI Max val on Axis %u is : %d  \n", axis, uint_vme_data);
	return 0;

}

int GetAllSSIMaxVal(struct SIS1100_Device_Struct* dev, unsigned int* SSIMax_Buf)
{
	unsigned int uint_vme_data = 0;
	for (int i = 1; i < 5; i++)
	{
		// The SSI max value (0xFFFF) corresponds to 1.25V
		GetSSIMaxVal(dev, i, &uint_vme_data);
		*(SSIMax_Buf + i - 1) = uint_vme_data;
	}

	return 0;

}

int ResetSSIMaxVal(struct SIS1100_Device_Struct* dev, unsigned int axis, unsigned int* SSIMax)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_data = 0;
	// The SSI max value (0xFFFF) corresponds to 1.25V

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zSSIMax);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	*SSIMax = uint_vme_data;
	printf("SSI Max val on Axis %u is : %u  \n", axis, uint_vme_data);
	return 0;

}
int CheckSaturation(struct SIS1100_Device_Struct* dev, unsigned int axis, bool* sat)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	// The SSI max value (0xFFFF) corresponds to 1.25V

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat0);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

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
	return 0;

}

int CheckAllSaturation(struct SIS1100_Device_Struct* dev, bool* sat_Buf)
{
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	bool sat = false;
	for (int i = 1; i < 5; i++)
	{
		CheckSaturation(dev, i, &sat);
		*(sat_Buf + i - 1) = sat;
	}

	return 0;

}
/*This fuction reads the ZMI "Time Register" on 32 bits
*/
int ReadAPD_Gain(struct SIS1100_Device_Struct* dev, unsigned int axis, double* APD_Gain) {
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_data = 0;
	double APD_Gain_L2 = 0.0;

	EnableAuxRegisters(dev, axis);
	printf("Reading APD GAIN L2 on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDGain_L2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	APD_Gain_L2 = (double)uint_vme_data;
	*APD_Gain = pow(2, ((int)(APD_Gain_L2 / 1024)));
	printf("-------------------------------------------------------\n");
	printf("APD Gain on axis %u: %f \n", axis, *APD_Gain);
	printf("-------------------------------------------------------\n");
	DisableAuxRegisters(dev, axis);
	return 0;
}

int ReadAllAPD_Gain(struct SIS1100_Device_Struct* dev, double* APD_Gain_Buf) {

	double APD_Gain = 0.0;

	for (int i = 1; i < 5; i++)
	{
		ReadAPD_Gain(dev, i, &APD_Gain);
		*(APD_Gain_Buf + i - 1) = APD_Gain;
		APD_Gain = 0.0;
	}
	return 0;
}

int EnableAuxRegisters(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	// Enable auxiliary registers
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_data |= 0x200;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	return 0;
}

int Enable32bitsOverflow(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	// Enable auxiliary registers

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_data |= 0x800;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int Disable32bitsOverflow(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	// Enable auxiliary registers
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_data &= 0xF7FF;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int DisableAuxRegisters(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	// Disable auxiliary registers
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);
	uint_vme_data = 0;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_data &= 0xFDFF;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int SampleVMEPosition(struct SIS1100_Device_Struct* dev, unsigned int axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	printf("Sampling velocity and position on axis %d...\n", axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_data |= 0x200;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	while (!(uint_vme_data & 0x400))
	{
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);
	}

	return 0;
}
int Sclk_On(struct SIS1100_Device_Struct* dev) {
	//Turn on bits 7 and 9 (SCLK Timer enable and SCLK0 output)
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl16);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_data |= 0x280;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}
int VMESysReset(struct SIS1100_Device_Struct* dev) {
	printf("Hard reseting the system...\n");
	stat = sis1100w_VmeSysreset(dev);

	if (stat != Stat1100Success) {
		printf("Errors occured while hard reseting the card\n");
		return -1;
	}
	printf("Reseting Zygo board...\n");
	return 0;
}
int Sclk_Off(struct SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl16);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_data &= 0xFD7F;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int SetSampTimerFreq(struct SIS1100_Device_Struct* dev, unsigned int sampFreq) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zSampleTimer);
	uint_vme_data = sampFreq;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int SetHoldSampEnable(struct SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);
	uint_vme_data |= 0x2000;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
}

int ResetHoldSampEnable(struct SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);
	uint_vme_data &= 0xDFFF;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return 0;
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
	return 0;
}


int EnableSampleTimer(struct SIS1100_Device_Struct* dev) {
	Sclk_On(dev);
	return 0;
}
int StopSampling(struct SIS1100_Device_Struct* dev) {
	Sclk_Off(dev);
	return 0;
}

int GetSampFlagState(struct SIS1100_Device_Struct* dev, unsigned int val) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl2);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	val = uint_vme_data;
	return val;
}
int EEPROMread(
	struct SIS1100_Device_Struct* dev,
	unsigned int offset,
	unsigned int* uint_vme_data,
	unsigned int nBytes) {
	unsigned int uint_vme_address = 0,
		vme_data = 0;
	char ch_access_mode[10];
	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);
	uint_vme_address = ADD(BASE_ADDRESS[2], zTestStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	// Verify the EEPROM is error-free 
	if ((vme_data & 0x800) != 0) {
		uint_vme_address = ADD(BASE_ADDRESS[2], zTestCmd1); // Clear the error 
		vme_data = 0x04;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &vme_data, 1) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);
	}
	// Wait until EEPROM Busy clears 
	vme_data = 0x0200;
	while (vme_data & 0x0200) {
		uint_vme_address = ADD(BASE_ADDRESS[2], zTestStat1);
		vme_data = 0;
		if (Read_Write(ch_access_mode, dev, uint_vme_address, &vme_data, 0) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);

	}; // Wait while EEPROM busy 
		// Start EEPROM Read 
	//First send the adress to read
	uint_vme_address = ADD(BASE_ADDRESS[2], zEEpromCtrl);
	vme_data = zEEReadCmd | (offset & 0x3ff); // keep the last 10 bits and add them to the eerdcmd
	if (Read_Write(ch_access_mode, dev, uint_vme_address, &vme_data, 1) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	vme_data = 0x0200;
	uint_vme_address = ADD(BASE_ADDRESS[2], zTestStat1);
	while (vme_data & 0x0200) {

		if (Read_Write(ch_access_mode, dev, uint_vme_address, &vme_data, 0) == RET_FAILED)
			printf("Register %6X access Faillure !  \n", uint_vme_address);

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
		return -1;
		break;
	}

	uint_vme_address = ADD(BASE_ADDRESS[2], zEEpromReadReg);
	*uint_vme_data = 0;
	if (Read_Write(ch_access_mode, dev, uint_vme_address, uint_vme_data, 0) == RET_FAILED)
		printf("Register %6X access Faillure !  \n", uint_vme_address);

	return 0;

}

int Read_Write(char* ch_access_mode,
	struct SIS1100_Device_Struct* dev,
	unsigned int uint_vme_address,
	unsigned int* uint_vme_data,
	int read_write) {

	/*
	read_wreite: 0->read, 1 -> write
	*/

	/**************************************************************************/
	/***   "A24D32":   A24  privileged data access                       ***/
	/**************************************************************************/

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
