/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

//*****************************************************************************
// CHECSUM (Use ITE Tools - FU.exe /WCS function)
//*****************************************************************************
//-----------------------------------------------------------------------------
const unsigned char OEM_CHKSUM[] =
{
    0x00, 0x00, 0x00, 0x00,
    'C', 'H', 'E', 'C', 'K', 'S', 'U', 'M', '3', '2', 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Project Information
//-----------------------------------------------------------------------------
const unsigned char SIGN_FV[] = {_BUILD_FV};
const unsigned char SIGN_LSFV[] =  {_BUILD_LSFV};
const unsigned char SIGN_MUFG[] = {_BUILD_MUFG};
const unsigned char SIGN_MODL[] = {_BUILD_MODEL};
const unsigned char SIGN_GUST[] = {_BUILD_GUEST};
const unsigned char SIGN_PCBV[] = {_BUILD_BOARD};
const unsigned char SIGN_TAG1[] = "BUILD DATE:";
const unsigned char SIGN_DATE[] = {_BUILD_DATE};
const unsigned char SIGN_TAG2[] = "TIME:";
const unsigned char SIGN_TIME[] = {_BUILD_TIME};
const unsigned char SIGN_MAFW[] =
{'M', 'A', 'I', 'N', '_', 'F', 'W', '_', 'A', 'D', 'D', 'R', ':', 0x00, 0x20};
//-----------------------------------------------------------------------------
void Reload_EC_Ver(void)
{
    xEC_MainVersion = _EC_MAIN_VERSION;
    xEC_SubVersion = _EC_SUB_VERSION;
    xEC_TestVersion = _EC_TEST_VERSION;
    xEC_BetaVersion = _EC_BETA_VERSION;

    xHI2C_EC_VER[0] = 3;    /* Byte Count */
    xHI2C_EC_VER[1] = _EC_TEST_VERSION;
    xHI2C_EC_VER[2] = _EC_SUB_VERSION;
    xHI2C_EC_VER[3] = _EC_MAIN_VERSION;

    xHI2C_BBK_VER[0] = 3;
    xHI2C_BBK_VER[1] = _BBK_TEST_VERSION;
    xHI2C_BBK_VER[2] = _BBK_SUB_VERSION;
    xHI2C_BBK_VER[3] = _BBK_MAIN_VERSION;

    xHI2C_EC_FULL_VER[0] = 7;    /* Byte Count */

    xHI2C_EC_FULL_VER[1] = _EC_TEST_VERSION;
    xHI2C_EC_FULL_VER[2] = _EC_SUB_VERSION;
    xHI2C_EC_FULL_VER[3] = _EC_MAIN_VERSION;

    xHI2C_EC_FULL_VER[4] = _LSFV_TEST_VERSION;
    xHI2C_EC_FULL_VER[5] = _LSFV_SUB_VERSION;
    xHI2C_EC_FULL_VER[6] = _LSFV_MAIN_VERSION;

    //ITempB01 = eFlash_Read_1Byte(0x00, 0x00, 0x6F);
    //xHI2C_EC_FULL_VER[7] = ITempB01;
}