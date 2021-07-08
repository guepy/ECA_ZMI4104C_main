#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "zVME_const.h"
#include "wingetopt.h" 
#include "sis3100_vme_calls.h"
#include "sis1100w.h"
#include "sis3302.h"
#include "sis3100.h"
#include "vmeInterruptConst.h"
#pragma comment (lib, "sis1100w.lib")
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
#define LOG_FILE_PATH						"C:\\Users\\guekam\\source\\repos\\ECA_ZMI4104_Project\\ECA_ZMI4104C_main\\LogFiles\\"
#define POSITION_FILE_PATH					"C:\\Users\\guekam\\source\\repos\\ECA_ZMI4104_Project\\ECA_ZMI4104C_main\\data\\"
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
#define FATAL(errmsg, ...) do{											\
handle_err(EXIT_FAILLURE, "FATAL:%s:%s:%d: " errmsg, __FILE__,__FUNCTION__, __LINE__, __VA_ARGS__); \
}while(0)
#define WARN(errmsg, ...) do{											\
handle_err(NON_FATAL, "WARNING:%s:%s:%d: " errmsg, __FILE__,__FUNCTION__, __LINE__, __VA_ARGS__); \
return RET_FAILED;}while(0)
#define INFO(errmsg, ...) do{											\
handle_err(INFO_PURPOSE, "INFO: " errmsg, __VA_ARGS__); \
}while(0)
// get SIS3104 base address as argument at the process startup
#define SIS3104_BASE_ADDRESS				0x0

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
	double acqTime; // ACQUISITION TIME in seconds
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
	SCLK0=0, 
	SCLK1 = 1
}sclk;
typedef enum _InterferoConfig {
	SGLE = 1,
	DBLE = 2,
}InterferoConfig;
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
const char* const biasControlModeString[BIAS_CTRL_MODE_NBR] = {
	"BIAS_OFF_MODE",
	"BIAS_CONSTANT_VOLTAGE_MODE",
	"BIAS_CONSTANT_GAIN_MODE",
	"BIAS_ACONSTANT_OPTICAL_POWER_MODE",
	"BIAS_SIG_RMS_ADJUST_MODE",
};

SIS1100W_STATUS stat;
SIS1100_Device_Struct dev;

unsigned int	BASE_ADDRESS[] = { 0x4000, 0x5000, 0x6000, 0x7000 }, // Base adresses 
return_code = 0,
comp_err = 0,
valid_flag = 0,
NbrBdAx = 0;
//uint32_t sis_irq_array[16]; // 16 IRQs
uint32_t vme_irq_level = 0, vme_irq_vector = 0;
uint8_t read_irq_vector = 0;

unsigned short	IntVector[] = { 0x101, 0, 0x202, 0 },
SCLKDrive = 2,
Direction[] = { 0, 0, 0, 0 };

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


double	SSICalMin[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} },    //( (Ax1SSI,Ax1uW),(Ax2SSI,Ax2uW), etc) 
SSICalNom[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} },
SSICalMax[4][2] = { {1, 1}, {1, 1}, {1, 1}, {1, 1} },     //1 all by default to prevent /0
SSICalValues[4][2] = { {1, 1}, {1, 1}, {1, 1}, {1, 1} },  //( (Ax1m,Ax1b),(Ax2m,Ax2b), etc) 
SSIsquelch[] = { 1, 1, 1, 1 },								//Squelch with default values in uW
SSIMax[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} },    //( (Ax1SSIMax,Ax1MaxuW),(Ax2MaxSSI,Ax2MaxuW), etc)
SSIMin[4][2] = { {0, 0}, {0, 0}, {0, 0}, {0, 0} },    //( (Ax1SSIMin,Ax1MinuW),(Ax2SSIMin,Ax2MinuW), etc)
positionScale = DOUBLE_PASS_INT_POS_COEF,    //Converts to mm as default
velocityScale = DOUBLE_PASS_INT_VEL_COEF * (1e-3),      //Converts to mm/s
OpticalPower_uW[] = { 0, 0, 0, 0 };

bool	enableResetFindsVelocity[] = { false, false, false, false },
ZMIError[] = { false, false, false, false, false },  //Extra ZMIError is for reference
signal[] = { false, false, false, false, false }, //Extra signal is for ref
testMode[] = { false, false, false, false }; //Extra signal is for ref

