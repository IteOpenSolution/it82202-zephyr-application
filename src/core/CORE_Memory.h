/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_CORE_MEMORY_H_
#define _ITE_CORE_MEMORY_H_

#include "../core/CORE_TYPES.h"

//----------------------------------------------------------------------------
// The Controller Command Byte.  Accessed through Commands 20h
// and 60h.  First byte in the 0 through 1F space in an 8042.
//----------------------------------------------------------------------------
#define INTR_KEY     0x01   //bit0
#define INTR_AUX     0x02   //bit1
//#define SYS_FLAG     0x04 //bit2
#define DISAB_KEY    0x10   //bit4
#define DISAB_AUX    0x20   //bit5
#define XLATE_PC     0x40   //bit6

#define all         byte
#define SCROLL      bit0
#define NUM         bit1
#define CAPS        bit2
#define OVL         bit3
#define LED4        bit4
#define LED5        bit5
#define LED6        bit6
#define LED7        bit7


//----------------------------------------------------------------------------
// Internal ram variables (direct)[0x30-0x7F]
//----------------------------------------------------------------------------
extern IBYTE    xFSH_AddrH;
extern IBYTE    xFSH_AddrM;
extern IBYTE    xFSH_AddrL;
#if UNUSED
extern IBYTE    xFSH_Data0;
extern IBYTE    xFSH_Data1;
#endif
extern IBYTE    xFSH_Command;
extern IBYTE    xFSH_Position;

extern IBYTE    xFSH_A2_BYTECNT;
extern IWORD    wFSH_ByteCount;
extern IBYTE    xFSH_BSIZE;
extern IBYTE    ICHECKSUM_L;
extern IBYTE    ICHECKSUM_M;
extern IBYTE    ICHECKSUM_H;
extern IBYTE    ICHECKSUM_U;
#if UNUSED
//----------------------------------------------------------------------------
// Timer_A, Timer_B
// Bits 0 through 3 of TIMER are reserved for "count".
//----------------------------------------------------------------------------
extern  TIMER Timer_A;      // Timer A. Timer A has a time base of 1 mS.
#define HIF2_SAFETY  count  // Secondary host interface timer.
#define TMR_SCAN     bit4   // Scanner interval enabled.
#define TMR_GENTMO   bit5   // General timeouts.
//                   bit6   //
//                   bit7   //
extern TIMER Timer_B;       // Timer B. Timer A has a time base of 150 uS.
#define SEND_DELAY   count  // Internal device send delay count used with SEND_ENABLE.
#define SEND_ENABLE  bit4   // Internal device send request.
#define INH_CLEAR    bit5   // Delay to enable serial clock lines.
#define UNLOCK_TMO   bit6   // Delay for unlock request.
//                   bit7   //

extern  IBYTE     *data Tmp_Pntr;
extern  IBYTE     Timer1msCnt;        // 0x43
extern  IBYTE     Timer5msCnt;        // 0x44
extern  IBYTE     Timer100msCnt;      // 0x45
extern  IBYTE     Timer100msCntB;     // 0x46
extern  IBYTE     Timer1SecCnt;       // 0x47
extern  IBYTE     TargetDCR1;         // 0x48

extern  BYTE code *data Tmp_code_pointer;
extern  IBYTE     INT_NUM;      // 0x57
extern  IBYTE     INT_CNT;      // 0x58
#endif /* UNUSED */
extern IBYTE      DebugHLOSTx;
#if UNUSED
extern IBYTE      SPIOPCMD;

extern  IBYTE   Loopi;
extern  IBYTE   xNTC_Pointer;
extern  IWORD   ITempW02;
//extern  IBYTE   PM1DataCount;

extern  IBYTE   last_new_key_kso_index;
extern  IBYTE   last_new_key_ksi_index;
extern  IBYTE   last_new_accept_time;
#endif // UNUSED
extern  IBYTE   ITempB01;
extern  IBYTE   ITempB02;
extern  IBYTE   ITempB03;
extern  IBYTE   ITempB04;
extern  IBYTE   ITempB05;
extern  IBYTE   ITempB06;
extern  IWORD   ITempW01;
#if UNUSED
extern  IBYTE   bscan_matrix[];

//----------------------------------------------------------------------------
// Internal ram variables (Indirect)[0x80-0xCF]
//----------------------------------------------------------------------------
extern   IIBYTE  xCopyParameter[];
#define  xCopyToPosH       xCopyParameter[0]
extern   IIBYTE  xCopyToPosM;
extern   IIBYTE  xCopyEndPosM;
extern   IIBYTE  xReadAtPosH;
extern   IIBYTE  xReadAtPosM;
extern   IIBYTE  xReadAtPosL;
extern   IIBYTE  iCheckSumBuf[];

extern  IIBYTE      Save_Typematic;         // 0x96
#endif // UNUSED

extern  IIBYTE  I2C_Tag;

#if UNUSED
extern  IIBYTE  HID_ScannerState;

