/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

#define SPI_FLASH_READ_REGION_OFFSET 0x0000
#define SPI_FLASH_ERASE_REGION_OFFSET 0x30000
#define SPI_FLASH_WRITE_REGION_OFFSET 0x3000
#define SPI_FLASH_SECTOR_SIZE 0x2000
#define SPI_PUBLICKEY_REGION_OFFSET   0xC00

#define EC_Register_Base_Address    0x00F00000
#define EC_SRAM_Base                0x80100000

//for sig hash mode
#define	SHA256_mode			0
#define	RSA_mode			1		//SHA256 + RSA
#define	ECDSA_mode			2		//SHA256 + ECDSA
#define Not_verify_sig  	3

#define DLM_Select(X)  X    //X * 0x400   

#define DLM_Sel_0			0x00		// 0x8010000 ~ 0x8010000
#define DLM_Sel_1			0x01		// 0x8010400 ~ 0x8010800
#define DLM_Sel_2			0x02		// 0x8010800 ~ 0x8010C00
#define DLM_Sel_3			0x03		// 0x8010C00 ~ 0x8011000
#define DLM_Sel_4			0x04		// 0x8011000 ~ 0x8011400

#define RSA_DLM					DLM_Sel_0	//DLM base address (need 4k alignment)
#define	SHA256_Length					0x20
#define SHA256_append_meg_addr_DLM_Sel	DLM_Sel_3	// 0x8010C00
#define SHA256_append_meg_addr			0x80100f00
#define RSA_Data_addr_DLM_Sel			DLM_Sel_1	// 0x8010400
#define	RSA_Result_offset				0x1F
#define UCODE0_start_addr	0x8000
#define UCODE1_start_addr	0x29000
#define UCODE0_size			0x20000
#define UCODE1_size			0x20000
#define Sig0_start_addr		0x28000
#define Sig1_start_addr		0x49000
#define SPI_BOOT_START_ADDR			0x0000000
#define SPI_USER0_START_ADDR		0x0008000
#define SPI_USER1_START_ADDR		0x0029000
#define SSPI_USER0_START_ADDR		0x1008000

//Select_path
enum 
{
	Select_EM,				// eflash
	Select_SPI,				// FSPI
	Select_fetch,			//
	Select_SSPI,			// SSPI
	Select_SSPI_PublicKey,	//
	Select_ESPI,			// ESPI
	Select_storage_END,	//
};

//Select_mode
enum
{
	SPI_Read,
	SPI_Program,
};

#define gu8SSPI0_Write_Buffer	SD_PTR_UCHAR_8(EC_SRAM_Base)		//[0x100];

#define Test			        SD_UCHAR_8(EC_SRAM_Base+0x1400)
#define TestAddress			    SD_ULONG_32(EC_SRAM_Base+0x1404)
#define M1K_DLM_SEL				SD_ULONG_32(EC_SRAM_Base+0x1410)
#define hash					SD_PTR_UCHAR_8(EC_SRAM_Base+0x1420)

uint8_t EC_INDIRECT_READ_FLASH;

uint8_t ReadBuffer[256];
/* function table define */

