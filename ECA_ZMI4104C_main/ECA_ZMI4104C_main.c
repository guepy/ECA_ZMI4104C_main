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

PUINT base_A24D32_FR_ptr, base_A24D32_ptr;
static SIS1100_Device_Struct dev;

int main(int argc, char** agrv)
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
	BIAS_MODE bias_mode = BIAS_SIG_RMS_ADJUST_MODE;
	// Create a mutex with no initial owner
	/*/
	ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	if (ghMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		return 1;
	}*/
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
	GetLocalTime(&lt);
	if (fopen_s(&fdLog, "logfile.txt", "a") != RET_SUCCESS)
		return RET_FAILED;
	
	fprintf(fdLog, "[***********; %d/%d/%d at %d:%d:%d] ;************]\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute,lt.wSecond);
	printf("ok0");
	if(Init_SIS_boards(&dev)!=RET_SUCCESS) FATAL("Failed to initialize SIS boards\n");
	//Sleep(10);
	printf("ok1");
	if(Init_ZMI_bd(&dev) != RET_SUCCESS) FATAL("Failed to initialize ZMI board\n");
	printf("ok2");
	if(InitAxis(&dev, bias_mode) != RET_SUCCESS) FATAL("Failed to initialize axis\n");
	printf("ok3");
	EnableDoublePassInterferometer();
	//Here you should first strat up the motor at the planned running velocity to enable CEC hardware
	// to calculate CE coefficients. thereafter you should start acquisition
	
	enableSampling(&dev, 3e-4);
	
#if ACTIVATE_CEC
	if (configureCEChardware(&dev, 3, 96, 31457) != RET_SUCCESS) // used default velocity value;
	{
		WARN("Can not configure CEC hardware\n");
		return RET_FAILED;
	}
#endif
	double pos = 0.0, temp_pos=0.0;
	FILE* fd=NULL;
	vme_irq_level = INT_LEVEL6;
	vme_irq_vector = 12;
	UCHAR fifoAxis[4], tabSize;
	int ret = 0;
	CEratios ceRatios = { 0.0,0.0,0.0 };
	CECoeffs ceCoeffs = { 0.0,0.0,0.0 };
	CEratioUnits ratioUnits = ratio_in_percent;
	fifoParam testparam;
	int valid_flag = 0;
	/*/
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
	CreateThreads(&dev);
	while (1)
	{
		ReadOpticalPowerUsingSSIav(&dev, position);
		// rmq: some functions I wrote tend to be incompatible with readposition32 function, need
		// to check its implementation
		//ReadPosition32(&dev, AXIS3, position);
		ReadSamplePosition32(&dev, AXIS3, position);
		//ReadTime32_ForAllAxis(&dev, time);
		ReadVelocity32_ForAllAxis(&dev, time);
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
			WARN("Failed to calculate CE ratios \n");
			valid_flag = 1;
			break;
		}
		INFO("CEC0coeff %f+i%f, CEC1coeff %f, CECNcoeff  %f+i%f\n", ceCoeffs.CEC0coeff.rpart, 
			ceCoeffs.CEC0coeff.ipart, ceCoeffs.CEC1coeff, ceCoeffs.CECNcoeff.rpart, ceCoeffs.CECNcoeff.ipart);
		if (calculateCEratio(&dev, 3, &ceRatios, ratioUnits) != RET_SUCCESS)
		{
			WARN("Failed to calculate CE ratios \n");
			valid_flag = 1;
			break;
		}
		INFO("Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
		ceRatios.measSignal = 0;
		ceRatios.CE0ratio = 0;
		ceRatios.CENratio = 0;
		if(getAproximateCEratio(&dev, 3, &ceRatios, ratioUnits) != RET_SUCCESS)
		{
			WARN("Failed to calculate CE ratios \n");
			valid_flag = 1;
			break;
		}
		INFO("Approximate Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
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
		fifoAxis[2] = 6;
		fifoAxis[3] = 1;
		testparam.acqTime = 0;
		testparam.freq = 8000;
		testparam.nbrPts = (UINT)40;

		tabSize = sizeof(fifoAxis) / sizeof(fifoAxis[0]);
		configureFifoFlyscan(&dev, &testparam, base_A24D32_ptr,fifoAxis, &tabSize);
		processFifoData(tabSize, fifoAxis, base_A24D32_ptr, testparam.nbrPts);
#endif
//*/
#if FLYSCAN_MODE_ON
		INFO("Sampling data... \n");
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
