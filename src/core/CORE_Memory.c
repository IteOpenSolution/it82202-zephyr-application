/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

//----------------------------------------------------------------------------
// Internal ram variables (direct)[0x30-0x7F]
//----------------------------------------------------------------------------
IBYTE xFSH_AddrH;
IBYTE xFSH_AddrM;
IBYTE xFSH_AddrL;
#if UNUSED
IBYTE xFSH_Data0;
IBYTE xFSH_Data1;
#endif // UNUSED
IBYTE xFSH_Command;
IBYTE xFSH_Position; // 0x4F internal 0x0F external

IBYTE xFSH_A2_BYTECNT;
IWORD wFSH_ByteCount;
IBYTE xFSH_BSIZE;
IBYTE ICHECKSUM_L;
IBYTE ICHECKSUM_M;
IBYTE ICHECKSUM_H;
IBYTE ICHECKSUM_U;
#if UNUSED
TIMER Timer_A;
TIMER Timer_B;
IBYTE *data Tmp_Pntr;
IBYTE Timer1msCnt;
IBYTE Timer5msCnt;
IBYTE Timer100msCnt;
IBYTE Timer100msCntB;
IBYTE Timer1SecCnt;
IBYTE TargetDCR1;
data union Unew_keyl new_keyl;
data struct Sscan scan;       // 3 BYTES
data union KEY new_keyh;      // Holds new scan key address and debounce status.
data union KEY typematic;     // Holds new_keyh for typematic action.
data union KEY new_extendkey; // For extend keys
data struct Sscan extendscan; // 3 BYTES
data union Unew_keyl extendstatus;
data union KEY etkeytypematic;
BYTE code *data Tmp_code_pointer;
IBYTE INT_NUM;
IBYTE INT_CNT;
#endif // UNUSED

IBYTE DebugHLOSTx;
#if UNUSED
IBYTE SPIOPCMD;

IBYTE Loopi;
IBYTE xNTC_Pointer;
IWORD ITempW02;

IBYTE last_new_key_kso_index;
IBYTE last_new_key_ksi_index;
IBYTE last_new_accept_time;
#endif // UNUSED
IBYTE ITempB01; /* Don't Move */
IBYTE ITempB02;
IBYTE ITempB03;
IBYTE ITempB04;
IBYTE ITempB05;
IBYTE ITempB06;
IWORD ITempW01;
#if UNUSED
IBYTE bscan_matrix[MAX_SCAN_LINES];

//----------------------------------------------------------------------------
// Internal ram variables (Indirect)[0x80-0xCF]
//----------------------------------------------------------------------------
IIBYTE xCopyParameter[1];
IIBYTE xCopyToPosM;
IIBYTE xCopyEndPosM;
IIBYTE xReadAtPosH;
IIBYTE xReadAtPosM;
IIBYTE xReadAtPosL;
IIBYTE iCheckSumBuf[10];

IIBYTE Save_Typematic;
#endif // UNUSED

IIBYTE I2C_Tag;

#if UNUSED
IIBYTE HID_ScannerState;

IIBYTE TIMETICKB0;
IIBYTE TIMETICKB1;
IIBYTE TIMETICKB2;
IIBYTE TIMETICKB3;
IIBYTE TIMETICKB4;
IIBYTE TIMETICKB5;
IIBYTE TIMETICKB6;
IIBYTE TIMETICKB7;

IIBYTE FanControlStep;
#endif // UNUSED

IIBYTE PMC_RdIdx;
IIBYTE PMC_WrIdx;


IIBYTE xHI2C_AcpiCmdCode;
IIBYTE xHI2C_AcpiCmdCode2;
IIBYTE xHI2C_AcpiCmdCode3;
IIBYTE FAN_XPntr_wLen;
XBYTE *PMC_XPntr; // 2 bytes
XBYTE *FAN_XPntr; // 2 bytes
#if UNUSED
INT_VAR Int_Var; // 2 bytes
FLAGS Flag;      // 2 bytes
EXT_CB2 Ext_Cb2;
IIBYTE Save_Kbd_State;
#endif
XBYTE *Tmp_XPntr; // 2 bytes

XWORD *HID_XPntr; // 2 bytes
#if UNUSED
key_state temp_scanner_state;
#endif // UNUSED
IIBYTE HID_RdIdxA;
IIBYTE HID_WrIdxA;
IIBYTE HID_RdIdxB;
IIBYTE HID_WrIdxB;

#if UNUSED
//****************************************************************************
// Stack                             0xD0 - 0xFF         // 48 bytes
//
// Don't use Idata (0xD0 ~ 0xFF).
// Idata (0xD0 ~ 0xFF). for stack point.
//****************************************************************************

