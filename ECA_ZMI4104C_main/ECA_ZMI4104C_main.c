/***************************************************************************/
/*                                                                         */
/*  Filename: ECA_ZMI4104C_main.c								           */
/*                                                                         */
/*  FunCtion:  SIS1100/SIS310x Visual C								*/
/*                                                                         */
/*  Author:                Pythagore Guekam                                 */
/*  date:                 19.03.2021                                       */
/*  last modification:    20.03.2021                                       */
/*                                                                         */

/*  © 2021                                                                 */
/*                                                                         */
/***************************************************************************/

//#include "stdafx.h"

#include "ECA_ZMI4104C_main.h"
HANDLE vmeIrq6Event, lemoIN1Event;
HANDLE  hThreadArray[THREADCOUNT];
HANDLE vmeIntThread, lemoIN1Thread, fastReadThread, WaitForSis3100IrqThread, WaitForVmeIrqThread;
DWORD WINAPI vmeIntThreadFunc(LPVOID);
int main(void);
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
int  CreateThreads(void)
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
	return RET_SUCCESS;
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
InterferoConfig curInterferoConfig;

unsigned int pdg[100];
volatile int irq;
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
	char sc_char[4];
	double unitScale[4][4] = { {positionScale * (10 ^ 3), positionScale * (10 ^ 6), positionScale * (10 ^ 9), 1} \
					   , {timeScale, timeScale * (10 ^ 3), timeScale * (10 ^ 6), 1} \
					   , {velocityScale, velocityScale * (10 ^ 3), velocityScale * (10 ^ 6), 1} \
					   , {1 * (10 ^ -3), 1, 1 * (10 ^ 3), 1} };
	BIAS_MODE bias_mode = BIAS_SIG_RMS_ADJUST_MODE;
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
	Init_ZMI_bd(&dev);

	InitAxis(&dev, bias_mode);
	EnableDoublePassInterferometer();
	//Here you should first strat up the motor at the planned running velocity to enable CEC hardware
	// to calculate CE coefficients. thereafter you should start acquisition

	enableSampling(&dev, 3e-4);
#if ACTIVATE_CEC
	if (configureCEChardware(&dev, 3, 96, 31457) != RET_SUCCESS) // used default velocity value;
	{
		printf("Can not configure CEC hardware\n");
		return RET_FAILED;
	}
#endif
	double pos = 0.0, temp_pos=0.0;
	FILE* fd=NULL;
	vme_irq_level = INT_LEVEL6;
	vme_irq_vector = 12;
	char fifoAxis[2];
	int ret = 0;
	CEratios ceRatios = { 0.0,0.0,0.0 };
	CECoeffs ceCoeffs = { 0.0,0.0,0.0 };
	CEratioUnits ratioUnits = ratio_in_percent;
	fifoParam testparam;
	UINT val1, val2;
	double pos1;
	dwWaitResult = WaitForSingleObject( //wait for the main thread to sent an event
		ghMutex, // event handle
		INFINITE);    // indefinite wait*/
	if (!(base_A24D32_ptr = allocateMemSpace(64 * 1024)))
		return RET_FAILED;
	if (!(base_A24D32_FR_ptr = allocateMemSpace(64 * 1024)))
		return RET_FAILED;

	/*  test the flyscan mode*/
#if FLYSCAN_MODE_ON
	if (configureFlyscan(&dev, 1, 3e-4, 0) != RET_SUCCESS) {
		return RET_FAILED;
	}
#endif	
	CreateThreads();
	while (1)
	{
		//ReadOpticalPowerUsingSSIav(&dev);
		// rmq: some functions I wrote tend to be incompatible with readposition32 function, need
		// to check its implementation
		//ReadPosition32(&dev, AXIS3, position);
		//ReadSamplePosition32(&dev, AXIS3, position);
		//ReadTime32_ForAllAxis(&dev, time);
		//ReadVelocity32_ForAllAxis(&dev, time);
		/*dwWaitResult = WaitForSingleObject( //wait for the main thread to sent an event
			ghMutex, // event handle
			INFINITE);    // indefinite wait*/
			//ReadAllErrs(&dev, AXIS3);
			/*if (!ReleaseMutex(ghMutex))
				printf("Error while releasing mutex\n");*/
		//*/
#if ACTIVATE_CEC
		if (readCalcCECoeffs(&dev, 3, &ceCoeffs) != RET_SUCCESS)
		{
			printf("Failed to calculate CE ratios \n");
			valid_flag = 1;
			break;
		}
		printf("CEC0coeff %f+i%f, CEC1coeff %f, CECNcoeff  %f+i%f\n", ceCoeffs.CEC0coeff.rpart, 
			ceCoeffs.CEC0coeff.ipart, ceCoeffs.CEC1coeff, ceCoeffs.CECNcoeff.rpart, ceCoeffs.CECNcoeff.ipart);
		if (calculateCEratio(&dev, 3, &ceRatios, ratioUnits) != RET_SUCCESS)
		{
			printf("Failed to calculate CE ratios \n");
			valid_flag = 1;
			break;
		}
		printf("Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
		ceRatios.measSignal = 0;
		ceRatios.CE0ratio = 0;
		ceRatios.CENratio = 0;
		if(getAproximateCEratio(&dev, 3, &ceRatios, ratioUnits) != RET_SUCCESS)
		{
			printf("Failed to calculate CE ratios \n");
			valid_flag = 1;
			break;
		}
		printf("Approximate Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
		//*/
		readCEerrorStatReg(&dev, 3, &ret);
		printf(" Press \'a\' to start acquisition \'q\' to exit \n");
		//*/
#endif

		printf(" Press \'a\' to start acquisition \'q\' to exit \n");
		scanf_s("%c", sc_char, 2);
		if (!strncmp(sc_char, "q", 1))
		{
			valid_flag = 1;
			break;
		}
		/*  test the FIFO flyscan mode*/
#if FIFO_FLYSCAN_MODE
		fifoAxis[0] = AXIS3;
		fifoAxis[1] = AXIS2;
		testparam.acqTime = 0;
		testparam.freq = 8000;
		testparam.nbrPts = (UINT)4000;
		configureFifoFlyscan(&dev, 3, &testparam, base_A24D32_ptr);
		if (fopen_s(&fd, "C:\\Users\\guekam\\source\\repos\\ECA_ZMI4104_Project\\ECA_ZMI4104C_main\\FIFO_Position_values.csv", "a") != RET_SUCCESS)
			return RET_FAILED;

		fprintf(fd, "Axis1; ; Axis3\n");
		for (UINT j = 0; j < (testparam.nbrPts); j++) {
			val1 = (unsigned int)(base_A24D32_ptr[j]);
			pos1 = (double)(((int)val1) * positionScale);
			fprintf(fd, "%lf; 0x%x\n", pos1, val1);
			val1 = 0;
			pos1 = 0;
		}
		printf("file closed \n");
#endif
//*/
#if FLYSCAN_MODE_ON
		printf("Sampling data... \n");
		if (getFlyscanData(&dev, base_A24D32_FR_ptr, base_A24D32_ptr, &ret) != RET_SUCCESS)
		{
			valid_flag = 1;
			break;
		}
		if (processRAMData(ret, base_A24D32_FR_ptr, base_A24D32_ptr) != RET_SUCCESS)
		{
			valid_flag = 1;
			break;
		}
#endif
		//*/
		if (valid_flag == 1)
			break;
		//ClearAllVMEErrs_ForAllAxis(&dev);
	}
	//=================================================================
	printf("Main thread waiting for threads to exit...\n");

	printf("Freeing buf 0x%p and 0x%p\n", base_A24D32_FR_ptr, base_A24D32_ptr);
	free(base_A24D32_FR_ptr);
	free(base_A24D32_ptr);
	_fcloseall();
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
int allocateWinMemSpace(SIS1100_Device_Struct* dev, UCHAR *nof_windows) {

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
int releaseWinMemSpace(SIS1100_Device_Struct* dev, UCHAR nof_vme_windows) {
	// cleanup
	stat = sis1100w_vme_unmap(dev, nof_vme_windows * 4);
	if (stat != Stat1100Success) {
		printf("Error in 'sis1100w_vme_unmap': %d\n", stat);
		return RET_FAILED;
	}

	sis1100w_Close(dev);
	printf("Windows -vme map demo- finished \n");

}
int sis3301w_Init(SIS1100_Device_Struct* dev, uint32_t mod_base, uint32_t vme_irq_level, uint32_t vme_irq_vector)
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
/// <summary>
/// This function configure and enable the CE compensation
/// </summary>
/// <param name="dev">device </param>
/// <param name="axis">the axis number</param>
/// <param name="ceVelMin">his value specifies the minimum velocity where CEC will be applied</param>
/// <param name="ceVelMax">This value specifies the maximum velocity where CEC will be applied</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int configureCEChardware(SIS1100_Device_Struct* dev, UCHAR axis, USHORT ceVelMin, USHORT ceVelMax) {
		unsigned int uint_vme_address = 0, uint_vme_data=0;
		char sc_char[3];
		/*At the startup CEC is disabled*/
		/*When a motion occurs, CEC coeff are calculated*/
		/*1-First of all we should set CE_Min_Vel and CE_Max_Vel
		 * - The default value of CE_Min_Vel is 96 which represents a 7.3Khz Doppler shift or 
		 * a velocity of approximately 1.2mm/s. . The units of this register are 76.3 Hz, or 12 μm/sec for a double-pass
		 * interferometer Its value shouldn't be less than 24 which represents a 1.8Khz Doppler shift
		 * and may cause improper operation of the CEC fuction
		 * - The default value of CE_Max_Vel is 31457  which represents a 2.4Mhz Doppler shift or a velocity of approximately 
		 * 0.38m/s(double pass)*/


		/*1-Then, we should perform a motion at a velocity higher than the CE_Min_Vel and 
		 *greater than CE_Max_Vel so that the the CEC coeff can be calculated. The motion should last at least
		 *4.1ms before CEC coeff can be updated
		 */

		if (ceVelMin < 24) {
			printf("ERROR: The CE Min Velocity should not be set to a value smaller than 24, which represents a \
				1.8 kHz Doppler shift, or a velocity of approximately 0.29 mm/s. this may cause improper operation of the CEC function\n");
			return RET_FAILED;
		}
		//set ce min velocity
		SetCEMinVel(dev, axis, CE_MIN_VEL);
		//set ce max velocity
		SetCEMaxVel(dev, axis, CE_MAX_VEL);
		printf("Start the motor for a displacement of at least 1s then press Enter. CEC hardware need to observe the motion at startup \
in order to determine correct CE coefficients \n");
		scanf_s("%c", sc_char, 2);
		if (waitCEinit2Complete(dev, axis) != RET_SUCCESS) {
			printf("failed to initialize CE hardware\n");
			return RET_FAILED;
		}
		printf(" CE hardware configuration is complete\n");
		
		if (EnableCECcompensation(dev, axis) != RET_SUCCESS) {
			printf("failed to enable CE compensation\n");
			return RET_FAILED;
		}

		readCEerrorStatReg(dev, axis, &uint_vme_data);
		return RET_SUCCESS;

}
int readCEerrorStatReg(SIS1100_Device_Struct* dev, unsigned char axis, PUINT CEstatReg) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCEerrorStat);
	uint_vme_data = 0;
	printf("Reading CE status register\n");
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	*CEstatReg = uint_vme_data;
	if ((uint_vme_data & 0x1)) {
		printf("The cyclic error 0 has exceeded the value set in the CE 0 Limit register\n ");
	}
	if ((uint_vme_data & 0x2)) {
		printf("The cyclic error N has exceeded the value set in the CE N Limit register\n ");
	}
	if ((uint_vme_data & 0xFFF0)) {
		printf("An arithmetic overflow has occured at some point in the CEC signal processing.This may occur if the CE levels are greater than 20 percent . \n");
	}
	return RET_SUCCESS;
}
DWORD WaitForVmeIrqThreadFunc(LPVOID lpParam)
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
DWORD WaitForSis3100IrqThreadFunc(LPVOID lpParam)
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
int	AckForSis3100VME_Irq(SIS1100_Device_Struct* dev,uint32_t sis_get_irq_level)
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

	positionScale = SINGLE_PASS_INT_POS_COEF;    //Converts to mm as default
	curInterferoConfig = SGLE;
	velocityScale = SINGLE_PASS_INT_VEL_COEF * (1e-3);    //Converts to m/s as default
	return RET_SUCCESS;
}
int EnableDoublePassInterferometer(void) {

	positionScale = DOUBLE_PASS_INT_POS_COEF;    //Converts to mm as default
	curInterferoConfig = DBLE;
	velocityScale = DOUBLE_PASS_INT_VEL_COEF * (1e-3);    //Converts to m/s as default
	return RET_SUCCESS;
}

