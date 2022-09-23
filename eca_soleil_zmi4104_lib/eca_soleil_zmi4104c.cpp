#include "pch.h"
#include "eca_soleil_zmi4104c.h"
#include "vmeInterruptConst.h"
#include <zVME_const.h>

volatile uint32_t pNbr = 0;
volatile uint32_t tNbr = 0;

int operator-(const Axes& a, const int l) {
	int tmp = static_cast<uint8_t>(a) - l;
	return tmp;
}

void setBaseAddress(uint32_t baseAddressAxis3) {
	zygoLogInfo("Modifying base address\n");
	BASE_ADDRESS[0] = baseAddressAxis3 - 0x2000;
	BASE_ADDRESS[1] = baseAddressAxis3 - 0x1000;
	BASE_ADDRESS[AXIS3 - 1] = baseAddressAxis3;
	BASE_ADDRESS[3] = baseAddressAxis3 + 0x1000;
	zygoLogInfo("New base address is 0x%07X", baseAddressAxis3);
}
int createEvents()
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
		return CREATE_EVENT_FAILED;
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
		return CREATE_EVENT_FAILED;
	}
	return RET_SUCCESS;
}
int  createThreads()
{
	int i = 0;
	DWORD dwThreadID;

	// Create  thread 
		// TODO: More complex scenarios may require use of a parameter
		//   to the thread procedure, such as an event per thread to  
		//   be used for synchronization.
	vmeIntThread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		vmeIntThreadFunc,        // name of the thread function
		(LPVOID)dev,              //  thread parameters
		0,                 // default startup flagsba
		&dwThreadID);

	if (vmeIntThread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return CREATE_THREAD_FAILED;
	}
	else
		hThreadArray[0] = vmeIntThread;

	waitForSis3100IrqThread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		waitForSis3100IrqThreadFunc,        // name of the thread function
		(LPVOID)dev,              //  thread parameters
		0,                 // default startup flags
		&dwThreadID);
	if (waitForSis3100IrqThread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return CREATE_THREAD_FAILED;
	}
	else
		hThreadArray[1] = waitForSis3100IrqThread;

	waitForVmeIrqThread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		waitForVmeIrqThreadFunc,        // name of the thread function
		(LPVOID)dev,              //  thread parameters
		0,                 // default startup flags
		&dwThreadID);
	if (waitForVmeIrqThread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return CREATE_THREAD_FAILED;
	}
	else
		hThreadArray[2] = waitForVmeIrqThread;

	lemoIN1Thread = CreateThread(
		NULL,              // default security
		0,                 // default stack size
		lemoIN1ThreadFunc,        // name of the thread function
		(LPVOID)dev,              //  thread parameters
		0,                 // default startup flags
		&dwThreadID);
	if (lemoIN1Thread == NULL)
	{
		printf("CreateThread failed (%d)\n", GetLastError());
		return CREATE_THREAD_FAILED;
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
void closeThreads(void)
{
	// Close all event handles (currently, only one global handle).
	CloseHandle(vmeIntThread);
	CloseHandle(lemoIN1Thread);
	CloseHandle(waitForSis3100IrqThread);
	CloseHandle(waitForVmeIrqThread);
}
void CloseEvents()
{
	// Close all event handles (currently, only one global handle).

	CloseHandle(vmeIrq6Event);
	CloseHandle(lemoIN1Event);
}
int lemoInterruptCallbackFunction(FILE* fd) {
	double pos[4];

	if (return_code = readPositionForAllAxis(pos)) {
		zygoLogWarn("read sample position faillure\n");
		return return_code;
	}

	fprintf(fd, "%lf;%lf;%lf;%lf\n", pos[0], pos[1], pos[2], pos[3]);
	return RET_SUCCESS;
}
DWORD WINAPI lemoIN1ThreadFunc(LPVOID lpParam)
{
	SIS1100_Device_Struct* dev = (SIS1100_Device_Struct*)lpParam;
	uint32_t get_irq_level = 0;
	DWORD dwWaitResult = 0;
	uint32_t loop_cnt, error_cnt;
	//------------------------------------------------------------------------------------
	error_cnt = 0;
	loop_cnt = 0;
	zygoLogInfo("Thread lemoIN1 is running\n");
	do {
		dwWaitResult = WaitForSingleObject(
			lemoIN1Event,    // handle to mutex
			1000);  // 1s time-out interval

		switch (dwWaitResult)
		{
			// The thread got ownership of the mutex
		case WAIT_OBJECT_0:
			zygoLogInfo("Interrupt Thread %d is using the dev structure...\n", GetCurrentThreadId());
			zygoLogInfo("A LEMO INTERRUPT HAS OCCURED\n");
			//lemoInterruptCallbackFunction(fd);
			loop_cnt++;
			break;
		case WAIT_ABANDONED:
			break;
		default:
			break;
		}
	} while (1); //(valid_flag != 1);
	zygoLogInfo("==============================================================\n");
	zygoLogInfo("nbr of LEMO interrupt %d\n", loop_cnt);
	zygoLogInfo("==============================================================\n");
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
		zygoLogInfo("Closing Interrupt Handler \n");
		/* close VME environment
		sis1100w_Close(&dev);
		if (!ReleaseMutex(ghMutex))
			zygoLogInfo("Error while releasing mutex\n");
		break;

		// An error occurred
	default:
		zygoLogInfo("Wait error (%d)\n", GetLastError());

		return RET_SUCCESS;
	}
	*/
	// Now that we are done reading the buffer, we could use another
	// event to signal that this thread is no longer reading. This
	// example simply uses the thread handle for synchronization (the
	// handle is signaled when the thread terminates.)

	zygoLogInfo("Thread %d exiting\n", GetCurrentThreadId());
	return RET_SUCCESS;
}
DWORD WINAPI vmeIntThreadFunc(LPVOID lpParam)
{

	SIS1100_Device_Struct* dev = (SIS1100_Device_Struct*)lpParam;
	uint32_t get_irq_level = 0x6;
	DWORD dwWaitResult = 0;
	uint32_t loop_cnt, error_cnt;
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
			zygoLogInfo("Interrupt Thread %d is using the dev structure...\n", GetCurrentThreadId());
			zygoLogInfo(" \tA VME INTERRUPT HAS OCCURED \n");
			rc = vme_IACK_D8_read(dev, get_irq_level, &read_irq_vector);
			if (rc != 0) zygoLogInfo("IACK Cycle:  rc = 0x%08x\n", rc);
			zygoLogInfo(" read_irq_vector =  %x \r\n", read_irq_vector);
			break;
		case WAIT_ABANDONED:
			break;
		default:
			break;
		}
	} while (1); //(valid_flag != 1);
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
		zygoLogInfo("Closing Interrupt Handler \n");
		/* close VME environment
		sis1100w_Close(&dev);
		if (!ReleaseMutex(ghMutex))
			zygoLogInfo("Error while releasing mutex\n");
		break;

		// An error occurred
	default:
		zygoLogInfo("Wait error (%d)\n", GetLastError());

		return RET_SUCCESS;
	}
	*/
	// Now that we are done reading the buffer, we could use another
	// event to signal that this thread is no longer reading. This
	// example simply uses the thread handle for synchronization (the
	// handle is signaled when the thread terminates.)

	zygoLogInfo("Thread %d exiting\n", GetCurrentThreadId());
	return RET_SUCCESS;
}
/*********************************************************/
/*
DWORD WINAPI fastReadThreadFunc(LPVOID lpParam)
{
	// lpParam not used in this example.
	UNREFERENCED_PARAMETER(lpParam);

	DWORD dwWaitResult = 0;
	uint32_t position;
	zygoLogInfo(" Thread %d is running...\n",GetCurrentThreadId());
	do {
		//ReadSamplePosition32(&dev, AXIS3, &position);
	} while (0);//1
	zygoLogInfo("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}

DWORD WINAPI readThreadFunc(LPVOID lpParam)
{
	// lpParam not used in this example.
	UNREFERENCED_PARAMETER(lpParam);

	DWORD dwWaitResult = 0;
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0,
		get_lwords = 0,
		no_of_lwords=0;
	uint32_t* ptr = base_A24D32_ptr;
	zygoLogInfo(" Thread %d is running...\n", GetCurrentThreadId());
	do {
		for (USHORT i = 0; i < 0x1C7; i = i + 4) {
			uint_vme_address = BASE_ADDRESS + i;
			return_code = vme_A32DMA_D32_read(&dev, uint_vme_address, &uint_vme_data, no_of_lwords, &get_lwords);
			if (return_code != 0) {
				zygoLogWarn("return Error vme_A32DMA_D32_read:   return_code = 0x%08x  at address = 0x%08x\n", return_code, uint_vme_address);
				return RET_FAILED;
			}
			if (no_of_lwords != get_lwords) {
				zygoLogWarn("length Error vme_A32DMA_D32_read:   must length = 0x%08x  read length = 0x%08x\n", no_of_lwords, get_lwords);
				return RET_FAILED;
			}
			*(base_A24D32_ptr++) = uint_vme_data;
		}
		base_A24D32_ptr = ptr;
	} while (!end_read);
	zygoLogInfo("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}
*/
/*/
int allocateWinMemSpace(  uint8_t* nof_windows) {

	uint32_t nof_vme_windows = 2;
	uint32_t mapParams[2 * 4] = {  // 2 descriptors (Address windows) each contains 4 32-bit entries

		// 1.descriptor
		0xff010800, //* protocol header
		0x39,       //* A24
		0x00000000, //* VME Base Address
		0,

		// 2.descriptor
		0xff010800, //* protocol header
		0x39,       //* A24
		0x00400000, //* VME Base Address
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
	uint32_t* mappedArea = NULL;
	stat = sis1100w_vme_map_get_ptr(dev, &mappedArea);
	if (stat != Stat1100Success) {
		printf("Error in 'sis1100w_vme_map_get_adr': %d\n", stat);
		return RET_FAILED;
	}
	printf("mapped area: %p\n", mappedArea);

	//* VME Windows pointer
	uint8_t* vme_window1_ptr = (uint8_t*)mappedArea;                    // 1st 4MB block;
	uint8_t* vme_window2_ptr = (uint8_t*)mappedArea + (1 * 0x400000);    // 2st 4MB block;

	// VME Address Pointer definitons

		//1.descriptor 4MB block A24/D32-cycles ;
	base_A24D32_FR_ptr = (uint32_t*)(vme_window1_ptr);  // D32 cycle pointer with VME Base Address 0x00000000
	//*(base_A24D32_0x000000_ptr + 0x0)      -> first VME address 0x00000000
	//*(base_A24D32_0x000000_ptr + 0xFFFFF)  -> last  VME address 0x003FFFFC
	// To use in fast position reading cycle

	//2.descriptor 4MB block A24/D32-cycles ;
	base_A24D32_ptr = (uint32_t*)(vme_window2_ptr);  // D32 cycle pointer with VME Base Address 0x00000000
	//*(base_A24D32_0x000000_ptr + 0x0)      -> first VME address 0x00000000
	//*(base_A24D32_0x000000_ptr + 0xFFFFF)  -> last  VME address 0x003FFFFC
	//To use in central read thread

}
int releaseWinMemSpace(  uint8_t nof_vme_windows) {
	// cleanup
	stat = sis1100w_vme_unmap(dev, nof_vme_windows * 4);
	if (stat != Stat1100Success) {
		printf("Error in 'sis1100w_vme_unmap': %d\n", stat);
		return RET_FAILED;
	}

	sis1100w_Close(dev);
	printf("Windows -vme map demo- finished \n");

}
*/

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
int configureCecHardware(Axes axis, USHORT ceVelMin, USHORT ceVelMax) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	char sc_char[3];
	/*At the startup CEC is disabled*/
	/*When a motion occurs, CEC coeff are calculated*/
	/*1-First of all we should set CE_Min_Vel and CE_Max_Vel
	 * - The default value of CE_Min_Vel is 96 which represents a 7.3Khz Doppler shift or
	 * a velocity of approximately 1.2mm/s. . The units of this register are 76.3 Hz, or 12 μm/sec for a double-pass
	 * interferometer Its value shouldn't be less than 24 which represents a 1.8Khz Doppler shift
	 * and may cause improper operation of the CEC function
	 * - The default value of CE_Max_Vel is 31457  which represents a 2.4Mhz Doppler shift or a velocity of approximately
	 * 0.38m/s(double pass)*/


	 /*1-Then, we should perform a motion at a velocity higher than the CE_Min_Vel and
	  *lesser than CE_Max_Vel so that the the CEC coeff can be calculated. The motion should last at least
	  *4.1ms before CEC coeff can be updated
	  */

	if (ceVelMin < CE_MIN_VEL) {
		zygoLogWarn("ERROR: The CE Min Velocity should not be set to a value smaller than 24, which represents a \
				1.8 kHz Doppler shift, or a velocity of approximately 0.29 mm/s. this may cause improper operation of the CEC function\n");
		return CEC_MIN_VEL_ERROR;
	}
	//set ce min velocity
	if (return_code = setCeminVel(axis, CE_MIN_VEL))
	{
		{zygoLogWarn("setCeminVel failed !  \n"); return return_code; }
	}
	//set ce max velocity
	if (return_code = setCemaxVel(axis, CE_MAX_VEL))
	{
		{zygoLogWarn("setCemaxVel failed !  \n");  return return_code; }
	}
	zygoLogInfo("Start the motor for a displacement of at least 1s then press Enter. CEC hardware need to observe the motion at startup \
in order to determine correct CE coefficients \n");
	if (return_code = waitCeinit2Complete(axis)) {
		zygoLogWarn("failed to initialize CE hardware\n");
		return return_code;
	}
	zygoLogInfo(" CE hardware configuration is complete\n");

	if (return_code = enableCecCompensation(axis)) {
		zygoLogWarn("failed to enable CE compensation\n");
		return return_code;
	}
	/*
	if (return_code = readCecErrorStatReg(  axis, &uint_vme_data)) {
		zygoLogWarn("readCecErrorStatReg failed\n");
		return return_code;
	}
	*/
	cecState = 1;
	return RET_SUCCESS;

}
int readCecErrorStatReg(Axes axis, uint32_t* CEstatReg) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCEerrorStat);
	uint_vme_data = 0;
	zygoLogInfo("Reading CE status register\n");
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
	}
	*CEstatReg = uint_vme_data;
	if ((uint_vme_data & 0x1)) {
		zygoLogInfo("The cyclic error 0 has exceeded the value set in the CE 0 Limit register\n ");
	}
	if ((uint_vme_data & 0x2)) {
		zygoLogInfo("The cyclic error N has exceeded the value set in the CE N Limit register\n ");
	}
	if ((uint_vme_data & 0xFFF0)) {
		zygoLogInfo("An arithmetic overflow has occured at some point in the CEC signal processing.This may occur if the CE levels are greater than 20 percent . \n");
	}
	return RET_SUCCESS;
}
DWORD WINAPI waitForVmeIrqThreadFunc(LPVOID lpParam)
{
	int rc;
	uint32_t doorbell_value = 0;
	uint32_t sis_get_irq_level = 0;

	SIS1100_Device_Struct* dev = (SIS1100_Device_Struct*)lpParam;

	vmeIrq6Event = CreateEvent(
		NULL,               // default security attributes
		FALSE,               // Auto-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("vmeIrq6Event")  // object name
	);
	if (vmeIrq6Event == NULL)
	{
		zygoLogWarn("CreateEvent failed (%d)\n", GetLastError()); 
		return CREATE_EVENT_FAILED;
	}
	sis1100w_sis310x_Register_For_Irq(dev, vmeIrqMask); //Register to listen to IRQ level interrupt
	//PLX_INTERRUPT intSrc;
	//createEvents();
	do {
		//IRQ update on SIS3100
		rc = s3100_control_write(dev, SIS3100_OPT_IN_IRQ_LATCH, DOORBELL_IRQ_UPDATE);
		if (Stat1100Success != rc) {
			zygoLogInfo("Error in 's3100_control_write' (Thread Running: %s, stopping)\n", __FUNCTION__);
			break;
		}
		rc = sis1100w_sis310x_Wait_For_Irq(dev, 1000, &doorbell_value); //wait for 1s, use -1 for INFINITE
		if (doorbell_value) {
			zygoLogInfo("Doorbell value is %X\n", doorbell_value);
			sis_get_irq_level = 0;
			// VME IRQ7
			if ((doorbell_value & DOORBELL_VME_IRQ7) == DOORBELL_VME_IRQ7) {
				sis_get_irq_level = 0x7;
			}

			// VME IRQ6
			if ((doorbell_value & DOORBELL_VME_IRQ6) == DOORBELL_VME_IRQ6) {
				sis_get_irq_level = 0x6;
				zygoLogInfo("Sending vmeIrq event to ISR..\n");
				if (!SetEvent(vmeIrq6Event))
				{
					zygoLogWarn("SetEvent failed (%d)\n", GetLastError()); return RET_FAILED;
					break;
				}
				rc = s3100_control_write(dev, SIS3100_OPT_VME_IRQ_CTRL, VME_IRQ6_STA_CLR_BIT);
				if (Stat1100Success != rc) {
					zygoLogWarn("\n\nError in 's3100_control_write' (Thread Running: %s, stopping)\n", __FUNCTION__); return rc;
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
	} while (1); //(valid_flag != 1);

	CloseHandle(vmeIrq6Event);
	//zygoLogInfo("Terminating Thread %d..\n", GetCurrentThreadId());
	return RET_SUCCESS;
}
DWORD WINAPI waitForSis3100IrqThreadFunc(LPVOID lpParam)
{
	int rc;
	uint32_t doorbell_value;
	uint32_t sis_get_irq_level = 0;

	SIS1100_Device_Struct* dev = (SIS1100_Device_Struct*)lpParam;
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
		return CREATE_EVENT_FAILED;
	}

	sis1100w_sis310x_Register_For_Irq(dev, sisIrqMask); //Register to listen to IRQ level interrupt
	//createEvents();
	do {
		//IRQ update on SIS3100
		rc = s3100_control_write(dev, SIS3100_OPT_IN_IRQ_LATCH, DOORBELL_IRQ_UPDATE);
		if (Stat1100Success != rc) {
			printf("\n\nError in 's3100_control_write' (IRQ Running: %d, stopping)\n", rc);
			continue;
		}
		rc = sis1100w_sis310x_Wait_For_Irq(dev, 1000, &doorbell_value); //wait for 1s, use -1 for INFINITE
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
				rc = s3100_control_write(dev, SIS3100_OPT_IN_IRQ_LATCH, FLAT_IN3_IRQ_STA_CLR_BIT);
				if (Stat1100Success != rc) {
					printf("\n\nError in 's3100_control_write' (Thread Running: %s, stopping)\n", __FUNCTION__);
					break;
				}
			}
		}
		doorbell_value = 0;
	} while (1); //(valid_flag != 1);

	CloseHandle(lemoIN1Event);
	printf("Terminating Thread %d..\n", GetCurrentThreadId());
	return RET_SUCCESS;
}
int	ackForSis3100VmeIrq(uint32_t sis_get_irq_level)
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

int enableSinglePassInterferometer(void) {
	zygoLogInfo("Single pass interferometer activated\n");
	positionScale = SINGLE_PASS_INT_POS_COEF;    //Converts to mm as default
	curInterferoConfig = 1;
	velocityScale = SINGLE_PASS_INT_VEL_COEF * (1e-3);    //Converts to m/s as default
	return RET_SUCCESS;
}
int enableDoublePassInterferometer(void) {

	zygoLogInfo("Double pass interferometer activated\n");
	positionScale = DOUBLE_PASS_INT_POS_COEF;    //Converts to mm as default
	curInterferoConfig = 2;
	velocityScale = DOUBLE_PASS_INT_VEL_COEF * (1e-3);    //Converts to m/s as default
	return RET_SUCCESS;
}
int enableQuadPassInterferometer(void) {

	zygoLogInfo("Quad pass interferometer activated\n");
	positionScale = QUAD_PASS_INT_POS_COEF;    //Converts to mm as default
	curInterferoConfig = 3;
	velocityScale = QUAD_PASS_INT_VEL_COEF * (1e-3);    //Converts to m/s as default
	return RET_SUCCESS;
}

int setInterferometerConfiguration(uint32_t config) {
	if (checkLimits(config, 1, 2))
		return BAD_ARG_VALUE;
	if (config == 1)
		enableSinglePassInterferometer();
	else
		enableDoublePassInterferometer();
	return RET_SUCCESS;
}

int initAxis(BIAS_MODE bias_mode) {
	/*************************Axis Initialization***********************************/
	char	ch_access_mode[16];
	uint32_t	vme_data = 0,
		uint_vme_address = 0,
		uint_vme_data = 0;
	double val = 0.0;
	zygoLogInfo("Initializing axis\n");
	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);
	//select SCLK0 as sample clock source
	if (return_code = setVMEBusSampleClk(AXIS3, SCLK::SCLK0))
	{
		zygoLogWarn("setSampleSourceClock failed !  \n");
		return return_code;
	}
	if (return_code = setResetSourceClock(AXIS3, SCLK::SCLK0))
	{
		zygoLogWarn("setResetSourceClock failed !  \n");
		return return_code;
	}//select SCLK0 as reset clock source
	if (return_code = setTimeDelayBetweenResAndCompleteBit(AXIS3, 0))
	{
		zygoLogWarn("setTimeDelayBetweenResAndCompleteBit failed !  \n");
		return return_code;
	}
	if (return_code = enableDoublePassInterferometer())
	{
		zygoLogWarn("enableDoublePassInterferometer failed !  \n");
		return return_code;
	}
	//sis1100w_sis310x_Register_For_Irq(dev, sis_irq_mask); //Register to listen to IRQ6 level interrupt
	if (return_code = setVmeIntLevel(AXIS3, INT_LEVEL6))
	{
		zygoLogWarn("setResetSourceClock failed !  \n");
		return return_code;
	}//3
	if (return_code = setVmeIntVector(AXIS3, 0x12))
	{
		zygoLogWarn("setResetSourceClock failed !  \n");
		return return_code;
	}
	if (return_code = enableVmeGlobalInterrupt(AXIS3))
	{
		zygoLogWarn("setResetSourceClock failed !  \n");
		return return_code;
	}
	if (return_code = enableAllVmeInterrupts(AXIS3))
	{
		zygoLogWarn("setResetSourceClock failed !  \n");
		return return_code;
	}
	for (const auto& a : AXES) {

		//Enable auxiliary registers by default as we don't use data age ram
		if (return_code = enableAuxRegisters(a))
		{
			zygoLogWarn("enableDoublePassInterferometer failed !  \n");
			return return_code;
		}

		//disableAllVmeInterrupts(  a);
		if (return_code = disable32BitsOverflow(a))
		{
			zygoLogWarn("disable32BitsOverflow failed !  \n");
			return return_code;
		}
		if (return_code = enable37BitsSignExtension(a))
		{
			zygoLogWarn("enable37BitsSignExtension failed !  \n");
			return return_code;
		}			
		// enable sign extension of 32 bits to match 37 bits register size 
																			// when register data is written
		if (return_code = setPositionOffset37(a, &val))
		{
			zygoLogWarn("setPositionOffset37 failed !  \n");
			return return_code;
		}
		if (return_code = setKpAndKvCoeff(a, defKp, defKv))
		{
			zygoLogWarn("setKpAndKvCoeffr failed !  \n");
			return return_code;
		}				// Set Kp = -6 and Kv = -15		

		if (return_code = boardControlMode(a, bias_mode))
		{
			zygoLogWarn("boardControlMode failed !  \n");
			return return_code;
		}
		if (return_code = setSsiSquelch(a, defaultSSISquelch))
		{
			zygoLogWarn("setSsiSquelch failed !  \n");
			return return_code;
		}
		
	}

	if (return_code = getSamplingFrequency(Axes::Axis_3, currentSamplingFrequency))
	{
		zygoLogWarn("getSamplingFrequency failed !  \n");
		return return_code;
	}
	setPrecision(0);// set precision to 32bits;
	return RET_SUCCESS;
}
int disableAllVmeInterrupts(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab0);				// Disable VME interrupts 0
	uint_vme_data = 0;
	zygoLogInfo("Disabling VME Interrupts\n");
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab1);				// Disable VME interrupts 1
	uint_vme_data = 0x8000;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab2);				// Disable VME interrupts 2
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
	}
	return RET_SUCCESS;
}

