/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_TASK_DEFINE_H__
#define _ITE_TASK_DEFINE_H__

#include <zephyr/kernel.h>

#define MAX_MSG_LEN 256

#define MAX_MESSAGE_COUNT 10

extern struct k_sem i2c_semaphore;

extern uint8_t hid_i2c_wbuff[];
extern uint8_t hid_i2c_rbuff[];
extern uint32_t hid_i2c_wlength;
extern uint32_t hid_i2c_rlength;

extern uint8_t acpi_i2c_wbuff[];
extern uint8_t acpi_i2c_rbuff[];
extern uint32_t acpi_i2c_wlength;
extern uint32_t acpi_i2c_rlength;



#endif // _ITE_TASK_DEFINE_H__