int InitAxis(SIS1100_Device_Struct* dev, BIAS_MODE bias_mode) {
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
		SetKpAndKvCoeff(dev, a, 5, 4);					// Set Kp = -7 and Kv = -15		

		BoardControlMode(dev, a, bias_mode);
		ResetAxis(dev, a);
	}

	uint_vme_data = 0;


	return RET_SUCCESS;
}
int DisableAllVMEInterrupts(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int EnableAllVMEInterrupts(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int EnableVMEGlobalInterrupt(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int processRAMData(UINT nbrAxis, PUINT base_A24D32_axis1_ptr, PUINT base_A24D32_axis3_ptr) {
	static int a = 0;
	static SYSTEMTIME  lt;
	GetLocalTime(&lt);
	static FILE* fd;
	UINT val1=0, val2 = 0;
	double pos1 = 0.0, pos2 = 0.0;

	if (nbrAxis>=2) {
		if (!base_A24D32_axis1_ptr || !base_A24D32_axis3_ptr) {
			printf("Based on the number of axis which is %d, none of the pointer argument is allow to be NULL", nbrAxis);
			return RET_FAILED;
		}
	}
	else {
		if (!base_A24D32_axis1_ptr && !base_A24D32_axis3_ptr) {
			printf("Based on the number of axis which is %d, both pointer arguments can not be NULL", nbrAxis);
			return RET_FAILED;
		}
	}
	if (fopen_s(&fd, "C:\\Users\\guekam\\source\\repos\\ECA_ZMI4104_Project\\ECA_ZMI4104C_main\\Position_values.csv", "a") != RET_SUCCESS)
		return RET_FAILED;
	fprintf(fd, "[***********; %d/%d/%d at %d:%d] ;************\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute);
	switch (nbrAxis)
	{
	case 1:
		fprintf(fd, "Axis3\n");
		for (int i = 0; i < 64; i++) {
			// Shift to the next page
			for (int j = 0; j < 256; j++) {
				val1 = (unsigned int)(base_A24D32_axis3_ptr[i * 256 + j]);
				pos1 = (double)(((int)val1) * positionScale);
				pos1 /= 8.0;
				fprintf(fd, "%lf; 0x%x \n", pos1, val1);
				val1 = 0;
			}
		}
		break;
	case 2:
		fprintf(fd, "Axis1; ; Axis3\n");
		for (int i = 0; i < 64; i++) {
			// Shift to the next page
			for (int j = 0; j < 256; j++) {
				val1 = (unsigned int)(base_A24D32_axis1_ptr[i * 256 + j]);
				pos1 = (double)(((int)val1) * positionScale)/8.0;
				val2 = (unsigned int)(base_A24D32_axis3_ptr[i * 256 + j]);
				pos2 = (double)(((int)val2) * positionScale) / 8.0;
				fprintf(fd, "%lf; 0x%x; %lf; 0x%x \n", pos1, val1, pos2, val2);
				val1 = 0;
				val2 = 0;
			}
		}
		break;
	default:
		fprintf(fd, "Axis1; ; Axis2; ; Axis3; ; Axis4\n");
		UINT val11 = 0;
		double pos11 = 0.0;
		UINT val21 = 0;
		double pos21 = 0.0;
		for (int i = 0; i < 64; i++) {
			// Shift to the next page
			for (int j = 0; j < 256/2; j++) {
				val1 = (unsigned int)(base_A24D32_axis1_ptr[i * 256 + j * 2]);
				val11 = (unsigned int)(base_A24D32_axis1_ptr[i * 256 + j * 2 + 1]);
				pos1 = (double)(((int)val1) * positionScale) / 8.0;
				pos11 = (double)(((int)val11) * positionScale) / 8.0;

				val2 = (unsigned int)(base_A24D32_axis3_ptr[i * 256 + j * 2]);
				val21 = (unsigned int)(base_A24D32_axis3_ptr[i * 256 + j * 2 + 1]);
				pos2 = (double)(((int)val2) * positionScale) / 8.0;
				pos21 = (double)(((int)val21) * positionScale) / 8.0;
				fprintf(fd, "%lf; 0x%x; %lf; 0x%x; %lf; 0x%x; %lf; 0x%x \n", pos1, val1, pos11, val11, pos2, val2, pos21, val21);
				val1 = 0;
				val11 = 0;
				val2 = 0;
				val21 = 0;
				//don't miss the overflow case
			}
			//fprintf(fd, "-----------------------Page %u: End address 0x%p ------------------------ \n", i + 1, base_A24D32_axis1_ptr - 1);

		}
		break;
	}

	fclose(fd);
	return RET_SUCCESS;
}
int configureFifoFlyscan(SIS1100_Device_Struct* dev, unsigned char Axis, fifoParam *param, PUINT startAdresses){

	if (!(param->acqTime || param->freq) || !(param->nbrPts || param->freq) || !(param->nbrPts || param->acqTime)) {
		printf("At most one of the fifo parameters can be nulled\n");
		return RET_FAILED;
	}
	if (!(param->acqTime)) {
		// this mean acquisition time has not be given so we need to infer it from the 
		//other parameter
		param->acqTime = (UINT)(((double)(param->nbrPts)) / ((double)(param->freq)));
	}
	if (!(param->nbrPts)) {
		// this mean acquisition time has not be given so we need to infer it from the 
		//other parameter
		param->acqTime = (UINT)(((double)(param->acqTime)) * ((double)(param->freq)));
	}
	if (!(param->freq)) {
		// this mean acquisition time has not be given so we need to infer it from the 
		//other parameter
		param->acqTime = (UINT)(((double)(param->nbrPts)) / ((double)(param->acqTime)));
	}
	printf("FIFO Flyscan configuration: Freq: %u \t Nbr_of_points: %u \t acquisition_time: %u \n", param->freq, param->nbrPts, param->acqTime);
	if (fifoFlyscan(dev, Axis, *param, startAdresses) != RET_SUCCESS) {
		printf("FIFO flyscan configuration failed\n");
		return RET_FAILED;
	}
	return RET_SUCCESS;
}
int fifoFlyscan(SIS1100_Device_Struct* dev, unsigned char axis, fifoParam param, PUINT startAdress) {

	UINT uint_vme_data = 0, uint_vme_address = 0, len=0, pos = 0;
	len = 1;
	printf("setting up FIFO flyscan...\n");
	if ( !startAdress)	return	RET_FAILED;
	/*/
	if (strlen(axis) != strlen(startAdresses)) {
		printf("number of axis should match the number of start addresses\n");
		return	RET_FAILED;
	}
	*/
	for (UINT i = 0; i < len; i++) {
		if (checkValues(i, 0, 4)) {
			printf("bad axis number\n");
			return RET_FAILED;
		}
	}
	//1- Disable SCLK Timer
	DisableSampleTimer(dev);
	//2- Reset all axis and wait for reset to complete
	for (UINT i = 0; i < len; i++) {
		if (ResetAxis(dev, axis)) {
			return RET_FAILED;
		}
	}
	// 3- enable sampling timer
	enableSampling(dev, (param.freq)*1e-6);//convert to MHz
	// 4- check if new data is avalaible and Read FIFO position
	for (UINT i = 0; i < (param.nbrPts); i++) {
		while (!(isFifoDavbitSet(dev, AXIS3)));
		for (UINT j = 0; j < len; j++) {
			ReadFIFOPosition(dev, axis, &pos);
			*startAdress++ = pos;
		}
	}
	// 5-disable sclk timer
	DisableSampleTimer(dev);
	//6-verify the FIFO overflow bit
	for (UINT i = 0; i < len; i++) {
		if (isFifoOVFbitSet(dev, axis)) {
			printf("WARNING: some data samples have been missed on axis %d. The frequency must be decreased\n", axis);
		}
	}
	return RET_SUCCESS;
}
bool isFifoDavbitSet(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	if ((uint_vme_data & 0x400))
		return true;
	return false;
}
bool isFifoOVFbitSet(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	if ((uint_vme_data & 0x200))
		return true;
	return false;
}
/// <summary>
/// This function configures the Flyscan mode to continuously acquire position data from all 4 axes
/// 
/// </summary>
/// <param name="dev"> device to be used</param>
/// <param name="nbrAxis">number of axis. If nbrAxis is 2, make sure you're using one of 
/// the following couple for measurements: (axis1, axis3) or (axis2, axis4) </param>
/// <param name="freqMHz">
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
int configureFlyscan(SIS1100_Device_Struct* dev, unsigned char nbrAxis, double freqMHz, UCHAR trig) {
	/*'
		'4 X 8kSamples of 32 bit position values at FULL resolution of lambda/4096/8
		' returns false if unsuccessful
		' sample freq in mHz 10MHZ is max
		' trigger type: instant = 0
		'               P2D_In = 1*/
	short rdVal = 0, sclkVal = 0;
	UINT ctr=0;
	UINT uint_vme_data = 0, uint_vme_address = 0;
	int ramAxisAddr = 0x0;

	/* Check if RAM is busy*/
	printf("setting up flyscan...\n");
	if (checkValues(nbrAxis, 0, 4)) {
		return RET_FAILED;
	}
	do {
		ctr++;
		if (ctr > 1500)
		{
			printf("\nRAM has been busy for more than %d stamps time \n exiting... \n\n", ctr);
			return RET_FAILED;
		}
	} while (isRAMbusy(dev));

	enableSampling(dev, freqMHz);
	if (nbrAxis <= 2)
		uint_vme_data = 0x8000;
	else
		uint_vme_data = 0x9000;
	//Setup axis 1 and 2
	switch (nbrAxis)
	{
	case 1:
		uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zDiagFFTCtrl);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
		}
		break;
	default:
		uint_vme_address = ADD(BASE_ADDRESS[AXIS1 - 1], zDiagFFTCtrl);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
		}
		//Setup axis 3 and 4
		uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zDiagFFTCtrl);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
		}

		break;
	}

	//Option to start acquire immediately
	if (trig) {
		if (startAquisition(dev, nbrAxis) != RET_SUCCESS)
			return RET_FAILED;
		printf("Starting acquisition...\n");
	}
	return RET_SUCCESS;
}
/// <summary>
/// Start acquisition
/// </summary>
/// <param name="dev"></param>
/// <param name="nbrAxis"></param>
/// <returns></returns>
int startAquisition(SIS1100_Device_Struct* dev, unsigned char nbrAxis) {
	UINT uint_vme_data = 0x8, uint_vme_address = 0;

	//Start acquisition on axis 1

	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestCmd1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	if (nbrAxis >= 2) {
		//Start acquisition on axis 3
		uint_vme_address = ADD(BASE_ADDRESS[AXIS1 - 1], zTestCmd1);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
		}
	}
	return RET_SUCCESS;
}

