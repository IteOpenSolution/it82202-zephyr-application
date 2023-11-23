/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

LOG_MODULE_REGISTER(ite_task_handler, 4);

/* size of stack area used by each thread */
#define EC_TASK_STACK_SIZE 1024

/* scheduling priority used by each thread */
#define EC_TASK_PRIORITY K_PRIO_COOP(7)

/* K_FOREVER can no longer be used with K_THREAD_DEFINE
 * Zephyr community is using user-defined macros instead to achieve
 * the same behavior than with K_FOREVER.
 * For EC define macro until the new flag K_THREAD_NO_START is available.
 */
#define EC_WAIT_FOREVER (-1)

void ThreadDummy1(void *p1, void *p2, void *p3)
{
    while(1)
    {
        DPRINTK(1, "ThreadDummy1 loop sleep");
        k_sleep(K_MSEC(1000));
    }
}

void ThreadDummy2(void *p1, void *p2, void *p3)
{

    while(1)
    {
        DPRINTK(1, "ThreadDummy2 loop sleep");
        k_sleep(K_MSEC(1000));
    }
}
