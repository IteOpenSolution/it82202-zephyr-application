/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"
//-----------------------------------------------------------------------------

XBYTE   SysPowState                 ;
XBYTE   CtrlPowStep                 ;
XWORD   PowSeqDelay                 ;
XWORD   PowSeqWait                  ;
XBYTE   UpdateTest                  ;
XBYTE   PowerOnFailed               ;
XBYTE   PowSwFlag                   ;
XBYTE   SetAutoBootTimer            ;
XBYTE   AutoBootTimer               ;
XBYTE   xPSHOLD_HiDelay             ;
XBYTE   xPSHOLD_LoDelay             ;
XBYTE   xEC_VerUartOut              ;
XBYTE   LID_Debounce                ;
XBYTE   LID_OpenDebounce            ;
XWORD   PowSwLockTimer              ;
XWORD   PowSwDownTimer              ;
XWORD   PowSwDebounce               ;
XWORD   wPwrSwTypingDelay           ;
XWORD   wLockPWRBTN                 ;
XWORD   LID_Resend                  ;
XWORD   LID_OpenResend              ;
XBYTE   xEC_FanUartOut              ;

//-----------------------------------------------------------------------------
XBYTE   xFAN_ProfileSwitch[2]       ;
XBYTE   xNUM_LUTS[2]                ;
XBYTE   xFAN_QC_TEST[6]             ;
XBYTE   TFanProfileSwitch           ;
XBYTE   xNTC_SampleRateSet          ;
XBYTE   xNTC_SampleRate[4]          ;

//-----------------------------------------------------------------------------
XBYTE   xHI2C_EC_VER[4]             ;
XBYTE   xHI2C_BAT1_BST1[12]         ;
XBYTE   xHI2C_BAT1_BIF1[12]         ;
XBYTE   xHI2C_BAT1_BTP1[2]          ;
XBYTE   xHI2C_DataReadyA0           ;
XBYTE   xACPI_AC_RSOC[4]            ;
XBYTE   xACPI_EC_STATE[4]           ;
XBYTE   xHI2C_BBK_VER[4]            ;
//-----------------------------------------------------------------------------
XBYTE   SCIEVT_BUF[16]              ;
XBYTE   SCIEVT_WIDX                 ;
XBYTE   SCIEVT_RIDX                 ;
XBYTE   SCIEVT_OUT                  ;
XBYTE   SCIEVT_LOSE                 ;
XBYTE   SCIEVT_OVT                  ;
XBYTE   SCIEVT_DELAY                ;
XBYTE   SCIEVT_LAST                 ;
XBYTE   SCIEVT_CNT                  ;
XBYTE   SCIEVT_ENABLED              ;
XBYTE   SCIEVT_FAN1_STS             ;
XBYTE   SCIEVT_FAN2_STS             ;
XBYTE   SCIEVT_DIS_TMR              ;

//-----------------------------------------------------------------------------
LWORD   dwMainCheckSum              ;
LWORD   dwAllCheckSum               ;
LWORD   dwTempCheckSum              ;

//-----------------------------------------------------------------------------
XBYTE   xMSBY_Mode                  ;
XBYTE   xMSBY_SleepCounter          ;
XBYTE   xMSBY_DozeCounter           ;
XBYTE   xMSBY_ServiceKey            ;
XBYTE   xMSBY_ExitKey               ; /* 03E0 */
XBYTE   xMSBY_EnLidOpenWake         ;
XBYTE   xMSBY_GetBatteryStep        ;
XBYTE   xMSBY_GetThermalStep        ;
XWORD   wMSBY_SLP_S0_LoT            ;
XWORD   wMSBY_SLP_S0_HiT            ;
XWORD   wMSBY_EnterDelay            ;
XBYTE   xMSBY_SleepDelay            ;
XBYTE   xSLPM_RESUME                ;
XBYTE   xECPW_DeepSleepDelay        ;
XBYTE   xECPW_S5toG3delay           ;
XBYTE   xMSTBY_STEP                 ;
XBYTE   xMSTBY_NOTIFY               ;
XBYTE   SaveNVTimer                 ;

//-----------------------------------------------------------------------------
XBYTE   xDBG_UartDispTimer1         ;
XBYTE   xDBG_UartDisp               ;
XBYTE   xDBG_UartDisp2              ;
XBYTE   xMSM_SleepCounter           ;
XBYTE   xMSM_AP_SUSPEND             ;

//-----------------------------------------------------------------------------
/*****************************************************************************/
/* STANDARD RAM AREA      (0x0400 ~ 0x04FF) **********************************/
/*****************************************************************************/
//-----------------------------------------------------------------------------
XBYTE   xEC_MainVersion             ;
XBYTE   xEC_SubVersion              ;
XBYTE   xEC_KBCVersion              ;
XBYTE   xEC_TestVersion             ;
XBYTE   xEC_BoardID                 ;
XBYTE   xEC_BetaVersion             ;
XBYTE   xBoard_ID_ADC               ;
XBYTE   xEC_KB_Backlight            ;
XBYTE   xHI2C_EC_FULL_VER[8]        ;

