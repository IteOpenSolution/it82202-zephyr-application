/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

// K_MSGQ_DEFINE(i2c_msgq, MAX_MSG_LEN, MAX_MESSAGE_COUNT, 4);

K_SEM_DEFINE(i2c_semaphore, 0, 1);  // 初始计数为0，最大计数为1


uint8_t hid_i2c_wbuff[255] = {0};
uint8_t hid_i2c_rbuff[255] = {0};
uint32_t hid_i2c_wlength = 0;
uint32_t hid_i2c_rlength = 0;

uint8_t acpi_i2c_wbuff[255] = {0};
uint8_t acpi_i2c_rbuff[255] = {0};
uint32_t acpi_i2c_wlength = 0;
uint32_t acpi_i2c_rlength = 0;

