#pragma once
#define INT_LEVEL0							0		// Interrupt level 0
#define INT_LEVEL1							1		// Interrupt level 1
#define INT_LEVEL2							2		// Interrupt level 2
#define INT_LEVEL3							3		// Interrupt level 3
#define INT_LEVEL4							4		// Interrupt level 4
#define INT_LEVEL5							5		// Interrupt level 5
#define INT_LEVEL6							6		// Interrupt level 6
#define INT_LEVEL7							7		// Interrupt level 7

#define CEC_ERR_INT							0		// CEC Error interrupt bit
#define PHASE_NOISE_ERR_INT					1		// PHASE NOISE Error interrupt bit
#define ACCELERATION_ERR_INT				2		// Acceleration Error interrupt bit
#define MEAS_SIG_GLITCH_ERR_INT				3		// Measure signal glitch Error interrupt bit
#define MEAS_SIG_DROP_ERR_INT				4		// Measre signal drop Error interrupt bit
#define SSI_MAX_LIM_ERR_INT					5		// SSI Max Limit Error interrupt bit
#define MEAS_SIG_SAT_ERR_INT				6		// Measured signal saturation Error interrupt bit
#define MEAS_SIG_MIS_ERR_INT				7		// Measured signal missing Error interrupt bit
#define OV_TMP_ERR_INT						8		// Overflow temperature Error interrupt bit
#define FPGA_SYNC_ERR_INT					9		// FPGA synchronisation Error interrupt bit
#define RES_FAIL_ERR_INT					10		// Reset failed Error interrupt bit
#define RES_COMP_ERR_INT					11		// Reset comparator Error interrupt bit
#define REF_PLL_ERR_INT						12		// Reference PLL Error interrupt bit
#define REF_SIG_MIS_ERR_INT					13		// Reference Signal Missing Error interrupt bit
#define WRT_ERR_INT							14		// Write error interrupt bit
#define PWR_ERR_INT							15		// Power Error interrupt bit
#define VME_EXT_FLAG_SAMPLE_ERR_INT			16		// VME external flag sample Error interrupt bit
#define P32_POS_OV_ERR_INT					17		// P32 position overflow Error interrupt bit
#define VME32_POS_OV_ERR_INT				18		// VME32 position overflow Error interrupt bit
#define VME37_POS_OV_ERR_INT				19		// VME37 position overflow Error interrupt bit
#define USR_VEL_ERR_INT						20		// User velocity Error interrupt bit
#define VEL_ERR_INT							21		// Velocity Error interrupt bit
#define PROC_INIT_BSY_ERR_INT				22		// Process initialisation busy Error interrupt bit
#define PROC_FAIL_ERR_INT					23		// Process Failed Error interrupt bit
#define BIAS_SUPPLY_ERR_INT					24		// Bias supply Error interrupt bit
#define WRT_PROTECT_ERR_INT					25		// Write Protect Error interrupt bit
#define SIG_MAX_ERR_INT						26		// maximum SSI signal reached Error interrupt bit
#define SIG_MIN_ERR_INT						27		// minimum SSI signal reached Error interrupt bit
#define BIAS_CALC_COMP_INT					28		// Bias calculation complete interrupt bit
#define BIAS_ERR_INT						29		// Bias error Error interrupt bit
#define APD_DC_ERR_INT						30		// APD Gain DC  Error interrupt bit
#define BIAS_SET_ERR_INT					31		// Bias set Error interrupt bit
#define APD_FAIL_ERR_INT					32		// APD calculation failed Error interrupt bit
#define APD_TMP_ERR_INT						33		// APD temperature setup failed Error interrupt bit

#define MIN_INT_NBR							0		// value the smallest interrupt number
#define MAX_INT_NBR							33		// value the Highest interrupt number
#define THREADCOUNT							4 


HANDLE vmeIrq6Event, lemoIN1Event;
HANDLE  hThreadArray[THREADCOUNT];
HANDLE vmeIntThread, lemoIN1Thread, fastReadThread, WaitForSis3100IrqThread, WaitForVmeIrqThread;
DWORD WINAPI vmeIntThreadFunc(LPVOID);

DWORD WINAPI lemoIN1ThreadFunc(LPVOID);
DWORD WINAPI readThreadFunc(LPVOID);
DWORD WINAPI fastReadThreadFunc(LPVOID);
DWORD WINAPI WaitForVmeIrqThreadFunc(LPVOID);
DWORD WINAPI WaitForSis3100IrqThreadFunc(LPVOID);

static UINT sisIrqMask = DOORBELL_DSP_IRQ |
DOORBELL_LEMO_IN1_IRQ |
DOORBELL_LEMO_IN2_IRQ |
DOORBELL_LEMO_IN3_IRQ |
DOORBELL_FLAT_IN4_IRQ |
DOORBELL_FLAT_IN3_IRQ |
DOORBELL_FLAT_IN2_IRQ |
DOORBELL_FLAT_IN1_IRQ;
static UINT vmeIrqMask =
DOORBELL_VME_IRQ1 |
DOORBELL_VME_IRQ2 |
DOORBELL_VME_IRQ3 |
DOORBELL_VME_IRQ4 |
DOORBELL_VME_IRQ5 |
DOORBELL_VME_IRQ6;

static int irq;//previously volatile
static DWORD dwWaitResult;
static HANDLE ghMutex;
static struct sis1100_irq_ctl irqctl;
static struct sis1100_irq_get irqget;
static struct sis1100_irq_ack irqack;
//uint32_t sis_irq_array[16]; // 16 IRQs
static uint32_t vme_irq_level = 0, IntVector[] = { 0x101, 0, 0x202, 0 }, vme_irq_vector = 0;
static uint8_t read_irq_vector = 0;
