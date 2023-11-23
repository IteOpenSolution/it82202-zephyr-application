/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_OEM_MEMORY_H_
#define _ITE_OEM_MEMORY_H_

#include "../include/include.h"
//-----------------------------------------------------------------------------

extern XBYTE    SysPowState;
#define F_PST_BUSY          BIT(7)
extern XBYTE    CtrlPowStep;
extern XWORD    PowSeqDelay;
extern XWORD    PowSeqWait;
extern XBYTE    ResendPowerButton;
extern XBYTE    PowerOnFailed;
extern XBYTE    PowSwFlag;
#define F_PSW_WAIT_UP       BIT(0)
#define F_PSW_UP_DELAY      BIT(1)
#define F_PSW_UART_DN       BIT(2)
#define F_PSW_UART_UP       BIT(3)

#define F_PSW_EVT_BREAK     BIT(5)
#define F_PSW_SCANCODE      BIT(6)
#define F_PSW_RSMRST        BIT(7)
extern XWORD    PowSwLockTimer;
extern XWORD    PowSwDownTimer;
extern XWORD    PowSwDebounce;
extern XWORD    wPwrSwTypingDelay;
extern XWORD    wLockPWRBTN;
extern XBYTE    SetAutoBootTimer;
extern XBYTE    AutoBootTimer;
extern XBYTE    xPSHOLD_HiDelay;
extern XBYTE    xPSHOLD_LoDelay;
extern XBYTE    xEC_VerUartOut;
extern XBYTE    LID_Debounce;
extern XBYTE    LID_OpenDebounce;
extern XWORD    LID_Resend;
extern XWORD    LID_OpenResend;
extern XBYTE    xEC_FanUartOut;

//-----------------------------------------------------------------------------
extern XBYTE    xFAN_ProfileSwitch[];
extern XBYTE    xNUM_LUTS[];
extern XBYTE    xFAN_QC_TEST[];
extern XBYTE    TFanProfileSwitch;
extern XBYTE    xNTC_SampleRateSet;
extern XBYTE    xNTC_SampleRate[];

//-----------------------------------------------------------------------------
extern XBYTE    xHI2C_EC_VER[];
extern XBYTE    xHI2C_BAT1_BST1[];
#define F_BATT_DISCHARGING  BIT(0)
#define F_BATT_CHARGING     BIT(1)
#define F_BATT_CRITICAL     BIT(2)
#define F_BATT_LOW          BIT(3)
#define F_BATT_PRESENT      BIT(6)
#define F_ADAPTER_IN        BIT(7)
extern XBYTE    xHI2C_BAT1_BIF1[];
extern XBYTE    xHI2C_BAT1_BTP1[];
extern XBYTE    xHI2C_DataReadyA0;
extern XBYTE    xACPI_AC_RSOC[];
extern XBYTE    xACPI_EC_STATE[];
extern XBYTE    xHI2C_BBK_VER[];

//-----------------------------------------------------------------------------
extern XBYTE    SCIEVT_BUF[];
extern XBYTE    SCIEVT_WIDX;
extern XBYTE    SCIEVT_RIDX;
extern XBYTE    SCIEVT_OUT;
extern XBYTE    SCIEVT_LOSE;
extern XBYTE    SCIEVT_OVT;
extern XBYTE    SCIEVT_DELAY;
extern XBYTE    SCIEVT_LAST;
extern XBYTE    SCIEVT_CNT;
extern XBYTE    SCIEVT_ENABLED;
extern XBYTE    SCIEVT_FAN1_STS;
extern XBYTE    SCIEVT_FAN2_STS;
extern XBYTE    SCIEVT_DIS_TMR;

//-----------------------------------------------------------------------------
extern LWORD    dwMainCheckSum;
extern LWORD    dwAllCheckSum;
extern LWORD    dwTempCheckSum;

//-----------------------------------------------------------------------------
extern XBYTE    xMSBY_Mode;
extern XBYTE    xMSBY_SleepCounter;
extern XBYTE    xMSBY_DozeCounter;
extern XBYTE    xMSBY_ServiceKey;
extern XBYTE    xMSBY_ExitKey;
extern XBYTE    xMSBY_EnLidOpenWake;


extern XBYTE    xMSBY_GetBatteryStep;
extern XBYTE    xMSBY_GetThermalStep;
extern XWORD    wMSBY_SLP_S0_LoT;
extern XWORD    wMSBY_SLP_S0_HiT;
extern XWORD    wMSBY_EnterDelay;
extern XBYTE    xMSBY_SleepDelay;
extern XBYTE    xSLPM_RESUME;
extern XBYTE    xECPW_DeepSleepDelay;
extern XBYTE    xECPW_S5toG3delay;
extern XBYTE    xMSTBY_STEP;
extern XBYTE    xMSTBY_NOTIFY;
#define F_ENTER_MODERN_STANDBY  BIT0
extern XBYTE    SaveNVTimer;

#define F_MS_FAN_STOP_SCI_OK    BIT7
#define F_EXIT_MS_NEED_SCI      BIT2
#define F_ENTER_MS_INIT_OK      BIT1
#define F_IN_MODERN_STANBY      BIT0

//-----------------------------------------------------------------------------
extern XBYTE    xDBG_UartDispTimer1;
extern XBYTE    xDBG_UartDisp;
extern XBYTE    xDBG_UartDisp2;
extern XBYTE    xMSM_SleepCounter;
extern XBYTE    xMSM_AP_SUSPEND;

