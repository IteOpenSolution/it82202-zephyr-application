/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include "../include/include.h"

#if SUPPORT_CODE_SALVE_I2C

#define DEBUG_HID_RAMDEBUG                  false
#define HID_UART_DEBUG_OUTPUT               true
#define SUPPORT_CHANNEL_A_HID               false
#define SUPPORT_CHANNEL_B_HID               true
#define SUPPORT_CHANNEL_A_ACPI              true
#define SUPPORT_CHANNEL_B_ACPI              true
#define SUPPORT_CHANNEL_AB_SAME_ACPI        true

#define SUPPORT_HID_CHANNEL_A_KEYCODE       false
#define SUPPORT_HID_CHANNEL_B_KEYCODE       true
#define SUPPORT_HID_KEYBOARD                true
#define SUPPORT_HID_KEYBOARD_LED            true
#define SUPPORT_HID_MULTIMEDIA_KEYBOARD     true
#define SUPPORT_HID_WIRELESS_RADIO_CTRL     true
#define SUPPORT_HID_GENERAL_DESKTOP_CTRL    true
#define SUPPORT_HID_MOUSE                   false
#define SUPPORT_HID_SYNAPTICS_TP            false
#define SUPPORT_HID_ITE_I2EC_CTRL           true

//-----------------------------------------------------------------------------
/******************************************************************************
 * HID over I2C - REPORT DESCRIPTOR
 *****************************************************************************/
