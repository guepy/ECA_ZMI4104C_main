#pragma once


#ifdef ECASOLEILZMI4104LIB_EXPORTS
#define ECASOLEILZMI4104CLIB_API __declspec(dllexport)
#else
#define ECASOLEILZMI4104CLIB_API __declspec(dllimport)
#endif

#pragma comment (lib, "sis1100w.lib")
#include <complex>
#include <array>


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <vector>
#include "sis1100w.h"
#include "zVME_const.h"
#include "sis3302.h"
#include "sis3100.h"
#include "sis3100_vme_calls.h"
#include "zygoErrorCodes.h"
#ifdef __cplusplus
extern "C" {
#endif
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
#define QUAD_PASS_INT_POS_COEF				(0.1545388427734375*1e-6)/2 // LAMBDA/4096	==> 0.15 nm resolution
#define SSI_MAX_SAT							2047
#define SINGLE_PASS_INT_VEL_COEF			2.946705 * (1e-3)	//  ± 5.1 m/sec resolution
#define DOUBLE_PASS_INT_VEL_COEF			1.473352 * (1e-3)	// ± 2.55 m/sec resolution
#define QUAD_PASS_INT_VEL_COEF			(1.473352 * (1e-3))/2	// ± 2.55 m/sec resolution
#define CE_MAX_VEL_DFLT						31457
#define CE_MIN_VEL_DFLT						96
#define MAX_HEAP_SIZE						0x10000000
#define PI									3.14159265359
#define BIAS_CTRL_MODE_NBR					5		
#define NON_FATAL							0
#define EXIT_FAILLURE						-1
#define INFO_PURPOSE						2
#define SAMP_FREQ_MIN						305	// 1/(0xFFFF*0.05*2) in Hz
#define SAMP_FREQ_MIN_DIV_2					SAMP_FREQ_MIN/2	//in Mhz. min freq with divide by 2 enable in control register 16
#define SAMP_FREQ_MAX						1e7				
#define defaultAPDGAinL2Set					7
#define defaultAPDOptPwrL2Set				0
#define defaultAPDSigRMSL2Set				13200
#define defaultSSISquelch					800
#define ApdBiasVoltageCoeff					61.65
#define READ								0
#define WRITE								1
#define ERRSTRMAX							512
#define NBR_RAM_PAGES						64
#define NBR_SAMP_PER_PAGE					256
#define CE_MIN_VEL							24
#define CE_MAX_VEL							31457 // max vel is 0.38 m/s
#define ACTIVATE_CEC						0
#define FIFO_FLYSCAN_MODE					1
#define CE_VEL_COEFF						12e-3 // mm/s
#define A24D16_VME_ADDR_MODE				"A24D16"
#define A24D32_VME_ADDR_MODE				"A24D32"
#define A24D8_VME_ADDR_MODE					"A24D8"

typedef INT64 my_int64_t;
constexpr static const uint64_t TMP32 = static_cast<uint64_t>(1) << 32;
constexpr static const int defKp = -3;
constexpr static const int defKv = -9;
constexpr static const unsigned int defMinVel = 96;
constexpr static const double minOptPwrDC = 0.01; // µW
constexpr static const int minOptPwrDC_hex = 0xE56C;
constexpr static const double maxOptPwrDC = 100; // µW
constexpr static const int maxOptPwrDC_hex = 0x1A94;
constexpr static const int SIZE_WORDS = 100;
constexpr static const int EEPROM_AXIS_DATA_BASE_OFFSET = 50;
constexpr static const int EEPROM_NOM_SSI_OFFSET = 16;
constexpr static const int EEPROM_MIN_SSI_OFFSET = 9;
constexpr static const int EEPROM_MAX_SSI_OFFSET = 23;
constexpr static const int EEPROM_OPT_PWR_L2_MIN_OFFSET = 5;
constexpr static const int EEPROM_OPT_PWR_L2_NOM_OFFSET = 12;
constexpr static const int EEPROM_OPT_PWR_L2_MAX_OFFSET = 19;
static char logfileName[100];
static char fifoFile[100];
static char ramdataFile[100];
	struct CECoeffs 
	{
		std::complex<double> CEC0coeff;	// 20MHz(Leakage) cyclic error
		double CEC1coeff;	//Doppler signal magnitude 
		std::complex<double> CECNcoeff;	//Negative doppler cyclic error
	};
	struct CECLimits
	{
		double CEC0Limit;
		double CECNLimit;
	};
	
	struct CECoeffBoundaries 
	{
		double CEMagcoeff;
		double CEMincoeff;
		double CEMaxcoeff;
	};
	struct fifoParam 
	{
		double acqTime; // ACQUISITION TIME in ms
		uint32_t freq;	// sample frequency in Hz
		uint32_t nbrPts;	// number of points to acquire
	};
	struct CEratios 
	{
		double measSignal;
		double CE0ratio;
		double CENratio;
	};
	struct CEratiosBoundaries 
	{
		double CEMinratio;
		double CEMaxratio;
	};
	enum class Axes:uint8_t
	{
		Axis_1=1,
		Axis_2,
		Axis_3,
		Axis_4,
	};
	enum struct CEratioUnits
	{
		ratio_in_dB = 0,
		ratio_in_percent,
		ratio_in_nmRMS
	};
	enum class SampleDividerCoeffs :uint8_t
	{
		SDV0 = 0,
		SDV1,
		SDV2,
		SDV3,
		SDV4,
		SDV5,
		SDV6,
		SDV7,
		SDV8,
		SDV9,
		SDV10,
		SDV11,
		SDV12,
		SDV13,
		SDV14,
		SDV15
	};
	enum class State :bool
	{
		OFF = 0,
		ON = 1
	};
	enum class SCLK:bool
	{
		SCLK0 = 0,
		SCLK1 = 1
	};
	enum class SerialOutputDriver :bool
	{
		P2Z = 0,
		P2D = 1
	};
	enum class SerialDataPositionSize :bool
	{
		P32 = 0,
		P37 = 1
	};

	enum class BitWindow: uint8_t
	{
		BW1 = 0,
		BW2,
		BW4,
		BW8,
		BW16,
		BW32,
		BWhalf,
		BWquater
	};
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
	static const char* biasControlModeString[BIAS_CTRL_MODE_NBR] = {
		"OFF",//"OFF_MODE",
		"VOLT",//"CONSTANT_VOLTAGE_MODE",
		"GAIN",//"CONSTANT_GAIN_MODE",
		"OPWR",//"CONSTANT_OPT_PWR_MODE",
		"SRMS"//"SIG_RMS_ADJUST_MODE"
};

	static constexpr const Axes AXIS1 = Axes::Axis_1;
	static constexpr const Axes AXIS2 = Axes::Axis_2;
	static constexpr const Axes AXIS3 = Axes::Axis_3;
	static constexpr const Axes AXIS4 = Axes::Axis_4;
	static const std::vector<Axes> AXES = { AXIS1, AXIS2, AXIS3,AXIS4 };

	static uint32_t	BASE_ADDRESS[] = { 0x14000, 0x15000, 0x16000, 0x17000 }; // Base adresses;

	static char* POSITION_FILE_PATH;
	static char PCI_VME_GATEWAY_FIRMWARE_VERSION[50];
	static char PCI_VME_GATEWAY_BOARD_VERSION[50];
	static char str[256];
	static char ZYGO_BOARD_VERSION[50];
	static char ZYGO_BOARD_SN[50];
	static char ZYGO_FIRMWARE_VERSION[50];
	static char ZYGO_BOARD_TYPE[50];
	static SCLK currentVMEBusSclk = SCLK::SCLK0;
	static SCLK currentResetSclk = SCLK::SCLK0;
	static bool curPrecision = 0, INFO_LEVEL = 0;
	//static variable which hold the cached value of sampling frequency in Hertz
	static uint32_t currentSamplingFrequency[2] = { 0 };
	static HANDLE	zygoLogInfo_key,zygoLogWarn_key,zygoLogFatal_key, rw_key;
	static DWORD dwEvent;
	static uint8_t tabLen = sizeof(ZYGO_BOARD_TYPE) / sizeof(ZYGO_BOARD_TYPE[0]);	
	/**/
	//GUID sis1100w_GUID = { 0x944adde8, 0x4f6d, 0x4bee, 0xa309, 0x7ad62ab0b4bb };

	/// <summary>
	/// APD Bias Mode typedef
	/// </summary>
	enum class BIAS_MODE
	{
		BIAS_OFF_MODE = 0,
		BIAS_CONSTANT_VOLT_MODE,
		BIAS_CONSTANT_GAIN_MODE,
		BIAS_CONSTANT_OPT_PWR_MODE,
		BIAS_SIG_RMS_ADJUST_MODE
	};


	static double positionScale = DOUBLE_PASS_INT_POS_COEF,    //Converts to mm as default
		velocityScale = DOUBLE_PASS_INT_VEL_COEF * (1e-3);      //Converts to mm/s
		// ZMI Scalars
	static const double	timeScale = 25 * (1e-6);                   //Converts to ms as default	
	static const double	SSIScale = 0.019073486328125;           //Converts to mV as default	
	static int return_code = 0;
	static uint8_t curInterferoConfig=1;
	static bool cecState = 0;
	static FILE* fdLog;
	static SYSTEMTIME  lt;
	static SIS1100_Device_Struct* dev = new SIS1100_Device_Struct;

	ECASOLEILZMI4104CLIB_API int initAxis(BIAS_MODE bias_mode);
	ECASOLEILZMI4104CLIB_API int initSisBoards(bool argin);
	ECASOLEILZMI4104CLIB_API int initZmiBoards();
	//ECASOLEILZMI4104CLIB_API int sis3301wInit(uint32_t, uint32_t, uint32_t);
	ECASOLEILZMI4104CLIB_API uint32_t* allocateMemSpace(uint32_t mem_size);
	ECASOLEILZMI4104CLIB_API int vmeSysReset();
	ECASOLEILZMI4104CLIB_API int boardControlMode(Axes axis, BIAS_MODE biasMode);
	ECASOLEILZMI4104CLIB_API int setBiasMode(Axes axis, BIAS_MODE biasMode);
	ECASOLEILZMI4104CLIB_API int getBiasMode(Axes axis, BIAS_MODE& biasMode);
	ECASOLEILZMI4104CLIB_API int startBiasCalculation(Axes axis);
	ECASOLEILZMI4104CLIB_API int setTimeDelayBetweenResAndCompleteBit(Axes axis, uint8_t timeDelay);
	ECASOLEILZMI4104CLIB_API int resetAxis(Axes axis);
	ECASOLEILZMI4104CLIB_API int waitResetComplete(Axes axis);
	ECASOLEILZMI4104CLIB_API int enablePreset(Axes axis);

	ECASOLEILZMI4104CLIB_API int setPrecision(bool precision);
	ECASOLEILZMI4104CLIB_API bool getPrecision();

	ECASOLEILZMI4104CLIB_API int enableSinglePassInterferometer(void);
	ECASOLEILZMI4104CLIB_API int enableDoublePassInterferometer(void);
	ECASOLEILZMI4104CLIB_API int enableQuadPassInterferometer(void);

	ECASOLEILZMI4104CLIB_API const char* getSisBoardVersion();
	ECASOLEILZMI4104CLIB_API const char* getSisFirmwareVersion();
	ECASOLEILZMI4104CLIB_API const char* getZygoBoardRef();
	ECASOLEILZMI4104CLIB_API const char* getZygoFirmwareVersion();
	ECASOLEILZMI4104CLIB_API const char* getZygoSerialNumber();
	ECASOLEILZMI4104CLIB_API const char* getZygoBoardVersion();

	ECASOLEILZMI4104CLIB_API int setResetSourceClock(Axes axis, SCLK sclk);
	ECASOLEILZMI4104CLIB_API int getVMEBusSampleClk(Axes axis, SCLK& clk);
	ECASOLEILZMI4104CLIB_API int setVMEBusSampleClk(Axes axis, SCLK clk);
	ECASOLEILZMI4104CLIB_API int getResetSourceClock(Axes axis, SCLK& sclk);

	ECASOLEILZMI4104CLIB_API uint8_t getInterferometerConfiguration();
	ECASOLEILZMI4104CLIB_API int setInterferometerConfiguration(uint32_t config);

	ECASOLEILZMI4104CLIB_API bool getCachedCecState();
	ECASOLEILZMI4104CLIB_API int disableCecCompensation( Axes axis);
	ECASOLEILZMI4104CLIB_API int configureCecHardware(Axes axis, USHORT ceVelMin, USHORT ceVelMax);
	ECASOLEILZMI4104CLIB_API int readCecoefBoundaries(Axes axis, CECoeffBoundaries& CE0CoeffBound, CECoeffBoundaries& CENCoeffBound);
	ECASOLEILZMI4104CLIB_API int readCalcCecoeffs(Axes axis, CECoeffs& CECalcCoeffs);
	ECASOLEILZMI4104CLIB_API int enableCecCompensation(Axes axis);
	ECASOLEILZMI4104CLIB_API int calculateCeratio(Axes axis, CEratios& ceRatios, CEratioUnits units);
	ECASOLEILZMI4104CLIB_API int readCecErrorStatReg( Axes axis, uint32_t& CEstatReg);
	ECASOLEILZMI4104CLIB_API int getAproximateCeratio(Axes axis, CEratios& ceRatios, CEratioUnits units);
	ECASOLEILZMI4104CLIB_API int waitCeinit2Complete(Axes axis);
	ECASOLEILZMI4104CLIB_API int setCEMinVel(Axes axis, double CEMaxVelValue);
	ECASOLEILZMI4104CLIB_API int setCEMaxVel(Axes axis, double CEMinVelValue);
	ECASOLEILZMI4104CLIB_API int getCEMinVel(Axes axis, double& CEMaxVelValue);
	ECASOLEILZMI4104CLIB_API int getCEMaxVel(Axes axis, double& CEMinVelValue);
	ECASOLEILZMI4104CLIB_API int enableCeuserSuppliedCoefAtStartup(Axes axis);
	ECASOLEILZMI4104CLIB_API int disableCeuserSuppliedCoefAtStartup(Axes axis);
	ECASOLEILZMI4104CLIB_API int enableCeuserSuppliedCoef(Axes axis);
	ECASOLEILZMI4104CLIB_API int disableCeuserSuppliedCoef(Axes axis);
	ECASOLEILZMI4104CLIB_API int setUserSuppliedCoeffs(Axes axis, CECoeffs& coeffs);
	ECASOLEILZMI4104CLIB_API int getUserSuppliedCoeffs(Axes axis, CECoeffs& coeffs);
	ECASOLEILZMI4104CLIB_API int getCELimts(Axes axis, CECLimits& val);
	ECASOLEILZMI4104CLIB_API int setCE0Limit(Axes axis, double CEC0Limit);
	ECASOLEILZMI4104CLIB_API int setCENLimit(Axes axis, double CECNLimit);

	ECASOLEILZMI4104CLIB_API int getLedsStatus( bool* ledsStatus);
	ECASOLEILZMI4104CLIB_API int getLedsErrorStatus( bool* ledsErrorStatus);

	ECASOLEILZMI4104CLIB_API void setBaseAddress(uint32_t baseAddressAxis3);
	ECASOLEILZMI4104CLIB_API uint32_t getCachedBaseAddress();

	ECASOLEILZMI4104CLIB_API int createEvents();
	ECASOLEILZMI4104CLIB_API int  createThreads( );
	ECASOLEILZMI4104CLIB_API void closeThreads(void);

	ECASOLEILZMI4104CLIB_API int zygoLogFatal(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int zygoLogWarn(const char* fmt, ...);
	ECASOLEILZMI4104CLIB_API int zygoLogInfo(const char* fmt, ...);

	ECASOLEILZMI4104CLIB_API int getGainControlAgc(Axes axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int getGainMinControl(Axes axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int getGainMaxControl(Axes axis, bool* agcState);
	ECASOLEILZMI4104CLIB_API int setApdL2SigRmsMinLim(Axes axis, double minLim);
	ECASOLEILZMI4104CLIB_API int getApdL2SigRmsMinLim(Axes axis, double *minLim);
	ECASOLEILZMI4104CLIB_API int setApdL2SigRmsMaxLim(Axes axis, double maxLim);
	ECASOLEILZMI4104CLIB_API int getApdL2SigRmsMaxLim(Axes axis, double *maxLim);

	ECASOLEILZMI4104CLIB_API SCLK getCachedSampleSclk();
	ECASOLEILZMI4104CLIB_API SCLK getCachedResetSclk();

	ECASOLEILZMI4104CLIB_API int readWrite(const char* ch_access_mode, uint32_t uint_vme_address, uint32_t* uint_vme_data,
		uint16_t read_write);
	ECASOLEILZMI4104CLIB_API int eepromRead(uint16_t offset, uint32_t* uint_vme_data,uint16_t nBytes);

	ECASOLEILZMI4104CLIB_API int readSamplePosition32(Axes axis, double* position);
	ECASOLEILZMI4104CLIB_API int readSamplePosition37(Axes axis, double* position);
	ECASOLEILZMI4104CLIB_API int readPosition(Axes axis, double* position);
	ECASOLEILZMI4104CLIB_API int readPositionForAllAxis(double* position);
	ECASOLEILZMI4104CLIB_API int readFifoPosition(Axes axis, uint32_t* position);
	ECASOLEILZMI4104CLIB_API int sampleVmePosition(Axes axis);
	ECASOLEILZMI4104CLIB_API int setPositionOffset32(Axes axis, double* offsetPos);
	ECASOLEILZMI4104CLIB_API int setPositionOffset37(Axes axis, double* offsetPos);
	ECASOLEILZMI4104CLIB_API int setPositionOffset(Axes axis, double* offsetPos);
	ECASOLEILZMI4104CLIB_API int getPositionOffset(Axes axis, double* offsetPos);
	ECASOLEILZMI4104CLIB_API int setPresetPosition32(Axes axis, double *presetPos);
	ECASOLEILZMI4104CLIB_API int setPresetPosition37(Axes axis, double *presetPos);
	ECASOLEILZMI4104CLIB_API int setPresetPosition(Axes axis, double *presetPos);
	ECASOLEILZMI4104CLIB_API int getPresetPosition(Axes axis, double* offsetPos);
	ECASOLEILZMI4104CLIB_API bool isVmePos32Overflow(Axes axis);
	ECASOLEILZMI4104CLIB_API int setHoldSampEnable(Axes axis);

	ECASOLEILZMI4104CLIB_API int enable32BitsOverflow(Axes axis);
	ECASOLEILZMI4104CLIB_API int disable32BitsOverflow(Axes axis);

	ECASOLEILZMI4104CLIB_API int enable37BitsSignExtension(Axes axis);
	ECASOLEILZMI4104CLIB_API int disable37bitsSignExtension(Axes axis);

	ECASOLEILZMI4104CLIB_API int readTime(Axes axis, double* time);
	ECASOLEILZMI4104CLIB_API int readTimeForAllAxis(double* time);

	ECASOLEILZMI4104CLIB_API int readVelocity(Axes axis, double* velocity);
	ECASOLEILZMI4104CLIB_API int readVelocityForAllAxis(double* velocity);

	ECASOLEILZMI4104CLIB_API int readOpticalPowerUsingSsiAv(Axes axis, double* opticalPower);
	ECASOLEILZMI4104CLIB_API int readOpticalPowerUsingSsiAvForAllAxis(double* opticalPower);
	ECASOLEILZMI4104CLIB_API int readSsiAv(Axes axis, double* ssi);
	ECASOLEILZMI4104CLIB_API int readSsiAvForAllAxis(double* ssi);
	ECASOLEILZMI4104CLIB_API int readScaledSsiAv(Axes axis, double* ssiPtr);
	ECASOLEILZMI4104CLIB_API int readScaledSsiAvForAllAxis(double* ssiPtr);
	ECASOLEILZMI4104CLIB_API int readSsiCalibrationData(Axes axis, double* SSIVals, double* OptPwrVals);
	ECASOLEILZMI4104CLIB_API int readOptPwrDC(Axes axis, double& OptPwrDC_L2);
	ECASOLEILZMI4104CLIB_API int readOptPwrDCForAllAxis(std::array<double, 4>& OptPwrDC);
	/*
	ECASOLEILZMI4104CLIB_API int readMixingFrequency(Axes axis, double& mxFreq);
	ECASOLEILZMI4104CLIB_API int readMixingFrequencyForAllAxis(std::array<double, 4>& mxFreq);
	*/
	ECASOLEILZMI4104CLIB_API int readApdGain(Axes axis, double*apdGain);
	ECASOLEILZMI4104CLIB_API int readApdGainForAllAxis(double* apdGain);
	ECASOLEILZMI4104CLIB_API int readApdTemp(Axes axis, double* APD_Temp);

	ECASOLEILZMI4104CLIB_API int setSsiSquelch(Axes axis, uint32_t squelchValue);
	ECASOLEILZMI4104CLIB_API int getSsiSquelch(Axes axis, uint32_t* squelchValue);

	ECASOLEILZMI4104CLIB_API int readGseData(Axes axis, double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC);
	ECASOLEILZMI4104CLIB_API int readGseDataForAllAxis(double* gseTargetGain, double* gseActualGain, double* gseSigRMS, double* gseMeasDC);

	ECASOLEILZMI4104CLIB_API int setApdBiasVoltage(Axes axis, double ApdBiasVoltage_mV);
	ECASOLEILZMI4104CLIB_API int getApdBiasVoltage(Axes axis, double* ApdBiasVoltage_mV);

	ECASOLEILZMI4104CLIB_API int setApdL2GainSet(Axes axis, double);
	ECASOLEILZMI4104CLIB_API int getApdL2GainSet(Axes axis, double* APDGainL2);

	ECASOLEILZMI4104CLIB_API int setApdL2OptPwrSet(Axes axis, double APDOptPwrL2);
	ECASOLEILZMI4104CLIB_API int getApdL2OptPwrSet(Axes axis, double* APDOptPwrL2);

	ECASOLEILZMI4104CLIB_API int setApdL2SigRmsSet(Axes axis, double APDSigRMSL2);
	ECASOLEILZMI4104CLIB_API int getApdL2SigRmsSet(Axes axis, double* APDSigRMSL2);

	ECASOLEILZMI4104CLIB_API int enableAuxRegisters(Axes axis);
	ECASOLEILZMI4104CLIB_API int disableAuxRegisters(Axes axis);

	ECASOLEILZMI4104CLIB_API int sclkOutputOn(Axes axis, SCLK clk);
	ECASOLEILZMI4104CLIB_API int sclkOutputOff(Axes axis, SCLK clk);
	ECASOLEILZMI4104CLIB_API uint32_t getCachedSamplingFrequency();
	ECASOLEILZMI4104CLIB_API int setSamplingFrequency(Axes axis, uint32_t sampleFreq, SCLK clk);
	ECASOLEILZMI4104CLIB_API int getSamplingFrequency(Axes axis, uint32_t* sampFreq);
	ECASOLEILZMI4104CLIB_API int enableSampling(Axes axis, uint32_t freq, SCLK clk);
	ECASOLEILZMI4104CLIB_API int disableSampleTimer(Axes axis, SCLK clk);
	ECASOLEILZMI4104CLIB_API int setSampTimerFreq(Axes axis, uint16_t sampTimerVal, SCLK clk);
	ECASOLEILZMI4104CLIB_API int getVmeExtSampFlag(Axes axis, int* sampleFlag);

	ECASOLEILZMI4104CLIB_API int resetHoldSampEnable(Axes axis);
	ECASOLEILZMI4104CLIB_API int enableResetFindsVelocity(Axes axis);
	ECASOLEILZMI4104CLIB_API int enableResetFindsVelocityForAllAxis();
	ECASOLEILZMI4104CLIB_API int disableResetFindsVelocity(Axes axis);
	ECASOLEILZMI4104CLIB_API int disableResetFindsVelocityForAllAxis();

	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus2(Axes axis, uint32_t* vmeErrorStatus2);
	ECASOLEILZMI4104CLIB_API int parseVmePosErrs(Axes axis, uint32_t* vmePosErrs);
	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus1(Axes axis, uint32_t* vmeErrorStatus1);
	ECASOLEILZMI4104CLIB_API int parseVmeErrorStatus0(Axes axis, uint32_t* vmeErrorStatus0);
	ECASOLEILZMI4104CLIB_API int parseApdErrCode(Axes axis, uint32_t* apdErrCode);
	ECASOLEILZMI4104CLIB_API int readCecErrorStatReg(Axes axis, uint32_t* CEstatReg);
	ECASOLEILZMI4104CLIB_API int readVmeErrs(Axes axis);
	ECASOLEILZMI4104CLIB_API int readApdCtrlSoftErrs(Axes axis);
	ECASOLEILZMI4104CLIB_API int readAllErrs(Axes axis);
	ECASOLEILZMI4104CLIB_API int checkLimits(int num2check, int minVal, int maxVal);

	ECASOLEILZMI4104CLIB_API int configureFlyscan(uint8_t axis, double, uint8_t);
	ECASOLEILZMI4104CLIB_API int deconfigureFlycsan(uint8_t axesNbr);
	ECASOLEILZMI4104CLIB_API int startAquisition(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int stopAquisition(uint8_t axis);
	ECASOLEILZMI4104CLIB_API int getFlyscanData(uint32_t*, uint32_t*, uint32_t*, uint32_t ramPagesNbr);
	ECASOLEILZMI4104CLIB_API int processRamData(uint32_t, uint32_t*, uint32_t*, uint32_t ramPagesNbr, char* folderName, double* meanVal, double* stdDevVal);

	ECASOLEILZMI4104CLIB_API int configureFifoFlyscan(fifoParam& fifoparameters, uint32_t* startAdress, uint8_t* axisTab, uint32_t* sizeOfTab, int32_t* ret_code, bool mode);
	ECASOLEILZMI4104CLIB_API int fifoFlyscan(fifoParam param, uint32_t* startAddress, uint8_t nbrAxis, int32_t* ret_code, ...);
	ECASOLEILZMI4104CLIB_API int manualFifoFlyscan(fifoParam &param, uint32_t* startAddress, uint8_t nbrAxis, int32_t* ret_code, ...);
	ECASOLEILZMI4104CLIB_API int processFifoData(uint32_t nbrAxis, uint8_t* axisTab, uint32_t* memPtr, uint32_t nbrOfPts, const char* folderName, double* meanVal, double* stdDevVal);
	ECASOLEILZMI4104CLIB_API bool isFifoDavBitSet(Axes axis);
	ECASOLEILZMI4104CLIB_API bool isFifoOvfBitSet(Axes axis);
	ECASOLEILZMI4104CLIB_API bool isRamBusy();

	ECASOLEILZMI4104CLIB_API int setGainControlAgc(Axes axis);
	ECASOLEILZMI4104CLIB_API int resetGainControlAgc(Axes axis);
	ECASOLEILZMI4104CLIB_API int setGainMinControl(Axes axis);
	ECASOLEILZMI4104CLIB_API int resetGainMinControl(Axes axis);
	ECASOLEILZMI4104CLIB_API int setGainMaxControl(Axes axis);
	ECASOLEILZMI4104CLIB_API int resetGainMaxControl(Axes axis);
	ECASOLEILZMI4104CLIB_API int readScaledSsiAv(double* ssiPtr);

	ECASOLEILZMI4104CLIB_API int convertFloat2Decimal(uint32_t floatNbr, double* doubleVal);
	ECASOLEILZMI4104CLIB_API int convertUsfloat2Double(uint16_t USFloatNbr, double* doubleVal);


	ECASOLEILZMI4104CLIB_API int enableVmeInterruptBit(Axes axis, uint16_t intNumber);
	ECASOLEILZMI4104CLIB_API int disableVmeInterruptBit(Axes axis, uint16_t intNumber);
	ECASOLEILZMI4104CLIB_API int enableVmeGlobalInterrupt(Axes axis);
	ECASOLEILZMI4104CLIB_API int disableGlobalInterrupt(Axes axis);
	ECASOLEILZMI4104CLIB_API int disableAllVmeInterrupts(Axes axis);
	ECASOLEILZMI4104CLIB_API int enableAllVmeInterrupts(Axes axis);
	ECASOLEILZMI4104CLIB_API int enableVmeGlobalInterrupt(Axes axis);
	ECASOLEILZMI4104CLIB_API int setVmeIntVector(Axes axis, uint8_t IntVect);
	ECASOLEILZMI4104CLIB_API int setVmeIntLevel(Axes axis, uint8_t IntVect);
	ECASOLEILZMI4104CLIB_API int ackForSis3100VmeIrq(uint32_t);

	ECASOLEILZMI4104CLIB_API int setKpAndKvCoeff(Axes axis, int Kp, int Kv);
	ECASOLEILZMI4104CLIB_API int getKpAndKvCoeff(Axes axis, int* coeff);

	ECASOLEILZMI4104CLIB_API int configureSerialBus(Axes axis, SCLK clk, SerialOutputDriver sdo, SerialDataPositionSize sdps, BitWindow bw, uint32_t sampFreq);
	ECASOLEILZMI4104CLIB_API int startSerialBus(Axes axis);
	ECASOLEILZMI4104CLIB_API int stopSerialBus(Axes axis);
	ECASOLEILZMI4104CLIB_API int getSerialBusState(Axes axis, State& s);
	ECASOLEILZMI4104CLIB_API int setSerialBusSampleClk(Axes axis, SCLK clk);
	ECASOLEILZMI4104CLIB_API int p2BusClkDriver(Axes axis, SCLK clk);
	ECASOLEILZMI4104CLIB_API int clearP2BusOutputDriver(Axes axis);
	ECASOLEILZMI4104CLIB_API int setSerialBusOutputDriver(Axes axis, SerialOutputDriver sdo);
	ECASOLEILZMI4104CLIB_API int setSerialBusDataPositionSize(Axes axis, SerialDataPositionSize sdps);
	ECASOLEILZMI4104CLIB_API int setP2BusBitWindow(Axes axis, BitWindow bw);
	ECASOLEILZMI4104CLIB_API int enableSCLKDivideBy2(Axes axis);
	ECASOLEILZMI4104CLIB_API int enableSCLKDivider(Axes axis);
	ECASOLEILZMI4104CLIB_API int setSCLKDividerCoeff(Axes axis, SampleDividerCoeffs sdv);
	ECASOLEILZMI4104CLIB_API int disableSCLKDivideBy2(Axes axis);
	ECASOLEILZMI4104CLIB_API int disableSCLKDivider(Axes axis);
	ECASOLEILZMI4104CLIB_API int getSCLKDivideBy2(Axes axis, State& s);
	ECASOLEILZMI4104CLIB_API int getSCLKDividerState(Axes axis, State& s);


	ECASOLEILZMI4104CLIB_API int convertComplex2Uint(std::complex<double> nbr, uint32_t& val);
	ECASOLEILZMI4104CLIB_API int convertDouble2Float(double doubleNbr, uint32_t* floatVal);
	ECASOLEILZMI4104CLIB_API int convertCint16ToComplex(uint32_t, std::complex<double>&);
	ECASOLEILZMI4104CLIB_API int convertCfloat2Complex(uint32_t, std::complex<double>&);