// ZMI Scalars
const double	timeScale = 25 * (1e-9),                   //Converts to s as default				
TACI_Spacing_small = 7.19 * (1e-3),
TACI_Spacing_large = (7.19 * 2) * (1e-3);
int handle_err(int fatal, const char* fmt, ...);
int convertUSFloat2Double(USHORT, double*);
int calculateCEratio(SIS1100_Device_Struct*, unsigned char, CEratios*, CEratioUnits); 
int configureCEChardware(SIS1100_Device_Struct*, UCHAR, USHORT, USHORT);
int readCEerrorStatReg(SIS1100_Device_Struct* dev, unsigned char axis, PUINT CEstatReg);
int getAproximateCEratio(SIS1100_Device_Struct*, unsigned char, CEratios*, CEratioUnits );
int Read_Write(char*, SIS1100_Device_Struct*, unsigned int, unsigned int*, unsigned short);
int ReadVMEErrs(SIS1100_Device_Struct*, unsigned char);
int InitAxis(SIS1100_Device_Struct*, BIAS_MODE);
int Init_SIS_boards(SIS1100_Device_Struct*);
int Init_ZMI_bd(SIS1100_Device_Struct*);
int ReadSamplePosition37(SIS1100_Device_Struct*, unsigned char, double*);
int ReadSamplePosition32(SIS1100_Device_Struct*, unsigned char, double*);
int ReadSamplePosition37_ForAllAxis(SIS1100_Device_Struct*, double*);
int ReadSamplePosition32_ForAllAxis(SIS1100_Device_Struct*, double*);
int ReadPosition37(SIS1100_Device_Struct*, unsigned char, double*);
int ReadPosition32(SIS1100_Device_Struct*, unsigned char, double*);
int ReadFIFOPosition(SIS1100_Device_Struct*, unsigned char, PUINT position);
int ReadVelocity32(SIS1100_Device_Struct*, unsigned char, double*);
int ReadPosition37_ForAllAxis(SIS1100_Device_Struct*, double*);
int ReadPosition32_ForAllAxis(SIS1100_Device_Struct*, double*);
int ReadVelocity32_ForAllAxis(SIS1100_Device_Struct*, double*);
int ReadTime32(SIS1100_Device_Struct*, unsigned char, double*);
int ReadTime32_ForAllAxis(SIS1100_Device_Struct*, double*);
int ReadAllTime32(SIS1100_Device_Struct*, double*);
int ReadOpticalPowerUsingSSIav(SIS1100_Device_Struct*);
int ReadAPDGain(SIS1100_Device_Struct*, unsigned char, double*);
int EnableAuxRegisters(SIS1100_Device_Struct*, unsigned char);
int DisableAuxRegisters(SIS1100_Device_Struct*, unsigned char);
int Disable37bitsSignExtension(SIS1100_Device_Struct*, unsigned char);
int Sclk_On(SIS1100_Device_Struct*);
int Sclk_Off(SIS1100_Device_Struct*);
int SetSampTimerFreq(SIS1100_Device_Struct*, unsigned short);
int SetHoldSampEnable(SIS1100_Device_Struct*);
int ResetHoldSampEnable(SIS1100_Device_Struct*);
int enableSampling(SIS1100_Device_Struct*, double);
int DisableSampleTimer(SIS1100_Device_Struct*);
int VMESysReset(SIS1100_Device_Struct*);
int startAquisition(SIS1100_Device_Struct*, unsigned char);
int stopAquisition(SIS1100_Device_Struct*, unsigned char);
bool GetVMEExtSampFlag(SIS1100_Device_Struct*, unsigned char);
int Disable32bitsOverflow(SIS1100_Device_Struct*, unsigned char);
int Enable32bitsOverflow(SIS1100_Device_Struct*, unsigned char);
int Enable37bitsSignExtension(SIS1100_Device_Struct*, unsigned char);
int EnableSinglePassInterferometer(void);
int EnableDoublePassInterferometer(void);
int ReadAPDGain_ForAllAxis(SIS1100_Device_Struct*, double*);
int SampleVMEPosition(SIS1100_Device_Struct*, unsigned char);
int ParseVMEErrorStatus2(SIS1100_Device_Struct*, unsigned char, unsigned int*);
int ParseVMEPosErrs(SIS1100_Device_Struct*, unsigned char, unsigned int*);
int ParseVMEErrorStatus1(SIS1100_Device_Struct*, unsigned char, unsigned int*);
int ParseVMEErrorStatus0(SIS1100_Device_Struct*, unsigned char, unsigned int*);
int ParseAPDErrCode(SIS1100_Device_Struct*, unsigned char, unsigned int*);
int BoardControlMode(SIS1100_Device_Struct*, unsigned char, unsigned int);
int BiasControlMode(SIS1100_Device_Struct*, unsigned char, unsigned int);
int StartBiasCalculation(SIS1100_Device_Struct*, unsigned char);
int SetAPDGainL2(SIS1100_Device_Struct*, unsigned char, unsigned int);
int checkValues(UINT, UINT, UINT);
int ClearAllVMEErrs_ForAllAxis(SIS1100_Device_Struct*);
BOOL isRAMbusy(SIS1100_Device_Struct*);
int SetAPDSigRMSL2(SIS1100_Device_Struct*, unsigned char, unsigned int);
int SetAPDOptPwrL2(SIS1100_Device_Struct*, unsigned char, unsigned int);
int ResetAxis(SIS1100_Device_Struct*, unsigned char);
int WaitResetComplete(SIS1100_Device_Struct*, unsigned char);
int SetPositionOffset32(SIS1100_Device_Struct*, unsigned char, unsigned int);
int EnableCECcompensation(SIS1100_Device_Struct* , unsigned char );
int SetPositionOffset37(SIS1100_Device_Struct*, unsigned char, unsigned int, unsigned int);
int EnableVMEInterrupt_bit(SIS1100_Device_Struct*, unsigned char, unsigned short);
int DisableVMEInterrupt_bit(SIS1100_Device_Struct*, unsigned char, unsigned short);
int EnableVMEGlobalInterrupt(SIS1100_Device_Struct*, unsigned char);
int DisableGlobalInterrupt(SIS1100_Device_Struct*, unsigned char);
int DisableAllVMEInterrupts(SIS1100_Device_Struct*, unsigned char);
int SetKpAndKvCoeff(SIS1100_Device_Struct*, unsigned char, unsigned short, unsigned short);
int ReadAPDCtrlSoftErrs(SIS1100_Device_Struct*, unsigned char);
int ReadAllErrs(SIS1100_Device_Struct*, unsigned char);
int SetTimeDelayBetweenResAndCompleteBit(SIS1100_Device_Struct*, unsigned char, unsigned char);
int EnableAllVMEInterrupts(SIS1100_Device_Struct*, unsigned char);
int EnableVMEGlobalInterrupt(SIS1100_Device_Struct*, unsigned char);
int setVMEIntVector(SIS1100_Device_Struct*, unsigned char, unsigned char);
int setVMEIntLevel(SIS1100_Device_Struct*, unsigned char, unsigned char);
int sis3301w_Init(SIS1100_Device_Struct*, uint32_t, uint32_t, uint32_t);
int	AckForSis3100VME_Irq(SIS1100_Device_Struct*, uint32_t);
int getFlyscanData(SIS1100_Device_Struct*, PUINT, PUINT, PUINT);
PUINT allocateMemSpace(UINT);
int processRAMData(UINT, PUINT, PUINT);
int processFifoData(UINT nbrAxis, PUCHAR axisTab, PUINT memPtr, UINT nbrOfPts);
int configureFifoFlyscan(SIS1100_Device_Struct*, fifoParam*, PUINT, PUCHAR, PUCHAR );
int fifoFlyscan(SIS1100_Device_Struct*, fifoParam, PUINT, UCHAR, ...);
bool isFifoDavbitSet(SIS1100_Device_Struct*, unsigned char);
bool isFifoOVFbitSet(SIS1100_Device_Struct*, unsigned char);
int configureFlyscan(SIS1100_Device_Struct*, unsigned char, double, UCHAR);
int convertCInt162Complex(UINT, complex*);
int convertCFloat2Complex(UINT, complex*);
int waitCEinit2Complete(SIS1100_Device_Struct*, unsigned char);
int SetCEMaxVel(SIS1100_Device_Struct*, unsigned char, unsigned int);
int SetCEMinVel(SIS1100_Device_Struct*, unsigned char , unsigned int);
int readCalcCECoeffs(SIS1100_Device_Struct*, unsigned char, CECoeffs*);
int readCECoeffboundaries(SIS1100_Device_Struct*, unsigned char, CECoeffBoundaries*, CECoeffBoundaries*);
int calculateCEratio(SIS1100_Device_Struct* dev, unsigned char axis, CEratios* ceRatios, CEratioUnits units);
int EEPROMread(SIS1100_Device_Struct*, unsigned short, unsigned int*, unsigned short);
int convertFloat2Double(UINT, double*);

#define THREADCOUNT 4 
#define coeff_a   6.049264479990438e-8
#define coeff_b   -1.351195412225471e-6
#define coeff_c   -0.002995301725927718
#define coeff_d   0.4474028058422057
#define coeff_f   -9.023933972316671
