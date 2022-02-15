/**
* Filename: sis1100wType.h
*
* Function:
*
* Main SIS1100 Windows API types
*
* Author:				TH, TF
* Date:					2010
* Last modification:	17.01.2018
*
* ---------------------------------------------
*
* SIS  Struck Innovative Systeme GmbH
*
* Harksheider Str. 102A
* 22399 Hamburg
*
* Tel. +49 (0)40 60 87 305 0
* Fax  +49 (0)40 60 87 305 20
*
* http://www.struck.de
*
* © 2018
*/
#ifndef SIS1100WTYPE_H_
#define SIS1100WTYPE_H_

// device handle struct
typedef struct SIS1100_Device_Struct {
	PVOID plx_Va;
	PVOID plx_map_Va;
	PVOID devObj;
	PVOID cBuf;
	UINT32 fw;
}SIS1100_Device_Struct;

// api revision information struct
typedef struct _SIS1100W_VERSION {
	UCHAR SisMajor;
	UCHAR SisMinor;
	UCHAR PlxMajor;
	UCHAR PlxMinor;
} SIS1100W_VERSION, *PSIS1100W_VERSION;

// IRQ mask bits
typedef enum _SIS1100W_IRQ {
	IRQ_SIS3100_FLAT1 = 0x1,
	IRQ_SIS3104_NIM1  = 0x1,
	IRQ_SIS3100_FLAT2 = 0x2,
	IRQ_SIS3104_NIM2  = 0x2,
	IRQ_SIS3100_FLAT3 = 0x4,
	IRQ_SIS3104_TTL1  = 0x4,
	IRQ_SIS3100_FLAT4 = 0x8,
	IRQ_SIS3104_TTL2  = 0x8,
	IRQ_SIS3100_LEMO1 = 0x10,
	IRQ_SIS3100_LEMO2 = 0x20,
	IRQ_SIS3100_LEMO3 = 0x40,
	IRQ_SIS3100_DSP   = 0x80,
	IRQ_SIS310X_VME1  = 0x100,
	IRQ_SIS310X_VME2  = 0x200,
	IRQ_SIS310X_VME3  = 0x400,
	IRQ_SIS310X_VME4  = 0x800,
	IRQ_SIS310X_VME5  = 0x1000,
	IRQ_SIS310X_VME6  = 0x2000,
	IRQ_SIS310X_VME7  = 0x4000
} SIS1100_IRQ;

#endif
