/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

LOG_MODULE_REGISTER(thermalmgm, LOG_LEVEL_INF);

void ThreadThermalMgm(void *p1, void *p2, void *p3)
{
    while(1)
    {
        LOG_INF("ThreadThermalMgm loop sleep");
        k_msleep(1000);
    }
}