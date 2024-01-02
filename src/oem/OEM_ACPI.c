/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

/*-----------------------------------------------------------------------------
 * Local Parameter Process Definition
 *---------------------------------------------------------------------------*/
#define DEBUG_EC6266 FALSE
#define DEBUG_EC6266_READ FALSE
#define DEBUG_EC6266_WRITE FALSE
#define DEBUG_SCIEVT FALSE
#define DEBUG_DISABLE_SCIEVT FALSE

/*-----------------------------------------------------------------------------
 * Depends on parameter definition
 *---------------------------------------------------------------------------*/
#if DEBUG_EC6266
#define EC6266_RamDebug(x) RamDebug(x)
#else
#define EC6266_RamDebug(x) \
    {                      \
    }
#endif
#if DEBUG_SCIEVT
#define SCIEVT_RamDebug(x) RamDebug(x)
#else
#define SCIEVT_RamDebug(x) \
    {                      \
    }
#endif

#if UNUSED

/*-----------------------------------------------------------------------------
 * Local Calling Prototype
 *---------------------------------------------------------------------------*/

//-----------------------------------------------------------------------------
//*****************************************************************************
// CODE START
//*****************************************************************************
//-----------------------------------------------------------------------------
/*-----------------------------------------------------------------------------
 * @subroutine - SCI_EventCenter
 * @function - SCI_EventCenter
 * @upstream - Hook_Timer5msEvent
 * @input    - None
 * @return   - None
 * @note     - None
 */
void SCI_EventCenter(void)
{
#if 0
    if (IS_MASK_SET(HID_DeviceActived, F_HID_OPCODE_SET_POWER_SLEEP) ||
            (HID_HandshakeBusy > 0))
    {
        return;
    }
#else
    if ((!SCIEVT_ENABLED) || (HID_HandshakeBusy))
    {
        return;
    }
    // if (SCIEVT_DIS_TMR > 0)
    //{
    //     SCIEVT_DIS_TMR--;
    //     if (SCIEVT_DIS_TMR == 0)
    //     {
    //         SCIEVT_ENABLED = 0;
    //         return;
    //     }
    // }
#endif
#if DEBUG_DISABLE_SCIEVT
    if (SCIEVT_OUT != 0)
    {
        SCIEVT_OUT = 0;
        SCIEVT_OVT++;
        return;
    }
    if (SCIEVT_RIDX == SCIEVT_WIDX)
    {
        return;
    }
    ReadSCI_Buffer();
    return;
#endif
    if (SCIEVT_DELAY != 0)
    {
        SCIEVT_DELAY--;
        return;
    }
#if 0 /* 0: 8cGenX only S0 status */
    if (SysPowState != _SYSTEM_S0)
    {
        if (SCIEVT_OUT != 0)
        {
            printf("\nEC NOT S0 SCI[%bX]", SCIEVT_OUT);
            SCIEVT_DELAY = 20;  //20*5=100ms
        }
        return;
    }
#endif
    if (SCIEVT_OUT != 0)
    {
        // printf("\nECRS[%bX]", SCIEVT_OUT);
#if SUPPORT_HID_PLATFORM
        INTERRUPT_ACPI_LO();
        WNCKR = 0x00; // Delay 15.26 us
        WNCKR = 0x00; // Delay 15.26 us
        WNCKR = 0x00; // Delay 15.26 us
        INTERRUPT_ACPI_HI();
#else
        OEM_ACPI_Gen_Int();
#endif
        SCIEVT_DELAY = 20; // 20*5=100ms  (Resend delay)
        SCIEVT_OVT++;
        return;
    }
    if (SCIEVT_RIDX == SCIEVT_WIDX)
    {
        SCIEVT_RIDX = 0;
        SCIEVT_WIDX = 0;
        SCIEVT_BUF[0] = 0;
        return;
    }
    ReadSCI_Buffer();
#if SUPPORT_HID_PLATFORM
    INTERRUPT_ACPI_LO();
    WNCKR = 0x00; // Delay 15.26 us
    WNCKR = 0x00; // Delay 15.26 us
    INTERRUPT_ACPI_HI();
#else
    OEM_ACPI_Gen_Int();
#endif
    SCIEVT_DELAY = 1; // Next Event Delay: 1*5ms = 5ms
    // DebugUartTimeStamp(1);
    // printf("\nECOS[%bX]", SCIEVT_OUT);
}

/*-----------------------------------------------------------------------------
 * @subroutine - ReadSCI_Buffer
 * @function - Read SCI Event Buffer
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void ReadSCI_Buffer(void)
{
    SCIEVT_OUT = SCIEVT_BUF[SCIEVT_RIDX];
    SCIEVT_LAST = SCIEVT_OUT;
    SCIEVT_RIDX = (SCIEVT_RIDX + 1) & 0x0F;
    SET_MASK(PM1STS, SCIEVT);
    SCIEVT_RamDebug(SCIEVT_LAST);
    DebugUartTimeStamp(1);
    printf("\nHOSTG[%bX]", SCIEVT_LAST);
}
#endif /* UNUSED */
/*-----------------------------------------------------------------------------
 * @subroutine - WriteSCI_Buffer
 * @function - Write SCI Event Buffer
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void WriteSCI_Buffer(BYTE SCI_NUM, BYTE PRIORITY)
{
#if TODO
    BYTE i;

    if (!SCIEVT_ENABLED)
    {
        return;
    }

    SCIEVT_CNT++;
    i = (SCIEVT_WIDX + 1) & 0x0F;

    if (i == SCIEVT_RIDX)
    {
        SCIEVT_LOSE++;
        Clear_SCI_Buffer();
        return;
    }
    SCIEVT_BUF[SCIEVT_WIDX] = SCI_NUM;
    SCIEVT_WIDX = i;
    DebugUartTimeStamp(1);
#endif /* TODO */
}
#if UNUSED
/*-----------------------------------------------------------------------------
 * @subroutine - Clear_SCI_Buffer
 * @function - Clear SCI Event Buffer
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Clear_SCI_Buffer(void)
{
    for (ITempB01 = 0; ITempB01 < 18; ITempB01++)
    {
        SCIEVT_BUF[ITempB01] = 0x00;
    }
    // SCIEVT_WIDX = 0;
    // SCIEVT_RIDX = 0;
}
#endif

/*-----------------------------------------------------------------------------
 * @subroutine - AcpiReadData_I2C_AB
 * @function - AcpiReadData_I2C_AB
 * @upstream - By call
 * @input    - None
 * @return   - Send Byte to Host
 * @note     - None
 */
