/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_OEM_ACPI_H_
#define _ITE_OEM_ACPI_H_

#include "../include/include.h"

#define Get_RamProfileLUT(x)
#define Load_FanProfileToRam(x)


/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * OEM SCI/SMI Event Code Define
 *---------------------------------------------------------------------------*/
#define _SCI_QUEUE                  0x00
#define _PRIORITY_FIRST             0x01
#define _SCIEVT_NULL                0x00    //Can't use
#define _SCIEVT_ADAPTER_IN          0x01    //Adapter in
#define _SCIEVT_ADAPTER_OUT         0x02    //Adapter out
#define _SCIEVT_UCSI                0x20    //USB TYPE C Q EVENT
#define _SCIEVT_USBC_C0_HPD         0x21    //USB TYPE C Q EVENT
#define _SCIEVT_USBC_C1_HPD         0x22    //USB TYPE C Q EVENT

/* Previous Reference Definition */
#define _SCIEVT_FnF1                0x01    //Hotkey Fn+ F1 Event
#define _SCIEVT_FnF2                0x02    //Hotkey Fn+ F2 Event
#define _SCIEVT_FnF3                0x03    //Hotkey Fn+ F3 Event
#define _SCIEVT_FnF4                0x04    //Hotkey Fn+ F4 Event
#define _SCIEVT_FnF5                0x05    //Hotkey Fn+ F5 Event
#define _SCIEVT_FnF6                0x06    //Hotkey Fn+ F6 Event
#define _SCIEVT_FnF7                0x07    //Hotkey Fn+ F7 Event
#define _SCIEVT_FnF8                0x08    //Hotkey Fn+ F8 Event
#define _SCIEVT_FnF9                0x09    //Hotkey Fn+ F9 Event
#define _SCIEVT_FnF10               0x10    //Hotkey Fn+F10 Event
#define _SCIEVT_FnF11               0x11    //Hotkey Fn+F11 Event
#define _SCIEVT_FnF12               0x12    //Hotkey Fn+F12 Event
#define _SCIEVT_ADAPTER             0x0A    //Adapter status changed
#define _SCIEVT_BATTERY             0x0B    //Battery status changed

#define _SCIEVT_VOLUME_UP           0x80
#define _SCIEVT_VOLUME_DOWN         0x81
#define _SCIEVT_WINDOWS_HOME        0x85

#define _SCIEVT_THERMAL_DPTF        0xF1

#define _SCIEVT_PWRBTN_CTRL         0x54
#define _SCIEVT_PWRBTN_MAKE         0xD5
#define _SCIEVT_PWRBTN_BREAK        0xD6

#define _SCIEVT_FAN1_RPM_TRIP       0x32
#define _SCIEVT_FAN1_RPM_HI         0x32
#define _SCIEVT_FAN1_RPM_LO         0x32    //0x33
#define _SCIEVT_FAN1_STATUS         0x30    //0x36

#define _SCIEVT_FAN2_RPM_TRIP       0x33
#define _SCIEVT_FAN2_RPM_HI         0x33    //0x34
#define _SCIEVT_FAN2_RPM_LO         0x33    //0x35
#define _SCIEVT_FAN2_STATUS         0x31    //0x37

#define _SCIEVT_SETTING_LUT_OK      0x34
#define _SCIEVT_SWITCH_PROFILE_OK   0x35

#define _SCIEVT_THRESHOLD_CHANGED_NTC1  0x36
#define _SCIEVT_THRESHOLD_CHANGED_NTC2  0x37
#define _SCIEVT_THRESHOLD_CHANGED_NTC3  0x38
#define _SCIEVT_THRESHOLD_CHANGED_NTC4  0x39
#define _SCIEVT_THRESHOLD_CHANGED_NTC5  0x3A
#define _SCIEVT_THRESHOLD_CHANGED_NTC6  0x3B
#define _SCIEVT_THRESHOLD_CHANGED_NTC7  0x3C
#define _SCIEVT_RECOVERD_FROM_RESET     0x3D


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Hook_62Port(BYTE PM1_Cmd);
extern void Hook_66Port(BYTE PM1_Cmd);
extern void Hook_ACPICommand(void);

extern BYTE Hook_ReadMapECSpace(BYTE MapIndex);
extern void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1);

extern void SCI_EventCenter(void);
extern void ReadSCI_Buffer(void);
extern void WriteSCI_Buffer(BYTE SCI_NUM, BYTE PRIORITY);
extern void OEM_ACPI_Gen_Int(void);
extern void Clear_SCI_Buffer(void);