extern IIBYTE     TIMETICKB0;
extern IIBYTE     TIMETICKB1;
extern IIBYTE     TIMETICKB2;
extern IIBYTE     TIMETICKB3;
extern IIBYTE     TIMETICKB4;
extern IIBYTE     TIMETICKB5;
extern IIBYTE     TIMETICKB6;
extern IIBYTE     TIMETICKB7;

extern  IIBYTE       FanControlStep;
#endif

extern  IIBYTE       PMC_RdIdx;
extern  IIBYTE       PMC_WrIdx;


extern  IIBYTE       xHI2C_AcpiCmdCode;
extern  IIBYTE       xHI2C_AcpiCmdCode2;
extern  IIBYTE       xHI2C_AcpiCmdCode3;
extern  IIBYTE       FAN_XPntr_wLen;
extern  XBYTE        *PMC_XPntr;
extern  XBYTE        *FAN_XPntr;
#if UNUSED
extern  INT_VAR Int_Var;
//----------------------------------------------------------------------------
// Flag
//----------------------------------------------------------------------------
extern  FLAGS   Flag;
#define SCAN_INH         bit0 // 1 = Scanner transmission inhibited. 
#define SENDING_SCAN_RC  bit1 // For diagnostic mode. 
#define PASS_READY       bit2 // Password loaded. 
#define NEW_PRI_K        bit3 // Switch to new primary keyboard. 
#define NEW_PRI_M        bit4 // Switch to new primary mouse. 
#define VALID_SCAN       bit5
#define LED_ON           bit6
#define ENTER_LOW_POWER  bit7 // Go into low power mode. 
#define ACPI_IN_PROGRESS bit8
#define ACPI_SMB_ALARM   bit9
#define LEGACY_SMB_ALARM bit10
#define ALT_PRESSED      bit11// External keyboard ALT key state. 
#define CTRL_PRESSED     bit12// External keyboard CTRL key state. 
#define DETECT_EC_B0     bit13// Used to allow Insyde Software's 
#define DETECT_EC_B1     bit14// embedded controller to be detected.
#define Aux_Not_RESP     bit15

extern  EXT_CB2     Ext_Cb2;
extern IIBYTE Save_Kbd_State;

/* maskLEDS is used by Keyboard Command EDh to qualify the data.
   If any bits outside of the mask are attempted to be modifed
   by Keyboard Command EDh, the command is rejected. */
#define maskLEDS     0x07

/* shiftCODESET is used to shift the bits for the saved Scan Code
   Set number to the lower part of the byte.  maskCODESET is then
   used to isolate those bits. */
#define shiftCODESET 3
#define maskCODESET  0x03

/* The enabled state of the external keyboard
   modified by Keyboard Command F4h/F5h. */
#define maskAUXENAB  (1 << 5)

/* Bit 0 through 5 used for code. */
#define maskKBD_RESPONSE_CODE 0x03F

/* Multibyte response codes. */
#define respCMD_AC   0x80  // Diagnostic dump.  Sends version string. 
#define respCMD_CFG  0x81  // Configuration Table. 
#define respARRAY    0x82  // Sends bytes in an array. 
// Codes 83h through 8Fh are reserved for the core code.
#endif // UNUSED
//extern    IIBYTE      Save_Typematic;
extern  XBYTE *Tmp_XPntr;


extern  XWORD   *HID_XPntr;

#if UNUSED
extern  key_state   temp_scanner_state;
#endif // UNUSED

extern  IIBYTE  HID_RdIdxA;
extern  IIBYTE  HID_WrIdxA;
extern  IIBYTE  HID_RdIdxB;
extern  IIBYTE  HID_WrIdxB;

#if UNUSED
//----------------------------------------------------------------------------
//Pass_xxx
//----------------------------------------------------------------------------
extern  XBYTE   bKEY_BUFF[];
extern  XBYTE   Pass_Buff[];    // Password buffer.
extern  XBYTE   Pass_Buff_Idx;  // Password buffer index
// (0 to PASS_SIZE-1).
extern  XBYTE   Pass_On;        // Security Code On byte.
extern  XBYTE   Pass_Off;       // Security Code Off byte.
extern  XBYTE   Pass_Make1;     // Reject make code 1.
extern  XBYTE   Pass_Make2;     // Reject make code 2.

//*******************************************************
//#ifdef KB_HW_KeyScan   // Hardware scan keyboard
//*******************************************************
extern  XBYTE   KB_HW_ExtendKeyIndex;       // 0x20
extern  XBYTE   KB_HW_ExtendKeyTypematic;   // 0x21

//*******************************************************
//#endif // KB_HW_KeyScan Hardware scan keyboard
//*******************************************************

extern  XBYTE   bTMrepeat;
extern  XBYTE   bTMdelay;
extern  XBYTE   bTMcount;
extern  XBYTE   diode_key;
extern  BYTE code *Scanner_Table_Pntr;
extern  BYTE code *Extendkey_Table_Pntr;
extern  BYTE code *eFlashRom_Pntr;

