#pragma once

#ifdef ECA_SOLEIL_ZMI4104C_LIB_EXPORTS
#define ECASOLEILZMI4104CLIB_API __declspec(dllexport)
#else
#define ECASOLEILZMI4104CLIB_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
#pragma comment (lib, "sis1100w.lib")

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "sis1100w.h"
#include "zVME_const.h"
#include "sis3302.h"
#include "sis3100.h"
#include "sis3100_vme_calls.h"
//#include "vmeInterruptConst.h"

#define FLYSCAN_MODE_ON						0
#define READ_MODE							0
#define WRITE_MODE							1
#define FFTRAM_SIZE_PER_AXIS				16384
#define MAX_NOF_ACCESS_MODE_DEFINES			11 
#define RET_SUCCESS							0
#define RET_FAILED							-1
#define LAMBDA								632.9911 //"Nominal Vacuum Wavelength: 632.9911 ± 0.0001 nm"
#define SINGLE_PASS_INT_POS_COEF			0.309077685546875*1e-6 // LAMBDA/2048 ==> 0.31 nm resolution
#define DOUBLE_PASS_INT_POS_COEF			0.1545388427734375*1e-6 // LAMBDA/4096	==> 0.15 nm resolution
#define SSI_MAX_SAT							2047
#define SINGLE_PASS_INT_VEL_COEF			2.946705 * (1e-3)	//  ± 5.1 m/sec resolution
#define DOUBLE_PASS_INT_VEL_COEF			1.473352 * (1e-3)	// ± 2.55 m/sec resolution
#define CE_MAX_VEL_DFLT						31457
#define CE_MIN_VEL_DFLT						96
#define NO_EXCEPTION_ERROR					0
#define EXCEPTION_ERROR						1
#define STACK_OVERFLOW						2
#define SWITCH_DEFAULT_ERROR				3
#define COMM_ERROR							4
#define AXIS1								1
#define AXIS2								2
#define AXIS3								3
#define AXIS4								4
#define PI									3.14159265359
#define BIAS_CTRL_MODE_NBR					5		
#define NON_FATAL							0
#define EXIT_FAILLURE						1
#define INFO_PURPOSE						2
#define SAMP_FREQ_MIN	0.000305	// 1/(65536*005) in Mhz
#define SAMP_FREQ_MIN_DIV_2		0.000305/2	//in Mhz. min ferq with divide by 2 enable in control register 16
#define SAMP_FREQ_MAX	20			// 1/(005) in Mhz
#define DESCRIPTOR_1_TEST
#define DESCRIPTOR_2_TEST
#define DESCRIPTOR_3_TEST
#define DESCRIPTOR_4_TEST
#define DESCRIPTOR_5_TEST

#define ERRSTRMAX 512