//-----------------------------------------------------------------------------
extern XBYTE    xEC_MainVersion;
extern XBYTE    xEC_SubVersion;
extern XBYTE    xEC_KBCVersion;
extern XBYTE    xEC_TestVersion;
extern XBYTE    xEC_BoardID;
extern XBYTE    xEC_BetaVersion;
extern XBYTE    xBoard_ID_ADC;
extern XBYTE    xEC_KB_Backlight;
extern XBYTE    xHI2C_EC_FULL_VER[];

//-----------------------------------------------------------------------------
extern XWORD    wADC[];
extern XWORD    T_wACC[];
extern XBYTE    xADC[];
extern XBYTE    xADC_Scan;
extern XBYTE    xADC_Timer;
extern XBYTE    xADC_Count;
extern XBYTE    T_AVG_CNT;
extern XWORD    TFanRomPointer;

extern XBYTE    xFanMinDCRLevel;
extern XBYTE    TFanDebugCommand;

//-----------------------------------------------------------------------------
extern XBYTE    xHLOS_TMPR[];
extern XBYTE    xHLOS_T[];

//-----------------------------------------------------------------------------
extern XBYTE    T_PktHead[];
extern XBYTE    T_Sensors[];
extern XBYTE    xNTC_DebugKey;
extern XBYTE    TFanTemperature[];
extern XBYTE    TFanTblPointer[];
extern XBYTE    TFanTargetRPMs[];

extern XBYTE    Fan1_EventDelay;
extern XBYTE    Fan1_TripAutoMode;
extern XBYTE    Fan2_EventDelay;
extern XBYTE    Fan2_TripAutoMode;

extern XWORD    wFan1_EventRPM_H;
extern XWORD    wFan1_EventRPM_L;
extern XWORD    wFan2_EventRPM_H;
extern XWORD    wFan2_EventRPM_L;

//-----------------------------------------------------------------------------
extern XBYTE    xFAN1_PACKET[];
extern XBYTE    xFAN1_TRIP_H[];
extern XBYTE    xFAN1_TRIP_L[];
extern XBYTE    xFAN1_STATUS[];
#define _FAN_STS_OFF        0x00
#define _FAN_STS_ON         0x01
#define _FAN_STS_ERR        0x02
extern XBYTE    xFAN1_STATUS_L;
extern XBYTE    xFAN1_2S_EVENT;

extern XBYTE    Fan1_CalibraDelay;
extern XBYTE    xFAN1_ProfileNum[];
extern XBYTE    xFAN1_NumLUTs[];

//-----------------------------------------------------------------------------
extern XBYTE    xFAN2_PACKET[];
extern XBYTE    xFAN2_TRIP_H[];
extern XBYTE    xFAN2_TRIP_L[];
extern XBYTE    xFAN2_STATUS[];
extern XBYTE    xFAN2_STATUS_L;
extern XBYTE    xFAN2_2S_EVENT;

extern XBYTE    Fan2_CalibraDelay;
extern XBYTE    xFAN2_ProfileNum[];
extern XBYTE    xFAN2_NumLUTs[];

//-----------------------------------------------------------------------------
extern XBYTE    Fan1_DnTempr;
extern XBYTE    Fan1_RefTempr;
extern XBYTE    Fan1_UpTempr;
extern XBYTE    Fan1_LevelDir;
extern XBYTE    Fan1_InitDCR;
extern XBYTE    Fan1_NowDCR;
extern XWORD    wFan1_TargetRPM;
extern XWORD    wFan1_CurrentRPM;
extern XBYTE    Fan1_Up_Delay;
extern XBYTE    Fan1_Step;
extern XBYTE    Fan1_NeedInit;
extern XBYTE    Fan1_Error;
extern XBYTE    Fan1_DebugCmd2;
extern XBYTE    Fan1_DebugCmd;
extern XBYTE    Fan1_DebugKey;

//-----------------------------------------------------------------------------
extern XBYTE    Fan2_DnTempr;
extern XBYTE    Fan2_RefTempr;
extern XBYTE    Fan2_UpTempr;
extern XBYTE    Fan2_LevelDir;
extern XBYTE    Fan2_InitDCR;
extern XBYTE    Fan2_NowDCR;
extern XWORD    wFan2_TargetRPM;
extern XWORD    wFan2_CurrentRPM;
extern XBYTE    Fan2_Up_Delay;
extern XBYTE    Fan2_Step;
extern XBYTE    Fan2_NeedInit;
extern XBYTE    Fan2_Error;
extern XBYTE    Fan2_DebugCmd2;
extern XBYTE    Fan2_DebugCmd;
extern XBYTE    Fan2_DebugKey;

extern XBYTE    xFANx_LUT[];
extern XBYTE    xRamProfileNum;
extern XBYTE    xFanProfileNum;
extern XBYTE    xFanLUTsNum;
extern XBYTE    xFanLUTsGetSetError;

extern XBYTE    xNTC_PSV[];
extern XBYTE    xNTC_CR3[];
extern XBYTE    xNTC_HOT[];
extern XBYTE    xNTC_CRT[];
extern XBYTE    xNTC_LEVEL[];
extern XBYTE    xNTC_EVTCNT;
extern XBYTE    xNTC_ActiveEvent;
extern XBYTE    xNTC_SampleCount;
extern XWORD    wNTC_SampleCounter;

extern XBYTE    RamBuffer1[];
extern XBYTE    RamBuffer2[];
extern XBYTE    FLASH_BUF[];

#endif // _ITE_OEM_MEMORY_H_