int enableAllVmeInterrupts(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0xFFFF;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab0);				// VME interrupts 0

	zygoLogInfo("Enabling VME Interrupts\n");
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code; 
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab1);				// VME interrupts 1
	uint_vme_data |= 0x811F;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code; 
	}
	uint_vme_data = 0xF0FF;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab2);				//  VME interrupts 2
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code; 
	}
	return RET_SUCCESS;
}
int enableVmeGlobalInterrupt(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data;

	zygoLogInfo("Enabling Global Interrupts\n");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab1);				// Disable VME interrupts 
	uint_vme_data = 0;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code; 
	}
	uint_vme_data |= 0x8000;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code; 
	}
	return RET_SUCCESS;
}
int processRamData(uint32_t nbrAxis, uint32_t* base_A24D32_axis1_ptr, uint32_t* base_A24D32_axis3_ptr, uint32_t ramPagesNbr, char* folderName, double* meanVal, double* stdDevVal) {
	static int a = 0;
	GetLocalTime(&lt);
	static FILE* fd;
	uint32_t val1 = 0, val2 = 0;
	double pos1 = 0.0, pos2 = 0.0;
	double mean[4] = { 0.0, 0.0, 0.0, 0.0 }, stdDev[4] = { 0.0, 0.0, 0.0, 0.0};
	double* localPos;
	char* path;
	if (checkLimits(ramPagesNbr, 1, NBR_RAM_PAGES)) {
		zygoLogWarn("ramPagesNbr is not in the requested range \n");
		return BAD_ARG_VALUE;
	}
	if (meanVal == NULL || stdDevVal == NULL || folderName == NULL ) {
		return BAD_ARG_POINTER;
	}
	zygoLogInfo("Processing RAM data\n");
	if (nbrAxis >= 2) {
		if (!base_A24D32_axis1_ptr || !base_A24D32_axis3_ptr) {
			zygoLogWarn("Based on the number of axis which is %d, none of the pointer argument is allow to be NULL", nbrAxis); 
			return BAD_ARG_POINTER;
		}
	}
	else {
		if (!base_A24D32_axis1_ptr && !base_A24D32_axis3_ptr) {
			zygoLogWarn("Based on the number of axis which is %u, both pointer arguments can not be NULL", nbrAxis); 
			return BAD_ARG_POINTER;
		}
	}
	val1 = strlen(folderName) + strlen("\\Position_values.csv") + 2;
	path = (char*)calloc( val1, sizeof(char));
	zygoLogInfo("size of path is %d\n", val1);
	sprintf_s(path, val1, "%s\\Position_values.csv", folderName);
	zygoLogInfo("Opening file %s to store position values \n", path);
	if (fopen_s(&fd, path, "a") != RET_SUCCESS) {
		zygoLogWarn("Failed to open file %s\n", path);
		free(path);
		return FILE_OPEN_FAILED;
	}
	fprintf(fd, "[***********, %d/%d/%d at %d:%d] ,************\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute);
	uint32_t nbrOfPts = (ramPagesNbr * NBR_SAMP_PER_PAGE);
	switch (nbrAxis)
	{
	case 1:
		fprintf(fd, "Axis3\n");
		localPos = (double*)calloc(nbrOfPts , sizeof(double));
		if (localPos == NULL) {
			fclose(fd);
			free(path);
			perror("localPos calloc:");
			return ALLOC_MEM_ERROR;
		}
		for (int i = 0; i < ramPagesNbr; i++) {
			// Shift to the next page
			for (int j = 0; j < NBR_SAMP_PER_PAGE; j++) {
				val1 = (uint32_t)(base_A24D32_axis3_ptr[i * NBR_SAMP_PER_PAGE + j]);
				pos1 = static_cast<double>(((int)val1) * positionScale) / 8.0;
				fprintf(fd, "%.12lf, 0x%x \n", pos1, val1);
				localPos[i] = pos1;
				*mean += pos1;
			}

		}
		// working out the mean
		meanVal[2] = (*mean) / nbrOfPts; // meanval on main axis (axis 3)

		//working out the standard deviation
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			*stdDev += std::pow((localPos[i] - meanVal[2]), 2);
		}
		stdDevVal[2] = sqrt((*stdDev) / nbrOfPts);

		fprintf(fd, "Mean\n");
		fprintf(fd, "%.12lf\n", meanVal[2]);
		fprintf(fd, "Std dev\n");
		fprintf(fd, "%.12lf\n", stdDevVal[2]);
		break;
	case 2:
		fprintf(fd, "Axis1, , Axis3\n");
		zygoLogInfo("ramPage nbr is %d\n", ramPagesNbr);
		localPos = (double*)calloc(2* nbrOfPts, sizeof(double));
		if (localPos == NULL) {
			fclose(fd);
			free(path);
			perror("localPos calloc:");
			return ALLOC_MEM_ERROR;
		}
		for (int i = 0; i < ramPagesNbr; i++) {
			// Shift to the next page
			for (int j = 0; j < NBR_SAMP_PER_PAGE; j++) {
				val1 = (uint32_t)(base_A24D32_axis1_ptr[i * NBR_SAMP_PER_PAGE + j]);
				pos1 = static_cast<double>((((int)val1) * positionScale) / 8.0);
				val2 = (uint32_t)(base_A24D32_axis3_ptr[i * NBR_SAMP_PER_PAGE + j]);
				pos2 = static_cast<double>((((int)val2) * positionScale) / 8.0);
				localPos[2 * i] = pos1;
				localPos[2 * i + 1] = pos2;
				*mean += pos1;
				mean[1] += pos2;
				fprintf(fd, "%.12lf, 0x%x, %.12lf, 0x%x \n", pos1, val1, pos2, val2);
			}
		}

		// working out the mean
		meanVal[0] = (*mean) / nbrOfPts;
		meanVal[2] = (mean[1]) / nbrOfPts;
		//working out the standard deviation
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			*stdDev += std::pow((localPos[2 * i] - *meanVal), 2);
			stdDev[1] += std::pow((localPos[2 * i + 1] - meanVal[2]), 2);
		}
		stdDevVal[0] = sqrt((*stdDev) / (nbrOfPts));
		stdDevVal[2] = sqrt((stdDev[1]) / (nbrOfPts));

		fprintf(fd, "Mean\n");
		fprintf(fd, "%.12lf,%.12lf\n", meanVal[0], meanVal[2]);
		fprintf(fd, "Std dev\n");
		fprintf(fd, "%.12lf,%.12lf\n", stdDevVal[0], stdDevVal[2]);
		break;
	default:
		fprintf(fd, "Axis1, , Axis2, , Axis3, , Axis4\n");
		uint32_t val11 = 0;
		double pos11 = 0.0;
		uint32_t val21 = 0;
		double pos21 = 0.0;
		localPos = (double*)calloc(4 * nbrOfPts, sizeof(double));
		if (localPos == NULL) {
			fclose(fd);
			perror("localPos calloc:");
			free(path);
			return ALLOC_MEM_ERROR;
		}
		for (int i = 0; i < ramPagesNbr; i++) {
			// Shift to the next page
			for (int j = 0; j < NBR_SAMP_PER_PAGE / 2; j++) {
				val1 = (uint32_t)(base_A24D32_axis1_ptr[i * NBR_SAMP_PER_PAGE + j * 2]);
				val11 = (uint32_t)(base_A24D32_axis1_ptr[i * NBR_SAMP_PER_PAGE + j * 2 + 1]);
				pos1 = static_cast<double>(((int)val1) * positionScale) / 8.0;
				pos11 = static_cast<double>(((int)val11) * positionScale) / 8.0;

				val2 = (uint32_t)(base_A24D32_axis3_ptr[i * NBR_SAMP_PER_PAGE + j * 2]);
				val21 = (uint32_t)(base_A24D32_axis3_ptr[i * NBR_SAMP_PER_PAGE + j * 2 + 1]);
				pos2 = static_cast<double>(((int)val2) * positionScale) / 8.0;
				pos21 = static_cast<double>(((int)val21) * positionScale) / 8.0;
				fprintf(fd, "%.12lf, 0x%x, %.12lf, 0x%x, %.12lf, 0x%x, %.12lf, 0x%x \n", pos1, val1, pos11, val11, pos2, val2, pos21, val21);
				localPos[4 * i] = pos1;
				localPos[4 * i + 1] = pos11;
				localPos[4 * i + 2] = pos2;
				localPos[4 * i + 3] = pos21;
				*mean += pos1;
				mean[1] += pos11;
				mean[2] += pos2;
				mean[3] += pos21;
				//don't miss the overflow case
			}

		}
		//taking into account the fact that one memory region store values of 2 axes
		nbrOfPts = nbrOfPts / 2;
		// working out the mean
		for (int i = 0; i < 4; i++)
			meanVal[i] = (mean[i]) / nbrOfPts;
		//working out the standard deviation
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			*stdDev += std::pow((localPos[4 * i] - *meanVal), 2);
			stdDev[1] += std::pow((localPos[4 * i + 1] - meanVal[1]), 2);
			stdDev[2] += std::pow((localPos[4 * i + 2] - meanVal[2]), 2);
			stdDev[3] += std::pow((localPos[4 * i + 3] - meanVal[3]), 2);
		}
		for (int i = 0; i < 4; i++)
			stdDevVal[i] = sqrt((stdDev[i]) / nbrOfPts);

		fprintf(fd, " ,Mean\n");
		fprintf(fd, "%.12lf,%.12lf,%.12lf,%.12lf\n", meanVal[0], meanVal[1], meanVal[2], meanVal[3]);
		fprintf(fd, ", Std dev\n");
		fprintf(fd, "%.12lf,%.12lf,%.12lf,%.12lf\n", stdDevVal[0], stdDevVal[1], stdDevVal[2], stdDevVal[3]);
		break;
	}

	zygoLogInfo("Processiong RAM Data Done\n");
	free(localPos);
	free(path);
	fclose(fd);
	return RET_SUCCESS;
}
int processFifoData(uint32_t nbrAxis, uint8_t* axisTab, uint32_t* memPtr, uint32_t nbrOfPts, const char* folderName, double* meanVal, double* stdDevVal) {

	GetLocalTime(&lt);
	static FILE* fd;
	uint32_t val1 = 0, val2 = 0, sLen; // a = 0;
	double pos1 = 0.0, pos2 = 0.0, pos3 = 0.0, pos4 = 0.0;
	double mean[4] = { 0.0, 0.0, 0.0, 0.0, }, stdDev[4] = { 0.0, 0.0, 0.0, 0.0, };
	double* localPos;
	char *path;
	zygoLogInfo("Processing Fifo data\n");
	zygoLogInfo("Opening file to store position values \n");
	sLen = strlen(folderName) + strlen("%s\\Fifo_position_values.csv") + 1;
	path = (char*)calloc(sLen, sizeof(char));
	sprintf_s(path, sLen, "%s\\Fifo_position_values.csv", folderName);
	if (fopen_s(&fd, path, "a") != RET_SUCCESS) {
		zygoLogWarn("Openning file %s failed\n", path);
		free(path);
		return FILE_OPEN_FAILED;
	}
	fprintf(fd, "[***********, %d/%d/%d at %d:%d] ,************\n", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute);
	switch (nbrAxis)
	{
	case 1:
		fprintf(fd, "Axis %d\n", axisTab[0]);
		localPos = (double*)calloc(nbrOfPts, sizeof(double));
		if (localPos == NULL) {
			fclose(fd);
			zygoLogWarn("processFifoData::calloc failed\n");
			free(path);
			return ALLOC_MEM_ERROR;
		}
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			pos1 = static_cast<double>((int)(memPtr[i])) * positionScale;
			localPos[i] = pos1;
			*mean += pos1;
			fprintf(fd, "%.12lf\n", pos1);
		}
		
		// working out the mean
		meanVal[axisTab[0] - 1] = (*mean) / nbrOfPts;

		*mean = (*mean) / nbrOfPts;
		//working out the standard deviation
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			*stdDev += std::pow((localPos[i] - *mean), 2);
		}
		stdDevVal[axisTab[0] - 1] = sqrt((*stdDev) / (nbrOfPts));
		
		fprintf(fd, "Mean\n");
		fprintf(fd, "%.12lf\n", meanVal[axisTab[0] - 1]);
		fprintf(fd, "Std dev\n");
		fprintf(fd, "%.12lf\n", stdDevVal[axisTab[0] - 1]);
		
		break;
	case 2:
		fprintf(fd, "Axis %d,Axis %d\n", axisTab[0], axisTab[1]);
		localPos = (double*)calloc(2 * nbrOfPts, sizeof(double));
		if (localPos == NULL) {
			fclose(fd);
			zygoLogWarn("processFifoData::calloc failed\n");
			free(path);
			return ALLOC_MEM_ERROR;
		}
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			pos1 = static_cast<double>((int)(memPtr[2 * i])) * positionScale;
			pos2 = static_cast<double>((int)(memPtr[2 * i + 1])) * positionScale;
			localPos[2 * i] = pos1;
			localPos[2 * i + 1] = pos2;
			*mean += pos1;
			mean[1] += pos2;
			fprintf(fd, "%.12lf,%.12lf\n", pos1, pos2);
		}
		// working out the mean
		meanVal[axisTab[0] - 1] = (*mean) / nbrOfPts;
		meanVal[axisTab[1] - 1] = (mean[1]) / nbrOfPts;

		*mean = (*mean) / nbrOfPts;
		mean[1] = (mean[1]) / nbrOfPts;
		//working out the standard deviation
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			*stdDev += std::pow((localPos[2 * i] - *mean), 2);
			stdDev[1] += std::pow((localPos[2 * i + 1] - mean[1]), 2);
		}
		stdDevVal[axisTab[0] - 1] = sqrt((*stdDev) / (nbrOfPts));
		stdDevVal[axisTab[1] - 1] = sqrt((stdDev[1]) / (nbrOfPts));

		fprintf(fd, "Mean\n");
		fprintf(fd, "%.12lf,%.12lf\n", meanVal[axisTab[0] - 1], meanVal[axisTab[1] - 1]);
		fprintf(fd, "Std dev\n");
		fprintf(fd, "%.12lf,%.12lf\n", stdDevVal[axisTab[0] - 1], stdDevVal[axisTab[1] - 1]);
		break;
	case 3:
		fprintf(fd, "Axis %d,Axis %d,Axis %d\n", axisTab[0], axisTab[1], axisTab[2]);
		localPos = (double*)calloc(3* nbrOfPts, sizeof(double));
		if (localPos == NULL) {
			fclose(fd);
			zygoLogWarn("processFifoData::calloc failed\n");
			free(path);
			return ALLOC_MEM_ERROR;
		}
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			pos1 = static_cast<double>((int)(memPtr[3 * i])) * positionScale;
			pos2 = static_cast<double>((int)(memPtr[3 * i + 1])) * positionScale;
			pos3 = static_cast<double>((int)(memPtr[3 * i + 2])) * positionScale;
			localPos[3 * i] = pos1;
			localPos[3 * i + 1] = pos2;
			localPos[3 * i + 2] = pos3;
			*mean += pos1;
			mean[1] += pos2;
			mean[2] += pos3;
			fprintf(fd, "%.12lf,%.12lf,%.12lf\n", pos1, pos2, pos3);
		}
		// working out the mean
		meanVal[axisTab[0] - 1] = (*mean) / nbrOfPts;
		meanVal[axisTab[1] - 1] = (mean[1]) / nbrOfPts;
		meanVal[axisTab[2] - 1] = (mean[2]) / nbrOfPts;

		*mean = (*mean) / nbrOfPts;
		mean[1] = (mean[1]) / nbrOfPts;
		mean[2] = (mean[2]) / nbrOfPts;
		//working out the standard deviation
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			*stdDev += std::pow((localPos[3 * i] - *mean), 2);
			stdDev[1] += std::pow((localPos[3 * i + 1] - mean[1]), 2);
			stdDev[2] += std::pow((localPos[3 * i + 2] - mean[2]), 2);
		}
		stdDevVal[axisTab[0] - 1] = sqrt((*stdDev) / (nbrOfPts));
		stdDevVal[axisTab[1] - 1] = sqrt((stdDev[1]) / (nbrOfPts));
		stdDevVal[axisTab[2] - 1] = sqrt((stdDev[2]) / (nbrOfPts));

		fprintf(fd, " ,Mean\n");
		fprintf(fd, "%.12lf,%.12lf,%.12lf\n", meanVal[axisTab[0] - 1], meanVal[axisTab[1] - 1], meanVal[axisTab[2] - 1]);
		fprintf(fd, " ,Std dev\n");
		fprintf(fd, "%.12lf,%.12lf,%.12lf\n", stdDevVal[axisTab[0] - 1], stdDevVal[axisTab[1] - 1], stdDevVal[axisTab[2] - 1]);
		break;
	case 4:
		fprintf(fd, "Axis %d,Axis %d,Axis %d,Axis %d\n", axisTab[0], axisTab[1], axisTab[2], axisTab[3]);
		localPos = (double*)calloc(4 * nbrOfPts, sizeof(double));
		if (localPos == NULL) {
			fclose(fd);
			zygoLogWarn("processFifoData::calloc failed\n");
			free(path);
			return ALLOC_MEM_ERROR;
		}
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			pos1 = static_cast<double>((int)(memPtr[4 * i])) * positionScale;
			pos2 = static_cast<double>((int)(memPtr[4 * i + 1])) * positionScale;
			pos3 = static_cast<double>((int)(memPtr[4 * i + 2])) * positionScale;
			pos4 = static_cast<double>((int)(memPtr[4 * i + 3])) * positionScale;
			localPos[4 * i] = pos1;
			localPos[4 * i + 1] = pos2;
			localPos[4 * i + 2] = pos3;
			localPos[4 * i + 3] = pos4;
			*mean += pos1;
			mean[1] += pos2;
			mean[2] += pos3;
			mean[3] += pos4;
			fprintf(fd, "%.12lf,%.12lf,%.12lf,%.12lf\n", pos1, pos2, pos3, pos4);
		}
		// working out the mean
		meanVal[axisTab[0] - 1] = (*mean) / nbrOfPts;
		meanVal[axisTab[1] - 1] = (mean[1]) / nbrOfPts;
		meanVal[axisTab[2] - 1] = (mean[2]) / nbrOfPts;
		meanVal[axisTab[3] - 1] = (mean[3]) / nbrOfPts;


		*mean = (*mean) / nbrOfPts;
		mean[1] = (mean[1]) / nbrOfPts;
		mean[2] = (mean[2]) / nbrOfPts;
		mean[3] = (mean[3]) / nbrOfPts;
		//working out the standard deviation
		for (uint32_t i = 0; i < nbrOfPts; i++) {
			*stdDev += std::pow((localPos[4 * i] - *mean), 2);
			stdDev[1] += std::pow((localPos[4 * i + 1] - mean[1]), 2);
			stdDev[2] += std::pow((localPos[4 * i + 2] - mean[2]), 2);
			stdDev[3] += std::pow((localPos[4 * i + 3] - mean[3]), 2);
		}
		stdDevVal[axisTab[0] - 1] = sqrt((*stdDev) / (nbrOfPts));
		stdDevVal[axisTab[1] - 1] = sqrt((stdDev[1]) / (nbrOfPts));
		stdDevVal[axisTab[2] - 1] = sqrt((stdDev[2]) / (nbrOfPts));
		stdDevVal[axisTab[3] - 1] = sqrt((stdDev[3]) / (nbrOfPts));

		fprintf(fd, " ,Mean\n");
		fprintf(fd, "%.12lf,%.12lf,%.12lf,%.12lf\n", meanVal[axisTab[0] - 1], meanVal[axisTab[1] - 1], meanVal[axisTab[2] - 1], meanVal[axisTab[3] - 1]);
		fprintf(fd, "; Std dev\n");
		fprintf(fd, "%.12lf,%.12lf,%.12lf,%.12lf\n", stdDevVal[axisTab[0] - 1], stdDevVal[axisTab[1] - 1], stdDevVal[axisTab[2] - 1], stdDevVal[axisTab[3] - 1]);
		break;
	default:
		printf("Bad number of axis, exiting\n");
		free(path);
		fclose(fd);
		return BAD_ARG_VALUE;
		break;
	}

	free(localPos);
	free(path);
	fclose(fd);
	return RET_SUCCESS;
}
int configureFifoFlyscan(fifoParam &param, uint32_t* startAdress, uint8_t* axisTab, uint32_t* sizeOfTab, int32_t* ret_code, bool mode) {
	int nAxis = 0, ctr = 0, tab[4] = { -1,-2,-3,-4 }, ftab[4] = { 0,0,0,0 }, tablen = 4, k = 0;
	
	if (checkLimits(*sizeOfTab, 1, 4)) {
		zygoLogWarn("bad number of axes\n");
		return BAD_AXIS_VALUE;
	}
	for (int i = 0; i < tablen; i++) {
		zygoLogInfo("Checking if axis value %u in the tab is corrrect\n", i);
		if (!checkLimits((uint32_t)axisTab[i], 1, 4)) {
			tab[ctr] = axisTab[i];
			ctr++;
			for (uint8_t j = 0; j < i; j++)
			{
				if (tab[j] == tab[i]) {
					zygoLogInfo("2 identical axis. Deleting one\n");
					ctr--;
					tab[i] = -i;
				}
			}
		}
		else
		{
			zygoLogWarn("%d is not a correct axis value. Skiping this axis\n", axisTab[i]);
		}
	}
	*sizeOfTab = ctr;
	zygoLogInfo("Fifo flyscan is configured on %d axis(es). They are: \n", ctr);
	axisTab[0] = 0;
	axisTab[1] = 0;
	axisTab[2] = 0;
	axisTab[3] = 0;
	for (int j = 0; j < tablen; j++) {
		if (tab[j] > 0) {
			zygoLogInfo("axis %d, \n", tab[j]);
			ftab[k] = tab[j];
			axisTab[k] = tab[j];
			k++;
		}
	}
	if (k == 0) {
		zygoLogWarn("No axis has been given to fifo flyscan config\n");
		*ret_code = RET_FAILED;
		return RET_FAILED;
	}
	/*
	if ((param->acqTime < 1e-6)) {
		// this mean acquisition time has not been given so we need to infer it from
		//other parameters
		param->acqTime = ((static_cast<double>(param->nbrPts)) / (static_cast<double>(param->freq))) * 1e3; // acquisition time in ms
	}
	if ((param->nbrPts < 0.1)) {
		// this mean the number of points has not been given so we need to infer it from the
		//other parameter
		param->nbrPts = (uint32_t)((static_cast<double>(param->acqTime * 1e-3)) * (static_cast<double>(param->freq)));
	}
	if ((param->freq < 0.1)) {
		// this mean frequency has not been given so we need to infer it from the
		//other parameter
		param->freq = ((static_cast<double>(param->nbrPts)) / (static_cast<double>(param->acqTime * 1e-3)));
	}
	*/
	if (!mode) {
		zygoLogInfo("\n FIFO Flyscan configuration: Freq: %u Hz \t Nbr_of_points: %u \t acquisition_time: %f ms\n", param.freq, param.nbrPts, param.acqTime);
		zygoLogInfo("%u,%u,%u,%u is sent to fifo flyscan\n ", ftab[0], ftab[1], ftab[2], ftab[3]);
		if (return_code = fifoFlyscan(param, startAdress, ctr, ret_code, ftab[0], ftab[1], ftab[2], ftab[3])) {
			zygoLogWarn("FIFO flyscan configuration failed\n");
			return return_code;
		}
	}
	else {
		zygoLogInfo("\n FIFO Flyscan configuration: Freq: %f Hz \t Nbr_of_points: INFINITE \t acquisition_time: UNKNOW ms\n", param.freq);
		zygoLogInfo("%u,%u,%u,%u is sent to fifo flyscan\n ", ftab[0], ftab[1], ftab[2], ftab[3]);
		if (return_code = manualFifoFlyscan(param, startAdress, ctr, ret_code, ftab[0], ftab[1], ftab[2], ftab[3])) {
			zygoLogWarn("manual FIFO flyscan configuration failed\n");
			return return_code;
		}

	}
	return RET_SUCCESS;
}
int fifoFlyscan(fifoParam param, uint32_t* startAddress, uint8_t nbrAxis, int32_t* ret_code, ...) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0, pos = 0;
	uint8_t* axisPtr;
	va_list argPtr;
	axisPtr = (uint8_t*)calloc(nbrAxis, sizeof(uint8_t));
	zygoLogInfo("setting up FIFO flyscan... %u\n", param.freq);
	va_start(argPtr, ret_code);
	for (int i = 0; i < nbrAxis; i++) {
		axisPtr[i] = va_arg(argPtr, uint8_t);
	}
	//1- Disable SCLK Timer
	if (return_code = disableSampleTimer(Axes::Axis_3, SCLK::SCLK0))
	{
		zygoLogWarn("disableSampleTimer failed !  \n");
		return return_code;
	}
	//2- Reset all axis and wait for reset to complete
	for (uint8_t i = 0; i < nbrAxis; i++) {
		if (return_code = resetAxis(static_cast<Axes>(axisPtr[i])))
		{
			zygoLogWarn("resetAxis failed !  \n");
			return return_code;
		}
	}
	// 3- enable sampling timer
	if (return_code = enableSampling(Axes::Axis_3, param.freq, SCLK::SCLK0))
	{
		zygoLogWarn("enableSampling failed !  \n");
		return return_code;
	}//convert to MHz
	
	// 4- check if new data is avalaible and Read FIFO position from all axes
	//startAddress = (uint32_t*)calloc(param.nbrPts * nbrAxis * 1.5, sizeof(int));
	zygoLogInfo("size is: %u, axis number is %u\n", param.nbrPts, nbrAxis);

	int ctr = 0;
	uint32_t h = 0;
	for (uint32_t i = 0; i < (param.nbrPts); i++) {
		
		while (!(isFifoDavBitSet(AXIS3))) {
			ctr++;
			if (ctr > 1500){
				free(axisPtr);
				return NO_FIFO_DATA_AV;
			}

		};
		ctr =0;
		for (uint8_t j = 0; j < nbrAxis; j++) {
			readFifoPosition(static_cast<Axes>(axisPtr[j]), &pos);
			startAddress[h] = pos;
			h++;
		}
	}
	// 5-disable sclk timer
	if (return_code = disableSampleTimer(Axes::Axis_3, SCLK::SCLK0))
	{
		zygoLogWarn("disableSampleTimer failed !  \n");
		return return_code;
	}
	//6-verify the FIFO overflow bit
	for (uint32_t i = 0; i < nbrAxis; i++) {
		if (isFifoOvfBitSet(static_cast<Axes>(axisPtr[i]))) {
			zygoLogWarn("some data samples could have been missed on axis %d. The frequency must be decreased\n", axisPtr[i]);
			//return return_code;
			*ret_code = FIFO_OVERLAP_ERR_CODE;
		}
		else
			*ret_code = RET_SUCCESS;
	}
	free(axisPtr);
	return RET_SUCCESS;
}

//*/
int manualFifoFlyscan(fifoParam& param, uint32_t* startAddress, uint8_t nbrAxis, int32_t* ret_code, ...) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0, pos = 0;
	uint8_t* axisPtr;
	va_list argPtr;
	axisPtr = (uint8_t*)calloc(nbrAxis, sizeof(uint8_t));
	if(axisPtr == NULL) {
		return BAD_ARG_POINTER;
	}
	zygoLogInfo("setting up FIFO flyscan...\n");
	va_start(argPtr, ret_code);
	for (int i = 0; i < nbrAxis; i++) {
		axisPtr[i] = va_arg(argPtr, uint8_t);
	}
	//1- Disable SCLK Timer
	if (return_code = disableSampleTimer(Axes::Axis_3, SCLK::SCLK0))
	{
		zygoLogWarn("disableSampleTimer failed !  \n");
		free(axisPtr);
		return return_code;
	}
	//2- Reset all axis and wait for reset to complete
	for (uint8_t i = 0; i < nbrAxis; i++) {
		if (return_code = resetAxis(static_cast<Axes>(axisPtr[i])))
		{
			zygoLogWarn("resetAxis failed !  \n");
			free(axisPtr);
			return return_code;
		}
	}
	// 3- enable sampling timer
	if (return_code = enableSampling(Axes::Axis_3, param.freq, SCLK::SCLK0))
	{
		zygoLogWarn("enableSampling failed !  \n");
		free(axisPtr);
		return return_code;
	}//convert to MHz
	// 4- check if new data is avalaible and Read FIFO position from all axes
	zygoLogInfo("size is unlimmited, axis number is %u\n", nbrAxis);
	// 5-disable sclk timer
	/*
	if (return_code = sampleVmePosition(AXIS3))
	{
		zygoLogWarn("sampleVmePosition failed !  \n");
		return return_code;
	}
	*/
	//startAddress = (uint32_t*)calloc(30000, sizeof(int));
	int ctr = 0;
	size_t h = 0;
	for (;;) {

		dwWaitResult = WaitForSingleObject( //wait for the main thread to sent an event
			stopReadPositionEvent, // event handle
			0);    // If dwMilliseconds is zero, the function does not enter a wait state if the object is not signaled; it always returns immediately

		switch (dwWaitResult)
		{
			// Event object was signaled
		case WAIT_OBJECT_0:
			//free(startAddress);
			zygoLogInfo("stopReadPositionEvent received \n");
			free(axisPtr);
			param.nbrPts = h;
			return RET_SUCCESS;
			// An error occurred
		default:

			while (!(isFifoDavBitSet(AXIS3))) {
				ctr++;
				if (ctr > 1500) {
					free(axisPtr);
					return NO_FIFO_DATA_AV;
				}
			}
			ctr =0;
			if (h > (MAX_HEAP_SIZE - 1)) {
				return_code = MAX_HEAP_SIZE_REACH	;
				param.nbrPts = h;
				free(axisPtr);
				return return_code;
			}
			for (uint8_t j = 0; j < nbrAxis; j++) {
				readFifoPosition(static_cast<Axes>(axisPtr[j]), &pos);
				startAddress[h] = pos;
				h++;
			}
			break;
		}
	}
	//6-verify the FIFO overflow bit
	for (uint32_t i = 0; i < nbrAxis; i++) {
		if (isFifoOvfBitSet(static_cast<Axes>(axisPtr[i]))) {
			zygoLogWarn("some data samples could have been missed on axis %d. The frequency must be decreased\n", axisPtr[i]);
			//return return_code;
			*ret_code = FIFO_OVERLAP_ERR_CODE;
		}
		else
			*ret_code = RET_SUCCESS;
	}
	free(axisPtr);
	return RET_SUCCESS;
}
//*/
bool isFifoDavBitSet(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zStat1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	if ((uint_vme_data & 0x400))
		return true;
	return false;
}
bool isFifoOvfBitSet(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zStat1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
	}
	if ((uint_vme_data & 0x200))
		return true;
	return false;
}

