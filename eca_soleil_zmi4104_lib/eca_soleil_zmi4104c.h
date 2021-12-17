#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ECA_SOLEIL_ZMI4104C_LIB_EXPORTS
#define ECASOLEILZMI4104CLIB_API __declspec(dllexport)
#else
#define ECASOLEILZMI4104CLIB_API __declspec(dllimport)
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


#define KPMIN	-7
#define KPMAX	-2
#define KVMIN	-21
#define KVMAX	-7
#define LOGICAL_AND_OP_CODE		0
#define LOGICAL_OR_OP_CODE		1
#define ADDITION_OR_OP_CODE		2
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
#define SAMP_FREQ_MIN						0.000305	// 1/(65536*005) in Mhz
#define SAMP_FREQ_MIN_DIV_2					0.000305/2	//in Mhz. min ferq with divide by 2 enable in control register 16
#define SAMP_FREQ_MAX						20			// 1/(005) in Mhz
#define DESCRIPTOR_1_TEST
#define DESCRIPTOR_2_TEST
#define DESCRIPTOR_3_TEST
#define DESCRIPTOR_4_TEST
#define DESCRIPTOR_5_TEST
#define defaultAPDGAinL2Set					0xB3B
#define defaultAPDOptPwrL2Set				0
#define defaultAPDSigRMSL2Set				0x3390
#define READ								0
#define WRITE								1
#define VME_PROT_ERROR						0x211
#define FIFO_OVERLAP_ERR_CODE				-100
#define ERRSTRMAX							512
#define NBR_RAM_PAGES			64
#define NBR_SAMP_PER_PAGE		256
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
		uint32_t nbrPts;	// number of points to acquire
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

	static unsigned int	BASE_ADDRESS[] = { 0x4000, 0x5000, 0x6000, 0x7000 }; // Base adresses;

	static char* POSITION_FILE_PATH;
	static char PCI_VME_GATEWAY_FIRMWARE_VERSION[50];
	static char PCI_VME_GATEWAY_BOARD_VERSION[50];
	//char str[256];
	static char ZYGO_BOARD_VERSION[50];
	static char ZYGO_BOARD_SN[50];
	static char ZYGO_FIRMWARE_VERSION[50];
	static char ZYGO_BOARD_TYPE[50];
	static bool currentSampleSCLK = 0;
	static bool currentResetSCLK = 0;
	static double currentSamplingFrequency = 0;
	static uint8_t tabLen = sizeof(ZYGO_BOARD_TYPE) / sizeof(ZYGO_BOARD_TYPE[0]);
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
	//int return_code = 0;
	static unsigned int curInterferoConfig=1;
	static FILE* fdLog;
	static SYSTEMTIME  lt;
	static SIS1100_Device_Struct* dev = new SIS1100_Device_Struct;

	ECASOLEILZMI4104CLIB_API int disableCECcompensation( unsigned char axis);
	ECASOLEILZMI4104CLIB_API int readCEerrorStatReg( unsigned char axis, uint32_t* CEstatReg);
	ECASOLEILZMI4104CLIB_API int getLEDsStatus( bool* ledsStatus);
	ECASOLEILZMI4104CLIB_API int getLEDsErrorStatus( bool* ledsErrorStatus);
	ECASOLEILZMI4104CLIB_API void modifyBaseAddress(uint32_t baseAddressAxis3);
	ECASOLEILZMI4104CLIB_API void CreateEvents();
	ECASOLEILZMI4104CLIB_API int  CreateThreads( );
	ECASOLEILZMI4104CLIB_API void CloseThreads(void);
	ECASOLEILZMI4104CLIB_API int convertUSFloat2Double(uint16_t, double*);
	ECASOLEILZMI4104CLIB_API int calculateCEratio(  unsigned char, CEratios*, CEratioUnits);
	ECASOLEILZMI4104CLIB_API int configureCEChardware(  uint8_t, uint16_t, uint16_t);
	ECASOLEILZMI4104CLIB_API int readCEerrorStatReg( unsigned char axis, uint32_t* CEstatReg);
	ECASOLEILZMI4104CLIB_API int getAproximateCEratio(  unsigned char, CEratios*, CEratioUnits);
	ECASOLEILZMI4104CLIB_API int Read_Write(const char*, unsigned int, unsigned int*, unsigned short);
	ECASOLEILZMI4104CLIB_API int FATAL(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int WARN(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int INFO(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int ReadVMEErrs(  unsigned char);
	ECASOLEILZMI4104CLIB_API int initAxis(  BIAS_MODE);
	ECASOLEILZMI4104CLIB_API int getGainControlAGC(unsigned char axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int getGainMinControl(unsigned char axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int getGainMaxControl(unsigned char axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int initSISboards( );
	ECASOLEILZMI4104CLIB_API int initZMIboards( );
	ECASOLEILZMI4104CLIB_API uint32_t getCurrentInterType();
	ECASOLEILZMI4104CLIB_API uint32_t getBaseAddress();
	ECASOLEILZMI4104CLIB_API bool getSampleSCLK();
	ECASOLEILZMI4104CLIB_API bool getResetSCLK();
	ECASOLEILZMI4104CLIB_API double getSampFreq();
	ECASOLEILZMI4104CLIB_API int ReadSamplePosition37(  unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadSamplePosition32(  unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadSamplePosition37_ForAllAxis(  double*);
	ECASOLEILZMI4104CLIB_API int ReadSamplePosition32_ForAllAxis(  double*);
	ECASOLEILZMI4104CLIB_API int ReadPosition37(  unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadPosition32(  unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadFIFOPosition(  unsigned char, uint32_t* position);
	ECASOLEILZMI4104CLIB_API int ReadVelocity32(  unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadPosition37_ForAllAxis(  double*);
	ECASOLEILZMI4104CLIB_API int ReadPosition32_ForAllAxis(  double*);
	ECASOLEILZMI4104CLIB_API int ReadVelocity32_ForAllAxis(  double*);
	ECASOLEILZMI4104CLIB_API int ReadTime32(  unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int ReadTime32_ForAllAxis(  double*);
	ECASOLEILZMI4104CLIB_API int ReadAllTime32(  double*);
	ECASOLEILZMI4104CLIB_API int IsVMEPos32Overflow( unsigned char axis);
	ECASOLEILZMI4104CLIB_API int ReadOpticalPowerUsingSSIav(  double*);
	ECASOLEILZMI4104CLIB_API int ReadSSIav( double* ssiPtr);
	ECASOLEILZMI4104CLIB_API int ReadSSICalibrationData(unsigned char axis, double* SSIVals, double* OptPwrVals);
	ECASOLEILZMI4104CLIB_API int ReadAPDGain(  unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int EnableAuxRegisters(  unsigned char);
	ECASOLEILZMI4104CLIB_API int DisableAuxRegisters(  unsigned char);
	ECASOLEILZMI4104CLIB_API int Disable37bitsSignExtension(  unsigned char);
	ECASOLEILZMI4104CLIB_API int Sclk_On( );
	ECASOLEILZMI4104CLIB_API int Sclk_Off( );
	ECASOLEILZMI4104CLIB_API int SetSampTimerFreq(  unsigned short);
	ECASOLEILZMI4104CLIB_API int SetHoldSampEnable( );
	ECASOLEILZMI4104CLIB_API int ResetHoldSampEnable( );
	ECASOLEILZMI4104CLIB_API int EnableResetFindsVelocity( unsigned char axis);
	ECASOLEILZMI4104CLIB_API int EnableResetFindsVelocity_ForAllAxis(   );
	ECASOLEILZMI4104CLIB_API int DisableResetFindsVelocity( unsigned char axis);
	ECASOLEILZMI4104CLIB_API int DisableResetFindsVelocity_ForAllAxis(   );
	ECASOLEILZMI4104CLIB_API int enableSampling(  double);
	ECASOLEILZMI4104CLIB_API int DisableSampleTimer( );
	ECASOLEILZMI4104CLIB_API int setSamplingFrequency(unsigned int sampleFreq);
	ECASOLEILZMI4104CLIB_API int VMESysReset( );
	ECASOLEILZMI4104CLIB_API int startAquisition(  unsigned char);
	ECASOLEILZMI4104CLIB_API int stopAquisition(  unsigned char);
	ECASOLEILZMI4104CLIB_API int GetVMEExtSampFlag(  unsigned char);
	ECASOLEILZMI4104CLIB_API int Disable32bitsOverflow(  unsigned char);
	ECASOLEILZMI4104CLIB_API int Enable32bitsOverflow(  unsigned char);
	ECASOLEILZMI4104CLIB_API int Enable37bitsSignExtension(  unsigned char);
	ECASOLEILZMI4104CLIB_API int EnableSinglePassInterferometer(void);
	ECASOLEILZMI4104CLIB_API int EnableDoublePassInterferometer(void);
	ECASOLEILZMI4104CLIB_API int ReadAPDGain_ForAllAxis(  double*);
	ECASOLEILZMI4104CLIB_API int SampleVMEPosition(  unsigned char);
	ECASOLEILZMI4104CLIB_API int ParseVMEErrorStatus2(  unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int ParseVMEPosErrs(  unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int ParseVMEErrorStatus1(  unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int ParseVMEErrorStatus0(  unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int ParseAPDErrCode(  unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int BoardControlMode(  unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int BiasControlMode(  unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int StartBiasCalculation(  unsigned char);
	ECASOLEILZMI4104CLIB_API int SetAPDGainL2(  unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int checkValues(int, int, int);
	ECASOLEILZMI4104CLIB_API int ClearAllVMEErrs_ForAllAxis( );
	ECASOLEILZMI4104CLIB_API int setSampleSourceClock(unsigned char axis, bool SCLK);
	ECASOLEILZMI4104CLIB_API int setResetSourceClock(unsigned char axis, bool SCLK);
	ECASOLEILZMI4104CLIB_API int getSampleSourceClock(unsigned char axis, bool* SCLK);
	ECASOLEILZMI4104CLIB_API int getResetSourceClock(unsigned char axis, bool* SCLK);
	ECASOLEILZMI4104CLIB_API int getSamplingFrequency(double* sampFreq);
	ECASOLEILZMI4104CLIB_API int ReadScaledSSIav( double* ssiPtr);
	ECASOLEILZMI4104CLIB_API BOOL isRAMbusy( );
	ECASOLEILZMI4104CLIB_API int SetAPDSigRMSL2( unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int SetAPDOptPwrL2(  unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int ResetAxis(  unsigned char);
	ECASOLEILZMI4104CLIB_API int WaitResetComplete(  unsigned char);
	ECASOLEILZMI4104CLIB_API int SetPresetPosition32( unsigned char axis, unsigned int presetPos32);
	ECASOLEILZMI4104CLIB_API int SetPositionOffset32(  unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int EnableCECcompensation(  unsigned char);
	ECASOLEILZMI4104CLIB_API int SetPositionOffset37(  unsigned char, double offsetPos);
	ECASOLEILZMI4104CLIB_API int SetPresetPosition37(  unsigned char, double presetPos);
	ECASOLEILZMI4104CLIB_API int EnableVMEInterrupt_bit(  unsigned char, unsigned short);
	ECASOLEILZMI4104CLIB_API int DisableVMEInterrupt_bit(  unsigned char, unsigned short);
	ECASOLEILZMI4104CLIB_API int EnableVMEGlobalInterrupt(  unsigned char);
	ECASOLEILZMI4104CLIB_API int DisableGlobalInterrupt(  unsigned char);
	ECASOLEILZMI4104CLIB_API int DisableAllVMEInterrupts(  unsigned char);
	ECASOLEILZMI4104CLIB_API int SetKpAndKvCoeff(  unsigned char, int, int);
	ECASOLEILZMI4104CLIB_API int getKpAndKvCoeff(unsigned char axis, int* coeff);
	ECASOLEILZMI4104CLIB_API int getAPDGainL2(unsigned char axis, unsigned int* APDGainL2);
	ECASOLEILZMI4104CLIB_API int getAPDBiasDAC(unsigned char axis, unsigned int* APDBiasDac);
	ECASOLEILZMI4104CLIB_API int getAPDOptPwrL2(unsigned char axis, unsigned int* APDOptPwrL2);
	ECASOLEILZMI4104CLIB_API int getAPDSigRMSL2(unsigned char axis, unsigned int* APDSigRMSL2);
	ECASOLEILZMI4104CLIB_API int ReadAPDCtrlSoftErrs(  unsigned char);
	ECASOLEILZMI4104CLIB_API int ReadAllErrs(  unsigned char);
	ECASOLEILZMI4104CLIB_API int SetTimeDelayBetweenResAndCompleteBit(  unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int EnableAllVMEInterrupts(  unsigned char);
	ECASOLEILZMI4104CLIB_API int EnableVMEGlobalInterrupt(  unsigned char);
	ECASOLEILZMI4104CLIB_API int setVMEIntVector(  unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int setVMEIntLevel(  unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int sis3301w_Init(  uint32_t, uint32_t, uint32_t);
	ECASOLEILZMI4104CLIB_API int AckForSis3100VME_Irq(  uint32_t);
	ECASOLEILZMI4104CLIB_API int getFlyscanData(  uint32_t*, uint32_t*, uint32_t*, uint32_t size);
	ECASOLEILZMI4104CLIB_API uint32_t* allocateMemSpace(uint32_t);
	ECASOLEILZMI4104CLIB_API int processRAMData(uint32_t, uint32_t*, uint32_t*, uint32_t size, char* folderName, double* meanVal, double* stdDevVal);
	ECASOLEILZMI4104CLIB_API int processFifoData(uint32_t nbrAxis, uint8_t* axisTab, uint32_t* memPtr, uint32_t nbrOfPts, uint8_t* folderName, double* meanVal, double* stdDevVal);
	ECASOLEILZMI4104CLIB_API int configureFifoFlyscan(  fifoParam* fifoparameters, uint32_t* startAdress, uint8_t* axisTab, uint32_t* sizeOfTab, int32_t* ret_code);
	ECASOLEILZMI4104CLIB_API int fifoFlyscan(  fifoParam, uint32_t*, uint8_t, int32_t* ret_code, ...);
	ECASOLEILZMI4104CLIB_API bool isFifoDavbitSet(  unsigned char);
	ECASOLEILZMI4104CLIB_API bool isFifoOVFbitSet(  unsigned char);
	ECASOLEILZMI4104CLIB_API int configureFlyscan(  unsigned char, double, uint8_t);
	ECASOLEILZMI4104CLIB_API int convertCInt162Complex(uint32_t, complex*);
	ECASOLEILZMI4104CLIB_API int convertCFloat2Complex(uint32_t, complex*);
	ECASOLEILZMI4104CLIB_API int setSSISquelch(unsigned short axis, uint32_t squelchValue);
	ECASOLEILZMI4104CLIB_API int getSSISquelch(unsigned short axis, uint32_t* squelchValue);
	ECASOLEILZMI4104CLIB_API int waitCEinit2Complete(  unsigned char);
	ECASOLEILZMI4104CLIB_API int SetCEMaxVel(  unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int SetCEMinVel(  unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int readCalcCECoeffs(  unsigned char, CECoeffs*);
	ECASOLEILZMI4104CLIB_API int setGainControlAGC(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int resetGainControlAGC(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int setGainMinControl(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int resetGainMinControl(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int setGainMaxControl(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int resetGainMaxControl(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int readCECoeffboundaries(  unsigned char, CECoeffBoundaries*, CECoeffBoundaries*);
	ECASOLEILZMI4104CLIB_API int calculateCEratio( unsigned char axis, CEratios* ceRatios, CEratioUnits units);
	ECASOLEILZMI4104CLIB_API int EEPROMread(  unsigned short, unsigned int*, unsigned short);
	ECASOLEILZMI4104CLIB_API int convertFloat2Double(uint32_t, double*);
	ECASOLEILZMI4104CLIB_API int SetAPDBiasDAC( unsigned char axis, unsigned int APDBiasDac);
	ECASOLEILZMI4104CLIB_API int EnableGlitchFilter( unsigned char axis, unsigned short glitchFilterTime);
	ECASOLEILZMI4104CLIB_API int readGSEData(unsigned int axis, double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC);
	ECASOLEILZMI4104CLIB_API int readGSEData_ForAllAxis(double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC);
#ifdef __cplusplus
}
#endif
