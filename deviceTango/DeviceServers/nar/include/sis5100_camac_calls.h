/***************************************************************************/
/*                                                                         */
/*  Filename: sis5100_camac_calls.h                                        */
/*                                                                         */
/*  Funktion:                                                              */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 26.02.2004                                       */
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

typedef unsigned long u_int32_t;

int camac_read(struct SIS1100_Device_Struct* pDevice, u_int32_t N, u_int32_t A, u_int32_t F, u_int32_t* camac_data ) ;

int camac_dma_read(struct SIS1100_Device_Struct* pDevice, u_int32_t N, u_int32_t A, u_int32_t F, u_int32_t* camac_data, 
                      u_int32_t req_num_of_lwords, u_int32_t* got_num_of_lwords) ;


int camac_write(struct SIS1100_Device_Struct* pDevice, u_int32_t N, u_int32_t A, u_int32_t F, u_int32_t camac_data ) ;

int camac_dma_write(struct SIS1100_Device_Struct* pDevice, u_int32_t N, u_int32_t A, u_int32_t F, u_int32_t* camac_data, 
                      u_int32_t req_num_of_lwords, u_int32_t* got_num_of_lwords) ;


int s5100_control_read(struct SIS1100_Device_Struct* p, int offset, u_int32_t* data)   ;
int s5100_control_write(struct SIS1100_Device_Struct* p, int offset, u_int32_t data)   ;