//----------------------------------------------------------------------------
// External ram variables (0x00 ~ 0xFF)
//----------------------------------------------------------------------------
XBYTE bKEY_BUFF[KBF_SIZE]; // Scanned keyboard buffer storage.
XBYTE Pass_Buff[8];
XBYTE Pass_Buff_Idx;
XBYTE Pass_On;
XBYTE Pass_Off;
XBYTE Pass_Make1;
XBYTE Pass_Make2;

//*******************************************************
#ifdef KB_HW_KeyScan // Hardware scan keyboard
//*******************************************************
XBYTE KB_HW_ExtendKeyIndex;
XBYTE KB_HW_ExtendKeyTypematic;

//*******************************************************
#endif               // KB_HW_KeyScan Hardware scan keyboard
//*******************************************************
// 0x22

XBYTE bTMrepeat;
XBYTE bTMdelay;
XBYTE bTMcount;
XBYTE diode_key;
BYTE code *Scanner_Table_Pntr;
BYTE code *Extendkey_Table_Pntr;
BYTE code *eFlashRom_Pntr;
// Reserved 0x2B ~ 0x3B
XBYTE RunCodeBlockTag;
XBYTE CodeCheckSumB0;
XBYTE CodeCheckSumB1;
XBYTE CodeCheckSumB2;
XBYTE CodeCheckSumB3;

XBYTE WinFlashMark;
XBYTE RamCodePort;

XBYTE KBDataPending[4];
XBYTE KBPendingRXCount;
XBYTE KBPendingTXCount;

// Reserved 0x7E ~ 0x80

XBYTE ExtendScanPin;
XBYTE RSTStatus;
XBYTE RamcodeCmd;
XBYTE RamcodeSend;
BYTE code *Tmp_Code_Pntr;
FUNCT_PTR_V_V Tmp_Func_Pnter;
XBYTE SMBus1RecoverCunt;
XBYTE SMBus2RecoverCunt;
XBYTE SMBus3RecoverCunt;
XBYTE SPIWriteStatusL;
XBYTE FN_Key_Break;
XBYTE FN_Key_Break_HS;
XBYTE SMBus_BusyRecover;

XBYTE SPIIDBuf[4];
XBYTE SPIIndex;
XBYTE SPIAddrCycle[3];
XBYTE SPIAEraseCmd;
XBYTE SPIReadStatus;
#endif
XBYTE SPIWriteStatus;
#if UNUSED
XBYTE *SPIDataPointer;
XBYTE SPIID;
XBYTE SSTDeviceID;
XBYTE EC_Indirect_Selection;

// Reserved 0xA0 ~ 0xDF

XBYTE FnKeyBundledFalg[16];

XBYTE SMBus5RecoverCunt;
XBYTE SMBus6RecoverCunt;

XBYTE KeyScanKSI;
XBYTE KeyScanKSO;
XBYTE KeyScanACK;
XBYTE ExtKeyScanKSI;
XBYTE ExtKeyScanKSO;
XBYTE UtilityFlag;
#endif // UNUSED

#if UNUSED
// redefine in CORE_Memory.h
#define _HID_IN_BUF_LEN 64 + 10
#define _HID_OUT_BUF1_LEN 32
#define _HID_OUT_BUF2_LEN 32
#endif 

#define HIDA_MemBase 0x0100

XWORD HID_wRegIndex_A;
XBYTE HID_PowerState;
XBYTE HID_RegOPCode;
XBYTE HID_RegReportID;
XBYTE HID_RegReportType;
XBYTE HID_ReportType;
XBYTE HID_DescriptorID;
XBYTE HID_InterruptMode;
XBYTE HID_ChannelStatus;
XBYTE HID_ScannerStateL;
XBYTE HID_UsagePage0C_L;
XBYTE HID_UsagePage0C_H;
XBYTE HID_UsagePage0C_Out;
XBYTE HID_i2ecMode;
XBYTE HID_BB_Command;
XWORD HID_wRegIndex_B;
XBYTE HID_KB_Packet[6];
XBYTE HID_ScannerStateBreakTimer;
XBYTE HID_PacketCounter;
XBYTE HID_HandshakeBusy;
XBYTE HID_DeviceActived;
XBYTE HID_DevReportBuf[4];
XBYTE HID_OutBuf_A[_HID_OUT_BUF1_LEN];
XBYTE HID_OutBuf_B[_HID_OUT_BUF2_LEN];
XBYTE HID_InBuf_A[_HID_IN_BUF_LEN];
XBYTE HID_InBuf_B[_HID_IN_BUF_LEN];

#define PMC_MemBase 0x0200
#if UNUSED
// redefine in CORE_Memory.h
#define _PMC_IN_BUF_LEN 64 + 10
#define _PMC_OUT_BUF_LEN 64 + 10
#endif 
XBYTE PMC_InBuf[_PMC_IN_BUF_LEN];
XBYTE PMC_OutBuf[_PMC_OUT_BUF_LEN];