int deconfigureFlycsan(uint8_t axesNbr) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[AXIS1 - 1], zDiagFFTCtrl);
	if (axesNbr > 1) {
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
	}

	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zDiagFFTCtrl);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	return RET_SUCCESS;
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
int configureFlyscan(uint8_t nbrAxis, double freqHz, uint8_t trig) {
	/*'
		'4 X 8kSamples of 32 bit position values at FULL resolution of lambda/4096/8
		' returns false if unsuccessful
		' sample freq in mHz 10MHZ is max
		' trigger type: instant = 0
		'               P2D_In = 1
		
	*/
	short rdVal = 0, sclkVal = 0;
	uint32_t ctr = 0;
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	int ramAxisAddr = 0x0;
	if (checkLimits(nbrAxis, 1, 4)){
		zygoLogWarn("%s %s %d: bad number of axes\n");
		return BAD_AXIS_VALUE;
	}
	if (freqHz < 300) {
		zygoLogWarn("Frequency can not be lesser than 300Hz\n");
		return LESSER_THAN_MIN_FREQUENCY;
	}
	/* Check if RAM is busy*/
	zygoLogInfo("setting up flyscan...\n");
	if (checkLimits(nbrAxis, 1, 4)) {
		zygoLogWarn("Bad axis value\n");
		return BAD_AXIS_VALUE;
	}
	do {
		ctr++;
		if (ctr > 1500)
		{
			zygoLogWarn("\nRAM has been busy for more than %d stamps time \n exiting... \n\n", ctr);
			return ZYGO_RAM_BUSY_FOR_TOO_LONG;
		}
	} while (isRamBusy());

	if (return_code = enableSampling(Axes::Axis_3, freqHz * 1e-6, SCLK::SCLK0))
	{
		zygoLogWarn("disableSampleTimer failed !  \n");
		return return_code;
	}
	if (nbrAxis <= 2)
		uint_vme_data = 0x8000;
	else
		uint_vme_data = 0x9000;
	//Setup axis 1 and 2
	switch (nbrAxis)
	{
	case 1:
		uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zDiagFFTCtrl);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		uint_vme_address = ADD(BASE_ADDRESS[AXIS1 - 1], zDiagFFTCtrl);
		uint_vme_data = 0;
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		break;
	default:
		uint_vme_address = ADD(BASE_ADDRESS[AXIS1 - 1], zDiagFFTCtrl);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		//Setup axis 3 and 4
		uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zDiagFFTCtrl);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}

		break;
	}

	//Option to start acquire immediately
	if (trig) {
		zygoLogInfo("Starting acquisition...\n");
		if (return_code = startAquisition(nbrAxis)) {
			zygoLogWarn("disableSampleTimer failed !  \n");
			return return_code;
		}
	}
	return RET_SUCCESS;
}
/// <summary>
/// Start acquisition
/// </summary>
/// <param name="dev"></param>
/// <param name="nbrAxis"></param>
/// <returns></returns>
int startAquisition(uint8_t nbrAxis) {
	uint32_t uint_vme_data = 0x8, uint_vme_address = 0;

	//Start acquisition on axis 1
	zygoLogInfo("Starting RAM data acquisition...\n");

	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestCmd1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	if (nbrAxis >= 2) {
		//Start acquisition on axis 3
		uint_vme_address = ADD(BASE_ADDRESS[AXIS1 - 1], zTestCmd1);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
	}
	return RET_SUCCESS;
}

int stopAquisition(uint8_t nbrAxis) {
	uint32_t uint_vme_data = 0x10, uint_vme_address = 0;
	return_code = RET_SUCCESS;
	stopReadPositionEvent = CreateEvent(
		NULL,               // default security attributes
		TRUE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("lemoIN1Event")  // object name
	);
	if (stopReadPositionEvent == NULL) {
		zygoLogWarn("CreateEvent failed in %s", __FUNCTION__);
		perror("");
		return errno;
	}
	if (!SetEvent(stopReadPositionEvent)) {
		zygoLogWarn("SetEvent failed in %s", __FUNCTION__);
		perror("");
		return errno;
	}
	//Stop acquisition on axis 1 
	zygoLogInfo("Altering data acquisition...\n");

	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestCmd1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
	}
	if (nbrAxis >= 2) {
		//Stop acquisition on axis 3 
		uint_vme_address = ADD(BASE_ADDRESS[AXIS1 - 1], zTestCmd1);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
		{
			{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
		}
	}
	return return_code;
}
/// <summary>
/// The function allocate the specified memory space on Windows
/// </summary>
/// <param name="mem_size"> the size in bytes(max val is 10240)</param>
/// <returns>
/// -1 if unsuccessful
/// 0 else
/// </returns>
uint32_t* allocateMemSpace(uint32_t mem_size) {
	zygoLogInfo("Allocating Windows Memory space...\n");
	if (checkLimits(mem_size, 0, 1024 * 70))
		return nullptr;
	return (uint32_t*)calloc((uint32_t)(mem_size), sizeof(uint32_t));

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
int readModifyWrite(const char* accessMode, uint32_t uint_vme_address,
	uint32_t uint_vme_data, uint8_t opCode) {
	uint32_t vme_data = 0;
	zygoLogInfo("ReadModifyWrite function executing...\n");
	if (return_code = readWrite(accessMode, uint_vme_address, &vme_data, READ)) {
		{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
	}
	switch (opCode)
	{
	case 0:
		vme_data &= (uint32_t)uint_vme_data;
		break;
	case 1:
		vme_data |= (uint32_t)uint_vme_data;
		break;
	case 2:
		vme_data += (uint32_t)uint_vme_data;
		break;
	default:
		break;
	}
	if (return_code = readWrite(accessMode, uint_vme_address, &vme_data, WRITE)) {
		{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
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
int getFlyscanData(uint32_t* startAddress_axis1, uint32_t* startAddress_axis3, uint32_t* nbrFlyscanAxis, uint32_t ramPagesNbr) {

	zygoLogInfo("Getting Flyscan data...\n");
	uint32_t uint_vme_address = 0, nbr_of_read = 0, ctr1[2] = { 0,0 }, ctr = 0, nbrAxis = 0;
	uint32_t ramPageAddr = 0;
	uint32_t* startAddress = 0;
	//get the value of Diag FFT RAM configuration register
	// Here we need only to know whether the user is going to make measurement on 
	// more than 2 axis or not, so 2 is our threshold
	uint_vme_address = ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS3 - 1]);
	if (checkLimits(ramPagesNbr, 1, NBR_RAM_PAGES)) {
		zygoLogWarn("ramPagesNbr is not in the requested range \n");
		return BAD_ARG_VALUE;
	}
	for (int k = 0; k < 2; k++) {
		if (return_code = readWrite("A24D16", uint_vme_address, &ramPageAddr, READ))
		{
			{zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code; }
		}
		if ((ramPageAddr & 0x9000) != 0x8000) { // check the 15th and the 12th bits of the loaded value
			if ((ramPageAddr & 0x9000) != 0x9000) {
				if (ctr < 1) {// to take into account the 2 cycles
					zygoLogInfo("Flyscan is not properly configured. RAM FFT Ctrl value is 0x%X\n", ramPageAddr);
					zygoLogWarn("Note the main axis is axis 3. If you're setting up flyscan for measurement only on 1 axis, you should configure it on the main axis \n");
					return RET_FAILED;
				}
			}
			else {
				ctr += 2;
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
			zygoLogWarn("Bad arguments serve to %s. The current configuration does not allow any of the pointer passed as argument to be null %s\n", __FUNCTION__);
			return BAD_ARG_POINTER;
		}
		nbrAxis = 2;
	}
	else {
		if ((!startAddress_axis3)) {
			zygoLogWarn("Bad arguments serve to %s. Axis 3 is the main axis.The corresponding argumentis not allowed to be null\n", __FUNCTION__);
			return BAD_ARG_POINTER;
		}
		nbrAxis = 1;
	}
	zygoLogInfo("Starting acquisition on %d axis \n", ctr);
	if (return_code = startAquisition(1))
	{
		zygoLogWarn("startAquisition failed !  \n");
		return return_code;
	}
	ctr=0;
	do {
		if (ctr > 1500)
		{
			zygoLogWarn("RAM has been busy for more than %ds stamps time \n exiting... \n", ctr);
			return ZYGO_RAM_BUSY_FOR_TOO_LONG;
		}
		Sleep(1);
		ctr++;
	} while (isRamBusy());

	uint_vme_address = ADD(zDiagFFTRamData, BASE_ADDRESS[AXIS3 - 1]);
	ramPageAddr = ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS3 - 1]);
	startAddress = startAddress_axis3;
	ctr = ctr1[0];
	for (uint32_t k = 0; k < nbrAxis; k++) {
		for (int i = 0; i < ramPagesNbr; i++) {
			zygoLogInfo("-----------------------Page %u: Start address 0x%p ------------------------ \n", i + 1, startAddress);
			if (return_code = vme_A24DMA_D32_read(dev, uint_vme_address, startAddress, NBR_SAMP_PER_PAGE, &nbr_of_read))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
				return return_code; 
			}
			else zygoLogInfo("%d 32bits words read from 0x%x  \n", nbr_of_read, uint_vme_address);
			//request the next page
			if (return_code = readWrite("A24D16", ramPageAddr, &ctr, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
				return return_code; 
			}
			// Shift to the next page
			startAddress += nbr_of_read;
			ctr++;
			zygoLogInfo("-----------------------Page %u: End address 0x%p ------------------------ \n", i + 1, startAddress - 1);
			nbr_of_read = 0;
		}
		startAddress = startAddress_axis1;
		uint_vme_address = ADD(zDiagFFTRamData, BASE_ADDRESS[AXIS1 - 1]);
		ramPageAddr = ADD(zDiagFFTCtrl, BASE_ADDRESS[AXIS1 - 1]);
		ctr = ctr1[1];
	}
	deconfigureFlycsan(*nbrFlyscanAxis);
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
bool isRamBusy() {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	/* Check if RAM is busy*/
	zygoLogInfo("Checking whether or not the RAM is busy...\n");
	uint_vme_address = BASE_ADDRESS[AXIS3 - 1] + zTestStat1;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogInfo("Register %6X access Faillure !  \n", uint_vme_address);
		return TRUE;
	}

	if ((uint_vme_data & 0x400)) {
		zygoLogInfo("RAM is currently busy\n");
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
int setVmeIntVector(Axes axis, uint8_t IntVect) {
	uint32_t uint_vme_address = 0;
	zygoLogInfo("Setting VME interrupt vector %d...\n", IntVect);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zIntVector);				// Disable VME interrupts 
	if (checkLimits(IntVect, 0, 255) < 0)
		return BAD_ARG_VALUE;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, IntVect, 1))
	{
		zygoLogWarn("readModifyWrite failed !  \n");
		return return_code;
	}

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
int checkLimits(int num2check, int minVal, int maxVal) {
	if (minVal > maxVal) {
		zygoLogWarn("min>max(%d>%d) => Permuting min and max value\n", minVal, maxVal);
		minVal = minVal + maxVal;
		maxVal = minVal - maxVal;
		minVal = minVal - maxVal;
	}
	if (num2check < minVal || num2check > maxVal) {
		zygoLogInfo("\tBad Value\n");
		zygoLogWarn("\tthe range allowed is %d to %d while the one recieve is %d\n", minVal, maxVal, num2check);
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
int setVmeIntLevel(Axes axis, uint8_t IntLevel) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Setting VME interrupt level %d...\n", IntLevel);
	if (checkLimits(IntLevel, INT_LEVEL0, INT_LEVEL7) < 0)
		return BAD_ARG_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zIntVector);				// Disable VME interrupts 
	uint_vme_data = ((uint32_t)IntLevel) << 8;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, 1))
	{
		zygoLogWarn("readModifyWrite failed !  \n");
		return return_code;
	}
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
int disableGlobalInterrupt(Axes axis) {
	uint32_t uint_vme_address = 0;
	zygoLogInfo("Disabling VME global interrupt...\n");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab1);
	// Disable VME interrupts 
	if (return_code = readModifyWrite("A24D16", uint_vme_address, 0x7FFF, 0))
	{
		zygoLogWarn("readModifyWrite failed !  \n");
		return return_code;
	}
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
int enableVmeInterruptBit(Axes axis, uint16_t intNumber) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Enabling VME interrupt bit %d...\n", intNumber);
	if (checkLimits(intNumber, MIN_INT_NBR, MAX_INT_NBR) < 0)
		return BAD_ARG_VALUE;
	if (intNumber < VME_EXT_FLAG_SAMPLE_ERR_INT)
	{
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab0);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		switch (intNumber)
		{
		case CEC_ERR_INT:
			uint_vme_data |= 0x8000;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case PHASE_NOISE_ERR_INT:
			uint_vme_data |= 0x4000;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case ACCELERATION_ERR_INT:
			uint_vme_data |= 0x2000;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case MEAS_SIG_GLITCH_ERR_INT:
			uint_vme_data |= 0x1000;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case MEAS_SIG_DROP_ERR_INT:
			uint_vme_data |= 0x800;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case SSI_MAX_LIM_ERR_INT:
			uint_vme_data |= 0x400;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case MEAS_SIG_SAT_ERR_INT:
			uint_vme_data |= 0x200;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case MEAS_SIG_MIS_ERR_INT:
			uint_vme_data |= 0x100;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case OV_TMP_ERR_INT:
			uint_vme_data |= 0x80;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case FPGA_SYNC_ERR_INT:
			uint_vme_data |= 0x40;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case RES_FAIL_ERR_INT:
			uint_vme_data |= 0x20;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case RES_COMP_ERR_INT:
			uint_vme_data |= 0x10;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case REF_PLL_ERR_INT:
			uint_vme_data |= 0x8;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case REF_SIG_MIS_ERR_INT:
			uint_vme_data |= 0x4;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case WRT_ERR_INT:
			uint_vme_data |= 0x2;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case PWR_ERR_INT:
			uint_vme_data |= 0x1;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		default:
			break;
		}
	}
	else if ((intNumber >= VME_EXT_FLAG_SAMPLE_ERR_INT) && (intNumber < PROC_INIT_BSY_ERR_INT))
	{
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab1);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		switch (intNumber)
		{
		case VME_EXT_FLAG_SAMPLE_ERR_INT:
			uint_vme_data |= 0x100;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case P32_POS_OV_ERR_INT:
			uint_vme_data |= 0x10;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case VME32_POS_OV_ERR_INT:
			uint_vme_data |= 0x8;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case VME37_POS_OV_ERR_INT:
			uint_vme_data |= 0x4;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case USR_VEL_ERR_INT:
			uint_vme_data |= 0x2;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case VEL_ERR_INT:
			uint_vme_data |= 0x1;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		default:
			zygoLogInfo(" Unknow interrupt number\n");
			break;
		}
	}
	else
	{
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab2);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		switch (intNumber)
		{
		case PROC_INIT_BSY_ERR_INT:
			uint_vme_data |= 0x8000;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case PROC_FAIL_ERR_INT:
			uint_vme_data |= 0x4000;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case BIAS_SUPPLY_ERR_INT:
			uint_vme_data |= 0x2000;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case WRT_PROTECT_ERR_INT:
			uint_vme_data |= 0x1000;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case SIG_MAX_ERR_INT:
			uint_vme_data |= 0x80;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case SIG_MIN_ERR_INT:
			uint_vme_data |= 0x40;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case BIAS_CALC_COMP_INT:
			uint_vme_data |= 0x20;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case BIAS_ERR_INT:
			uint_vme_data |= 0x10;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case APD_DC_ERR_INT:
			uint_vme_data |= 0x8;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case BIAS_SET_ERR_INT:
			uint_vme_data |= 0x4;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case APD_FAIL_ERR_INT:
			uint_vme_data |= 0x2;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
			break;
		case APD_TMP_ERR_INT:
			uint_vme_data |= 0x1;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				return return_code;
			}
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
int disableVmeInterruptBit(Axes axis, uint16_t intNumber) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Disabling VME interrupt bit %d...\n", intNumber);
	if (intNumber < VME_EXT_FLAG_SAMPLE_ERR_INT)
	{
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab0);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
		switch (intNumber)
		{
		case CEC_ERR_INT:
			uint_vme_data &= 0x7FFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case PHASE_NOISE_ERR_INT:
			uint_vme_data &= 0xBFFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case ACCELERATION_ERR_INT:
			uint_vme_data &= 0xDFFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case MEAS_SIG_GLITCH_ERR_INT:
			uint_vme_data &= 0xEFFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case MEAS_SIG_DROP_ERR_INT:
			uint_vme_data &= 0xF7FF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case SSI_MAX_LIM_ERR_INT:
			uint_vme_data &= 0xFBFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case MEAS_SIG_SAT_ERR_INT:
			uint_vme_data &= 0xFDFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case MEAS_SIG_MIS_ERR_INT:
			uint_vme_data &= 0xFEFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case OV_TMP_ERR_INT:
			uint_vme_data &= 0xFF7F;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case FPGA_SYNC_ERR_INT:
			uint_vme_data &= 0xFFBF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case RES_FAIL_ERR_INT:
			uint_vme_data &= 0xFFDF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case RES_COMP_ERR_INT:
			uint_vme_data &= 0xFFEF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case REF_PLL_ERR_INT:
			uint_vme_data &= 0xFFF7;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case REF_SIG_MIS_ERR_INT:
			uint_vme_data &= 0xFFFB;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case WRT_ERR_INT:
			uint_vme_data &= 0xFFFD;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case PWR_ERR_INT:
			uint_vme_data &= 0xFFFE;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		default:
			break;
		}
	}
	else if ((intNumber >= VME_EXT_FLAG_SAMPLE_ERR_INT) && (intNumber < PROC_INIT_BSY_ERR_INT))
	{
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab1);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
		switch (intNumber)
		{
		case VME_EXT_FLAG_SAMPLE_ERR_INT:
			uint_vme_data &= 0xFEFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case P32_POS_OV_ERR_INT:
			uint_vme_data &= 0xFFEF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case VME32_POS_OV_ERR_INT:
			uint_vme_data &= 0xFFF7;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case VME37_POS_OV_ERR_INT:
			uint_vme_data &= 0xFFFB;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case USR_VEL_ERR_INT:
			uint_vme_data &= 0xFFFD;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case VEL_ERR_INT:
			uint_vme_data &= 0xFFFE;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		default:
			printf(" Unknow interrupt number\n");
			break;
		}
	}
	else
	{
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEIntEnab2);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
		switch (intNumber)
		{
		case PROC_INIT_BSY_ERR_INT:
			uint_vme_data &= 0x7FFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case PROC_FAIL_ERR_INT:
			uint_vme_data &= 0xBFFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case BIAS_SUPPLY_ERR_INT:
			uint_vme_data &= 0xDFFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case WRT_PROTECT_ERR_INT:
			uint_vme_data &= 0xEFFF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case SIG_MAX_ERR_INT:
			uint_vme_data &= 0xFF7F;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case SIG_MIN_ERR_INT:
			uint_vme_data &= 0xFFBF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case BIAS_CALC_COMP_INT:
			uint_vme_data &= 0xFFDF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case BIAS_ERR_INT:
			uint_vme_data &= 0xFFEF;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case APD_DC_ERR_INT:
			uint_vme_data &= 0xFFF7;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case BIAS_SET_ERR_INT:
			uint_vme_data &= 0xFFFB;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case APD_FAIL_ERR_INT:
			uint_vme_data &= 0xFFFD;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
			break;
		case APD_TMP_ERR_INT:
			uint_vme_data &= 0xFFFE;
			if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
			}
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
int resetAxis(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCmd);
	uint_vme_data = 0x20;
	zygoLogInfo("Reseting axis %u...\n", axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogInfo("Register 0x%6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	if (return_code = waitResetComplete(axis))
	{
		zygoLogWarn("waitResetComplete failed !  \n");
		return return_code;
	}	// Wait for reset complete on the main axis
	return RET_SUCCESS;
}
/// <summary>
/// This function is used after an resetAxis to wait for the reset to complete
/// </summary>
/// <param name="dev">axis</param>
/// <param name="axis">
/// axis to wait reset completion on
/// </param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int waitResetComplete(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0, ct = 0;
	zygoLogInfo("Waiting for reset to complete on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zStat1);
	while (!(uint_vme_data & 0x0001))	// Wait for reset complete 
	{
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
		ct++;
		if (ct > 0xFFFFFFF1) {

			zygoLogWarn("Failed to reset axis %d !  \n", axis);
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
int initSisBoards(bool verboseLevel) {

	/******************************************************************************************************************************/
	/* VME Master Create, Open and Setup                                                                                          */
	/******************************************************************************************************************************/
	// device open, use the first device if present

	char short_data = 0;
	uint32_t  nof_found_sis1100_devices = 0;
	uint32_t sis3100_data = 0;
	short sis3100_add = 0;
	SIS1100W_STATUS stat;
	
	if(verboseLevel)
		INFO_LEVEL = 1;
	else
		INFO_LEVEL = 0;

	zygoLogFatal_key = CreateMutex(NULL, FALSE, NULL);
	if (!zygoLogFatal_key)
	{
		fprintf(stderr, "failed to create zygoLogFatal mutex key %d\n", GetLastError());
		perror("zygoLogFatal_key: ");
		exit(-1);
	}
	zygoLogInfo_key = CreateSemaphore(NULL, 1,1, NULL);
	if (!zygoLogInfo_key)
	{
		fprintf(stderr, "failed to create zygoLogInfo semaphore key %d\n", GetLastError());
		perror("zygoLogInfo_key: ");
		exit(-1);
	}
	zygoLogWarn_key = CreateMutex(NULL, FALSE, NULL);
	if (!zygoLogWarn_key)
	{
		fprintf(stderr, "failed to create zygoLogWarn mutex key %d\n", GetLastError());
		perror("zygoLogWarn_key: ");
		exit(-1);
	}
	rw_key = CreateMutex(NULL, FALSE, NULL);
	if (!rw_key)
	{
		fprintf(stderr, "failed to create rw mutex key %d\n", GetLastError());
		perror("rw_key: ");
		exit(-1);
	}

	ReleaseSemaphore(zygoLogInfo_key, 1, NULL);
	ReleaseMutex(zygoLogWarn_key);
	ReleaseMutex(zygoLogFatal_key);

	sprintf_s(PCI_VME_GATEWAY_FIRMWARE_VERSION, 10, "UNKNOW\0");
	sprintf_s(PCI_VME_GATEWAY_BOARD_VERSION, 10,"UNKNOW\0");
	sprintf_s(str, 10, "UNKNOW\0");
	sprintf_s(ZYGO_BOARD_VERSION, 10, "UNKNOW\0");
	sprintf_s(ZYGO_BOARD_SN, 10, "UNKNOW\0");
	sprintf_s(ZYGO_FIRMWARE_VERSION, 10, "UNKNOW\0");
	sprintf_s(ZYGO_BOARD_TYPE, 10, "UNKNOW\0");
	
	zygoLogInfo("Setting up SIS boards...\n");
	zygoLogInfo("Scanning connected SIS' PCIe card...\n");
	stat = sis1100w_Find_No_Of_sis1100(&nof_found_sis1100_devices);
	if (stat != Stat1100Success) {
		zygoLogInfo("Error while connected SIS' PCIe card\n");
		zygoLogInfo("\tNo valid device were suplied or a Null argument were suplied\n");
		zygoLogWarn("\tError in 'sis1100w_Find_No_Of_sis1100': %d\n", stat);
		return stat;
	}

	if (nof_found_sis1100_devices == 0) {
		zygoLogWarn("No SIS' PCIe card found, exiting...\n");
		return NO_DEVICE_FOUND;
	}

	zygoLogInfo("%u SIS' PCIe card found\n", nof_found_sis1100_devices);
	zygoLogInfo("Connecting to the first device...\n");
	stat = sis1100w_Get_Handle_And_Open(0, dev); // 
	if (stat != Stat1100Success) {
		zygoLogInfo("Connection to SIS' PCIe card failed\n");
		zygoLogWarn("\tError in 'sis1100w_Get_Handle_And_Open': %d\n", stat);
		return stat;
	}
	zygoLogInfo("Connection successful\n");
	/*
	printf("Getting SIS' PCIe card infos...\n");
	if ((stat = sis1100w_Get_IdentVersion(dev, &nof_found_sis1100_devices)) != Stat1100Success) {
		printf("Failed TO GET SIS' PCIe card\n");
		printf("\tError in 'sis1100w_Get_IdentVersion': %d\n", stat);
	}*/
	zygoLogInfo("Initializing the SIS' PCIe card...\n");
	stat = sis1100w_Init(dev, 0);
	if (stat != Stat1100Success) {
		zygoLogInfo("first SIS' PCIe card initialization failed...\n");
		zygoLogWarn("\tError in 'sis1100w_Init': %d\n", stat);
		return stat;
	}
	zygoLogInfo("first SIS' PCIe card initialized\n");
	zygoLogInfo("Initializing VME/PCI gateway...\n");
	stat = sis1100w_Init_sis3100(dev, 0);
	if (stat != Stat1100Success) {
		zygoLogInfo("VME/PCI gateway initialization failed...\n");
		zygoLogWarn("\tError in 'sis1100w_Init_sis3100': %d\n", stat);
		return stat;
	}

	zygoLogInfo("VME/PCI gateway initialized\n");

	zygoLogInfo("Reading VME/PCI card Identifier...\n");
	sis3100_add = 0x0;
	if ((stat = sis1100w_sis1100_Control_Read(dev, sis3100_add, &sis3100_data)) != Stat1100Success) {
		zygoLogWarn("\tReading address %X of sis3100 card failed\n", sis3100_add);
		return stat;
	}
	zygoLogInfo("\t 0x0 data: %010X\n", sis3100_data);
	short_data = sis3100_data;
	switch ((int)short_data)
	{
	case 1:
		zygoLogInfo("\t PLI/PLX Interface\n");
		break;
	case 2:
		zygoLogInfo("\tVME Controler\n");
		break;
	case 3:
		zygoLogInfo("\tCAMAC/FERA Controller\n");
		break;
	case 4:
		zygoLogInfo("\tReadoutsystem mit LVD SCSI\n");
		break;
	case 0x82:
		zygoLogInfo("\tVME Initiator\n");
		break;
	default:
		break;
	}
	short_data = sis3100_data >> 8;
	zygoLogInfo("\t Hardware Version: %d\n", (int)short_data);
	short_data = sis3100_data >> 16; // error to be reviewed
	zygoLogInfo("\t Firmware type: %d\n", (int)short_data);
	short_data = sis3100_data >> 24; // error to be reviewed
	zygoLogInfo("\t Firmware Version: %d\n", (int)short_data);
	sprintf_s(PCI_VME_GATEWAY_FIRMWARE_VERSION, tabLen, "v%d", short_data);
	zygoLogInfo("Reading VME/PCI card Firmware Register version...\n");
	sis3100_add = 0x4;
	if ((stat = sis1100w_sis1100_Control_Read(dev, sis3100_add, &sis3100_data)) != Stat1100Success) {
		zygoLogInfo("\tReading address %X of sis3100 card failed\n", sis3100_add);
	}

	zygoLogInfo("\t 0x4 data: %010X\n", sis3100_data);

	zygoLogInfo("sis3100 card Frirmware Register version:\n");
	short_data = sis3100_data;
	zygoLogInfo("\t Firmware Version: %d\n", (int)short_data);
	short_data = sis3100_data >> 8;
	zygoLogInfo("\t Firmware type: %d\n", (int)short_data);
	short_data = sis3100_data >> 16; // error to be reviewed
	zygoLogInfo("\t Board version: %d\n", (int)short_data);
	sprintf_s(PCI_VME_GATEWAY_BOARD_VERSION, tabLen, "v%d", short_data);

	curPrecision = getPrecision();
	enableDoublePassInterferometer();// default to doublepass interferometer
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
int initZmiBoards() {
	short value = 0;
	bool queryBoard = false;
	char	ch_access_mode[16];
	bool* ledsStatus;
	uint32_t	vme_data = 0,
		uint_vme_address = 0,
		uint_vme_data = 0;
	uint32_t  uint_vme_data_buf[20];

	int return_code = 0;
	static bool enableResetFindsVelocity[] = { true, true, true, true };
	if (return_code = vmeSysReset())
	{
		zygoLogWarn("vmeSysReset failed !  \n");
		return RESET_ZYGO_FAILED;
	}
	Sleep(4000);
	memset(uint_vme_data_buf, 0, _countof(uint_vme_data_buf));
	uint_vme_data_buf[19] = '\0';
	zygoLogInfo("Initializing ZMI board... \n");
	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);

	zygoLogInfo("\n \n Base ADDRESS is 0x%06X\n\n", BASE_ADDRESS[0]);

	if (return_code = readWrite(ch_access_mode, BASE_ADDRESS[AXIS3 - 1], &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	//printf("%X\n", uint_vme_data_buf[1]);
	vme_data = uint_vme_data;
	uint_vme_data = vme_data >> 12;
	//printf("%d\n", uint_vme_data);
	switch (uint_vme_data)
	{
	case 0b1111:
		zygoLogInfo("\tZMI System type: ZMI 4004 / ZMI 1002 \n");
		memcpy(ZYGO_BOARD_TYPE, "ZMI 4004 / ZMI 1002", tabLen);
		break;
	case 0b0111:
		zygoLogInfo("\tZMI System type: ZMI 4104 \n");
		memcpy(ZYGO_BOARD_TYPE, "ZMI 4104", tabLen);
		break;
	case 0b1011:
		memcpy(ZYGO_BOARD_TYPE, "ZMI 4104C", tabLen);
		zygoLogInfo("\tZMI System type: %s\n", ZYGO_BOARD_TYPE);
		queryBoard = true;
		break;
	default:
		if (uint_vme_data < 13) {
			zygoLogInfo("\tZMI System type: ZMI 2002 series \n");
			memcpy(ZYGO_BOARD_TYPE, "ZMI 2002 series", tabLen);
		}
		else
			zygoLogInfo("\tZMI System type: UNKNOW \n");
		memcpy(ZYGO_BOARD_TYPE, "UNKNOW", tabLen);
		break;
	}
	if (!queryBoard) {
		zygoLogInfo("Either the bmeasurement board doesn't match with the one require by the library or you are getting incoherent data from your system\n");
		zygoLogInfo("This library has been developped to drive only the ZMI 4104C board\n");
		zygoLogWarn("Make sure your measurement board is the ZMI4104C one and if so, change the board position in the VME chassis\n");
		return RET_FAILED;
	}

	uint_vme_data = vme_data;

	if (uint_vme_data & 0x00000001)
		zygoLogInfo("\t[Power Ok] All on-board analog power supplies are operating properly\n");
	else
		zygoLogInfo("\t[Power Warning] Some on-board analog power supplies are not operating properly\n");


	if (uint_vme_data & 0x00000002)
		zygoLogInfo("\t[Ref_Sig OK] The reference fiber signal is plugged or the reference signal tree is present \n");
	else
		zygoLogInfo("\t[Ref_Sig Warning] Either the fiber signal isn't plugged or the reference signal tree is missing");


	if (uint_vme_data & 0x00000004)
		zygoLogInfo("\t[Ref_Tree_sig OK] The electrical reference tree input is present \n");
	else
		zygoLogInfo("\t[Ref_Tree_sig Warning] The electrical reference tree input is missing \n");

	if (uint_vme_data & 0x00000008)
		zygoLogInfo("\t[Ref_Fib_sig OK] The Optical reference fiber signal is present \n");
	else
		zygoLogInfo("\t[Ref_Fib_sig Warning] The Optical reference fiber signal is missing \n");

	if (uint_vme_data & 0x00000010)
		zygoLogInfo("\t[Ref_PLL OK] The PLL that generates the on-board system clock is operating properly \n");
	else
		zygoLogInfo("\t[Ref_PLL Warning] The PLL that generates the on-board system clock\n\t is not operating properly\n");

	if (uint_vme_data & 0x00000020)
		zygoLogInfo("\t[FPGA_DLL Locked] The master and slave FPGA are properly synchronized \n\tand the"
			" DLL in the FPGA is operating properly \n");
	else
		zygoLogInfo("\t[FPGA_DLL Warning] The master and slave FPGA are not synchronized\n");

	if (uint_vme_data & 0x00000040)
		zygoLogInfo("\t[FPGA_Temp Warning] The FPGA temperature exceeds the preset limit (+85°C)");
	else
		zygoLogInfo("\t[FPGA_Temp Ok] The FPGA temperature is good at all\n");

	if (uint_vme_data & 0x00000100)
		zygoLogInfo("\t[VME_IRQ_PENDING] An error is asserted in the VME Error Status register\n");

	uint_vme_data = 0;
	if (return_code = eepromRead(ADD(BASE_ADDRESS[AXIS3 - 1], zBdAxInf), &uint_vme_data, WRITE)) {
		zygoLogWarn("Faillure when running eepromRead\n");
		return EEPROM_READ_FAILED;
	}
	zygoLogInfo("The number of axes is %d \n", uint_vme_data);

	memset(uint_vme_data_buf, 0, sizeof(uint_vme_data_buf));
	ledsStatus = (bool*)calloc(5, sizeof(bool));
	if (ledsStatus == NULL) {
		return BAD_ARG_POINTER;
	}
	if (return_code = getLedsStatus(ledsStatus)) {
		zygoLogWarn("Faillure when running getLedsStatus\n");
		free(ledsStatus);
		return RET_FAILED;
	}
	for (int i = 0; i < 4; i++) {
		uint_vme_data = 0;
		if (ledsStatus[i])
			zygoLogInfo("\t[Meas_Sig OK] The measurement signal is present on Axis %d\n", i + 1);
		else
			zygoLogInfo("\t[Meas_Sig Warning] The measurement signal is missing on Axis %d\n", i + 1);
	}

	if (uint_vme_data & 0x00000001)
		zygoLogInfo("\t[RST OK] Reset Complete\n");

	zygoLogInfo("\nBoard charracteristics... \n");
	for (int i = 0; i < 19; i++)
	{
		uint_vme_data = 0;
		if (return_code = eepromRead(i, &uint_vme_data, 2)) {
			zygoLogWarn("Faillure when running getLedsStatus\n");
			free(ledsStatus);
			return return_code;
		}
		uint_vme_data_buf[i] = uint_vme_data;
	}

	zygoLogInfo("\tBoard data version format: %u \n", uint_vme_data_buf[0]);
	zygoLogInfo("\tSize of Board Data Block: %u \n", uint_vme_data_buf[1]);
	zygoLogInfo("\tDate of manufacture: %u/%u/%u \n", uint_vme_data_buf[2], uint_vme_data_buf[3], uint_vme_data_buf[4]);
	zygoLogInfo("\tBoard Assy Number: (%u, %u) \n", uint_vme_data_buf[5], uint_vme_data_buf[6]);
	zygoLogInfo("\tBoard Configuration: %u \n", uint_vme_data_buf[7]);
	zygoLogInfo("\tOriginal Board Revision: %u \n", uint_vme_data_buf[8]);
	sprintf_s(ZYGO_BOARD_VERSION, tabLen, "v%u", uint_vme_data_buf[8]);
	zygoLogInfo("\tReworked Board Revision: %u \n", uint_vme_data_buf[9]);
	zygoLogInfo("\tNumber of axes: %u \n", uint_vme_data_buf[15]);
	zygoLogInfo("\tVendor code: %u \n", uint_vme_data_buf[18]);

	sprintf_s(ZYGO_BOARD_SN, tabLen, "%u:%u:%u:%u:%u", uint_vme_data_buf[10], \
		uint_vme_data_buf[11], \
		uint_vme_data_buf[12], \
		uint_vme_data_buf[13], \
		uint_vme_data_buf[14]);

	zygoLogInfo("\tBoard serial Number: %s \n", ZYGO_BOARD_SN);
	strcpy_s(ch_access_mode, sizeof(ch_access_mode), access_mode_Selection[6]);
	if (return_code = readWrite(ch_access_mode, ADD(BASE_ADDRESS[AXIS3 - 1], zFWVer), &vme_data, 0)) {
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		free(ledsStatus);
		return return_code;
	}
	zygoLogInfo("\tFirmware Version: %d \n", uint_vme_data);
	sprintf_s(ZYGO_FIRMWARE_VERSION, tabLen, "%u", uint_vme_data);

	if (return_code = readWrite(ch_access_mode, ADD(BASE_ADDRESS[AXIS3 - 1], zFWRev), &vme_data, 0))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		free(ledsStatus);
		return return_code;
	}
	zygoLogInfo("\tFirmware Revision: ");
	switch (uint_vme_data)
	{
	case 0x7401:
		zygoLogInfo(" 8020-9274-01\n");
		break;
	case 0x7402:
		zygoLogInfo(" 8020-9274-02\n");
		break;
	default:
		zygoLogInfo(" unknow\n");
		break;
	}

	/*Read SSI calibration data*/

	/*Enable reset finds velocity*/
	//EnableResetFindsVelocity(  axis);
	//Enable preset
//Enable test mode
	for (int i = 0; i < 4; i++)
	{
		if (enableResetFindsVelocity[i])
		{
			vme_data = 0x10;
			if (return_code = readWrite(ch_access_mode, ADD(BASE_ADDRESS[i], zTestCtrl0), &vme_data, 1))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				free(ledsStatus);
				return return_code;
			}
		}
		else
		{
			vme_data = 0;
			if (return_code = readWrite(ch_access_mode, ADD(BASE_ADDRESS[i], zTestCtrl0), &vme_data, 1))
			{
				zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
				free(ledsStatus);
				return return_code;
			}
		}
	}
	free(ledsStatus);
	return RET_SUCCESS;
}

int readSsiCalibrationData(Axes axis, double* SSIVals, double* OptPwrVals) {
	uint32_t temp32 = 0,
		offset = 0;
	double m = 0.0, b = 0.0;
	uint32_t uint_vme_data = 0;
	/*Read SSI calibration data*/
	zygoLogInfo("Reading SSI calibration data \n");

	if ((SSIVals == NULL) || (OptPwrVals == NULL))
		return 	BAD_ARG_POINTER;
	/*SSI reading with minimum signal*/
	offset = EEPROM_AXIS_DATA_BASE_OFFSET + EEPROM_MIN_SSI_OFFSET + (SIZE_WORDS * (axis - 1));
	if (return_code = eepromRead(offset, &uint_vme_data, 1)) {
		zygoLogWarn("EEPROM Offset %d access Faillure !  \n", offset);
		return return_code;
	}
	SSIVals[0] = uint_vme_data;

	/*SSI reading with nominal signal*/
	offset = EEPROM_AXIS_DATA_BASE_OFFSET + EEPROM_NOM_SSI_OFFSET + (SIZE_WORDS * (axis - 1));
	uint_vme_data = 0;
	if (return_code = eepromRead(offset, &uint_vme_data, WRITE)) {
		zygoLogWarn("EEPROM Offset %d access Faillure !  \n", offset);
		return return_code;
	}
	SSIVals[1] = uint_vme_data;

	/*SSI reading with maximum signal*/
	offset = EEPROM_AXIS_DATA_BASE_OFFSET + EEPROM_MAX_SSI_OFFSET + (SIZE_WORDS * (axis - 1));
	uint_vme_data = 0;
	if (return_code = eepromRead(offset, &uint_vme_data, WRITE)) {
		zygoLogWarn("EEPROM Offset %d access Faillure !  \n", offset);
		return return_code;
	}
	SSIVals[2] = uint_vme_data;

	/*opt pwr l2 reading with minimum signal*/
	offset = EEPROM_AXIS_DATA_BASE_OFFSET + EEPROM_OPT_PWR_L2_MIN_OFFSET + (SIZE_WORDS * (axis - 1));
	uint_vme_data = 0;
	if (return_code = eepromRead(offset, &uint_vme_data, WRITE)) /*Read optical power L2*/
	{
		zygoLogWarn("EEPROM Offset %d access Faillure !  \n", offset);
		return return_code;
	}
	OptPwrVals[0] = std::pow(2, uint_vme_data / 1024.0);

	/*opt pwr l2 reading with nominal signal*/
	offset = EEPROM_AXIS_DATA_BASE_OFFSET + EEPROM_OPT_PWR_L2_NOM_OFFSET + (SIZE_WORDS * (axis - 1));
	uint_vme_data = 0;
	if (return_code = eepromRead(offset, &uint_vme_data, WRITE)) {
		zygoLogWarn("EEPROM Offset %d access Faillure !  \n", offset);
		return return_code;
	}
	OptPwrVals[1] = std::pow(2, uint_vme_data / 1024.0);

	/*opt pwr l2 reading with maximum signal*/
	offset = EEPROM_AXIS_DATA_BASE_OFFSET + EEPROM_OPT_PWR_L2_MAX_OFFSET + (SIZE_WORDS * (axis - 1));
	uint_vme_data = 0;
	if (return_code = eepromRead(offset, &uint_vme_data, WRITE)) {
		zygoLogWarn("EEPROM Offset %d access Faillure !  \n", offset);
		return return_code;
	}
	OptPwrVals[2] = std::pow(2, uint_vme_data / 1024.0);

	zygoLogInfo("SSIVals:  [%lf,%lf,%lf]; OptPwrVals: [%lf,%lf,%lf] \n", SSIVals[0], SSIVals[1], SSIVals[2], OptPwrVals[0], OptPwrVals[1], OptPwrVals[2]);
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
int enableCecCompensation(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Enabling CEC compensation on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCECCtl);
	uint_vme_data = 0x3;// C0 and CN compensation
	//enableAuxRegisters(  3);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, 1))
	{
		zygoLogInfo("readWriteModify failed!!!!!!\n");
		zygoLogWarn("Enabling CE compensation failed\n");
		return return_code;
	}
	//disableAuxRegisters(  3);
	printf("Enabling CE compensation success\n");
	return RET_SUCCESS;
}


/// <summary>
/// This function disable Cyclics errors compensation
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int disableCecCompensation(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Disabling CEC compensation on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCECCtl);
	uint_vme_data = 0x0;// disable C0 and CN compensation
	//enableAuxRegisters(  3);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, 0))
	{
		zygoLogInfo("readWriteModify failed!!!!!!\n");
		zygoLogWarn("Disabling CE compensation failed\n");
		return return_code;
	}
	//disableAuxRegisters(  3);
	cecState = 0;
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
int useCeuserSuppliedCoef(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCECCtl);
	uint_vme_data = 0x1C;// C0 and CN compensation
	zygoLogInfo("Enabling the use of CE user supplied coefficients on axis %u during compensation...\n", axis);
	//enableAuxRegisters(  3);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, 1))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	//disableAuxRegisters(  3);
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
int useCeuserSupplyCoefAtStartup(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCECCtl);
	uint_vme_data = 0x40;
	zygoLogInfo("Enabling the use of CE user supplied coefficients on axis %u at the Startup...\n", axis);
	//enableAuxRegisters(  3);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, 1))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	//disableAuxRegisters(  3);
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
int resetCecErrors(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCEcmd);
	uint_vme_data = 0x1;
	zygoLogInfo("Reseting compensation errors on axis %u...\n", axis);
	//enableAuxRegisters(  3);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	//disableAuxRegisters(  3);
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
int waitCeinit2Complete(Axes axis) {
	uint32_t uint_vme_address = 0, ct = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCEstat);
	uint_vme_data = 0;
	zygoLogInfo("Waiting for CEC hardware initialization to complete on axis %u...\n", axis);
	//enableAuxRegisters(  3);
	while (!(uint_vme_data & 0x20)) {
		zygoLogInfo("Initializing CE coefficients...\n");
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
		Sleep(1);// sleep for 1ms
		ct++;
		if (ct > 3000) {
			zygoLogInfo("Any motion has not been detected for more than 30 secs\n");
			zygoLogWarn("CEC hardware initialization has failed \n");
			return NO_MOTION_DETECTED;
		}
	}
	//disableAuxRegisters(  3);
	zygoLogInfo("CEC hardware initialization success \n");
	return RET_SUCCESS;
}

int getLedsStatus(bool* ledsStatus) {
	uint32_t uint_vme_address = 0, uint_vme_data;

	zygoLogInfo("running getLedsStatus\n");
	for (int i = 0; i < 4; i++) {
		uint_vme_address = ADD(BASE_ADDRESS[i], zStat1);
		uint_vme_data = 0;
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		if (uint_vme_data & 0x2) {
			//zygoLogInfo("\t[Meas_Sig OK] The measurement signal is present on Axis %d\n", i + 1);
			ledsStatus[i] = true;
		}
		else {
			//zygoLogInfo("\t[Meas_Sig Warning] The measurement signal is missing on Axis %d\n", i + 1);
			ledsStatus[i] = false;
		}

	}
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zStat0);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	if (uint_vme_data & 0x2) {
		//The reference signal is present
		ledsStatus[4] = true;
	}
	else {
		//The reference signal is absent
		ledsStatus[4] = false;
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
int setCemaxVel(Axes axis, uint32_t CEMaxVelValue) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Setting cyclic error max velocity on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCEMaxVel);
	uint_vme_data = CEMaxVelValue;
	//enableAuxRegisters(  3);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	//disableAuxRegisters(  3);
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
int setCeminVel(Axes axis, uint32_t CEMinVelValue) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Setting cyclic error min velocity on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCEMinVel);
	uint_vme_data = CEMinVelValue;
	//enableAuxRegisters(  axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	//disableAuxRegisters(  axis);
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
int readCalcCecoeffs(Axes axis, CECoeffs& CECalcCoeffs) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Reading cyclic error calculated coefficients on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCEC0CalcCoeff);

	//enableAuxRegisters(  3);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return RET_FAILED;
	}
	// CE0 val is stored in zygo register as a complex Int16 value so we should 
	// convert it to a complex number
	convertCint162Complex(uint_vme_data, CECalcCoeffs.CEC0coeff);  //coeffs[0] = uint_vme_data;

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCEC1CalcCoeff);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	// CE1 val is stored in zygo register as a float value so we should 
// convert it to double
	convertFloat2Decimal(uint_vme_data, &(CECalcCoeffs.CEC1coeff));// coeffs[1] = uint_vme_data;

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCECNCalcCoeff);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	//disableAuxRegisters(  3);
	// CEN val is stored in zygo register as a complex float value so we should 