#define CE_MIN_VEL								50 // min vel is 0.5mm/s
#define CE_MAX_VEL								31457 // max vel is 0.38 m/s
#define ACTIVATE_CEC							0
#define FIFO_FLYSCAN_MODE						1
	typedef struct _comp {
		double rpart;
		double ipart;
	}complex;

	typedef struct _CECoeffs {
		complex CEC0coeff;	// 20MHz(Leakage) cyclic error
		double CEC1coeff;	//Doppler signal magnitude 
		complex CECNcoeff;	//Negative doppler cyclic error
	}CECoeffs;
	typedef struct _CECoeffBoundaries {
		double CEMagcoeff;
		double CEMincoeff;
		double CEMaxcoeff;
	}CECoeffBoundaries;
	typedef struct _fifoParam {
		double acqTime; // ACQUISITION TIME in ms
		double freq;	// sample frequency in Hz
		UINT nbrPts;	// number of points to acquire
	}fifoParam;
	typedef struct _CEratios {
		double measSignal;
		double CE0ratio;
		double CENratio;
	}CEratios;
	typedef struct _CEratiosBoundaries {
		double CEMinratio;
		double CEMaxratio;
	}CEratiosBoundaries;
	typedef enum _CEratioUnits {
		ratio_in_dB = 0,
		ratio_in_percent = 1,
		ratio_in_nmRMS = 2
	}CEratioUnits;
	typedef enum _sclk {
		SCLK0 = 0,
		SCLK1 = 1
	}sclk;
	typedef enum _InterferoConfig {
		SGLE =1,
		DBLE =2,
	}InterferoConfig;
	static const char* access_mode_Selection[MAX_NOF_ACCESS_MODE_DEFINES] = {
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
	static const char* biasControlModeString[BIAS_CTRL_MODE_NBR] = {
		"BIAS_OFF_MODE",
		"BIAS_CONSTANT_VOLTAGE_MODE",
		"BIAS_CONSTANT_GAIN_MODE",
		"BIAS_ACONSTANT_OPTICAL_POWER_MODE",
		"BIAS_SIG_RMS_ADJUST_MODE",
	};

	static unsigned int	BASE_ADDRESS[] = { 0x4000, 0x5000, 0x6000, 0x7000 }; // Base adresses ;

	static char* POSITION_FILE_PATH;

	/**/
	//GUID sis1100w_GUID = { 0x944adde8, 0x4f6d, 0x4bee, 0xa309, 0x7ad62ab0b4bb };

	/// <summary>
	/// APD Bias Mode typedef
	/// </summary>
	typedef enum _BIAS_MODE {
		BIAS_OFF_MODE = 0,
		BIAS_CONSTANT_VOLT_MODE = 1,
		BIAS_CONSTANT_GAIN_MODE = 2,
		BIAS_CONSTANT_OPT_PWR_MODE = 3,
		BIAS_SIG_RMS_ADJUST_MODE = 4
	}BIAS_MODE;


	static double positionScale = DOUBLE_PASS_INT_POS_COEF,    //Converts to mm as default
		velocityScale = DOUBLE_PASS_INT_VEL_COEF * (1e-3);      //Converts to mm/s
		// ZMI Scalars
	static const double	timeScale = 25 * (1e-6);                   //Converts to ms as default	
	static const double	SSIScale = 0.019073486328125;           //Converts to mV as default	

	static InterferoConfig curInterferoConfig;
	static FILE* fdLog;
	static SYSTEMTIME  lt;

	//static SIS1100_Device_Struct* dev;
	ECASOLEILZMI4104CLIB_API int disableCECcompensation(SIS1100_Device_Struct* dev, unsigned char axis);
	ECASOLEILZMI4104CLIB_API int readCEerrorStatReg(SIS1100_Device_Struct* dev, unsigned char axis, PUINT CEstatReg);
	ECASOLEILZMI4104CLIB_API int getLEDsStatus(SIS1100_Device_Struct* dev, bool* ledsStatus);
	ECASOLEILZMI4104CLIB_API int getLEDsErrorStatus(SIS1100_Device_Struct* dev, bool* ledsErrorStatus);
	ECASOLEILZMI4104CLIB_API void modifyBaseAddress(UINT baseAddressAxis3);
	ECASOLEILZMI4104CLIB_API void CreateEvents();
	ECASOLEILZMI4104CLIB_API int  CreateThreads(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API void CloseThreads(void);
	ECASOLEILZMI4104CLIB_API int convertUSFloat2Double(USHORT, double*);
	ECASOLEILZMI4104CLIB_API int calculateCEratio(SIS1100_Device_Struct*, unsigned char, CEratios*, CEratioUnits);
	ECASOLEILZMI4104CLIB_API int configureCEChardware(SIS1100_Device_Struct*, UCHAR, USHORT, USHORT);
	ECASOLEILZMI4104CLIB_API int readCEerrorStatReg(SIS1100_Device_Struct* dev, unsigned char axis, PUINT CEstatReg);
	ECASOLEILZMI4104CLIB_API int getAproximateCEratio(SIS1100_Device_Struct*, unsigned char, CEratios*, CEratioUnits);
	ECASOLEILZMI4104CLIB_API int Read_Write(const char*, SIS1100_Device_Struct*, unsigned int, unsigned int*, unsigned short);
	ECASOLEILZMI4104CLIB_API int FATAL(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int WARN(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int INFO(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int ReadVMEErrs(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int initAxis(SIS1100_Device_Struct*, BIAS_MODE);
	ECASOLEILZMI4104CLIB_API int initSISboards(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int initZMIboards(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int ReadSamplePosition37(SIS1100_Device_Struct*, unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadSamplePosition32(SIS1100_Device_Struct*, unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadSamplePosition37_ForAllAxis(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int ReadSamplePosition32_ForAllAxis(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int ReadPosition37(SIS1100_Device_Struct*, unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadPosition32(SIS1100_Device_Struct*, unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadFIFOPosition(SIS1100_Device_Struct*, unsigned char, PUINT position);
	ECASOLEILZMI4104CLIB_API int ReadVelocity32(SIS1100_Device_Struct*, unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadPosition37_ForAllAxis(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int ReadPosition32_ForAllAxis(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int ReadVelocity32_ForAllAxis(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int ReadTime32(SIS1100_Device_Struct*, unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadTime32_ForAllAxis(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int ReadAllTime32(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int IsVMEPos32Overflow(SIS1100_Device_Struct* dev, unsigned char axis);
	ECASOLEILZMI4104CLIB_API int ReadOpticalPowerUsingSSIav(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int ReadSSIav(SIS1100_Device_Struct* dev, double* ssiPtr);
	ECASOLEILZMI4104CLIB_API int ReadSSICalibrationData(SIS1100_Device_Struct* dev, unsigned char axis, double* SSIMin, double* SSIMax, double* SSINom, double* SSIVal);
	ECASOLEILZMI4104CLIB_API int ReadAPDGain(SIS1100_Device_Struct*, unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int EnableAuxRegisters(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int DisableAuxRegisters(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int Disable37bitsSignExtension(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int Sclk_On(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int Sclk_Off(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int SetSampTimerFreq(SIS1100_Device_Struct*, unsigned short);
	ECASOLEILZMI4104CLIB_API int SetHoldSampEnable(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int ResetHoldSampEnable(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int enableSampling(SIS1100_Device_Struct*, double);
	ECASOLEILZMI4104CLIB_API int DisableSampleTimer(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int VMESysReset(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int startAquisition(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int stopAquisition(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int GetVMEExtSampFlag(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int Disable32bitsOverflow(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int Enable32bitsOverflow(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int Enable37bitsSignExtension(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int EnableSinglePassInterferometer(void);
	ECASOLEILZMI4104CLIB_API int EnableDoublePassInterferometer(void);
	ECASOLEILZMI4104CLIB_API int ReadAPDGain_ForAllAxis(SIS1100_Device_Struct*, double*);
	ECASOLEILZMI4104CLIB_API int SampleVMEPosition(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int ParseVMEErrorStatus2(SIS1100_Device_Struct*, unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int ParseVMEPosErrs(SIS1100_Device_Struct*, unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int ParseVMEErrorStatus1(SIS1100_Device_Struct*, unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int ParseVMEErrorStatus0(SIS1100_Device_Struct*, unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int ParseAPDErrCode(SIS1100_Device_Struct*, unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int BoardControlMode(SIS1100_Device_Struct*, unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int BiasControlMode(SIS1100_Device_Struct*, unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int StartBiasCalculation(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int SetAPDGainL2(SIS1100_Device_Struct*, unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int checkValues(UINT, UINT, UINT);
	ECASOLEILZMI4104CLIB_API int ClearAllVMEErrs_ForAllAxis(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int ReadScaledSSIav(SIS1100_Device_Struct* dev, double* ssiPtr);
	ECASOLEILZMI4104CLIB_API BOOL isRAMbusy(SIS1100_Device_Struct*);
	ECASOLEILZMI4104CLIB_API int SetAPDSigRMSL2(SIS1100_Device_Struct*, unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int SetAPDOptPwrL2(SIS1100_Device_Struct*, unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int ResetAxis(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int WaitResetComplete(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int SetPresetPosition32(SIS1100_Device_Struct* dev, unsigned char axis, unsigned int presetPos32);
	ECASOLEILZMI4104CLIB_API int SetPositionOffset32(SIS1100_Device_Struct*, unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int EnableCECcompensation(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int SetPositionOffset37(SIS1100_Device_Struct*, unsigned char, unsigned int, unsigned int);
	ECASOLEILZMI4104CLIB_API int SetPresetPosition37(SIS1100_Device_Struct*, unsigned char, unsigned int, unsigned int);
	ECASOLEILZMI4104CLIB_API int EnableVMEInterrupt_bit(SIS1100_Device_Struct*, unsigned char, unsigned short);
	ECASOLEILZMI4104CLIB_API int DisableVMEInterrupt_bit(SIS1100_Device_Struct*, unsigned char, unsigned short);
	ECASOLEILZMI4104CLIB_API int EnableVMEGlobalInterrupt(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int DisableGlobalInterrupt(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int DisableAllVMEInterrupts(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int SetKpAndKvCoeff(SIS1100_Device_Struct*, unsigned char, unsigned short, unsigned short);
	ECASOLEILZMI4104CLIB_API int ReadAPDCtrlSoftErrs(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int ReadAllErrs(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int SetTimeDelayBetweenResAndCompleteBit(SIS1100_Device_Struct*, unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int EnableAllVMEInterrupts(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int EnableVMEGlobalInterrupt(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int setVMEIntVector(SIS1100_Device_Struct*, unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int setVMEIntLevel(SIS1100_Device_Struct*, unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int sis3301w_Init(SIS1100_Device_Struct*, uint32_t, uint32_t, uint32_t);
	ECASOLEILZMI4104CLIB_API int AckForSis3100VME_Irq(SIS1100_Device_Struct*, uint32_t);
	ECASOLEILZMI4104CLIB_API int getFlyscanData(SIS1100_Device_Struct*, PUINT, PUINT, PUINT);
	ECASOLEILZMI4104CLIB_API PUINT allocateMemSpace(UINT);
	ECASOLEILZMI4104CLIB_API int processRAMData(UINT, PUINT, PUINT, char* folderName);
	ECASOLEILZMI4104CLIB_API int processFifoData(UINT nbrAxis, PUCHAR axisTab, PUINT memPtr, UINT nbrOfPts);
	ECASOLEILZMI4104CLIB_API int configureFifoFlyscan(SIS1100_Device_Struct*, fifoParam*, PUINT, PUCHAR, PUCHAR);
	ECASOLEILZMI4104CLIB_API int fifoFlyscan(SIS1100_Device_Struct*, fifoParam, PUINT, UCHAR, ...);
	ECASOLEILZMI4104CLIB_API bool isFifoDavbitSet(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API bool isFifoOVFbitSet(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int configureFlyscan(SIS1100_Device_Struct*, unsigned char, double, UCHAR);
	ECASOLEILZMI4104CLIB_API int convertCInt162Complex(UINT, complex*);
	ECASOLEILZMI4104CLIB_API int convertCFloat2Complex(UINT, complex*);
	ECASOLEILZMI4104CLIB_API int waitCEinit2Complete(SIS1100_Device_Struct*, unsigned char);
	ECASOLEILZMI4104CLIB_API int SetCEMaxVel(SIS1100_Device_Struct*, unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int SetCEMinVel(SIS1100_Device_Struct*, unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int readCalcCECoeffs(SIS1100_Device_Struct*, unsigned char, CECoeffs*);
	ECASOLEILZMI4104CLIB_API int readCECoeffboundaries(SIS1100_Device_Struct*, unsigned char, CECoeffBoundaries*, CECoeffBoundaries*);
	ECASOLEILZMI4104CLIB_API int calculateCEratio(SIS1100_Device_Struct* dev, unsigned char axis, CEratios* ceRatios, CEratioUnits units);
	ECASOLEILZMI4104CLIB_API int EEPROMread(SIS1100_Device_Struct*, unsigned short, unsigned int*, unsigned short);
	ECASOLEILZMI4104CLIB_API int convertFloat2Double(UINT, double*);
#ifdef __cplusplus
}
#endif