extern  XBYTE   RunCodeBlockTag;
extern  XBYTE   CodeCheckSumB0;
extern  XBYTE   CodeCheckSumB1;
extern  XBYTE   CodeCheckSumB2;
extern  XBYTE   CodeCheckSumB3;

extern  XBYTE   WinFlashMark;
extern  XBYTE   RamCodePort;

extern  XBYTE   KBDataPending[];
extern  XBYTE   KBPendingRXCount;
extern  XBYTE   KBPendingTXCount;

extern  XBYTE   ExtendScanPin;
extern  XBYTE   RSTStatus;
extern  XBYTE   RamcodeCmd;
extern  XBYTE   RamcodeSend;
extern  BYTE code *Tmp_Code_Pntr;
extern  FUNCT_PTR_V_V Tmp_Func_Pnter;
extern  XBYTE   SMBus1RecoverCunt; 
extern  XBYTE   SMBus2RecoverCunt;
extern  XBYTE   SMBus3RecoverCunt; 
extern  XBYTE   SPIWriteStatusL; 
extern  XBYTE   FN_Key_Break;
extern  XBYTE   FN_Key_Break_HS; 
extern  XBYTE   SMBus_BusyRecover; 

extern  XBYTE   SPIIDBuf[];
extern  XBYTE   SPIIndex;   
extern  XBYTE   SPIAddrCycle[]; 
extern  XBYTE   SPIAEraseCmd;  
extern  XBYTE   SPIReadStatus;   
#endif
extern  XBYTE   SPIWriteStatus;   
#if UNUSED
extern  XBYTE   *SPIDataPointer;    
#define SPIDataPointerLowByte (*(XBYTE*)( 0x09C))   
extern  XBYTE   SPIID;  
extern  XBYTE   SSTDeviceID;  
extern  XBYTE   EC_Indirect_Selection; 

extern  XBYTE   FnKeyBundledFalg[];

#define F_CLR_PLTRST_STEP       0
#define F_PLTRST_HI_LEVEL       1
#define F_PLTRST_HI_TO_LO       2
#define F_PLTRST_LO_TO_HI       3
#define F_PLTRST_DETECTED       3

extern  XBYTE   SMBus5RecoverCunt;
extern  XBYTE   SMBus6RecoverCunt;

extern  XBYTE   KeyScanKSI;
extern  XBYTE   KeyScanKSO;
extern  XBYTE   KeyScanACK;
extern  XBYTE   ExtKeyScanKSI;
extern  XBYTE   ExtKeyScanKSO;
extern  XBYTE   UtilityFlag;

#define KBDebug         BIT6    // 1: for keyboard matrix utility
#define SMBusDebug      BIT7    // 1: for smbus utility

/* Bits 7 and 6 are used to select the scanner table.

   Bit
   7 6  Selection
   --- -----------
   0 0 RAM Table
   0 1 ROM Table 1
   1 0 ROM Table 2
   1 1 ROM Table 3

   shiftSCAN_SELECT is used to shift the bits for the scanner
   selection designation to the lower part of the byte.
   maskSCAN_SELECT is then used to isolate those bits. */
#define shiftSCAN_SELECT    6
#define maskSCAN_SELECT     0x03

#endif // UNUSED

#define _HID_IN_BUF_LEN         64+10
#define _HID_OUT_BUF1_LEN       32
#define _HID_OUT_BUF2_LEN       32

extern XWORD    HID_wRegIndex_A;
extern XBYTE    HID_PowerState;
#define _HID_SET_POWER_SLEEP    0x01
#define _HID_SET_POWER_NORMAL   0x00

extern XBYTE    HID_RegOPCode;
extern XBYTE    HID_RegReportID;
extern XBYTE    HID_RegReportType;
extern XBYTE    HID_ReportType;
extern XBYTE    HID_DescriptorID;
extern XBYTE    HID_InterruptMode;
extern XBYTE    HID_ChannelStatus;
extern XBYTE    HID_ScannerStateL;
extern XBYTE    HID_UsagePage0C_L;
extern XBYTE    HID_UsagePage0C_H;
extern XBYTE    HID_UsagePage0C_Out;
extern XBYTE    HID_i2ecMode;
extern XBYTE    HID_BB_Command;
extern XWORD    HID_wRegIndex_B;
extern XBYTE    HID_KB_Packet[];
extern XBYTE    HID_ScannerStateBreakTimer;
extern XBYTE    HID_PacketCounter;
extern XBYTE    HID_HandshakeBusy;
extern XBYTE    HID_DeviceActived;
#define F_HID_DESC_LAYOUT               BIT0
#define F_HID_REPORT_DESC               BIT1
#define F_HID_OPCODE_RESET              BIT2
#define F_HID_OPCODE_SET_POWER          BIT3