int stopAquisition(SIS1100_Device_Struct* dev, unsigned char nbrAxis) {
	UINT uint_vme_data = 0x10, uint_vme_address = 0;

	//Start acquisition on axis 1 

	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestCmd1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	if (nbrAxis >= 2) {
		//Start acquisition on axis 3 
		uint_vme_address = ADD(BASE_ADDRESS[AXIS1 - 1], zTestCmd1);
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
		}
	}
	return RET_SUCCESS;
}
/// <summary>
/// The function allocate the specified memory space on Windows
/// </summary>
/// <param name="mem_size"> the size in bytes(max val is 10240)</param>
/// <returns>
/// -1 if unsuccessful
/// 0 else
/// </returns>
PUINT allocateMemSpace(UINT mem_size) {

	if (checkValues(mem_size, 0, 1024*70))
		return NULL;
	return (PUINT)calloc((UINT)(mem_size), sizeof(unsigned int));

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
int readModifyWrite(char* accessMode, SIS1100_Device_Struct* dev, unsigned int uint_vme_address, 
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
/// The function fetchs the flyscan configuration of each axis and thereafter get measured positions from the RAM
/// based on the read configuration. 
/// if an axis is not properly configured for flyscan operation, the function won't acquire data from 
/// that axis and the user will be notified.
/// </summary>
/// <param name="dev"> device</param>
/// <param name="startAdress_axis1">
/// a pointer to the location to store axis 1 and 2 measured position
/// </param>
/// <param name="startAdress_axis3">
/// a pointer to the location to store axis 3 and 4 measured position
/// </param>
/// <param name="nbrFlyscanAxis">
/// this is a value-return argument. It contains the number of axis which has been
/// indicated properly configured by the function. based on this value, the user can
/// infer the number of sample data which has been acquired and therefore assert whether or
/// all axis have been properly configured.
/// </param>
/// <returns>
/// 0 if success
/// -1 if failed
/// </returns>
int getFlyscanData(SIS1100_Device_Struct* dev,PUINT startAddress_axis1, PUINT startAddress_axis3, PUINT nbrFlyscanAxis){
#define NBR_RAM_PAGES			64
#define NBR_SAMP_PER_PAGE		512

	UINT uint_vme_address = 0, nbr_of_read = 0, ctr1[2] = { 0,0 }, ctr = 0, nbrAxis = 0;
	UINT ramPageAddr = 0;
	PUINT startAddress = 0;
	//get the value of Diag FFT RAM configuration register
	// Here we need only to know whether the user is going to make measurement on 
	// more than 2 axis or not, so 2 is our threshold
	uint_vme_address = ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS3 - 1]);
	for (int k = 0; k < 2; k++) {
		if (Read_Write("A24D16", dev, uint_vme_address, &ramPageAddr, 0) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address);
			return RET_FAILED;
		}
		if ((ramPageAddr & 0x9000) != 0x8000) { // check the 15th and the 12th bits of the loaded value
			if ((ramPageAddr & 0x9000) != 0x9000) {
				if (ctr < 1) {// to take into account the 2 cycles
					printf("Flyscan is not properly configured. RAM FFT Ctrl value is 0x%X\n", ramPageAddr);
					printf("Note the main axis is axis 3. If you're setting up flyscan for measurement only on 1 axis, you should configure it on the main axis \n");
					return RET_FAILED;
				}
			}
			else { 
				ctr+=2;
				ctr1[k] = (ramPageAddr & 0x9000);
			}
		}
		else {
			ctr++;
			ctr1[k] = (ramPageAddr & 0x8000);
		}
		
		uint_vme_address = ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS1 - 1]);
		ramPageAddr = 0;
	}
	*nbrFlyscanAxis = ctr;

	if (ctr > 1) {
		if ((!startAddress_axis1) || (!startAddress_axis3)) {
			printf("Bad arguments serve to %s. The current configuration does not allow any of the pointer passed as argument to be null\n", __FUNCTION__);
			return RET_FAILED;
		}
		nbrAxis = 2;
	}
	else{
		if ((!startAddress_axis3)) {
			printf("Bad arguments serve to %s. Axis 3 is the main axis.The corresponding argumentis not allowed to be null\n", __FUNCTION__);
			return RET_FAILED;
		}
		nbrAxis = 1;
	}
	printf("Starting acquisition on %d axis \n", ctr);
	if (startAquisition(dev, 1) != RET_SUCCESS)
		return RET_FAILED;

	do{
		ctr++;
		Sleep(1);
		if (ctr > 15000)
		{
			printf("RAM has been busy for more than %ds stamps time \n eiting... \n", ctr);
			return RET_FAILED;
		}
	} while (isRAMbusy(dev));

	uint_vme_address = ADD(zDiagFFTRamData, BASE_ADDRESS[AXIS3-1]);
	ramPageAddr = ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS3 - 1]);
	startAddress = startAddress_axis3;
	ctr = ctr1[0];
	for (UINT k = 0; k < nbrAxis; k++) {
		for (int i = 0; i < 64; i++) {
			printf("-----------------------Page %u: Start address 0x%p ------------------------ \n", i + 1, startAddress);
			if (vme_A24DMA_D32_read(dev, uint_vme_address, startAddress, NBR_SAMP_PER_PAGE / 2, &nbr_of_read) != RET_SUCCESS)
			{
				printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
			}
			else printf("%d 32bits words read from 0x%x  \n", nbr_of_read, uint_vme_address);
			//request the next page
			if (Read_Write("A24D16", dev, ramPageAddr, &ctr, 1) != RET_SUCCESS)
			{
				printf("Register %6X access Faillure !  \n", uint_vme_address);
				return RET_FAILED;
			}
			// Shift to the next page
			startAddress += nbr_of_read;
			ctr++;
			printf("-----------------------Page %u: End address 0x%p ------------------------ \n", i + 1, startAddress - 1);
			nbr_of_read = 0;
		}
		startAddress = startAddress_axis1;
		uint_vme_address = ADD(zDiagFFTRamData, BASE_ADDRESS[AXIS1 - 1]);
		ramPageAddr = ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS1 - 1]);
		ctr = ctr1[1];
	}
	
	return RET_SUCCESS;
}
/// <summary>
/// This function checks whether the RAM is busy or not.
/// </summary>
/// <param name="dev"> device</param>
/// <returns>
/// TRUE if RAM is busy
/// FALSE else
/// </returns>
BOOL isRAMbusy(SIS1100_Device_Struct*  dev) {
	UINT uint_vme_data = 0, uint_vme_address = 0;
	/* Check if RAM is busy*/
	uint_vme_address = BASE_ADDRESS[AXIS3-1] + zTestStat1;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address);
		return TRUE;
	}

	if ((uint_vme_data & 0x400)) {
		printf("RAM is currently busy\n");
		return TRUE;
	}
	return FALSE;
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
int setVMEIntVector(SIS1100_Device_Struct* dev, unsigned char axis, unsigned char IntVect) {
	unsigned int uint_vme_address = 0;
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
		printf("Error in file %s:function %s:line%d", __FILE__, __FUNCTION__,__LINE__);
		printf("\tBad Value\n");
		printf("\tthe range allowed is %d to %d\n", minVal, maxVal);
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
int setVMEIntLevel(SIS1100_Device_Struct* dev, unsigned char axis, unsigned char IntLevel) {
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
int DisableGlobalInterrupt(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int EnableVMEInterrupt_bit(SIS1100_Device_Struct* dev, unsigned char axis, unsigned short intNumber){
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	if (checkValues(intNumber, MIN_INT_NBR, MAX_INT_NBR) < 0)
		return RET_FAILED;
	if (intNumber < VME_EXT_FLAG_SAMPLE_ERR_INT)
	{
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEIntEnab0);				
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int DisableVMEInterrupt_bit(SIS1100_Device_Struct* dev, unsigned char axis, unsigned short intNumber) {
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
int ResetAxis(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data =0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	uint_vme_data = 0x20;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{
		printf("Register %6X access Faillure !  \n", uint_vme_address);
	return RET_FAILED;
	}
	if (WaitResetComplete(dev, axis) < 0)	// Wait for reset complete on the main axis
		return RET_FAILED;
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
int WaitResetComplete(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int Init_SIS_boards(SIS1100_Device_Struct* dev) {

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
int Init_ZMI_bd(SIS1100_Device_Struct* dev) {
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
		if (EEPROMread(dev, i, &uint_vme_data, 2) != RET_SUCCESS)
			printf("EEPROM Offset %d access Faillure !  \n", i);
		uint_vme_data_buf[i] = uint_vme_data;
	}

	printf("\tBoard data version format: %u \n", uint_vme_data_buf[0]);
	printf("\tSize of Board Data Block: %u \n", uint_vme_data_buf[1]);
	printf("\tDate of manufacture: %u/%u/%u \n", uint_vme_data_buf[2], uint_vme_data_buf[3], uint_vme_data_buf[4]);
	printf("\tBoard Assy Number: (%u, %u) \n", uint_vme_data_buf[5],uint_vme_data_buf[6]);
	printf("\tBoard Configuration: %u \n", uint_vme_data_buf[7]);
	printf("\tOriginal Board Revision: %u \n", uint_vme_data_buf[8]);
	printf("\tReworked Board Revision: %u \n", uint_vme_data_buf[9]);
	printf("\tNumber of axes: %u \n", uint_vme_data_buf[15]);
	printf("\tVendor code: %u \n", uint_vme_data_buf[18]);
	printf("\tBoard serial Number: %u:%u:%u:%u:%u \n", uint_vme_data_buf[10], \
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
int SetPositionOffset32(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int offsetPos) {
	unsigned int uint_vme_address = 0, uint_vme_data;

	uint_vme_data = offsetPos;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zOffsetMSB);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// This function enable the C0 and CN compensation
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int EnableCECcompensation(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCECCtl);
	uint_vme_data = 0x3;// C0 and CN compensation
	printf("Enabling CE compensation...\n");
	EnableAuxRegisters(dev, 3);
	if (readModifyWrite("A24D16", dev, uint_vme_address, uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("readWriteModify failed!!!!!!\n"); 
		printf("Enabling CE compensation failed\n");
		return RET_FAILED;
	}
	DisableAuxRegisters(dev, 3);
	printf("Enabling CE compensation success\n");
	return RET_SUCCESS;
}
/// <summary>
/// This function disable the C0 and CN compensation
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int disableCECcompensation(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCECCtl);
	uint_vme_data = 0xFFFC;// C0 and CN compensation

	EnableAuxRegisters(dev, 3);
	if (readModifyWrite("A24D16", dev, uint_vme_address, uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("readWriteModify failed!!!!!!\n"); return RET_FAILED;
	}
	DisableAuxRegisters(dev, 3);
	return RET_SUCCESS;
}
/// <summary>
/// This function selects the use of user supplied coefficients C0, C1 and CN.
///  Prior to the use of this function you should set C0, C1 and CN user coeffs.
/// It's recommended those coefficients to be loaded using respectively calculated C0, C1 and CN coeffs.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int useCEUserSuppliedCoeff(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCECCtl);
	uint_vme_data = 0x1C;// C0 and CN compensation
	EnableAuxRegisters(dev, 3);
	if (readModifyWrite("A24D16", dev, uint_vme_address, uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("readWriteModify failed!!!!!!\n"); return RET_FAILED;
	}
	DisableAuxRegisters(dev, 3);
	return RET_SUCCESS;
}
/// <summary>
/// This function enable the use of user supplied coefficients C0, C1 and CN only at the startup or
/// after an axis reset.
/// Those coeffs should be primarily set by the user.
/// It's recommended those coefficients to be loaded using respectively calculated C0, C1 and CN coeffs.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int useCEUserSupplyCoeffAtStartup(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCECCtl);
	uint_vme_data = 0x40;
	EnableAuxRegisters(dev, 3);
	if (readModifyWrite("A24D16", dev, uint_vme_address, uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("readWriteModify failed!!!!!!\n"); return RET_FAILED;
	}
	DisableAuxRegisters(dev, 3);
	return RET_SUCCESS;
}
/// <summary>
/// This function resets CEC errors
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ResetCECerrors(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCEcmd);
	uint_vme_data = 0x1;
	EnableAuxRegisters(dev, 3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	DisableAuxRegisters(dev, 3);
	return RET_SUCCESS;
}
/// <summary>
/// This function check whether  the initialization of the Cyclic Error coefficients is 
///complete.This occurs after an axis reset and a  Motion at a velocity where Cyclic Error coefficients are calculated.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int waitCEinit2Complete(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0,ct=0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCEstat);
	uint_vme_data = 0;
	EnableAuxRegisters(dev, 3);
	while (!(uint_vme_data & 0x20)) {
		printf("Initializing CE coefficients...\n");
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
		}
		Sleep(1);// sleep for 1ms
		ct++;
		if (ct > 3000) {
			printf("Any motion has been detected for more than 30 secs\n");
			printf("CEC hardware initialization has failed \n");
			return RET_FAILED;
		}
	}
	DisableAuxRegisters(dev, 3);
	if (ct < 3000) {
		printf("CEC hardware initialization success \n");
	}
	return RET_SUCCESS;
}
/// <summary>
/// This function sets This specifies the maximum velocity where CEC will be applied. The units of this register are 
///76.3 Hz, or 12 μm / sec for a double - pass interferometer.The default value is 0x7ae1 (31457),
///which corresponds to 2.4 MHz or 380 mm / s.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="CEMaxVelValue"></param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetCEMaxVel(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int CEMaxVelValue) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCEMaxVel);
	uint_vme_data = CEMaxVelValue;
	EnableAuxRegisters(dev, 3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	DisableAuxRegisters(dev, 3);
	return RET_SUCCESS;
}
/// <summary>
/// This function sets the minimum velocity where CEC will be applied. The units of this register are 
///76.3 Hz, or 12 μm / sec for a double - pass interferometer.The default value is 0x0060 (96), which
///corresponds to 7.3 kHz or 1.2 mm / s.Settings lower than this value may adversely affect CE
///functionality
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="CEMinVelValue"></param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int SetCEMinVel(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int CEMinVelValue) {
	unsigned int uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCEMinVel);
	uint_vme_data = CEMinVelValue;
	EnableAuxRegisters(dev, 3);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	DisableAuxRegisters(dev, 3);
	return RET_SUCCESS;
}
/// <summary>
/// The function gets the CE coeffs that have been calculated by the Zygo integrated microcontroler
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="coeffs">This is a value return argument and will contain the read coeffs in
/// the following order C0 -> C1 -> CN</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int readCalcCECoeffs(SIS1100_Device_Struct* dev, unsigned char axis,CECoeffs* CECalcCoeffs) {
	unsigned int uint_vme_address = 0, uint_vme_data=0;
	if (!CECalcCoeffs) {
		printf("None of the pointer passed as argument should be NULL\n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCEC0CalcCoeff);

	EnableAuxRegisters(dev, 3);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	// CE0 val is stored in zygo register as a complex Int16 value so we should 
	// convert it to a complex number
	convertCInt162Complex(uint_vme_data, &(CECalcCoeffs->CEC0coeff));  //coeffs[0] = uint_vme_data;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCEC1CalcCoeff);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	// CE1 val is stored in zygo register as a float value so we should 
// convert it to double
	convertFloat2Double(uint_vme_data, &(CECalcCoeffs->CEC1coeff));// coeffs[1] = uint_vme_data;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCECNCalcCoeff);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	DisableAuxRegisters(dev, 3);
	// CEN val is stored in zygo register as a complex float value so we should 
// convert it to a complex number
	convertCFloat2Complex(uint_vme_data, &(CECalcCoeffs->CECNcoeff));//coeffs[2] = uint_vme_data;
	return RET_SUCCESS;
}
/// <summary>
/// The function gets the CE coeffs that have been calculated by the Zygo integrated microcontroler
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="coeffs">This is a value return argument and will contain the read coeffs in
/// the following order C0 -> C1 -> CN</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int readCECoeffboundaries(SIS1100_Device_Struct* dev, unsigned char axis, CECoeffBoundaries* CE0CoeffBound, CECoeffBoundaries* CENCoeffBound) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	USHORT tmp1 = 0, tmp2 = 0;
	if (!CE0CoeffBound || !CENCoeffBound) {
		printf("None of the pointer passed as argument should be NULL\n");
		return RET_FAILED;
	}

	EnableAuxRegisters(dev, 3);
	for (int i = 0; i < 2; i++) {
		// Read CE mag coefficient
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], (i==0 ? zCE0Mag: zCENMag));
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
		}
		// CE Mag val is stored in zygo register as an unsigned short value so we should 
		// convert it to a real number
		convertUSFloat2Double(uint_vme_data, (i == 0 ? &(CE0CoeffBound->CEMagcoeff) : &(CENCoeffBound->CEMagcoeff)));

		printf("CE0 mag Bare val 0x%X, CE mag %f \n", uint_vme_data, (i == 0 ? (CE0CoeffBound->CEMagcoeff) : (CENCoeffBound->CEMagcoeff)));
		// Read CE min and max coefficients
		uint_vme_address = ADD(BASE_ADDRESS[axis - 1], (i == 0 ? zCE0Min : zCENMin));
		uint_vme_data = 0;
		if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{
			printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
		}
		//split data to get CE min and CE max value
		tmp1 = uint_vme_data & 0xFFFF; // CE Min
		tmp2 = (uint_vme_data >> 16) & 0xFFFF; //  CE max
		// CE1 val is stored in zygo register as a float value so we should 
	// convert it to double
		convertUSFloat2Double(tmp1, (i==0? &(CE0CoeffBound->CEMincoeff): &(CENCoeffBound->CEMincoeff)));
		convertUSFloat2Double(tmp2, (i==0? &(CE0CoeffBound->CEMaxcoeff): &(CENCoeffBound->CEMaxcoeff)));
		uint_vme_data = 0;
	}
	DisableAuxRegisters(dev, 3);
	return RET_SUCCESS;
}
/// <summary>
/// The function use CE coeffs that have been calculated by the Zygo integrated microcontroler to determine
/// CE Ratios.
/// /// </summary>
/// <param name="dev">device</param>
/// <param name="axis">axis number</param>
/// <param name="ceRatios">stores CE ratios</param>
/// <param name="units">ratio units(%,dB,nm RMS) to use</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int calculateCEratio(SIS1100_Device_Struct* dev, unsigned char axis, CEratios* ceRatios, CEratioUnits units){
	CECoeffs ceCoeffs;
	CEratios ceRatiotmp;
	double temp;
	if (readCalcCECoeffs(dev, axis, &ceCoeffs) != RET_SUCCESS)
		RET_FAILED;
	if (!(temp = sqrt(ceCoeffs.CEC1coeff))) {
		printf("Can not perform CEC ratios calculation, Measurement signal value is 0\n");
		goto exit_flag;
	}
	ceRatiotmp.measSignal = temp;
	ceRatiotmp.CE0ratio = sqrt(pow(ceCoeffs.CEC0coeff.rpart, 2) + pow(ceCoeffs.CEC0coeff.ipart, 2)) / temp;
	ceRatiotmp.CENratio = sqrt(pow(ceCoeffs.CECNcoeff.rpart, 2) + pow(ceCoeffs.CECNcoeff.ipart, 2)) / pow(temp,2);
	ceRatios->measSignal = temp;
	switch (units)
	{
	case ratio_in_dB:
		//ceRatios->measSignal = 20 * log10(ceRatiotmp.measSignal);
		ceRatios->CE0ratio= 20 * log10(ceRatiotmp.CE0ratio);
		ceRatios->CENratio = 20 * log10(ceRatiotmp.CENratio);
		break;
	case ratio_in_percent:
		//ceRatios->measSignal = 100*ceRatiotmp.measSignal;
		ceRatios->CE0ratio = 100 * ceRatiotmp.CE0ratio;
		ceRatios->CENratio = 100 * ceRatiotmp.CENratio;
		break;
	case ratio_in_nmRMS:
		//ceRatios->measSignal =  ceRatiotmp.measSignal *(1/(2*PI))*(LAMBDA/(2*(double)(curInterferoConfig)))* 0.70710678118654;
		ceRatios->CE0ratio = ceRatiotmp.CE0ratio * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		ceRatios->CENratio = ceRatiotmp.CENratio * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		break;
	default:
		break;
	}
exit_flag: 
	return RET_SUCCESS;
}
/// <summary>
/// The function use an approximation to calculate the cyclic error percentage.Due to the approximation used, these values may
///differ from values calculated from the coefficient calculated by calculateCEratio() by approximately 10 %, depending on the phase of the coefficient.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">axis number</param>
/// <param name="ceRatios">stores CE ratios</param>
/// <param name="units">ratio units(%,dB,nm RMS) to use</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getAproximateCEratio(SIS1100_Device_Struct* dev, unsigned char axis, CEratios* ceRatios, CEratioUnits units) {
	CECoeffs ceCoeffs;
	CECoeffBoundaries CE0bound = { 0,0,0 }, CENbound = { 0,0,0 };
	double tmp;
	if (readCalcCECoeffs(dev, axis, &ceCoeffs) != RET_SUCCESS)
		RET_FAILED;
	if (readCECoeffboundaries(dev, axis, &CE0bound, &CENbound) != RET_SUCCESS)
		RET_FAILED;
	tmp = sqrt(ceCoeffs.CEC1coeff);
	switch (units)
	{
	case ratio_in_dB:
		ceRatios->CE0ratio = 20 * log10(CE0bound.CEMagcoeff);
		ceRatios->CENratio = 20 * log10(CENbound.CEMagcoeff);
		break;
	case ratio_in_percent:
		ceRatios->CE0ratio = 100 * ((double)(CE0bound.CEMagcoeff)) / tmp;
		ceRatios->CENratio = 100 * ((double)(CENbound.CEMagcoeff));
		printf("CE0 mag %f, CEN mag %f \n", CE0bound.CEMagcoeff, CENbound.CEMagcoeff);
		break;
	case ratio_in_nmRMS:
		ceRatios->CE0ratio = CE0bound.CEMagcoeff * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		ceRatios->CENratio = CENbound.CEMagcoeff * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		break;
	default:
		break;
	}
	return RET_SUCCESS;
}

/// <summary>
/// This function gets the CE limits the CE values that will result in a corresponding CE Max Limit 0 or CE Max Limit N error indication in the CE Error
///Status register
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">axis number</param>
/// <param name="ceRatios">stores CE ratios limits</param>
/// <param name="units">ratio units(%,dB,nm RMS) to use</param>
/// <param name="units"></param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getCERatioLimits(SIS1100_Device_Struct* dev, unsigned char axis, CEratios* ceRatioLimits, CEratioUnits units) {
	CECoeffs ceCoeffs;
	CEratios ceRatiotmp;
	CECoeffBoundaries CE0bound = { 0.0,0.0,0.0 }, CENbound = { 0.0,0.0,0.0 };
	double tmp;
	if (readCalcCECoeffs(dev, axis, &ceCoeffs) != RET_SUCCESS)
		RET_FAILED;
	if (calculateCEratio(dev, axis, &ceRatiotmp, units) != RET_SUCCESS)
		RET_FAILED;
	tmp = sqrt(ceCoeffs.CEC1coeff);

	ceRatioLimits->CE0ratio = tmp * (ceRatiotmp.CE0ratio) / 100;
	ceRatioLimits->CENratio = (ceRatiotmp.CE0ratio) / 100;

	return RET_SUCCESS;
}
/// <summary>
/// The function give an approximation of the minimum and maximum values reach by the CE 
/// ratios since the card has been powered up.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">axis number</param>
/// <param name="ceRatios">stores CE ratios boundaries</param>
/// <param name="units">ratio units(%,dB,nm RMS) to use</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getAproximateCEratioBoundaries(SIS1100_Device_Struct* dev, unsigned char axis, 
	CEratiosBoundaries* ce0RatiosBoundaries, CEratiosBoundaries* ceNRatiosBoundaries,CEratioUnits units) {
	CECoeffs ceCoeffs = { 0.0,0.0,0.0 };
	CECoeffBoundaries CE0bound = {0.0,0.0,0.0}, CENbound={ 0.0,0.0,0.0 };
	double tmp;
	if (readCalcCECoeffs(dev, axis, &ceCoeffs) != RET_SUCCESS)
		RET_FAILED;
	if (readCECoeffboundaries(dev, axis, &CE0bound, &CENbound) != RET_SUCCESS)
		RET_FAILED;
	tmp = sqrt(ceCoeffs.CEC1coeff);
	switch (units)
	{
	case ratio_in_dB:
		ce0RatiosBoundaries->CEMinratio = 20 * log10(((double)CE0bound.CEMincoeff)) / tmp;
		ce0RatiosBoundaries->CEMaxratio = 20 * log10(((double)CE0bound.CEMaxcoeff)) / tmp;

		ceNRatiosBoundaries->CEMinratio = 20 * log10(((double)CENbound.CEMincoeff));
		ceNRatiosBoundaries->CEMaxratio = 20 * log10(((double)CENbound.CEMaxcoeff));
		break;
	case ratio_in_percent:
		ce0RatiosBoundaries->CEMinratio = 100 * ((double)(CE0bound.CEMincoeff)) / tmp;
		ce0RatiosBoundaries->CEMaxratio = 100 * ((double)(CE0bound.CEMaxcoeff)) / tmp;

		ceNRatiosBoundaries->CEMinratio = 100 * ((double)(CENbound.CEMincoeff));
		ceNRatiosBoundaries->CEMaxratio = 100 * ((double)(CENbound.CEMaxcoeff));
		break;
	case ratio_in_nmRMS:
		ce0RatiosBoundaries->CEMinratio = CE0bound.CEMincoeff * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		ce0RatiosBoundaries->CEMaxratio = CE0bound.CEMaxcoeff * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;

		ceNRatiosBoundaries->CEMinratio = CENbound.CEMincoeff * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		ceNRatiosBoundaries->CEMaxratio = CENbound.CEMaxcoeff * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		break;
	default:
		break;
	}
	return RET_SUCCESS;
}

