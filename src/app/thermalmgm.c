/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

void ThreadThermalMgm(void *p1, void *p2, void *p3)
{
    while(1)
    {
        printk("ThreadThermalMgm loop sleep");
        k_msleep(1000);
    }
}