#define F_HID_KB_LED_UPDATE             BIT5
#define F_HID_OPCODE_SET_POWER_ON       BIT6
#define F_HID_OPCODE_SET_POWER_SLEEP    BIT7

extern XBYTE    HID_DevReportBuf[];
extern XBYTE    HID_InBuf_A[];
extern XBYTE    HID_InBuf_B[];
extern XBYTE    HID_OutBuf_A[];
extern XBYTE    HID_OutBuf_B[];

#define _PMC_IN_BUF_LEN         64+10
#define _PMC_OUT_BUF_LEN        64+10
extern XBYTE   PMC_InBuf[];
extern XBYTE   PMC_OutBuf[];

#endif // _ITE_CORE_MEMORY_H

#if 0
/*-----------------------------------------------------------------------------
 * Filename: CORE_MEMORY.H     For Chipset: ITE.IT85XX
 *
 * Function: Memory Definition for extern all code base reference
 *
 * [Memory Map Description]
 *
 * =Chip Internal= 0x00-0xFF
 * 0x00-0xFF     For Kernel and Chip Level use
 *
 ***************************************************
 * Chip 8500       : External ram 0x000-0x7FF
 * Chip Other 85XX : External ram 0x000-0xFFF
 ***************************************************
 * Memory Map :
 * 0x000-0x0FF   For Kernel Core/Module
 * 0x600-0x6FF   For ITE flash utility,EC SPI rom read write function.
 * 0x700-0x7FF   For Keil C Complier and Ram Code Space (for SPI programming).
 *
 * Copyright (c) 2006-2009, ITE Tech. Inc. All Rights Reserved.
 *---------------------------------------------------------------------------*/
#ifndef CORE_DAT_H
#define CORE_DAT_H

//----------------------------------------------------------------------------
// The Controller Command Byte.  Accessed through Commands 20h
// and 60h.  First byte in the 0 through 1F space in an 8042.
//----------------------------------------------------------------------------
#define INTR_KEY     0x01   //bit0
#define INTR_AUX     0x02   //bit1
//#define SYS_FLAG     0x04 //bit2
#define DISAB_KEY    0x10   //bit4
#define DISAB_AUX    0x20   //bit5
#define XLATE_PC     0x40   //bit6

#define all         byte
#define SCROLL      bit0
#define NUM         bit1
#define CAPS        bit2
#define OVL         bit3
#define LED4        bit4
#define LED5        bit5
#define LED6        bit6
#define LED7        bit7

#if 0
extern  IBYTE   KBHICmd;
extern  IBYTE   KBHIStep;
extern  IBYTE   KBHIData;
extern  IBYTE   KBHIData1;
extern  IBYTE   KBHIData2;
extern  IBYTE   PM1Cmd;
extern  IBYTE   PM1Step;
extern  IBYTE   PM1Data;
extern  IBYTE   PM1Data1;
extern  IBYTE   PM1Data2;
extern  IBYTE   PM2Cmd;
extern  IBYTE   PM2DataCount;
extern  IBYTE   PM2Data;
extern  IBYTE   PM2Data1;
extern  IBYTE   PM2Data2;
#else
extern IBYTE    xFSH_AddrH;
extern IBYTE    xFSH_AddrM;
extern IBYTE    xFSH_AddrL;
extern IBYTE    xFSH_Data0;
extern IBYTE    xFSH_Data1;
extern IBYTE    xFSH_Command;
extern IBYTE    xFSH_Position;
extern IBYTE    xFSH_A2_BYTECNT;
extern IWORD    wFSH_ByteCount;
extern IBYTE    xFSH_BSIZE;
extern IBYTE    ICHECKSUM_L;
extern IBYTE    ICHECKSUM_M;
extern IBYTE    ICHECKSUM_H;
extern IBYTE    ICHECKSUM_U;
#endif

extern  IBYTE   Tmp_Load;

//----------------------------------------------------------------------------
// Timer_A, Timer_B
// Bits 0 through 3 of TIMER are reserved for "count".
//----------------------------------------------------------------------------
extern  TIMER Timer_A;      // Timer A. Timer A has a time base of 1 mS.
#define HIF2_SAFETY  count  // Secondary host interface timer.
#define TMR_SCAN     bit4   // Scanner interval enabled.
#define TMR_GENTMO   bit5   // General timeouts.
//                   bit6   //
//                   bit7   //
extern TIMER Timer_B;       // Timer B. Timer A has a time base of 150 uS.
#define SEND_DELAY   count  // Internal device send delay count used with SEND_ENABLE.
#define SEND_ENABLE  bit4   // Internal device send request.
#define INH_CLEAR    bit5   // Delay to enable serial clock lines.
#define UNLOCK_TMO   bit6   // Delay for unlock request.
//                   bit7   //

extern  IBYTE     *data Tmp_Pntr;
extern  IBYTE     Timer1msCnt;        // 0x43
extern  IBYTE     Timer5msCnt;        // 0x44
extern  IBYTE     Timer100msCnt;      // 0x45
extern  IBYTE     Timer100msCntB;     // 0x46
extern  IBYTE     Timer1SecCnt;       // 0x47
extern  IBYTE     TargetDCR1;         // 0x48

