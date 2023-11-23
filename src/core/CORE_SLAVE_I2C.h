/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ITE_CORE_SLAVE_I2C_H_
#define _ITE_CORE_SLAVE_I2C_H_

#include "../include/include.h"

// TODO function
#define EC_CAP_LED_EN_HI()
#define EC_CAP_LED_EN_LO()

#define Init_HID_Keyboard()   

#define I2EC_Mode()

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
/* HID & ACPI over i2c extended command */
//-----------------------------------------------------------------------------
/* I2C ACPI Command */
#define _ACPI_CMD_EVENT             0x05    /* Without BYTE count */
#define _ACPI_CMD_CHIP_ID           0x06
#define _ACPI_CMD_BST1              0x07
#define _ACPI_CMD_BIF1              0x08
#define _ACPI_CMD_BTP1              0x0B
#define _ACPI_CMD_ECVER             0x0D    /* Without BYTE count */

/* ACPI command without BYTE Count protocol. */
#define _CMD_DATA_BUFFER_WRITE      0xA0    /* Without BYTE count */
//[A0][Size][ADRH][ADRM][ADRL]
#define _CMD_DATA_BUFFER_READ       0xA1    /* Without BYTE count */
//[A1][Size][ADRH][ADRM][ADRL]

/* ACPI command with BYTE Count protocol. */
#define _CMD_ACPI_GET_EC_VER        0x0E
#define _CMD_ACPI_GET_EC_Fv_LsFV    0x0F
#define _CMD_ACPI_GET_FULL_VER      0x0F
#define _CMD_ACPI_GET_EVENT         0x10
#define _CMD_ACPI_MIRROR_ONCE       0x11
#define _CMD_ACPI_FORCE_MIRROR      0x12
#define _CMD_ACPI_OFF_DO_MIRROR     0x13
#define _CMD_ACPI_E2A_SPI_COPY      0x14

#define _CMD_THERMAL_CMD_GROUP      0x20  //WC2WD3
#define _CMD_SOC_TJ_FROM_HLOS       0x20  //WC2RWD1
#define _CMD_GET_FAN_STATUS         0x21  //WC2RWD3
#define _CMD_GET_FAN_SPEED_RPM      0x22  //WC1RWD1
#define _CMD_MODERN_STANDBY_NOTIFY  0x23  //WC1WD1
#define _CMD_FAN_PROFILE_SWITCH     0x24  //WC1RWD1
#define _CMD_FAN_TRIP_POINT         0x25  //WC2RD3
#define _CMD_NUM_PROFILE            0x26  //WC2RD2
#define _CMD_NUM_LUTS               0x27  //WC2RD1
#define _CMD_GET_SET_LUT_TABLE      0x28  //WC3RWD66
#define _CMD_THERMISTOR_READ_ADC0   0x29  //WC1RD1
#define _CMD_THERMISTOR_READ_ADC1   0x2A  //WC1RD1
#define _CMD_THERMISTOR_READ_ADC2   0x2B  //WC1RD1
#define _CMD_THERMISTOR_READ_ADC3   0x2C  //WC1RD1
#define _CMD_THERMISTOR_READ_ADC4   0x2D  //WC1RD1
#define _CMD_THERMISTOR_READ_ADC5   0x2E  //WC1RD1
#define _CMD_THERMISTOR_READ_ADC6   0x2F  //WC1RD1

#define _CMD_THERMAL_CMD_GROUP2     0x30 
#define _CMD_QC_TOOLS_TEST_CMD      0x30  //WC2WD4
#define _CMD_THERMAL_EC_RESET       0x31  //R1
#define _CMD_SET_NTC_THRESHOLD      0x32  //WC2WD5  PSV<CR3<HOT<CRT
#define _CMD_SET_NTC_SAMPLE_RATE    0x34  //WC1WD2

#define _CMD_UART_LOG_TIME_STAMP    0x40
#define _CMD_SEND_SET_TIME_STAMP    0x41

#define _CMD_ACPI_DATA_BLOCK_READ   0xA2
#define _CMD_ACPI_GET_AC_BATT       0xAB
#define _CMD_ACPI_GET_EC_STATE      0xEC
#define _CMD_ACPI_QUICK_PROCESS     0xAF     /* [ST][ADRW][AF][BC=1][CMD][ED] */
#define _CMD_SPI_ERASE_INT_EC_FW    0xEA     /* EXT.SPI EC 128K */
#define _CMD_SPI_ERASE_EXT_EC_FW1   0xEB
#define _CMD_SPI_ERASE_EXT_EC_FW2   0xED

