/**
* Filename: sis1100w.h
*
* Function:
*
* Main SIS1100 Windows API header
*
* Author:				TH, TF
* Date:					2010
* Last modification:	17.01.2017
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
* � 2018
*/

#ifdef SIS1100W_EXPORTS
#define SIS1100W_API __declspec(dllexport)
#else
#define SIS1100W_API __declspec(dllimport)
#endif

#include <windows.h>

#include "sis1100wStat.h"
#include "sis1100wType.h"


struct sis1100_irq_ack {
    UINT irq_mask;
};
struct sis1100_irq_get {
    UINT irq_mask;      /* IRQs for which information is requested */
    INT   remote_status; /* -1: down 1: up 0: unchanged */
    UINT opt_status;    /* content of opt. status register of sis1100 */
    UINT mbx0;          /* content of mailbox 0 of PLX */
    UINT irqs;          /* pending IRQs */
    INT   level;         /* highest level of pendig VME IRQs */
    INT   vector;        /* corresponding IRQ vector */
};
struct sis1100_ctrl_rw {
    UINT offset;
    UINT fifo;
    UINT count;
    UINT* data;
    UINT error;
};

struct sis1100_irq_ctl {
    UINT irq_mask;
    HANDLE   event;  /* >0: signal; ==0: disable; <0: no signal but select */
};

#ifdef __cplusplus
extern "C"{
#endif

// Logging
SIS1100W_API SIS1100W_STATUS sis1100w_Logging( BOOLEAN enable );

// Version Information
SIS1100W_API SIS1100W_STATUS sis1100w_Api_Version( PSIS1100W_VERSION version );

// Extended Error handling
SIS1100W_API SIS1100W_STATUS sis1100w_Get_Last_Plx_Error( int *err );

// Device handling
SIS1100W_API SIS1100W_STATUS sis1100w_Find_No_Of_sis1100( UINT *no_found );
SIS1100W_API SIS1100W_STATUS sis1100w_Get_Handle_And_Open( UINT deviceNo, struct SIS1100_Device_Struct *handle );
SIS1100W_API SIS1100W_STATUS sis1100w_Close( struct SIS1100_Device_Struct *handle );
SIS1100W_API SIS1100W_STATUS sis1100w_Init( struct SIS1100_Device_Struct *handle, UINT dummy );
SIS1100W_API SIS1100W_STATUS sis1100w_Get_IdentVersion( struct SIS1100_Device_Struct *handle, UINT *ident );

// Remote Device handling
SIS1100W_API SIS1100W_STATUS sis1100w_Init_sis3100( struct SIS1100_Device_Struct *handle, UINT dummy );
SIS1100W_API SIS1100W_STATUS sis1100w_VmeSysreset( struct SIS1100_Device_Struct *handle );

// Local control access
SIS1100W_API SIS1100W_STATUS sis1100w_sis1100_Control_Read( struct SIS1100_Device_Struct *handle, UINT offset, UINT *data );
SIS1100W_API SIS1100W_STATUS sis1100w_sis1100_Control_Write( struct SIS1100_Device_Struct *handle, UINT offset, UINT data );

// Remote control access
SIS1100W_API SIS1100W_STATUS sis1100w_sis3100_Control_Read( struct SIS1100_Device_Struct *handle, UINT offset, UINT *data );
SIS1100W_API SIS1100W_STATUS sis1100w_sis3100_Control_Write( struct SIS1100_Device_Struct *handle, UINT offset, UINT data );

// Vme single cycle access
SIS1100W_API SIS1100W_STATUS sis1100w_Vme_Single_Read( struct SIS1100_Device_Struct *handle, UINT addr, UINT am, UINT size, UINT *data );
SIS1100W_API SIS1100W_STATUS sis1100w_Vme_Single_Write( struct SIS1100_Device_Struct *handle, UINT addr, UINT am, UINT size, UINT data );

// Vme block access
SIS1100W_API SIS1100W_STATUS sis1100w_Vme_Dma_Read(	struct SIS1100_Device_Struct *handle, UINT addr, UINT am, UINT size, UINT fifo_mode, UINT *dmabufs, UINT req_num_data, UINT *got_num_data );
SIS1100W_API SIS1100W_STATUS sis1100w_Vme_Dma_Write( struct SIS1100_Device_Struct *handle, UINT addr, UINT am, UINT size, UINT fifo_mode, UINT *dmabufs, UINT req_num_data, UINT *put_num_data );

// Remote Sharc access
SIS1100W_API SIS1100W_STATUS sis1100w_SdramSharc_Single_Read( struct SIS1100_Device_Struct *handle, UINT addr, UINT *data );
SIS1100W_API SIS1100W_STATUS sis1100w_SdramSharc_Single_Write( struct SIS1100_Device_Struct *handle, UINT addr, UINT data );

// Remote Sharc block access
SIS1100W_API SIS1100W_STATUS sis1100w_SdramSharc_Dma_Read( struct SIS1100_Device_Struct *handle, UINT addr, UINT *dmabufs, UINT req_num_data, UINT *got_num_data );
SIS1100W_API SIS1100W_STATUS sis1100w_SdramSharc_Dma_Write( struct SIS1100_Device_Struct *handle, UINT addr, UINT *dmabufs, UINT req_num_data, UINT *put_num_data );

// IRQ access
SIS1100W_API SIS1100W_STATUS sis1100w_sis310x_Register_For_Irq( struct SIS1100_Device_Struct *handle, UINT mask );
SIS1100W_API SIS1100W_STATUS sis1100w_sis310x_Unregister_From_Irq( struct SIS1100_Device_Struct *handle, UINT mask );
SIS1100W_API SIS1100W_STATUS sis1100w_sis310x_Wait_For_Irq( struct SIS1100_Device_Struct *handle, DWORD msec, PUINT mask );

// VME mapping
SIS1100W_API SIS1100W_STATUS sis1100w_vme_map( struct SIS1100_Device_Struct *handle, UINT *param, UINT count );
SIS1100W_API SIS1100W_STATUS sis1100w_vme_map_get_ptr( struct SIS1100_Device_Struct *handle, UINT **adr );
SIS1100W_API SIS1100W_STATUS sis1100w_vme_unmap( struct SIS1100_Device_Struct *handle, UINT count );

// Ringmode variants
// Local Ring control
SIS1100W_API SIS1100W_STATUS sis1100w_Init_Ring( struct SIS1100_Device_Struct *handle, UINT *slaveCount );
// Remote control access
SIS1100W_API SIS1100W_STATUS sis1100w_Remote_Control_Read_Ring( struct SIS1100_Device_Struct *handle, USHORT ringAdr, UINT addr, UINT *data );
SIS1100W_API SIS1100W_STATUS sis1100w_Remote_Control_Write_Ring( struct SIS1100_Device_Struct *handle, USHORT ringAdr, UINT addr, UINT data );

SIS1100W_API SIS1100W_STATUS sis1100w_Vme_Dma_Read_Ring( struct SIS1100_Device_Struct *handle, USHORT ringAdr, UINT addr, UINT am, UINT size, UINT fifo_mode, UINT *dmabufs, UINT req_num_data, UINT *got_num_data );
SIS1100W_API SIS1100W_STATUS sis1100w_Vme_Dma_Write_Ring( struct SIS1100_Device_Struct *handle, USHORT ringAdr, UINT addr, UINT am, UINT size, UINT fifo_mode, UINT *dmabufs, UINT req_num_data, UINT *put_num_data );

#ifdef __cplusplus
}
#endif