//-----------------------------------------------------------------------------
const unsigned char Report_Descriptor[] =
{
#if SUPPORT_HID_KEYBOARD
    //-------------------------------------------------------------------------
    // Keyboard     // 65 Bytes
    // Input report: Length LSB(0x0B), Length MSB(0x00), ID(0x01),
    //               Button, Reserve, Key0, Key1, Key2, Key3, Key4, Key5
    // Output report: Length LSB(0x04), Length MSB(0x00), ID(0x01), LED states
    //-------------------------------------------------------------------------
    0x05, 0x01, // Usage Page (Generic Desktop),
    0x09, 0x06, // Usage (Keyboard),
    0xA1, 0x01, // Collection (Application),
    0x85, HID_KB_GENERIC + HID_OFFSET,
    0x05, 0x07, // Usage Page (Key Codes);
    0x19, 0xE0, // Usage Minimum (224),
    0x29, 0xE7, // Usage Maximum (231),
    0x15, 0x00, // Logical Minimum (0),
    0x25, 0x01, // Logical Maximum (1),
    0x75, 0x01, // Report Size (1),
    0x95, 0x08, // Report Count (8),
    0x81, 0x02, // Input (Data, Variable, Absolute), ;Modifier byte
    0x95, 0x01, // Report Count (1),
    0x75, 0x08, // Report Size (8),
    0x81, 0x03, // Input (Constant, Var, Abs), ;Reserved byte
    0x95, 0x05, // Report Count (5),
    0x75, 0x01, // Report Size (1),
    0x05, 0x08, // Usage Page (Page# for LEDs),
    0x19, 0x01, // Usage Minimum (1),
    0x29, 0x05, // Usage Maximum (5),
    0x91, 0x02, // Output (Data, Variable, Absolute), ;LED report
    0x95, 0x01, // Report Count (1),
    0x75, 0x03, // Report Size (3),
    0x91, 0x03, // Output (Constant, Var, Abs), ;LED report padding
    0x95, 0x06, // Report Count (6),
    0x75, 0x08, // Report Size (8),
    0x15, 0x00, // Logical Minimum (0),
    0x25, 0x65, // Logical Maximum(101),
    0x05, 0x07, // Usage Page (Key Codes),
    0x19, 0x00, // Usage Minimum (0),
    0x29, 0xDD, // Usage Maximum (221),
    0x81, 0x00, // Input (Data, Array), ;Key arrays (6 bytes)
    0xC0,       // End Collection
#endif
    //-------------------------------------------------------------------------
    // Consumer Control     // 25 Bytes
    // Input report: Length LSB(0x05), Length MSB(0x00), ID(0x03),
    //               Data LSB, Data MSB
    //-------------------------------------------------------------------------
#if SUPPORT_HID_MULTIMEDIA_KEYBOARD
    /* Multimedia Keyboard */
    0x05, 0x0C, // Usage Page (Consumer)
    0x09, 0x01, // Usage (Consumer Control)
    0xA1, 0x01, // Collection (Application)
    0x85, HID_KB_MM_CONSUMER_FN_REPORT_ID + HID_OFFSET, // Report ID (2)
    0x19, 0x00, // Usage Minimum (0)
    0x2A, 0x3C, 0x02,   // Usage Maximum (572)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0x3C, 0x02,   // Logical Maximum (572)
    0x75, 0x10, // Report Size (16)
    0x95, 0x01, // Report Count (1)
    0x81, 0x00, // Input(Data, Array, Absolute)
    0xC0,       // End Collection
#endif
    //-------------------------------------------------------------------------
    //  Wireless radio button   // 25 Bytes
    // Input report: Length LSB(0x04), Length MSB(0x00), ID(0x03), 0x01
    //-------------------------------------------------------------------------
#if SUPPORT_HID_WIRELESS_RADIO_CTRL
    0x05, 0x01,
    0x09, 0x0C, // Usage Page (Wireless Radio Controls)
    0xA1, 0x01, // Collection (Application)
    0x85, HID_KB_MM_WIRELESS_FN_REPORT_ID + HID_OFFSET, // Report ID (3)
    0x15, 0x00, // Logical Maximum (0)
    0x25, 0x01, // Logical Minimum (1)
    0x09, 0xC6, // Usage (Wireless Radio Button)
    0x95, 0x01, // Report Count (1)
    0x75, 0x01, // Report Size (1)
    0x81, 0x06, // Input (Data,Var,Rel)
    0x75, 0x07, // Report Size (7)
    0x81, 0x03, // Input (Cnst,Var,Abs)
    0xC0,       // End Collection
#endif
    //-------------------------------------------------------------------------
    // Mouse        // 52 bytes
    // Input report: Length LSB(0x06), Length MSB(0x00), ID(0x02), Button,X,Y
    //-------------------------------------------------------------------------
#if SUPPORT_HID_MOUSE
    0x05, 0x01, // Usage Page (Generic Desktop),
    0x09, 0x02, // Usage (Mouse),
    0xA1, 0x01, // Collection (Application),
    0x85, HID_MOUSE_GENERIC + HID_OFFSET,
    0x09, 0x01, // Usage (Pointer),
    0xA1, 0x00, // Collection (Physical),
    0x05, 0x09, // Usage Page (Buttons),
    0x19, 0x01, // Usage Minimum (01),
    0x29, 0x03, // Usage Maximun (03),
    0x15, 0x00, // Logical Minimum (0),
    0x25, 0x01, // Logical Maximum (1),
    0x95, 0x03, // Report Count (3),
    0x75, 0x01, // Report Size (1),
    0x81, 0x02, // Input (Data, Variable, Absolute), ;3 button bits
    0x95, 0x01, // Report Count (1),
    0x75, 0x05, // Report Size (5),
    0x81, 0x03, // Input (Constant, Var, Abs), ;5 bit padding
    0x05, 0x01, // Usage Page (Generic Desktop),
    0x09, 0x30, // Usage (X),
    0x09, 0x31, // Usage (Y),
    0x15, 0x81, // Logical Minimum (-127),
    0x25, 0x7F, // Logical Maximum (127),
    0x75, 0x08, // Report Size (8),
    0x95, 0x02, // Report Count (2),
    0x81, 0x06, // Input (Data, Variable, Relative),2 position bytes (X,Y)
    0xC0,       // End Collection,
    0xC0,       // End Collection
#endif
    //-------------------------------------------------------------------------
#if SUPPORT_HID_ITE_I2EC_CTRL
    0x06, 0x85, 0xFF,   // Usage Page(Vender Defined Usage Page)
    0x09, 0x68,         // Usage (Vendor Usage 0x68)
    0xA1, 0x01,         // Collection (Application)
    0x85, HID_ITE_I2EC_REPORT_ID1 + HID_OFFSET, // Report ID (9)
    0x09, 0x01,         // Usage (Vendor Usage 0x01)
    0x15, 0x00,         // Logical Minimum (0)
    0x26, 0xFF, 0x00,   // Logical Maximum(255)
    0x75, 0x08,         // Report Size (8)
    0x95, HID_ITE_I2EC_REPORT_LENGTH1,  // Report Count (6)
    0xB1, 0x00,         // Feature (Data,Ary,Abs)

    0x85, HID_ITE_I2EC_REPORT_ID2 + HID_OFFSET, // Report ID (10)
    0x09, 0x01,         // USAGE (Vendor Usage 0x01)
    0x15, 0x00,         // Logical Minimum (0)
    0x26, 0xFF, 0x00,   // Logical Maximum(255)
    0x75, 0x08,         // Report Size (1)
    0x95, HID_ITE_I2EC_REPORT_LENGTH2,  // Report Count (128)
    0xB1, 0x00,         // Feature (Data,Ary,Abs)
    0xC0,       // End Collection
#endif
    //-------------------------------------------------------------------------
#if SUPPORT_HID_GENERAL_DESKTOP_CTRL
    0x05, 0x01, // Usage Page (Generic Desktop Control)
    0x09, 0x80, // Usage (System)
    0xA1, 0x01, // Collection (Application)
    0x85, HID_KB_MM_SYSTEM_FN_REPORT_ID + HID_OFFSET, // Report ID (5)
    0x19, 0x81, // Usage Minimum (129)
    0x29, 0x83, // Usage Maximum (131)
    0x15, 0x00, // Logical Minimum (0)
    0x25, 0x01, // Logical Maximum (1)
    0x95, 0x08, // Report Count (8)
    0x75, 0x01, // Report Size (1)
    0x81, 0x02, // Input(Data, Variable, Absolute)
    0xC0,       // End Collection
#endif
    //-------------------------------------------------------------------------
#if SUPPORT_HID_SYNAPTICS_TP
    0x05, 0x01, // Usage Page (Generic Desktop Ctrls)
    0x09, 0x02, // Usage (Mouse)
    0xA1, 0x01, // Collection (Application)
    0x85, 0x02, //  Report ID (2)
    0x09, 0x01, //  Usage (Pointer)
    0xA1, 0x00, //  Collection (Physical)
    0x05, 0x09, //   Usage Page (Button)
    0x19, 0x01, //   Usage Minimum (0x01)
    0x29, 0x02, //   Usage Maximum (0x02)
    0x15, 0x00, //   Logical Minimum (0)
    0x25, 0x01, //   Logical Maximum (1)
    0x75, 0x01, //   Report Size (1)
    0x95, 0x02, //   Report Count (2)
    0x81, 0x02, //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x06, //   Report Count (6)
    0x81, 0x01, //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01, //   Usage Page (Generic Desktop Ctrls)
    0x09, 0x30, //   Usage (X)
    0x09, 0x31, //   Usage (Y)
    0x15, 0x81, //   Logical Minimum (-127)
    0x25, 0x7F, //   Logical Maximum (127)
    0x75, 0x08, //   Report Size (8)
    0x95, 0x02, //   Report Count (2)
    0x81, 0x06, //   Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,       //  End Collection
    0xC0,       // End Collection
    //-------------------------------------------------------------------------
    0x05, 0x0D, // Usage Page (Digitizer)
    0x09, 0x05, // Usage (Touch Pad)
    0xA1, 0x01, // Collection (Application)
    0x85, 0x03, // Report ID (3)
    0x05, 0x0D, // Usage Page (Digitizer)
    0x09, 0x22, // Usage (Finger)
    0xA1, 0x02, // Collection (Logical)
    0x15, 0x00, //  Logical Minimum (0)
    0x25, 0x01, //  Logical Maximum (1)
    0x09, 0x47, //  Usage (0x47)
    0x09, 0x42, //  Usage (Tip Switch)
    0x95, 0x02, //  Report Count (2)
    0x75, 0x01, //  Report Size (1)
    0x81, 0x02, //  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01, //  Report Count (1)
    0x75, 0x03, //  Report Size (3)
    0x25, 0x05, //  Logical Maximum (5)
    0x09, 0x51, //  Usage (0x51)
    0x81, 0x02, //  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x01, //  Report Size (1)
    0x95, 0x03, //  Report Count (3)
    0x81, 0x03, //  Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01, //  Usage Page (Generic Desktop Ctrls)
    0x15, 0x00, //  Logical Minimum (0)
    0x26, 0xC3, 0x04, // Logical Maximum (1219)
    0x75, 0x10, // Report Size (16)
    0x55, 0x0E, // Unit Exponent (-2)
    0x65, 0x11, // Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30, // Usage (X)
    0x35, 0x00, // Physical Minimum (0)
    0x46, 0xF8, 0x03, // Physical Maximum (1016)
    0x95, 0x01, // Report Count (1)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0x9A, 0x02, // Physical Maximum (666)
    0x26, 0x1F, 0x03, // Logical Maximum (799)
    0x09, 0x31, // Usage (Y)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,       // End Collection
    //-------------------------------------------------------------------------
    0x05, 0x0D, // Usage Page (Digitizer)
    0x09, 0x22, // Usage (Finger)
    0xA1, 0x02, // Collection (Logical)
    0x15, 0x00, //  Logical Minimum (0)
    0x25, 0x01, //  Logical Maximum (1)
    0x09, 0x47, //  Usage (0x47)
    0x09, 0x42, //  Usage (Tip Switch)
    0x95, 0x02, //  Report Count (2)
    0x75, 0x01, //  Report Size (1)
    0x81, 0x02, //  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01, //  Report Count (1)
    0x75, 0x03, //  Report Size (3)
    0x25, 0x05, //  Logical Maximum (5)
    0x09, 0x51, //  Usage (0x51)
    0x81, 0x02, //  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x01, //  Report Size (1)
    0x95, 0x03, //  Report Count (3)
    0x81, 0x03, //  Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01, //  Usage Page (Generic Desktop Ctrls)
    0x15, 0x00, //  Logical Minimum (0)
    0x26, 0xC3, 0x04, // Logical Maximum (1219)
    0x75, 0x10, // Report Size (16)
    0x55, 0x0E, // Unit Exponent (-2)
    0x65, 0x11, // Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30, // Usage (X)
    0x35, 0x00, // Physical Minimum (0)
    0x46, 0xF8, 0x03, // Physical Maximum (1016)
    0x95, 0x01, // Report Count (1)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0x9A, 0x02, // Physical Maximum (666)
    0x26, 0x1F, 0x03, // Logical Maximum (799)
    0x09, 0x31, // Usage (Y)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,       // End Collection
    //-------------------------------------------------------------------------
    0x05, 0x0D, //Usage Page (Digitizer)
    0x09, 0x22, //Usage (Finger)
    0xA1, 0x02, //Collection (Logical)
    0x15, 0x00, // Logical Minimum (0)
    0x25, 0x01, // Logical Maximum (1)
    0x09, 0x47, // Usage (0x47)
    0x09, 0x42, // Usage (Tip Switch)
    0x95, 0x02, // Report Count (2)
    0x75, 0x01, // Report Size (1)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01, // Report Count (1)
    0x75, 0x03, // Report Size (3)
    0x25, 0x05, // Logical Maximum (5)
    0x09, 0x51, // Usage (0x51)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x01, // Report Size (1)
    0x95, 0x03, // Report Count (3)
    0x81, 0x03, // Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01, // Usage Page (Generic Desktop Ctrls)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xC3, 0x04, // Logical Maximum (1219)
    0x75, 0x10, // Report Size (16)
    0x55, 0x0E, // Unit Exponent (-2)
    0x65, 0x11, // Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30, // Usage (X)
    0x35, 0x00, // Physical Minimum (0)
    0x46, 0xF8, 0x03, // Physical Maximum (1016)
    0x95, 0x01, // Report Count (1)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0x9A, 0x02, // Physical Maximum (666)
    0x26, 0x1F, 0x03, // Logical Maximum (799)
    0x09, 0x31, // Usage (Y)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,       // End Collection
    //-------------------------------------------------------------------------
    0x05, 0x0D, // Usage Page (Digitizer)
    0x09, 0x22, // Usage (Finger)
    0xA1, 0x02, // Collection (Logical)
    0x15, 0x00, //  Logical Minimum (0)
    0x25, 0x01, //  Logical Maximum (1)
    0x09, 0x47, //  Usage (0x47)
    0x09, 0x42, //  Usage (Tip Switch)
    0x95, 0x02, //  Report Count (2)
    0x75, 0x01, //  Report Size (1)
    0x81, 0x02, //  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01, //  Report Count (1)
    0x75, 0x03, //  Report Size (3)
    0x25, 0x05, //  Logical Maximum (5)
    0x09, 0x51, //  Usage (0x51)
    0x81, 0x02, //  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x01, //  Report Size (1)
    0x95, 0x03, //  Report Count (3)
    0x81, 0x03, //  Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01, //  Usage Page (Generic Desktop Ctrls)
    0x15, 0x00, //  Logical Minimum (0)
    0x26, 0xC3, 0x04, // Logical Maximum (1219)
    0x75, 0x10, // Report Size (16)
    0x55, 0x0E, // Unit Exponent (-2)
    0x65, 0x11, // Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30, // Usage (X)
    0x35, 0x00, // Physical Minimum (0)
    0x46, 0xF8, 0x03, // Physical Maximum (1016)
    0x95, 0x01, // Report Count (1)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0x9A, 0x02, // Physical Maximum (666)
    0x26, 0x1F, 0x03, // Logical Maximum (799)
    0x09, 0x31, // Usage (Y)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,       // End Collection
    0x05, 0x0D, // Usage Page (Digitizer)
    0x09, 0x22, // Usage (Finger)
    0xA1, 0x02, // Collection (Logical)
    0x15, 0x00, //  Logical Minimum (0)
    0x25, 0x01, //  Logical Maximum (1)
    0x09, 0x47, //  Usage (0x47)
    0x09, 0x42, //  Usage (Tip Switch)
    0x95, 0x02, //  Report Count (2)
    0x75, 0x01, //  Report Size (1)
    0x81, 0x02, //  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01, //  Report Count (1)
    0x75, 0x03, //  Report Size (3)
    0x25, 0x05, //  Logical Maximum (5)
    0x09, 0x51, //  Usage (0x51)
    0x81, 0x02, //  Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x01, //  Report Size (1)
    0x95, 0x03, //  Report Count (3)
    0x81, 0x03, //  Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01, //  Usage Page (Generic Desktop Ctrls)
    0x15, 0x00, //  Logical Minimum (0)
    0x26, 0xC3, 0x04, // Logical Maximum (1219)
    0x75, 0x10, // Report Size (16)
    0x55, 0x0E, // Unit Exponent (-2)
    0x65, 0x11, // Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30, // Usage (X)
    0x35, 0x00, // Physical Minimum (0)
    0x46, 0xF8, 0x03, // Physical Maximum (1016)
    0x95, 0x01, // Report Count (1)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0x9A, 0x02, // Physical Maximum (666)
    0x26, 0x1F, 0x03, // Logical Maximum (799)
    0x09, 0x31, // Usage (Y)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,       // End Collection
    0x05, 0x0D, // Usage Page (Digitizer)
    0x55, 0x0C, // Unit Exponent (-4)
    0x66, 0x01, 0x10, // Unit (System: SI Linear, Time: Seconds)
    0x47, 0xFF, 0xFF, 0x00, 0x00, // Physical Maximum (65534)
    0x27, 0xFF, 0xFF, 0x00, 0x00, // Logical Maximum (65534)
    0x75, 0x10, // Report Size (16)
    0x95, 0x01, // Report Count (1)
    0x09, 0x56, // Usage (0x56)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x54, // Usage (0x54)
    0x25, 0x7F, // Logical Maximum (127)
    0x95, 0x01, // Report Count (1)
    0x75, 0x08, // Report Size (8)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x09, // Usage Page (Button)
    0x09, 0x01, // Usage (0x01)
    0x25, 0x01, // Logical Maximum (1)
    0x75, 0x01, // Report Size (1)
    0x95, 0x01, // Report Count (1)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x07, // Report Count (7)
    0x81, 0x03, // Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0D, // Usage Page (Digitizer)
    0x85, 0x08, // Report ID (8)
    0x09, 0x55, // Usage (0x55)
    0x09, 0x59, // Usage (0x59)
    0x75, 0x04, // Report Size (4)
    0x95, 0x02, // Report Count (2)
    0x25, 0x0F, // Logical Maximum (15)
    0xB1, 0x02, // Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x0D, // Report ID (13)
    0x09, 0x60, // Usage (0x60)
    0x75, 0x01, // Report Size (1)
    0x95, 0x01, // Report Count (1)
    0x15, 0x00, // Logical Minimum (0)
    0x25, 0x01, // Logical Maximum (1)
    0xB1, 0x02, // Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x95, 0x07, // Report Count (7)
    0xB1, 0x03, // Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x07, // Report ID (7)
    0x06, 0x00, 0xFF, // Usage Page (Vendor Defined 0xFF00)
    0x09, 0xC5, // Usage (0xC5)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08, // Report Size (8)
    0x96, 0x00, 0x01, // Report Count (256)
    0xB1, 0x02, // Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,       // End Collection
    0x05, 0x0D, // Usage Page (Digitizer)
    0x09, 0x0E, // Usage (0x0E)
    0xA1, 0x01, // Collection (Application)
    0x85, 0x04, //  Report ID (4)
    0x09, 0x22, //  Usage (Finger)
    0xA1, 0x02, //  Collection (Logical)
    0x09, 0x52, //  Usage (0x52)
    0x15, 0x00, //  Logical Minimum (0)
    0x25, 0x0A, //  Logical Maximum (10)
    0x75, 0x08, //  Report Size (8)
    0x95, 0x01, //  Report Count (1)
    0xB1, 0x02, //  Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,       // End Collection
    //-------------------------------------------------------------------------
    0x09, 0x22, // Usage (Finger)
    0xA1, 0x00, // Collection (Physical)
    0x85, 0x06, //  Report ID (6)
    0x09, 0x57, //  Usage (0x57)
    0x09, 0x58, //  Usage (0x58)
    0x75, 0x01, //  Report Size (1)
    0x95, 0x02, //  Report Count (2)
    0x25, 0x01, //  Logical Maximum (1)
    0xB1, 0x02, //  Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x95, 0x06, //  Report Count (6)
    0xB1, 0x03, //  Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,       // End Collection
    0xC0,       // End Collection
    //-------------------------------------------------------------------------
    0x06, 0x00, 0xFF, // Usage Page (Vendor Defined 0xFF00)
    0x09, 0x01, // Usage (0x01)
    0xA1, 0x01, // Collection (Application)
    0x85, 0x09, // Report ID (9)
    0x09, 0x02, // Usage (0x02)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08, // Report Size (8)
    0x95, 0x14, // Report Count (20)
    0x91, 0x02, // Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x0A, // Report ID (10)
    0x09, 0x03, // Usage (0x03)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08, // Report Size (8)
    0x95, 0x14, // Report Count (20)
    0x91, 0x02, // Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x0B, // Report ID (11)
    0x09, 0x04, // Usage (0x04)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08, // Report Size (8)
    0x95, 0x3D, // Report Count (61)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x0C, // Report ID (12)
    0x09, 0x05, // Usage (0x05)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08, // Report Size (8)
    0x95, 0x3D, // Report Count (61)
    0x81, 0x02, // Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x0F, // Report ID (15)
    0x09, 0x06, // Usage (0x06)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08, // Report Size (8)
    0x95, 0x03, // Report Count (3)
    0xB1, 0x02, // Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x0E, // Report ID (14)
    0x09, 0x07, // Usage (0x07)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xFF, 0x00, // Logical Maximum (255)
    0x75, 0x08, // Report Size (8)
    0x95, 0x01, // Report Count (1)
    0xB1, 0x02, // Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,       // End Collection
#endif  //SUPPORT_HID_SYNAPTICS_TP
};

