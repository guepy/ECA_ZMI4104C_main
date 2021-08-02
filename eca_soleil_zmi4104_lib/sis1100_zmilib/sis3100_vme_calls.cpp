/***************************************************************************/
/*                                                                         */
/*  Filename: sis3100_vme_calls.c                                          */
/*                                                                         */
/*  Funktion: sis1100/sis310x C library                                    */
/*                                                                         */
/*  Autor:                TH                                               */
/*  date:                 10.05.2002                                       */
/*  last modification:    28.09.2020                                       */
/*                                                                         */
/*  17.08.2009:                                                            */
/*  new: #define SIS3104_VERSION1                                          */
/*  reason: SIS3104 Version 1 was not compatible with SIS3100              */
/*  modified: vme_A24DMA_D16_write, vme_A24DMA_D16FIFO_write,              */
/*            vme_A24DMA_D16_write, vme_A24DMA_D16FIFO_write               */
/*                                                                         */
/*  28.09.2020:                                                            */
/*  add: #define CRCSR calls                                               */
/*                                                                         */
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
/*  © 2020                                                                 */
/*                                                                         */
/***************************************************************************/

/*---------------------------------------------------------------------------*/
/* Include files                                                             */
/*---------------------------------------------------------------------------*/
#include "pch.h"
#include "sis3100_vme_calls.h"
#include "sis1100w.h"

	typedef unsigned char           uint8_t;
	typedef unsigned short          uint16_t;
	typedef unsigned int            uint32_t;
	typedef signed int	            int32_t;

	/**********************/
	/*                    */
	/*    VME SYSReset    */
	/*                    */
	/**********************/
	int vmesysreset(
		struct SIS1100_Device_Struct* pDevice
	)
	{
		sis1100w_VmeSysreset(pDevice);
		return 0;
	}


	/**********************************/
	/*                                */
	/*    VME Interrupt Acknowledge   */
	/*                                */
	/**********************************/

	int vme_IACK_D8_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_irq_level,
		uint8_t* vme_data
	)
	{
		int return_code;
		unsigned int data;

		return_code = sis1100w_Vme_Single_Read(pDevice, (vme_irq_level << 1) + 1, 0x4000, 1, &data);
		*vme_data = (uint8_t)data;
		return return_code;
	}

	/*****************/
	/*               */
	/*    VME CRCSR  */
	/*               */
	/*****************/

	int vme_CRCSR_D8_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint8_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x2F, 1, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint8_t)readdata;
		return return_code;
	}


	int vme_CRCSR_D16_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x2F, 2, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint16_t)readdata;
		return return_code;
	}


	/* VME CRCSR  Write Cycles */

	int vme_CRCSR_D8_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint8_t vme_data
	)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x2F, 1, data_32);
		return return_code;
	}


	int vme_CRCSR_D16_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t vme_data
	)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x2F, 2, data_32);
		return return_code;
	}



	/*****************/
	/*               */
	/*    VME A16    */
	/*               */
	/*****************/

	/* VME A16  Read Cycles */

	int vme_A16D8_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint8_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x29, 1, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint8_t)readdata;
		return return_code;
	}


	int vme_A16D16_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x29, 2, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint16_t)readdata;
		return return_code;
	}


	/* VME A16  Write Cycles */

	int vme_A16D8_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint8_t vme_data
	)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x29, 1, data_32);
		return return_code;
	}


	int vme_A16D16_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t vme_data
	)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x29, 2, data_32);
		return return_code;
	}


	/*****************/
	/*               */
	/*    VME A24    */
	/*               */
	/*****************/

	/* VME A24  Read Cycles */

	int vme_A24D8_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint8_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x39, 1, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint8_t)readdata;
		return return_code;
	}


	int vme_A24D16_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x39, 2, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint16_t)readdata;
		return return_code;
	}



	int vme_A24D16P_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x3D, 2, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint16_t)readdata;
		return return_code;
	}



#ifdef not_tested
	int vme_A24BLT16_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_lwords,
		uint32_t* got_num_of_lwords
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_lwords * sizeof(uint32_t));
		if (buf == NULL) {
			free(buf);
			return -1;
		}

		return_code = sis1100w_Vme_Dma_Read(pDevice, vme_adr, 0x3b, 2, 0, buf, req_num_of_lwords, got_num_of_lwords);
		if (return_code)
			return return_code;

		for (i = 0; i < req_num_of_lwords; i++) {
			vme_data[i] = (uint16_t)buf[i];
		}
		free(buf);
		return return_code;
	}