extern  BYTE code *data Tmp_code_pointer;
extern  IBYTE     INT_NUM;      // 0x57
extern  IBYTE     INT_CNT;      // 0x58

extern IBYTE      DebugHLOSTx;
extern IBYTE      SPIOPCMD;
//extern  IBYTE   PM3Cmd;             // 0x59
//extern  IBYTE   PM3DataCount;       // 0x5A
//extern  IBYTE   PM3Data;            // 0x5B
//extern  IBYTE   PM3Data1;           // 0x5C
//extern  IBYTE   PM3Data2;           // 0x5D

//extern  IBYTE   MainFucnLow;      // 0x5E
//extern  IBYTE   MainFucnHigh;     // 0x5F
extern  IBYTE   Loopi;
extern  IBYTE   xNTC_Pointer;
extern  IWORD   ITempW02;
//extern  IBYTE   PM1DataCount;

extern  IBYTE   last_new_key_kso_index;
extern  IBYTE   last_new_key_ksi_index;
extern  IBYTE   last_new_accept_time;
extern  IBYTE   ITempB01;
extern  IBYTE   ITempB02;
extern  IBYTE   ITempB03;
extern  IBYTE   ITempB04;
extern  IBYTE   ITempB05;
extern  IBYTE   ITempB06;
extern  IWORD   ITempW01;
extern  IBYTE   bscan_matrix[];

/*****************************************************************************/
/* INTERNAL INDIRECT RAM AREA     (0x80 ~ 0xFF) ******************************/
/*****************************************************************************/
//----------------------------------------------------------------------------
// Internal ram variables (Indirect)[0x80-0xCF]
//----------------------------------------------------------------------------
extern   IIBYTE  xCopyParameter[];
#define  xCopyToPosH       xCopyParameter[0]
extern   IIBYTE  xCopyToPosM;
extern   IIBYTE  xCopyEndPosM;
extern   IIBYTE  xReadAtPosH;
extern   IIBYTE  xReadAtPosM;
extern   IIBYTE  xReadAtPosL;
extern   IIBYTE  iCheckSumBuf[];
//PS2 Port Service
//extern  IIBYTE      AUXInactiveCounter;     // 0x80
//extern    IIBYTE      CheckAUXIndex;      // 0x81
//extern  IIBYTE      TPResolution;           // 0x82
//extern  IIBYTE      TPSamplingRate;         // 0x83
//extern  IIBYTE      PS2_IRQ_Channel;        // 0x84
//extern  IIBYTE      TPACKCounter;           // 0x85
//extern  IIBYTE      AUXCmdFFCnt;            // 0x86
//extern  IIBYTE      AUXPortNum;             // 0x87
//extern  IIBYTE      AuxFlags[];             // 0x88 ~ 0x8A
//#define DEVICE_IS_MOUSE             BIT7
//#define DEVICE_IS_KEYBOARD          BIT6
//#define DEVICE_IS_MAIN_MOUSE        BIT5
//#define DEVICE_IS_MAIN_KB           BIT4
//#define DEVICE_NEED_CONFIG          BIT3
//#define DEVICE_MS_DRIVER_NO_MATCH   BIT2
//#define DEVICE_NEED_INIT            BIT1
//#define DEVICE_IS_ATTACHED          BIT0
//
//extern  IIBYTE      MousePendingBuf;        // 0x8B
//extern  IIBYTE      ScanAUXStepIndex;       // 0x8C
//extern  IIBYTE      AuxFlags2[];            // 0x8D ~ 0x8F
//#define DEVICE_POWER_DOWN           BIT7
//#define DEVICE_ENABLED_TIME_OUT     BIT6
//#define DEVICE_IS_ENABLED           BIT5
//#define DEVICE_NEED_ENABLED         BIT4
//
//#define DEVICE_DISABLE_TIME_OUT     BIT2
//#define DEVICE_IS_DISABLED          BIT1
//#define DEVICE_NEED_DISABLED        BIT0
//
//extern  IIBYTE      MS_ID_CUNT;             // 0x90
//extern  IIBYTE      MS_DRIVER_TYPE;         // 0x91
//
//extern  IIBYTE      KB_CodeSet;             // 0x93
//extern  IIBYTE      PS2KB_Typematic;        // 0x94
//extern  IIBYTE      PS2IFAck;               // 0x95
extern  IIBYTE      Save_Typematic;         // 0x96
//extern  IIBYTE      PS2PortxData[3];        // 0x97
//extern  IIBYTE      KB_Typematic;           // 0x98
//
extern IIBYTE     TIMETICKB0;
extern IIBYTE     TIMETICKB1;
extern IIBYTE     TIMETICKB2;
extern IIBYTE     TIMETICKB3;
extern IIBYTE     TIMETICKB4;
extern IIBYTE     TIMETICKB5;
extern IIBYTE     TIMETICKB6;
extern IIBYTE     TIMETICKB7;
//extern  IIBYTE      Main_MOUSE_CHN;         // 0x9B
//extern  IIBYTE      Main_KB_CHN;            // 0x9C
//extern  IIBYTE      Main_KB_ACK_CUNT;       // 0x9D
//extern  IIBYTE      AUX_SCAN_INDEX;         // 0x9E
//extern  IIBYTE      AUX_SCAN_INDEX_HS;      // 0x9F
//extern  IIBYTE      AUX_SCAN_TIMEOUT_CUNT;  // 0xA0
//extern  IIBYTE      SKIP_AUX_SCAN_CUNT;     // 0xA1
//extern  IIBYTE      AuxFlags_KB_CMD[];      // 0xA2 ~ 0xA4
//#define KB_CMD_0xF5     BIT0
//#define KB_CMD_0xF4     BIT1
//#define KB_CMD_0xF3     BIT2
//#define KB_CMD_0xED     BIT3
//
//extern  IIBYTE      AuxFlags_MS_CMD[];      // 0xA5 ~ 0xA7
//extern  IIBYTE      AuxScanWDT;             // 0xA8;
//
////--- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -
//extern  IIBYTE      PS2_SSIRQ_Channel;      // 0xAA
//extern  IIBYTE      PS2_KBCmd_BK;           // 0xAB
//extern  IIBYTE      KB_Command;             // 0xAC
//extern  IIBYTE      MSPending;              // 0xAD
//extern  IIBYTE      PS2_ReTryCunt;          // 0xAE
//extern  IIBYTE      SMBCRC8_A;              // 0xAF
extern  IIBYTE       FanControlStep;
extern  IIBYTE       PMC_RdIdx;
extern  IIBYTE       PMC_WrIdx;
extern  IIBYTE       xHI2C_AcpiCmdCode;
extern  IIBYTE       xHI2C_AcpiCmdCode2;
extern  IIBYTE       xHI2C_AcpiCmdCode3;
extern  IIBYTE       FAN_XPntr_wLen;
extern  XBYTE   *idata  PMC_XPntr;
extern  XBYTE   *idata  FAN_XPntr;