/// <summary>
/// The function gets minimum and maximum value the CEMag register has reached since the card has been powered up.
/// The CEMag register contains an approximation of the CE ratio in percentage 
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">axis number</param>
/// <param name="ce0RatiosBoundaries">Stores the CE0boundaries ratios(CE0min and CE0max)</param>
/// <param name="ceNRatiosBoundaries">Stores the CE0boundaries ratios(CENmin and CENmax)</param>
/// <param name="units">ratio units to use (%,dB,nm RMS)</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getCERatioboundaries(SIS1100_Device_Struct* dev, unsigned char axis, CEratios* ceRatios, CEratioUnits units) {
	CECoeffs ceCoeffs;
	CEratios ceRatiotmp;
	double temp;
	if(readCalcCECoeffs(dev, axis, &ceCoeffs) != RET_SUCCESS)
		RET_FAILED;
	temp = sqrt(ceCoeffs.CEC1coeff);
	ceRatiotmp.measSignal = temp;
	ceRatiotmp.CE0ratio = (sqrt(pow(ceCoeffs.CEC0coeff.rpart, 2) + pow(ceCoeffs.CEC0coeff.ipart, 2))) / temp;
	ceRatiotmp.CENratio = (sqrt(pow(ceCoeffs.CECNcoeff.rpart, 2) + pow(ceCoeffs.CECNcoeff.ipart, 2))) / pow(temp, 2);
	switch (units)
	{
	case ratio_in_dB:
		ceRatios->measSignal = 20 * log10(ceRatiotmp.measSignal);
		ceRatios->CE0ratio = 20 * log10(ceRatiotmp.CE0ratio);
		ceRatios->CENratio = 20 * log10(ceRatiotmp.CENratio);
		break;
	case ratio_in_percent:
		ceRatios->measSignal = 100 * ceRatiotmp.measSignal;
		ceRatios->CE0ratio = 100 * ceRatiotmp.CE0ratio;
		ceRatios->CENratio = 100 * ceRatiotmp.CENratio;
		break;
	case ratio_in_nmRMS:
		ceRatios->measSignal = ceRatiotmp.measSignal * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		ceRatios->CE0ratio = ceRatiotmp.CE0ratio * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		ceRatios->CENratio = ceRatiotmp.CENratio * (1 / (2 * PI)) * (LAMBDA / (2 * (double)(curInterferoConfig))) * 0.70710678118654;
		break;
	default:
		break;
	}
	return RET_SUCCESS;
}
/// <summary>
/// this function convert an unsigned integer value from a zygo register to a complex value
/// </summary>
/// <param name="nbr">register value</param>
/// <param name=" val">a complex variable to store the converted value in</param>
/// <returns></returns>
int convertCInt162Complex(UINT nbr, complex* val) {

	val->ipart = (double)((short)(nbr & 0xFFFF));
	val->rpart = (double)((short)(nbr & 0xFFFF0000) >> 16);
	return RET_SUCCESS;
}
/// <summary>
/// This function convert a complex value to an unsigned int value to be loaded in
/// a zygo register
/// </summary>
/// <param name="nbr">the complex number </param>
/// <param name="val"> a pointer on a variable to store the result</param>
/// <returns> 0 </returns>
int convertComplex2Uint(complex nbr, PUINT val) {
	*val = (((UINT)(nbr.rpart) & 0xFFFF) << 16) | (UINT)(nbr.ipart) & (UINT)0xFFFF;
	return RET_SUCCESS;
}
/// <summary>
/// The function convert a given a complex float number to a complex number
/// </summary>
/// <param name="cfloatNbr">the complex float value</param>
/// <param name="complexVal"> the complex pointer to store the result</param>
/// <returns>0 </returns>
int convertCFloat2Complex(UINT cfloatNbr, complex* complexVal) {
	UINT rpart = 0, ipart = 0;
	USHORT exp = 0, Rsign = 0, Isign = 0, Imant = 0, Rmant = 0,temp=0;
	temp = (cfloatNbr & 0xFF000000) >> 23;
	Rsign = temp & 0x1;
	exp = temp >> 1;
	Imant = cfloatNbr & 0x7FF;
	temp = ((cfloatNbr >> 11) & 0xFFF);
	Isign = temp & 0x1;
	Rmant= temp >> 1;
	complexVal->ipart = (1 - 2 *(double) Isign) * Imant * pow(2, (double)exp - 127 - 10);
	complexVal->rpart = (1 - 2 * (double)Rsign) * Rmant * pow(2, (double)exp - 127 - 10);
	return RET_SUCCESS;
}