#endif

	int vme_A24DMA_D16_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint32_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		return_code = sis1100w_Vme_Dma_Read(pDevice, vme_adr, 0x39, 2, 0, buf, req_num_of_words, got_num_of_words);
		if (return_code) {
			free(buf);
			return return_code;
		}
		//printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*******-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		for (i = 0; i < req_num_of_words; i++) {
			//printf("Writing %x to memory case 0x%p\n", vme_data[i], vme_data + i);
			*vme_data++ = buf[i];
		}
		//printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*******-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		free(buf);
		return return_code;
	}

	int vme_A24DMA_D32_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint32_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;
		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		return_code = sis1100w_Vme_Dma_Read(pDevice, vme_adr, 0x39, 4, 0, buf, req_num_of_words, got_num_of_words);
		if (return_code) {
			free(buf);
			return return_code;
		}
		//printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*******-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		for (i = 0; i < req_num_of_words; i++) {
			//printf("Writing %x to memory case 0x%p\n", vme_data[i], vme_data + i);
			vme_data[i] = buf[i];
		}
		printf("End Address 0x%p\n", vme_data + i - 1);
		printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*******-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		free(buf);
		return return_code;
	}

	int vme_A24DMA_D16FIFO_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		return_code = sis1100w_Vme_Dma_Read(pDevice, vme_adr, 0x39, 2, 1, buf, req_num_of_words, got_num_of_words);
		if (return_code) {
			free(buf);
			return return_code;
		}

		for (i = 0; i < req_num_of_words; i++) {
			vme_data[i] = (uint16_t)buf[i];
		}
		free(buf);
		return return_code;
	}




	/* VME A24  Write Cycles */

	int vme_A24D8_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint8_t vme_data
	)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x39, 1, data_32);
		return return_code;
	}


	int vme_A24D16_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t vme_data)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x39, 2, data_32);
		return return_code;
	}

	int vme_A24D16P_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t vme_data)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x3D, 2, data_32);
		return return_code;
	}


#ifdef not_tested
	int vme_A24BLT16_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_lwords,
		uint32_t* got_num_of_lwords
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_lwords * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		for (i = 0; i < req_num_of_lwords; i++) {
			buf[i] = (uint32_t)vme_data[i];
		}

		return_code = sis1100w_Vme_Dma_Write(pDevice, vme_adr, 0x3b, 2, 0, buf, req_num_of_lwords, got_num_of_lwords);

		free(buf);
		return return_code;
	}
#endif



	int vme_A24DMA_D16_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		for (i = 0; i < req_num_of_words; i++) {
#ifdef SIS3104_VERSION1
			buf[i] = (uint32_t)vme_data[i];
#else
			buf[i] = (((uint32_t)vme_data[i]) & 0xffff) + ((((uint32_t)vme_data[i]) & 0xffff) << 16); // new with SIS3104 version2 (2009-08-17)
#endif
		}

		return_code = sis1100w_Vme_Dma_Write(pDevice, vme_adr, 0x39, 2, 0, buf, req_num_of_words, got_num_of_words);

		free(buf);
		return return_code;
	}

	int vme_A24DMA_D16FIFO_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{

		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		for (i = 0; i < req_num_of_words; i++) {
#ifdef SIS3104_VERSION1
			buf[i] = (uint32_t)vme_data[i];
#else
			buf[i] = (((uint32_t)vme_data[i]) & 0xffff) + ((((uint32_t)vme_data[i]) & 0xffff) << 16); // new with SIS3104 version2 (2009-08-17)
#endif
		}

		return_code = sis1100w_Vme_Dma_Write(pDevice, vme_adr, 0x39, 2, 1, buf, req_num_of_words, got_num_of_words);

		free(buf);
		return return_code;
	}







	/*****************/
	/*               */
	/*    VME A32    */
	/*               */
	/*****************/

	/* VME A32  Read Cycles */

	int vme_A32D8_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint8_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x9, 1, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint8_t)readdata;
		return return_code;
	}

	int vme_A32D16_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data
	)
	{
		unsigned int readdata;
		int return_code;
		return_code = sis1100w_Vme_Single_Read(pDevice, vme_adr, 0x9, 2, &readdata);
		if (return_code < 0)
			return return_code;
		*vme_data = (uint16_t)readdata;
		return return_code;
	}