// convert it to a complex number
	convertCfloat2Complex(uint_vme_data, CECalcCoeffs.CECNcoeff);//coeffs[2] = uint_vme_data;
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
int readCecoefBoundaries(Axes axis, CECoeffBoundaries& CE0CoeffBound, CECoeffBoundaries& CENCoeffBound) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0
		, uint_vme_data1 = 0;
	USHORT tmp1 = 0, tmp2 = 0;
	//enableAuxRegisters(  3);
	for (int i = 0; i < 2; i++) {
		// Read CE mag coefficient
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], (i == 0 ? zCE0Mag : zCENMag));
		zygoLogInfo("Reading cyclic error %s Mag coefficients on axis %u...\n", (i == 0 ? "0" : "N"), axis);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}

		uint_vme_data1 = uint_vme_data;
		// Read CE min and max coefficients
		zygoLogInfo("Reading cyclic error %s Min and Max coefficients on axis %u...\n", (i == 0 ? "0" : "N"), axis);
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], (i == 0 ? zCE0Min : zCENMin));
		uint_vme_data = 0;
		if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}

		//disableAuxRegisters(  axis);
		// CE Mag val is stored in zygo register as an uint16_t value so we should 
		// convert it to a real() number
		convertUsfloat2Double(uint_vme_data1, (i == 0 ? &(CE0CoeffBound.CEMagcoeff) : &(CENCoeffBound.CEMagcoeff)));

		//split data to get CE min and CE max value
		tmp1 = uint_vme_data & 0xFFFF; // CE Min
		tmp2 = (uint_vme_data >> 16) & 0xFFFF; //  CE max
		// CE1 val is stored in zygo register as a float value so we should 
	// convert it to double
		convertUsfloat2Double(tmp1, (i == 0 ? &(CE0CoeffBound.CEMincoeff) : &(CENCoeffBound.CEMincoeff)));
		convertUsfloat2Double(tmp2, (i == 0 ? &(CE0CoeffBound.CEMaxcoeff) : &(CENCoeffBound.CEMaxcoeff)));
		uint_vme_data = 0;
	}
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
int calculateCeratio(Axes axis, CEratios& ceRatios, CEratioUnits units) {
	CECoeffs ceCoeffs;
	CEratios ceRatiotmp;
	double temp = 0.0;
	if (return_code=readCalcCecoeffs(axis, ceCoeffs))
		return return_code;
	ceRatiotmp.measSignal = temp;
	ceRatiotmp.CE0ratio = sqrt(std::pow(ceCoeffs.CEC0coeff.real(), 2) + std::pow(ceCoeffs.CEC0coeff.real(), 2)) / temp;
	ceRatiotmp.CENratio = sqrt(std::pow(ceCoeffs.CECNcoeff.real(), 2) + std::pow(ceCoeffs.CECNcoeff.imag(), 2)) / std::pow(temp, 2);
	ceRatios.measSignal = temp;
	switch (units)
	{
	case CEratioUnits::ratio_in_dB:
		zygoLogInfo("Performing CE ratio calculation in dB on axis %u...\n", axis);
		//ceRatios.measSignal = 20 * log10(ceRatiotmp.measSignal);
		ceRatios.CE0ratio = 20 * log10(ceRatiotmp.CE0ratio);
		ceRatios.CENratio = 20 * log10(ceRatiotmp.CENratio);
		break;
	case CEratioUnits::ratio_in_percent:
		zygoLogInfo("Performing CE ratio calculation in percent on axis %u...\n", axis);
		//ceRatios.measSignal = 100*ceRatiotmp.measSignal;
		ceRatios.CE0ratio = 100 * ceRatiotmp.CE0ratio;
		ceRatios.CENratio = 100 * ceRatiotmp.CENratio;
		break;
	case CEratioUnits::ratio_in_nmRMS:
		zygoLogInfo("Performing CE ratio calculation in nmRMS on axis %u...\n", axis);
		//ceRatios.measSignal =  ceRatiotmp.measSignal *(1/(2*PI))*(LAMBDA/(2*static_cast<double>(curInterferoConfig)))* 0.70710678118654;
		ceRatios.CE0ratio = ceRatiotmp.CE0ratio * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
		ceRatios.CENratio = ceRatiotmp.CENratio * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
		break;
	default:
		break;
	}
	return RET_SUCCESS;
}
/// <summary>
/// The function use an approximation to calculate the cyclic error percentage.Due to the approximation used, these values may
///differ from values calculated from the coefficient calculated by calculateCeratio() by approximately 10 %, depending on the phase of the coefficient.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">axis number</param>
/// <param name="ceRatios">stores CE ratios</param>
/// <param name="units">ratio units(%,dB,nm RMS) to use</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getAproximateCeratio(Axes axis, CEratios& ceRatios, CEratioUnits units) {
	CECoeffs ceCoeffs;
	CECoeffBoundaries CE0bound = { 0,0,0 }, CENbound = { 0,0,0 };
	double tmp;
	if (return_code = readCalcCecoeffs(axis, ceCoeffs))
		return return_code;
	if (return_code=readCecoefBoundaries(axis, CE0bound, CENbound))
		return return_code;
	tmp = sqrt(ceCoeffs.CEC1coeff);
	switch (units)
	{
	case CEratioUnits::ratio_in_dB:
		zygoLogInfo("Calculating estimate CE ratio  in dB on axis %u...\n", axis);
		ceRatios.CE0ratio = 20 * log10(CE0bound.CEMagcoeff);
		ceRatios.CENratio = 20 * log10(CENbound.CEMagcoeff);
		break;
	case CEratioUnits::ratio_in_percent:
		zygoLogInfo("Calculating estimate CE ratio  in percent on axis %u...\n", axis);
		ceRatios.CE0ratio = 100 * (static_cast<double>(CE0bound.CEMagcoeff)) / tmp;
		ceRatios.CENratio = 100 * (static_cast<double>(CENbound.CEMagcoeff));
		break;
	case CEratioUnits::ratio_in_nmRMS:
		zygoLogInfo("Calculating estimate CE ratio  in nmRMS on axis %u...\n", axis);
		ceRatios.CE0ratio = CE0bound.CEMagcoeff * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
		ceRatios.CENratio = CENbound.CEMagcoeff * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
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
int getCeratioLimits(Axes axis, CEratios& ceRatioLimits, CEratioUnits units) {
	CECoeffs ceCoeffs;
	CEratios ceRatiotmp;
	CECoeffBoundaries CE0bound = { 0.0,0.0,0.0 }, CENbound = { 0.0,0.0,0.0 };
	double tmp;
	zygoLogInfo("Performing CE ratio limits calculation on axis %u...\n", axis);
	if (return_code = readCalcCecoeffs(axis, ceCoeffs))
		return return_code;
	if (return_code = calculateCeratio(axis, ceRatiotmp, units))
		return return_code;
	tmp = sqrt(ceCoeffs.CEC1coeff);

	ceRatioLimits.CE0ratio = tmp * (ceRatiotmp.CE0ratio) / 100;
	ceRatioLimits.CENratio = (ceRatiotmp.CE0ratio) / 100;

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
int getAproximateCeratioBoundaries(Axes axis,
	CEratiosBoundaries& ce0RatiosBoundaries, CEratiosBoundaries& ceNRatiosBoundaries, CEratioUnits units) {
	CECoeffs ceCoeffs = { 0.0 };
	CECoeffBoundaries CE0bound = { 0.0 }, CENbound = { 0.0};
	double tmp;
	if (return_code = readCalcCecoeffs(axis, ceCoeffs))
		return return_code;
	if (return_code = readCecoefBoundaries(axis, CE0bound, CENbound))
		return return_code;
	tmp = sqrt(ceCoeffs.CEC1coeff);
	switch (units)
	{
	case CEratioUnits::ratio_in_dB:
		zygoLogInfo(" Estimation of CE ratio limits in dB on axis %u...\n", axis);
		ce0RatiosBoundaries.CEMinratio = 20 * log10((static_cast<double>(CE0bound.CEMincoeff))) / tmp;
		ce0RatiosBoundaries.CEMaxratio = 20 * log10((static_cast<double>(CE0bound.CEMaxcoeff))) / tmp;

		ceNRatiosBoundaries.CEMinratio = 20 * log10((static_cast<double>(CENbound.CEMincoeff)));
		ceNRatiosBoundaries.CEMaxratio = 20 * log10((static_cast<double>(CENbound.CEMaxcoeff)));
		break;
	case CEratioUnits::ratio_in_percent:
		zygoLogInfo(" Estimation of CE ratio limits in percent on axis %u...\n", axis);
		ce0RatiosBoundaries.CEMinratio = 100 * (static_cast<double>(CE0bound.CEMincoeff)) / tmp;
		ce0RatiosBoundaries.CEMaxratio = 100 * (static_cast<double>(CE0bound.CEMaxcoeff)) / tmp;

		ceNRatiosBoundaries.CEMinratio = 100 * (static_cast<double>(CENbound.CEMincoeff));
		ceNRatiosBoundaries.CEMaxratio = 100 * (static_cast<double>(CENbound.CEMaxcoeff));
		break;
	case CEratioUnits::ratio_in_nmRMS:
		zygoLogInfo(" Estimation of CE ratio limits in nmRMS on axis %u...\n", axis);
		ce0RatiosBoundaries.CEMinratio = CE0bound.CEMincoeff * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
		ce0RatiosBoundaries.CEMaxratio = CE0bound.CEMaxcoeff * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;

		ceNRatiosBoundaries.CEMinratio = CENbound.CEMincoeff * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
		ceNRatiosBoundaries.CEMaxratio = CENbound.CEMaxcoeff * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
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
int getCeRatioBoundaries(Axes axis, CEratios& ceRatios, CEratioUnits units) {
	CECoeffs ceCoeffs;
	CEratios ceRatiotmp;
	double temp;
	if (return_code = readCalcCecoeffs(axis, ceCoeffs))
		return return_code;
	temp = sqrt(ceCoeffs.CEC1coeff);
	ceRatiotmp.measSignal = temp;
	ceRatiotmp.CE0ratio = (sqrt(std::pow(ceCoeffs.CEC0coeff.real(), 2) + std::pow(ceCoeffs.CEC0coeff.imag(), 2))) / temp;
	ceRatiotmp.CENratio = (sqrt(std::pow(ceCoeffs.CECNcoeff.imag(), 2) + std::pow(ceCoeffs.CECNcoeff.imag(), 2))) / std::pow(temp, 2);
	switch (units)
	{
	case CEratioUnits::ratio_in_dB:
		zygoLogInfo("Performing CE ratio limits calculation in dB on axis %u...\n", axis);
		ceRatios.measSignal = 20 * log10(ceRatiotmp.measSignal);
		ceRatios.CE0ratio = 20 * log10(ceRatiotmp.CE0ratio);
		ceRatios.CENratio = 20 * log10(ceRatiotmp.CENratio);
		break;
	case CEratioUnits::ratio_in_percent:
		zygoLogInfo("Performing CE ratio limits calculation in pecent on axis %u...\n", axis);
		ceRatios.measSignal = 100 * ceRatiotmp.measSignal;
		ceRatios.CE0ratio = 100 * ceRatiotmp.CE0ratio;
		ceRatios.CENratio = 100 * ceRatiotmp.CENratio;
		break;
	case CEratioUnits::ratio_in_nmRMS:
		zygoLogInfo("Performing CE ratio limits calculation in nmRMS on axis %u...\n", axis);
		ceRatios.measSignal = ceRatiotmp.measSignal * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
		ceRatios.CE0ratio = ceRatiotmp.CE0ratio * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
		ceRatios.CENratio = ceRatiotmp.CENratio * (1 / (2 * PI)) * (LAMBDA / (2 * static_cast<double>(curInterferoConfig))) * 0.70710678118654;
		break;
	default:
		break;
	}
	return RET_SUCCESS;
}
/// <summary>
/// this function convert an uint32_teger value from a zygo register to a complex value
/// </summary>
/// <param name="nbr">register value</param>
/// <param name=" val">a complex variable to store the converted value in</param>
/// <returns></returns>
int convertCint162Complex(uint32_t nbr, std::complex<double>& val) {

	zygoLogInfo("Conversion from complex int16 to double...\n");
	val = std::complex<double>(static_cast<double>((short)(nbr & 0xFFFF)),static_cast<double>((short)((nbr & 0xFFFF0000) >> 16)));
	return RET_SUCCESS;
}
/// <summary>
/// This function convert a complex value to an uint32_t value to be loaded in
/// a zygo register
/// </summary>
/// <param name="nbr">the complex number </param>
/// <param name="val"> a pointer on a variable to store the result</param>
/// <returns> 0 </returns>
int convertComplex2Uint(std::complex<double> nbr, uint32_t* val) {
	zygoLogInfo("Conversion from complex  to uint32_t...\n");
	*val = (((uint32_t)(nbr.real()) & 0xFFFF) << 16) | (uint32_t)(nbr.imag()) & (uint32_t)0xFFFF;
	return RET_SUCCESS;
}

/// <summary>
/// The function convert a given a complex float number to a complex number
/// </summary>
/// <param name="cfloatNbr">the complex float value</param>
/// <param name="complexVal"> the complex pointer to store the result</param>
/// <returns>0 </returns>
int convertCfloat2Complex(uint32_t cfloatNbr, std::complex<double>& complexVal) {

	zygoLogInfo("Conversion from complex float to complex...\n");
	USHORT exp = 0, Rsign = 0, Isign = 0, Imant = 0, Rmant = 0, temp = 0;
	temp = (cfloatNbr & 0xFF000000) >> 23;
	Rsign = temp & 0x1;
	exp = temp >> 1;
	Imant = cfloatNbr & 0x7FF;
	temp = ((cfloatNbr >> 11) & 0xFFF);
	Isign = temp & 0x1;
	Rmant = temp >> 1;
	complexVal = std::complex<double>((1 - 2 * static_cast<double>(Isign)) * Imant * std::pow(2, static_cast<double>(exp) - 127 - 10), (1 - 2 * static_cast<double>(Rsign)) * Rmant * std::pow(2, static_cast<double>(exp) - 127 - 10));
	return RET_SUCCESS;
}

/// <summary>
/// The function convert a given complex number to a complex float number 
/// </summary>
/// <param name="complexNbr"> the complex value </param>
/// <param name="cfloatVal">the complex float pointer to store the result </param>
/// <returns>0 </returns>
int convertComplex2Cfloat(std::complex<double> complexNbr, uint32_t* cfloatVal) {

	zygoLogInfo("Conversion from complex to complex float...\n");
	uint32_t rexp = 0, iexp = 0, exp = 0;
	rexp = (uint32_t)floor(log2(complexNbr.real()));
	iexp = (uint32_t)floor(log2(complexNbr.imag()));
	exp = max(rexp, iexp);
	*cfloatVal = (exp + 127) * 0x1000000 + (complexNbr.real() < 0 ? 0x8000000 : 0)
		+ (uint32_t)(round(sqrt(std::pow(complexNbr.real(), 2)) * std::pow(2, -static_cast<double>(exp) + 10))) * 0x1000
		+ (uint32_t)((complexNbr.imag() < 0 ? 0x800 : 0) + round(sqrt(std::pow((complexNbr.imag()), 2)) * std::pow(2, -static_cast<double>(exp) + 10)));//use sqrt bcuz abs() does take only integer
	return RET_SUCCESS;
}
/// <summary>
/// The function convert a given float number to a real() number 
/// </summary>
/// <param name="floatNbr"> the float value</param>
/// <param name="doubleVal">the real() pointer to store the result</param>
/// <returns>0 </returns>
int convertFloat2Decimal(uint32_t floatNbr, double* doubleVal) {
	zygoLogInfo("Conversion from float to double...\n");
	uint32_t sign = 0, exp = 0, mant = 0, temp = 0;
	temp = floatNbr & (uint32_t)0x1FFFFFF;
	sign = temp >> 24;
	exp = (temp >> 16) & (uint32_t)0xFF;
	mant = temp & (uint32_t)0xFFFF;
	*doubleVal = (1 - 2 * static_cast<double>(sign)) * (static_cast<double>(mant + 0x10000)) * std::pow(2, exp - 127 - 16);
	zygoLogInfo("doubleVal is %lf\n", *doubleVal);
	return RET_SUCCESS;
}
/// <summary>
/// The function convert a given real() number to a float number 
/// </summary>
/// <param name="doubleNbr"> the real() value</param>
/// <param name="floatVal">the float pointer to store the result</param>
/// <returns>0 </returns>
int convertDouble2Float(double doubleNbr, uint32_t* floatVal) {
	zygoLogInfo("Conversion from double to float...\n");
	USHORT exp = 0;
	exp = (USHORT)floor(log2(doubleNbr));
	*floatVal = (doubleNbr < 0 ? 0x1000000 : 0) + (exp + 127) * 0x10000
		+ (uint32_t)(round(sqrt(std::pow(doubleNbr, 2)) * std::pow(2, 16 - static_cast<double>(exp)))) & 0xFFFF;//sqrt(std::pow(doubleNbr,2))=abs(doubleNbr)
	return RET_SUCCESS;
}
/// <summary>
/// The function convert a given uint16_t float number to a real() number 
/// </summary>
/// <param name="USFloatNbr"> the uint16_t float value</param>
/// <param name="doubleVal">the real() pointer to store the result</param>
/// <returns>0 </returns>
int convertUsfloat2Double(uint16_t USFloatNbr, double* doubleVal) {
	USHORT exp = 0, mant = 0;
	zygoLogInfo("Conversion from uint16_t float to double...\n");
	exp = (USHORT)(USFloatNbr >> 8) & (USHORT)0xFF;
	mant = (USHORT)USFloatNbr & (USHORT)0xFF;
	*doubleVal = (static_cast<double>(mant) + static_cast<double>((USHORT)0x100)) * std::pow(2, static_cast<double>(exp) - 127 - 8);
	return RET_SUCCESS;
}
/// <summary>
/// The function convert a given real() number to an uint16_t float number  
/// </summary>
/// <param name="doubleNbr"> the real() value</param>
/// <param name="USFloatVal">the float pointer to store the result</param>
/// <returns>0 </returns>
int convertDouble2Usfloat(double doubleNbr, PUSHORT USFloatVal) {
	USHORT exp = 0;
	zygoLogInfo("Conversion from double to uint16_t float...\n");
	exp = (USHORT)floor(log2(doubleNbr));
	*USFloatVal = (exp + 127) * 0x100 + (uint32_t)(round((doubleNbr)*std::pow(2, 8 - static_cast<double>(exp)))) & 0x00FF;
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
int setCompARegVal32(Axes axis, uint32_t compAval32) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Setting comparator A register 32bits value to 0x%08x on axis %u...\n", compAval32, axis);
	uint_vme_data = compAval32;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCompAMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
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
int enable37BitsSignExtension(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl0);
	uint_vme_data = 0x40;

	zygoLogInfo("Enabling 37 bits sign extension on axis %u...\n", axis);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("Read write modify failed!  \n");
		return return_code;
	}


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
int disable37bitsSignExtension(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0xFFBF;
	zygoLogInfo("Disabling 37 bits sign extension on axis %u...\n", axis);

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl0);

	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("Read write modify failed!  \n");
		return return_code;
	}

	return RET_SUCCESS;
}
/// <summary>
/// The function set the digital filter coefficients on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="Kp">Value of the Kp coefficient(range is -2 to -9)</param>
/// <param name="Kv">Value of the kv coefficient(range is -7 to -21)</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setKpAndKvCoeff(Axes axis, int Kp, int Kv) {

	zygoLogInfo("Setting digital filter coefficient to (Kp=%d, Kv=%d)on axis %u...\n", Kp, Kv, axis);
	if ((checkLimits(Kp, KPMIN, KPMAX) || checkLimits(Kv, KVMIN, KVMAX)) != RET_SUCCESS){

		zygoLogWarn("Bad Kp or Kv value. Kp range is -2 to -9 and Kv range is -7 to -21\n");
		return BAD_ARG_VALUE;
	}
	uint32_t uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl1);
	uint_vme_data = 0;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	uint_vme_data |= ((-Kp - 2) << 4) + (-(Kv + 7) / 2);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	return RET_SUCCESS;
}

