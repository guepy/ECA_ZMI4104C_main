/***************************************************************************/
/*                                                                         */
/*  Filename: sis5100_camac_calls.c                                        */
/*                                                                         */
/*  Funktion:                                                              */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 25.02.2004                                       */
/*  last modification:    06.11.2008 - TF                                  */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*                                                                         */
/*  SIS  Struck Innovative Systeme GmbH                                    */
/*                                                                         */
/*  Harksheider Str. 102A                                                  */
/*  22399 Hamburg                                                          */
/*                                                                         */
/*  Tel. +49 (0)40 60 87 305 0                                             */
/*  Fax  +49 (0)40 60 87 305 20                                            */
/*                                                                         */
/*  http://www.struck.de                                                   */
/*                                                                         */
/*  © 2004 - 2008                                                          */
/*                                                                         */
/***************************************************************************/

/*---------------------------------------------------------------------------*/
/* Include files                                                             */
/*---------------------------------------------------------------------------*/

#include <stdio.h>


#include "sis1100w.h" // Header sis1100w.dll

/* typedef unsigned char           u_int8_t;	 */
/* typedef unsigned short          u_int16_t;	 */
typedef unsigned long           u_int32_t;

/* CAMAC  Read Cycles */

int camac_read(struct SIS1100_Device_Struct* pDevice, u_int32_t N, u_int32_t A, u_int32_t F, u_int32_t* camac_data )
{
  unsigned int readdata, camac_addr ;
  int return_code ;
  if (F >= 16) return 0x2216 ;
  camac_addr  =  ((F & 0x1f) << 11) + ((N & 0x1f) << 6) +((A & 0xf) << 2) ; 
  return_code = sis1100w_Vme_Single_Read(pDevice, camac_addr, /* AM */ 0x0, 4,  &readdata) ;
  *camac_data = readdata; 
  if (return_code != 0)  return return_code ; 
  return_code = ((readdata >> 24) & 0xC0);
  if (return_code != 0) return_code = return_code + 0x200;
  return return_code ;
}

int camac_dma_read(struct SIS1100_Device_Struct* pDevice, u_int32_t N, u_int32_t A, u_int32_t F, u_int32_t* camac_data, 
                      u_int32_t req_num_of_lwords, u_int32_t* got_num_of_lwords)
{
  int return_code ;
  unsigned int camac_addr ;
	if (F >= 16) return 0x2216 ;
  	camac_addr  =  ((F & 0x1f) << 11) + ((N & 0x1f) << 6) +((A & 0xf) << 2) ; 
	return_code = sis1100w_Vme_Dma_Read(pDevice, camac_addr, /* AM */ 0x0, 4, 0,camac_data, req_num_of_lwords, got_num_of_lwords);
	return return_code ;
}

int camac_write(struct SIS1100_Device_Struct* pDevice, u_int32_t N, u_int32_t A, u_int32_t F, u_int32_t camac_data )
{
  unsigned int camac_addr ;
  int return_code ;
  if (F <= 15) return 0x2200 ;
  camac_addr  =  ((F & 0x1f) << 11) + ((N & 0x1f) << 6) +((A & 0xf) << 2) ; 
  return_code = sis1100w_Vme_Single_Write(pDevice, camac_addr, /* AM */ 0x0, 4, camac_data) ;
  return return_code ;
}

int camac_dma_write(struct SIS1100_Device_Struct* pDevice, u_int32_t N, u_int32_t A, u_int32_t F, u_int32_t* camac_data, 
                      u_int32_t req_num_of_lwords, u_int32_t* got_num_of_lwords)
{
  int return_code ;
  unsigned int camac_addr ;
  if (F <= 15) return 0x2200 ;
  	camac_addr  =  ((F & 0x1f) << 11) + ((N & 0x1f) << 6) +((A & 0xf) << 2) ; 
	return_code = sis1100w_Vme_Dma_Write(pDevice, camac_addr, /* AM */ 0x0, 4, 0,camac_data, req_num_of_lwords, got_num_of_lwords);
	return return_code ;
}

/***********************/
/*                     */
/*    s5100_control    */
/*                     */
/***********************/

int s5100_control_read(struct SIS1100_Device_Struct* p, int offset, u_int32_t* data)
{
int error ;
	error = sis1100w_sis3100_Control_Read(p, offset, data) ;
  	return error ;
}

int s5100_control_write(struct SIS1100_Device_Struct* p, int offset, u_int32_t data)
{
int error ;
	error = sis1100w_sis3100_Control_Write(p, offset, data) ;
  	return error ;
}