#ifdef not_tested
	int vme_A32BLT16_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_lwords,
		uint32_t* got_num_of_lwords
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_lwords * sizeof(uint32_t));
		if (buf == NULL) {
			free(buf);
			return -1;
		}

		return_code = sis1100w_Vme_Dma_Read(pDevice, vme_adr, 0xb, 2, 0, buf, req_num_of_lwords, got_num_of_lwords);
		if (return_code)
			return return_code;

		for (i = 0; i < req_num_of_lwords; i++) {
			vme_data[i] = (uint16_t)buf[i];
		}
		*got_num_of_lwords >>= 1;
		free(buf);
		return return_code;
	}
#endif



	int vme_A32DMA_D16_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		return_code = sis1100w_Vme_Dma_Read(pDevice, vme_adr, 0x9, 2, 0, buf, req_num_of_words, got_num_of_words);
		if (return_code) {
			free(buf);
			return return_code;
		}

		for (i = 0; i < req_num_of_words; i++) {
			vme_data[i] = (uint16_t)(buf[i] & 0xffff);
		}
		free(buf);
		return return_code;
	}


	int vme_A32DMA_D16FIFO_read(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		return_code = sis1100w_Vme_Dma_Read(pDevice, vme_adr, 0x9, 2, 1, buf, req_num_of_words, got_num_of_words);
		if (return_code) {
			free(buf);
			return return_code;
		}

		for (i = 0; i < req_num_of_words; i++) {
			vme_data[i] = (uint16_t)buf[i];
		}
		free(buf);
		return return_code;
	}


	/* VME A32  Write Cycles */

	int vme_A32D8_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint8_t vme_data
	)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x9, 1, data_32);
		return return_code;
	}


	int vme_A32D16_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t vme_data
	)
	{
		uint32_t data_32;
		int return_code;
		data_32 = (uint32_t)vme_data;
		return_code = sis1100w_Vme_Single_Write(pDevice, vme_adr, 0x9, 2, data_32);
		return return_code;
	}


#ifdef not_tested
	int vme_A32BLT16_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;
		unsigned int req_num_of_lwords;
		//unsigned int got_num_of_lwords;

		req_num_of_lwords = 2 * req_num_of_words;
		buf = (uint32_t*)malloc(req_num_of_lwords * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		for (i = 0; i < req_num_of_lwords; i++) {
			buf[i] = (uint32_t)vme_data[i];
		}

		return_code = sis1100w_Vme_Dma_Write(pDevice, vme_adr, 0xb, 2, 0, buf, req_num_of_lwords, &got_num_of_words);

		free(buf);
		return return_code;
	}