/// <summary>
/// The function gets the digital filter coefficients on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="Kp">Variable to store value of the Kp coefficient</param>
/// <param name="Kv">Variable to store value of the kv coefficient</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getKpAndKvCoeff(Axes axis, int* coeff) {

	zygoLogInfo("Getting digital filter coefficient(Kp,Kv) on axis %u...\n", axis);
	if (coeff == NULL)
	{
		zygoLogWarn("None of the function's arguments can be null \n");
		return BAD_ARG_POINTER;
	}
	uint32_t uint_vme_address = 0, uint_vme_data;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl1);
	uint_vme_data = 0;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	//Kp
	coeff[0] = -2 - (uint_vme_data & 0x07);
	//Kv
	coeff[1] = -2 * ((uint_vme_data & 0x7) >> 3) - 7;
	zygoLogInfo("Kp = %d, Kv = %d\n", coeff[0], coeff[1]);
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
int setCompARegVal37(Axes axis, uint32_t compAval32, uint32_t compAvalExt) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Setting comparator A 37bits value to 0x%09x on axis %u...\n", compAval32, axis);
	setCompARegVal32(axis, compAval32);
	zygoLogInfo("Setting comparator A ext value to 0x%02x on axis %u...\n", compAvalExt, axis);
	uint_vme_data = compAvalExt;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCompAExt);
	if (return_code = readWrite("A24D8", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
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
int setCompBRegVal32(Axes axis, uint32_t compBval32) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Setting comparator B 32bits value to 0x%08x on axis %u...\n", compBval32, axis);
	uint_vme_data = compBval32;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCompBMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
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
int setCompBRegVal37(Axes axis, uint32_t compBval32, uint32_t compBvalExt) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	zygoLogInfo("Setting comparator B 32bits value to 0x%08x on axis %u...\n", compBval32, axis);
	if (return_code = setCompBRegVal32(axis, compBval32))
	{
		zygoLogWarn("setCompBRegVal32 failed !  \n");
		return return_code;
	}
	zygoLogInfo("Setting comparator B ext value to 0x%02x on axis %u...\n", compBvalExt, axis);
	uint_vme_data = compBvalExt;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCompBExt);
	if (return_code = readWrite("A24D8", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 37bits value of the offset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="offsetPos32">The 32bits value</param>
/// <param name="offsetPosExt">The 5bits value</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>

int setPositionOffset37(Axes axis, double* offsetPos) {

	uint32_t uint_vme_address = 0, uint_vme_data, mem[2];
	uint8_t offsetPosExt;
	uint64_t ptr[1];
	my_int64_t val[1];
	if (offsetPos == NULL) {
		zygoLogWarn("Can not accept Null pointer in setPositionOffset37 function\n");
		return BAD_ARG_POINTER;
	}
	*val = (my_int64_t)(*offsetPos / positionScale);
	*ptr = (uint64_t)(*val);
	memcpy(mem, ptr, sizeof(my_int64_t));
	uint_vme_data = mem[0];
	offsetPosExt = (uint8_t)(mem[1] & 0xFF);
	zygoLogInfo("Setting offset position 32bits value to 0x%08x on axis %u...\n", uint_vme_data, axis);
	zygoLogInfo("Setting offset position ext value to 0x%8x on axis %u...\n", offsetPosExt, axis);

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zOffsetMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	uint_vme_data = offsetPosExt;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zOffsetExt);
	if (return_code = readWrite("A24D8", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
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
int setPositionOffset32(Axes axis, double* offsetPos) {
	if (offsetPos == NULL) {
		zygoLogWarn("Can not accept Null pointer in setPositionOffset32 function\n");
		return BAD_ARG_POINTER;
	}
	uint32_t uint_vme_address = 0, uint_vme_data;
	int32_t tmp = 0;
	tmp = (int32_t)((*offsetPos) / positionScale);
	uint_vme_data = (uint32_t)(tmp);
	zygoLogInfo("Setting position offset 32bits value to 0x%08x on axis %u....\n", tmp, axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zOffsetMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zOffsetExt);
	if (return_code = readWrite("A24D8", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	return RET_SUCCESS;
}

/// <summary>
/// The function sets the  value of the offset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="presetPos">The value return pointer</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>

int setPositionOffset(Axes axis, double* offsetPos) {
	if (offsetPos == NULL) {
		zygoLogWarn("Can not accept Null pointer in setPositionOffset function\n");
		return BAD_ARG_POINTER;
	}
	if(!curPrecision)
	{
		if (return_code = setPositionOffset32(axis, offsetPos))
		{
			zygoLogWarn("setPositionOffset32 failed !  \n");
			return return_code;
		}
	}
	else
	{
		if (return_code = setPositionOffset37(axis, offsetPos))
		{
			zygoLogWarn("setPositionOffset37 failed !  \n");
			return return_code;
		}
		
	}
	resetAxis(axis);
	return RET_SUCCESS;
}


/// <summary>
/// This function gets the position offset on a specific axis.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="offsetPos">the value return parameter</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getPositionOffset(Axes axis, double* offsetPos) {
	zygoLogInfo("Getting offset position value on axis %u...\n", axis);
	if (offsetPos == NULL) {
		zygoLogWarn("Can not accept Null pointer in getPositionOffset function\n");
		return BAD_ARG_POINTER;
	}
	short val = 0;
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0, temp32 = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zOffsetMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("getPositionOffset: Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	if (curPrecision) {//37 bits read

		temp32 = (uint32_t)uint_vme_data;
		uint_vme_data = 0;
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zOffsetExt);		//Read the Ext
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("getPositionOffset: Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		val = (short)uint_vme_data;
		//*
		if ((val & 0x10) != 0) { // check if the ext value is negative

			*offsetPos = static_cast<double>((short)(0xffe0 + (val & 0x001f)));

			*offsetPos = (((*offsetPos) * (TMP32)) + temp32) * positionScale;

		}
		else {
			*offsetPos = (((val & 0x1F) * (TMP32)) + temp32) * positionScale;
		}
		//*/
	}
	else {//32 bits read
		*offsetPos = (static_cast<double>((int)uint_vme_data)) * positionScale;
	}
	return RET_SUCCESS;
}

/// <summary>
/// The function gets the  value of the preset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="presetPos">The value return pointer</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getPresetPosition(Axes axis, double* presetPos) {

	zygoLogInfo("Getting preset position value on axis %u...\n", axis);
	if (presetPos == NULL) {
		zygoLogWarn("Can not accept Null pointer in getPositionOffset function\n");
		return BAD_ARG_POINTER;
	}
	short val = 0;
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0, temp32 = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zPresPosMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("getPresetPosition: Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	if (curPrecision) {//37 bits read

		temp32 = (uint32_t)uint_vme_data;
		uint_vme_data = 0;
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zPresPosExt);		//Read the Ext
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("getPresetPosition: Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		val = (short)uint_vme_data;
		//*
		if ((val & 0x10) != 0) { // check if the ext value is negative

			*presetPos = static_cast<double>((short)(0xffe0 + static_cast<short>(val & 0x1f)));
			*presetPos = (((*presetPos) * (TMP32)) + temp32) * positionScale;

		}
		else {
			*presetPos = (((val & 0x1F) * (TMP32)) + temp32) * positionScale;
		}
		//*/
	}
	else {//32 bits read
		*presetPos = (static_cast<double>((int)uint_vme_data)) * positionScale;
	}
	return RET_SUCCESS;
}

/// <summary>
/// The function sets the 32bits value of the offset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="presetPos32">The value return pointer</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setPresetPosition32(Axes axis, double* presetPos) {
	uint32_t uint_vme_address = 0, uint_vme_data;

	uint_vme_data = (uint32_t)((int32_t)((*presetPos) / positionScale));
	if (presetPos == NULL) {
		zygoLogWarn("Can not accept Null pointer in setPresetPosition32 function\n");
		return BAD_ARG_POINTER;
	}
	zygoLogInfo("Setting preset position 32bits value to 0x%08x on axis %u...\n", uint_vme_data, axis);	
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zPresPosMSB);
	if (return_code = enablePreset(axis)) {
		zygoLogWarn("enablePreset failed !  \n");
		return return_code;
	}
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zPresPosExt);
	if (return_code = readWrite("A24D8", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the 37bits value of the offset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="presetPos">The value return pointer</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setPresetPosition37(Axes axis, double* presetPos) {
	uint32_t uint_vme_address = 0, uint_vme_data, mem[2];
	uint8_t presetPosExt;
	uint64_t ptr[1];
	uint64_t val[1];

	if (presetPos == NULL) {
		zygoLogWarn("Can not accept Null pointer in setPresetPosition37 function\n");
		return BAD_ARG_POINTER;
	}
	*val = (uint64_t)(*presetPos / positionScale);
	*ptr = (uint64_t)(*val);
	memcpy(mem, ptr, sizeof(my_int64_t));
	uint_vme_data = mem[0];
	presetPosExt = (uint8_t)(mem[1] & 0xFF);
	/*
	uint_vme_data = (uint32_t)(*ptr & (uint32_t)0xFFFFFFFF);
	presetPosExt = (uint8_t)((((*ptr >> 31) >> 1)) & (uint32_t)0x1F);
	*/
	if (*presetPos < 0) {

	}
	zygoLogInfo("Setting preset position 32bits value to 0x%08x on axis %u...\n", uint_vme_data, axis);
	zygoLogInfo("Setting preset position ext value to 0x%x on axis %u...\n", presetPosExt, axis);

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zPresPosMSB);
	if (return_code = enablePreset(axis)) {
		zygoLogWarn("enablePreset failed !  \n");
		return return_code;
	}
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	uint_vme_data = presetPosExt;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zPresPosExt);
	if (return_code = readWrite("A24D8", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	return RET_SUCCESS;
}
/// <summary>
/// The function sets the value of the offset position register on a specific axis
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis' number</param>
/// <param name="presetPos">The value return pointer</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setPresetPosition(Axes axis, double* presetPos) {	

	if (presetPos == NULL) {
		zygoLogWarn("Can not accept Null pointer in setPresetPosition function\n");
		return BAD_ARG_POINTER;
	}
	if (curPrecision) {
		if (return_code = setPresetPosition37(axis, presetPos))
		{
			zygoLogWarn("setPresetPosition37 failed !  \n");
			return return_code;
		}
	}
	else {
		if (return_code = setPresetPosition32(axis, presetPos))
		{
			zygoLogWarn("setPresetPosition32 failed !  \n");
			return return_code;
		}

	}
	resetAxis(axis);
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
int readVmeErrs(Axes axis) {
	uint32_t
		uint_vme_address = 0,
		VMEErrorStatus0 = 0,
		VMEErrorStatus1 = 0,
		VMEErrorStatus2 = 0,
		TestStat1 = 0,
		APDError = 0,
		VMEPosError = 0,
		uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat1);		//Read VME errors
	zygoLogInfo("Reading VME errors on axis %u ...\n", axis);
	zygoLogInfo("***************************VME Errors*******************************\n");
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	TestStat1 = uint_vme_data;
	if (TestStat1 & 0x800)
		zygoLogInfo("EEPROM Error has been detected\n");
	if (return_code = parseVmeErrorStatus0(axis, &VMEErrorStatus0))
	{
		zygoLogWarn("parseVmeErrorStatus0 failed !  \n");
		return return_code;
	}
	if (return_code = parseVmeErrorStatus1(axis, &VMEErrorStatus1))
	{
		zygoLogWarn("parseVmeErrorStatus1 failed !  \n");
		return return_code;
	}
	if (return_code = parseVmeErrorStatus2(axis, &VMEErrorStatus2))
	{
		zygoLogWarn("parseVmeErrorStatus2 failed !  \n");
		return return_code;
	}
	if (return_code = parseVmePosErrs(axis, &VMEPosError))
	{
		zygoLogWarn("parseVmePosErrs failed !  \n");
		return return_code;
	}
	if (return_code = parseApdErrCode(axis, &APDError))
	{
		zygoLogWarn("parseApdErrCode failed !  \n");
		return return_code;
	}
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
int readAllErrs(Axes axis) {
	if (return_code = readVmeErrs(axis))
	{
		zygoLogWarn("readVmeErrs failed !  \n");
		return return_code;
	}
	if (return_code = readApdCtrlSoftErrs(axis))
	{
		zygoLogWarn("readApdCtrlSoftErrs !  \n");
		return return_code;
	}
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
int ClearEEPROMErrs() {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestCmd1);
	uint_vme_data = 0x4;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite failed !  \n");
		return return_code;
	}
	return RET_SUCCESS;
}
/// <summary>
/// The function configures the Board control Mode. It operates using boardControlMode function.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="biasMode">the bias mode. There are 5 bias modes(from 0 to 4)</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int boardControlMode(Axes axis, BIAS_MODE biasMode) {
	/*Activate APD Constant voltage mode*/

	if (return_code = setBiasMode(axis, biasMode)) {
		return return_code;
	}
	switch (biasMode)
	{

	case BIAS_MODE::BIAS_CONSTANT_VOLT_MODE:
		break;
	case BIAS_MODE::BIAS_CONSTANT_GAIN_MODE:
		if (return_code = setApdL2GainSet(axis, defaultAPDGAinL2Set)) {
			zygoLogWarn("setApdL2GainSet failed with error code %d\n", return_code);
			return return_code;
		}
		break;
	case BIAS_MODE::BIAS_SIG_RMS_ADJUST_MODE:
		if (return_code = setApdL2SigRmsSet(axis, defaultAPDSigRMSL2Set)) {
			zygoLogWarn("setApdL2SigRms failed!\n");
			return return_code;
		}
		break;
	case BIAS_MODE::BIAS_CONSTANT_OPT_PWR_MODE:
		if (return_code = setApdL2OptPwrSet(axis, defaultAPDOptPwrL2Set)) {
			zygoLogWarn("setApdL2OptPwr failed!\n");
			return return_code;
		}
		if (return_code = setApdL2SigRmsSet(axis, defaultAPDSigRMSL2Set)) {
			zygoLogWarn("setApdL2SigRms failed!\n");
			return return_code;
		}
		break;
	default:
		break;
	}
	/*Set APD GAIN L2 to 892*/
	//setApdL2Gain(  axis,APDGain);
	/* Start bias calculation */
	if (return_code = startBiasCalculation(axis)) {
		zygoLogWarn("Can not perform bias calculation");
		return return_code;
	}
	//Sleep(1000);
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
int setBiasMode(Axes axis, BIAS_MODE mode) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);//rw
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	uint_vme_data &= ~(7);
	uint_vme_data |= static_cast<uint32_t>(mode);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code;
	}
	zygoLogInfo("Board switched to  %s\n", biasControlModeString[static_cast<uint32_t>(mode)]);
	return RET_SUCCESS;
}

int getBiasMode(Axes axis, BIAS_MODE& biasMode) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);//rw
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	biasMode = static_cast<BIAS_MODE>(uint_vme_data & 0x7);
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
int startBiasCalculation(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0, ctr = 0;
	zygoLogInfo("Starting Bias calculation on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCmd);
	uint_vme_data = (1 << 6);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat2);
	uint_vme_data = 0;
	while (!(uint_vme_data & (1 << 5)))
	{
		// wait for Bias calc complete to be asserted
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		Sleep(1000);// 
		ctr++;
		if (ctr > 10) {
			zygoLogInfo("Can not start bias calculation after 10seconds, aborting...");
			zygoLogWarn("Bias calculation failed");
			return BIAS_CALC_FAILED;
		}
	}
	zygoLogInfo("Bias calculation complete \n");
	return RET_SUCCESS;
}

/// <summary>
/// This function sets the value of APD Gain L2 set register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDGain">The APDGain value already formatted into L2 format</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setApdL2GainSet(Axes axis, double APDGainL2) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	//APDGain: the default val is 7(2875 L2); range: 4(2048 L2) to 32(5120 L2)
	if (checkLimits(APDGainL2, 4, 32))
		return BAD_ARG_VALUE;
	zygoLogInfo("Setting APD Gain L2 to %lf on axis %u...\n", APDGainL2, axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDGainL2Set);
	uint_vme_data = static_cast<uint32_t>((std::log2(APDGainL2)) * 1024);
	//enableAuxRegisters(  axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code;
	}
	//disableAuxRegisters(  axis);
	return RET_SUCCESS;
}