#define _CMD_ACPI_HID_SPI_COMMAND   0xBB     /* Compatible with HID SPI command */
#define _CMD_ACPI_ERASE_SECTOR      0xAE
#define _CMD_ACPI_BUFFER_SPI_WRITE  0xAA
/* Size: 1:32B, 2:64B 4:128B,8:256B,16:512B */
#define _CMD_ACPI_SPI_READ_BUFFER   0xA7
#define _CMD_ACPI_WRITE_EC_REGISTER 0xA8
#define _CMD_ACPI_READ_EC_REGISTER  0xA9

/* PPM UCSI Command */
#define _CMD_UCSI_GET_VER           0xC0
#define _CMD_UCSI_GET_CCI           0xC1
#define _CMD_UCSI_SET_CTRL          0xC2
#define _CMD_UCSI_SET_MGI           0xC3
#define _CMD_UCSI_GET_MGO           0xC4

#define _CMD_GET_PD_C0_STATUS       0xC8
#define _CMD_GET_PD_C1_STATUS       0xC9
#define _CMD_PD_I2C_DEBUG_MODE      0xCF

//-----------------------------------------------------------------------------
/* HID BB command + Sub-Command */
//-----------------------------------------------------------------------------
#define _CMD_ENTER_PRE_DEFINE       0xB4
#define _CMD_ENTER_FLASH_IDLE       0xDC
#define _CMD_JUMP_MAIN_SERVICE      0x33
#define _CMD_EXIT_FLASH_IDLE        0x33
#define _CMD_ITE_MCU_RESET          0xCC
#define _CMD_ITE_MIRROR_ONCE        0x11
#define _CMD_ITE_FORCE_MIRROR       0x12
#define _CMD_ITE_OFF_DO_MIRROR      0x13

#define _CMD_COPY_A_MBK_TO_BAKUP    0x15
#define _CMD_COPY_BAKUP_TO_A_MBK    0x16
#define _CMD_COPY_A_BBK_TO_BAKUP    0x17
#define _CMD_COPY_BAKUP_TO_A_BBK    0x18

#define _CMD_SPI_WRITE_DISABLE      0xE0
#define _CMD_SPI_WRITE_ENABLE       0xE1
#define _CMD_SPI_ERASE_SECTOR       0xE2
#define _CMD_SPI_WRITE_256          0xE3
#define _CMD_SPI_WRITE              0xE4
#define _CMD_SPI_READ_256           0xE5
#define _CMD_SPI_READ_ID            0xE6
#define _CMD_SPI_ERASE_INT_MAIN_FW  0xE7
#define _CMD_SPI_ERASE_EXT_EC_FW12  0xE8

#define _CMD_GET_CHECKSUM_STATUS    0xEB    //B0:ABBK B1:BBBK B2:AMAIN B4:BBAIN
#define _CMD_RUN_MAIN_CHECKSUM      0xED
#define _CMD_RUN_MAIN_ALL_CHECKSUM      0xF0
#define _CMD_RUN_BACKUP_ALL_CHECKSUM    0xF1
#define _CMD_RUN_BACKUP_BBK_CHECKSUM    0xF4
#define _CMD_RUN_BACKUP_MAIN_CHECKSUM   0xF5

#define _CHKSUM_PASS                0xAC
#define _CHKSUM_FAILED              0xFA
#define _ABOOT_CHKSUM_POS           0x34
#define _BBOOT_CHKSUM_POS           0x39
#define _AMAIN_CHKSUM_POS           0x44
#define _BMAIN_CHKSUM_POS           0x49
#define _ALL_CHKSUM_STATUS          0x4A

#define _COPYBBBK_ABBK              0
#define _COPYBMAIN_AMAIN            6
#define _COPYABBK_BBBK              12
#define _COPYAMAIN_BMAIN            18

#define _CHKSUM_ACT_BBK             0
#define _CHKSUM_ACT_MAIN            8
#define _CHKSUM_BAK_BBK             16
#define _CHKSUM_BAK_MAIN            24

//-----------------------------------------------------------------------------
/* HID Over I2C Protocol Specification (Device Side) Version 1.00 */
//-----------------------------------------------------------------------------
#define HID_OFFSET                          0x30
#define HID_KB_GENERIC                      0x02
#define HID_KB_MM_CONSUMER_FN_REPORT_ID     0x03
#define HID_KB_MM_WIRELESS_FN_REPORT_ID     0x04
#define HID_KB_MM_SYSTEM_FN_REPORT_ID       0x05
#define HID_MOUSE_GENERIC                   0x06
#define HID_ITE_I2EC_REPORT_ID1             0x09
#define HID_ITE_I2EC_REPORT_LENGTH1         8
#define HID_ITE_I2EC_REPORT_ID2             0x0A
#define HID_ITE_I2EC_REPORT_LENGTH2         64

