/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_TASK_HANDLER_H__
#define _ITE_TASK_HANDLER_H__

#include <zephyr/kernel.h>
int main(void);
void ThreadDummy1(void *p1, void *p2, void *p3);
void ThreadDummy2(void *p1, void *p2, void *p3);
void start_all_tasks(void);

#endif // _ITE_TASK_HANDLER_H__