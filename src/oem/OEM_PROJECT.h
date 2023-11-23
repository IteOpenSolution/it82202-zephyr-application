/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_OEM_PROJECT_H_
#define _ITE_OEM_PROJECT_H_

#include "../include/include.h"

//*****************************************************************************
/* BBK Firmware Version */
//*****************************************************************************
#define _BBK_MAIN_VERSION            0xB0
#define _BBK_SUB_VERSION             0x1
#define _BBK_TEST_VERSION            0x04

//*****************************************************************************
/* EC Firmware OEM Version */
//*****************************************************************************
#define _EC_MAIN_VERSION            0x00
#define _EC_SUB_VERSION             0x00
#define _EC_TEST_VERSION            0x00
// #define _BUILD_FV                   "EC VER:00.19.04$"
#define _EC_BETA_VERSION            0x00

#define _LSFV_MAIN_VERSION          0
#define _LSFV_SUB_VERSION           0x19
#define _LSFV_TEST_VERSION          0x00
// #define _BUILD_LSFV                 "LsFv:00.19.00$"

// #define _BUILD_MUFG                 "Qualcomm$"
// #define _BUILD_MODEL                "WoS 8c GenX$"
// #define _BUILD_GUEST                "ODM$"
// #define _BUILD_BOARD                "MB:A0$"

#define SUPPORT_NV_SPACES           false
#define _SAVE_NV_TIMER              10  //10x100ms = 1sec
#define _SAVE_NV_TIMER3             30  //30x100ms = 3sec

//*****************************************************************************
/*
  PROJECT NOTES:
  ADC7 Board ID:
  < 1V   | IDP  | Fan1(A2)
  < 1.7V | IDPS | Fan1(A2) Fan2(A3_SOCKET FAN)
  < 2.5V | CRD  | Fan1(A2)

  ----| Fan1                  | Fan2
  CRD | Multi-Profile         | N/A
  IDP | [TSkin,ADC0-2][CPUTj] | N/A
  IDPS| [TSkin,ADC0-7]        | [CPUTj]

*/
//*****************************************************************************
/* CODE FEATURE SETTING */
//*****************************************************************************
#define SUPPORT_X86_PLATFORM        false
#define SUPPORT_HID_PLATFORM        true

//*****************************************************************************
/* OEM Configuration */
//*****************************************************************************
#define SUPPORT_SMB_SLAVE_A         true
#define SUPPORT_SMB_SLAVE_B         true
#define SUPPORT_SMART_CHARGER       false
#define SUPPORT_SMART_BATTERY       false
#define SUPPORT_SWAP_SMBUS_A_D      false
#define SUPPORT_SWAP_SMBUS_B_D      true

#define SUPPORT_SW_MIRROR           false
#define SUPPORT_PECI                false
#define SUPPORT_PECI_CS_MODE        false
#define SUPPORT_LID_SWITCH          false

#define SUPPORT_HOTKEY_SWAP         true
#define _HOTKEY_WIN_UP_TIMER        150     //5ms*150=0.75s

//*****************************************************************************
/* CHIP LEVEL CONFIGURATION */
//*****************************************************************************
#define ITE_CHIP_IT557X             false
#define ITE_eSPI_LOW_FREQUENCY      true    // true: For Bring Up, LA Analyzer
#define SUPPORT_INTERFACE_eSPI      false
#define ITE_eSPI_SAFS_MODE          false
#define eSPI_RESET_FOR_DSW_PWROK    true    // true: eSPI with None-DeepSx
#define SUPPORT_LPC_BUS_1_8V        true    // true: Setting LPC Bus 1.8V
#define SUPPORT_MIRROR_ONCE         false
#define SHARED_BIOS_TRI_STATE       false
#define SUPPORT_PORT_I2EC           false
#define SUPPORT_PWRSW_RESET         false   // GPE.4
#define EC_SIGNATURE_FLAG           0xB5    // For 8518 crystal free

//*****************************************************************************
/* ITE EC KERNEL CODE FUNCTION SETTING */
//*****************************************************************************
#define SUPPORT_CORE_FLASH_API      true
#define SUPPORT_SMBUS_E_F           false
#define SUPPORT_CHECK_SMBUS_CAN_USE false
#define REMOVE_CORE_INIT_SIO        false
#define SUPPORT_FLASH_OFF_SEQUENCE  false
#define SUPPORT_HOOK_WARMBOOT       true
#define SUPPORT_SERVICE_PS2         false   // true: Support PS/2 devices
#define SUPPORT_REPEAT_CTRL_EFFECT  false
#define SUPPORT_CODE_SALVE_I2C      true
#define UART1_DEBUG                 true
#undef  UART2_DEBUG
#define SUPPORT_EXT_KSO_SCAN        true

//*****************************************************************************
/* PS2 interface */
//*****************************************************************************
/* Note : If TouchPad_only is set, remeber to call
          PowerOffClearTPPendingData() function in power off sequnce
          include (S3, S4, and S5)
*/
#define TouchPad_only           true    // true : Only PS/2 touch pad device
#define Hook_ECACKMouseDriver
#define SUPPORT_PS2_VIRTUAL     true

//*****************************************************************************
/* Keyboard scan */
//*****************************************************************************
#define KB_FnStickKey           false   // true: for Fn stick key function

//*****************************************************************************
// UART debug interface
// Timer 2 baudrate IT557x
// (only support 9600 bps, please change to Uart EC side for 115200bps)
//*****************************************************************************
//#define UART_Debug        // Define : enable Tx debug (GPIO E6)
// #ifdef UART_Debug
// #define R2HV                    0xFF
// #define R2LV                    0xFB  //9600 bps
// #endif

#endif /* _ITE_OEM_PROJECT_H_ */