BYTE AcpiReadData_I2C_AB(uint8_t rbuff[], uint32_t *rlength)
{
    if (xHI2C_AcpiCmdCode == _CMD_DATA_BUFFER_READ) // 0xA1
    {
#if NO_NEED
        ITempB01 = *HID_XPntr;
        HID_XPntr++;
#else
        *rlength = *HID_XPntr;
        rbuff[0] = *rlength;
        memcpy((void *)(rbuff + 1), (const void *)HID_XPntr, *rlength);
#endif
        return *rlength;
    }
    if (xHI2C_AcpiCmdCode == _CMD_ACPI_GET_EVENT) // 0x10
    {
#if NO_NEED
        ITempB01 = 1; /* ByteCount */
        if (PktIdxR > 0)
        {
            ITempB01 = SCIEVT_OUT;
            SCIEVT_OUT = 0;
        }
        return ITempB01;
#else
        *rlength = 1;
        rbuff[0] = *rlength;
        rbuff[1] = SCIEVT_OVT;
#endif
    }
    ITempB06 = xHI2C_AcpiCmdCode & 0xF0;
    if (ITempB06 == _CMD_THERMAL_CMD_GROUP) // 0x2X
    {
#if NO_NEED
        FAN_XPntr_wLen = 0;
        ITempB01 = *FAN_XPntr;
        FAN_XPntr++;
        if ((xFanLUTsGetSetError > 0) && (PktIdxR > 0))
        {
            ITempB01 = 0;
        }
        return ITempB01;
#else
        if (FAN_XPntr[0] == 1)
        {
            *rlength = 1;
            rbuff[0] = FAN_XPntr[1];
        }
        else if (FAN_XPntr[0] > 1)
        {
            *rlength = FAN_XPntr[0] + 1;            // length byte + data bytes
            memcpy((void *)(rbuff), (const void *)(FAN_XPntr), *rlength);
        }
        return *rlength;
        

#endif
    }
    if (ITempB06 == _CMD_THERMAL_CMD_GROUP2) // 0x3X
    {
#if NO_NEED
        FAN_XPntr_wLen = 0;
        ITempB01 = *FAN_XPntr;
        FAN_XPntr++;
        return ITempB01;
#else
        FAN_XPntr_wLen = 0;
        *rlength = FAN_XPntr[0];
        memcpy((void *)(rbuff + 1), (const void *)FAN_XPntr, *rlength);
        return *rlength;
#endif
    }
    if (xHI2C_AcpiCmdCode == _ACPI_CMD_EVENT) // 0x05
    {
#if NO_NEED
        ITempB01 = SCIEVT_OUT; /* Without byte count. */
        SCIEVT_OUT = 0;
        return ITempB01;
#else
        *rlength = 1;
        rbuff[0] = *rlength;
        rbuff[1] = SCIEVT_OUT;
        SCIEVT_OUT = 0;
        return *rlength;
#endif
    }
    if (xHI2C_AcpiCmdCode == _ACPI_CMD_CHIP_ID) // 0x06
    {
        /*
        < QCOM_CHIPID_1>_ITE_8987=0x1  //7cGen3
        < QCOM_CHIPID_2>_ITE_8987=0x2  //8cGenX
        < QCOM_CHIPID_2>_ITE_5671=0x3
        */
        return 0x02;
    }
    if (xHI2C_AcpiCmdCode == _CMD_ACPI_GET_EC_STATE) // 0xEC
    {
#if NO_NEED
        xACPI_EC_STATE[0] = 2;
        if (SPIWriteStatus == 0x3C)
        {
            xACPI_EC_STATE[1] = 0x1C;
        }
        else
        {
            xACPI_EC_STATE[1] = 0x0C;
        }
        xACPI_EC_STATE[2] = xFSH_Position;
        return xACPI_EC_STATE[PktIdxR];
#else
        *rlength = 2;
        rbuff[0] = *rlength;
        rbuff[1] = (SPIWriteStatus == 0x3C) ? 0x1C : 0x0C;
        rbuff[2] = xFSH_Position;
        return *rlength;
#endif
    }
    if (xHI2C_AcpiCmdCode == _CMD_ACPI_GET_EC_VER) // 0x0E
    {
        *rlength = 4;
        rbuff[0] = *rlength;
        memcpy(rbuff, (const void *)xHI2C_EC_VER, *rlength);
        return *rlength;
    }
    if (xHI2C_AcpiCmdCode == _CMD_ACPI_GET_FULL_VER) // 0x0F
    {
        *rlength = 4;
        rbuff[0] = *rlength;
        memcpy(rbuff, (const void *)xHI2C_EC_FULL_VER, *rlength);
        return *rlength;
    }
    if (xHI2C_AcpiCmdCode == _ACPI_CMD_ECVER) // 0x0D
    {
        *rlength = 3;
        rbuff[0] = *rlength;
        memcpy(rbuff + 1, (const void *)(xHI2C_EC_VER + 1), *rlength);
        return *rlength;
    }
    if (xHI2C_AcpiCmdCode == _CMD_ACPI_DATA_BLOCK_READ) // 0xA2
    {
#if NO_NEED
        if (PktIdxR == 0)
        {
            HID_XPntr = &FLASH_BUF[0];
            return xFSH_A2_BYTECNT;
        }
        else
        {
            ITempB01 = *HID_XPntr;
            HID_XPntr++;
            return ITempB01;
        }
#else
        *rlength = xFSH_A2_BYTECNT;
        rbuff[0] = *rlength;
        memcpy((void *)(rbuff + 1), (const void *)HID_XPntr, *rlength);
        return *rlength;
#endif
    }
    return 0x00;
}

typedef void (*pAcpiCmdFunction)(uint8_t wbuff[], uint32_t wlength);