extern  INT_VAR Int_Var;
//----------------------------------------------------------------------------
// Flag
//----------------------------------------------------------------------------
extern  FLAGS   Flag;
#define SCAN_INH         bit0 // 1 = Scanner transmission inhibited. 
#define SENDING_SCAN_RC  bit1 // For diagnostic mode. 
#define PASS_READY       bit2 // Password loaded. 
#define NEW_PRI_K        bit3 // Switch to new primary keyboard. 
#define NEW_PRI_M        bit4 // Switch to new primary mouse. 
#define VALID_SCAN       bit5
#define LED_ON           bit6
#define ENTER_LOW_POWER  bit7 // Go into low power mode. 
#define ACPI_IN_PROGRESS bit8
#define ACPI_SMB_ALARM   bit9
#define LEGACY_SMB_ALARM bit10
#define ALT_PRESSED      bit11// External keyboard ALT key state. 
#define CTRL_PRESSED     bit12// External keyboard CTRL key state. 
#define DETECT_EC_B0     bit13// Used to allow Insyde Software's 
#define DETECT_EC_B1     bit14// embedded controller to be detected.
#define Aux_Not_RESP     bit15

extern  EXT_CB2     Ext_Cb2;
extern IIBYTE Save_Kbd_State;

/* maskLEDS is used by Keyboard Command EDh to qualify the data.
   If any bits outside of the mask are attempted to be modifed
   by Keyboard Command EDh, the command is rejected. */
#define maskLEDS     0x07

/* shiftCODESET is used to shift the bits for the saved Scan Code
   Set number to the lower part of the byte.  maskCODESET is then
   used to isolate those bits. */
#define shiftCODESET 3
#define maskCODESET  0x03

/* The enabled state of the external keyboard
   modified by Keyboard Command F4h/F5h. */
#define maskAUXENAB  (1 << 5)

/* Bit 0 through 5 used for code. */
#define maskKBD_RESPONSE_CODE 0x03F

/* Multibyte response codes. */
#define respCMD_AC   0x80  // Diagnostic dump.  Sends version string. 
#define respCMD_CFG  0x81  // Configuration Table. 
#define respARRAY    0x82  // Sends bytes in an array. 
// Codes 83h through 8Fh are reserved for the core code.
//extern    IIBYTE      Save_Typematic;
extern  XBYTE   *idata  Tmp_XPntr;
extern  XBYTE   *idata  HID_XPntr;
extern  IIBYTE      KBHIReponse ;
extern  key_state   temp_scanner_state;

extern  LWORD   CodeCheckSum;

extern  XBYTE   bKEY_BUFF[];