//-----------------------------------------------------------------------------
XWORD   wADC[8]                     ;
XWORD   T_wACC[8]                   ;
XBYTE   xADC[8]                     ;
XBYTE   xADC_Scan                   ;
XBYTE   xADC_Timer                  ;
XBYTE   xADC_Count                  ;
XBYTE   T_AVG_CNT                   ;
XWORD   TFanRomPointer              ;

XBYTE   xFanMinDCRLevel             ;
XBYTE   TFanDebugCommand            ;
//-----------------------------------------------------------------------------
XBYTE   xHLOS_TMPR[24]              ;
XBYTE   xHLOS_T[8]                  ;

//-----------------------------------------------------------------------------
XBYTE   T_PktHead[1]                ;   /* Notes:combine next. */
XBYTE   T_Sensors[9]                ;   /* Notes:combine upper. */
XBYTE   xNTC_DebugKey               ;
XBYTE   TFanTemperature[9]          ;
XBYTE   TFanTblPointer[9]           ;
XBYTE   TFanTargetRPMs[9]           ;

XBYTE   Fan1_EventDelay             ;
XBYTE   Fan1_TripAutoMode           ;
XBYTE   Fan2_EventDelay             ;
XBYTE   Fan2_TripAutoMode           ;

XWORD   wFan1_EventRPM_H            ;
XWORD   wFan1_EventRPM_L            ;
XWORD   wFan2_EventRPM_H            ;
XWORD   wFan2_EventRPM_L            ;

//-----------------------------------------------------------------------------
XBYTE   xFAN1_PACKET[3]             ;
XBYTE   xFAN1_TRIP_H[3]             ;    /* Maybe Move to NV */
XBYTE   xFAN1_TRIP_L[3]             ;    /* Maybe Move to NV */
XBYTE   xFAN1_STATUS[2]             ;
XBYTE   xFAN1_STATUS_L              ;
XBYTE   xFAN1_2S_EVENT              ;

XBYTE   Fan1_CalibraDelay           ;
XBYTE   xFAN1_ProfileNum[2]         ;
XBYTE   xFAN1_NumLUTs[4]            ;

//-----------------------------------------------------------------------------
XBYTE   xFAN2_PACKET[3]             ;
XBYTE   xFAN2_TRIP_H[3]             ;    /* Maybe Move to NV */
XBYTE   xFAN2_TRIP_L[3]             ;    /* Maybe Move to NV */
XBYTE   xFAN2_STATUS[2]             ;
XBYTE   xFAN2_STATUS_L              ;
XBYTE   xFAN2_2S_EVENT              ;

XBYTE   Fan2_CalibraDelay           ;
XBYTE   xFAN2_ProfileNum[2]         ;
XBYTE   xFAN2_NumLUTs[4]            ;

//-----------------------------------------------------------------------------
XBYTE   Fan1_DnTempr                ;
XBYTE   Fan1_RefTempr               ;
XBYTE   Fan1_UpTempr                ;
XBYTE   Fan1_LevelDir               ;
XBYTE   Fan1_InitDCR                ;
XBYTE   Fan1_NowDCR                 ;
XWORD   wFan1_TargetRPM             ;
XWORD   wFan1_CurrentRPM            ;
XBYTE   Fan1_Error                  ;
XBYTE   Fan1_Step                   ;
XBYTE   Fan1_NeedInit               ;
XBYTE   Fan1_DebugCmd2              ;
XBYTE   Fan1_DebugCmd               ;
XBYTE   Fan1_DebugKey               ;

//-----------------------------------------------------------------------------
XBYTE   Fan2_DnTempr                ;
XBYTE   Fan2_RefTempr               ;
XBYTE   Fan2_UpTempr                ;
XBYTE   Fan2_LevelDir               ;
XBYTE   Fan2_InitDCR                ;
XBYTE   Fan2_NowDCR                 ;
XWORD   wFan2_TargetRPM             ;
XWORD   wFan2_CurrentRPM            ;
XBYTE   Fan2_Error                  ;
XBYTE   Fan2_Step                   ;
XBYTE   Fan2_NeedInit               ;
XBYTE   Fan2_DebugCmd2              ;
XBYTE   Fan2_DebugCmd               ;
XBYTE   Fan2_DebugKey               ;

XBYTE   xFANx_LUT[128]              ;
XBYTE   xRamProfileNum = 6              ;
XBYTE   xFanProfileNum              ;
XBYTE   xFanLUTsNum                 ;
XBYTE   xFanLUTsGetSetError         ;

XBYTE   xNTC_PSV[6]                 ;
XBYTE   xNTC_CR3[6]                 ;
XBYTE   xNTC_HOT[6]                 ;
XBYTE   xNTC_CRT[6]                 ;
XBYTE   xNTC_LEVEL[6]               ;
XBYTE   xNTC_EVTCNT                 ;
XBYTE   xNTC_ActiveEvent            ;
XBYTE   xNTC_SampleCount            ;
XWORD   wNTC_SampleCounter          ;


XBYTE   RamBuffer1[256]             ;
XBYTE   RamBuffer2[256]             ;
XBYTE   FLASH_BUF[256]              ;
