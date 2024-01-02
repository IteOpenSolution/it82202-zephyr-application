/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

LOG_MODULE_REGISTER(cmdparser, LOG_LEVEL_INF);

void ThreadACPI(void *p1, void *p2, void *p3)
{
    while(1)
    {
        LOG_INF("ThreadACPI loop sleep");
        k_sleep(K_MSEC(1000));
    }
}