#if 1   //SLAVE I2C RESOURCES
extern  IIBYTE  I2C_Tag;
extern  IIBYTE  HID_ScannerState;
extern  IIBYTE  HID_RdIdxA;
extern  IIBYTE  HID_WrIdxA;
extern  IIBYTE  HID_RdIdxB;
extern  IIBYTE  HID_WrIdxB;
#endif


//----------------------------------------------------------------------------
//Pass_xxx
//----------------------------------------------------------------------------
extern  XBYTE   Pass_Buff[];    // Password buffer.
extern  XBYTE   Pass_Buff_Idx;  // Password buffer index
// (0 to PASS_SIZE-1).
extern  XBYTE   Pass_On;        // Security Code On byte.
extern  XBYTE   Pass_Off;       // Security Code Off byte.
extern  XBYTE   Pass_Make1;     // Reject make code 1.
extern  XBYTE   Pass_Make2;     // Reject make code 2.
//extern  XBYTE   PS_Debug_ECToHost;  //_at_ 0x1D
//extern  XBYTE   PS_Debug_DeviceToEC;//_at_ 0x1E
//extern  XBYTE   DebugTest;      //_at_ 0x1F

//*******************************************************
//#ifdef KB_HW_KeyScan   // Hardware scan keyboard
//*******************************************************
extern  XBYTE   KB_HW_ExtendKeyIndex;       // 0x20
extern  XBYTE   KB_HW_ExtendKeyTypematic;   // 0x21

//*******************************************************
//#endif // KB_HW_KeyScan Hardware scan keyboard
//*******************************************************

extern  XBYTE   bTMrepeat;
extern  XBYTE   bTMdelay;
extern  XBYTE   bTMcount;
extern  XBYTE   diode_key;
extern  BYTE code *Scanner_Table_Pntr;
extern  BYTE code *Extendkey_Table_Pntr;
extern  BYTE code *eFlashRom_Pntr;

extern  XBYTE   RunCodeBlockTag;
extern  XBYTE   CodeCheckSumB0;
extern  XBYTE   CodeCheckSumB1;
extern  XBYTE   CodeCheckSumB2;
extern  XBYTE   CodeCheckSumB3;

//extern  XBYTE   PS2BufHead;
//extern  XBYTE   PS2BufTail;
//extern  XBYTE   PS2DataPinStatusCounter;
//extern  XBYTE   PS2TypeCounter; // Dino 1128
extern  XBYTE   WinFlashMark;
extern  XBYTE   RamCodePort;

extern  XBYTE   KBDataPending[];            //_at_ 0x47;
extern  XBYTE   KBPendingRXCount;           //_at_ 0x4B;
extern  XBYTE   KBPendingTXCount;           //_at_ 0x4C;
//extern  XBYTE   PS2DataPinStatus;           //_at_ 0x4D;

//extern  XBYTE   SetShutdownType;
//
//extern  XBYTE   *SMBus1BlockPtr;            // 0x50;    // 2 bytes
//extern  XBYTE   *SMBus2BlockPtr;            // 0x52;    // 2 bytes
//extern  XBYTE   *SMBus3BlockPtr;            // 0x54;    // 2 bytes
//
//extern  XBYTE   DB_SMBusAddr;               // 0x56
//extern  XBYTE   DB_SMBusCmd;                // 0x57
//extern  XBYTE   DB_SMBusBCunt;              // 0x58
//extern  XBYTE   DB_SMBusFlag1;              // 0x59
//extern  XBYTE   DB_SMBusFlag2;              // 0x5A
//extern  XBYTE   DB_SMBusFlag3;              // 0x5B
//#define DB_S    BIT0
//#define DB_R    BIT1
//#define DB_RB   BIT2
//#define DB_WB   BIT3
//#define DB_RW   BIT4
//#define DB_WW   BIT5
//#define DB_RBB  BIT6
//#define DB_WBB  BIT7

//extern  XBYTE   DB_SMBusData[];             // 0x5C 20 bytes
//
//extern  XBYTE   DB_SMBusAck1;               // 0x7c
//extern  XBYTE   DB_SMBusACDID;              // 0x7D

extern  XBYTE   ExtendScanPin;
extern  XBYTE   RSTStatus;
extern  XBYTE   RamcodeCmd;
extern  XBYTE   RamcodeSend;
extern  BYTE code *Tmp_Code_Pntr;
extern  FUNCT_PTR_V_V Tmp_Func_Pnter;
extern  XBYTE   SMBus1RecoverCunt;          // 0x89;
extern  XBYTE   SMBus2RecoverCunt;          // 0x8A;
extern  XBYTE   SMBus3RecoverCunt;          // 0x8B;
extern  XBYTE   SPIWriteStatusL;            // 0x8C;
extern  XBYTE   FN_Key_Break;               // 0x8D;
extern  XBYTE   FN_Key_Break_HS;            // 0x8E;
extern  XBYTE   SMBus_BusyRecover;          // 0x8F;