#if 1   //SUPPORT_HID_PLATFORM
/*-----------------------------------------------------------------------------
 * I2C/HID External Calling Prototype
 *---------------------------------------------------------------------------*/
extern BYTE AcpiReadData_I2C_A(BYTE PktIdxR);
extern void AcpiWriteData_I2C_A(BYTE PktIdxW, BYTE PktData);

extern BYTE AcpiReadData_I2C_B(BYTE PktIdxR);
extern void AcpiWriteData_I2C_B(BYTE PktIdxW, BYTE PktData);

extern BYTE AcpiReadData_I2C_AB(uint8_t rbuff[], uint32_t *rlength);
extern void AcpiWriteData_I2C_AB(uint8_t wcmd[], uint32_t wlength);
extern void Hook_SlaveI2C_AB_Stop(void);

extern void Service_BB_Command(void);
extern void Service_FwCopyToExtSPI(void);

#endif



#endif /* _ITE_OEM_ACPI_H_ */

#if 0
/*-----------------------------------------------------------------------------
 * @file     | OEM_ACPI.H
 *-----------+-----------------------------------------------------------------
 * @function | OEM_ACPI.C Function prototype include definition
 *-----------+-----------------------------------------------------------------
 * @model    | ITE Embedded Controller Firmware
 * @version  | Kernel-14.4,14.5,14.6,eSPI_14.6
 * @author   | ITE Tech. Inc. Technical Marketing Div.I, Dept. II.
 * @note     | Copyright(c)2012-2021, ITE Tech. Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#ifndef OEM_ACPI_H
#define OEM_ACPI_H

/*-----------------------------------------------------------------------------
 * Parameter & Label Process Definition
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * OEM SCI/SMI Event Code Define
 *---------------------------------------------------------------------------*/
#define _SCI_QUEUE                  0x00
#define _PRIORITY_FIRST             0x01
#define _SCIEVT_NULL                0x00    //Can't use
#define _SCIEVT_ADAPTER_IN          0x01    //Adapter in
#define _SCIEVT_ADAPTER_OUT         0x02    //Adapter out
#define _SCIEVT_UCSI                0x20    //USB TYPE C Q EVENT
#define _SCIEVT_USBC_C0_HPD         0x21    //USB TYPE C Q EVENT
#define _SCIEVT_USBC_C1_HPD         0x22    //USB TYPE C Q EVENT

/* Previous Reference Definition */
#define _SCIEVT_FnF1                0x01    //Hotkey Fn+ F1 Event
#define _SCIEVT_FnF2                0x02    //Hotkey Fn+ F2 Event
#define _SCIEVT_FnF3                0x03    //Hotkey Fn+ F3 Event
#define _SCIEVT_FnF4                0x04    //Hotkey Fn+ F4 Event
#define _SCIEVT_FnF5                0x05    //Hotkey Fn+ F5 Event
#define _SCIEVT_FnF6                0x06    //Hotkey Fn+ F6 Event
#define _SCIEVT_FnF7                0x07    //Hotkey Fn+ F7 Event
#define _SCIEVT_FnF8                0x08    //Hotkey Fn+ F8 Event
#define _SCIEVT_FnF9                0x09    //Hotkey Fn+ F9 Event
#define _SCIEVT_FnF10               0x10    //Hotkey Fn+F10 Event
#define _SCIEVT_FnF11               0x11    //Hotkey Fn+F11 Event
#define _SCIEVT_FnF12               0x12    //Hotkey Fn+F12 Event
#define _SCIEVT_ADAPTER             0x0A    //Adapter status changed
#define _SCIEVT_BATTERY             0x0B    //Battery status changed
//#define _SCIEVT_LID_CLOSED        0x0C    //LID closed event
//#define _SCIEVT_LID_OPEN          0x0D
//#define _SCIEVT_SLEEP             0x0E
//#define _SCIEVT_BRIGHTNESS        0x13
//#define _SCIEVT_CPU_T             0x20
//#define _SCIEVT_SKIN_T            0x21
//#define _SCIEVT_CHARGER_T         0x22
//#define _SCIEVT_THROT_OFF         0x30
//#define _SCIEVT_THROT_LV1         0x31
//#define _SCIEVT_THROT_LV2         0x32
//#define _SCIEVT_THROT_LV3         0x33
//#define _SCIEVT_THROT_LV4         0x34
//#define _SCIEVT_THROT_LV5         0x35
//#define _SCIEVT_THROT_LV6         0x36
//#define _SCIEVT_THROT_LV7         0x37
//#define _SCIEVT_CPU_DN_SPEED      0x3B
//#define _SCIEVT_CPU_UP_SPEED      0x3C
//#define _SCIEVT_CPU_TURBO_OFF     0x3D
//#define _SCIEVT_CPU_TURBO_ON      0x3E
//#define _SCIEVT_SHUTDOWN          0x3F