/// <summary>
/// This function gets the value of APD Gain L2 Set register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDGain">The variable to store APDGain value in</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getApdL2GainSet(Axes axis, double* APDGainL2) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	//APDGain: the default val is 7(2875 L2); range: 4(2048 L2) to 32(5120 L2)
	zygoLogInfo("Getting APD Gain L2 on axis %u...\n", axis);
	if (APDGainL2 == NULL) {
		zygoLogWarn("APDGainL2 pointer can not be NULL \n");
		return BAD_ARG_POINTER;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDGainL2Set);
	//enableAuxRegisters(axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code;
	}
	*APDGainL2 = std::pow(2,(uint_vme_data/1024.0));
	//disableAuxRegisters(axis);
	return RET_SUCCESS;
}

/// <summary>
/// This function sets the value of APDSigRMSL2 register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDSigRMSL2">The APDSigRMSL2 value already formatted into L2 format</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setApdL2SigRmsSet(Axes axis, double APDSigRMSL2) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Setting APD Sig RMS L2 to 0x%04x on axis %u...\n", APDSigRMSL2, axis);
	uint_vme_data = static_cast<uint32_t>(std::log2(APDSigRMSL2) * 1024);
	if (checkLimits(uint_vme_data, 0, 0xFFFF)) {
		zygoLogWarn("Inapropriate value. range is 0 to 0xFFFF \n");
		return BAD_ARG_VALUE;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDSigRMSL2);
	//enableAuxRegisters(  axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code;
	}
	//disableAuxRegisters(  axis);
	return RET_SUCCESS;
}

/// <summary>
/// This function gets the value of APDSigRMSL2 register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="APDSigRMSL2">The variable to store APDSigRMSL2 value in</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getApdL2SigRmsSet(Axes axis, double* APDSigRMSL2) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("getting APD Sig RMS L2 on axis %u...\n", axis);
	if (APDSigRMSL2 == NULL) {
		zygoLogWarn("APDSigRMSL2 pointer can not be NULL \n");
		return BAD_ARG_POINTER;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDSigRMSL2);
	//enableAuxRegisters(axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code;
	}

	*APDSigRMSL2 = std::pow(2, uint_vme_data / 1024.0);
	return RET_SUCCESS;
}

int setApdL2SigRmsMaxLim(Axes axis, double maxLim) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Setting APD Sig RMS L2 Max Lim to 0x%04x on axis %u...\n", maxLim, axis);
	uint_vme_data = static_cast<uint32_t>(std::log2(maxLim) * 1024);
	if (checkLimits(uint_vme_data, 0, 0xFFFF)) {
		zygoLogWarn("Inapropriate value. range is 0 to 0xFFFF \n");
		return BAD_ARG_VALUE;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDSigRMSL2MaxLim);
	//enableAuxRegisters(  axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	//disableAuxRegisters(  axis);
	return RET_SUCCESS;
}

int getApdL2SigRmsMaxLim(Axes axis, double* maxLim) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("getting APD Sig RMS L2 Max Lim on axis %u...\n", axis);
	if (maxLim == NULL) {
		zygoLogWarn("APDSigRMSL2 pointer can not be NULL \n");
		return BAD_ARG_POINTER;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDSigRMSL2MaxLim);
	//enableAuxRegisters(axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}

	*maxLim = std::pow(2, uint_vme_data / 1024.0);
	return RET_SUCCESS;
}


int setApdL2SigRmsMinLim(Axes axis, double minLim) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Setting APD Sig RMS L2 Min Lim to 0x%04x on axis %u...\n", minLim, axis);
	uint_vme_data = static_cast<uint32_t>(std::log2(minLim) * 1024);
	if (checkLimits(uint_vme_data, 0, 0xFFFF)) {
		zygoLogWarn("Inapropriate value. range is 0 to 0xFFFF \n");
		return BAD_ARG_VALUE;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDSigRMSL2MinLim);
	//enableAuxRegisters(  axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	//disableAuxRegisters(  axis);
	return RET_SUCCESS;
}

int getApdL2SigRmsMinLim(Axes axis, double* minLim) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("getting APD Sig RMS L2 Min Limon axis %u...\n", axis);
	if (minLim == NULL) {
		zygoLogWarn("APDSigRMSL2 pointer can not be NULL \n");
		return BAD_ARG_POINTER;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDSigRMSL2MinLim);
	//enableAuxRegisters(axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}

	*minLim = std::pow(2, uint_vme_data / 1024.0);
	return RET_SUCCESS;
}
/// <summary>
/// This function sets the value of APD Opt Pwr L2 set register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis"> The axis number </param>
/// <param name="APDOptPwrL2">The APDOptPwrL2 value</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setApdL2OptPwrSet(Axes axis, double APDOptPwrL2) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	// the default value is 1uw(0 L2); range: 70nW(-3930 L2) to 10uW(3402 L2)
	zygoLogInfo("Setting APD optical power L2 to 0x%04x on axis %u...\n", APDOptPwrL2, axis);
	if (checkLimits(APDOptPwrL2, -3930, 3402))
	{
		zygoLogWarn("Inapropriate value. range is 0 to 0xFFFF \n");
		return BAD_ARG_VALUE;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDOptPwrL2Set);
	uint_vme_data = static_cast<uint32_t>(std::log2(APDOptPwrL2) * 1024);
	//enableAuxRegisters(  axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	//disableAuxRegisters(  axis);
	return RET_SUCCESS;
}

/// <summary>
/// This function gets the value of APD Opt Pwr L2 set register.
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis"> The axis number </param>
/// <param name="APDOptPwrL2">A pointer to the APDOptPwrL2 value</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getApdL2OptPwrSet(Axes axis, double* APDOptPwrL2) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	// the default value is 1uw(0 L2); range: 70nW(-3930 L2) to 10uW(3402 L2)
	zygoLogInfo("getting APD optical power L2 on axis %u...\n", axis);
	if (APDOptPwrL2 == NULL) {
		zygoLogWarn("APDOptPwrL2 pointer can not be NULL \n");
		return BAD_ARG_POINTER;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDOptPwrL2Set);
	//enableAuxRegisters(axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	*APDOptPwrL2 = std::pow(2, uint_vme_data / 1024.0);
	return RET_SUCCESS;
}

/*
int readMixingFrequencyForAllAxis(std::array<double, 4>& mxFreq) {
	double opt = 0.0;
	zygoLogInfo("Reading mixing frequency value on all axis...  \n");
	for (int i = 1; i < 5; i++)
	{
		if (return_code = readMixingFrequency(i, opt))
		{
			zygoLogWarn(" readMixingFrequency Failled !  \n"); return return_code;
		}
		mxFreq.at(i - 1) = opt;
		opt = 0.0;
	}
}
int readMixingFrequency(Axes axis, double& mxFreq) {
	double dcoptpwr;
	double acoptpwr;
	if (return_code = readOptPwrDC(axis, dcoptpwr))
	{
		zygoLogWarn(" readOptPwrDC Failled !  \n"); return return_code;
	}
	if (return_code = readOpticalPowerUsingSsiAv(axis, &acoptpwr))
	{
		zygoLogWarn(" readOptPwrDC Failled !  \n"); return return_code;
	}
	mxFreq = acoptpwr / dcoptpwr;
	return RET_SUCCESS;
}
*/
int readOptPwrDCForAllAxis(std::array<double, 4>& OptPwrDC) {

	double opt = 0.0;
	zygoLogInfo("Reading optical power DC value on all axis...  \n");
	for (const auto& i : AXES)
	{
		if (return_code = readOptPwrDC(i, opt))
		{
			zygoLogWarn(" readOptPwrDC Failled !  \n"); return return_code;
		}
		OptPwrDC.at(i - 1) = opt;
		opt = 0.0;
	}
}
int readOptPwrDC(Axes axis, double& OptPwrDC) {
	//The maximum signal level for this register is roughly 10 to 30 µm depending on the APD gain
	//Above this value, 100µW is set to the register
	// The minimum signal level for this register is 0.1 to 1µW. below this level, the measurement is not accuarate
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	OptPwrDC = 0.0;
	zygoLogInfo("getting APD optical power L2 on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zOptPwrDCL2);
	//enableAuxRegisters(axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	if (uint_vme_data == maxOptPwrDC_hex) {
		//zygoLogWarn("The value of optical power DC on axis %u  is above the maximum authorized, setting it to the constant value 100µW\n", axis);
		OptPwrDC = maxOptPwrDC;
	}
	else if (uint_vme_data == minOptPwrDC_hex) {
		zygoLogWarn("The value of optical power DC on axis %u is below the minimum authorized, setting it to the constant value 0.01µW\n",axis);
		OptPwrDC = minOptPwrDC;
	}
	else
		OptPwrDC = std::pow(2, uint_vme_data / 1024.0);
	//disableAuxRegisters(axis);
	return RET_SUCCESS;
}

/// <summary>
/// This function specifies the value of APD Bias DAC register
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="ApdBiasVoltage_mV">The ApdBiasVoltage value in mV</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int setApdBiasVoltage(Axes axis, double ApdBiasVoltage_mV) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Setting APD BIAS DAC L2 to 0x%04x on axis %lf mV...\n", ApdBiasVoltage_mV, axis);

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDBiasDAC);
	uint_vme_data = static_cast<uint32_t>(ApdBiasVoltage_mV/ ApdBiasVoltageCoeff);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	return RET_SUCCESS;
}


/// <summary>
/// This function specifies the value of APD Bias DAC register
/// </summary>
/// <param name="dev">device</param>
/// <param name="axis">the axis number</param>
/// <param name="ApdBiasVoltage_mV">the pointer to ApdBiasVoltage value in mV</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int getApdBiasVoltage(Axes axis, double* ApdBiasVoltage_mV) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("getting APD BIAS DAC L2 on axis %u...\n", axis);
	if (ApdBiasVoltage_mV == NULL) {
		zygoLogWarn("ApdBiasVoltage pointer can not be NULL \n");
		return BAD_ARG_POINTER;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDBiasDAC);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	*ApdBiasVoltage_mV = uint_vme_data * ApdBiasVoltageCoeff;
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
int parseVmeErrorStatus2(Axes axis, uint32_t* VMEErrorStatus2Reg) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Parsing VME Error Status 2 on axis %u...\n", axis);
	zygoLogInfo("-------------------------------------------------------------------");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat2);		//Read VME errors
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	zygoLogInfo("Axis %u VME Status Error 2: %X \n", axis, uint_vme_data);
	*VMEErrorStatus2Reg = uint_vme_data;

	if (uint_vme_data & (1 << 14))
		zygoLogInfo("Proc fail has been detected\n");
	if (uint_vme_data & (1 << 13))
		zygoLogInfo("Bias supply error has been detected\n");
	if (uint_vme_data & (1 << 12))
		zygoLogInfo("Write Protect error has been detected\n");
	if (uint_vme_data & 0x80) {
		zygoLogInfo("Sig max has been detected, The input signal's optical power is above the allowed range\n");
		zygoLogInfo("Fix: -Try to increase the max optical power in SSI MAX register\n ");
		zygoLogInfo("     -Reduce the input optical power using a neutral density filter\n ");
	}
	if (uint_vme_data & (1 << 6)) {
		zygoLogInfo("Sig min has been detected, The input signal's optical power is below the allowed range\n");
		zygoLogInfo("Fix: -Try to decrease the min optical power in SSI min register\n ");
		zygoLogInfo("     -Increase the input signal's optical power \n ");
	}
	if (uint_vme_data & (1 << 4))
		zygoLogInfo("Bias Error has been detected\n");
	if (uint_vme_data & (1 << 3))
		zygoLogInfo("APD DC Error has been detected\n");
	if (uint_vme_data & (1 << 2))
		zygoLogInfo("APD command Error has been detected\n");
	if (uint_vme_data & (1 << 1))
		zygoLogInfo("APD Fail Error has been detected\n");
	if (uint_vme_data & (1 << 0))
		zygoLogInfo("APD Temp Error has been detected\n");
	zygoLogInfo("-------------------------------------------------------------------");

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
int parseVmePosErrs(Axes axis, uint32_t* VMEPosErrReg) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Parsing VME Error position errors on axis %u...\n", axis);
	zygoLogInfo("-------------------------------------------------------------------");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEPosErr);		//Read VME errors
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	zygoLogInfo("Axis %u Position Errors: %X \n", axis, uint_vme_data);
	*VMEPosErrReg = uint_vme_data;
	if (uint_vme_data & (1 << 3))
		zygoLogInfo("Measurement Error has been detected\n");
	if (uint_vme_data & (1 << 1))
		zygoLogInfo("Ref Error has been detected\n");
	zygoLogInfo("-------------------------------------------------------------------");
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
int parseVmeErrorStatus1(Axes axis, uint32_t* VMEErrorStatus1Reg) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Parsing VME Error Status 1 on axis %u...\n", axis);
	zygoLogInfo("-------------------------------------------------------------------");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat1);		//Read VME errors
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	zygoLogInfo("Axis %u VME Status Error 1: %X \n", axis, uint_vme_data);
	*VMEErrorStatus1Reg = uint_vme_data;
	if (uint_vme_data & (1 << 3))
		zygoLogInfo("VME 32bits postion register has overflowed\n");
	if (uint_vme_data & (1 << 2))
		zygoLogInfo("VME 37bits postion has overflowed\n");
	if (uint_vme_data & (1 << 1))
		zygoLogInfo("User velocity error has been detected\n");
	if (uint_vme_data & (1 << 0))
		zygoLogInfo("Velocity error has been detected\n");
	zygoLogInfo("-------------------------------------------------------------------");
	return RET_SUCCESS;
}

int getLedsErrorStatus(bool* ledsErrorStatus) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("running getLedsErrorStatus\n");
	for (int axis = 0; axis < 4; axis++) {
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis)], zVMEErrStat0);
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
		if ((uint_vme_data & 0x1B20)) {
			ledsErrorStatus[axis] = true;
		}
		else
		{
			ledsErrorStatus[axis] = false;
		}
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis)], zVMEErrStat2);		
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
		if ((uint_vme_data & 0x001A)) {
			ledsErrorStatus[axis] = true;
		}
		else
		{
			ledsErrorStatus[axis] = ledsErrorStatus[axis] | false;
		}
	}

	/*uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zVMEErrStat2);		//Read VME errors
	if (return_code=readWrite("A24D16",   uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}*/
	if ((uint_vme_data & 0xA)) {
		ledsErrorStatus[4] = true;
	}
	else
	{
		ledsErrorStatus[4] = false;
	}

	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zVMEErrStat0);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	if ((uint_vme_data & 0x2C)) {
		ledsErrorStatus[4] = true;
	}
	else
	{
		ledsErrorStatus[4] = ledsErrorStatus[4] | false;
	}

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
int parseVmeErrorStatus0(Axes axis, uint32_t* VMEErrorStatus0Reg) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Parsing VME Error Status 0 on axis %u...\n", axis);
	zygoLogInfo("-------------------------------------------------------------------");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat0);		//Read VME errors
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	zygoLogInfo("Axis %u VME Status Error 0: %X \n", axis, uint_vme_data);
	*VMEErrorStatus0Reg = uint_vme_data;

	if (uint_vme_data & 0x8000)
		zygoLogInfo("CEC Error has been detected\n");
	if (uint_vme_data & 0x4000)
		zygoLogInfo("Phase noise Error has been detected\n");
	if (uint_vme_data & 0x2000)
		zygoLogInfo("Acceleration Error has been detected\n");
	if (uint_vme_data & 0x1000)
		zygoLogInfo("Measure signal glitch has been detected\n");
	if (uint_vme_data & 0x800)
		zygoLogInfo("Measure signal dropout has been detected\n");
	if (uint_vme_data & 0x400)
		zygoLogInfo("SSI Max limit has been detected\n");
	if (uint_vme_data & 0x200)
		zygoLogInfo("Measure signal is saturated\n");
	if (uint_vme_data & 0x100)
		zygoLogInfo("Measure signal is missing\n");
	if (uint_vme_data & 0x80)
		zygoLogInfo("Overtemp error has been detected\n");
	if (uint_vme_data & 0x40)
		zygoLogInfo("FPGA Sync error has been detected\n");
	if (uint_vme_data & 0x20)
		zygoLogInfo("Reset faillure has been detected\n");
	if (uint_vme_data & 0x8)
		zygoLogInfo("Reference PLL Error has been detected\n");
	if (uint_vme_data & 0x4)
		zygoLogInfo("Reference signal is missing\n");
	if (uint_vme_data & 0x2)
		zygoLogInfo("Write error has been detected\n");
	if (uint_vme_data & 0x1)
		zygoLogInfo("Power error has been detected\n");
	zygoLogInfo("-------------------------------------------------------------------");
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
int parseApdErrCode(Axes axis, uint32_t* APDErrCode) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	zygoLogInfo("Parsing APD Error code on axis %u...\n", axis);
	zygoLogInfo("-------------------------------------------------------------------");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDErr);		//Read APD errors
	//enableAuxRegisters(  axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	zygoLogInfo("Axis %u APD Error Code: %X \n", axis, uint_vme_data);
	*APDErrCode = uint_vme_data;
	//disableAuxRegisters(  axis);

	switch (uint_vme_data & 0x00FF)
	{
	case 0:
		zygoLogInfo("No APD Axis error \n");
		break;
	case 1:
		zygoLogInfo("[zygoLogFatal BOARD] APD Temp Init Error  \n");
		break;
	case 2:
		zygoLogInfo("[zygoLogFatal BOARD] Bias range Init Error  \n");
		break;
	case 3:
		zygoLogInfo("DC Meas Low Init Error \n");
		break;
	case 7:
		zygoLogInfo("[zygoLogFatal BOARD] Bias Limit Init Error  \n");
		break;
	case 128:
		zygoLogInfo("APD Gain Set Error \n");
		break;
	case 129:
		zygoLogInfo("Sig RMS Set Error \n");
		break;
	case 130:
		zygoLogInfo("Optical Power Set error \n");
		break;
	case 8:
		zygoLogInfo("[zygoLogFatal BOARD] DC Meas High Init Error \n");
		break;
	case 9:
		zygoLogInfo("[zygoLogFatal BOARD] Bias Limit Op Error \n");
		break;
	case 133:
		zygoLogInfo("Sig RMS call max error \n");
		break;
	case 134:
		zygoLogInfo("Sig RMS call min error \n");
		break;
	case 135:
		zygoLogInfo("APD MATH GAIN error \n");
		zygoLogInfo("\t Invalid APD Gain, should be in the range 4 to 32 \n");
		break;
	case 136:
		zygoLogInfo("APD Math Poly error, Invalid APD bias equation coeffs(0) \n");
		break;
	case 137:
		zygoLogInfo("APD Math Temp error, Invalid APD temperature, range is 10 degreeC to 70 degreeC \n");
		break;
	case 138:
		zygoLogInfo("APD Math T0, Invalid APD bias equation T0, range is 10 degreeC to 50 degreeC \n");
		break;
	case 139:
		zygoLogInfo("APD Math TC, Invalid APD bias equation TC, range is 0.3 to 0.9V/degreeC \n");
		break;
	case 140:
		zygoLogInfo("APD Temp Op Error \n");
		break;
	case 141:
		zygoLogInfo("Bias range Op Error, \n\tAPD Bias failed range check after axis initialization (deviation > 10 V after 0.5 sec)\n");
		break;
	case 142:
		zygoLogInfo("DC Meas Low Op Error,  Meas DC failed low limit check (-4.5 V) after axis initialization\n\t \n");
		break;
	case 143:
		zygoLogInfo("DC Meas Hi Op Error,  Meas DC failed high limit check (-1.4 V) after axis initialization\n\t \n");
		break;
	default:
		zygoLogInfo("Unknow APD Axis error code \n");
		break;
	}


	switch ((uint_vme_data >> 8) & 0x00FF)
	{
	case 0:
		zygoLogInfo("No APD System error \n");
		break;
	case 1:
		zygoLogInfo("[zygoLogFatal BOARD] HV Init error: HV failed limit test during board initialization\n");
		break;
	case 2:
		zygoLogInfo("[zygoLogFatal BOARD] LV Init error: LV failed limit test during board initialization\n");
		break;
	case 3:
		zygoLogInfo("[zygoLogFatal BOARD] FOR Init Error: Fiber Optic Receiver not detected during board initialization (no APD temp)\n");
		break;
	case 4:
		zygoLogInfo("[zygoLogFatal BOARD] LV OK Timeout Error:  Slave did not detect LV_OK within allotted time\n");
		break;
	case 5:
		zygoLogInfo("[zygoLogFatal BOARD] Slave Act FOR Timeout: Master did not receive Slave response that FOR detected\n");
		break;
	case 6:
		zygoLogInfo("[zygoLogFatal BOARD] HV OK Timeout: Slave did not detect HV_OK within allotted time\n");
		break;
	case 7:
		zygoLogInfo("[zygoLogFatal BOARD]  EE Cal Read Error: Master unable to read EE calibration data\n");
		break;
	case 8:
		zygoLogInfo("[zygoLogFatal BOARD] EE Cal Xfer Error: EE Cal transfer to Slave failed or timeout\n");
		break;
	case 9:
		zygoLogInfo("[zygoLogFatal BOARD]  CEC Ver Timeout:  Slave failed to tell Master that CEC enabled\n");
		break;
	case 10:
		zygoLogInfo("[zygoLogFatal BOARD]  Ovr Ver Timeout: Master unable to verify that Override enabled on Slave\n");
		break;
	case 11:
		zygoLogInfo("[zygoLogFatal BOARD] Illegal Opcode Error: Hardware exception due to an attempt to execute an illegal opcode\n");
		break;
	case 12:
		zygoLogInfo("[MATH ERROR] Divide By Zero Error \n");
		break;
	case 128:
		zygoLogInfo("[zygoLogFatal BOARD] HV Operation error: HV Failed limits after board initialization \n");
		zygoLogInfo("\t Invalid APD Gain, should be in the range 4 to 32 \n");
		break;
	case 129:
		zygoLogInfo("[zygoLogFatal BOARD] LV Operation error:  LV reading failed limit test after board initialization\n");
		break;
	case 130:
		zygoLogInfo("[NOT zygoLogFatal] EEprom Checksum Error: EEprom Checksum Error during Board Initialization \n");
		break;
	case 131:
		zygoLogInfo("[zygoLogFatal BOARD] Slave Timeout Op: The Slave did not respond to the Master within the specified time\n");
		break;
	case 132:
		zygoLogInfo("[zygoLogFatal BOARD] Slave Req. Not Conf. Op error: Master unable to confirm the request for Slave status\n");
		break;
	case 133:
		zygoLogInfo("[zygoLogFatal BOARD] Master Rcvd Slave zygoLogFatal error: Master received zygoLogFatal error status from Slave\n");
		break;

	default:
		zygoLogInfo("Unknow APD System error code \n");
		break;
	}
	zygoLogInfo("-------------------------------------------------------------------");
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
int readSamplePosition37(Axes axis, double* position) {
	short val;
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	int temp32 = 0;
	//zygoLogInfo("Reading the 37bits sample Position value on Axis %d...  \n", axis);

	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMESampPosMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	temp32 = (uint32_t)uint_vme_data;
	uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMESampPosExt);		//Read the Ext
	if (return_code = readWrite("A24D8", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	val = (short)uint_vme_data;
	if ((val & 0x80) != 0) { // check if the ext value is negative
		*position = static_cast<double>((short)(0xff00 + static_cast<uint32_t>(val & 0xff)));
		*position = ((*position) * (TMP32)) + temp32;
	}
	else {
		*position = ((val & 0xFF) * (TMP32)) + temp32;
	}
	zygoLogInfo("37 bits position is %lf\n", *position);
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
int readSamplePosition32(Axes axis, double* position) {

	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	//zygoLogInfo("Reading the 32bits sample Position value on Axis %d...  \n", axis);

	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMESampPosMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}

	*position = static_cast<double>((int)(uint_vme_data) * (positionScale));
	return RET_SUCCESS;
}

int setPrecision(bool prec) {
	zygoLogInfo("Modifying register position from %s to %s\n", curPrecision ? "37 bits" : "32 bits", prec ? "37 bits" : "32 bits");
	double pres[4];
	double off[4];
	for (const auto& axis : AXES) {
		getPresetPosition(axis, pres + (static_cast<int>(axis) - 1));
		getPositionOffset(axis, off + (static_cast<int>(axis) - 1));
	}
	zygoLogInfo("Preset position values: %lf, %lf, %lf, %lf\n", pres[0], pres[1], pres[2], pres[3]);
	if (prec) { //37 bits

		for (const auto& axis : AXES) {
			if (return_code = disable32BitsOverflow(axis))
			{
				zygoLogWarn(" Disable32bitsSignExtension Failled !  \n"); return return_code;
			}
			if (return_code = enable37BitsSignExtension(axis))
			{
				zygoLogWarn(" enable37BitsSignExtension Failled !  \n"); return return_code;
			}
		}
	}
	else { //32 bits
		for (const auto& axis : AXES) {
			if (return_code = enable32BitsOverflow(axis))
			{
				zygoLogWarn(" enable32BitsOverflow Failled !  \n"); return return_code;
			}
			if (return_code = disable37bitsSignExtension(axis))
			{
				zygoLogWarn(" disable37bitsSignExtension Failled !  \n"); return return_code;
			}
		}
	}
	curPrecision = prec;
	for (const auto& axis : AXES) {
		//convert 32bits preset position
		setPresetPosition(axis, pres + (static_cast<int>(axis) - 1));
		setPositionOffset(axis, off + (static_cast<int>(axis) - 1));
	}
	return RET_SUCCESS;
}
bool getPrecision() {

	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	// Enable auxiliary registers
	zygoLogInfo("Getting axes precision\n");
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zCtrl0);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("readWrite at 0x%6X Failed !  \n", uint_vme_address);
		return return_code;
	}
	curPrecision = (uint_vme_data & 0x40) ? 1 : 0;
	zygoLogInfo("current precision is  %s\n", curPrecision? "37bits":"32bits");
	return curPrecision;
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
int readFifoPosition(Axes axis, uint32_t* position) {

	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;

	zygoLogInfo("Reading FIFO Position on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEFifoPos);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
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
int readVelocity(Axes axis, double* velocity) {

	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEVelocMSB);
	if (return_code = sampleVmePosition(axis))
	{
		zygoLogWarn("readVelocity: sampleVmePosition Failled !  \n"); return return_code;
	}// the function both sample velocity and value
	//Read the MSB and LSB	
	if (return_code = setHoldSampEnable(axis))
	{
		zygoLogWarn("readVelocity:  setHoldSampEnable Failled !  \n"); return return_code;
	}
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("readVelocity: Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	if (return_code = resetHoldSampEnable(axis))
	{
		zygoLogWarn("readVelocity:  resetHoldSampEnable Failled !  \n"); return return_code;
	}
	*velocity = static_cast<double>((int)uint_vme_data) * velocityScale;
	return RET_SUCCESS;
}

int readVelocityForAllAxis(double* Velocity32_buf) {

	double Velocity = 0.0;
	zygoLogInfo("Reading the 32bits velocity value on all axis...  \n");
	for (const auto& i : AXES){
		if (return_code = readVelocity(i, &Velocity))
		{
			zygoLogWarn(" ReadVelocity32 Failled !  \n"); return return_code;
		}
		*(Velocity32_buf + (static_cast<int>(i) - 1)) = Velocity;
		Velocity = 0.0;
	}
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
int readPosition(Axes axis, double* position) {
	short val = 0;
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0, temp32 = 0;
	//read sample position
	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMESampPosMSB);
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("readPosition: Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}

	if (curPrecision) {//37 bits read

		temp32 = (uint32_t)uint_vme_data;
		uint_vme_data = 0;
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMESampPosExt);		//Read the Ext
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("readPosition: Register %6X access Faillure !  \n", uint_vme_address);
			return return_code;
		}
		val = (short)uint_vme_data;
		//*
		if ((val & 0x10) != 0) { // check if the ext value is negative
	
			*position = static_cast<double>((short)((short)0xffe0 + (val & 0x1f)));
			
			*position = (((*position) * (TMP32)) + temp32) * positionScale;
			
		}
		else {
			*position = (((val & 0x1F) * (TMP32)) + temp32)* positionScale;
		}
		//*/

		zygoLogInfo("37 bits position is %lf\n", *position);
	}
	else {//32 bits read
		*position = (static_cast<double>((int)uint_vme_data)) * positionScale;
		zygoLogInfo("32 bits position is %lf\n", *position);
	}
	return RET_SUCCESS;
}
int readPositionForAllAxis(double* PositionBuf) {

	double position = 0.0;
	zygoLogInfo("Reading the position value on all axis...  \n");
	for (const auto& i : AXES)
	{
		if (return_code = readPosition(i, &position))
		{
			zygoLogWarn(" ReadPosition Failled !  \n"); 
			return return_code;
		}
		*(PositionBuf + (static_cast<int>(i) - 1)) = position;
		position = 0.0;
	}
	return RET_SUCCESS;
}
bool isVmePos32Overflow(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	zygoLogInfo("Checking VME 32bits position overflow \n ");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return FALSE;
	}
	if ((uint_vme_data & 0x0008))
		return TRUE;
	return FALSE;
}
bool IsVMEPos37Overflow(Axes axis) {

	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Checking VME 37bits position overflow \n ");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return false;
	}
	if ((uint_vme_data & 0x0004))
		return true;
	return false;
}
bool IsUserVelError(Axes axis) {

	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Checking VME 32bits position overflow bit...\n ");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return false;
	}
	if ((uint_vme_data & 0x0002))
		return true;
	return false;
}
bool IsVelError(Axes axis) {

	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Checking velocity error bit...\n ");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return false;
	}
	if ((uint_vme_data & 0x0001))
		return true;
	return false;
}
bool IsAccError(Axes axis) {

	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Checking acceleration error bit...\n ");
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat0);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return false;
	}
	if (uint_vme_data & 0x2000)
		return true;
	return false;
}
int ClearPosAndVelErrs(Axes axis) {

	uint32_t uint_vme_data = 0xF, uint_vme_address = 0;

	zygoLogInfo("Reseting Position and velocity errors on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrClr1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	return RET_SUCCESS;
}
int ClearAllVMEErrs(Axes axis) {

	uint32_t uint_vme_data = 0xFFFF,
		uint_vme_address = 0;

	zygoLogInfo("Reseting all VME errors on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrClr0);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrClr1);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrClr2);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	uint_vme_data = 1;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCmd);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
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
int clearPosAndVelErrsForAllAxis(Axes axis) {

	uint32_t uint_vme_data = 0xFFFF,
		uint_vme_address = 0;

	for (const auto& i : AXES)
	{
		if (return_code = ClearPosAndVelErrs(i))
		{
			zygoLogWarn("ClearPosAndVelErrs Failled !  \n"); return return_code;
		}
	}

	return RET_SUCCESS;
}
/// <summary>
/// ClearAllVMEErrs_ForAllAxis: 
/// Clear VME Errors for all axis(1 to 4).
/// Rmk: Doesn't clear zygoLogFatal Board errors
/// </summary>
/// <param device="dev"></param>
/// <param measurement_axis="axis"></param>
/// <returns>
/// 0 if successful
/// </returns>
int clearAllVMEErrsForAllAxis() {

	for (const auto& i : AXES)
	{
		if (return_code = ClearAllVMEErrs(i))
		{
			zygoLogWarn(" ClearAllVMEErrs Failled !  \n"); return return_code;
		}
	}


	return RET_SUCCESS;
}
/*This fuction reads the ZMI "Time Register" on 32 bits
*/
int readTime(Axes axis, double* time) {

	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;

	zygoLogInfo("Reading Elapsed time on Axis %d...  \n", axis);
	//Read the MSB and LSB
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMETimeMSB);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	*time = uint_vme_data * timeScale;
	zygoLogInfo("-------------------------------------------------------\n");
	zygoLogInfo("Elapsed time is : %f ms\n", *time);
	zygoLogInfo("-------------------------------------------------------\n");
	return RET_SUCCESS;
}
int readTimeForAllAxis(double* Time32_buf) {

	double time = 0.0;
	for (const auto& i : AXES)
	{
		if (return_code = readTime(i, &time))
		{
			zygoLogWarn(" ReadTime32 Failled !  \n"); return return_code;
		}
		*(Time32_buf + (static_cast<int>(i) - 1)) = time;
		time = 0.0;
	}
	return RET_SUCCESS;
}
int resetTime(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Reseting Time on Axis: %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCmd);
	uint_vme_data = (1 << 3);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn(" readModifyWrite Failled !  \n"); return return_code;
	}

}
int ResetPositionQuick(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Quick position reset on Axis: %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCmd);
	uint_vme_data = (1 << 4);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn(" readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int resetPosition(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Reseting Position on Axis: %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCmd);
	uint_vme_data = (1 << 2);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn(" readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int enablePreset(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Enabling preset position on Axis: %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl3);
	uint_vme_data = (1 << 8);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn(" readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int enableSclkResetOnAxisReset(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Enabling sampling clock reset on axis %u reset...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl3);
	uint_vme_data = (1 << 9);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn(" readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int disableSCLKResetOnAxisReset(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Disabling sampling clock reset on axis %u reset...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl3);
	uint_vme_data = ~(1 << 9);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn(" readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int enableResetFindsVelocity(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Enabling reset finds velocity  on Axis %d... \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl3);
	uint_vme_data = (1 << 11);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn(" readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int enableResetFindsVelocityForAllAxis()
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	for (const auto& i : AXES) {

		if (return_code = enableResetFindsVelocity(i))
		{
			zygoLogWarn(" EnableResetFindsVelocity Failled !  \n"); return return_code;
		}
	}
	return RET_SUCCESS;

}

int disableResetFindsVelocity(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Disabling reset finds velocity  on Axis %d... \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl3);
	uint_vme_data = ~(1 << 11);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn(" readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}

int disableResetFindsVelocityForAllAxis()
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;

	for (const auto& i : AXES) {
		if (return_code = disableResetFindsVelocity(i))
		{
			zygoLogWarn(" DisableResetFindsVelocity Failled !  \n"); return return_code;
		}
	}
	return RET_SUCCESS;

}


int getVMEBusSampleClk(Axes axis, SCLK& clk)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;

	zygoLogInfo("getting sample source clock  on axis %u ... \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	clk = static_cast<SCLK>((uint_vme_data & 0x1000) >> 12);
	zygoLogInfo("sample source clock on axis %u is %s... \n", axis, (clk == SCLK::SCLK0 ? "SCLK0" : "SCLK1"));
	currentResetSclk = clk;
	return RET_SUCCESS;

}

int setResetSourceClock(Axes axis, SCLK clk)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;

	zygoLogInfo("Setting reset source clock to %s on axis %u ... \n", (clk == SCLK::SCLK0 ? "SCLK0" : "SCLK1"), axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl3);
	
	if (static_cast<bool>(clk)) {
		uint_vme_data = 0x0400;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
		{
			zygoLogWarn("readModifyWrite failed !  \n");
			return return_code;
		}
	}
	else {
		uint_vme_data = 0XFBFF;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("readModifyWrite failed !  \n");
			return return_code;
		}
	}

	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite failed !  \n");
		return return_code;
	}
	currentResetSclk = clk;
	return RET_SUCCESS;

}


int getResetSourceClock(Axes axis, SCLK& clk)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;

	zygoLogInfo("getting reset source clock  on axis %u ... \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl3);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	clk = static_cast<SCLK>((uint_vme_data & 0x400) >> 10);
	zygoLogInfo("Reset source clock on axis %u is %s... \n", axis, clk == SCLK::SCLK0 ? "SCLK0" : "SCLK1");
	currentResetSclk = clk;
	return RET_SUCCESS;

}


int setTimeDelayBetweenResAndCompleteBit(Axes axis, uint8_t timeDelay)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Setting time delay between axis %d and the assertion of position reset complete bit to %u... \n", axis, timeDelay);
	if (((int)timeDelay) > 7)
	{
		zygoLogWarn("Time delay value is ranged 0 to 7\n"); return return_code;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl3);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	uint_vme_data |= (timeDelay << 12);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	zygoLogInfo("Setting time delay between axis reset and and reset complete assertion on Axis: %d  \n", axis);
	return RET_SUCCESS;

}

int readScaledSsiAv(Axes axis, double* ssiPtr) {
	if (return_code = readSsiAv(axis, ssiPtr))
	{
		zygoLogWarn("readSsiAv failed !  \n");
		return return_code;
	}
	*ssiPtr *= SSIScale;
	return RET_SUCCESS;
}

/// <summary>
/// Returns the SSI value in mV
/// </summary>
/// <param name="dev">device</param>
/// <param name="ssiPtr">value return parameter</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int readScaledSsiAvForAllAxis(double* ssiPtr) {
	for (const auto& i : AXES) {
		if (return_code = readScaledSsiAv(i, ssiPtr + (static_cast<int>(i) - 1)))
		{
			zygoLogWarn("readSsiAvForAllAxis failed !  \n");
			return return_code;
		}
	}
	return RET_SUCCESS;
}