//-----------------------------------------------------------------------------
#define wReportDescLengthL  (sizeof(Report_Descriptor) & 0xFF)
#define wReportDescLengthH  (sizeof(Report_Descriptor) >> 8)
//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
 * HID over I2C - HID Descriptor Layout
 *---------------------------------------------------------------------------*/
const unsigned char HID_Descriptor_Layout[] =
{
    wHIDDescLength,         wHIDDescLength >> 8,
    (bcdVersion & 0xFF),             bcdVersion >> 8,
    wReportDescLengthL,     wReportDescLengthH,
    wReportDescRegister,    wReportDescRegister >> 8,
    wInputRegister,         wInputRegister >> 8,
    wMaxInputLength,        wMaxInputLength >> 8,
    wOutputRegister,        wOutputRegister >> 8,
    wMaxOutputLength,       wMaxOutputLength >> 8,
    wCommandRegister,       wCommandRegister >> 8,
    wDataRegister,          wDataRegister >> 8,
    (wVendorID & 0xFF),              wVendorID >> 8,
    (wProductID & 0xFF),             wProductID >> 8,
    wVersionID,             wVersionID >> 8,
    wReserved,              wReserved >> 8,
    wReserved,              wReserved >> 8,
};
//-----------------------------------------------------------------------------
#define wHIDDescriptorLayoutLength  (sizeof(HID_Descriptor_Layout) - 1)

#if UNUSED
//-----------------------------------------------------------------------------
//*****************************************************************************
// CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - SettingTimer1
 * @function - Setting Timer1
 * @Upstream - By call
 * @input    - SET_TMR
 * @return   - None
 * @note     - None
 */
void SettingTimer1(WORD SET_TMR)
{
    TR1 = 0;                // Disable timer1
    ET1 = 0;                // Disable timer1 interrupt
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TH1 = SET_TMR >> 8;     // Set timer1 counter 30ms
    TL1 = SET_TMR;          // Set timer1 counter 30ms
    TF1 = 0;                // Clear overflow flag
    TR1 = 1;                // Enable timer1
}

