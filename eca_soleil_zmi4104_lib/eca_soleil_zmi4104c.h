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
#define SAMP_FREQ_MIN						305	// 1/(65536*005) in Hz
#define SAMP_FREQ_MIN_DIV_2					305/2	//in Mhz. min freq with divide by 2 enable in control register 16
#define SAMP_FREQ_MAX						20000000			// 1/(005) in Hz
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
		unsigned int freq;	// sample frequency in Hz
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
	static char str[256];
	static char ZYGO_BOARD_VERSION[50];
	static char ZYGO_BOARD_SN[50];
	static char ZYGO_FIRMWARE_VERSION[50];
	static char ZYGO_BOARD_TYPE[50];
	static bool currentSampleSCLK = 0;
	static bool currentResetSCLK = 0;
	static bool curPrecision = 0;
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
	static int return_code = 0;
	static unsigned int curInterferoConfig=0;
	static bool cecState = 0;
	static FILE* fdLog;
	static SYSTEMTIME  lt;
	static SIS1100_Device_Struct* dev = new SIS1100_Device_Struct;

	ECASOLEILZMI4104CLIB_API int initAxis(BIAS_MODE);
	ECASOLEILZMI4104CLIB_API int initSisBoards();
	ECASOLEILZMI4104CLIB_API int initZmiBoards();
	ECASOLEILZMI4104CLIB_API int sis3301wInit(uint32_t, uint32_t, uint32_t);
	ECASOLEILZMI4104CLIB_API uint32_t* allocateMemSpace(uint32_t);
	ECASOLEILZMI4104CLIB_API int vmeSysReset();
	ECASOLEILZMI4104CLIB_API int boardControlMode(unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int biasControlMode(unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int startBiasCalculation(unsigned char);
	ECASOLEILZMI4104CLIB_API int setTimeDelayBetweenResAndCompleteBit(unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int resetAxis(unsigned char);
	ECASOLEILZMI4104CLIB_API int waitResetComplete(unsigned char);
	ECASOLEILZMI4104CLIB_API int enablePreset(unsigned char axis);

	ECASOLEILZMI4104CLIB_API int setPrecision(bool prec);
	ECASOLEILZMI4104CLIB_API bool getPrecision();

	ECASOLEILZMI4104CLIB_API int enableSinglePassInterferometer(void);
	ECASOLEILZMI4104CLIB_API int enableDoublePassInterferometer(void);

	ECASOLEILZMI4104CLIB_API const char* getZygoFactoryProp();
	ECASOLEILZMI4104CLIB_API const char* getSisFactoryProp();
	ECASOLEILZMI4104CLIB_API uint32_t getCurrentInterType();

	ECASOLEILZMI4104CLIB_API bool getCecState();
	ECASOLEILZMI4104CLIB_API int disableCecCompensation( unsigned char axis);
	ECASOLEILZMI4104CLIB_API int configureCecHardware(uint8_t, uint16_t, uint16_t);
	ECASOLEILZMI4104CLIB_API int readCecoefBoundaries(unsigned char, CECoeffBoundaries*, CECoeffBoundaries*);
	ECASOLEILZMI4104CLIB_API int readCalcCecoeffs(unsigned char, CECoeffs*);
	ECASOLEILZMI4104CLIB_API int enableCecCompensation(unsigned char);
	ECASOLEILZMI4104CLIB_API int setSampleSourceClock(unsigned char axis, bool SCLK);
	ECASOLEILZMI4104CLIB_API int setResetSourceClock(unsigned char axis, bool SCLK);
	ECASOLEILZMI4104CLIB_API int getSampleSourceClock(unsigned char axis, bool* SCLK);
	ECASOLEILZMI4104CLIB_API int getResetSourceClock(unsigned char axis, bool* SCLK);
	ECASOLEILZMI4104CLIB_API int calculateCeratio(unsigned char axis, CEratios* ceRatios, CEratioUnits units);
	ECASOLEILZMI4104CLIB_API int readCecErrorStatReg( unsigned char axis, uint32_t* CEstatReg);
	ECASOLEILZMI4104CLIB_API int getAproximateCeratio(unsigned char, CEratios*, CEratioUnits);
	ECASOLEILZMI4104CLIB_API int waitCeinit2Complete(unsigned char);
	ECASOLEILZMI4104CLIB_API int setCemaxVel(unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int setCeminVel(unsigned char, unsigned int);

	ECASOLEILZMI4104CLIB_API int getLedsStatus( bool* ledsStatus);
	ECASOLEILZMI4104CLIB_API int getLedsErrorStatus( bool* ledsErrorStatus);

	ECASOLEILZMI4104CLIB_API void setBaseAddress(uint32_t baseAddressAxis3);
	ECASOLEILZMI4104CLIB_API uint32_t getBaseAddress();

	ECASOLEILZMI4104CLIB_API void createEvents();
	ECASOLEILZMI4104CLIB_API int  createThreads( );
	ECASOLEILZMI4104CLIB_API void closeThreads(void);

	ECASOLEILZMI4104CLIB_API int fatal(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int warn(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int info(const char* fmt, ...);

	ECASOLEILZMI4104CLIB_API int getGainControlAgc(unsigned char axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int getGainMinControl(unsigned char axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int getGainMaxControl(unsigned char axis, bool* agcState);

	ECASOLEILZMI4104CLIB_API bool getSampleSclk();
	ECASOLEILZMI4104CLIB_API bool getResetSclk();

	ECASOLEILZMI4104CLIB_API int readWrite(const char*, unsigned int, unsigned int*, unsigned short);
	ECASOLEILZMI4104CLIB_API int eepromRead(unsigned short, unsigned int*, unsigned short);

	ECASOLEILZMI4104CLIB_API int readSamplePosition32(unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int readSamplePosition37(unsigned char axis, double* position);
	ECASOLEILZMI4104CLIB_API int readPosition(unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int readPositionForAllAxis(double* position);
	ECASOLEILZMI4104CLIB_API int readFifoPosition(unsigned char, uint32_t* position);
	ECASOLEILZMI4104CLIB_API int sampleVmePosition(unsigned char);
	ECASOLEILZMI4104CLIB_API int setPresetPosition32(unsigned char axis, unsigned int presetPos32);
	ECASOLEILZMI4104CLIB_API int setPositionOffset32(unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int setPositionOffset37(unsigned char, double offsetPos);
	ECASOLEILZMI4104CLIB_API int setPresetPosition37(unsigned char, double presetPos);
	ECASOLEILZMI4104CLIB_API int isVmePos32Overflow(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int setHoldSampEnable();

	ECASOLEILZMI4104CLIB_API int enable32BitsOverflow(unsigned char);
	ECASOLEILZMI4104CLIB_API int disable32BitsOverflow(unsigned char);

	ECASOLEILZMI4104CLIB_API int enable37BitsSignExtension(unsigned char);
	ECASOLEILZMI4104CLIB_API int disable37bitsSignExtension(unsigned char);

	ECASOLEILZMI4104CLIB_API int readTime(unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int readTimeForAllAxis(double*);

	ECASOLEILZMI4104CLIB_API int readVelocity(unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int readVelocityForAllAxis(double*);

	ECASOLEILZMI4104CLIB_API int readOpticalPowerUsingSsiAv(double*);
	ECASOLEILZMI4104CLIB_API int readSsiAv(double* ssiPtr);
	ECASOLEILZMI4104CLIB_API int readSsiCalibrationData(unsigned char axis, double* SSIVals, double* OptPwrVals);

	ECASOLEILZMI4104CLIB_API int readApdGain(unsigned char, double*);
	ECASOLEILZMI4104CLIB_API int readApdGainForAllAxis(double*);

	ECASOLEILZMI4104CLIB_API int setSsiSquelch(unsigned short axis, uint32_t squelchValue);
	ECASOLEILZMI4104CLIB_API int getSsiSquelch(unsigned short axis, uint32_t* squelchValue);

	ECASOLEILZMI4104CLIB_API int readGseData(unsigned int axis, double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC);
	ECASOLEILZMI4104CLIB_API int readGseDataForAllAxis(double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC);

	ECASOLEILZMI4104CLIB_API int setApdBiasDac(unsigned char axis, unsigned int APDBiasDac);
	ECASOLEILZMI4104CLIB_API int getApdBiasDac(unsigned char axis, unsigned int* APDBiasDac);

	ECASOLEILZMI4104CLIB_API int setApdL2Gain(unsigned char, unsigned int);
	ECASOLEILZMI4104CLIB_API int getApdL2Gain(unsigned char axis, unsigned int* APDGainL2);

	ECASOLEILZMI4104CLIB_API int setApdL2OptPwr(unsigned char axis, unsigned int APDOptPwrL2);
	ECASOLEILZMI4104CLIB_API int getApdL2OptPwr(unsigned char axis, unsigned int* APDOptPwrL2);

	ECASOLEILZMI4104CLIB_API int setApdL2SigRms(unsigned char axis, unsigned int APDSigRMSL2);
	ECASOLEILZMI4104CLIB_API int getApdL2SigRms(unsigned char axis, unsigned int* APDSigRMSL2);

	ECASOLEILZMI4104CLIB_API int enableAuxRegisters(unsigned char);
	ECASOLEILZMI4104CLIB_API int disableAuxRegisters(unsigned char);

	ECASOLEILZMI4104CLIB_API int sclkOn();
	ECASOLEILZMI4104CLIB_API int sclkOff();
	ECASOLEILZMI4104CLIB_API unsigned int getSampFreq();
	ECASOLEILZMI4104CLIB_API int setSamplingFrequency(unsigned int sampleFreq);
	ECASOLEILZMI4104CLIB_API int getSamplingFrequency(double* sampFreq);
	ECASOLEILZMI4104CLIB_API int enableSampling(unsigned int);
	ECASOLEILZMI4104CLIB_API int disableSampleTimer();
	ECASOLEILZMI4104CLIB_API int setSampTimerFreq(unsigned short);
	ECASOLEILZMI4104CLIB_API int getVmeExtSampFlag(unsigned char);

	ECASOLEILZMI4104CLIB_API int resetHoldSampEnable();
	ECASOLEILZMI4104CLIB_API int enableResetFindsVelocity(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int enableResetFindsVelocityForAllAxis();
	ECASOLEILZMI4104CLIB_API int disableResetFindsVelocity(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int disableResetFindsVelocityForAllAxis();

	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus2(unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int parseVmePosErrs(unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus1(unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus0(unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int parseApdErrCode(unsigned char, unsigned int*);
	ECASOLEILZMI4104CLIB_API int readCecErrorStatReg(unsigned char axis, uint32_t* CEstatReg);
	ECASOLEILZMI4104CLIB_API int readVmeErrs(unsigned char);
	ECASOLEILZMI4104CLIB_API int readApdCtrlSoftErrs(unsigned char);
	ECASOLEILZMI4104CLIB_API int readAllErrs(unsigned char);
	ECASOLEILZMI4104CLIB_API int checkValues(int, int, int);

	ECASOLEILZMI4104CLIB_API int configureFlyscan(unsigned char, double, uint8_t);
	ECASOLEILZMI4104CLIB_API int startAquisition(unsigned char);
	ECASOLEILZMI4104CLIB_API int stopAquisition(unsigned char);
	ECASOLEILZMI4104CLIB_API int getFlyscanData(uint32_t*, uint32_t*, uint32_t*, uint32_t size);
	ECASOLEILZMI4104CLIB_API int processRamData(uint32_t, uint32_t*, uint32_t*, uint32_t size, char* folderName, double* meanVal, double* stdDevVal);

	ECASOLEILZMI4104CLIB_API int configureFifoFlyscan(fifoParam* fifoparameters, uint32_t* startAdress, uint8_t* axisTab, uint32_t* sizeOfTab, int32_t* ret_code, bool mode);
	ECASOLEILZMI4104CLIB_API int fifoFlyscan(fifoParam param, uint32_t* startAddress, uint8_t nbrAxis, int32_t* ret_code, ...);
	ECASOLEILZMI4104CLIB_API int manualFifoFlyscan(fifoParam param, uint32_t* startAddress, uint8_t nbrAxis, int32_t* ret_code, ...);
	ECASOLEILZMI4104CLIB_API int processFifoData(uint32_t nbrAxis, uint8_t* axisTab, uint32_t* memPtr, uint32_t nbrOfPts, uint8_t* folderName, double* meanVal, double* stdDevVal);
	ECASOLEILZMI4104CLIB_API bool isFifoDavBitSet(unsigned char);
	ECASOLEILZMI4104CLIB_API bool isFifoOvfBitSet(unsigned char);
	ECASOLEILZMI4104CLIB_API int convertCint162Complex(uint32_t, complex*);
	ECASOLEILZMI4104CLIB_API int convertCfloat2Complex(uint32_t, complex*);
	ECASOLEILZMI4104CLIB_API bool isRamBusy();

	ECASOLEILZMI4104CLIB_API int setGainControlAgc(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int resetGainControlAgc(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int setGainMinControl(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int resetGainMinControl(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int setGainMaxControl(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int resetGainMaxControl(unsigned char axis);
	ECASOLEILZMI4104CLIB_API int readScaledSsiAv(double* ssiPtr);

	ECASOLEILZMI4104CLIB_API int convertFloat2Double(uint32_t, double*);
	ECASOLEILZMI4104CLIB_API int convertUsfloat2Double(uint16_t, double*);


	ECASOLEILZMI4104CLIB_API int enableVmeInterruptBit(  unsigned char, unsigned short);
	ECASOLEILZMI4104CLIB_API int disableVmeInterruptBit(  unsigned char, unsigned short);
	ECASOLEILZMI4104CLIB_API int enableVmeGlobalInterrupt(  unsigned char);
	ECASOLEILZMI4104CLIB_API int disableGlobalInterrupt(  unsigned char);
	ECASOLEILZMI4104CLIB_API int disableAllVmeInterrupts(  unsigned char);
	ECASOLEILZMI4104CLIB_API int enableAllVmeInterrupts(unsigned char);
	ECASOLEILZMI4104CLIB_API int enableVmeGlobalInterrupt(unsigned char);
	ECASOLEILZMI4104CLIB_API int setVmeIntVector(unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int setVmeIntLevel(unsigned char, unsigned char);
	ECASOLEILZMI4104CLIB_API int ackForSis3100VmeIrq(uint32_t);

	ECASOLEILZMI4104CLIB_API int setKpAndKvCoeff(  unsigned char, int, int);
	ECASOLEILZMI4104CLIB_API int getKpAndKvCoeff(unsigned char axis, int* coeff);

#ifdef __cplusplus
}
#endif