int readSsiAv(Axes axis, double* ssiPtr) {
	uint32_t uint_vme_address = 0;
	uint32_t  uint_vme_data = 0;
	// The max SSI Average value (0xFFFF) corresponds to 1.25V
	//zygoLogInfo("Reading SSI average on Axis %u...  \n", i + 1);
	/*/
	if (return_code = resetAxis(  i+1))
	{
		zygoLogWarn("resetAxis failed !  \n");
		return return_code;
	}
	//*/
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis)-1], zSSIAvg);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	*ssiPtr = static_cast<double>(uint_vme_data);
	return RET_SUCCESS;
}
/// <summary>
/// Returns the SSI bare value in decimal
/// </summary>
/// <param name="dev">device</param>
/// <param name="ssiPtr">value return parameter</param>
/// <returns>
/// 0 if success
/// -1 else
/// </returns>
int readSsiAvForAllAxis(double* ssiPtr) {
	uint32_t uint_vme_address = 0;
	uint32_t  uint_vme_data = 0;
	for (const auto& i : AXES)
	{
		if (return_code = readSsiAv(i, ssiPtr + (static_cast<int>(i) - 1)))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}

	}
	return RET_SUCCESS;
}
int readOpticalPowerUsingSsiAv(Axes axis, double* OpticalPower_uW) {
	double APD_Gain[1], SSI[1];
	if (return_code = readSsiAv(axis, SSI))
	{
		zygoLogWarn("readSsiAv failed !  \n");
		return return_code;
	}
	if (return_code = readApdGain(axis, APD_Gain))
	{
		zygoLogWarn("readApdGainForAllAxis failed !  \n");
		return return_code;
	}
	*OpticalPower_uW = *SSI * 0.00218 / *APD_Gain;
	if (*OpticalPower_uW < 0)
	{
		*OpticalPower_uW = 0;
		zygoLogInfo("-------------------------------------------------------\n");
		zygoLogInfo("[WARNING] SSI is negative on axis %d. Setting it to 0...%u\n", axis);
		zygoLogInfo("Optical Power on axis %d is %f uW\n", axis, *OpticalPower_uW);
		zygoLogInfo("-------------------------------------------------------\n");
	}
	else
	{
		zygoLogInfo("-------------------------------------------------------\n");
		zygoLogInfo("Optical Power on axis %d is %f uW\n", axis, *OpticalPower_uW);
		zygoLogInfo("-------------------------------------------------------\n");
	}
	return RET_SUCCESS;
}
int readOpticalPowerUsingSsiAvForAllAxis(double* OpticalPower_uW) {
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;

	double APD_Gain[] = { 0.0, 0.0, 0.0, 0.0 },
		SSI[] = { 0.0, 0.0, 0.0, 0.0 };

	if (return_code = readSsiAvForAllAxis(SSI))
	{
		zygoLogWarn("readSsiAv failed !  \n");
		return return_code;
	}
	if (return_code = readApdGainForAllAxis(APD_Gain))
	{
		zygoLogWarn("readApdGainForAllAxis failed !  \n");
		return return_code;
	}

	for (int i = 0; i < 4; i++)
	{
		OpticalPower_uW[i] = SSI[i] * 0.00218 / APD_Gain[i];
		if (OpticalPower_uW[i] < 0)
		{
			OpticalPower_uW[i] = 0;
			zygoLogInfo("-------------------------------------------------------\n");
			zygoLogInfo("[WARNING] SSI is negative on axis %d. Setting it to 0...%u\n", i + 1);
			zygoLogInfo("Optical Power on axis %d is %f uW\n", i + 1, OpticalPower_uW[i]);
			zygoLogInfo("-------------------------------------------------------\n");
		}
		else
		{
			zygoLogInfo("-------------------------------------------------------\n");
			zygoLogInfo("Optical Power on axis %d is %f uW\n", i + 1, OpticalPower_uW[i]);
			zygoLogInfo("-------------------------------------------------------\n");
		}
	}

	return RET_SUCCESS;
}
int setSsiSquelch(Axes axis, uint32_t squelchValue) {

	//Set SSI Squelch(minimum AC optical signal that causes measurement signal ZMIError)
	// default value is 0x80
	//SSI Squelch is only 12bits, so max is 4095 (0x0FFF) or about __ uW
	uint32_t value = 0;
	uint32_t uint_vme_address = 0;
	zygoLogInfo("Setting SSI Squelch value to %d on axis %u...\n", squelchValue, axis);
	if (squelchValue > 0xFFF)
	{
		zygoLogInfo("[SSI_Squelch] Value given is too large or negative, setting to default value(0x80)\n");
		value = 0x80; // Setting to default value
	}
	else
		value = (short)(squelchValue & 0xFFF);

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zSSISquelch);
	if (return_code = readWrite("A24D16", uint_vme_address, &value, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	return RET_SUCCESS;
}
int getSsiSquelch(Axes axis, uint32_t* squelchValue) {

	//get SSI Squelch(minimum AC optical signal that causes measurement signal ZMIError)
	// default value is 0x80
	//SSI Squelch is only 12bits, so max is 4095 (0x0FFF) or about __ uW
	uint32_t value = 0;
	uint32_t uint_vme_address = 0;
	if (squelchValue == NULL)
		return BAD_ARG_VALUE;
	zygoLogInfo("getting SSI Squelch value  on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zSSISquelch);
	if (return_code = readWrite("A24D16", uint_vme_address, &value, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	*squelchValue = static_cast<double>(value);
	return RET_SUCCESS;
}

int getSsiMaxVal(Axes axis, uint32_t* SSIMax)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;

	zygoLogInfo("Getting SSI max value  on axis %u...\n", axis);
	// The SSI max value (0xFFFF) corresponds to 1.25V

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zSSIMax);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	*SSIMax = uint_vme_data;
	zygoLogInfo("SSI Max val on Axis %u is : %d  \n", axis, uint_vme_data);
	return RET_SUCCESS;

}
int getSsiMaxValForAllAxis(uint32_t* SSIMax_Buf)
{
	zygoLogInfo("Getting SSI max value  on all axis... \n");
	uint32_t uint_vme_data = 0;
	for (const auto& i : AXES)
	{
		// The SSI max value (0xFFFF) corresponds to 1.25V
		if (return_code = getSsiMaxVal(i, &uint_vme_data))
		{
			zygoLogWarn("readApdGainForAllAxis failed !  \n");
			return return_code;
		}
		*(SSIMax_Buf + (static_cast<int>(i) - 1)) = uint_vme_data;
	}

	return RET_SUCCESS;

}
int resetSSIMinAndMax(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Reseting SSI max and min values  on axis %u...\n", axis);
	// The SSI max value (0xFFFF) corresponds to 1.25V
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zTestCmd0);
	uint_vme_data = 0x2;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int resetPhaseNoisePeak(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Reseting SSI phase noise peak on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zTestCmd0);
	uint_vme_data = 0x1;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int resetSigRmsL2MinAndMax(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Reseting SigRMSL2 min and max on axis %u...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zTestCmd0);
	uint_vme_data = (1 << 2);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}

	return RET_SUCCESS;

}
int setGainControlMax(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	zygoLogInfo("Enabling Gain control max value on axis %u...\n", axis);
	uint_vme_data = (1 << 3);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;
}
int setGainControlMin(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);
	zygoLogInfo("Enabling Gain control min value on axis %u...\n", axis);
	uint_vme_data = (1 << 4);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}

	return RET_SUCCESS;
}
int adjustGainControl(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);
	zygoLogInfo("Allowing Gain control to be continuously be adjusted in response to changing signal levels on axis %u...\n", axis);

	uint_vme_data = (1 << 5);
	return RET_SUCCESS;
}
int resetOptPowL2MinAndMax(Axes axis)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Reseting optical power min and max on axis %u...\n", axis);
	// The SSI max value (0xFFFF) corresponds to 1.25V
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zTestCmd0);

	uint_vme_data = (1 << 2);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;

}
int checkSaturation(Axes axis, bool* sat)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Checking signal saturation on axis %u...\n", axis);
	// The SSI max value (0xFFFF) corresponds to 1.25V

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat0);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	if (uint_vme_data & (0x200))
	{
		zygoLogInfo("Measurement signal is saturated on Axis %u...  \n", axis);
		if (return_code = getSsiMaxVal(axis, &uint_vme_data))
		{
			zygoLogWarn("getSsiMaxVal Failled !  \n"); return return_code;
		}
		zygoLogInfo("The SSI max register on this axis has the value %u. ", uint_vme_data);
		zygoLogInfo("This value should be lesser than %u...  \n", SSI_MAX_SAT);
		*sat = true;
	}
	else
	{
		zygoLogInfo("Measurement signal is not saturated on Axis %u...  \n", axis);
		if (return_code = getSsiMaxVal(axis, &uint_vme_data))
		{
			zygoLogWarn("getSsiMaxVal Failled !  \n"); return return_code;
		}
		zygoLogInfo("The SSI max register on this axis has the value %u. ", uint_vme_data);
		*sat = false;
	}
	return RET_SUCCESS;

}
int checkSaturationForAllAxis(bool* sat_Buf)
{
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	zygoLogInfo("Checking signal saturation on all axis...\n");
	bool sat = false;
	for (const auto& i : AXES)
	{
		if (return_code = checkSaturation(i, &sat))
		{
			zygoLogWarn("CheckSaturation Failled !  \n"); return return_code;
		}
		*(sat_Buf + (static_cast<int>(i) - 1)) = sat;
	}

	return RET_SUCCESS;

}
int readApdTemp(Axes axis, double* APD_Temp) {
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	double APD_Temp_Reg = 0.0;

	//enableAuxRegisters(  axis);
	zygoLogInfo("Reading APD GAIN L2 on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDTemp);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	APD_Temp_Reg = static_cast<double>(uint_vme_data);
	*APD_Temp = APD_Temp_Reg/256.0;
	zygoLogInfo("-------------------------------------------------------\n");
	zygoLogInfo("APD Temp on axis %u: %f \n", axis, *APD_Temp);
	zygoLogInfo("-------------------------------------------------------\n");
	//disableAuxRegisters(  axis);
	return RET_SUCCESS;
}

int readApdGain(Axes axis, double* APD_Gain) {
	uint32_t uint_vme_data = 0,
		uint_vme_address = 0;
	double APD_Gain_L2 = 0.0;

	//enableAuxRegisters(  axis);
	zygoLogInfo("Reading APD GAIN L2 on Axis %d...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zAPDGainL2);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	APD_Gain_L2 = static_cast<double>(uint_vme_data);
	*APD_Gain = std::pow(2 , (APD_Gain_L2 / 1024.0));
	zygoLogInfo("-------------------------------------------------------\n");
	zygoLogInfo("APD Gain on axis %u: %f \n", axis, *APD_Gain);
	zygoLogInfo("-------------------------------------------------------\n");
	//disableAuxRegisters(  axis);
	return RET_SUCCESS;
}
int readApdGainForAllAxis(double* APD_Gain_Buf) {

	double APD_Gain = 0.0;
	zygoLogInfo("Reading APD GAIN L2 on all axis ...  \n");

	for (const auto& i : AXES)
	{
		if (return_code = readApdGain(i, &APD_Gain))
		{
			zygoLogWarn("CheckSaturation Failled !  \n"); return return_code;
		}
		*(APD_Gain_Buf + (static_cast<int>(i) - 1)) = APD_Gain;
		APD_Gain = 0.0;
	}
	return RET_SUCCESS;
}
int enableAuxRegisters(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	zygoLogInfo("Enabling auxiliary registers on axis %u...  \n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);//rw
	uint_vme_data = 0x200;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;
}
bool isApdCtrlSoftErrs(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zVMEErrStat2);

	zygoLogInfo("Checking the APD control software errors on axis %u...  \n", axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return false;
	}
	if (uint_vme_data & 0x100)
		return true;
	return false;
}
int readApdCtrlSoftErrs(Axes axis) {
#define APD_NESTED_ERR_END	-10
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	int ret_code=0,val=0;
	int val1 = 0;
	zygoLogInfo("Reading APD  errors on axis %u...  \n", axis);
	zygoLogInfo("*************************APD Errors****************************\n");
	if (return_code = isApdCtrlSoftErrs(axis))
	{
		zygoLogWarn("isApdCtrlSoftErrs Failled !  \n"); return return_code;
	}

	//enableAuxRegisters(  axis); // Enable auxiliary registers to read the register value
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zSoftErrID);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	val=uint_vme_data >> 12;
	switch (val)
	{
	case 0:
		zygoLogInfo("No APD controller software error\n");
		ret_code=0;
		break;
	case 1:
		zygoLogInfo("APD controller raises an EXCEPTION ERROR\n");
		val1=uint_vme_data & 0xFFF;
		if(val1>5)
			ret_code = APD_ERROR_CODE_START + APD_NESTED_ERR_END;
		else
			ret_code = APD_ERROR_CODE_START-val1;
		switch (val1)
		{
		case 1:
			zygoLogInfo("\tUnaligned access exception\n");
			break;
		case 2:
			zygoLogInfo("\tTimeout from the IOPB bus exception\n");
			break;
		case 3:
			zygoLogInfo("\tIllegal op code execution exception\n");
			break;
		case 4:
			zygoLogInfo("\tTimeout on the DOPB bus exception\n");
			break;

		case 5:
			zygoLogInfo("\tDivide by zero exception\n");
			break;
		default:
			zygoLogInfo("\tUnknow exception error ID\n");
			break;
		}
		break;
	case 2:
		zygoLogInfo("STACK OVERFLOW\n");
		ret_code=APD_ERROR_CODE_START + APD_NESTED_ERR_END - 2;
		break;
	case 3:
		zygoLogInfo("Swith default error \n");
		ret_code=APD_ERROR_CODE_START + APD_NESTED_ERR_END - 3;
		break;

	case 4:
		zygoLogInfo("No APD controller software error\n");
		if ((uint_vme_data & 0xFFF) == 1){
			zygoLogInfo("\tRecieve Overflow\n");
			ret_code=APD_ERROR_CODE_START + APD_NESTED_ERR_END - 4;
		}
		break;
	default:
		zygoLogInfo("Unknow software error type\n");
		ret_code=APD_ERROR_CODE_START + APD_NESTED_ERR_END - 10;
		break;
	}
	//disableAuxRegisters(  axis); // Enable auxiliary registers
	return ret_code;
}
int enable32BitsOverflow(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	// Enable auxiliary registers
	zygoLogInfo("Enabling 32bits overflow on axis %u\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	uint_vme_data = 0x800;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); 
		return return_code;
	}
	return RET_SUCCESS;
}
int disable32BitsOverflow(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	// Enable auxiliary registers
	zygoLogInfo("Disabling 32bits overflow on axis %u\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	uint_vme_data = 0xF7FF;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;
}
int disableAuxRegisters(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	// Disable auxiliary registers
	zygoLogInfo("Disabling auxiliary registers on axis %u\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	uint_vme_data = 0xFDFF;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readModifyWrite Failled !  \n"); return return_code;
	}
	return RET_SUCCESS;
}
int sampleVmePosition(Axes axis) {
	uint32_t uint_vme_data = 0x200, ctr = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCmd);
	zygoLogInfo("Sampling velocity and position on axis %d...\n", axis);
	//*
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code; 
	}
	while (!(uint_vme_data & 0x400))
	{
		if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
			return return_code;
		}
	}
	//*/
	return RET_SUCCESS;
}

int setVMEBusSampleClk(Axes axis, SCLK clk) {
	uint32_t uint_vme_data = 0x1000, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	if (clk == SCLK::SCLK1) {
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE)) {

			zygoLogWarn("ReadWriteModify failed!  \n");
			return return_code;
		}
	}
	else
	{
		uint_vme_data = 0xEFFF;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE)) {

			zygoLogWarn("ReadWriteModify failed!  \n");
			return return_code;
		}
	}
	currentVMEBusSclk = clk;
	return RET_SUCCESS;
}

int enableSCLKDivider(Axes axis) {
	uint32_t uint_vme_data = 0x40, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE)) {

		zygoLogWarn("ReadWriteModify failed!  \n");
		return return_code;
	}
}

int getSCLKDividerState(Axes axis, State& s) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);

	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	if (uint_vme_data & 0x40)
		s = State::ON;
	else
		s = State::OFF;
	return RET_SUCCESS;
}
int disableSCLKDivider(Axes axis) {
	uint32_t uint_vme_data = 0xFFBF, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE)) {

		zygoLogWarn("ReadWriteModify failed!  \n");
		return return_code;
	}
}

int enableSCLKDivideBy2(Axes axis) {
	uint32_t uint_vme_data = 0x20, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE)) {

		zygoLogWarn("ReadWriteModify failed!  \n");
		return return_code;
	}
}

int disableSCLKDivideBy2(Axes axis) {
	uint32_t uint_vme_data = 0xFFDF, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE)) {

		zygoLogWarn("ReadWriteModify failed!  \n");
		return return_code;
	}
}

int getSCLKDivideBy2(Axes axis, State& s) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);

	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	if (uint_vme_data & 0x20)
		s = State::ON;
	else
		s = State::OFF;
	return RET_SUCCESS;
}
int setSCLKDividerCoeff(Axes axis, SampleDividerCoeffs sdv) {
	uint32_t uint_vme_data = 0xFF0F, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl15);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE)) {

		zygoLogWarn("ReadWriteModify failed!  \n");
		return return_code;
	}
	uint_vme_data = static_cast<uint32_t>(sdv);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE)) {

		zygoLogWarn("ReadWriteModify failed!  \n");
		return return_code;
	}
	return RET_SUCCESS;
}
int sclkOutputOn(Axes axis, SCLK clk) {
	//Turn on bits 7 and 9 (SCLK Timer enable and SCLK output)
	uint32_t uint_vme_data = 0x280, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	
	setVMEBusSampleClk(axis, clk);
	if (clk == SCLK::SCLK0) {
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE)) {

			zygoLogWarn("ReadWriteModify failed!  \n");
			return return_code;
		}
	}
	else
	{
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
		uint_vme_data = 0x80;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE)) {

			zygoLogWarn("ReadWriteModify failed!  \n");
			return return_code;
		}
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl17);
		uint_vme_data = 0x200;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE)) {

			zygoLogWarn("ReadWriteModify failed!  \n");
			return return_code;
		}
	}
	return RET_SUCCESS;
}