/*-----------------------------------------------------------------------------
 * @subroutine - Init_HID_Keyboard
 * @function - Init_HID_Keyboard
 * @upstream - By Call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Init_HID_Keyboard(void)
{

}
#endif
/*-----------------------------------------------------------------------------
 * @subroutine - Send_HID_Interrupt
 * @function - Send HID Interrupt
 * @upstream - By Call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Send_HID_Interrupt(void)
{
    if (IS_MASK_CLEAR(HID_DeviceActived, F_HID_REPORT_DESC))
    {
        return;
    }
#if 1
    Hid_Interrupt_Pin_Toggle();
#else
    INTERRUPT_HID_LO();
    WNCKR = 0x00;
    WNCKR = 0x00;
    WNCKR = 0x00;
    INTERRUPT_HID_HI();
#endif

#if 0
#if 1
    INTERRUPT_HID_ON();
#else
    if (HID_InterruptMode == _HID_INTR_LEVEL)
    {
        INTERRUPT_HID_ON();
        return;
    }
    DisableAllInterrupt();
    INTERRUPT_HID_ON();
    WNCKR = 0x00;
    WNCKR = 0x00;
    WNCKR = 0x00;
    INTERRUPT_HID_OFF();
    EA = 1; //EnableAllInterrupt();
    F_HID_WaitHost = 1;
    HID_WaitHostTimer = 20;
#endif
#endif
}
#if UNUSED
/*-----------------------------------------------------------------------------
 * @subroutine - Read_HID_DeviceA
 * @function - Read_HID_DeviceA
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Read_HID_DeviceA(void)
{
    /* From Host HID Read Protocol */
    if ((HID_wRegIndex_A == _HID_DESC_LAYOUT) ||
        (HID_wRegIndex_A == _HID_DESC_LAYOUT2))
    {
        /* Device Descriptor Constants */
        ITempB01 = HID_Descriptor_Layout[HID_RdIdxA];
        ITempB02 = ITempB01;
        SLDA_A = ITempB01;
        SLDA_A = ITempB02;
        SCIEVT_ENABLED = 0;
        HID_HandshakeBusy = 10;
        if (HID_RdIdxA >= wHIDDescriptorLayoutLength)
        {
            HID_DeviceActived = F_HID_DESC_LAYOUT;
            
        }
        else
        {
            HID_DeviceActived = 0;
        }
        HID_RdIdxA++;
    }
    else if (HID_wRegIndex_A == _REPORT_DESC_REG)
    {
        /* Device Report Descriptor Details */
        ITempB01 = Report_Descriptor[HID_RdIdxA];
        ITempB02 = ITempB01;
        SLDA_A = ITempB01;
        SLDA_A = ITempB02;
        if (HID_RdIdxA >= (wReportDescLengthL - 1))
        {
            HID_DeviceActived |= F_HID_REPORT_DESC;
            SCIEVT_ENABLED = 1;
            HID_HandshakeBusy = 10;
        }
        HID_RdIdxA++;
    }
    else if (HID_wRegIndex_A == _HID_COMMAND_REG)
    {
        if (HID_RdIdxA < 3)
        {
            /* Device Report Descriptor Details */
            ITempB01 = HID_DevReportBuf[HID_RdIdxA];
            ITempB02 = ITempB01;
        }
        else if (HID_i2ecMode == 0)
        {
            ITempB01 = *HID_XPntr;
            ITempB02 = ITempB01;
            HID_XPntr++;
        }
        else if (HID_i2ecMode == 1)
        {
            ITempB01 = *HID_XPntr;
            ITempB02 = ITempB01;
            HID_XPntr++;
        }
        else if (HID_i2ecMode == 2)
        {
#pragma asm
            MOV R1, #0BAH
            MOV A, @R1
            MOV R0, A
            MOV A, @R0
            MOV R1, #065H
            MOV @R1, A
#pragma endasm
            //ITempB01 = *HID_XPntr;
            ITempB02 = ITempB01;
            HID_XPntr++;
        }
        SLDA_A = ITempB01;
        SLDA_A = ITempB02;
        HID_RdIdxA++;
    }
    else
    {
        if (HID_DescriptorID == 0)
        {
            /* Input Report of KB */
            if (HID_ReportType == _KB_INPUT_REPORT)
            {
                if (HID_OutBuf_A[0] > 0)
                {
                    ITempB01 = HID_OutBuf_A[HID_RdIdxA];
                    ITempB02 = ITempB01;
                    SLDA_A = ITempB01;
                    SLDA_A = ITempB02;
                }
                else
                {
                    SLDA_A = 0x00;
                    SLDA_A = 0x00;
                }
                HID_RdIdxA++;

                if (HID_RdIdxA >= HID_OutBuf_A[0])
                {
                    HID_OutBuf_A[0] = 0;
                    HID_ReportType = 0;
                }
            }
            else
            {
                /* Null data */
                SLDA_A = 0x00;
                SLDA_A = 0x00;
            }
        }
#if SUPPORT_HID_SYNAPTICS_TP
        if (HID_DescriptorID == 1)
        {
            //TODO:
        }
        else if (HID_DescriptorID == 2)
        {
            //TODO:
        }
#endif
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_HID_OPCodeRead
 * @function - Process_HID OP Code Read
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Process_HID_OPCodeRead(void)
{
    if (HID_InBuf_A[4] == (HID_ITE_I2EC_REPORT_ID1 + HID_OFFSET))
    {
        //HID_ITE_I2EC_REPORT_ID1+HID_OFFSET
        HID_DevReportBuf[0] = HID_ITE_I2EC_REPORT_LENGTH1 + 3;
        HID_DevReportBuf[1] = 0;
        HID_DevReportBuf[2] = HID_ITE_I2EC_REPORT_ID1 + HID_OFFSET;
        return;
    }
    if (HID_InBuf_A[4] == (HID_ITE_I2EC_REPORT_ID2 + HID_OFFSET))
    {
        //HID_ITE_I2EC_REPORT_ID1+HID_OFFSET
        HID_DevReportBuf[0] = HID_ITE_I2EC_REPORT_LENGTH2 + 3;
        HID_DevReportBuf[1] = 0;
        HID_DevReportBuf[2] = HID_ITE_I2EC_REPORT_ID2 + HID_OFFSET;
        return;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_HID_OPCodeWrite
 * @function - Process HID OP Code Write
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 * OS HID - ITE I2EC Feature
 *
 */
void Process_HID_OPCodeWrite(void)
{
    if (HID_InBuf_A[4] == (HID_ITE_I2EC_REPORT_ID1 + HID_OFFSET))
    {
        /* HID_InBuf_A[10] = ITE Command
                             [81]:Send Address + Write
                             [80]:Set Read Address
                             [BB]:Jump BootBlock
           HID_InBuf_A[11] = Address High Byte
           HID_InBuf_A[12] = Address Low Byte
           HID_InBuf_A[13] = Length 0~4
           HID_InBuf_A[14]..[17] = Data
        */
        if (HID_WrIdxA == (HID_ITE_I2EC_REPORT_LENGTH1 + 9))
        {
            HID_XPntr = ((HID_InBuf_A[11] << 8) + HID_InBuf_A[12]);
            ITempB01 = HID_InBuf_A[10];
            if (ITempB01 == 0x81)
            {
                ITempB02 = HID_InBuf_A[13];
                if (ITempB02 >= 4)      /* Max Length = 4 */
                {
                    ITempB02 = 4;
                }
                ITempB03 = 14;
                while (1)
                {
                    if (ITempB02 == 0)
                    {
                        break;
                    }
                    *HID_XPntr = HID_InBuf_A[ITempB03];
                    HID_XPntr++;
                    ITempB02--;
                    ITempB03++;
                }
                HID_InBuf_A[10] = 0x00;
            }
            else if (ITempB01 == 0x80)
            {
                HID_i2ecMode = 0;
                if (HID_InBuf_A[11] == 0x80)        //uC SFR
                {
                    HID_i2ecMode = 1;
                }
                else if (HID_InBuf_A[11] == 0xC0)   //uC RAM
                {
                    HID_i2ecMode = 2;
                }
                HID_InBuf_A[10] = 0x00;
            }
            else if (ITempB01 == _CMD_ACPI_HID_SPI_COMMAND) //0xBB
            {
                HID_BB_Command = HID_InBuf_A[11];
                xFSH_Command = HID_InBuf_A[12];
                xFSH_Position = HID_InBuf_A[13];
                xFSH_AddrL = HID_InBuf_A[14];
                xFSH_AddrM = HID_InBuf_A[15];
                xFSH_AddrH = HID_InBuf_A[16];
            }
        }
        return;
    }
    if (HID_InBuf_A[4] == (HID_ITE_I2EC_REPORT_ID2 + HID_OFFSET))
    {
        //HID_ITE_I2EC_REPORT_ID2+HID_OFFSET
        if (HID_WrIdxA == (HID_ITE_I2EC_REPORT_LENGTH2 + 10))
        {
            HID_i2ecMode = 0;
            /* Write 64 Bytes */
            ITempB02 = 64;
            ITempB03 = 10;
            while (1)
            {
                if (ITempB02 == 0)
                {
                    break;
                }
                *HID_XPntr = HID_InBuf_A[ITempB03];
                HID_XPntr++;
                ITempB02--;
                ITempB03++;
            }
        }
        return;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_HID_OPCode
 * @function - Process HID OPCode
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Process_HID_OPCode(void)
{
    HID_RegOPCode = (HID_InBuf_A[3] & 0x0F);
    if (HID_RegOPCode == _HID_OPCODE_READ)          //02
    {
        /* Get Feature */
        Process_HID_OPCodeRead();
        return;
    }
    else if (HID_RegOPCode == _HID_OPCODE_WRITE)    //03
    {
        /* Set Feature */
        Process_HID_OPCodeWrite();
        return;
    }
    else if (HID_RegOPCode == _HID_OPCODE_RESET)    //01
    {
        HID_DeviceActived |= F_HID_OPCODE_RESET;
        Init_HID_Keyboard();
        for (ITempB01 = 0; ITempB01 < _HID_OUT_BUF1_LEN; ITempB01++)
        {
            HID_OutBuf_A[ITempB01] = 0;
        }
        HID_ReportType = _KB_INPUT_REPORT;
        HID_DescriptorID = 0;
        HID_InterruptMode = 0;
        /* Interrupt Pulse Trigger */
        INTERRUPT_HID_LO();
        //WNCKR = 0x00;
        //WNCKR = 0x00;
        //WNCKR = 0x00;
        //WNCKR = 0x00;
        WNCKR = 0x00;
        WNCKR = 0x00;
        WNCKR = 0x00;
        INTERRUPT_HID_HI();
        return;
    }
    else if (HID_RegOPCode == _HID_OPCODE_SET_POWER)    //08
    {
        HID_DeviceActived |= F_HID_OPCODE_SET_POWER;
        /* BYTE#2: Power State: On(00) SLEEP (01) */
        HID_PowerState = HID_InBuf_A[2];
#if 1   /* Reserved, Please use HID_PowerState for global control. */
        if (HID_InBuf_A[2] == 0x00)
        {
            HID_DeviceActived &= ~(F_HID_OPCODE_SET_POWER_SLEEP);
            HID_DeviceActived |= F_HID_OPCODE_SET_POWER_ON;
        }
        if (HID_InBuf_A[2] == 0x01)
        {
            HID_DeviceActived &= ~(F_HID_OPCODE_SET_POWER_ON);
            HID_DeviceActived |= F_HID_OPCODE_SET_POWER_SLEEP;
        }
#endif
        return;
    }
#if SUPPORT_HID_SYNAPTICS_TP
    if (HID_InBuf_A[2] == 0x38)
    {
        HID_DescriptorID = 0x01;
    }
    else if (HID_InBuf_A[2] == 0x37)
    {
        HID_DescriptorID = 0x02;
    }
    else
    {
        HID_DescriptorID = 0x00;
    }
#endif
#ifdef  SUPPORT_HOOK_OEM_HID_OPCODE
    HID_RegReportID = (HID_InBuf_A[2] & 0x0F);
    HID_RegReportType = ((HID_InBuf_A[2] >> 4) & 0x0F);
    Hook_Oem_HID_OPCode();
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_HID_Registers
 * @function - Process_HID_Registers
 * @upstream - Process_SlaveHID()
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Process_HID_Registers(void)
{
#if 1   /* Fast Process */
    if (HID_wRegIndex_A == _HID_COMMAND_REG)    //0x0022
    {
        if (HID_WrIdxA > 0x03)
        {
            Process_HID_OPCode();
        }
        return;
    }
    if (HID_wRegIndex_A == _HID_OUTPUT_REG)
    {
#if SUPPORT_HID_KEYBOARD_LED
        /* OUTPUT REPORT */
        if (HID_WrIdxA > 0x05)  /* 6 byte or more */
        {
            /* ID = 1; */
            if (HID_InBuf_A[4] == (HID_KB_GENERIC + HID_OFFSET))
            {
                /* Keyboard LED */
                ITempB02 = HID_InBuf_A[5];

                //if (IS_MASK_SET(ITempB02, BIT(0)))
                //{
                //    //Hook_NUMLED_ON();
                //}
                //else
                //{
                //    //Hook_NUMLED_OFF();
                //}
                if (IS_MASK_SET(ITempB02, BIT(1)))
                {
                    //Hook_CAPLED_ON();
                    EC_CAP_LED_EN_HI();
                    SET_MASK(xDBG_UartDisp2, BIT6);
                }
                else
                {
                    //Hook_CAPLED_OFF();
                    EC_CAP_LED_EN_LO();
                    SET_MASK(xDBG_UartDisp2, BIT7);                    
                }
            }
        }
#endif
        return;
    }
    if ((HID_wRegIndex_A == _HID_DESC_LAYOUT) ||
            (HID_wRegIndex_A == _HID_DESC_LAYOUT2) ||
            (HID_wRegIndex_A == _REPORT_DESC_REG) ||
            (HID_wRegIndex_A == _HID_INPUT_REG) ||
            (HID_wRegIndex_A == _HID_DATA_REG))
    {
        if((HID_wRegIndex_A == _HID_DESC_LAYOUT) ||
            (HID_wRegIndex_A == _HID_DESC_LAYOUT2))
        {
            HID_DeviceActived = 0;
        }
        return;
    }
    HID_WrIdxA = 0x0000;
#else
    switch (HID_wRegIndex_A)
    {
    case _HID_DESC_LAYOUT:      //0x0001
    case _HID_DESC_LAYOUT2:     //0x0020
    case _REPORT_DESC_REG:      //0x0021
    case _HID_INPUT_REG:        //0x0024
        break;

    case _HID_OUTPUT_REG:       //0x0017
        /* OUTPUT REPORT */
        if (HID_WrIdxA > 0x05)  /* 6 byte or more */
        {
            HID_DeviceActived |= F_HID_KB_LED_UPDATE;
            /* ID = 1; */
            if (HID_InBuf_A[4] == (HID_KB_GENERIC + HID_OFFSET))
            {
                /* Keyboard LED */
                ITempB02 = HID_InBuf_A[5];

                if (IS_MASK_SET(ITempB02, BIT(0)))
                {
                    Hook_NUMLED_ON();
                }
                else
                {
                    Hook_NUMLED_OFF();
                }

                if (IS_MASK_SET(ITempB02, BIT(1)))
                {
                    Hook_CAPLED_ON();
                }
                else
                {
                    Hook_CAPLED_OFF();
                }
            }
        }
        break;

    case _HID_COMMAND_REG:      //0x0022
        if (HID_WrIdxA > 0x03)
        {
            Process_HID_OPCode();
        }
        break;

    case _HID_DATA_REG:
        break;

    default:
        HID_WrIdxA = 0x0000;
        break;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Write_HID_DeviceA
 * @function - Write_HID_DeviceA
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Write_HID_DeviceA(void)
{
    /* From Host HID Write Protocol */
    if (ChannelIsSlaveB)
    {
        ITempB01 = SLDA_B;
        ITempB02 = SLDA_B; /* Release Clock Pin */
    }
    else
    {
        ITempB01 = SLDA_A;
        ITempB02 = SLDA_A; /* Release Clock Pin */
    }
    HID_RdIdxA = 0;

    if (HID_WrIdxA < (_HID_IN_BUF_LEN + 1))
    {
        HID_InBuf_A[HID_WrIdxA] = ITempB01;
        //HID_RamDebug(0xCC);
        //HID_RamDebug(ITempB01);
        HID_WrIdxA++;

        if (HID_WrIdxA > 1)
        {
            /* 16 Bits Index(Command) */
            HID_wRegIndex_A = (WORD)((HID_InBuf_A[1] << 8) +
                                     HID_InBuf_A[0]);
            Process_HID_Registers();
        }
    }
    else
    {
        HID_WrIdxA++;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Read_ACPI_DeviceA
 * @function - Read_ACPI_DeviceA
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Read_ACPI_DeviceA(void)
{
#if SUPPORT_CHANNEL_AB_SAME_ACPI
    /* From Host ACPI Read Protocol */
    ITempB01 = AcpiReadData_I2C_AB(PMC_RdIdx);
    SLDA_A = ITempB01;  /* Send Data */
    SLDA_A = ITempB01;  /* Release Clock Pin */
    PMC_RdIdx++;
#else
    /* From Host ACPI Read Protocol */
    ITempB01 = AcpiReadData_I2C_A(HID_RdIdxA);
    SLDA_A = ITempB01;  /* Send Data */
    SLDA_A = ITempB01;  /* Release Clock Pin */
    HID_RdIdxA++;
#endif    
}

/*-----------------------------------------------------------------------------
 * @subroutine - Write_ACPI_DeviceA
 * @function - Write_ACPI_DeviceA
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Write_ACPI_DeviceA(void)
{
#if SUPPORT_CHANNEL_AB_SAME_ACPI
    /* From Host ACPI Write Protocol */
    ITempB01 = SLDA_A;  /* Receive Data */
    ITempB02 = SLDA_A;  /* Release Clock Pin */
    AcpiWriteData_I2C_AB(PMC_WrIdx, ITempB01);
    PMC_WrIdx++;
#else
    /* From Host ACPI Write Protocol */
    ITempB01 = SLDA_A;  /* Receive Data */
    ITempB02 = SLDA_A;  /* Release Clock Pin */
    AcpiWriteData_I2C_A(HID_WrIdxA, ITempB01);
    HID_WrIdxA++;
#endif    
}

/*-----------------------------------------------------------------------------
 * @subroutine - Enter_ITE_Predefine
 * @function - Enter_ITE_Predefine
 * @Upstream - By call (INT)
 * @input    - None
 * @return   - None
 * @note     - None
 */
//#pragma ot(7, SIZE)
//void Enter_ITE_Predefine(void)
//{
//    FLHCTRL3R = 0x08;   //non-tristate
//    HINSTC2 = 0x00;
//    RESLADR_2_A = 0x80 + 0x5B;
//    HOCTL2_A = 0x20;
//    SCLKTS_A = 0x04;
//    RESLADR_2_B = 0x80 + 0x5B;
//    HOCTL2_B = 0x20;
//    SCLKTS_B = 0x04;
//    SET_MASK(SMECCS, HOSTWA);
//    SET_MASK(SADFPCTL, HSAPE);  //Pre Define Enable
//    ChangePLLFrequency(_PLL_FREQ_18_4_MHZ);
//    RSTS = 0x40;
//#if 1   //SUPPORT_PWRSW_RESET
//    GCR10 = PWRSW_WDT2_12S;
//    GCR9 |= PWSW2EN2;
//#endif
//    DisableAllInterrupt();      // Disable all interrupt
//    while (1)
//    {
//        ;
//    }
//}

//-----------------------------------------------------------------------------
#pragma ot(8, SPEED)
/*-----------------------------------------------------------------------------
 * @subroutine - service_SlaveI2C_A
 * @function - I2C Salve Channel-A data service
 * @Upstream - By call (INT)
 * @input    - None
 * @return   - None
 * @note     - SMCLK2/GPF.6, SMDAT2/GPF.7 (SWAP)
 */
void service_SlaveI2C_A(void)
{
    I2C_Tag = 0;
    HID_RdIdxA = 0;
    HID_WrIdxA = 0;
    PMC_RdIdx = 0;
    PMC_WrIdx = 0;    
    ChannelIsSlaveB = 0;
    DisableAllInterrupt();
    SettingTimer1(Timer_26ms);
    //HID_RamDebug(0xCA);

    while (!TF1)
    {
        /* Stop condition Detected */
        if (IS_MASK_SET(SLSTA_A, SPDS))
        {
            I2C_Tag = 0xED;
            break;
        }
        /* Timeout Status */
        if (IS_MASK_SET(SLSTA_A, STS))
        {
            break;
        }
#if 0
        if (IS_MASK_SET(SLSTA_A, SSSLS))
        {
            CLEAR_MASK(HOCTL2_A, _SSCL);
            SET_MASK(HOCTL2_A, _SSCL);
            //break;
        }
#endif
        /* Slave data register is waiting for read or write */
        if (IS_MASK_SET(SLSTA_A, SDS))
        {
            /* Clear Status */
            SLSTA_A = SDS;
            /*
             * I2C Write to Read Cycle
             * EC send data to Host. 0: slave address, 1: slave address2
             */
            if (IS_MASK_SET(SLSTA_A, MSLA2))
            {
                /* ACPI Channel */
                /* RCS=1:Read by Host, RCS=0:Write by Host */
                if (IS_MASK_SET(SLSTA_A, RCS))
                {
                    Read_ACPI_DeviceA();
                }
                else
                {
                    Write_ACPI_DeviceA();
                }
            }
            else
            {
                /* HID Channel */
                /* RCS=1:Read by Host, RCS=0:Write by Host */
                if (IS_MASK_SET(SLSTA_A, RCS))
                {
                    Read_HID_DeviceA();
                }
                else
                {
                    Write_HID_DeviceA();
                }
            }
            /* Reset & Reload Timer1 */
            TH1 = Timer_26ms >> 8;
            TL1 = Timer_26ms;
            TF1 = 0;
        }
    }
    /* Clear Slave Bus Status */
#if 0
    SLSTA_A = SPDS + STS + SDS + HONOST;
#else
    SLSTA_A = SPDS + STS + SDS;
#endif
    TR1 = 0; /* Disable timer1 */
    TF1 = 0; /* Clear overflow flag */
    ET1 = 1; /* Enable timer1 interrupt */
#if 0
    /* Clear OutBuf */
    HID_OutBuf_A[0] = 0;
#endif
#if HID_UART_DEBUG_OUTPUT
    //if (HID_wRegIndex_A > 0)
    //{
    //    Main_UartDebug(2, HID_wRegIndex_A >> 8, HID_wRegIndex_A);
    //    HID_wRegIndex_A = 0;
    //}
#endif
    INTERRUPT_HID_HI();
    if (I2C_Tag == 0xED)
    {
#if SUPPORT_CHANNEL_AB_SAME_ACPI
        Hook_SlaveI2C_AB_Stop();
#else
        Hook_SlaveI2C_A_Stop();
#endif        
    }

    /* Enable HID Channel */
    ISR1 = Int_SMBUS0;
    IER1 |= Int_SMBUS0;

    /* Release Interrupt */
    EA = 1; //EnableAllInterrupt();
}
#endif // UNUSED
/*-----------------------------------------------------------------------------
 * @subroutine - Read_HID_DeviceB
 * @function - Read_HID_DeviceB
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Read_HID_DeviceB(uint8_t rbuff[], uint32_t *rlength)
{
#if SUPPORT_CHANNEL_B_HID
    /* From Host HID Read Protocol */
    if ((HID_wRegIndex_B == _HID_DESC_LAYOUT) ||
        (HID_wRegIndex_B == _HID_DESC_LAYOUT2))
    {
    #if NO_NEED
        /* Device Descriptor Constants */
        ITempB01 = HID_Descriptor_Layout[HID_RdIdxB];
        ITempB02 = ITempB01;
    
        SLDA_B = ITempB01;
        SLDA_B = ITempB02;

        if (HID_RdIdxB >= wHIDDescriptorLayoutLength)
        {
            HID_DeviceActived = F_HID_DESC_LAYOUT;
        }
        else
        {
            HID_DeviceActived = 0;         
        }
        HID_RdIdxB++;
    #else
        // output buffer set to HID_Descriptor_Layout
        *rlength = wHIDDescriptorLayoutLength + 1;
        memcpy(rbuff, HID_Descriptor_Layout, wHIDDescriptorLayoutLength);
    #endif 
        HID_DeviceActived = F_HID_DESC_LAYOUT;
        HID_RdIdxB = *rlength;
    }
    else if (HID_wRegIndex_B == _REPORT_DESC_REG)
    {
    #if NO_NEED
        /* Device Report Descriptor Details */
        ITempB01 = Report_Descriptor[HID_RdIdxB];
        ITempB02 = ITempB01;
    
        SLDA_B = ITempB01;
        SLDA_B = ITempB02;
        if (HID_RdIdxB >= (wReportDescLengthL - 1))
        {
            HID_DeviceActived |= F_HID_REPORT_DESC;
        }
        HID_RdIdxB++;
    #else
        // output buffer set to Report_Descriptor
        *rlength = sizeof(Report_Descriptor);
        memcpy(rbuff, Report_Descriptor, sizeof(Report_Descriptor));
    #endif 
        HID_DeviceActived |= F_HID_REPORT_DESC;
        HID_RdIdxB = wReportDescLengthL;
    }
    else if (HID_wRegIndex_B == _HID_COMMAND_REG)
    {
        if (HID_RdIdxB < 3)
        {
            /* Device Report Descriptor Details */
            ITempB01 = HID_DevReportBuf[HID_RdIdxB];
            ITempB02 = ITempB01;
        }
        else if (HID_i2ecMode == 0)
        {
            ITempB01 = *HID_XPntr;
            ITempB02 = ITempB01;
            HID_XPntr++;
        }
        else if (HID_i2ecMode == 1)
        {
            ITempB01 = *HID_XPntr;
            ITempB02 = ITempB01;
            HID_XPntr++;
        }
        else if (HID_i2ecMode == 2)
        {
#if 0
        #pragma asm
            MOV R1, #0BAH
            MOV A, @R1
            MOV R0, A
            MOV A, @R0
            MOV R1, #065H
            MOV @R1, A
        #pragma endasm
            //ITempB01 = *HID_XPntr;
            ITempB02 = ITempB01;
            HID_XPntr++;
#else
            I2EC_Mode();

#endif
        }
    #if NO_NEED
        SLDA_B = ITempB01;
        SLDA_B = ITempB02;
        HID_RdIdxB++;
    #endif // NO_NEED
    }
    else
    {
        if (HID_DescriptorID == 0)
        {
        #if NO_NEED
            /* Input Report of KB */
            if (HID_ReportType == _KB_INPUT_REPORT)
            {
                if (HID_OutBuf_B[0] > 0)
                {
                    ITempB01 = HID_OutBuf_B[HID_RdIdxB];
                    ITempB02 = ITempB01;
                    SLDA_B = ITempB01;
                    SLDA_B = ITempB02;
                }
                else
                {
                    SLDA_B = 0x00;
                    SLDA_B = 0x00;
                }
                HID_RdIdxB++;
            
                if (HID_RdIdxB >= HID_OutBuf_B[0])
                {
                    HID_OutBuf_B[0] = 0;
                    HID_ReportType = 0;
                }

            }
            else
            {
                /* Null data */
                SLDA_B = 0x00;
                SLDA_B = 0x00;
            }
        #endif
        }
#if SUPPORT_HID_SYNAPTICS_TP
        if (HID_DescriptorID == 1)
        {
            //TODO:
        }
        else if (HID_DescriptorID == 2)
        {
            //TODO:
        }
#endif
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_HID2_OPCodeRead
 * @function - Process_HID Bus-2 OP Code Read
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Process_HID2_OPCodeRead(void)
{  
    if (HID_InBuf_B[4] == (HID_ITE_I2EC_REPORT_ID1 + HID_OFFSET))
    {
        //HID_ITE_I2EC_REPORT_ID1+HID_OFFSET
        HID_DevReportBuf[0] = HID_ITE_I2EC_REPORT_LENGTH1 + 3;
        HID_DevReportBuf[1] = 0;
        HID_DevReportBuf[2] = HID_ITE_I2EC_REPORT_ID1 + HID_OFFSET;
        return;
    }
    if (HID_InBuf_B[4] == (HID_ITE_I2EC_REPORT_ID2 + HID_OFFSET))
    {
        //HID_ITE_I2EC_REPORT_ID1+HID_OFFSET
        HID_DevReportBuf[0] = HID_ITE_I2EC_REPORT_LENGTH2 + 3;
        HID_DevReportBuf[1] = 0;
        HID_DevReportBuf[2] = HID_ITE_I2EC_REPORT_ID2 + HID_OFFSET;
        return;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_HID2_OPCodeWrite
 * @function - Process HID Bus-2 OP Code Write
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 * OS HID - ITE I2EC Feature
 *
 */
void Process_HID2_OPCodeWrite(void)
{
    if (HID_InBuf_B[4] == (HID_ITE_I2EC_REPORT_ID1 + HID_OFFSET))
    {
        /* HID_InBuf_B[10] = ITE Command
                             [81]:Send Address + Write
                             [80]:Set Read Address
                             [BB]:Jump BootBlock
           HID_InBuf_B[11] = Address High Byte
           HID_InBuf_B[12] = Address Low Byte
           HID_InBuf_B[13] = Length 0~4
           HID_InBuf_B[14]..[17] = Data
        */
        if (HID_WrIdxB == (HID_ITE_I2EC_REPORT_LENGTH1 + 9))
        {
            HID_XPntr = (XWORD *)((HID_InBuf_B[11] << 8) + HID_InBuf_B[12]);
            ITempB01 = HID_InBuf_B[10];
            if (ITempB01 == 0x81)
            {
                ITempB02 = HID_InBuf_B[13];
                if (ITempB02 >= 4)      /* Max Length = 4 */
                {
                    ITempB02 = 4;
                }
                ITempB03 = 14;
                while (1)
                {
                    if (ITempB02 == 0)
                    {
                        break;
                    }
                    *HID_XPntr = HID_InBuf_B[ITempB03];
                    HID_XPntr++;
                    ITempB02--;
                    ITempB03++;
                }
                HID_InBuf_B[10] = 0x00;
            }
            else if (ITempB01 == 0x80)
            {
                HID_i2ecMode = 0;
                if (HID_InBuf_B[11] == 0x80)        //uC SFR
                {
                    HID_i2ecMode = 1;
                }
                else if (HID_InBuf_B[11] == 0xC0)   //uC RAM
                {
                    HID_i2ecMode = 2;
                }
                HID_InBuf_B[10] = 0x00;
            }
            else if (ITempB01 == _CMD_ACPI_HID_SPI_COMMAND)
            {
                HID_BB_Command = HID_InBuf_B[11];
                xFSH_Command = HID_InBuf_B[12];
                xFSH_Position = HID_InBuf_B[13];
                xFSH_AddrL = HID_InBuf_B[14];
                xFSH_AddrM = HID_InBuf_B[15];
                xFSH_AddrH = HID_InBuf_B[16];
            }
        }
        return;
    }
    if (HID_InBuf_B[4] == (HID_ITE_I2EC_REPORT_ID2 + HID_OFFSET))
    {
        //HID_ITE_I2EC_REPORT_ID2+HID_OFFSET
        if (HID_WrIdxB == (HID_ITE_I2EC_REPORT_LENGTH2 + 10))
        {
            HID_i2ecMode = 0;
            /* Write 64 Bytes */
            ITempB02 = 64;
            ITempB03 = 10;
            while (1)
            {
                if (ITempB02 == 0)
                {
                    break;
                }
                *HID_XPntr = HID_InBuf_B[ITempB03];
                HID_XPntr++;
                ITempB02--;
                ITempB03++;
            }
        }
        return;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_HID2_OPCode
 * @function - Process HID2 OPCode
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Process_HID2_OPCode(void)
{
    HID_RegOPCode = (HID_InBuf_B[3] & 0x0F);
    HID_RegReportID = (HID_InBuf_B[2] & 0x0F);
    HID_RegReportType = ((HID_InBuf_B[2] >> 4) & 0x0F);

    if (HID_RegOPCode == _HID_OPCODE_READ)          //02
    {
        /* Get Feature */
        Process_HID2_OPCodeRead();
        return;
    }
    else if (HID_RegOPCode == _HID_OPCODE_WRITE)    //03
    {
        /* Set Feature */
        Process_HID2_OPCodeWrite();
        return;
    }
    else if (HID_RegOPCode == _HID_OPCODE_RESET)    //01
    {
        HID_DeviceActived |= F_HID_OPCODE_RESET;

        Init_HID_Keyboard();

        for (ITempB01 = 0; ITempB01 < _HID_OUT_BUF1_LEN; ITempB01++)
        {
            HID_OutBuf_B[ITempB01] = 0;
        }

        HID_ReportType = _KB_INPUT_REPORT;
        HID_DescriptorID = 0;

 
        /* Interrupt Pulse Trigger */
    #if 1
        Hid_Interrupt_Pin_Toggle();
    #else
        INTERRUPT_HID_LO();


        WNCKR = 0x00;
        WNCKR = 0x00;
        WNCKR = 0x00;


        INTERRUPT_HID_HI();
    #endif
  
        return;
    }
    else if (HID_RegOPCode == _HID_OPCODE_SET_POWER)    //08
    {
        HID_DeviceActived |= F_HID_OPCODE_SET_POWER;
        /* BYTE#2: Power State: On(00) SLEEP (01) */
        HID_PowerState = HID_InBuf_B[2];
#if 1   /* Reserved, Please use HID_PowerState for global control. */
        if (HID_InBuf_B[2] == 0x00)
        {
            HID_DeviceActived &= ~(F_HID_OPCODE_SET_POWER_SLEEP);
            HID_DeviceActived |= F_HID_OPCODE_SET_POWER_ON;
        }
        if (HID_InBuf_B[2] == 0x01)
        {
            HID_DeviceActived &= ~(F_HID_OPCODE_SET_POWER_ON);
            HID_DeviceActived |= F_HID_OPCODE_SET_POWER_SLEEP;
        }
#endif
        return;
    }
#if SUPPORT_HID_SYNAPTICS_TP
    if (HID_InBuf_B[2] == 0x38)
    {
        HID_DescriptorID = 0x01;
    }
    else if (HID_InBuf_B[2] == 0x37)
    {
        HID_DescriptorID = 0x02;
    }
    else
    {
        HID_DescriptorID = 0x00;
    }
#endif
#ifdef  SUPPORT_HOOK_OEM_HID2_OPCODE
    HID_RegReportID = (HID_InBuf_B[2] & 0x0F);
    HID_RegReportType = ((HID_InBuf_B[2] >> 4) & 0x0F);
    Hook_Oem_HID2_OPCode();
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Process_HID2_Registers
 * @function - Process_HID2_Registers
 * @upstream - Process_SlaveHID()
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Process_HID2_Registers(void)
{
#if 1   /* Fast Process */
    if (HID_wRegIndex_B == _HID_COMMAND_REG)            // 0x0022
    {
        if (HID_WrIdxB > 0x03)
        {
            Process_HID2_OPCode();
        }
        return;
    }
    if (HID_wRegIndex_B == _HID_OUTPUT_REG)             // 0x0025
    {
#if SUPPORT_HID_KEYBOARD_LED
        /* OUTPUT REPORT */
        if (HID_WrIdxB > 0x05)  /* 6 byte or more */
        {
            HID_DeviceActived |= F_HID_KB_LED_UPDATE;
            /* ID = 1; */
            if (HID_InBuf_B[4] == (HID_KB_GENERIC + HID_OFFSET))
            {
                /* Keyboard LED */
                ITempB02 = HID_InBuf_B[5];

                if (IS_MASK_SET(ITempB02, BIT(1)))
                {
                    EC_CAP_LED_EN_HI();
                    SET_MASK(xDBG_UartDisp2, BIT6);               
                }
                else
                {
                    EC_CAP_LED_EN_LO();
                    SET_MASK(xDBG_UartDisp2, BIT7);                    
                }
            }
        }
#endif
        return;
    }
    if ((HID_wRegIndex_B == _HID_DESC_LAYOUT) ||        // 0x0001
            (HID_wRegIndex_B == _HID_DESC_LAYOUT2) ||   // 0x0020
            (HID_wRegIndex_B == _REPORT_DESC_REG) ||    // 0x0021
            (HID_wRegIndex_B == _HID_INPUT_REG) ||      // 0x0024
            (HID_wRegIndex_B == _HID_DATA_REG))         // 0x0023
    {
        if((HID_wRegIndex_B == _HID_DESC_LAYOUT) ||     // 0x0001
            (HID_wRegIndex_B == _HID_DESC_LAYOUT2))     // 0x0020
        {
            HID_DeviceActived = 0;
        }
        return;
    }
    HID_WrIdxB = 0x0000;
#else
    switch (HID_wRegIndex_B)
    {
    case _HID_DESC_LAYOUT:      //0x0001
    case _HID_DESC_LAYOUT2:     //0x0020
    case _REPORT_DESC_REG:      //0x0021
    case _HID_INPUT_REG:        //0x0024
        break;

    case _HID_OUTPUT_REG:       //0x0017
        /* OUTPUT REPORT */
        if (HID_WrIdxB > 0x05)  /* 6 byte or more */
        {
            /* ID = 1; */
            if (HID_InBuf_B[4] == (HID_KB_GENERIC + HID_OFFSET))
            {
                /* Keyboard LED */
                ITempB02 = HID_InBuf_B[5];

                if (IS_MASK_SET(ITempB02, BIT(0)))
                {
                    Hook_NUMLED_ON();
                }
                else
                {
                    Hook_NUMLED_OFF();
                }

                if (IS_MASK_SET(ITempB02, BIT(1)))
                {
                    Hook_CAPLED_ON();
                }
                else
                {
                    Hook_CAPLED_OFF();
                }
            }
        }
        break;

    case _HID_COMMAND_REG:      //0x0022
        if (HID_WrIdxB > 0x03)
        {
            Process_HID2_OPCode();
        }
        break;

    case _HID_DATA_REG:
        break;

    default:
        HID_WrIdxB = 0x0000;
        break;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Write_HID_DeviceB
 * @function - Write HID DeviceB
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
// void Write_HID_DeviceB(void)
void Write_HID_DeviceB(uint8_t wcmd[], uint32_t wlength)
{
#if NO_NEED
    /* From Host HID Write Protocol */
    ITempB01 = SLDA_B;
    ITempB02 = SLDA_B; /* Release Clock Pin */
#endif
    HID_RdIdxB = 0;

    memcpy((void *)HID_InBuf_B, wcmd, wlength);
    HID_WrIdxB = wlength;
    HID_wRegIndex_B = 0;
#if NO_NEED
    if (HID_WrIdxB < (_HID_IN_BUF_LEN + 1))
    {
        HID_InBuf_B[HID_WrIdxB] = ITempB01;

        HID_WrIdxB++;

        if (HID_WrIdxB > 1)
        {
#endif
        if( wlength != 0 )
        {
            /* 16 Bits Index(Command) */
            HID_wRegIndex_B = (WORD)((HID_InBuf_B[1] << 8) +
                                     HID_InBuf_B[0]);

            Process_HID2_Registers();
        }

#if NO_NEED
        }
    }
    else
    {
        HID_WrIdxB++;
    }
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Read_ACPI_DeviceB
 * @function - Read_ACPI_DeviceB
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Read_ACPI_DeviceB(uint8_t rbuff[], uint32_t *rlength)
{
    /* From Host ACPI Read Protocol */
#if SUPPORT_CHANNEL_AB_SAME_ACPI    /* 1:I2C A,B using same ACPI. */
    ITempB01 = AcpiReadData_I2C_AB(rbuff, rlength);
    #if NO_NEED
    SLDA_B = ITempB01;  /* Send Data */
    SLDA_B = ITempB01;  /* Release Clock Pin */
    PMC_RdIdx++;    
    #endif
#else
    ITempB01 = AcpiReadData_I2C_B(HID_RdIdxB);
    SLDA_B = ITempB01;  /* Send Data */
    SLDA_B = ITempB01;  /* Release Clock Pin */
    HID_RdIdxB++;    
#endif
}

/*-----------------------------------------------------------------------------
 * @subroutine - Write_ACPI_DeviceB
 * @function - Write_ACPI_DeviceB
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Write_ACPI_DeviceB(uint8_t wcmd[], uint32_t wlength)
{
    /* From Host ACPI Write Protocol */
#if NO_NEED
    ITempB01 = SLDA_B;  /* Receive Data */
    ITempB02 = SLDA_B;  /* Release Clock Pin */
#endif
#if SUPPORT_CHANNEL_AB_SAME_ACPI    /* 1:I2C A,B using same ACPI. */
    #if NO_NEED
    AcpiWriteData_I2C_AB(PMC_WrIdx, ITempB01);
    PMC_WrIdx++;
    #else
    AcpiWriteData_I2C_AB(wcmd, wlength);
    #endif
#else
    AcpiWriteData_I2C_B(HID_WrIdxB, ITempB01);
    HID_WrIdxB++;    
#endif
}

#if UNUSED
#pragma ot(8, SPEED)
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - service_SlaveI2C_B
 * @function - I2C Salve Channel-B data service
 * @Upstream - By call (INT)
 * @input    - None
 * @return   - None
 * @note     - SMCLK2/GPF.6, SMDAT2/GPF.7 (SWAP)
 */
// void service_SlaveI2C_B(void)
void service_SlaveI2C_B(ProtocolType target, I2CCmdType action, 
                        uint8_t wbuff[], uint32_t wlength,
                        uint8_t rbuff[], uint32_t *rlength)
{
    I2C_Tag = 0;
    HID_RdIdxB = 0;
    HID_WrIdxB = 0;
    PMC_RdIdx = 0;
    PMC_WrIdx = 0;
#if WAIT_TO_ADD
    ChannelIsSlaveB = 1;
#endif

#if 0
    // reference for new i2c target
    DisableAllInterrupt();
    SettingTimer1(Timer_26ms);
#endif

#if NO_NEED
    while (!TF1)
    {
        /* Stop condition Detected */
        if (IS_MASK_SET(SLSTA_B, SPDS))
        {
            I2C_Tag = 0xED;
            break;
        }
        /* Timeout Status */
        if (IS_MASK_SET(SLSTA_B, STS))
        {
            break;
        }

        /* Slave data register is waiting for read or write */
        if (IS_MASK_SET(SLSTA_B, SDS))
        {
            /* Clear Status */
            SLSTA_B = SDS;
            /*
             * I2C Write to Read Cycle
             * EC send data to Host. 0: slave address, 1: slave address2
             */
            if (IS_MASK_SET(SLSTA_B, MSLA2))
            {
                /* ACPI Channel */
                /* RCS=1:Read by Host, RCS=0:Write by Host */
                if (IS_MASK_SET(SLSTA_B, RCS))
                {
                    Read_ACPI_DeviceB();
                }
                else
                {
                    Write_ACPI_DeviceB();
                }
            }
            else
            {
                /* HID Channel */
                /* RCS=1:Read by Host, RCS=0:Write by Host */
                if (IS_MASK_SET(SLSTA_B, RCS))
                {
                    Read_HID_DeviceB();
                }
                else
                {
                    Write_HID_DeviceB();
                }
            }

            /* Reset & Reload Timer1 */
            TH1 = Timer_26ms >> 8;
            TL1 = Timer_26ms;
            TF1 = 0;
        }
    
    /* Clear Slave Bus Status */
    }   // while (!TF1)
#else
        if ( target == AcpiOverI2c )
        {
            if ( action == Read )
            {
                ARG_UNUSED(wbuff);
                ARG_UNUSED(wlength);
                Read_ACPI_DeviceB(rbuff, rlength);
            }
            else if ( action == Write )
            {
                ARG_UNUSED(rbuff);
                ARG_UNUSED(*rlength);
                Write_ACPI_DeviceB(wbuff, wlength);
            }
        }
        else if ( target == HidOverI2c )
        {
            if ( action == Read ) // read = 1
            {
                ARG_UNUSED(wbuff);
                ARG_UNUSED(wlength);
                Read_HID_DeviceB(rbuff, rlength);
            }
            else if ( action == Write )
            {
                ARG_UNUSED(rbuff);
                ARG_UNUSED(*rlength);
                Write_HID_DeviceB(wbuff, wlength);
            }
        }
#endif

#if UNUSED
    SLSTA_B = SPDS + STS + SDS;

    TR1 = 0; /* Disable timer1 */
    TF1 = 0; /* Clear overflow flag */
    ET1 = 1; /* Enable timer1 interrupt */

#if HID_UART_DEBUG_OUTPUT
    if (HID_wRegIndex_B > 0)
    {        
        Main_UartDebug(2, HID_wRegIndex_B >> 8, HID_wRegIndex_B);
        HID_wRegIndex_B = 0;
    }
#endif // HID_UART_DEBUG_OUTPUT

    INTERRUPT_HID_HI();
    if (I2C_Tag == 0xED)
    {
#if SUPPORT_CHANNEL_AB_SAME_ACPI        
        Hook_SlaveI2C_AB_Stop();
#else
        Hook_SlaveI2C_B_Stop();
#endif        
    }
#endif // UNUSED

#if 0
    // reference for new i2c target
    /* Enable Slave I2C Interrupt */
    ISR1 = Int_SMBUS1;
    IER1 |= Int_SMBUS1;
    /* Release Interrupt */
    EA = 1; //EnableAllInterrupt();
#endif 
}

#if UNUSED
/*-----------------------------------------------------------------------------
 * @subroutine - hid_i2c_kb_data_set
 * @function - hid_i2c_kb_data_set
 * @upstream - By call
 * @input    - Key Code
 * @return   - None
 * @note     - None
 */
//-----------------------------------------------------------------------------
/* PS/2 code to HID Code - index of PS/2 set 2 make */
const char code PS2_To_HID_UsageID[0x90] =
{
    0x00, 0x42, 0x00, 0x3E, 0x3C, 0x3A, 0x3B, 0x45, /* 0x00 ~ 0x07 */
    0x68, 0x43, 0x41, 0x3F, 0x3D, 0x2B, 0x35, 0x67, /* 0x08 ~ 0x0F */
    0x69, 0xE2, 0xE1, 0x88, 0xE0, 0x14, 0x1E, 0x00, /* 0x10 ~ 0x17 */
    0x6A, 0x00, 0x1D, 0x16, 0x04, 0x1A, 0x1F, 0x00, /* 0x18 ~ 0x1F */
    0x6B, 0x06, 0x1B, 0x07, 0x08, 0x21, 0x20, 0x8C, /* 0x20 ~ 0x27 */
    0x6C, 0x2C, 0x19, 0x09, 0x17, 0x15, 0x22, 0x00, /* 0x28 ~ 0x2F */
    0x6D, 0x11, 0x05, 0x0B, 0x0A, 0x1C, 0x23, 0x00, /* 0x30 ~ 0x37 */
    0x6E, 0x00, 0x10, 0x0D, 0x18, 0x24, 0x25, 0x00, /* 0x38 ~ 0x3F */
    0x6F, 0x36, 0x0E, 0x0C, 0x12, 0x27, 0x26, 0x00, /* 0x40 ~ 0x47 */
    0x70, 0x37, 0x38, 0x0F, 0x33, 0x13, 0x2D, 0x00, /* 0x48 ~ 0x4F */
    0x71, 0x87, 0x34, 0x00, 0x2F, 0x2E, 0x00, 0x72, /* 0x50 ~ 0x57 */
    0x39, 0xE5, 0x28, 0x30, 0x00, 0x31, 0x00, 0x73, /* 0x58 ~ 0x5F */
    0x00, 0x64, 0x93, 0x92, 0x8A, 0x00, 0x2A, 0x8B, /* 0x60 ~ 0x67 */
    0x00, 0x59, 0x89, 0x5C, 0x5F, 0x85, 0x00, 0x00, /* 0x68 ~ 0x6F */
    0x62, 0x63, 0x5A, 0x5D, 0x5E, 0x60, 0x29, 0x53, /* 0x70 ~ 0x77 */
    0x44, 0x57, 0x5B, 0x56, 0x55, 0x61, 0x47, 0x00, /* 0x78 ~ 0x7F */
    0x00, 0x00, 0x00, 0x40, 0x00, 0x48, 0x00, 0x00, /* 0x80 ~ 0x87 */
    0x32, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x88 ~ 0x90 */
};
/* Notes: 0x88 ~ 0x90 Special Code
   5D F0 5D -> 88 F0 88 -> Europe 1 -> 07 32
   5F F0 5F -> 89 F0 89 -> Zenkaku/Hankaku -> 07 94
   XX F0 XX -> 8A F0 8A -> Reserved
   XX F0 XX -> 8B F0 8B -> Reserved
   XX F0 XX -> 8C F0 8C -> Reserved
   XX F0 XX -> 8D F0 8D -> Reserved
   XX F0 XX -> 8E F0 8E -> Reserved
   XX F0 XX -> 8F F0 8F -> Reserved
*/
//-----------------------------------------------------------------------------
const char code PS2EX_To_HID_UsageID[0x88] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00 ~ 0x07 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x08 ~ 0x0F */
    0x21, 0xE6, 0x00, 0x70, 0xE4, 0xB6, 0x00, 0x00, /* 0x10 ~ 0x17 */
    0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE3, /* 0x18 ~ 0x1F */
    0x27, 0xEA, 0x00, 0xE2, 0x00, 0x00, 0x00, 0xE7, /* 0x20 ~ 0x27 */
    0x26, 0x00, 0x00, 0x92, 0x00, 0x00, 0x00, 0x65, /* 0x28 ~ 0x2F */
    0x25, 0x00, 0xE9, 0x00, 0xCD, 0x00, 0x81, 0x66, /* 0x30 ~ 0x37 */
    0x24, 0x00, 0x23, 0xB7, 0x00, 0x00, 0x00, 0x82, /* 0x38 ~ 0x3F */
    0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40 ~ 0x47 */
    0x8A, 0x00, 0x54, 0x00, 0x00, 0xB5, 0x00, 0x00, /* 0x48 ~ 0x4F */
    0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50 ~ 0x57 */
    0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x83, 0x00, /* 0x58 ~ 0x5F */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60 ~ 0x67 */
    0x00, 0x4D, 0x00, 0x50, 0x4A, 0x00, 0x00, 0x6F, /* 0x68 ~ 0x6F */
    0x49, 0x4C, 0x51, 0x00, 0x4F, 0x52, 0x00, 0x00, /* 0x70 ~ 0x77 */
    0x00, 0x00, 0x4E, 0x00, 0x46, 0x4B, 0x00, 0xF1, /* 0x78 ~ 0x7F */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80 ~ 0x87 */
};
/* Notes:
   System Power -> 01 81 -> E0 37 E0 F0 37 Changed-> E0 36 E0 F0 36
   Page 0C Usage ID 00 6F - Brightness Increment - E0 6F E0 F0 6F
   Page 0C Usage ID 00 70 - Brightness Decrement - E0 13 E0 F0 13
   ITE WIFI Button E0 7F E0 F0 7F (Use UNASSIGNED Code)
*/
const char code PS2EX_To_HID_UsagePG[0x88] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x00 ~ 0x07 */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x08 ~ 0x0F */
    0xC2, 0x70, 0x00, 0xC0, 0x70, 0xC0, 0x00, 0x00, /* 0x10 ~ 0x17 */
    0xC2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, /* 0x18 ~ 0x1F */
    0xC2, 0xC0, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x70, /* 0x20 ~ 0x27 */
    0xC2, 0x00, 0x00, 0xC1, 0x00, 0x00, 0x00, 0x70, /* 0x28 ~ 0x2F */
    0xC2, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x10, 0x70, /* 0x30 ~ 0x37 */
    0xC2, 0x00, 0xC2, 0xC0, 0x00, 0x00, 0x00, 0x10, /* 0x38 ~ 0x3F */
    0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40 ~ 0x47 */
    0xC1, 0x00, 0x70, 0x00, 0x00, 0xC0, 0x00, 0x00, /* 0x48 ~ 0x4F */
    0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x50 ~ 0x57 */
    0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x10, 0x00, /* 0x58 ~ 0x5F */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60 ~ 0x67 */
    0x00, 0x70, 0x00, 0x70, 0x70, 0x00, 0x00, 0xC0, /* 0x68 ~ 0x6F */
    0x70, 0x70, 0x70, 0x00, 0x70, 0x70, 0x00, 0x00, /* 0x70 ~ 0x77 */
    0x00, 0x00, 0x70, 0x00, 0x70, 0x70, 0x00, 0xF1, /* 0x78 ~ 0x7F */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80 ~ 0x87 */
};

/*-----------------------------------------------------------------------------
 * @subroutine - hid_kb_data_packet
 * @function - hid_kb_data_packet
 * @upstream - By Call
 * @input    - MAKE_EVENT, BREAK_EVENT
 * @return   - None
 * @note     - None
 */
BYTE hid_kb_data_packet(BYTE KCode, BYTE KEvent)
{
    if (KEvent == BREAK_EVENT)
    {
        for (ITempB01 = 0; ITempB01 < 6; ITempB01++)
        {
            if (HID_KB_Packet[ITempB01] == KCode)
            {
                HID_KB_Packet[ITempB01] = 0;
            }
        }
        return TRUE;
    }
    for (ITempB01 = 0; ITempB01 < 6; ITempB01++)
    {
        if (HID_KB_Packet[ITempB01] == KCode)
        {
            return TRUE;
        }
    }
    for (ITempB01 = 0; ITempB01 < 6; ITempB01++)
    {
        if (HID_KB_Packet[ITempB01] == 0x00)
        {
            HID_KB_Packet[ITempB01] = KCode;
            return TRUE;
        }
    }
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * @subroutine - hid_i2c_kb_data_set
 * @function - hid_i2c_kb_data_set
 * @upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 */
BYTE hid_i2c_kb_data_set(BYTE u8KeyCode)
{
    if (u8KeyCode == 0xE0)
    {
        /* Process Extend Key Page Code */
        u8KeyCode = Get_Buffer();
        if (u8KeyCode == 0xF0)
        {
            /* ScanCode Break: E0 F0 XX */
            u8KeyCode = Get_Buffer();
            /* Process Extend Key Page Code */
            ITempB01 = PS2EX_To_HID_UsageID[u8KeyCode];
            if (ITempB01 == 0x00)
            {
                return 0x00;
            }
            ITempB02 = PS2EX_To_HID_UsagePG[u8KeyCode];
            ITempB03 = (ITempB02 >> 4) & 0x0F;
            ITempB02 &= 0x0F;
            if (ITempB03 == 0x0F)   /* ITE WIFI Button Code */
            {
                return 0x00;
            }
            if (ITempB03 == 0x0C)
            {
                HID_UsagePage0C_L = 0;
                HID_UsagePage0C_H = 0;
                return 0x0C;
            }
            if (ITempB03 == 0x07)
            {
                hid_kb_data_packet(ITempB01, BREAK_EVENT);
                return 0x07;
            }
        }
        else
        {
            /* ScanCode Make: E0 XX */
            ITempB01 = PS2EX_To_HID_UsageID[u8KeyCode];
            if (ITempB01 == 0x00)
            {
                return 0x00;
            }
            ITempB02 = PS2EX_To_HID_UsagePG[u8KeyCode];
            ITempB03 = (ITempB02 >> 4) & 0x0F;
            ITempB02 &= 0x0F;
            if (ITempB03 == 0x0F)   /* ITE WIFI Button Code */
            {
                return 0x0F;
            }
            /* General Usage Page 0C */
            if (ITempB03 == 0x0C)
            {
                HID_UsagePage0C_L = ITempB01;
                HID_UsagePage0C_H = ITempB02;
                return 0x0C;
            }
            if (ITempB03 == 0x07)
            {
                hid_kb_data_packet(ITempB01, MAKE_EVENT);
                return 0x07;
            }
        }
    }
    else
    {
        if (u8KeyCode == 0xF0)
        {
            /* ScanCode Break:F0 XX */
            u8KeyCode = Get_Buffer();
            ITempB01 = PS2_To_HID_UsageID[u8KeyCode];
            hid_kb_data_packet(ITempB01, BREAK_EVENT);
            return 0x07;
        }
        else
        {
            /* ScanCode Make:XX */
            ITempB01 = PS2_To_HID_UsageID[u8KeyCode];
            if (ITempB01 == 0x00)
            {
                return FALSE;
            }
            hid_kb_data_packet(ITempB01, MAKE_EVENT);
            return 0x07;
        }
    }
    return 0x07;
}

/*-----------------------------------------------------------------------------
 * @subroutine - service_send
 * @function - service_send
 * @upstream - None
 * @input    - None
 * @return   - None
 * @note     - None
 */
void service_send(void)
{
    BYTE    u8DataWord;
    BYTE    gbHasData = FALSE;

#if 0   //1: Test Keyboard Scan Roll Out
    ITempB01 = Get_Buffer();
    return;
#endif

#if SUPPORT_HID_CHANNEL_A_KEYCODE
    if (HID_OutBuf_A[0] > 0)
    {
        HID_ReportType = _KB_INPUT_REPORT;
        Send_HID_Interrupt();      
        return;
    }
    /* Get & translate legacy PS/2 keyboard data packet */
    while (0xFF != (u8DataWord = Get_Buffer()))
    {
        ITempB01 = hid_i2c_kb_data_set(u8DataWord);
        if (ITempB01 == 0x07)
        {
            gbHasData = TRUE;
            break;
        }
        if (ITempB01 == 0x0C)
        {
            HID_UsagePage0C_Out = 0x0C;
            break;
        }
        if (ITempB01 == 0x0F)
        {
            HID_UsagePage0C_Out = 0x0F;
            break;
        }
    }

    /* Send HID WiFi Button data packet */
    if (HID_UsagePage0C_Out == 0x0F)
    {
        HID_UsagePage0C_Out = 0;
        HID_OutBuf_A[0] = 0x05;     /* Length = 0x0005 */
        HID_OutBuf_A[1] = 0x00;
        HID_OutBuf_A[2] = (HID_KB_MM_WIRELESS_FN_REPORT_ID + HID_OFFSET);
        HID_OutBuf_A[3] = 0x01;
        HID_OutBuf_A[4] = 0x00;
        return;
    }

    /* Send Media keyboard data packet */
    if (HID_UsagePage0C_Out == 0x0C)
    {
        HID_UsagePage0C_Out = 0;
        HID_OutBuf_A[0] = 0x05;     /* Length = 0x0005 */
        HID_OutBuf_A[1] = 0x00;
        HID_OutBuf_A[2] = (HID_KB_MM_CONSUMER_FN_REPORT_ID + HID_OFFSET);
        HID_OutBuf_A[3] = HID_UsagePage0C_L;
        HID_OutBuf_A[4] = HID_UsagePage0C_H;
        return;
    }

    /* Check & send CTRL,ALT,GUI,SHIFT special key changed */
    if (HID_ScannerStateL != HID_ScannerState)
    {
        HID_ScannerStateL = HID_ScannerState;
        gbHasData = TRUE;
    }

    /* General keyboard data packet */
    if (gbHasData)
    {
        HID_OutBuf_A[0] = 0x0B;     /* Length = 0x000B */
        HID_OutBuf_A[1] = 0x00;
        HID_OutBuf_A[2] = (HID_KB_GENERIC + HID_OFFSET);
        HID_OutBuf_A[3] = HID_ScannerStateL;  /* Control Byte */
        HID_OutBuf_A[4] = 0x00;     /* Reserved */
        HID_OutBuf_A[5] = HID_KB_Packet[0];
        HID_OutBuf_A[6] = HID_KB_Packet[1];
        HID_OutBuf_A[7] = HID_KB_Packet[2];
        HID_OutBuf_A[8] = HID_KB_Packet[3];
        HID_OutBuf_A[9] = HID_KB_Packet[4];
        HID_OutBuf_A[10] = HID_KB_Packet[5];
        return;
    }
    HID_UsagePage0C_Out = 0;
#elif SUPPORT_HID_CHANNEL_B_KEYCODE
    if (HID_OutBuf_B[0] > 0)
    {
        HID_ReportType = _KB_INPUT_REPORT;
        Send_HID_Interrupt();      
        return;
    }
    /* Get & translate legacy PS/2 keyboard data packet */
    while (0xFF != (u8DataWord = Get_Buffer()))
    {
        ITempB01 = hid_i2c_kb_data_set(u8DataWord);
        if (ITempB01 == 0x07)
        {
            gbHasData = TRUE;
            break;
        }
        if (ITempB01 == 0x0C)
        {
            HID_UsagePage0C_Out = 0x0C;
            break;
        }
        if (ITempB01 == 0x0F)
        {
            HID_UsagePage0C_Out = 0x0F;
            break;
        }
    }

    /* Send HID WiFi Button data packet */
    if (HID_UsagePage0C_Out == 0x0F)
    {
        HID_UsagePage0C_Out = 0;
        HID_OutBuf_B[0] = 0x05;     /* Length = 0x0005 */
        HID_OutBuf_B[1] = 0x00;
        HID_OutBuf_B[2] = (HID_KB_MM_WIRELESS_FN_REPORT_ID + HID_OFFSET);
        HID_OutBuf_B[3] = 0x01;
        HID_OutBuf_B[4] = 0x00;
        return;
    }

    /* Send Media keyboard data packet */
    if (HID_UsagePage0C_Out == 0x0C)
    {
        HID_UsagePage0C_Out = 0;
        HID_OutBuf_B[0] = 0x05;     /* Length = 0x0005 */
        HID_OutBuf_B[1] = 0x00;
        HID_OutBuf_B[2] = (HID_KB_MM_CONSUMER_FN_REPORT_ID + HID_OFFSET);
        HID_OutBuf_B[3] = HID_UsagePage0C_L;
        HID_OutBuf_B[4] = HID_UsagePage0C_H;
        return;
    }

    /* Check & send CTRL,ALT,GUI,SHIFT special key changed */
    if (HID_ScannerStateL != HID_ScannerState)
    {
        HID_ScannerStateL = HID_ScannerState;
        gbHasData = TRUE;
    }

    /* General keyboard data packet */
    if (gbHasData)
    {
        HID_OutBuf_B[0] = 0x0B;     /* Length = 0x000B */
        HID_OutBuf_B[1] = 0x00;
        HID_OutBuf_B[2] = (HID_KB_GENERIC + HID_OFFSET);
        HID_OutBuf_B[3] = HID_ScannerStateL;  /* Control Byte */
        HID_OutBuf_B[4] = 0x00;     /* Reserved */
        HID_OutBuf_B[5] = HID_KB_Packet[0];
        HID_OutBuf_B[6] = HID_KB_Packet[1];
        HID_OutBuf_B[7] = HID_KB_Packet[2];
        HID_OutBuf_B[8] = HID_KB_Packet[3];
        HID_OutBuf_B[9] = HID_KB_Packet[4];
        HID_OutBuf_B[10] = HID_KB_Packet[5];
        return;
    }
    HID_UsagePage0C_Out = 0;
#endif
}

#endif // UNUSED

#endif // SUPPORT_CODE_SALVE_I2C