//-----------------------------------------------------------------------------
#define _HID_INTR_LEVEL         0x00
#define _HID_INTR_EDGE          0x01
//-----------------------------------------------------------------------------
#define _HID_DESC_LAYOUT        0x0001
#define _HID_DESC_LAYOUT2       0x0020
/* The register index containing the Report Descriptor on the DEVICE. */
#define _REPORT_DESC_REG        0x0021
/* This field identifies, in unsigned bytes, the register number to read the
   input report from the DEVICE. */
#define _HID_INPUT_REG          0x0024
/* This field identifies, in unsigned bytes, the register number to send the
   output report to the DEVICE. */
#define _HID_OUTPUT_REG         0x0025
/* This field identifies, in unsigned bytes, the register number to send
   command requests to the DEVICE */
#define _HID_COMMAND_REG        0x0022
/* This field identifies in unsigned bytes the register number to exchange
   data with the Command Request */
#define _HID_DATA_REG           0x0023
/* EC send keyboard data to host */
#define _KB_INPUT_REPORT        0x00EC
#define _TP_INPUT_REPORT        0x00EE

#define _USAGE_PAGE_PREFIX_0C   0xFC
#define _WIRELESS_KEY_PREFIX    0xFD
#define _USAGE_PAGE_PREFIX_01   0xFE

/*** HID Op Code ***/
#define _HID_OPCODE_RESET       0x01
#define _HID_OPCODE_READ        0x02
#define _HID_OPCODE_WRITE       0x03
#define _HID_OPCODE_SET_POWER   0x08

//-----------------------------------------------------------------------------
/* HID Over I2C Protocol Specification (Device Side) Version 1.00 */
//-----------------------------------------------------------------------------
/* The length, in unsigned bytes, of the complete Hid Descriptor */
#define wHIDDescLength          0x001E  // 30 bytes
/* The version number, in binary coded decimal (BCD) format.
   DEVICE should default to 0x0100 */
#define bcdVersion              0x0100  // For version 1.00
/* The length, in unsigned bytes, of the Report Descriptor. */
//#define wReportDescLength     0x00A7  // 167 bytes
/* The register index containing the Report Descriptor on the DEVICE. */
#define wReportDescRegister     _REPORT_DESC_REG
/* This field identifies, in unsigned bytes, the register number to read the
   input report from the DEVICE. */
#define wInputRegister          _HID_INPUT_REG
/* This field identifies in unsigned bytes the length of the largest Input
   Report to be read from the Input Register (Complex HID Devices will need
   various sized reports). */
//#define wMaxInputLength       0x000E  // 11 bytes
#define wMaxInputLength         0x0018  // 24 bytes
/* This field identifies, in unsigned bytes, the register number to send the
   output report to the DEVICE. */
#define wOutputRegister         _HID_OUTPUT_REG
/* This field identifies in unsigned bytes the length of the largest output
   Report to be sent to the Output Register (Complex HID Devices will need
   various sized reports). */
//#define wMaxOutputLength      0x0017
#define wMaxOutputLength        0x0040  // 64 bytes
/* This field identifies, in unsigned bytes, the register number to send
   command requests to the DEVICE */
#define wCommandRegister        _HID_COMMAND_REG
/* This field identifies in unsigned bytes the register number to exchange
   data with the Command Request */
#define wDataRegister           _HID_DATA_REG
/* This field identifies the DEVICE manufacturers Vendor ID. Must be non-zero. */
#define wVendorID               0x048D  //ITE_0x048D
/* This field identifies the DEVICE's unique model / Product ID. */
#define wProductID              0x8987
/* This field identifies the DEVICE's firmware revision number. */
#define wVersionID              0x0003
/* This field is reserved and should be set to 0. */
#define wReserved               0x0000

extern const unsigned char Report_Descriptor[];
extern const unsigned char HID_Descriptor_Layout[];

void service_SlaveI2C_B(ProtocolType target, I2CCmdType action, uint8_t wbuff[], uint32_t wlength, uint8_t rbuff[], uint32_t *rlength);
#endif // _ITE_CORE_SLAVE_I2C_H_