extern  XBYTE   SPIIDBuf[];             //  _at_ 0x90
extern  XBYTE   SPIIndex;               //  _at_ 0x94
extern  XBYTE   SPIAddrCycle[];         //  _at_ 0x95
extern  XBYTE   SPIAEraseCmd;           //  _at_ 0x98
extern  XBYTE   SPIReadStatus;          //  _at_ 0x99
extern  XBYTE   SPIWriteStatus;         //  _at_ 0x9A
extern  XBYTE   *SPIDataPointer;        //  _at_ 0x9B
#define SPIDataPointerLowByte (*(XBYTE*)( 0x09C))   //  _at_ 0x9C   overlay SPIDataPointer low byte
extern  XBYTE   SPIID;                  //  _at_ 0x9D
extern  XBYTE   SSTDeviceID;            //  _at_ 0x9E
extern  XBYTE   EC_Indirect_Selection;  //  _at_ 0x9F

extern  XBYTE   FnKeyBundledFalg[];     //  _at_ 0xE0 ~ 0xEF, 16 bytes

extern  XBYTE   eSPI_CNT_INT153;
extern  XBYTE   eSPI_CNT_INT154;
extern  XBYTE   eSPI_BUF_VWCTRL1;
extern  XBYTE   eSPI_PLTRST_TAG;
#define F_CLR_PLTRST_STEP       0
#define F_PLTRST_HI_LEVEL       1
#define F_PLTRST_HI_TO_LO       2
#define F_PLTRST_LO_TO_HI       3
#define F_PLTRST_DETECTED       3

extern  XBYTE   SMBus5RecoverCunt;
extern  XBYTE   SMBus6RecoverCunt;

extern  XBYTE   KeyScanKSI;
extern  XBYTE   KeyScanKSO;
extern  XBYTE   KeyScanACK;
extern  XBYTE   ExtKeyScanKSI;
extern  XBYTE   ExtKeyScanKSO;
extern  XBYTE   UtilityFlag;

#define KBDebug         BIT6    // 1: for keyboard matrix utility
#define SMBusDebug      BIT7    // 1: for smbus utility

extern  XBYTE   KBCPortPending; // 0xF0
extern  XBYTE   PMPortPending;  // 0xF1
//extern  XBYTE PS2Buf[];

/* Bits 7 and 6 are used to select the scanner table.

   Bit
   7 6  Selection
   --- -----------
   0 0 RAM Table
   0 1 ROM Table 1
   1 0 ROM Table 2
   1 1 ROM Table 3

   shiftSCAN_SELECT is used to shift the bits for the scanner
   selection designation to the lower part of the byte.
   maskSCAN_SELECT is then used to isolate those bits. */
#define shiftSCAN_SELECT    6
#define maskSCAN_SELECT     0x03


#define _HID_IN_BUF_LEN         64+10
#define _HID_OUT_BUF1_LEN       32
#define _HID_OUT_BUF2_LEN       32

extern XWORD    HID_wRegIndex_A;
extern XBYTE    HID_PowerState;
#define _HID_SET_POWER_SLEEP    0x01
#define _HID_SET_POWER_NORMAL   0x00

extern XBYTE    HID_RegOPCode;
extern XBYTE    HID_RegReportID;
extern XBYTE    HID_RegReportType;
extern XBYTE    HID_ReportType;
extern XBYTE    HID_DescriptorID;
extern XBYTE    HID_InterruptMode;
extern XBYTE    HID_ChannelStatus;
extern XBYTE    HID_ScannerStateL;
extern XBYTE    HID_UsagePage0C_L;
extern XBYTE    HID_UsagePage0C_H;
extern XBYTE    HID_UsagePage0C_Out;
extern XBYTE    HID_i2ecMode;
extern XBYTE    HID_BB_Command;
extern XWORD    HID_wRegIndex_B;
extern XBYTE    HID_KB_Packet[];
extern XBYTE    HID_ScannerStateBreakTimer;
extern XBYTE    HID_PacketCounter;
extern XBYTE    HID_HandshakeBusy;
extern XBYTE    HID_DeviceActived;
#define F_HID_DESC_LAYOUT               BIT0
#define F_HID_REPORT_DESC               BIT1
#define F_HID_OPCODE_RESET              BIT2
#define F_HID_OPCODE_SET_POWER          BIT3

#define F_HID_KB_LED_UPDATE             BIT5
#define F_HID_OPCODE_SET_POWER_ON       BIT6
#define F_HID_OPCODE_SET_POWER_SLEEP    BIT7

extern XBYTE    HID_DevReportBuf[];
extern XBYTE    HID_InBuf_A[];
extern XBYTE    HID_InBuf_B[];
extern XBYTE    HID_OutBuf_A[];
extern XBYTE    HID_OutBuf_B[];

#define _PMC_IN_BUF_LEN         64+10
#define _PMC_OUT_BUF_LEN        64+10
extern XBYTE   PMC_InBuf[];
extern XBYTE   PMC_OutBuf[];

#endif

#endif