/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

LOG_MODULE_REGISTER(ite_hid_acpi_i2c, 4);

#define HidOverI2c 0
#define AcpiOverI2c 1

#define OverI2cWrite 0
#define OverI2cRead 1

uint8_t HidOverI2cReadBuff[255] = {0};
uint8_t AcpiOverI2cReadBuff[255] = {0};
uint32_t Hid_I2c_rlength = 0;
uint32_t Acpi_I2c_rlength = 0;

uint8_t HidKBBuff[32] = {0};

// HID
void HidOverI2cReadCmdParser(uint8_t **rbuff, uint32_t *rlength)
{
    printk("HidOverI2cReadCmdParser");

    memset(HidOverI2cReadBuff, 0, sizeof(HidOverI2cReadBuff));
    
    if( HID_wRegIndex_B != 0)
    {
        service_SlaveI2C_B(HidOverI2c, Read, NULL, 0, HidOverI2cReadBuff, &Hid_I2c_rlength);
        
        printk("Get back from HidOverI2cReadCmdParser");

        *rbuff = HidOverI2cReadBuff;
        *rlength = Hid_I2c_rlength;

        Hid_I2c_rlength = 0;

        HID_wRegIndex_B = 0;
    }
    else if( HID_wRegIndex_B == 0 )
    {
        if( HID_KB_Packet[0] != 0x00 )
        {
            printk("Return KB Data");
            HID_OutBuf_B[0] = 0x0B;     /* Length = 0x000B */
            HID_OutBuf_B[1] = 0x00;
            HID_OutBuf_B[2] = (HID_KB_GENERIC + HID_OFFSET);
            HID_OutBuf_B[3] = 0x00;//HID_ScannerStateL;  /* Control Byte */
            HID_OutBuf_B[4] = 0x00;     /* Reserved */
            HID_OutBuf_B[5] = HID_KB_Packet[0];
            HID_OutBuf_B[6] = HID_KB_Packet[1];
            HID_OutBuf_B[7] = HID_KB_Packet[2];
            HID_OutBuf_B[8] = HID_KB_Packet[3];
            HID_OutBuf_B[9] = HID_KB_Packet[4];
            HID_OutBuf_B[10] = HID_KB_Packet[5];

            memcpy(HidKBBuff, (void *)HID_OutBuf_B, 24);
            *rbuff = HidKBBuff;
            *rlength = 32;
            memset((void *)HID_KB_Packet, 0, 6);
            memset((void *)HID_OutBuf_B, 0, 24);
        }
        else
        {
            printk("Return Clear KB Data");
            memset(HidKBBuff, 0, sizeof(HidKBBuff));
            *rbuff = HidKBBuff;
            *rlength = 24;
        }

    }
}

void HidOverI2cWriteCmdParser(uint8_t wbuff[], uint32_t wlength)
{
    printk("HidOverI2cWriteCmdParser");
    service_SlaveI2C_B(HidOverI2c, Write, wbuff, wlength, NULL, NULL);
}

// ACPI
void AcpiOverI2cReadCmdParser(uint8_t **rbuff, uint32_t *rlength)
{
    printk("AcpiOverI2cReadCmdParser");

    memset(AcpiOverI2cReadBuff, 0, sizeof(AcpiOverI2cReadBuff));
    Acpi_I2c_rlength = 0;

    service_SlaveI2C_B(AcpiOverI2c, Read, NULL, 0, AcpiOverI2cReadBuff, &Acpi_I2c_rlength);

    printk("Get back from AcpiOverI2cReadCmdParser");


    *rbuff = AcpiOverI2cReadBuff;
    *rlength = Acpi_I2c_rlength;

    Acpi_I2c_rlength = 0;
}

void AcpiOverI2cWriteCmdParser(uint8_t wbuff[], uint32_t wlength)
{
    printk("AcpiOverI2cWriteCmdParser");
    service_SlaveI2C_B(AcpiOverI2c, Write, wbuff, wlength, NULL, NULL);
}