int OP_1K(uint32_t start_addr,uint8_t Sel_path,uint8_t size9_4,uint8_t Select_DLM ,uint8_t Sel_mode)
{

	uint32_t *Tmp_XPntr;
	uint16_t size;	
	//set DLM (buffer)
	Tmp_XPntr =(uint32_t *)(EC_SRAM_Base + Select_DLM*0x400);
	M1K_DLM_SEL = EC_SRAM_Base + Select_DLM*0x400;

    // get device
    const struct device *Fspi_dev = DEVICE_DT_GET(DT_NODELABEL(flashctrl));

	//check read size and read mode
	if ((size9_4 != 0x00) && (Sel_mode == SPI_Read))
	{
		size = (uint32_t)size9_4;
	}
	else	//always 1K szie for program/erase
	{
		size = 0x400;
	}

	if (Sel_mode == SPI_Read)	//for read use
	{
		if (Sel_path == Select_EM)
		{
            EC_INDIRECT_READ_FLASH = EC_INDIRECT_READ_INTERNAL_FLASH;
            flash_read(Fspi_dev, start_addr, Tmp_XPntr,size);
		}
		else if (Sel_path == Select_SPI)
		{
			EC_INDIRECT_READ_FLASH = EC_INDIRECT_READ_EXTERNAL_FLASH;
            flash_read(Fspi_dev, start_addr, Tmp_XPntr,size);
		}

	}
	else if (Sel_mode == SPI_Program) 	//for program use
	{
		if (Sel_path == Select_EM)
		{
            EC_INDIRECT_READ_FLASH = EC_INDIRECT_READ_INTERNAL_FLASH;
            flash_write(Fspi_dev, start_addr, Tmp_XPntr,size);						
		}
		else if (Sel_path == Select_SPI)
		{
            EC_INDIRECT_READ_FLASH = EC_INDIRECT_READ_EXTERNAL_FLASH;
            flash_write(Fspi_dev, start_addr, Tmp_XPntr,size);
		}
	}

	return	1;
}
void Set_SHA256_append_meg(uint32_t size)
{
	uint32_t i;

	for (i=0; i<0x400; i++)
	{
		ECREG(EC_SRAM_Base + (SHA256_append_meg_addr_DLM_Sel*0x400)+i) = 0;
	}
	
	ECREG(SHA256_append_meg_addr + 0x00) = 0x80;
	ECREG(SHA256_append_meg_addr + 0x3C) = ((size * 8) & 0xFF000000) >> 24;
	ECREG(SHA256_append_meg_addr + 0x3D) = ((size * 8) & 0x00FF0000) >> 16;
	ECREG(SHA256_append_meg_addr + 0x3E) = ((size * 8) & 0x0000FF00) >> 8;
	ECREG(SHA256_append_meg_addr + 0x3F) = ((size * 8) & 0x000000FF);
}
void SHA256_(uint32_t Start_Addr,uint32_t size,uint8_t S_path)
{
	//Start_Addr = 0;
	uint32_t i;
	uint32_t last_size = 0;
	uint32_t temp_addr=0;
	uint8_t Fast_block_flag = 1;

	for (i = 0; i < size ; i+=0x400)
	{
		//read data form Physical address , Data store to 0x800800
		ECREG(EC_Register_Base_Address+0x2046) &= 0xDF;    //after crtpyo finish , copy data
		if (S_path == Select_SSPI)
		{
			//SSPI_CMDQ_Dual_Read((Start_Addr+i), 0x400, DLM_Sel_2);				// Read SSPI to SRAM 0x80800
		}
		else
		{
			OP_1K((Start_Addr+i),S_path,0x00,DLM_Select(DLM_Sel_2),SPI_Read);//read data to DLM_Select(2)
		}
		ECREG(EC_Register_Base_Address+0x2046) |= 0x20;		//designer said for Crypto module use  
		//check size and init SHA256 module
		if ((size - i) >= 0x400)   //for 1k size
		{
			if (Fast_block_flag)
			{
				SHA256DBA1R = (M1K_DLM_SEL & 0x7F00) >> 8; //set SHA256DBA ,use 0x800800
				SHA256DBA0R = (M1K_DLM_SEL & 0xC0);
				SHA256ECR = load_1024bytes_into_SHA256_exe;//Calculate 1K range
				SHA256CR = SHA256INI+SHA256EXE;	//only first block need set SHA256INI bit
				Fast_block_flag = 0;
			}
			else
			{
				SHA256CR = SHA256EXE;	//only set SHA256EXE bit
			}

			while (SHA256SR & SHA256BUSY);

			SHA256SR = SHA256IS;
		}
		else
		{
			//data size small than 400h
			last_size = size - i;		//last block
			temp_addr = M1K_DLM_SEL;

			while (last_size > 0)
			{
				if (Fast_block_flag)
				{
					SHA256DBA1R = (temp_addr & 0x7F00) >> 8; //set SHA256DBA ,use 0x80800
					SHA256DBA0R = (temp_addr & 0xC0);
					SHA256ECR = load_512bit_into_SHA256_exe;//Calculate 64bytes range
					SHA256CR = SHA256INI+SHA256EXE;	//only first block need set SHA256INI bit
					Fast_block_flag = 0;
				}
				else
				{
					SHA256ECR = load_512bit_into_SHA256_exe; //Calculate 64bytes range
					SHA256CR = SHA256EXE;
				}

				while (SHA256SR & SHA256BUSY);

				SHA256SR = SHA256IS;
				last_size -= 0x40;
				temp_addr += 0x40;	//Calculate next 64bytes range
				SHA256DBA1R = (temp_addr & 0x7F00) >> 8; //set SHA256DBA ,next 64bytes range
				SHA256DBA0R = (temp_addr & 0xC0);
			}
		}
		ECREG(EC_Register_Base_Address+0x2046) &= 0xDF;    //after crtpyo finish , copy data
	}//exit for loop
    //Test = 0;
    //return;
	//M1KFLHCTRL3 = 0;
	//set appending message
	Set_SHA256_append_meg(size);
	ECREG(EC_Register_Base_Address+0x2046) |= 0x20;		//designer said for Crypto module use
	SHA256DBA1R = (SHA256_append_meg_addr & 0x7F00) >> 8; //set SHA256DBA
	SHA256DBA0R = (SHA256_append_meg_addr & 0xC0);
    //Test = 0;
    //return;
    //SHA256DBA1R = (SHA256_append_meg_addr_DLM_Sel * 0x04); //set SHA256DBA
	//SHA256DBA0R = 0;
	SHA256ECR = load_512bit_into_SHA256_exe; //select 512 bits for SHA-256
	SHA256CR = SHA256EXE;

	while (SHA256SR & SHA256BUSY);

	SHA256SR = SHA256IS;
	//SHA256DBA1R = 0x07; //set SHA256DBA , 0x80700
	//SHA256DBA1R = (DLM_Sel_8*0x4); //set SHA256DBA , 0x80700
	SHA256DBA1R = (DLM_Sel_3 * 0x04);
	SHA256DBA0R = 0;    //select DLM for write back data
	SHA256CR = SHA256WB;//write back

	while (SHA256SR & SHA256BUSY);

	SHA256SR = SHA256IS;
	
	ECREG(EC_Register_Base_Address+0x2046) &= 0xDF;    //after crtpyo finish , copy data
	
	WNCKR = 0x00;										// delay for copy correct value of hash
	WNCKR = 0x00;
	WNCKR = 0x00;
	
	for (i=0; i<0x20; i++)	//copy data to hash array
	{
		hash[i] = ECREG(EC_SRAM_Base + (DLM_Sel_3*0x400)+i);
	}

}
void RSA_main(uint32_t Start_Addr,uint8_t S_path)
{	
	uint16_t i;
	//const unsigned char *rsapublic = (const unsigned char*)(RSA_PUB_Key);
	//const unsigned char *rsapublic = (const unsigned char *)(0xE0C00);
	//printk("RSA_K %x %x %x %x\r\n",rsapublic[0],rsapublic[1],rsapublic[2],rsapublic[3]);

	ECREG(EC_Register_Base_Address+0x2046) &= 0xDF;		//after crtpyo finish , copy data
	
	if (S_path == Select_SSPI)
	{
		//========================================================================
		// Read Public key and Signature from SPI flash Start
		//M1KFLHCTRL3 = M1KPHY;
		//read Public	@ 0x80000
		//SSPI_CMDQ_Dual_Read(Start_Addr, 0x400, RSA_Data_addr_DLM_Sel);		// Read Public key
	}
	// Read Public key and Signature from SPI flash End
	else
	{
		//========================================================================
		// Read Public key and Signature from e-falsh and SPI flash Start
		// Signature and Public Key @eflash
		// Key_Start_Addr+0x000 is Signature , Key_Start_Addr+0x100 is PublicKey
		//M1KFLHCTRL3 = M1KPHY;
		OP_1K(Start_Addr,S_path,0x00,DLM_Select(RSA_Data_addr_DLM_Sel),SPI_Read);
	}

	for (i=0x100; i<0x400; i++)
	{
		ECREG(M1K_DLM_SEL+i) = 0x00;
	}

	for (i=0; i<0x100; i++) // Copy Public key
	{
		//printk("%2X ",RSA_PUB_Key[i]);
		//ECReg((EC_SRAM_Base+DLM_Select(RSA_DLM)*0x400)+i) = rsapublic[i];
        OP_1K(SPI_PUBLICKEY_REGION_OFFSET,S_path,0x00,DLM_Select(RSA_DLM),SPI_Read);
	}

	for (i=0x100; i<0x400; i++) // Copy Public key
	{
		//printk("%2X ",RSA_PUB_Key[i]);
		ECREG((EC_SRAM_Base+DLM_Select(RSA_DLM)*0x400)+i) = 0x00;
	}

	ECREG(EC_Register_Base_Address+0x2046) |= 0x20;		//designer said for Crypto module use

	//Tony_stop(0x60);	//debug for check data
	//set RSA Enable
	RSACR = RSAE;
	//set RSA public Modulus Length
	RSAC2R = RSA_Lenght_2048;
	//exponent 65535
	RSACR &= 0xCF;
	//set DLM base for RSA
	//	RSABAB1 = (RSA_DLM & 0x000) >> 8 ; 	//set 0x82000
	RSABAB1 = ((RSA_DLM*0x04) & 0x30); 	//set 0x8010000
	//enable RSA clk
	RSACR |= RSACE;
	//start RSA calculation
	RSASR = RSACS;

	while (!(RSASR & RSACD));

	RSASR = RSACD;	//write 1 clear
	RSACR &= ~(RSACE);	//disable RSA
	RSACR = RSAReset;
	// Tony_stop(0x61);
	
	ECREG(EC_Register_Base_Address+0x2046) &= 0xDF;		//after crtpyo finish , copy data
}
int Compare(uint32_t Start_Addr,uint8_t compare_size,uint8_t mode)
{
	uint8_t i = 0;

	if ((mode &0x03) ==  RSA_mode)
	{
		while (i < compare_size)
		{
			if (hash[i] != ECREG(Start_Addr-i))
			{
				DPRINTK(1,"hash compare error!!0x%2X\n\r",hash[i]);
				DPRINTK(1,"ECReg compare error!!0x%2X\n\r",ECREG(Start_Addr-i));
				return	0;
			}

			i++;
		}
	}
	else if ((mode &0x03) ==  SHA256_mode)
	{
		while (i < compare_size)
		{
			if (hash[i] != ECREG(Start_Addr+i))
			{
				return	0;
			}

			i++;
		}
	}

	DPRINTK(1,"hash compare ok\n\r");
	return 1;
}
int Sig_hash_Verify(uint32_t Start_Addr,uint32_t Key_Start_Addr,uint32_t size,uint8_t S_path,uint8_t mode, uint8_t Verify_Hash)
{
	DPRINTK(1,"hash verify Start_Addr:%X\r\n",Start_Addr);
	DPRINTK(1,"mode:%X\r\n",mode);
	DPRINTK(1,"Key_Start_Addr:%X\r\n",Key_Start_Addr);
	DPRINTK(1,"Size:%X\r\n",size);
	DPRINTK(1,"S_path:%X\r\n",S_path);
	DPRINTK(1,"Verify_Hash:%X\r\n",Verify_Hash);

	//not need Verify_sig
	if (mode == Not_verify_sig)
	{
		return 1;
	}

	//SHA256 result addr
	SHA256_(Start_Addr,size,S_path);
	//Tony_stop(0xD4);

	if ((mode &0x03) ==  RSA_mode)
	{
		//for RSA, Key reg include public modulus + Signature (512 bytes)
		//verify RSA mode
		RSA_main(Key_Start_Addr,S_path);
		//Tony_stop(mode);
		return Compare((EC_SRAM_Base+(DLM_Select(RSA_Data_addr_DLM_Sel)*0x400)+RSA_Result_offset),SHA256_Length,RSA_mode);
	}
	else
	{
		//for SHA256, Key reg include hash data(32 bytes)
		//only check SHA256 mode
		if (Verify_Hash == 1)
		{
			OP_1K(Key_Start_Addr,Select_EM,0x00,DLM_Select(DLM_Sel_2),SPI_Read);
		}
		else
		{
			OP_1K(Key_Start_Addr,S_path,0x00,DLM_Select(DLM_Sel_2),SPI_Read);
		}

		return Compare(M1K_DLM_SEL,SHA256_Length,SHA256_mode);
	}
}