/// <summary>
/// The function convert a given complex number to a complex float number 
/// </summary>
/// <param name="complexNbr"> the complex value </param>
/// <param name="cfloatVal">the complex float pointer to store the result </param>
/// <returns>0 </returns>
int convertComplex2CFloat(complex complexNbr, PUINT cfloatVal) {
	UINT rexp=0, iexp=0, exp=0;
	rexp= (UINT)floor(log2(complexNbr.rpart));
	iexp = (UINT)floor(log2(complexNbr.ipart));
	exp = max(rexp, iexp);
	*cfloatVal = (exp + 127) * 0x1000000 + (complexNbr.rpart < 0 ? 0x8000000 : 0)
		+ (UINT)(round(sqrt(pow(complexNbr.rpart, 2)) * pow(2, -(double)exp + 10))) * 0x1000
		+ (UINT)((complexNbr.ipart < 0 ? 0x800 : 0) + round(sqrt(pow((complexNbr.ipart),2)) * pow(2, -(double)exp + 10)));//use sqrt bcuz abs() does take only integer
	return RET_SUCCESS;
}
/// <summary>
/// The function convert a given float number to a real number 
/// </summary>
/// <param name="floatNbr"> the float value</param>
/// <param name="doubleVal">the real pointer to store the result</param>
/// <returns>0 </returns>
int convertFloat2Double(UINT floatNbr, double* doubleVal) {
	UINT sign=0, exp=0, mant=0, temp=0;
	temp = floatNbr & (UINT)0x1FFFFFF;
	sign = temp >> 24;
	exp = (temp >> 16) & (UINT)0xFF;
	mant = temp & (UINT)0xFFFF;
	*doubleVal = (1 - 2 * (double)sign) * (double)(mant + (UINT)0x10000) * pow(2, (double)exp - 127 - 16);
	return RET_SUCCESS;
}
/// <summary>
/// The function convert a given real number to a float number 
/// </summary>
/// <param name="doubleNbr"> the real value</param>
/// <param name="floatVal">the float pointer to store the result</param>
/// <returns>0 </returns>
int convertDouble2Float(double doubleNbr, PUINT floatVal) {
	USHORT exp = 0;
	exp = (USHORT)floor(log2(doubleNbr));
	*floatVal = (doubleNbr < 0 ? 0x1000000 : 0) + (exp + 127) * 0x10000 
		+ (UINT)(round(sqrt(pow(doubleNbr, 2)) * pow(2, 16 - (double)exp))) & 0xFFFF;//sqrt(pow(doubleNbr,2))=abs(doubleNbr)
	return RET_SUCCESS;
}
/// <summary>
/// The function convert a given unsigned short float number to a real number 
/// </summary>
/// <param name="USFloatNbr"> the unsigned short float value</param>
/// <param name="doubleVal">the real pointer to store the result</param>
/// <returns>0 </returns>
int convertUSFloat2Double(USHORT USFloatNbr, double* doubleVal) {
	USHORT exp=0, mant=0;
	exp = (USHORT)(USFloatNbr >> 8) & (USHORT)0xFF;
	mant = (USHORT)USFloatNbr & (USHORT)0xFF;
	*doubleVal = (double)(mant + (USHORT)0x100) * pow(2, (double)exp - 127 - 8);
	return RET_SUCCESS;
}

