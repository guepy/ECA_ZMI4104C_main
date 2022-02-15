#pragma once

#define zCmd 0x00						// write only 
#define zStat0 0x00						// read only 
#define zSCLKCmd 0x02					// write only 
#define zStat1 0x02						// read only 
#define zVMEIntEnab0 0x04 
#define zVMEIntEnab1 0x06 
#define zVMEErrStat0 0x08				// read only 
#define zVMEErrClr0 0x08				// write only 
#define zVMEErrStat1 0x0A				// read only 
#define zVMEErrClr1 0x0A				// write only 
#define zVMEErrStat2 0x1E				// read only 
#define zVMEErrClr2 0x1E				// write only 
#define zFWVer 0x0E						// read only 
#define zCtrl0 0x10						// Control Register 0
#define zCtrl1 0x12						// Control Register 1
#define zCtrl2 0x14						// Control Register 2
#define zCtrl3 0x16						// Control Register 3
#define zCtrl4 0x18						// Control Register 4
#define zCtrl5 0x1A						// Control Register 5
#define zVMEIntEnab2 0x1C 
#define zP2IntEnab0 0x20 
#define zP2IntEnab1 0x22 
#define zAPDGainL2 0x1A2
#define zAPDSigRMSL2 0x190
#define zAPDOptPwrL2 0x18E
#define zAPDGainL2Set 0x18C 
#define zAPDBiasDAC 0x18C 
#define zP2ErrStat0 0xDE				// read only 
#define zP2ErrClr0 0x24					// write only 
#define zP2ErrStat1 0x26				// read only 
#define zP2ErrClr1 0x26					// write only 
#define zAbsPhase 0x28					// read only 
#define zSSIAvg 0x2A					// read only 
#define zSSIMax 0x2C					// read only 
#define zPhNoiseLim 0x2E 
#define zDataAgeAdj 0x30 
#define zUsrExcVel 0x32 
#define zSampleTimer 0x38 // axis 3 only 
#define zCtrl15 0x3A // axis 1, 3 only 
#define zCtrl16 0x3C // axis 1, 3 only 
#define zCtrl17 0x3E // axis 1, 3 only 
#define zVMEPosMSB 0x40 // read only 
#define zVMEFifoPos 0x80 // read only 
#define zVMEPosLSB 0x42 // read only 
#define zVMEPosExt 0x44 // read only 
#define zVMEPosErr 0x46 // read only 
#define zVMESampPosMSB 0x48 // read only 
#define zVMESampPosLSB 0x4A // read only 
#define zVMESampPosExt 0x4C // read only 
#define zVMESampPosErr 0x4E // read only 
#define zVMEVelocMSB 0x50 // read only 
#define zVMEVelocLSB 0x52 // read only 
#define zVMETimeMSB 0x54 // read only 
#define zVMETimeLSB 0x56 // read only 
#define zPresPosMSB 0x60 
#define zPresPosLSB 0x62 
#define zPresPosExt 0x64 
#define zOffsetMSB 0x68 
#define zOffsetLSB 0x6A 
#define zOffsetExt 0x6C 
#define zCompAMSB 0x70 
#define zCompALSB 0x72 
#define zCompAExt 0x74 
#define zCompBMSB 0x78 
#define zCompBLSB 0x7A 
#define zCompBExt 0x7C 
#define zSSISquelch 0x34 
#define zSoftErrID 0x1BA 
#define zTestStat1 0xA0 // read axis 1, 3 only 
#define zTestCmd1 0xA0 // write axis 1, 3 only 
#define zTestCtrl1 0xA2 // axis 1, 3 only 
#define zDiagTempCtrl				0xA4 // axis 1, 3 only 
#define zDiagTempWr					0xA6 // axis 1, 3 only 
#define zDiagTempRd					0xA8 // read axis 1, 3 only 
#define zDiagADCRd					0xAA // read axis 3 only 
#define zEEpromCtrl 0xAC // axis 3 only 
#define zEEpromWr 0xAE // axis 3 only 
#define zEEpromReadReg 0xB0 // read axis 3 only 
#define zIntVector 0xB2 // axis 1, 3 only 
#define zTestStat0 0xC0 // read only 
#define zTestCmd0 0xC0 // write only 
#define zTestCtrl0 0xC2 
#define zSSIDACTest 0xC6 
#define zFWRev 0xC8 // read only 
#define zRefID 0xCA // read axis 3 only 
#define zSwitches 0xCC // read only 
#define zDiagRAMStrt 0xCE // read only 
#define zQuickRstMSB 0xD0 // read only 
#define zQuickRstLSB 0xD2 // read only 
#define zQuickRstExt 0xD4 // read only 
#define zSSIOffset 0xD6 // read only 
#define zPhNoisePeak 0xD8 // read only 
#define zPhNoiseAvg 0xDA // read only 
#define zCEstat 0x100 // read only 
#define zCEcmd 0x100 // write only 
#define zCEerrorStat 0x108 // read only 
#define zCEMaxVel 0x10E // read/write 
#define zCEMinVel 0x10C // read/write 
#define zCEC0UserCoeff				0x124 // read/write 
#define zCEC1UserCoeff				0x11C // read/write 
#define zCECNUserCoeff				0x134 // read/write 
#define zCEC0CalcCoeff				0x120 // read
#define zCEC1CalcCoeff				0x118 // read
#define zCECNCalcCoeff				0x130 // read
#define zCE0Limit					0x128 // read/write
#define zCE0Mag						0x12A // read
#define zCE0Min						0x12C // read
#define zCE0Max						0x12E // read
#define zCENLimit					0x138 // read/write
#define zCENMag						0x13A // read
#define zCENMin						0x13C // read
#define zCENMax						0x13E // read
#define zDataAgeRam					0x100 // to 0x1FE /read
#define zDiagSSIRam					0x200 // to 0x3FE 
#define zDiagRamData				0x800 // to 0xFFE 
#define zCECCtl 0x102 // AUX register 
#define zOptPowerL2 0x192 // Optical Power L2 
#define zEEReadCmd		0x2000 
#define zAPDErr		0x18A 
#define zBdAxInf		0x15
#define ADD(base, offset) ((unsigned int )(base + offset)) 
#define SIS3100IntReg		0x104
#define zDiagFFTCtrl		0xB4
#define zDiagFFTRamData		0x400