int check_source_not_all_ff(uint8_t Source_DLM,uint8_t S_path)
{	
	uint32_t i;

	for (i=0; i< 0x400 ; i++)
	{
		if (ECREG((EC_SRAM_Base+DLM_Select(Source_DLM)*0x400)+i) != 0xFF)
		{
			return 1;
		}
	}

	return 0;

}

int check_source_destination_different(uint8_t Des_DLM,uint8_t Source_DLM,uint8_t S_path)
{
	uint32_t i;

	for (i=0; i< 0x400 ; i++)
	{
		if (ECREG((EC_SRAM_Base+DLM_Select(Source_DLM)*0x400)+i)
				!= ECREG((EC_SRAM_Base+DLM_Select(Des_DLM)*0x400)+i))
		{
			DPRINTK(1,"different addr %X %X s_data %X d_data %X\r\n",Source_DLM,i,ECREG((EC_SRAM_Base+DLM_Select(Source_DLM)*0x400)+i),ECREG((EC_SRAM_Base+DLM_Select(Des_DLM)*0x400)+i));
			return 1;
		}
	}
	return 0;

}

int OPErase(uint32_t start_addr,uint32_t end_addr,uint8_t Sel_path)
{
	uint32_t addr;

    const struct device *Fspi_dev = DEVICE_DT_GET(DT_NODELABEL(flashctrl));

	if (Sel_path == Select_EM)
	{
		;								//82202 HW_Mirror_Manual_Mode function = erase + program
	}
	else
	{
		for(addr = start_addr; addr<=end_addr; addr+=0x1000)
		{
            EC_INDIRECT_READ_FLASH = EC_INDIRECT_READ_EXTERNAL_FLASH;
            flash_erase(Fspi_dev, addr, 0x1000);
		}
	}

	return	1;
}
//copy_to_flash(uint32_t S_startaddr,uint32_t D_startaddr,uint32_t Bin_size,
//                    uint8_t S_path,uint8_t D_path,uint8_t binstate)
//
//S_startaddr : source start addr
//D_startaddr : destination start addr
//Bin_size    : size
//S_path      : source path
//D_path      : destination path
//binstate    : data need descrypt before to flash
void copy_to_flash(uint32_t S_startaddr,uint32_t D_startaddr,uint32_t Bin_size,
				   uint8_t D_path,uint8_t S_path,uint8_t binstate)
{
	
	uint32_t i;
	uint8_t j;
	uint8_t Read1KnotAll_ff = 0;
	uint8_t neederase = 0;
	uint8_t bank_k = 0;

	bank_k = 4;					// check 4k at one time
	
	DPRINTK(1,"bin size %x\r\n",Bin_size);

	//		Tony_stop(0x01);
	//
	for (i = 0; i < Bin_size; i+=(bank_k*0x400))
	{
		Read1KnotAll_ff = 0;
		neederase = 0;
		DPRINTK(1,"process %x\r\n",i);
		DPRINTK(1,"D_staraddr %x\r\n",D_startaddr+i);

		for (j=0; j<bank_k; j++)
		{
			if (S_path == Select_SSPI)
			{

				//SSPI_CMDQ_Dual_Read(S_startaddr+i+(j*0x400),0x400,DLM_Select(DLM_Sel_0+j));		//source
			}
			else
			{
				//Tony_stop(0x02);
				OP_1K(S_startaddr+i+(j*0x400),S_path,0x00,DLM_Select(DLM_Sel_0+j),SPI_Read);		//source
			}
			if (D_path == Select_SSPI)
			{
				//SSPI_CMDQ_Dual_Read(D_startaddr+i+(j*0x400),0x400,DLM_Select(DLM_Sel_4));
			}
			else
			{
				OP_1K(D_startaddr+i+(j*0x400),D_path,0x00,DLM_Select(DLM_Sel_4),SPI_Read);
			}

			//Tony_stop(0x03);
			//check DLM is FFh
			Read1KnotAll_ff |= check_source_not_all_ff(DLM_Sel_0+j,S_path);
			//check DLM is the same??
			neederase |= check_source_destination_different(DLM_Sel_4,DLM_Sel_0+j,S_path);
		}

		if (neederase)
		{
			DPRINTK(1,"erase\r\n");
			if (D_path == Select_SSPI)
			{
				//SSPI_PIO_Write_Status(0x00);
				//SSPI_CMDQ_Sector_Erase(D_startaddr+i);
			}
			else
			{
				OPErase(D_startaddr+i,D_startaddr+i,D_path);
			}

			//Tony_stop(0x05);
			//program 1k
			if (Read1KnotAll_ff == 1)
			{
				for (j=0; j<bank_k; j++)
				{
					DPRINTK(1,"write\r\n");

					if (D_path == Select_SSPI)
					{
						//SSPI_CMDQ_Page_Program((D_startaddr+i+(j*0x400)),DLM_Select(DLM_Sel_0+j));
					}
					else
					{
						OP_1K(D_startaddr+i+(j*0x400),D_path,0x00,DLM_Select(DLM_Sel_0+j),SPI_Program);
					}
				}
			}

			if (D_path == Select_SSPI)
			{
				//SSPI_PIO_Write_Status(0xBC);	// all protect
			}
		}
	}
}
void NIST_Process(void)
{
    uint32_t ret;

    SCDCR0 = 0x00;
    ret = Sig_hash_Verify(SPI_USER0_START_ADDR, SPI_USER0_START_ADDR+UCODE0_size, UCODE0_size,Select_SPI,RSA_mode,0);
    if (ret == 0) 
    {
        DPRINTK(1,"USER0 Hash verify failed! %d\n", ret);
    } 
    else 
    {
        DPRINTK(1,"USER0 Hash verify succeeded!\n");
        copy_to_flash(SPI_USER0_START_ADDR,SPI_USER1_START_ADDR,UCODE1_size+0x1000,Select_SPI,Select_SPI,0);
        ret = Sig_hash_Verify(SPI_USER1_START_ADDR, SPI_USER1_START_ADDR+UCODE1_size, UCODE1_size,Select_SPI,RSA_mode,0);
        if (ret == 0) 
        {
            DPRINTK(1,"USER1 Hash verify failed! %d\n", ret);
        }
        else 
        {
            DPRINTK(1,"USER1 Hash verify succeeded!\n");
        }
    }
    SCDCR0 = 0x20;
}