/// <summary>
/// The function convert a given real number to an unsigned short float number  
/// </summary>
/// <param name="doubleNbr"> the real value</param>
/// <param name="USFloatVal">the float pointer to store the result</param>
/// <returns>0 </returns>
int convertDouble2USFloat(double doubleNbr, PUSHORT USFloatVal) {
	USHORT exp = 0;
	exp = (USHORT)floor(log2(doubleNbr));
	*USFloatVal = (exp + 127)*0x100 + (UINT)(round((doubleNbr) *pow(2,8-(double)exp))) & 0x00FF;
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
int SetCompARegVal32(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int compAval32) {
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
int Enable37bitsSignExtension(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int Disable37bitsSignExtension(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int SetKpAndKvCoeff(SIS1100_Device_Struct* dev, unsigned char axis, unsigned short Kp, unsigned short Kv) {
	
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
int EnableGlitchFilter(SIS1100_Device_Struct* dev, unsigned char axis, unsigned short glitchFilterTime) {

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
int SetCompARegVal37(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int compAval32, unsigned int compAvalExt) {
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
int SetCompBRegVal32(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int compBval32) {
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
int SetCompBRegVal37(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int compBval32, unsigned int compBvalExt) {
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
int SetPositionOffset37(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int offsetPos32, unsigned int offsetPosExt) {
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
int SetPresetPosition32(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int presetPos) {
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
int SetPresetPosition37(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int presetPos32, unsigned int presetPosExt) {
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
int ReadVMEErrs(SIS1100_Device_Struct* dev, unsigned char axis) {
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
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int ReadAllErrs(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int ClearEEPROMErrs(SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zTestCmd1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data |= 0x4;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}


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
int BoardControlMode(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int biasMode) {
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
int BiasControlMode(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int mode) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	
	if (mode > 4)
	{
		printf("Unknow mode: mode is ranged 0 to 4 \n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl5);//rw
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_data &= ~(7);
	uint_vme_data |= mode;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int StartBiasCalculation(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	printf("Starting Bias calculation...\n");
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	uint_vme_data = (1<<6);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat2); 
	uint_vme_data = 0;
	while (!(uint_vme_data & (1 << 5)))
	{
		// wait for Bias calc complete to be asserted
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int SetAPDGainL2(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int APDGain) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	//APDGain: the default val is 7(2875 L2); range: 4(2048 L2) to 32(5120 L2)
	if (!checkValues(APDGain,0,0xFFFF))
		return RET_FAILED;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDGainL2Set);
	uint_vme_data = APDGain;
	EnableAuxRegisters(dev, axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int SetAPDSigRMSL2(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int APDSigRMSL2) {
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
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int SetAPDOptPwrL2(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int APDOptPwrL2) {
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
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int SetAPDBiasDAC(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int APDBiasDac) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	if (APDBiasDac > 0xFFFF)
	{
		printf("Inapropriate value. range is 0 to 0xFFFF \n");
		return RET_FAILED;
	}
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDBiasDAC);
	uint_vme_data = APDBiasDac;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int ParseVMEErrorStatus2(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* VMEErrorStatus2Reg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat2);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
int ParseVMEPosErrs(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* VMEPosErrReg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosErr);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="VMEErrorStatus1Reg">stores the contain of the register</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ParseVMEErrorStatus1(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* VMEErrorStatus1Reg) {
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
/// <summary>
/// The function reads and parses VME Error Status 0 register
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="VMEErrorStatus0Reg">stores the contain of the register</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ParseVMEErrorStatus0(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* VMEErrorStatus0Reg) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat0);		//Read VME errors
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
/// <summary>
/// the function parses errors related to the APD gain calculation on a specific axis.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDErrCode">stores the contain of the register</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ParseAPDErrCode(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* APDErrCode) {
	unsigned int uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zAPDErr);		//Read APD errors
	EnableAuxRegisters(dev, axis);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
/// <summary>
/// The function samples and reads the 37bits position value on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="position">stores the measured position</param>
/// <returns>
/// 0 if success | 
/// -1 else
/// </returns>
int ReadSamplePosition37(SIS1100_Device_Struct* dev, unsigned char axis, double* position) {
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
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
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
}
/// <summary>
/// The function samples and reads the 32bits position value on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="position">stores the measured position</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ReadSamplePosition32(SIS1100_Device_Struct* dev, unsigned char axis, double* position) {

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
}

/// <summary>
/// The function reads the 37bits position value on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="position">stores the measured position</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ReadPosition37(SIS1100_Device_Struct* dev, unsigned char axis, double* position) {
	int val = 0, temp32 = 0;
	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosMSB);
	printf("Reading Position on Axis %d...  \n", axis);
	Disable32bitsOverflow(dev, axis);
	Enable37bitsSignExtension(dev, axis);
	SampleVMEPosition(dev, axis);
	while (!GetVMEExtSampFlag(dev, axis)); // Wait for the VME external sample flag to be set before reading
	SetHoldSampEnable(dev); // lock values
	//clearVMEExtSampFlag(dev, axis); // Clear VME external sample flag before reading
	//Read the MSB and LSB	
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	val = (int)uint_vme_data;
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosExt);		//Read the Ext
	if (Read_Write("A24D8", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %06X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	ResetHoldSampEnable(dev);
	val = (int)((short)uint_vme_data);
	*position = ((double)(val)) * (2 ^ 32) + (double)((unsigned int)temp32) * positionScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Position on axis %d: %f mm \n", axis, *position);
	printf("-------------------------------------------------------\n");

	return RET_SUCCESS;
}
/// <summary>
/// The function reads the 32bits position value on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="position">stores the measured position</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ReadPosition32(SIS1100_Device_Struct* dev, unsigned char axis, double* position) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading Position on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEPosMSB);
	Enable32bitsOverflow(dev, axis);
	Disable37bitsSignExtension(dev, axis);
	//enableSampling(dev, 1);
	SampleVMEPosition(dev, axis);
	SetHoldSampEnable(dev); // value of the position register is held until its LSB is read 
	//clearVMEExtSampFlag(dev, axis); // Clear VME external sample flag before reading
	//Read the MSB and LSB	
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	ResetHoldSampEnable(dev);
	*position = (double)((int)uint_vme_data) * positionScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Position on axis %d: %f mm \n", axis, *position);
	printf("bare value is  0x%x \n", uint_vme_data);
	printf("-------------------------------------------------------\n");
	Disable32bitsOverflow(dev, axis);

	return RET_SUCCESS;
}
int ReadFIFOPosition(SIS1100_Device_Struct* dev, unsigned char axis, PUINT position) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading FIFO Position on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEFifoPos);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	*position = uint_vme_data;
	return RET_SUCCESS;
}
/// <summary>
/// The function reads the 32bits velocity value on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>velocity</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int ReadVelocity32(SIS1100_Device_Struct* dev, unsigned char axis, double* velocity) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;

	printf("Reading Velocity on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEVelocMSB);
	SampleVMEPosition(dev, axis); // the function both sample velocity and value
	//Read the MSB and LSB	
	SetHoldSampEnable(dev);
	if (Read_Write("A24D32", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	ResetHoldSampEnable(dev);
	*velocity = (double)((int)uint_vme_data) * velocityScale;
	printf("-------------------------------------------------------\n");
	printf("Measured Velocity on axis %d: %f mm/s \n", axis, *velocity);
	printf("-------------------------------------------------------\n");

	return RET_SUCCESS;
}
int ReadSamplePosition32_ForAllAxis(SIS1100_Device_Struct* dev, double* SamplePosition32_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadSamplePosition32(dev, i, &position);
		*(SamplePosition32_buf + i - 1) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
int ReadSamplePosition37_ForAllAxis(SIS1100_Device_Struct* dev, double* SamplePosition37_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadSamplePosition37(dev, i, &position);
		*(SamplePosition37_buf + i - 1) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
int ReadPosition32_ForAllAxis(SIS1100_Device_Struct* dev, double* Position32_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadPosition32(dev, i, &position);
		*(Position32_buf + i - 1) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
int ReadVelocity32_ForAllAxis(SIS1100_Device_Struct* dev, double* Velocity32_buf) {

	double Velocity = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadVelocity32(dev, i, &Velocity);
		*(Velocity32_buf + i - 1) = Velocity;
		Velocity = 0.0;
	}
	return RET_SUCCESS;
}
int ReadPosition37_ForAllAxis(SIS1100_Device_Struct* dev, double* Position37_buf) {

	double position = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadPosition37(dev, i, &position);
		*(Position37_buf + i - 1) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
bool IsVMEPos32Overflow(SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data & 0x0008))
		return true;
	return false;
}
bool IsVMEPos37Overflow(SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data & 0x0004))
		return true;
	return false;
}
bool IsUserVelError(SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data & 0x0002))
		return true;
	return false;
}
bool IsVelError(SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data & 0x0001))
		return true;
	return false;
}
bool IsAccError(SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat0);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if (uint_vme_data & 0x2000)
		return true;
	return false;
}
int ClearPosAndVelErrs(SIS1100_Device_Struct* dev, unsigned char axis) {

	unsigned int uint_vme_data = 0xF, uint_vme_address = 0;

	printf("Reseting Position and velocity errors on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrClr1);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	return RET_SUCCESS;
}
int ClearAllVMEErrs(SIS1100_Device_Struct* dev, unsigned char axis) {

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
int ClearPosAndVelErrs_ForAllAxis(SIS1100_Device_Struct* dev, unsigned char axis) {

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
int ClearAllVMEErrs_ForAllAxis(SIS1100_Device_Struct* dev) {

	for (int i = 1; i < 5; i++)
	{
		ClearAllVMEErrs(dev, i);
	}

	return RET_SUCCESS;
}
/*This fuction reads the ZMI "Time Register" on 32 bits
*/
int ReadTime32(SIS1100_Device_Struct* dev, unsigned char axis, double* time) {

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
int ReadTime32_ForAllAxis(SIS1100_Device_Struct* dev, double* Time32_buf) {

	double time = 0.0;
	for (int i = 1; i < 5; i++)
	{
		ReadTime32(dev, i, &time);
		*(Time32_buf + i - 1) = time;
		time = 0.0;
	}
	return RET_SUCCESS;
}
int ResetTime(SIS1100_Device_Struct* dev, unsigned char axis)
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
int ResetPositionQuick(SIS1100_Device_Struct* dev, unsigned char axis)
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
int ResetPosition(SIS1100_Device_Struct* dev, unsigned char axis)
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
int EnablePreset(SIS1100_Device_Struct* dev, unsigned char axis)
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
int EnableSCLKResetOnAxisReset(SIS1100_Device_Struct* dev, unsigned char axis)
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
int DisableSCLKResetOnAxisReset(SIS1100_Device_Struct* dev, unsigned char axis)
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
int EnableResetFindsVelocity(SIS1100_Device_Struct* dev, unsigned char axis)
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
int DisableResetFindsVelocity(SIS1100_Device_Struct* dev, unsigned char axis)
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
int SCLKSelectOnAxisReset(SIS1100_Device_Struct* dev, unsigned char axis, unsigned char SCLK)
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
int SetTimeDelayBetweenResAndCompleteBit(SIS1100_Device_Struct* dev, unsigned char axis, unsigned char timeDelay)
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
int ReadOpticalPowerUsingSSIav(SIS1100_Device_Struct* dev) {

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
int SetSSISquelch(SIS1100_Device_Struct* dev, unsigned short axis, int squelchValue ) {

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
int GetSSIMaxVal(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int* SSIMax)
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
int GetSSIMaxVal_ForAllAxis(SIS1100_Device_Struct* dev, unsigned int* SSIMax_Buf)
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
int ResetSSIMinAndMax(SIS1100_Device_Struct* dev, unsigned char axis)
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
int ResetPhaseNoisePeak(SIS1100_Device_Struct* dev, unsigned char axis)
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
int ResetSigRMSL2MinAndMax(SIS1100_Device_Struct* dev, unsigned char axis)
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
int setGainControlMax(SIS1100_Device_Struct* dev, unsigned char axis)
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
int setGainControlMin(SIS1100_Device_Struct* dev, unsigned char axis)
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
int AdjustGainControl(SIS1100_Device_Struct* dev, unsigned char axis)
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
int ResetOptPowL2MinAndMax(SIS1100_Device_Struct* dev, unsigned char axis)
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
int CheckSaturation(SIS1100_Device_Struct* dev, unsigned char axis, bool* sat)
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
int CheckSaturation_ForAllAxis(SIS1100_Device_Struct* dev, bool* sat_Buf)
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
int ReadAPDGain(SIS1100_Device_Struct* dev, unsigned char axis, double* APD_Gain) {
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
int ReadAPDGain_ForAllAxis(SIS1100_Device_Struct* dev, double* APD_Gain_Buf) {

	double APD_Gain = 0.0;

	for (int i = 1; i < 5; i++)
	{
		ReadAPDGain(dev, i, &APD_Gain);
		*(APD_Gain_Buf + i - 1) = APD_Gain;
		APD_Gain = 0.0;
	}
	return RET_SUCCESS;
}
int EnableAuxRegisters(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCtrl2);//rw
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data |= 0x200;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	return RET_SUCCESS;
}
bool IsAPDCtrlSoftErrs(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zVMEErrStat2);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if (uint_vme_data & 0x100)
		return true;
	return false;
}
int ReadAPDCtrlSoftErrs(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int Enable32bitsOverflow(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int Disable32bitsOverflow(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int DisableAuxRegisters(SIS1100_Device_Struct* dev, unsigned char axis) {
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
int SampleVMEPosition(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, ctr=0, uint_vme_address = 0x200;
	uint_vme_address = ADD(BASE_ADDRESS[axis - 1], zCmd);
	printf("Sampling velocity and position on axis %d...\n", axis);
	//*
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
	{
		printf("Register %6X access Faillure !  \n", uint_vme_address); return RET_FAILED;
	}
	while (!(uint_vme_data & 0x400))
	{
		if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
			{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	}
	//*/

	while (!GetVMEExtSampFlag(dev, axis)); // Wait for the VME external sample flag to be set before reading
	return RET_SUCCESS;
}
int Sclk_On(SIS1100_Device_Struct* dev) {
	//Turn on bits 7 and 9 (SCLK Timer enable and SCLK0 output)

	return (readModifyWrite("A24D16", dev, ADD(BASE_ADDRESS[2], zCtrl16), 0x280, 1) != RET_SUCCESS);
}
int VMESysReset(SIS1100_Device_Struct* dev) {
	printf("Hard reseting the system...\n");
	stat = sis1100w_VmeSysreset(dev);

	if (stat != Stat1100Success) {
		printf("Errors occured while hard reseting the card\n");
		return RET_FAILED;
	}
	printf("Reseting Zygo board...\n");
	return RET_SUCCESS;
}
int Sclk_Off(SIS1100_Device_Struct* dev) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zCtrl16);
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}

	uint_vme_data &= 0xFD7F;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
/// <summary>
/// set the sampling frequency.
/// </summary>
/// <param name="dev"> device </param>
/// <param name="sampTimerVal">Value to load in the sample timer register</param>
/// <returns>
/// 0 if success
/// -1 if failed
/// </returns>
int SetSampTimerFreq(SIS1100_Device_Struct* dev, unsigned short sampTimerVal) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[2], zSampleTimer);
	uint_vme_data = sampTimerVal;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return RET_SUCCESS;
}
int SetHoldSampEnable(SIS1100_Device_Struct* dev) {
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
int ResetHoldSampEnable(SIS1100_Device_Struct* dev) {
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
/// <summary>
/// takes the target sampling frequency, determine the value to load in the sample timer register then start sampling.
/// </summary>
/// <param name="dev">device</param>
/// <param name="sampleFreq"> the sample frequency in MHz</param>
/// <returns>
/// 0 if success
/// -1 if failed
/// </returns>
int enableSampling(SIS1100_Device_Struct* dev, double sampleFreq) {
	unsigned short rdVal = 0, sclkVal = 0;
	if (sampleFreq <= 0 || sampleFreq > SAMP_FREQ_MAX)
	{
		sclkVal = 1;
		sampleFreq = 20.0;
	}
	if (sampleFreq <= SAMP_FREQ_MIN)
	{
		
		sclkVal = 0xFFFF;
		sampleFreq = 1 / (0.05 * 0xFFFF);
		printf("ZMI sample rate minimum is %f Hz.\n Setting to min...\n", (sampleFreq * 1e6));
	}
	else
		sclkVal = (unsigned short)(1 / (sampleFreq * 0.05) - 1);

	printf("Sampling at %f Mhz\n", sampleFreq);
	printf("SCLK0 Value: 0x%x\n", sclkVal);
	//turn off sclk (turn off 7 and 9) and turn off divider (turn off 6)
	Sclk_Off(dev);
	//set sclk rate(only master axis needed)
	SetSampTimerFreq(dev, sclkVal);
	Sclk_On(dev);
	return RET_SUCCESS;
}
int DisableSampleTimer(SIS1100_Device_Struct* dev) {
	Sclk_Off(dev);
	return RET_SUCCESS;
}
bool GetVMEExtSampFlag(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[axis-1], zStat0);

	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 0) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	if ((uint_vme_data &= 0x400)) {
		return true;
	}
	return false;
}
bool clearVMEExtSampFlag(SIS1100_Device_Struct* dev, unsigned char axis) {
	unsigned int uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_data = 0x100;
	if (Read_Write("A24D16", dev, uint_vme_address, &uint_vme_data, 1) != RET_SUCCESS)
		{printf("Register %6X access Faillure !  \n", uint_vme_address);return RET_FAILED;}
	return true;
}
bool IsVMEIntReqPending(SIS1100_Device_Struct* dev, unsigned char axis) {
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
	SIS1100_Device_Struct* dev,
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
	SIS1100_Device_Struct* dev,
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
		return return_code;

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
		return return_code;

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
		return return_code;
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
		return return_code;
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
		return return_code;
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
		return return_code;
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
		return return_code;
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
		return return_code;
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
		return return_code;
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
		return return_code;
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
		return return_code;
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
		return return_code;
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
		return return_code;
	}



	/******************************************************************************************************************************/

	/******************************************************************************************************************************/
	comp_valid_flag = 0;
	return RET_FAILED;
}
