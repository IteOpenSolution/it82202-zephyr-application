/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

LOG_MODULE_REGISTER(app, 4);

K_THREAD_STACK_DEFINE(thread_stack_acpi, 512);
struct k_thread thread_acpi;

K_THREAD_STACK_DEFINE(thread_stack_thermalmgm, 512);
struct k_thread thread_thermalmgm;

int main(void)
{
    DPRINTK(1, "Hello IT82202, %s", EC_VER);

    board_init();

    Reload_EC_Ver();

    k_thread_create(&thread_acpi, thread_stack_acpi, K_THREAD_STACK_SIZEOF(thread_stack_acpi),
                    ThreadACPI, NULL, NULL, NULL,
                    0, K_USER, K_NO_WAIT);

    k_thread_create(&thread_thermalmgm, thread_stack_thermalmgm, K_THREAD_STACK_SIZEOF(thread_stack_thermalmgm),
                    ThreadThermalMgm, NULL, NULL, NULL,
                    0, K_USER, K_NO_WAIT);
    while(1)
    {
        DPRINTK(1, "main");
        k_msleep(1000);
    }
    
    return 0;
}