//#define _SCIEVT_USBTC             0x79    //USB TYPE C Q EVENT
//#define _SCIEVT_USBTC_OUT         0x7A    //USB TYPE C PLUG-OUT EVENT

#define _SCIEVT_VOLUME_UP           0x80
#define _SCIEVT_VOLUME_DOWN         0x81
#define _SCIEVT_WINDOWS_HOME        0x85

#define _SCIEVT_THERMAL_DPTF        0xF1

#define _SCIEVT_PWRBTN_CTRL         0x54
#define _SCIEVT_PWRBTN_MAKE         0xD5
#define _SCIEVT_PWRBTN_BREAK        0xD6

//#define _SCIEVT_MS_FAN_STOP       0x30    // Removed
//#define _SCIEVT_EXIT_MS_MODE      0x31    // Removed

#define _SCIEVT_FAN1_RPM_TRIP       0x32
#define _SCIEVT_FAN1_RPM_HI         0x32
#define _SCIEVT_FAN1_RPM_LO         0x32    //0x33
#define _SCIEVT_FAN1_STATUS         0x30    //0x36

#define _SCIEVT_FAN2_RPM_TRIP       0x33
#define _SCIEVT_FAN2_RPM_HI         0x33    //0x34
#define _SCIEVT_FAN2_RPM_LO         0x33    //0x35
#define _SCIEVT_FAN2_STATUS         0x31    //0x37

#define _SCIEVT_SETTING_LUT_OK      0x34
#define _SCIEVT_SWITCH_PROFILE_OK   0x35

#define _SCIEVT_THRESHOLD_CHANGED_NTC1  0x36
#define _SCIEVT_THRESHOLD_CHANGED_NTC2  0x37
#define _SCIEVT_THRESHOLD_CHANGED_NTC3  0x38
#define _SCIEVT_THRESHOLD_CHANGED_NTC4  0x39
#define _SCIEVT_THRESHOLD_CHANGED_NTC5  0x3A
#define _SCIEVT_THRESHOLD_CHANGED_NTC6  0x3B
#define _SCIEVT_THRESHOLD_CHANGED_NTC7  0x3C
#define _SCIEVT_RECOVERD_FROM_RESET     0x3D


/*-----------------------------------------------------------------------------
 * Data Structure Prototype
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Extern Resources
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * External Calling Prototype
 *---------------------------------------------------------------------------*/
extern void Hook_62Port(BYTE PM1_Cmd);
extern void Hook_66Port(BYTE PM1_Cmd);
extern void Hook_ACPICommand(void);

extern BYTE Hook_ReadMapECSpace(BYTE MapIndex);
extern void Hook_WriteMapECSpace(BYTE MapIndex, BYTE data1);

extern void SCI_EventCenter(void);
extern void ReadSCI_Buffer(void);
extern void WriteSCI_Buffer(BYTE SCI_NUM, BYTE PRIORITY);
extern void OEM_ACPI_Gen_Int(void);
extern void Clear_SCI_Buffer(void);

#if 1   //SUPPORT_HID_PLATFORM
/*-----------------------------------------------------------------------------
 * I2C/HID External Calling Prototype
 *---------------------------------------------------------------------------*/
extern BYTE AcpiReadData_I2C_A(BYTE PktIdxR);
extern void AcpiWriteData_I2C_A(BYTE PktIdxW, BYTE PktData);
//extern void Hook_SlaveI2C_A_Stop(void);

extern BYTE AcpiReadData_I2C_B(BYTE PktIdxR);
extern void AcpiWriteData_I2C_B(BYTE PktIdxW, BYTE PktData);
//extern void Hook_SlaveI2C_B_Stop(void);

extern BYTE AcpiReadData_I2C_AB(BYTE PktIdxR);
extern void AcpiWriteData_I2C_AB(BYTE PktIdxW, BYTE PktData);
extern void Hook_SlaveI2C_AB_Stop(void);

extern void Service_BB_Command(void);
extern void Service_FwCopyToExtSPI(void);

#endif
//-----------------------------------------------------------------------------
#endif
/*-----------------------------------------------------------------------------
 * End of OEM_ACPI.H */
#endif /* 0 */