int sclkOutputOff(Axes axis, SCLK clk) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;

	if (clk == SCLK::SCLK0) {
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
		uint_vme_data = 0xFD7F;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("ReadWriteModify failed!  \n");
			return return_code;
		}
	}
	else
	{
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
		uint_vme_data = 0xFF7F;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("ReadWriteModify failed!  \n");
			return return_code;
		}

		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl17);
		uint_vme_data = 0xFDFF;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("ReadWriteModify failed!  \n");
			return return_code;
		}
	}

	return RET_SUCCESS;
}

int vmeSysReset() {
	SIS1100W_STATUS return_code;
	zygoLogInfo("Reseting Zygo board...\n");
	return_code = sis1100w_VmeSysreset(dev);

	if (return_code != Stat1100Success) {
		zygoLogWarn("Errors occured while hard reseting the card\n");
		return return_code;
	}
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
int setSampTimerFreq(uint16_t sampTimerVal) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	zygoLogInfo("Setting the sampling timer frequency to %u ...\n", sampTimerVal);
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zSampleTimer);
	uint_vme_data = sampTimerVal;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	return RET_SUCCESS;
}

/// <summary>
/// get the sampling frequency.
/// </summary>
/// <param name="dev"> device </param>
/// <param name="sampTimerVal">pointer to store the value in</param>
/// <returns>
/// 0 if success
/// -1 if failed
/// </returns>
int getSampTimerFreq(uint32_t* sampTimerVal) {
	uint32_t uint_vme_address = 0;
	zygoLogInfo("getting the sampling timer frequency ...\n");
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zSampleTimer);
	if (return_code = readWrite("A24D16", uint_vme_address, sampTimerVal, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code;
	}
	return RET_SUCCESS;
}

/// <summary>
/// get the frequency.
/// </summary>
/// <param name="dev"> device </param>
/// <param name="freq">pointer to store the value(Hz) in</param>
/// <returns>
/// 0 if success
/// -1 if failed
/// </returns>
int getSamplingFrequency(Axes axis, uint32_t* sampFreq) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0, tmp = 0;
	if (sampFreq == nullptr)
		return BAD_ARG_POINTER;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	zygoLogInfo("getting sampling frequency ...\n");
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zSampleTimer);
	if (return_code = getSampTimerFreq(&uint_vme_data))
	{
		zygoLogWarn("getSamplingFrequency failed !  \n"); 
		return return_code;
	}
	tmp = (uint32_t)(1e6 / ((static_cast<double>(uint_vme_data) + 1) * 0.05));
	State s;

	if (return_code = getSCLKDivideBy2(axis, s))
	{
		zygoLogWarn("getSCLKDivideBy2 failed !  \n");
		return return_code;
	}
	if (s == State::ON)
		tmp*= 2;
	currentSamplingFrequency[axis == Axes::Axis_1 ? 0:1] = tmp;
	*sampFreq = tmp;
	return RET_SUCCESS;
}
int setHoldSampEnable(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	zygoLogInfo("Holding measured samples...\n");
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	uint_vme_data = 0x2000;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("ReadWriteModify failed!  \n");
		return return_code;
	}
	return RET_SUCCESS;
}
int resetHoldSampEnable(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	zygoLogInfo("Updating measured samples...\n");
	uint_vme_data = 0xDFFF;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("ReadWriteModify failed!  \n");
		return return_code;
	}
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
int enableSampling(Axes axis, uint32_t sampleFreq, SCLK clk) {
	uint16_t rdVal = 0, sclkVal = 0;
	zygoLogInfo("Enabling sampling timer on the main axis...\n");
	if (return_code = setSamplingFrequency(axis, sampleFreq, SCLK::SCLK0))
	{
		zygoLogWarn("setSamplingFrequency failed!  \n");
		return return_code;
	}
	if (return_code = sclkOutputOn(axis, clk))
	{
		zygoLogWarn("sclk0OuputOn failed!  \n");
		return return_code;
	}
	return RET_SUCCESS;
}
/// <summary>
/// sets the sampling frequency
/// </summary>
/// <param name="sampleFreq">sampling frequency in Hz</param>
/// <returns>
/// 0 if success
/// -1 if failed
/// </returns>
int setSamplingFrequency(Axes axis, uint32_t sampleFreq, SCLK clk) {
	uint16_t rdVal = 0, sclkVal = 0;
	uint32_t sampFreqGo = sampleFreq;
	zygoLogInfo("Setting sampling frequency to %u...\n", sampleFreq);
	//turn off sclk (turn off 7 and 9)
	if (return_code = sclkOutputOff(axis, clk))
	{
		zygoLogWarn("sclkOutputOff failed!  \n");
		return return_code;
	}
	if (sampleFreq > SAMP_FREQ_MAX_X_2)
	{
		sampFreqGo = SAMP_FREQ_MAX;
		sclkVal = 1;
	}
	else if (sampleFreq <= SAMP_FREQ_MIN)
	{
		sclkVal = 0xFFFF;
		sampFreqGo = SAMP_FREQ_MIN;
		zygoLogInfo("ZMI sample frequency minimum is %u Hz.\n", (uint32_t)(SAMP_FREQ_MIN));
		zygoLogInfo("Setting to min...\n");
	}
	else if(sampleFreq > SAMP_FREQ_MAX){
		sampFreqGo = sampleFreq / 2;
		sclkVal = (uint16_t)(1 / (sampFreqGo * 0.05 * 1e-6) - 1);
		if (return_code = enableSCLKDivideBy2(axis))
		{
			zygoLogWarn("enableSCLKDivideBy2 failed!  \n");
		}
	}
	else 
		sclkVal = (uint16_t)(1 / (sampFreqGo * 0.05 * 1e-6) - 1);

	//set sclk rate(only master axis needed)
	if (return_code = setSampTimerFreq(sclkVal))
	{
		zygoLogWarn("setSampTimerFreq failed\n");
		return RET_FAILED;
	}
	//turn off sclk (turn off 7 and 9)
	if (return_code = sclkOutputOn(axis,clk))
	{
		zygoLogWarn("sclkOutputOn failed!  \n");
		return return_code;
	}
	currentSamplingFrequency[axis == Axes::Axis_1? 0:1] = sampFreqGo;
	return RET_SUCCESS;
}

int disableSampleTimer(Axes axis, SCLK clk) {
	zygoLogInfo("Disabling sampling timer ...\n");
	if (return_code = sclkOutputOff(axis, clk))
	{
		zygoLogWarn("sclkOutputOff failed!  \n");
		return return_code;
	}
	return RET_SUCCESS;
}
int getVmeExtSampFlag(Axes axis, int* sampleFlag) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zStat0);

	zygoLogInfo("Getting VME external sampling flag on axis %u...\n", axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); 
		return return_code;
	}
    *sampleFlag = uint_vme_data & 0x400;
	return RET_SUCCESS;
}
bool clearVmeExtSampFlag(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_data = 0x100;
	zygoLogInfo("Clearing VME external sampling flag bit on axis %u...\n", axis);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}
	return true;
}
bool isVmeIntReqPending(Axes axis) {
	uint32_t uint_vme_data = 0, uint_vme_address = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zStat0);
	zygoLogInfo("Checking VME external sample flag interrupt request  on axis %u...\n", axis);

	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	if ((uint_vme_data &= 0x100)) {
		return true;
	}
	return false;
}
int eepromRead(uint16_t offset, uint32_t* uint_vme_data, uint16_t nBytes) {
	uint32_t uint_vme_address = 0,
		vme_data = 0;
	char ch_access_mode[10];
	zygoLogInfo("Reading EEPROM data...\n");
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestStat1);
	if (return_code = readWrite("A24D16", uint_vme_address, &vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	// Verify the EEPROM is error-free 
	if ((vme_data & 0x800) != 0) {
		uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestCmd1); // Clear the error 
		vme_data = 0x04;
		if (return_code = readWrite(ch_access_mode, uint_vme_address, &vme_data, WRITE))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}
	}
	// Wait until EEPROM Busy clears 
	vme_data = 0x0200;
	while (vme_data & 0x0200) {
		uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestStat1);
		vme_data = 0;
		if (return_code = readWrite(ch_access_mode, uint_vme_address, &vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}

	}; // Wait while EEPROM busy 
		// Start EEPROM Read 
	//First send the adress to read
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zEEpromCtrl);
	vme_data = zEEReadCmd | (offset & 0x3ff); // keep the last 10 bits and add them to the eerdcmd
	if (return_code = readWrite(ch_access_mode, uint_vme_address, &vme_data, WRITE))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	vme_data = 0x0200;
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zTestStat1);
	while (vme_data & 0x0200) {

		if (return_code = readWrite(ch_access_mode, uint_vme_address, &vme_data, READ))
		{
			zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
		}

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

	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zEEpromReadReg);
	*uint_vme_data = 0;
	if (return_code = readWrite(ch_access_mode, uint_vme_address, uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}

	return RET_SUCCESS;

}

int readWrite(const char* ch_access_mode, uint32_t uint_vme_address, uint32_t* uint_vme_data,
	uint16_t read_write) {
	int return_code = 0, comp_err = 0;
	/**************************************************************************/
	/***   "A24D32":   A24  privileged data access                       ***/
	/**************************************************************************/
	uint8_t comp_valid_flag = 0;
	WaitForSingleObject(rw_key, INFINITE);
	comp_err = strncmp(ch_access_mode, "A24D32P", 7);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D32P_read(dev, uint_vme_address, uint_vme_data);
			zygoLogInfo("vme_A24D32_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D32P_write(dev, uint_vme_address, *uint_vme_data);
			zygoLogInfo("vme_A24D32_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		ReleaseMutex(rw_key);
		return return_code;

	}

	/**************************************************************************/
	/***   "A24D8":    A24 non privileged data access                       ***/
	/**************************************************************************/

	comp_err = strncmp(ch_access_mode, access_mode_Selection[5], 16);
	if (comp_err == 0) {

		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D8_read(dev, uint_vme_address, (uint8_t*)uint_vme_data);
			zygoLogInfo("vme_A24D8_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D8_write(dev, uint_vme_address, (uint8_t)*uint_vme_data);
			zygoLogInfo("vme_A24D8_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%02X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		ReleaseMutex(rw_key);
		return return_code;
	}

	/**************************************************************************/
	/***   "A24D16":   A24 non privileged data access                       ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, access_mode_Selection[6], 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D16_read(dev, uint_vme_address, (uint16_t*)uint_vme_data);
			zygoLogInfo("vme_A24D16_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D16_write(dev, uint_vme_address, (uint16_t)*uint_vme_data);
			zygoLogInfo("vme_A24D16_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		ReleaseMutex(rw_key);
		return return_code;
	}


	/**************************************************************************/
	/***   "A24D16":   A24  privileged data access                       ***/
	/**************************************************************************/
	comp_err = strncmp(ch_access_mode, "A24D16P", 16);
	if (comp_err == 0) {
		comp_valid_flag = 1;
		if (read_write == 0) {
			return_code = vme_A24D16P_read(dev, uint_vme_address, (uint16_t*)uint_vme_data);
			zygoLogInfo("vme_A24D16_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D16P_write(dev, uint_vme_address, (uint16_t)*uint_vme_data);
			zygoLogInfo("vme_A24D16_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%04X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		ReleaseMutex(rw_key);
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
			zygoLogInfo("vme_A24D32_read:  return_code = 0x%08X  address = 0x%08X   read = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		else {
			return_code = vme_A24D32_write(dev, uint_vme_address, *uint_vme_data);
			zygoLogInfo("vme_A24D32_write:  return_code = 0x%08X  address = 0x%08X   write = 0x%08X  \n", return_code, uint_vme_address, *uint_vme_data);
		}
		ReleaseMutex(rw_key);
		return return_code;
	}
	/******************************************************************************************************************************/
	/******************************************************************************************************************************/
	comp_valid_flag = 0;
	ReleaseMutex(rw_key);
	return RW_FAILED;
}

int zygoLogFatal(const char* fmt, ...) {
	WaitForSingleObject(zygoLogFatal_key, INFINITE);
	int argout = RET_SUCCESS;
	if (fopen_s(&fdLog, "logfile.txt", "a") != RET_SUCCESS) {
		ReleaseMutex(zygoLogFatal_key);
		return FILE_OPEN_FAILED;
	}
	va_list argPtr;
	char* errStr;
	errStr = (PCHAR)malloc(ERRSTRMAX);
	if (errStr == NULL) {
		ReleaseMutex(zygoLogFatal_key);
		fclose(fdLog);
		return ALLOC_MEM_ERROR;
	}
	va_start(argPtr, fmt);
	vsnprintf(errStr, ERRSTRMAX - 1, fmt, argPtr);
	va_end(argPtr);
	GetLocalTime(&lt);
	fprintf(fdLog, "%d/%d/%d|%d:%d:%d:%d [zygoLogFatal] %s", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds, errStr);
	if (errno) {
		perror("ECASOLEILZMI4104CLIB_API : ZYGOLOGFATAL: Kernel says ");
		argout = LOGFILE_RW_FAILED;
	}
	fclose(fdLog);
	ReleaseMutex(zygoLogFatal_key);
	free(errStr);
	return argout;
}
int zygoLogWarn(const char* fmt, ...) {
	WaitForSingleObject(zygoLogWarn_key, INFINITE);
	int argout = RET_SUCCESS;
	if (fopen_s(&fdLog, "logfile.txt", "a") != RET_SUCCESS) {
		ReleaseMutex(zygoLogFatal_key);
		return FILE_OPEN_FAILED;
	}
	va_list argPtr;
	char* errStr;
	errStr = (PCHAR)malloc(ERRSTRMAX);
	if (errStr == NULL) {
		fclose(fdLog);
		ReleaseMutex(zygoLogFatal_key);
		return ALLOC_MEM_ERROR;
	}
	va_start(argPtr, fmt);
	vsnprintf(errStr, ERRSTRMAX - 1, fmt, argPtr);
	va_end(argPtr);
	GetLocalTime(&lt);
	fprintf(fdLog, "%d/%d/%d|%d:%d:%d:%d [zygoLogWarn] %s", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds, errStr);
	if (errno) {
		perror("ECASOLEILZMI4104CLIB_API : ZYGOLOGWARN : Kernel says ");
		argout = LOGFILE_RW_FAILED;
	}
	fclose(fdLog);
	ReleaseMutex(zygoLogWarn_key);
	free(errStr);
	return argout;
}
int zygoLogInfo(const char* fmt, ...) {
	
	if(INFO_LEVEL){
		WaitForSingleObject(zygoLogInfo_key, INFINITE);
		if (fopen_s(&fdLog, "logfile.txt", "a") != RET_SUCCESS) {
			tNbr++;
			ReleaseSemaphore(zygoLogInfo_key, 1, NULL);
			return FILE_OPEN_FAILED;
		}
		va_list argPtr;
		char* errStr;
		errStr = (PCHAR)malloc(ERRSTRMAX);
		if (errStr == NULL) {
			fclose(fdLog);
			ReleaseSemaphore(zygoLogInfo_key, 1, NULL);
			return ALLOC_MEM_ERROR;
		}
		va_start(argPtr, fmt);
		vsnprintf(errStr, ERRSTRMAX - 1, fmt, argPtr);
		va_end(argPtr);
		GetLocalTime(&lt);
		fprintf(fdLog, "%d/%d/%d|%d:%d:%d:%d [zygoLogInfo] %s", lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds, errStr);
		if (errno) {
			perror("ECASOLEILZMI4104CLIB_API : ZYGOLOGINFO : Kernel says ");
			return LOGFILE_RW_FAILED;
		}
		fclose(fdLog);
		ReleaseSemaphore(zygoLogInfo_key, 1, NULL);
		free(errStr);
	}
	return RET_SUCCESS;
}
int setPositionFilePath(char* filePath) {
	POSITION_FILE_PATH = (char*)malloc(500 * sizeof(char));
	if (POSITION_FILE_PATH == NULL)
		return FILE_OPEN_FAILED;
	sprintf_s(POSITION_FILE_PATH, sizeof(POSITION_FILE_PATH), "%s", filePath);
	return RET_SUCCESS;
}

int setGainMinControl(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Setting up gain min control on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0x10;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	return RET_SUCCESS;
}


int getGainMinControl(Axes axis, bool* state) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Getting minimum gain control state on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}

	*state = (bool)((uint_vme_data & 0x10) >> 4);
	zygoLogInfo("minimum gain control is %d\n", *state);
	return RET_SUCCESS;
}


int resetGainMinControl(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Resettiing gain min control on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0xFFEF;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	return RET_SUCCESS;
}

int setGainMaxControl(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Setting up gain max control on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0x8;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}

	return RET_SUCCESS;
}


int getGainMaxControl(Axes axis, bool* state) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Getting maximum gain control state on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}

	*state = (bool)((uint_vme_data & 0x8) >> 3);
	zygoLogInfo("maximum gain control is %d\n", *state);
	return RET_SUCCESS;
}

int resetGainMaxControl(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Resetting gain max control on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0xFFF7;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	return RET_SUCCESS;
}


int setGainControlAgc(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Setting up automatic gain control on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0x20;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	return RET_SUCCESS;
}

int getGainControlAgc(Axes axis, bool* agcState) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Getting automatic gain control state on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0;
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address);
		return return_code;
	}

	*agcState = (bool)((uint_vme_data & 0x20) >> 5);
	zygoLogInfo("AGC state is %d\n", *agcState);
	return RET_SUCCESS;
}

int resetGainControlAgc(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Reseting automatic gain control on axis %d...\n", axis);
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl5);

	uint_vme_data = 0xFFDF;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	return RET_SUCCESS;
}

int readGseData(Axes axis, double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC) {
	uint32_t uint_vme_address = 0, uint_vme_data;
	double targetGain = 0, actualGain = 0, sigRMS = 0, measDC = 0;

	zygoLogInfo("Reading GSE data on axis %d...\n", axis);
	zygoLogInfo("Reading actual gain...\n");
	//enableAuxRegisters(axis);

	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zGSETargetGain);
	uint_vme_data = 0;
	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	actualGain = std::pow(2, ((uint_vme_data & 0xFFFF) / 1024.0));
	targetGain = std::pow(2, (((uint_vme_data & 0xFFFF0000) >> 16) / 1024.0));
	zygoLogInfo("The GSE current gain on axis %d is %lf\n", axis, actualGain);
	zygoLogInfo("The GSE target gain on axis %d is %lf\n", axis, targetGain);
	*gseTargetGain = targetGain;
	*gseActualGain = actualGain;


	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zGSESigRMSGain);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	sigRMS = std::pow(2, (uint_vme_data / 1024.0));
	zygoLogInfo("The GSE sig RMS gain on axis %d is %lf\n", axis, sigRMS);
	*gseSigRMS = sigRMS;


	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zGSEMeasDCLow);
	uint_vme_data = 0;

	if (return_code = readWrite("A24D32", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("Register %6X access Faillure !  \n", uint_vme_address); return return_code;
	}
	measDC = static_cast<double>(uint_vme_data);
	zygoLogInfo("The GSE meas DC on axis %d is %lf\n", axis, measDC);
	*gseMeasDC = measDC;

	//disableAuxRegisters(axis);

	return RET_SUCCESS;
}

int readGseDataForAllAxis(double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC) {

	double targetGain = 0, actualGain = 0, sigRMS = 0, measDC = 0;
	for (const auto& axis : AXES) {
		if (return_code = readGseData(axis, &targetGain, &actualGain, &sigRMS, &measDC))
		{
			zygoLogWarn("Read GSE data failed on axis %d !  \n", axis);
			return return_code;
		}
		gseTargetGain[axis - 1] = targetGain;
		gseActualGain[axis - 1] = actualGain;
		gseSigRMS[axis - 1] = sigRMS;
		gseMeasDC[axis - 1] = measDC;
	}

	return RET_SUCCESS;
}

int serialBusSampleClk(Axes axis, SCLK clk) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl15);
	if (clk == SCLK::SCLK1) {
		uint_vme_data = 0x1;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}
	}
	else
	{
		uint_vme_data = 0xFFFE;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}

	}
	return RET_SUCCESS;

}
int p2BusClkDriver(Axes axis, SCLK clk) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0x200;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	sclkOutputOn(axis, clk);
	if (clk == SCLK::SCLK0) {
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
		uint_vme_data = 0xFEFF;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}

		//sclk divider enable
		/*
		uint_vme_data = 0x40;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}
		*/
	}
	else
	{
		uint_vme_data = 0x100;
		uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}

	}
	return RET_SUCCESS;

}
int clearP2BusOutputDriver(Axes axis) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl16);
	uint_vme_data = 0xFDFF;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl17);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl15);
	uint_vme_data = 0xFFF9;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	return RET_SUCCESS;
}
int setSerialBusOutputDriver(Axes axis, SerialOutputDriver sdo){
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl15);
	if (sdo == SerialOutputDriver::P2D) { //P2d
		uint_vme_data = 0x2;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}
		uint_vme_data = 0xFFFB;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}
	}
	else { // P2z
		uint_vme_data = 0x4;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}
		uint_vme_data = 0xFFFD;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}
	}
	return RET_SUCCESS;
}
int setSerialBusDataPositionSize(Axes axis, SerialDataPositionSize sdps) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl15);
	if (sdps == SerialDataPositionSize::P37) { // 37 bits
		uint_vme_data = 0x8;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}
	}
	else { // 32 bits
		uint_vme_data = 0xFFF7;
		if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
		{
			zygoLogWarn("readWriteModify failed!!!!!!\n");
			return return_code;
		}
	}

	return RET_SUCCESS;
}
int setP2BusBitWindow(Axes axis, BitWindow bw) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], zCtrl4);
	uint_vme_data = 0xFF1F;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	uint_vme_data = (static_cast<uint32_t>(bw) << 5);
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	return RET_SUCCESS;
}
int configureSerialBus(Axes axis, SCLK clk, SerialOutputDriver sdo, SerialDataPositionSize sdps, BitWindow bw, uint32_t sampFreq) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;

	zygoLogInfo("Setting up serial data transmission on lines P2d and P2Z...\n");
	zygoLogInfo("Parameters: clk = SCLK %d, SerialOutputDriver = %s, SerialDataPositionSize = %s , BitWindow = %d, Sampling Frequency = %lu Hz\n", 
		(clk==SCLK::SCLK0)?0:1, (sdo == SerialOutputDriver::P2D)?"P2D":"P2Z", sdps == SerialDataPositionSize::P32?"32bits":"37bits", 
		static_cast<int>(bw), sampFreq);
	//startSerialBus();
		//set sclk rate(only master axis needed)


	//*
	if (return_code = setSamplingFrequency(axis, sampFreq, clk)) {
		zygoLogWarn("setSamplingFrequency failed!!!!!!\n");
		return return_code;
	}
	// Configure P2 bus clock driver
	
	if (return_code = p2BusClkDriver(axis, clk)) {
	zygoLogWarn("p2BusClkDriver failed!!!!!!\n");
	return return_code;
	}	
	//Select source clock to control the sampling of data 	
	if (return_code = serialBusSampleClk(axis, clk)) {
		zygoLogWarn("serialBusSampleClk failed!!!!!!\n");
		return return_code;
	}
	
	/*
	uint_vme_data = 0x1;
	uint_vme_address = ADD(BASE_ADDRESS[AXIS3 - 1], 0x2002);
	if (return_code = readWrite("A24D16", uint_vme_address, &uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readWrite failed!!!!!!\n");
		return return_code;
	}
	*/
	
	//Configure the serial output driver (P2d or P2Z)
	if (return_code = setSerialBusOutputDriver(axis, sdo)) {
	zygoLogWarn("setSerialBusOutputDriver failed!!!!!!\n");
	return return_code;
	}
	
	//Select serial data position size (32 bits or 37 bits)
	if (return_code = setSerialBusDataPositionSize(axis, sdps)) {
	zygoLogWarn("setSerialBusDataPositionSize failed!!!!!!\n");
	return return_code;
	}
	//Select P2 bit window
	if (return_code = setP2BusBitWindow(axis, bw)) {
	zygoLogWarn("setP2BusBitWindow failed!!!!!!\n");
	return return_code;
	}
	//*/
	return RET_SUCCESS;
}

int startSerialBus(Axes axis) {
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	
	zygoLogInfo("Starting serial data output...\n");
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	uint_vme_data = 0x100;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_OR_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	
	return RET_SUCCESS;
}

int stopSerialBus(Axes axis) {
	zygoLogInfo("Halting serial data output...\n");
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	uint_vme_data = 0xFEFF;
	if (return_code = readModifyWrite("A24D16", uint_vme_address, uint_vme_data, LOGICAL_AND_OP_CODE))
	{
		zygoLogWarn("readWriteModify failed!!!!!!\n");
		return return_code;
	}
	if (return_code = clearP2BusOutputDriver(axis))
	{
		zygoLogWarn("clearP2BusOutputDriver failed!!!!!!\n");
		return return_code;
	}
	return RET_SUCCESS;
}


int getSerialBusState(Axes axis, State& s) {
	uint32_t uint_vme_address = 0, uint_vme_data = 0;
	if (axis != Axes::Axis_1 && axis != Axes::Axis_3)
		return BAD_AXIS_VALUE;
	uint_vme_address = ADD(BASE_ADDRESS[static_cast<uint8_t>(axis) - 1], zCtrl2);
	uint_vme_data = 0x100;
	if (readWrite("A24D16", uint_vme_address, &uint_vme_data, READ))
	{
		zygoLogWarn("getSerialOutputState failed!!!!!!\n");
		return false;
	}
	if (uint_vme_data & 0x100) 
		s = State::ON;
	else
		s = State::OFF;
	return RET_SUCCESS;
}

uint8_t getInterferometerConfiguration() {
	return curInterferoConfig;
}
SCLK getCachedSampleSclk() {
	return currentResetSclk;
}
SCLK getCachedResetSclk() {
	return currentResetSclk;
}

uint32_t getCachedSamplingFrequency() {
	return (uint32_t)currentSamplingFrequency[1];
}

bool getCachedCecState() {
	return cecState;
}

uint32_t getCachedBaseAddress() {
	return BASE_ADDRESS[AXIS3 - 1];
}
/// <summary>
/// read the Zygo board version
/// </summary>
/// <returns>
/// the return the board version
/// </returns>
const char* getZygoBoardVersion() {

	sprintf_s(str, "%s", ZYGO_BOARD_VERSION);
	return str;
}
/// <summary>
/// read the Zygo serial number
/// </summary>
/// <returns>
/// return the  serial number
/// </returns>
const char* getZygoSerialNumber() {

	sprintf_s(str, "%s",ZYGO_BOARD_SN);
	return str;
}
/// <summary>
/// read the Zygofirmware version
/// </summary>
/// <returns>
///  return the firmware version
/// </returns>
const char* getZygoFirmwareVersion() {

	sprintf_s(str, "%s", ZYGO_FIRMWARE_VERSION);
	return str;
}
/// <summary>
/// read the Zygo board reference
/// </summary>
/// <returns>
/// return the board reference
/// </returns>
const char* getZygoBoardRef() {

	sprintf_s(str, "%s", ZYGO_BOARD_TYPE);
	return str;
}
/// <summary>
/// read the VME/PCI firmware version
/// </summary>
/// <returns>
/// return the firmware version
/// </returns>
const char* getSisFirmwareVersion() {
	sprintf_s(str, "%s", PCI_VME_GATEWAY_FIRMWARE_VERSION);
	return str;
}
/// <summary>
/// read the VME/PCI board version
/// </summary>
/// <returns>
/// return the board version
/// </returns>
const char* getSisBoardVersion() {
	sprintf_s(str, "%s",PCI_VME_GATEWAY_BOARD_VERSION);
	return str;
}