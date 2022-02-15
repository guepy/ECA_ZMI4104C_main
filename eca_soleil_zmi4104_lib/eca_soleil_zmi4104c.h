#pragma once


#ifdef ECA_SOLEIL_ZMI4104C_LIB_EXPORTS
#define ECASOLEILZMI4104CLIB_API __declspec(dllexport)
#else
#define ECASOLEILZMI4104CLIB_API __declspec(dllimport)
#endif

#pragma comment (lib, "sis1100w.lib")
#ifdef __cplusplus
extern "C" {
#endif

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


#ifdef __cplusplus
}
#endif
#define KPMIN								-7
#define KPMAX								-2
#define KVMIN								-21
#define KVMAX								-7
#define LOGICAL_AND_OP_CODE					0
#define LOGICAL_OR_OP_CODE					1
#define ADDITION_OR_OP_CODE					2
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
#define MAX_HEAP_SIZE						0x10000000
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
#define NBR_RAM_PAGES						64
#define NBR_SAMP_PER_PAGE					256
#define CE_MIN_VEL							50 // min vel is 0.5mm/s
#define CE_MAX_VEL							31457 // max vel is 0.38 m/s
#define ACTIVATE_CEC						0
#define FIFO_FLYSCAN_MODE					1
	typedef struct _comp 
	{
		double rpart;
		double ipart;
	}complex;

	typedef struct _CECoeffs 
	{
		complex CEC0coeff;	// 20MHz(Leakage) cyclic error
		double CEC1coeff;	//Doppler signal magnitude 
		complex CECNcoeff;	//Negative doppler cyclic error
	}CECoeffs;
	typedef struct _CECoeffBoundaries 
	{
		double CEMagcoeff;
		double CEMincoeff;
		double CEMaxcoeff;
	}CECoeffBoundaries;
	typedef struct _fifoParam 
	{
		double acqTime; // ACQUISITION TIME in ms
		uint32_t freq;	// sample frequency in Hz
		uint32_t nbrPts;	// number of points to acquire
	}fifoParam;
	typedef struct _CEratios 
	{
		double measSignal;
		double CE0ratio;
		double CENratio;
	}CEratios;
	typedef struct _CEratiosBoundaries 
	{
		double CEMinratio;
		double CEMaxratio;
	}CEratiosBoundaries;
	typedef enum _CEratioUnits 
	{
		ratio_in_dB = 0,
		ratio_in_percent = 1,
		ratio_in_nmRMS = 2
	}CEratioUnits;
	typedef enum _SCLK
	{
		SCLK0 = 0,
		SCLK1 = 1
	}SCLK;
	static const char* access_mode_Selection[MAX_NOF_ACCESS_MODE_DEFINES] = 
	{
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
	static const char* biasControlModeString[BIAS_CTRL_MODE_NBR] = 
	{
		"BIAS_OFF_MODE",
		"BIAS_CONSTANT_VOLTAGE_MODE",
		"BIAS_CONSTANT_GAIN_MODE",
		"BIAS_ACONSTANT_OPTICAL_POWER_MODE",
		"BIAS_SIG_RMS_ADJUST_MODE",
	};

	static uint32_t	BASE_ADDRESS[] = { 0x14000, 0x15000, 0x16000, 0x17000 }; // Base adresses;

	static char* POSITION_FILE_PATH;
	static char PCI_VME_GATEWAY_FIRMWARE_VERSION[50];
	static char PCI_VME_GATEWAY_BOARD_VERSION[50];
	static char str[256];
	static char ZYGO_BOARD_VERSION[50];
	static char ZYGO_BOARD_SN[50];
	static char ZYGO_FIRMWARE_VERSION[50];
	static char ZYGO_BOARD_TYPE[50];
	static bool currentSampleSclk = 0;
	static bool currentResetSclk = 0;
	static bool curPrecision = 0;
	//static variable which hold the cached value of sampling frequency in Hertz
	static uint32_t currentSamplingFrequency = 0;

	static uint8_t tabLen = sizeof(ZYGO_BOARD_TYPE) / sizeof(ZYGO_BOARD_TYPE[0]);
	/**/
	//GUID sis1100w_GUID = { 0x944adde8, 0x4f6d, 0x4bee, 0xa309, 0x7ad62ab0b4bb };

	/// <summary>
	/// APD Bias Mode typedef
	/// </summary>
	typedef enum _BIAS_MODE 
	{
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
	static uint32_t curInterferoConfig=1;
	static bool cecState = 0;
	static FILE* fdLog;
	static SYSTEMTIME  lt;
	static SIS1100_Device_Struct* dev = new SIS1100_Device_Struct;

	ECASOLEILZMI4104CLIB_API int initAxis(BIAS_MODE bias_mode);
	ECASOLEILZMI4104CLIB_API int initSisBoards();
	ECASOLEILZMI4104CLIB_API int initZmiBoards();
	//ECASOLEILZMI4104CLIB_API int sis3301wInit(uint32_t, uint32_t, uint32_t);
	ECASOLEILZMI4104CLIB_API uint32_t* allocateMemSpace(uint32_t mem_size);
	ECASOLEILZMI4104CLIB_API int vmeSysReset();
	ECASOLEILZMI4104CLIB_API int boardControlMode(uint8_t axis, uint32_t biasMode);
	ECASOLEILZMI4104CLIB_API int setBiasMode(uint8_t axis, uint32_t biasMode);
	ECASOLEILZMI4104CLIB_API int getBiasMode(uint8_t axis, uint32_t* biasMode);
	ECASOLEILZMI4104CLIB_API int startBiasCalculation(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int setTimeDelayBetweenResAndCompleteBit(uint8_t axis, uint8_t timeDelay);
	ECASOLEILZMI4104CLIB_API int resetAxis(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int waitResetComplete(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int enablePreset(uint8_t axis);

	ECASOLEILZMI4104CLIB_API int setPrecision(bool precision);
	ECASOLEILZMI4104CLIB_API bool getPrecision();

	ECASOLEILZMI4104CLIB_API int enableSinglePassInterferometer(void);
	ECASOLEILZMI4104CLIB_API int enableDoublePassInterferometer(void);

	ECASOLEILZMI4104CLIB_API const char* getSisBoardVersion();
	ECASOLEILZMI4104CLIB_API const char* getSisFirmwareVersion();
	ECASOLEILZMI4104CLIB_API const char* getZygoBoardRef();
	ECASOLEILZMI4104CLIB_API const char* getZygoFirmwareVersion();
	ECASOLEILZMI4104CLIB_API const char* getZygoSerialNumber();
	ECASOLEILZMI4104CLIB_API const char* getZygoBoardVersion();

	ECASOLEILZMI4104CLIB_API uint32_t getInterferometerConfiguration();
	ECASOLEILZMI4104CLIB_API int setInterferometerConfiguration(uint32_t config);

	ECASOLEILZMI4104CLIB_API bool getCachedCecState();
	ECASOLEILZMI4104CLIB_API int disableCecCompensation( uint8_t axis);
	ECASOLEILZMI4104CLIB_API int configureCecHardware(uint8_t axis, USHORT ceVelMin, USHORT ceVelMax);
	ECASOLEILZMI4104CLIB_API int readCecoefBoundaries(uint8_t axis, CECoeffBoundaries* CE0CoeffBound, CECoeffBoundaries* CENCoeffBound);
	ECASOLEILZMI4104CLIB_API int readCalcCecoeffs(uint8_t axis, CECoeffs* CECalcCoeffs);
	ECASOLEILZMI4104CLIB_API int enableCecCompensation(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int setSampleSourceClock(uint8_t axis, bool sclk);
	ECASOLEILZMI4104CLIB_API int setResetSourceClock(uint8_t axis, bool sclk);
	ECASOLEILZMI4104CLIB_API int getSampleSourceClock(uint8_t axis, bool* sclk);
	ECASOLEILZMI4104CLIB_API int getResetSourceClock(uint8_t axis, bool* sclk);
	ECASOLEILZMI4104CLIB_API int calculateCeratio(uint8_t axis, CEratios* ceRatios, CEratioUnits units);
	ECASOLEILZMI4104CLIB_API int readCecErrorStatReg( uint8_t axis, uint32_t* CEstatReg);
	ECASOLEILZMI4104CLIB_API int getAproximateCeratio(uint8_t axis, CEratios* ceRatios, CEratioUnits units);
	ECASOLEILZMI4104CLIB_API int waitCeinit2Complete(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int setCemaxVel(uint8_t axis, uint32_t CEMaxVelValue);
	ECASOLEILZMI4104CLIB_API int setCeminVel(uint8_t axis, uint32_t CEMinVelValue);

	ECASOLEILZMI4104CLIB_API int getLedsStatus( bool* ledsStatus);
	ECASOLEILZMI4104CLIB_API int getLedsErrorStatus( bool* ledsErrorStatus);

	ECASOLEILZMI4104CLIB_API void setBaseAddress(uint32_t baseAddressAxis3);
	ECASOLEILZMI4104CLIB_API uint32_t getCachedBaseAddress();

	ECASOLEILZMI4104CLIB_API void createEvents();
	ECASOLEILZMI4104CLIB_API int  createThreads( );
	ECASOLEILZMI4104CLIB_API void closeThreads(void);

	ECASOLEILZMI4104CLIB_API int zygoLogFatal(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int zygoLogWarn(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int zygoLogInfo(const char* fmt, ...);

	ECASOLEILZMI4104CLIB_API int getGainControlAgc(uint8_t axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int getGainMinControl(uint8_t axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int getGainMaxControl(uint8_t axis, bool* agcState);

	ECASOLEILZMI4104CLIB_API bool getCachedSampleSclk();
	ECASOLEILZMI4104CLIB_API bool getCachedResetSclk();

	ECASOLEILZMI4104CLIB_API int readWrite(const char* ch_access_mode, uint32_t uint_vme_address, uint32_t* uint_vme_data,
		uint16_t read_write);
	ECASOLEILZMI4104CLIB_API int eepromRead(uint16_t offset, uint32_t* uint_vme_data,uint16_t nBytes);

	ECASOLEILZMI4104CLIB_API int readSamplePosition32(uint8_t axis, double* position);
	ECASOLEILZMI4104CLIB_API int readSamplePosition37(uint8_t axis, double* position);
	ECASOLEILZMI4104CLIB_API int readPosition(uint8_t axis, double* position);
	ECASOLEILZMI4104CLIB_API int readPositionForAllAxis(double* position);
	ECASOLEILZMI4104CLIB_API int readFifoPosition(uint8_t axis, uint32_t* position);
	ECASOLEILZMI4104CLIB_API int sampleVmePosition(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int setPositionOffset32(uint8_t axis, double offsetPos);
	ECASOLEILZMI4104CLIB_API int setPositionOffset37(uint8_t axis, double offsetPos);
	ECASOLEILZMI4104CLIB_API int setPositionOffset(uint8_t axis, double offsetPos);
	ECASOLEILZMI4104CLIB_API int getPositionOffset(uint8_t axis, double* offsetPos);
	ECASOLEILZMI4104CLIB_API int setPresetPosition32(uint8_t axis, double presetPos32);
	ECASOLEILZMI4104CLIB_API int setPresetPosition37(uint8_t axis, double presetPos);
	ECASOLEILZMI4104CLIB_API int setPresetPosition(uint8_t axis, double presetPos);
	ECASOLEILZMI4104CLIB_API int getPresetPosition(uint8_t axis, double* offsetPos);
	ECASOLEILZMI4104CLIB_API int isVmePos32Overflow(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int setHoldSampEnable();

	ECASOLEILZMI4104CLIB_API int enable32BitsOverflow(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int disable32BitsOverflow(uint8_t axis);

	ECASOLEILZMI4104CLIB_API int enable37BitsSignExtension(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int disable37bitsSignExtension(uint8_t axis);

	ECASOLEILZMI4104CLIB_API int readTime(uint8_t axis, double* time);
	ECASOLEILZMI4104CLIB_API int readTimeForAllAxis(double* time);

	ECASOLEILZMI4104CLIB_API int readVelocity(uint8_t axis, double* velocity);
	ECASOLEILZMI4104CLIB_API int readVelocityForAllAxis(double* velocity);

	ECASOLEILZMI4104CLIB_API int readOpticalPowerUsingSsiAv(double* opticalPower);
	ECASOLEILZMI4104CLIB_API int readSsiAv(double* ssi);
	ECASOLEILZMI4104CLIB_API int readSsiCalibrationData(uint8_t axis, double* SSIVals, double* OptPwrVals);

	ECASOLEILZMI4104CLIB_API int readApdGain(uint8_t axis, double*apdGain);
	ECASOLEILZMI4104CLIB_API int readApdGainForAllAxis(double* apdGain);

	ECASOLEILZMI4104CLIB_API int setSsiSquelch(uint16_t axis, uint32_t squelchValue);
	ECASOLEILZMI4104CLIB_API int getSsiSquelch(uint16_t axis, uint32_t* squelchValue);

	ECASOLEILZMI4104CLIB_API int readGseData(uint32_t axis, double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC);
	ECASOLEILZMI4104CLIB_API int readGseDataForAllAxis(double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC);

	ECASOLEILZMI4104CLIB_API int setApdBiasDac(uint8_t axis, uint32_t APDBiasDac);
	ECASOLEILZMI4104CLIB_API int getApdBiasDac(uint8_t axis, uint32_t* APDBiasDac);

	ECASOLEILZMI4104CLIB_API int setApdL2Gain(uint8_t axis, uint32_t);
	ECASOLEILZMI4104CLIB_API int getApdL2Gain(uint8_t axis, uint32_t* APDGainL2);

	ECASOLEILZMI4104CLIB_API int setApdL2OptPwr(uint8_t axis, uint32_t APDOptPwrL2);
	ECASOLEILZMI4104CLIB_API int getApdL2OptPwr(uint8_t axis, uint32_t* APDOptPwrL2);

	ECASOLEILZMI4104CLIB_API int setApdL2SigRms(uint8_t axis, uint32_t APDSigRMSL2);
	ECASOLEILZMI4104CLIB_API int getApdL2SigRms(uint8_t axis, uint32_t* APDSigRMSL2);

	ECASOLEILZMI4104CLIB_API int enableAuxRegisters(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int disableAuxRegisters(uint8_t axis);

	ECASOLEILZMI4104CLIB_API int sclkOn();
	ECASOLEILZMI4104CLIB_API int sclkOff();
	ECASOLEILZMI4104CLIB_API uint32_t getCachedSamplingFrequency();
	ECASOLEILZMI4104CLIB_API int setSamplingFrequency(uint32_t sampleFreq);
	ECASOLEILZMI4104CLIB_API int getSamplingFrequency(uint32_t* sampFreq);
	ECASOLEILZMI4104CLIB_API int enableSampling(uint32_t);
	ECASOLEILZMI4104CLIB_API int disableSampleTimer();
	ECASOLEILZMI4104CLIB_API int setSampTimerFreq(uint16_t sampTimerVal);
	ECASOLEILZMI4104CLIB_API int getVmeExtSampFlag(uint8_t axis);

	ECASOLEILZMI4104CLIB_API int resetHoldSampEnable();
	ECASOLEILZMI4104CLIB_API int enableResetFindsVelocity(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int enableResetFindsVelocityForAllAxis();
	ECASOLEILZMI4104CLIB_API int disableResetFindsVelocity(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int disableResetFindsVelocityForAllAxis();

	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus2(uint8_t axis, uint32_t* vmeErrorStatus2);
	ECASOLEILZMI4104CLIB_API int parseVmePosErrs(uint8_t axis, uint32_t* vmePosErrs);
	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus1(uint8_t axis, uint32_t* vmeErrorStatus1);
	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus0(uint8_t axis, uint32_t* vmeErrorStatus0);
	ECASOLEILZMI4104CLIB_API int parseApdErrCode(uint8_t axis, uint32_t* apdErrCode);
	ECASOLEILZMI4104CLIB_API int readCecErrorStatReg(uint8_t axis, uint32_t* CEstatReg);
	ECASOLEILZMI4104CLIB_API int readVmeErrs(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int readApdCtrlSoftErrs(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int readAllErrs(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int checkLimits(int num2check, int minVal, int maxVal);

	ECASOLEILZMI4104CLIB_API int configureFlyscan(uint8_t axis, double, uint8_t);
	ECASOLEILZMI4104CLIB_API int startAquisition(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int stopAquisition(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int getFlyscanData(uint32_t*, uint32_t*, uint32_t*, uint32_t ramPagesNbr);
	ECASOLEILZMI4104CLIB_API int processRamData(uint32_t, uint32_t*, uint32_t*, uint32_t ramPagesNbr, char* folderName, double* meanVal, double* stdDevVal);

	ECASOLEILZMI4104CLIB_API int configureFifoFlyscan(fifoParam* fifoparameters, uint32_t* startAdress, uint8_t* axisTab, uint32_t* sizeOfTab, int32_t* ret_code, bool mode);
	ECASOLEILZMI4104CLIB_API int fifoFlyscan(fifoParam param, uint32_t* startAddress, uint8_t nbrAxis, int32_t* ret_code, ...);
	ECASOLEILZMI4104CLIB_API int manualFifoFlyscan(fifoParam *param, uint32_t* startAddress, uint8_t nbrAxis, int32_t* ret_code, ...);
	ECASOLEILZMI4104CLIB_API int processFifoData(uint32_t nbrAxis, uint8_t* axisTab, uint32_t* memPtr, uint32_t nbrOfPts, uint8_t* folderName, double* meanVal, double* stdDevVal);
	ECASOLEILZMI4104CLIB_API bool isFifoDavBitSet(uint8_t axis);
	ECASOLEILZMI4104CLIB_API bool isFifoOvfBitSet(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int convertCint162Complex(uint32_t, complex*);
	ECASOLEILZMI4104CLIB_API int convertCfloat2Complex(uint32_t, complex*);
	ECASOLEILZMI4104CLIB_API bool isRamBusy();

	ECASOLEILZMI4104CLIB_API int setGainControlAgc(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int resetGainControlAgc(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int setGainMinControl(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int resetGainMinControl(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int setGainMaxControl(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int resetGainMaxControl(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int readScaledSsiAv(double* ssiPtr);

	ECASOLEILZMI4104CLIB_API int convertFloat2Double(uint32_t floatNbr, double* doubleVal);
	ECASOLEILZMI4104CLIB_API int convertUsfloat2Double(uint16_t USFloatNbr, double* doubleVal);


	ECASOLEILZMI4104CLIB_API int enableVmeInterruptBit(uint8_t axis, uint16_t intNumber);
	ECASOLEILZMI4104CLIB_API int disableVmeInterruptBit(uint8_t axis, uint16_t intNumber);
	ECASOLEILZMI4104CLIB_API int enableVmeGlobalInterrupt(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int disableGlobalInterrupt(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int disableAllVmeInterrupts(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int enableAllVmeInterrupts(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int enableVmeGlobalInterrupt(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int setVmeIntVector(uint8_t axis, uint8_t IntVect);
	ECASOLEILZMI4104CLIB_API int setVmeIntLevel(uint8_t axis, uint8_t IntVect);
	ECASOLEILZMI4104CLIB_API int ackForSis3100VmeIrq(uint32_t);

	ECASOLEILZMI4104CLIB_API int setKpAndKvCoeff(uint8_t axis, int Kp, int Kv);
	ECASOLEILZMI4104CLIB_API int getKpAndKvCoeff(uint8_t axis, int* coeff);

