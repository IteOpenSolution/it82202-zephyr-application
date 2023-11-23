/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_I2C_DEV_TEST_H_
#define _ITE_I2C_DEV_TEST_H_

#include "../include/include.h"

#if ITE_I2C_DEV_TEST_EN

#define DEBUG_I2C0_DEV_EN   0
#define DEBUG_I2C1_DEV_EN   0
#define DEBUG_I2C2_DEV_EN   0
#define DEBUG_I2C3_DEV_EN   0
#define DEBUG_I2C4_DEV_EN   0
#define DEBUG_I2C5_DEV_EN   1

#define DEBUG_TARGET_SEL    2

#define BOARD_I2C5_VOLTAGE_LEVEL "1v8"

#define MASK_I2C_DEV_TEST           (ITE_I2C_DEV_TEST_COMM | \
                                    ITE_I2C_DEV_TEST_HID_PROT | \
                                    ITE_I2C_DEV_TEST_ACPI)
#define ITE_I2C_DEV_TEST_COMM      0x01
#define ITE_I2C_DEV_TEST_HID_PROT  0x02
#define ITE_I2C_DEV_TEST_ACPI      0x04


void test_ite_i2c(uint32_t opt);

#endif // ITE_I2C_DEV_TEST_EN

#endif // _ITE_I2C_DEV_TEST_H_