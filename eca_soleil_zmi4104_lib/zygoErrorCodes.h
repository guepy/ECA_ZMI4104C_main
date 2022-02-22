#pragma once
#define APD_ERROR_CODE_START					-50
//-------------------------------------------------------------------------------------------------------
//exeception error raises by APD controller on ZMI4104C. Their error_code starts at APD_ERROR_CODE_START
//-------------------------------------------------------------------------------------------------------
// APD Unaligned access exception
#define APD_UAERR								-51
//Timeout from the IOPB bus exception
#define APD_IOPBUS_TIMEOUT						-52
//Illegal op code execution exception
#define APD_ILLEXEC								-53
//Timeout on the DOPB bus exception
#define APD_DOPBUS_TIMEOUT						-54
//Divide by zero exception
#define APD_DIV_ZERO							-55
//Unknow APD  exception error ID
#define APD_UNKNOW_EXCEP						-60
//No APD controller's software error
#define APD_SOFT_NOT_FOUND						-61
//Stack overflow has been detected
#define APD_STACK_OVERFLOW						-62
//Swith default error has been detected
#define APD_SWDEFERR							-63
//Recieve Overflow
#define APD_SOFT_NOT_FOUND_4						-64
//Unknow software error type
#define APD_SOFT_ERR_NBR						-70


#define	RET_FAILED								-1
#define FIFO_OVERLAP_ERR_CODE					-100
#define VME_PCI_GATEWAY_NOT_FOUND				-101
#define VME_PROT_ERROR							0x211

#define	BAD_AXIS_VALUE							-2
#define	LESSER_THAN_MIN_FREQUENCY				-3
#define	GREATER_THAN_MAX_FREQUENCY				-4
#define	ZYGO_RAM_BUSY_FOR_TOO_LONG				-5
#define	RESET_ZYGO_FAILED						-6
#define	BAD_ARG_POINTER							-7
#define	BAD_ARG_VALUE							-8
#define	NO_MOTION_DETECTED						-9
#define	BIAS_CALC_FAILED						-10
#define	CREATE_EVENT_FAILED						-11
#define	CREATE_THREAD_FAILED					-12
#define	FILE_OPEN_FAILED						-13
#define	ALLOC_MEM_ERROR							-14
#define	NO_FIFO_DATA_AV							-15
#define	CEC_MIN_VEL_ERROR						-16

#define	NO_DEVICE_FOUND							-17
#define	RESET_AXIS_FAILED						-18
#define	EEPROM_READ_FAILED						-19
#define	RW_FAILED								-20
#define	LOGFILE_RW_FAILED						-21