#endif



	int vme_A32DMA_D16_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{
		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		for (i = 0; i < req_num_of_words; i++) {
#ifdef SIS3104_VERSION1
			buf[i] = (uint32_t)vme_data[i];
#else
			buf[i] = (((uint32_t)vme_data[i]) & 0xffff) + ((((uint32_t)vme_data[i]) & 0xffff) << 16); // new with SIS3104 version2 (2009-08-17)
#endif
		}

		return_code = sis1100w_Vme_Dma_Write(pDevice, vme_adr, 0x9, 2, 0, buf, req_num_of_words, got_num_of_words);

		free(buf);
		return return_code;
	}

	int vme_A32DMA_D16FIFO_write(
		struct SIS1100_Device_Struct* pDevice,
		uint32_t vme_adr,
		uint16_t* vme_data,
		uint32_t req_num_of_words,
		uint32_t* got_num_of_words
	)
	{

		uint32_t* buf;
		int return_code;
		unsigned int i;

		buf = (uint32_t*)malloc(req_num_of_words * sizeof(uint32_t));
		if (buf == NULL)
			return -1;

		for (i = 0; i < req_num_of_words; i++) {

#ifdef SIS3104_VERSION1
			buf[i] = (uint32_t)vme_data[i];
#else
			buf[i] = (((uint32_t)vme_data[i]) & 0xffff) + ((((uint32_t)vme_data[i]) & 0xffff) << 16); // new with SIS3104 version2 (2009-08-17)
#endif
		}

		return_code = sis1100w_Vme_Dma_Write(pDevice, vme_adr, 0x9, 2, 1, buf, req_num_of_words, got_num_of_words);

		free(buf);
		return return_code;
	}




	/***********************/
	/*                     */
	/*    s3100_sharc      */
	/*                     */
	/***********************/

	int s3100_sharc_write(
		struct SIS1100_Device_Struct* p_sharc_desc,
		uint32_t byte_adr,
		uint32_t* ptr_data,
		uint32_t num_of_lwords
	)
	{
		int return_code = 0;
		unsigned int put_num_of_lwords;
		unsigned int i, j;

		if (num_of_lwords <= 0x0)
			return 0;

		if (num_of_lwords <= 0x4) {
			j = 0;
			for (i = 0; i < num_of_lwords; i++) {
				return_code = sis1100w_SdramSharc_Single_Write(p_sharc_desc, byte_adr + j, ptr_data[i]);
				j = j + 4;
				if (return_code != 0)
					return -1;
			}
			return j;
		}
		else {
			return_code = sis1100w_SdramSharc_Dma_Write(p_sharc_desc, byte_adr, ptr_data, num_of_lwords, &put_num_of_lwords);
			if (return_code != 0)
				return -1;
			return (int)(put_num_of_lwords << 2);
		}
		return 0;
	}

	int s3100_sharc_read(
		struct SIS1100_Device_Struct* p_sharc_desc,
		uint32_t byte_adr,
		uint32_t* ptr_data,
		uint32_t num_of_lwords
	)
	{
		int return_code;
		unsigned int got_num_of_lwords;
		unsigned int i, j;

		if (num_of_lwords <= 0x0)
			return 0;

		if (num_of_lwords <= 0x4) {
			j = 0;
			for (i = 0; i < num_of_lwords; i++) {
				return_code = sis1100w_SdramSharc_Single_Read(p_sharc_desc, byte_adr + j, &ptr_data[i]);
				j = j + 4;
				if (return_code != 0)
					return -1;
			}
			return j;
		}
		else {
			return_code = sis1100w_SdramSharc_Dma_Read(p_sharc_desc, byte_adr, ptr_data, num_of_lwords, &got_num_of_lwords);
			if (return_code != 0)
				return -1;
			return (int)(got_num_of_lwords << 2);
		}
		return 0;
	}

	/***********************/
	/*                     */
	/*    s3100_sdram      */
	/*                     */
	/***********************/

	int s3100_sdram_write(
		struct SIS1100_Device_Struct* p_sdram_desc,
		uint32_t byte_adr,
		uint32_t* ptr_data,
		uint32_t num_of_lwords
	)
	{
		int return_code = 0;
		unsigned int put_num_of_lwords;
		unsigned int i, j;

		if (num_of_lwords <= 0x0)
			return 0;

		if (num_of_lwords <= 0x4) {
			j = 0;
			for (i = 0; i < num_of_lwords; i++) {
				return_code = sis1100w_SdramSharc_Single_Write(p_sdram_desc, byte_adr + j, ptr_data[i]);
				j = j + 4;
				if (return_code != 0)
					return -1;
			}
			return j;
		}
		else {
			return_code = sis1100w_SdramSharc_Dma_Write(p_sdram_desc, byte_adr, ptr_data, num_of_lwords, &put_num_of_lwords);
			if (return_code != 0)
				return -1;
			return (int)(put_num_of_lwords << 2);
		}
		return 0;
	}

	int s3100_sdram_read(
		struct SIS1100_Device_Struct* p_sdram_desc,
		uint32_t byte_adr,
		uint32_t* ptr_data,
		uint32_t num_of_lwords
	)
	{
		int return_code;
		unsigned int got_num_of_lwords;
		unsigned int i, j;

		if (num_of_lwords <= 0)
			return 0;
		if (num_of_lwords <= 0x4) {
			j = 0;
			for (i = 0; i < num_of_lwords; i++) {
				return_code = sis1100w_SdramSharc_Single_Read(p_sdram_desc, byte_adr + j, &ptr_data[i]);
				j = j + 4;
				if (return_code != 0)
					return -1;
			}
			return j;
		}
		else {
			return_code = sis1100w_SdramSharc_Dma_Read(p_sdram_desc, byte_adr, ptr_data, num_of_lwords, &got_num_of_lwords);
			if (return_code != 0)
				return -1;
			return (int)(got_num_of_lwords << 2);
		}
		return 0;
	}