void AcpiWriteA0(uint8_t wbuff[], uint32_t wlength);
void AcpiWriteA1(uint8_t wbuff[], uint32_t wlength);
void AcpiWriteA2(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite20(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite21(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite22(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite23(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite24(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite25(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite26(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite27(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite28(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite29(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite30(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite32(uint8_t wbuff[], uint32_t wlength);
void AcpiWrite34(uint8_t wbuff[], uint32_t wlength);
void AcpiWriteEB(uint8_t wbuff[], uint32_t wlength);

struct OEM_ACPI_W
{
    uint8_t cmd;
    pAcpiCmdFunction func;
};
struct OEM_ACPI_W acpi_cmd_function[] = {
    // A0, A1, A2, 0x24, 0x34, 0xEB , 0x20 ~ 0x28, 0x34
    {_CMD_DATA_BUFFER_WRITE,        AcpiWriteA0},
    {_CMD_DATA_BUFFER_READ,         AcpiWriteA1},
    {_CMD_ACPI_DATA_BLOCK_READ,     AcpiWriteA2},
    {_CMD_SOC_TJ_FROM_HLOS,         AcpiWrite20},
    {_CMD_GET_FAN_STATUS,           AcpiWrite21},
    {_CMD_GET_FAN_SPEED_RPM,        AcpiWrite22},
    {_CMD_MODERN_STANDBY_NOTIFY,    AcpiWrite23},
    {_CMD_FAN_PROFILE_SWITCH,       AcpiWrite24},
    {_CMD_FAN_TRIP_POINT,           AcpiWrite25},
    {_CMD_NUM_PROFILE,              AcpiWrite26},
    {_CMD_NUM_LUTS,                 AcpiWrite27},
    {_CMD_GET_SET_LUT_TABLE,        AcpiWrite28},
    {0x29,                          AcpiWrite29},
    {0x2A,                          AcpiWrite29},
    {0x2B,                          AcpiWrite29},
    {0x2C,                          AcpiWrite29},
    {0x2D,                          AcpiWrite29},
    {0x2E,                          AcpiWrite29},
    {0x2F,                          AcpiWrite29},
    {_CMD_QC_TOOLS_TEST_CMD,        AcpiWrite30},
    {_CMD_SET_NTC_THRESHOLD,        AcpiWrite32},
    {_CMD_SET_NTC_SAMPLE_RATE,      AcpiWrite34},
    {_CMD_GET_CHECKSUM_STATUS,      AcpiWriteEB},
};

void AcpiWriteA0(uint8_t wbuff[], uint32_t wlength)
{
    HID_XPntr = (volatile XWORD *)&FLASH_BUF[0];
    xHI2C_DataReadyA0 = 0xA0;
}

void AcpiWriteA1(uint8_t wbuff[], uint32_t wlength)
{
    HID_XPntr = (volatile XWORD *)&FLASH_BUF[0];
}

void AcpiWriteA2(uint8_t wbuff[], uint32_t wlength)
{
    HID_XPntr = (volatile XWORD *)&FLASH_BUF[0];
}

void AcpiWrite20(uint8_t wbuff[], uint32_t wlength)
{
    xHI2C_AcpiCmdCode2 = wbuff[1];

    xHLOS_TMPR[0] = wbuff[2];       // length
    xHLOS_TMPR[1] = wbuff[3];
    xHLOS_TMPR[2] = wbuff[4];

    FAN_XPntr = &xHLOS_TMPR[0];

    DebugHLOSTx = (xHI2C_AcpiCmdCode2 - 1) & 0x07;
    FAN_XPntr += (DebugHLOSTx * 3);
    FAN_XPntr_wLen = 3;
    SCIEVT_ENABLED = 1;
    SET_MASK(xDBG_UartDisp, BIT2);
}

void AcpiWrite21(uint8_t wbuff[], uint32_t wlength)
{
    // Byte 1: Bit7..2 Reserved, Bit1:Fan Failed, Bit0: 1-Fan on, 0-Fan Off
    // Notes: Without byte count
    xHI2C_AcpiCmdCode2 = wbuff[1];
    if (xHI2C_AcpiCmdCode2 == 0x01) // Fan#1
    {
        xFAN1_STATUS[0] = 1;        // length
        xFAN1_STATUS[1] = 0x20;

        FAN_XPntr = &xFAN1_STATUS[0];
        SET_MASK(xDBG_UartDisp, BIT4);
    }
    else if (xHI2C_AcpiCmdCode2 == 0x02) // Fan#2
    {
        xFAN2_STATUS[0] = 1;        // length
        xFAN2_STATUS[1] = 0x20;

        FAN_XPntr = &xFAN2_STATUS[0];
        SET_MASK(xDBG_UartDisp, BIT5);
    }
}

void AcpiWrite22(uint8_t wbuff[], uint32_t wlength)
{
    xHI2C_AcpiCmdCode2 = wbuff[1];
    if (xHI2C_AcpiCmdCode2 == 0x01) // Fan#1
    {
        xFAN1_PACKET[0] = 2;
        xFAN1_PACKET[1] = 0xE8;
        xFAN1_PACKET[2] = 0x03;

        FAN_XPntr = &xFAN1_PACKET[0];
        SET_MASK(xDBG_UartDisp, BIT6);
    }
    else if (xHI2C_AcpiCmdCode2 == 0x02) // Fan#2
    {
        xFAN2_PACKET[0] = 2;
        xFAN2_PACKET[1] = 0xD0;
        xFAN2_PACKET[2] = 0x07;

        FAN_XPntr = &xFAN2_PACKET[0];
        SET_MASK(xDBG_UartDisp, BIT7);
    }
}

void AcpiWrite23(uint8_t wbuff[], uint32_t wlength)
{
    xHI2C_AcpiCmdCode2 = wbuff[1];

    xMSTBY_NOTIFY = xHI2C_AcpiCmdCode2;
    SCIEVT_ENABLED = 1;

    SaveNVTimer = _SAVE_NV_TIMER;
}

void AcpiWrite24(uint8_t wbuff[], uint32_t wlength)
{
    FAN_XPntr = &xFAN_ProfileSwitch[0];
    FAN_XPntr_wLen = 0;

    xHI2C_AcpiCmdCode2 = wbuff[1];
    if (((xHI2C_AcpiCmdCode2 & 0x0F) > 0) && ((xHI2C_AcpiCmdCode2 & 0x0F) < 8))
    {
        xFAN_ProfileSwitch[0] = 1; // length
        xFAN_ProfileSwitch[1] = xHI2C_AcpiCmdCode2;

        TFanProfileSwitch = xHI2C_AcpiCmdCode2 & 0x0F;
        xFanProfileNum = TFanProfileSwitch;
        Load_FanProfileToRam(TFanProfileSwitch);
        xFanLUTsNum = 0;
        Get_RamProfileLUT(xFanLUTsNum);
        SaveNVTimer = _SAVE_NV_TIMER;
    }
    WriteSCI_Buffer(_SCIEVT_SWITCH_PROFILE_OK, _SCI_QUEUE);
}

void AcpiWrite25(uint8_t wbuff[], uint32_t wlength)
{
    xHI2C_AcpiCmdCode2 = wbuff[1];

    Fan1_EventDelay = 10; // Delay 500ms
    Fan2_EventDelay = 10; // Delay 500ms

    if (xHI2C_AcpiCmdCode2 == 0x21)
    {
        Fan1_TripAutoMode = 0;
  
        xFAN1_TRIP_H[0] = wbuff[2]; // length
        xFAN1_TRIP_H[1] = wbuff[3];
        xFAN1_TRIP_H[2] = wbuff[4];

        FAN_XPntr = &xFAN1_TRIP_H[0];
    }
    else if (xHI2C_AcpiCmdCode2 == 0x11)
    {
        Fan1_TripAutoMode = 0;

        xFAN1_TRIP_L[0] = wbuff[2]; // length
        xFAN1_TRIP_L[1] = wbuff[3];
        xFAN1_TRIP_L[2] = wbuff[4];

        FAN_XPntr = &xFAN1_TRIP_L[0];
    }
    else if (xHI2C_AcpiCmdCode2 == 0x22)
    {
        Fan2_TripAutoMode = 0;
        
        xFAN2_TRIP_H[0] = wbuff[2]; // length
        xFAN2_TRIP_H[1] = wbuff[3];
        xFAN2_TRIP_H[2] = wbuff[4];

        FAN_XPntr = &xFAN2_TRIP_H[0];
    }
    else if (xHI2C_AcpiCmdCode2 == 0x12)
    {
        Fan2_TripAutoMode = 0;

        xFAN2_TRIP_L[0] = wbuff[2]; // length
        xFAN2_TRIP_L[1] = wbuff[3];
        xFAN2_TRIP_L[2] = wbuff[4];

        FAN_XPntr = &xFAN2_TRIP_L[0];
    }
    else
    {
        FAN_XPntr_wLen = 0;
    }
}

void AcpiWrite26(uint8_t wbuff[], uint32_t wlength)
{
    xHI2C_AcpiCmdCode2 = wbuff[1];
    if (xHI2C_AcpiCmdCode2 == 0x01)
    {
        xFAN1_ProfileNum[0] = 1; 
        xFAN1_ProfileNum[1] = 6;    
        FAN_XPntr = &xFAN1_ProfileNum[0];
    }
    else if (xHI2C_AcpiCmdCode2 == 0x02)
    {
        xFAN2_ProfileNum[0] = 1;   
        xFAN2_ProfileNum[1] = 7;  
        FAN_XPntr = &xFAN2_ProfileNum[0];
    }
}

void AcpiWrite27(uint8_t wbuff[], uint32_t wlength)
{
    xHI2C_AcpiCmdCode2 = wbuff[1];

    ITempB06 = xHI2C_AcpiCmdCode2 & 0x0F;
    ITempB05 = (xHI2C_AcpiCmdCode2 >> 4) & 0x07;
    if (ITempB06 == 0x01)
    {
        xNUM_LUTS[0] = 1;           // length
        xNUM_LUTS[1] = 0xF1;//xFAN1_NumLUTs[ITempB05];
    }
    else if (ITempB06 == 0x02)
    {
        xNUM_LUTS[0] = 1;           // length
        xNUM_LUTS[1] = 0xF2;xFAN2_NumLUTs[ITempB05];
    }
    FAN_XPntr = &xNUM_LUTS[0];
}

void AcpiWrite28(uint8_t wbuff[], uint32_t wlength)
{
    // TODO: using QC machine would get 1 more bytes
    xHI2C_AcpiCmdCode2 = wbuff[1];
    xHI2C_AcpiCmdCode3 = wbuff[2];

    xFanProfileNum = xHI2C_AcpiCmdCode2 >> 4;
    xFanLUTsNum = xHI2C_AcpiCmdCode3 - 1;

    if (/*(xRamProfileNum == xFanProfileNum) &&*/ (xFanLUTsNum < 8) &&
        (xFanProfileNum > 0) && (xFanProfileNum < 8))
    {
        xFanLUTsGetSetError = 0;
        Get_RamProfileLUT(xFanLUTsNum);
        xFANx_LUT[0] = 64;                      // need 64 bytes
        for ( uint8_t i = 1; i < 65 ; i++)
            xFANx_LUT[i] = i;
    }
    else
    {
        xFanLUTsGetSetError = 1;
        // Get_RomProfileLUT(xFanProfileNum, xFanLUTsNum);
    }
    FAN_XPntr = &xFANx_LUT[0];                  // total bytes are 65 bytes
}

void AcpiWrite29(uint8_t wbuff[], uint32_t wlength)
{
    if ((wbuff[0] > 0x28) && (wbuff[0] < 0x30))
    {
        ITempB01 = xHI2C_AcpiCmdCode - 0x29;
        T_Sensors[0] = 1;
        for( uint8_t i = 1; i < 9; i++)
        {
            T_Sensors[i] = 25 + (i - 1);
        }
        FAN_XPntr = &T_Sensors[0];
    }
}

void AcpiWrite30(uint8_t wbuff[], uint32_t wlength)
{
    memcpy((void *)xFAN_QC_TEST, wbuff + 2, 5);

    FAN_XPntr = &xFAN_QC_TEST[0];
}

void AcpiWrite32(uint8_t wbuff[], uint32_t wlength)
{
    ITempB01 = wbuff[1];
    ITempB02 = (ITempB01 - 1) & 0x07;
    xNTC_ActiveEvent |= (1 << ITempB02);
    Tmp_XPntr = &xNTC_PSV[ITempB02];
    for (ITempB01 = 3; ITempB01 < 7; ITempB01++)
    {
        FLASH_BUF[ITempB01 - 2] = *Tmp_XPntr;
        Tmp_XPntr += 8;
    }
    FLASH_BUF[0] = 4;
    FAN_XPntr = &FLASH_BUF[0];
}

void AcpiWrite34(uint8_t wbuff[], uint32_t wlength)
{
    FAN_XPntr = &xNTC_SampleRate[0];

    xNTC_SampleRate[0] = wbuff[1];
    xNTC_SampleRate[1] = wbuff[2];
}

void AcpiWriteEB(uint8_t wbuff[], uint32_t wlength)
{
    xFSH_A2_BYTECNT = 1;
    ITempB02 = 0x80;
    if (BRAM2[_ABOOT_CHKSUM_POS] == _CHKSUM_PASS)
    {
        ITempB02 |= BIT0;
    }
    if (BRAM2[_BBOOT_CHKSUM_POS] == _CHKSUM_PASS)
    {
        ITempB02 |= BIT1;
    }
    if (BRAM2[_AMAIN_CHKSUM_POS] == _CHKSUM_PASS)
    {
        ITempB02 |= BIT2;
    }
    if (BRAM2[_BMAIN_CHKSUM_POS] == _CHKSUM_PASS)
    {
        ITempB02 |= BIT3;
    }
    BRAM2[_ALL_CHKSUM_STATUS] = ITempB02;
    FLASH_BUF[0] = xFSH_A2_BYTECNT;
    FLASH_BUF[1] = ITempB02;
    HID_XPntr = (volatile XWORD *)&FLASH_BUF[0];

    wbuff[0] = _CMD_DATA_BUFFER_READ;
}

void subfunc_xHI2C_AcpiCmdCode3(uint8_t xHI2C_AcpiCmdCode, uint8_t xHI2C_AcpiCmdCode2, uint8_t xHI2C_AcpiCmdCode3)
{
    // xHI2C_AcpiCmdCode3 = PktData;
    if (xHI2C_AcpiCmdCode == _CMD_SET_NTC_SAMPLE_RATE) // 0x34 //W1RW2
    {
        xNTC_SampleRate[0] = xHI2C_AcpiCmdCode2;
        xNTC_SampleRate[1] = xHI2C_AcpiCmdCode3;
    }
    else if (xHI2C_AcpiCmdCode == _CMD_GET_SET_LUT_TABLE) // 0x28-W3RW66
    {
        xFanProfileNum = xHI2C_AcpiCmdCode2 >> 4;
        xFanLUTsNum = xHI2C_AcpiCmdCode3 - 1;
        if ((xRamProfileNum == xFanProfileNum) && (xFanLUTsNum < 8) &&
            (xFanProfileNum > 0) && (xFanProfileNum < 8))
        {
            xFanLUTsGetSetError = 0;
            Get_RamProfileLUT(xFanLUTsNum);
            FAN_XPntr_wLen = 65; // 1(Byte CNT) + 64(1 LUT)
        }
        else
        {
            xFanLUTsGetSetError = 1;
            // Get_RomProfileLUT(xFanProfileNum, xFanLUTsNum);
            FAN_XPntr_wLen = 0; // 0: Can't Write
        }
        FAN_XPntr = &xFANx_LUT[0];
    }
}

void subfunc_xHI2C_AcpiCmdCode2(uint8_t xHI2C_AcpiCmdCode, uint8_t xHI2C_AcpiCmdCode2, uint8_t wcmd[], uint8_t wlength)
{
    ITempB06 = xHI2C_AcpiCmdCode & 0xF0;
    if (!((ITempB06 == _CMD_THERMAL_CMD_GROUP) || (ITempB06 == _CMD_THERMAL_CMD_GROUP2))) // 0x2X or 0x3X
    {
        return;
    }

    FAN_XPntr_wLen = 0;
    switch (xHI2C_AcpiCmdCode)
    {
    case _CMD_SOC_TJ_FROM_HLOS: // 0x20
    {
        FAN_XPntr = &xHLOS_TMPR[0];
        DebugHLOSTx = (xHI2C_AcpiCmdCode2 - 1) & 0x07;
        FAN_XPntr += (DebugHLOSTx * 3);
        FAN_XPntr_wLen = 3;
        SCIEVT_ENABLED = 1;
        SET_MASK(xDBG_UartDisp, BIT2);
    }
    break;

    case _CMD_GET_FAN_STATUS: // 0x21
    {
        // Byte 1: Bit7..2 Reserved, Bit1:Fan Failed, Bit0: 1-Fan on, 0-Fan Off
        // Notes: Without byte count
        if (xHI2C_AcpiCmdCode2 == 0x01) // Fan#1
        {
            FAN_XPntr = &xFAN1_STATUS[0];
            SET_MASK(xDBG_UartDisp, BIT4);
        }
        else if (xHI2C_AcpiCmdCode2 == 0x02) // Fan#2
        {
            FAN_XPntr = &xFAN2_STATUS[0];
            SET_MASK(xDBG_UartDisp, BIT5);
        }
    }
    break;

    case _CMD_GET_FAN_SPEED_RPM: // 0x22
    {
        if (xHI2C_AcpiCmdCode2 == 0x01) // Fan#1
        {
            FAN_XPntr = &xFAN1_PACKET[0];
            SET_MASK(xDBG_UartDisp, BIT6);
        }
        else if (xHI2C_AcpiCmdCode2 == 0x02) // Fan#2
        {
            FAN_XPntr = &xFAN2_PACKET[0];
            SET_MASK(xDBG_UartDisp, BIT7);
        }
    }
    break;

    case _CMD_MODERN_STANDBY_NOTIFY: // 0x23
    {
        xMSTBY_NOTIFY = xHI2C_AcpiCmdCode2;
        SCIEVT_ENABLED = 1;
        SaveNVTimer = _SAVE_NV_TIMER;
    }
    break;

    case _CMD_FAN_PROFILE_SWITCH: // 0x24
    {
        if (((xHI2C_AcpiCmdCode2 & 0x0F) > 0) && ((xHI2C_AcpiCmdCode2 & 0x0F) < 8))
        {
            xFAN_ProfileSwitch[0] = 1; // length
            xFAN_ProfileSwitch[1] = xHI2C_AcpiCmdCode2;
            TFanProfileSwitch = xHI2C_AcpiCmdCode2 & 0x0F;
            xFanProfileNum = TFanProfileSwitch;
            Load_FanProfileToRam(TFanProfileSwitch);
            xFanLUTsNum = 0;
            Get_RamProfileLUT(xFanLUTsNum);
            SaveNVTimer = _SAVE_NV_TIMER;
        }
        WriteSCI_Buffer(_SCIEVT_SWITCH_PROFILE_OK, _SCI_QUEUE);
    }
    break;

    case _CMD_FAN_TRIP_POINT: // 0x25
    {
        Fan1_EventDelay = 10; // Delay 500ms
        Fan2_EventDelay = 10; // Delay 500ms
        FAN_XPntr_wLen = 3;
        if (xHI2C_AcpiCmdCode2 == 0x21)
        {
            Fan1_TripAutoMode = 0;
            // FAN_XPntr = &xFAN1_TRIP_H[0];
            xFAN1_TRIP_H[0] = wcmd[2]; // length
            xFAN1_TRIP_H[1] = wcmd[3];
            xFAN1_TRIP_H[2] = wcmd[4];

            FAN_XPntr = xFAN1_TRIP_H;
        }
        else if (xHI2C_AcpiCmdCode2 == 0x11)
        {
            Fan1_TripAutoMode = 0;
            xFAN1_TRIP_L[0] = wcmd[2]; // length
            xFAN1_TRIP_L[1] = wcmd[3];
            xFAN1_TRIP_L[2] = wcmd[4];
            FAN_XPntr = &xFAN1_TRIP_L[0];
        }
        else if (xHI2C_AcpiCmdCode2 == 0x22)
        {
            Fan2_TripAutoMode = 0;
            xFAN2_TRIP_H[0] = wcmd[2]; // length
            xFAN2_TRIP_H[1] = wcmd[3];
            xFAN2_TRIP_H[2] = wcmd[4];

            FAN_XPntr = &xFAN2_TRIP_H[0];
        }
        else if (xHI2C_AcpiCmdCode2 == 0x12)
        {
            Fan2_TripAutoMode = 0;
            xFAN2_TRIP_L[0] = wcmd[2]; // length
            xFAN2_TRIP_L[1] = wcmd[3];
            xFAN2_TRIP_L[2] = wcmd[4];

            FAN_XPntr = &xFAN2_TRIP_L[0];
        }
        else
        {
            FAN_XPntr_wLen = 0;
        }
    }
    break;

    case _CMD_NUM_PROFILE: // 0x26
    {
        if (xHI2C_AcpiCmdCode2 == 0x01)
        {
            FAN_XPntr = &xFAN1_ProfileNum[0];
        }
        else if (xHI2C_AcpiCmdCode2 == 0x02)
        {
            FAN_XPntr = &xFAN2_ProfileNum[0];
        }
    }
    break;

    case _CMD_NUM_LUTS: // 0x27
    {
        ITempB06 = xHI2C_AcpiCmdCode2 & 0x0F;
        ITempB05 = (xHI2C_AcpiCmdCode2 >> 4) & 0x07;
        if (ITempB06 == 0x01)
        {
            xNUM_LUTS[0] = xFAN1_NumLUTs[ITempB05];
        }
        else if (ITempB06 == 0x02)
        {
            xNUM_LUTS[0] = xFAN2_NumLUTs[ITempB05];
        }
        FAN_XPntr = &xNUM_LUTS[0];
    }
    break;

    case _CMD_QC_TOOLS_TEST_CMD: // 0x30
    {
        FAN_XPntr_wLen = 4;
        FAN_XPntr = &xFAN_QC_TEST[0];
    }
    break;

    case _CMD_SET_NTC_THRESHOLD: // 0x32
    {
        FAN_XPntr_wLen = 5;
        ITempB01 = PMC_InBuf[1];
        ITempB02 = (ITempB01 - 1) & 0x07;
        xNTC_ActiveEvent |= (1 << ITempB02);
        Tmp_XPntr = &xNTC_PSV[ITempB02];
        for (ITempB01 = 3; ITempB01 < 7; ITempB01++)
        {
            FLASH_BUF[ITempB01 - 2] = *Tmp_XPntr;
            Tmp_XPntr += 8;
        }
        FLASH_BUF[0] = 4;
        FAN_XPntr = &FLASH_BUF[0];
    }
    break;

    default:
        break;
    }
}

void subfunc_xHI2C_AcpiCmdCode(uint8_t *acpi_cmd_code1)
{
    FAN_XPntr_wLen = 0;
    switch (*acpi_cmd_code1)
    {
    case _CMD_DATA_BUFFER_WRITE:    // A0
    case _CMD_DATA_BUFFER_READ:     // A1
    case _CMD_ACPI_DATA_BLOCK_READ: // A2
    {
        HID_XPntr = (volatile XWORD *)&FLASH_BUF[0];
        if (*acpi_cmd_code1 == _CMD_DATA_BUFFER_WRITE)
        {
            xHI2C_DataReadyA0 = 0xA0;
        }
    }
    break;
    case _CMD_FAN_PROFILE_SWITCH:   // 0x24 // W1R1
    {
        FAN_XPntr = &xFAN_ProfileSwitch[0];
    }
    break;
    case _CMD_SET_NTC_SAMPLE_RATE:  // 0x34
    {
        FAN_XPntr = &xNTC_SampleRate[0];
    }
    break;
    case _CMD_GET_CHECKSUM_STATUS:  // 0xEB
    {
        xFSH_A2_BYTECNT = 1;
        ITempB02 = 0x80;
        if (BRAM2[_ABOOT_CHKSUM_POS] == _CHKSUM_PASS)
        {
            ITempB02 |= BIT0;
        }
        if (BRAM2[_BBOOT_CHKSUM_POS] == _CHKSUM_PASS)
        {
            ITempB02 |= BIT1;
        }
        if (BRAM2[_AMAIN_CHKSUM_POS] == _CHKSUM_PASS)
        {
            ITempB02 |= BIT2;
        }
        if (BRAM2[_BMAIN_CHKSUM_POS] == _CHKSUM_PASS)
        {
            ITempB02 |= BIT3;
        }
        BRAM2[_ALL_CHKSUM_STATUS] = ITempB02;
        FLASH_BUF[0] = xFSH_A2_BYTECNT;
        FLASH_BUF[1] = ITempB02;
        HID_XPntr = (volatile XWORD *)&FLASH_BUF[0];

        *acpi_cmd_code1 = _CMD_DATA_BUFFER_READ;
    }
    break;
    default:
    {
        if ((xHI2C_AcpiCmdCode > 0x28) && (xHI2C_AcpiCmdCode < 0x30))
        {
            ITempB01 = xHI2C_AcpiCmdCode - 0x29;
            FAN_XPntr = &T_Sensors[ITempB01];
        }
    }
    break;
    }
}

/*-----------------------------------------------------------------------------
 * @subroutine - AcpiWriteData_I2C_AB
 * @function - AcpiWriteData_I2C_AB
 * @upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void AcpiWriteData_I2C_AB(uint8_t wcmd[], uint32_t wlength)
{
    PMC_WrIdx = wlength;
    memcpy((void *)PMC_InBuf, wcmd, wlength);
#if 0
    xHI2C_AcpiCmdCode = wcmd[0];
    xHI2C_AcpiCmdCode2 = wcmd[1];
    xHI2C_AcpiCmdCode3 = wcmd[2];


    subfunc_xHI2C_AcpiCmdCode((uint8_t *)&xHI2C_AcpiCmdCode);

    subfunc_xHI2C_AcpiCmdCode2(xHI2C_AcpiCmdCode, xHI2C_AcpiCmdCode2, wcmd, wlength);

    subfunc_xHI2C_AcpiCmdCode3(xHI2C_AcpiCmdCode, xHI2C_AcpiCmdCode2, xHI2C_AcpiCmdCode3);
#else
    xHI2C_AcpiCmdCode = wcmd[0]; // A0, A1, A2, 0x24, 0x34, 0xEB , 0x20 ~ 0x28, 0x34

    for (uint8_t i = 0; i < (sizeof(acpi_cmd_function) / sizeof(acpi_cmd_function[0])); i++)
    {
        if (acpi_cmd_function[i].cmd == xHI2C_AcpiCmdCode)
        {
            acpi_cmd_function[i].func(wcmd, wlength);
            xHI2C_AcpiCmdCode = wcmd[0];
            return;
        }
    }

#endif
#if NO_NEED
    // in DMA mode, we do not receive byte by byte,
    if (xHI2C_AcpiCmdCode == _CMD_DATA_BUFFER_WRITE) // 0xA0
    {
        *HID_XPntr = PktData;
        HID_XPntr++;
        return;
    }
    if (PktIdxW < 128)
    {
        PMC_InBuf[PktIdxW] = ITempB01;
        if (PktIdxW > 2)
        {
            return;
        }
    }

    if (PktIdxW == 0)
    {
        FAN_XPntr_wLen = 0;
        xHI2C_AcpiCmdCode = PktData;
        //_CMD_DATA_BUFFER_WRITE        0xA0
        //_CMD_DATA_BUFFER_READ         0xA1
        //_CMD_ACPI_DATA_BLOCK_READ     0xA2
        if ((xHI2C_AcpiCmdCode == _CMD_DATA_BUFFER_WRITE) ||
            (xHI2C_AcpiCmdCode == _CMD_DATA_BUFFER_READ) ||
            (xHI2C_AcpiCmdCode == _CMD_ACPI_DATA_BLOCK_READ))
        {
            HID_XPntr = &FLASH_BUF[0];
            if (xHI2C_AcpiCmdCode == _CMD_DATA_BUFFER_WRITE)
            {
                xHI2C_DataReadyA0 = 0xA0;
            }
        }
        else if (xHI2C_AcpiCmdCode == _CMD_FAN_PROFILE_SWITCH) // 0x24 //W1RW1
        {
            FAN_XPntr = &xFAN_ProfileSwitch[0];
        }
        else if (xHI2C_AcpiCmdCode == _CMD_SET_NTC_SAMPLE_RATE) // 0x34 //W1R1
        {
            FAN_XPntr = &xNTC_SampleRate[0];
        }
        else if (xHI2C_AcpiCmdCode == _CMD_GET_CHECKSUM_STATUS)
        {
            // B0:ABBK B1:BBBK B2:AMAIN B3:BBAIN
            xFSH_A2_BYTECNT = 1;
            ITempB02 = 0x80; /* BIT7: FINISHED */
            if (BRAM2[_ABOOT_CHKSUM_POS] == _CHKSUM_PASS)
            {
                ITempB02 |= BIT0;
            }
            if (BRAM2[_BBOOT_CHKSUM_POS] == _CHKSUM_PASS)
            {
                ITempB02 |= BIT1;
            }
            if (BRAM2[_AMAIN_CHKSUM_POS] == _CHKSUM_PASS)
            {
                ITempB02 |= BIT2;
            }
            if (BRAM2[_BMAIN_CHKSUM_POS] == _CHKSUM_PASS)
            {
                ITempB02 |= BIT3;
            }
            BRAM2[_ALL_CHKSUM_STATUS] = ITempB02;
            FLASH_BUF[0] = xFSH_A2_BYTECNT;
            FLASH_BUF[1] = ITempB02;
            HID_XPntr = &FLASH_BUF[0];
            xHI2C_AcpiCmdCode = _CMD_DATA_BUFFER_READ;
        }
        else if ((xHI2C_AcpiCmdCode > 0x28) &&
                 (xHI2C_AcpiCmdCode < 0x30)) // 0x29~0x2F //W1R1
        {
            ITempB01 = xHI2C_AcpiCmdCode - 0x29;
            FAN_XPntr = &T_Sensors[ITempB01];
        }
        return;
    }
    else if (PktIdxW == 1)
    {
        xHI2C_AcpiCmdCode2 = PktData;
        ITempB06 = xHI2C_AcpiCmdCode & 0xF0;
        if ((ITempB06 == _CMD_THERMAL_CMD_GROUP) ||
            (ITempB06 == _CMD_THERMAL_CMD_GROUP2))
        {
            FAN_XPntr_wLen = 0;
            if (xHI2C_AcpiCmdCode == _CMD_SOC_TJ_FROM_HLOS) // 0x20 //W2RW3
            {
                FAN_XPntr = &xHLOS_TMPR[0];
                DebugHLOSTx = (xHI2C_AcpiCmdCode2 - 1) & 0x07;
                FAN_XPntr += (DebugHLOSTx * 3);
                FAN_XPntr_wLen = 3;
                SCIEVT_ENABLED = 1;
                SET_MASK(xDBG_UartDisp, BIT2);
            }
            else if (xHI2C_AcpiCmdCode == _CMD_GET_FAN_STATUS) // 0x21 //W2R1
            {
                // Byte 1: Bit7..2 Reserved, Bit1:Fan Failed, Bit0: 1-Fan on, 0-Fan Off
                // Notes: Without byte count
                if (xHI2C_AcpiCmdCode2 == 0x01) // Fan#1
                {
                    FAN_XPntr = &xFAN1_STATUS[0];
                    SET_MASK(xDBG_UartDisp, BIT4);
                }
                else if (xHI2C_AcpiCmdCode2 == 0x02) // Fan#2
                {
                    FAN_XPntr = &xFAN2_STATUS[0];
                    SET_MASK(xDBG_UartDisp, BIT5);
                }
            }
            else if (xHI2C_AcpiCmdCode == _CMD_GET_FAN_SPEED_RPM) // 0x22 //W2R3
            {
                if (xHI2C_AcpiCmdCode2 == 0x01) // Fan#1
                {
                    FAN_XPntr = &xFAN1_PACKET[0];
                    SET_MASK(xDBG_UartDisp, BIT6);
                }
                else if (xHI2C_AcpiCmdCode2 == 0x02) // Fan#2
                {
                    FAN_XPntr = &xFAN2_PACKET[0];
                    SET_MASK(xDBG_UartDisp, BIT7);
                }
            }
            else if (xHI2C_AcpiCmdCode == _CMD_MODERN_STANDBY_NOTIFY) // 0x23 //W1W1
            {
                xMSTBY_NOTIFY = xHI2C_AcpiCmdCode2;
                SCIEVT_ENABLED = 1;
                SaveNVTimer = _SAVE_NV_TIMER;
            }
            else if (xHI2C_AcpiCmdCode == _CMD_FAN_PROFILE_SWITCH) // 0x24 //W1RW1
            {
                if (((xHI2C_AcpiCmdCode2 & 0x0F) > 0) && ((xHI2C_AcpiCmdCode2 & 0x0F) < 8))
                {
                    xFAN_ProfileSwitch[0] = xHI2C_AcpiCmdCode2;
                    xFAN_ProfileSwitch[1] = xHI2C_AcpiCmdCode2;
                    TFanProfileSwitch = xHI2C_AcpiCmdCode2 & 0x0F;
                    xFanProfileNum = TFanProfileSwitch;
                    Load_FanProfileToRam(TFanProfileSwitch);
                    xFanLUTsNum = 0;
                    Get_RamProfileLUT(xFanLUTsNum);
                    SaveNVTimer = _SAVE_NV_TIMER;
                }
                WriteSCI_Buffer(_SCIEVT_SWITCH_PROFILE_OK, _SCI_QUEUE);
            }
            else if (xHI2C_AcpiCmdCode == _CMD_FAN_TRIP_POINT) // 0x25 //W2RW3
            {
                Fan1_EventDelay = 10; // Delay 500ms
                Fan2_EventDelay = 10; // Delay 500ms
                FAN_XPntr_wLen = 3;
                if (xHI2C_AcpiCmdCode2 == 0x21)
                {
                    Fan1_TripAutoMode = 0;
                    FAN_XPntr = &xFAN1_TRIP_H[0];
                }
                else if (xHI2C_AcpiCmdCode2 == 0x11)
                {
                    Fan1_TripAutoMode = 0;
                    FAN_XPntr = &xFAN1_TRIP_L[0];
                }
                else if (xHI2C_AcpiCmdCode2 == 0x22)
                {
                    Fan2_TripAutoMode = 0;
                    FAN_XPntr = &xFAN2_TRIP_H[0];
                }
                else if (xHI2C_AcpiCmdCode2 == 0x12)
                {
                    Fan2_TripAutoMode = 0;
                    FAN_XPntr = &xFAN2_TRIP_L[0];
                }
                else
                {
                    FAN_XPntr_wLen = 0;
                }
            }
            else if (xHI2C_AcpiCmdCode == _CMD_NUM_PROFILE) // 0x26 //W2R2
            {
                if (xHI2C_AcpiCmdCode2 == 0x01)
                {
                    FAN_XPntr = &xFAN1_ProfileNum[0];
                }
                else if (xHI2C_AcpiCmdCode2 == 0x02)
                {
                    FAN_XPntr = &xFAN2_ProfileNum[0];
                }
            }
            else if (xHI2C_AcpiCmdCode == _CMD_NUM_LUTS) // 0x27 //W2R1
            {
                ITempB06 = xHI2C_AcpiCmdCode2 & 0x0F;
                ITempB05 = (xHI2C_AcpiCmdCode2 >> 4) & 0x07;
                if (ITempB06 == 0x01)
                {
                    xNUM_LUTS[0] = xFAN1_NumLUTs[ITempB05];
                }
                else if (ITempB06 == 0x02)
                {
                    xNUM_LUTS[0] = xFAN2_NumLUTs[ITempB05];
                }
                FAN_XPntr = &xNUM_LUTS[0];
            }
            else if (xHI2C_AcpiCmdCode == _CMD_QC_TOOLS_TEST_CMD) // 0x30 //W2W4
            {
                FAN_XPntr_wLen = 4;
                FAN_XPntr = &xFAN_QC_TEST[0];
            }
            else if (xHI2C_AcpiCmdCode == _CMD_SET_NTC_THRESHOLD) // 0x32  //WC2WD5  PSV<CR3<HOT<CRT
            {
                FAN_XPntr_wLen = 5;
                ITempB01 = PMC_InBuf[1];
                ITempB02 = (ITempB01 - 1) & 0x07;
                xNTC_ActiveEvent |= (1 << ITempB02);
                Tmp_XPntr = &xNTC_PSV[ITempB02];
                for (ITempB01 = 3; ITempB01 < 7; ITempB01++)
                {
                    FLASH_BUF[ITempB01 - 2] = *Tmp_XPntr;
                    Tmp_XPntr += 8;
                }
                FLASH_BUF[0] = 4;
                FAN_XPntr = &FLASH_BUF[0];
            }
        }
    }
    else if (PktIdxW == 2)
    {
        xHI2C_AcpiCmdCode3 = PktData;
        if (xHI2C_AcpiCmdCode == _CMD_SET_NTC_SAMPLE_RATE) // 0x34 //W1RW2
        {
            xNTC_SampleRate[0] = xHI2C_AcpiCmdCode2;
            xNTC_SampleRate[1] = xHI2C_AcpiCmdCode3;
        }
        else if (xHI2C_AcpiCmdCode == _CMD_GET_SET_LUT_TABLE) // 0x28-W3RW66
        {
            xFanProfileNum = xHI2C_AcpiCmdCode2 >> 4;
            xFanLUTsNum = xHI2C_AcpiCmdCode3 - 1;
            if ((xRamProfileNum == xFanProfileNum) && (xFanLUTsNum < 8) &&
                (xFanProfileNum > 0) && (xFanProfileNum < 8))
            {
                xFanLUTsGetSetError = 0;
                Get_RamProfileLUT(xFanLUTsNum);
                FAN_XPntr_wLen = 65; // 1(Byte CNT) + 64(1 LUT)
            }
            else
            {
                xFanLUTsGetSetError = 1;
                // Get_RomProfileLUT(xFanProfileNum, xFanLUTsNum);
                FAN_XPntr_wLen = 0; // 0: Can't Write
            }
            FAN_XPntr = &xFANx_LUT[0];
        }
    }
#endif /* NO_NEED */
}

#if UNUSED

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_SlaveI2C_AB_StopAcpi23X
 * @function - Handle I2C slave channel #AB - protocol 2X stop
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Hook_SlaveI2C_AB_StopAcpi23X(void)
{
    if (FAN_XPntr_wLen == 0)
    {
        return;
    }
    if (xHI2C_AcpiCmdCode == _CMD_SET_NTC_THRESHOLD) // 0x32 WC2WD5  PSV<CR3<HOT<CRT
    {
        ITempB01 = PMC_InBuf[1];
        ITempB02 = (ITempB01 - 1) & 0x07;
        xNTC_LEVEL[ITempB02] = 0;
        Tmp_XPntr = &xNTC_PSV[ITempB02];
        for (ITempB01 = 3; ITempB01 < 7; ITempB01++)
        {
            *Tmp_XPntr = PMC_InBuf[ITempB01];
            Tmp_XPntr += 8;
        }
        xNTC_ActiveEvent |= (1 << ITempB02);
    }
    if (xHI2C_AcpiCmdCode == _CMD_SOC_TJ_FROM_HLOS) // 0x20 //W2RW3
    {
        *FAN_XPntr = PMC_InBuf[2];
        FAN_XPntr++;
        *FAN_XPntr = PMC_InBuf[3];
        FAN_XPntr++;
        *FAN_XPntr = PMC_InBuf[4];

        FAN_XPntr = &xHLOS_TMPR[0];
        ITempB01 = 0;
        do
        {
            FAN_XPntr++;
            ITempB02 = *FAN_XPntr;
            FAN_XPntr++;
            ITempB03 = *FAN_XPntr;
            FAN_XPntr++;
            ITempW01 = (WORD)(ITempB03 * 256) + ITempB02;
            ITempB04 = ITempW01 / 10;
            xHLOS_T[ITempB01] = ITempB04;
            ITempB01++;
        } while (ITempB01 < 8);
    }
    else if (xHI2C_AcpiCmdCode == _CMD_FAN_TRIP_POINT) // 0x25 //W2RW3
    {
        *FAN_XPntr = PMC_InBuf[2];
        FAN_XPntr++;
        *FAN_XPntr = PMC_InBuf[3];
        FAN_XPntr++;
        *FAN_XPntr = PMC_InBuf[4];
    }
    else if (xHI2C_AcpiCmdCode == _CMD_SET_NTC_SAMPLE_RATE) // 0x34 //W1RW2
    {
        // FAN_XPntr_wLen = 3;
        // FAN_XPntr = &xNTC_SampleRate[0];
        *FAN_XPntr = PMC_InBuf[1];
        FAN_XPntr++;
        *FAN_XPntr = PMC_InBuf[2];
        // FAN_XPntr++;
        //*FAN_XPntr = PMC_InBuf[3];
    }
    else if (xHI2C_AcpiCmdCode == _CMD_QC_TOOLS_TEST_CMD) // 0x30 //W2W4
    {
        /*
           Wr Byte1: 0x30
           Wr Byte2 = (Fan) Fan1:0x1, Fan2:0x2
           Wr Byte3: Byte count
           Wr TEST[1]: Debug Mode On:0x1X, Off:0x0X
           Wr TEST[2]: RPM_L
           Wr TEST[3]: RPM_H
           Wr TEST[4]: PWM(0~FF) (Active if TEST[2] == 0)
        */
        xFAN_QC_TEST[0] = 3;
        xFAN_QC_TEST[1] = PMC_InBuf[3];
        xFAN_QC_TEST[2] = PMC_InBuf[4];
        xFAN_QC_TEST[3] = PMC_InBuf[5];
        xFAN_QC_TEST[4] = PMC_InBuf[6];
        xFAN_QC_TEST[5] = PMC_InBuf[7];
        SCIEVT_ENABLED = 1; /* Auto-Enable SCI on QC Test Mode. */
        if (xHI2C_AcpiCmdCode2 == 0x01)
        {
            if ((xFAN_QC_TEST[1] & 0x05) == 0x05)
            {
                Fan1_DebugKey = 0xDC;
                Fan1_DebugCmd = xFAN_QC_TEST[4];
                xFAN1_2S_EVENT = 20;
            }
            else if ((xFAN_QC_TEST[1] & 0x05) == 0x01)
            {
                Fan1_DebugKey = 0xDF;
                Fan1_DebugCmd = xFAN_QC_TEST[2];
                Fan1_DebugCmd2 = xFAN_QC_TEST[3];
            }
            else
            {
                Fan1_DebugKey = 0;
            }
        }
        else if (xHI2C_AcpiCmdCode2 == 0x02)
        {
            if ((xFAN_QC_TEST[1] & 0x05) == 0x05)
            {
                Fan2_DebugKey = 0xDC;
                Fan2_DebugCmd = xFAN_QC_TEST[4];
                xFAN2_2S_EVENT = 20;
            }
            else if ((xFAN_QC_TEST[1] & 0x05) == 0x01)
            {
                Fan2_DebugKey = 0xDF;
                Fan2_DebugCmd = xFAN_QC_TEST[2];
                Fan2_DebugCmd2 = xFAN_QC_TEST[3];
            }
            else
            {
                Fan2_DebugKey = 0;
            }
        }
        else
        {
            /* 2 sec event after exit QC Test Mode. */
            xFAN1_2S_EVENT = 20;
            xFAN2_2S_EVENT = 20;
        }
    }
    else if (xHI2C_AcpiCmdCode == _CMD_GET_SET_LUT_TABLE) // 0x28-W3RW66
    {
        Tmp_XPntr = &RamBuffer1[0];
        Tmp_XPntr += (xFanLUTsNum & 0x07) * 64;
        for (ITempB01 = 4; ITempB01 < (64 + 4); ITempB01++)
        {
            *Tmp_XPntr = PMC_InBuf[ITempB01];
            Tmp_XPntr++;
        }
        WriteSCI_Buffer(_SCIEVT_SETTING_LUT_OK, _SCI_QUEUE);
    }
    FAN_XPntr_wLen = 0;
}

/*-----------------------------------------------------------------------------
 * @subroutine - Service_BB_Command
 * @function - Service_BB_Command
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Service_BB_Command(void)
{
    if (HID_BB_Command == 0)
    {
        return;
    }
    ITempB06 = HID_BB_Command;
    HID_BB_Command = 0;
    if (ITempB06 == _CMD_ITE_MCU_RESET) // 0xCC
    {
#if ITE_CHIP_IT557X
        ETWCFG = EWDKEYEN; /* Force Watchdog active */
        EWDCNTLLR = 0x01;  // for 1ms counter
        EWDKEYR = 0x5A;    // External WDTreset not match
#else
        WDTRST = 1; // Reset watch dog timer
        WDTEB = 1;  // Enable watch dog
#endif
    }
    /* Check & Jump BootBlock Flash Service */
    if (ITempB06 == _CMD_ENTER_FLASH_IDLE) // 0xDC
    {
#pragma asm
        JMP 01000H
#pragma endasm
    }
    else if (ITempB06 == _CMD_COPY_A_MBK_TO_BAKUP) // 0x15
    {
#pragma asm
        MOV R2, #_COPYAMAIN_BMAIN JMP 0500H;
        ;
        CopyFirmware();
#pragma endasm
    }
    else if (ITempB06 == _CMD_COPY_BAKUP_TO_A_MBK) // 0x16
    {
#pragma asm
        MOV R2, #_COPYBMAIN_AMAIN JMP 0500H;
        ;
        CopyFirmware();
#pragma endasm
    }
    else if (ITempB06 == _CMD_COPY_A_BBK_TO_BAKUP) // 0x17
    {
#pragma asm
        MOV R2, #_COPYABBK_BBBK JMP 0500H;
        ;
        CopyFirmware();
#pragma endasm
    }
    else if (ITempB06 == _CMD_COPY_BAKUP_TO_A_BBK) // 0x18
    {
#pragma asm
        MOV R2, #_COPYBBBK_ABBK JMP 0500H;
        ;
        CopyFirmware();
#pragma endasm
    }
    else if ((ITempB06 == _CMD_RUN_MAIN_CHECKSUM) ||   // 0xED
             (ITempB06 == _CMD_RUN_MAIN_ALL_CHECKSUM)) // 0xF0
    {
        xFSH_A2_BYTECNT = 1;
        ITempB02 = _CHKSUM_ACT_MAIN;
#pragma asm
        CALL 0300H;
        ;
        BBK_GetFlashCheckSum();
#pragma endasm
        FLASH_BUF[0] = BRAM2[_AMAIN_CHKSUM_POS];
    }
    else if ((ITempB06 == _CMD_RUN_BACKUP_ALL_CHECKSUM) || // 0xF1
             (ITempB06 == _CMD_RUN_BACKUP_BBK_CHECKSUM) || // 0xF4
             (ITempB06 == _CMD_RUN_BACKUP_MAIN_CHECKSUM))  // 0xF5
    {
        xFSH_A2_BYTECNT = 1;
        ITempB02 = _CHKSUM_BAK_BBK;
#pragma asm
        CALL 0300H;
        ;
        BBK_GetFlashCheckSum();
#pragma endasm
        ITempB02 = _CHKSUM_BAK_MAIN;
#pragma asm
        CALL 0300H;
        ;
        BBK_GetFlashCheckSum();
#pragma endasm
        if (ITempB06 == _CMD_RUN_BACKUP_ALL_CHECKSUM) // 0xF1
        {
            if (BRAM2[_BBOOT_CHKSUM_POS] == _CHKSUM_PASS)
            {
                FLASH_BUF[0] = BRAM2[_BMAIN_CHKSUM_POS];
            }
            else
            {
                FLASH_BUF[0] = BRAM2[_BBOOT_CHKSUM_POS];
            }
        }
        else if (HID_BB_Command == _CMD_RUN_BACKUP_BBK_CHECKSUM) // 0xF4
        {
            FLASH_BUF[0] = BRAM2[_BBOOT_CHKSUM_POS];
        }
        else if (HID_BB_Command == _CMD_RUN_BACKUP_MAIN_CHECKSUM) // 0xF5
        {
            FLASH_BUF[0] = BRAM2[_BMAIN_CHKSUM_POS];
        }
    }
    // else if (ITempB06 == _CMD_ENTER_PRE_DEFINE)     //0xB4
    //{
    //     /* Notes: WoS8cGx IT8987 default predefine always */
    //     Enter_ITE_Predefine();
    // }
}

/*-----------------------------------------------------------------------------
 * @subroutine - Hook_SlaveI2C_AB_Stop
 * @function - Handle I2C slave channel #A - protocol stop
 * @Upstream - By call
 * @input    - None
 * @return   - None
 * @note     - None
 */
void Hook_SlaveI2C_AB_Stop(void)
{
    if (xHI2C_AcpiCmdCode == 0)
    {
        /* Check HID BB command In. */
        Service_BB_Command();
        return;
    }
    xFanLUTsGetSetError = 0; // Clear Fan error flag
    Main_UartDebug(0, xHI2C_AcpiCmdCode, xHI2C_AcpiCmdCode2);
    ITempB06 = xHI2C_AcpiCmdCode & 0xF0;
    if ((ITempB06 == _CMD_THERMAL_CMD_GROUP) ||
        (ITempB06 == _CMD_THERMAL_CMD_GROUP2))
    {
        //_CMD_THERMAL_CMD_GROUP 0x2X, _CMD_THERMAL_CMD_GROUP2 0x3X,
        Hook_SlaveI2C_AB_StopAcpi23X();
        xHI2C_AcpiCmdCode = 0;
        return;
    }
    if (xHI2C_AcpiCmdCode == _CMD_UART_LOG_TIME_STAMP) // 0x40
    {
        if (PMC_InBuf[1] == 0)
        {
            F_TimeStamp_HID = 0;
            F_TimeStamp_FAN = 0;
        }
        else if (PMC_InBuf[1] == 1)
        {
            F_TimeStamp_FAN = 1;
        }
        else if (PMC_InBuf[1] == 2)
        {
            F_TimeStamp_HID = 1;
        }
        return;
    }
    if (xHI2C_AcpiCmdCode == _CMD_SEND_SET_TIME_STAMP) // 0x41
    {
        TIMETICKB7 = PMC_InBuf[3];
        TIMETICKB6 = PMC_InBuf[4];
        TIMETICKB5 = PMC_InBuf[5];
        TIMETICKB4 = PMC_InBuf[6];
        TIMETICKB3 = PMC_InBuf[7];
        TIMETICKB2 = PMC_InBuf[8];
        TIMETICKB1 = PMC_InBuf[9];
        TIMETICKB0 = PMC_InBuf[10];
        return;
    }
    if ((xHI2C_AcpiCmdCode == _CMD_RUN_MAIN_CHECKSUM) ||   // 0xED
        (xHI2C_AcpiCmdCode == _CMD_RUN_MAIN_ALL_CHECKSUM)) // 0xF0
    {
        xFSH_A2_BYTECNT = 1;
        ITempB02 = _CHKSUM_ACT_MAIN;
#pragma asm
        CALL 0300H;
        ;
        BBK_GetFlashCheckSum();
#pragma endasm
        FLASH_BUF[0] = BRAM2[_AMAIN_CHKSUM_POS];
    }
    else if (xHI2C_AcpiCmdCode == _CMD_RUN_BACKUP_ALL_CHECKSUM) // 0xF1
    {
        xFSH_A2_BYTECNT = 1;
        ITempB02 = _CHKSUM_BAK_BBK;
#pragma asm
        CALL 0300H;
        ;
        BBK_GetFlashCheckSum();
#pragma endasm
        ITempB02 = _CHKSUM_BAK_MAIN;
#pragma asm
        CALL 0300H;
        ;
        BBK_GetFlashCheckSum();
#pragma endasm
        if (BRAM2[_BBOOT_CHKSUM_POS] == _CHKSUM_PASS)
        {
            FLASH_BUF[0] = BRAM2[_BMAIN_CHKSUM_POS];
        }
        else
        {
            FLASH_BUF[0] = BRAM2[_BBOOT_CHKSUM_POS];
        }
    }
    else if (xHI2C_AcpiCmdCode == _CMD_ACPI_HID_SPI_COMMAND) // 0xBB
    {
        HID_BB_Command = PMC_InBuf[2];
    }
    else if (xHI2C_AcpiCmdCode == _CMD_ACPI_QUICK_PROCESS) // 0xAF
    {
        HID_BB_Command = PMC_InBuf[2];
    }
    Service_BB_Command();
    xHI2C_AcpiCmdCode = 0;
}
//-----------------------------------------------------------------------------

#endif /* UNUSED */

/*-----------------------------------------------------------------------------
 * End of OEM_ACPI.C */