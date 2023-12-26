/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_TEST_FUNCTIONS_H_
#define _ITE_TEST_FUNCTIONS_H_

#include "../include/include.h"

#define ITE_DPRINTK_EN 1
#if ITE_DPRINTK_EN

#define DEBUG_MSG_LEVEL_1_EN   true
#define DEBUG_MSG_LEVEL_2_EN   false

#define DEBUG_MSG_LEVEL_1   1
#define DEBUG_MSG_LEVEL_2   2


#define DPRINTK(opt, ...) \
    do { \
        if (opt==DEBUG_MSG_LEVEL_1 && DEBUG_MSG_LEVEL_1_EN ) { \
            printk(__VA_ARGS__); \
            printk("\n"); \
        } \
        if (opt==DEBUG_MSG_LEVEL_2 && DEBUG_MSG_LEVEL_2_EN) { \
            printk(__VA_ARGS__); \
            printk("\n"); \
        } \
    } while(0)

#define DPRINTK_DUMP_BUFF(opt, buff, length) \
    do { \
        if (opt==DEBUG_MSG_LEVEL_1 && DEBUG_MSG_LEVEL_1_EN ) { \
            for (int i = 0; i < (length); i++) { \
                printk("%02x ", (buff)[i]); \
                if (i % 8 == 7) \
                    printk("\n"); \
            } \
            printk("\n"); \
        } \
        if (opt==DEBUG_MSG_LEVEL_2 && DEBUG_MSG_LEVEL_2_EN) { \
            for (int i = 0; i < (length); i++) { \
                printk("%02x ", (buff)[i]); \
                if (i % 8 == 7) \
                    printk("\n"); \
            } \
            printk("\n"); \
        } \
    } while(0)
#else
#define DPRINTK(opt, ...)
#define DPRINTK_DUMP_BUFF(opt, buff, length)
#endif
#if ITE_TEST_FUNCTIONS_EN

#include <zephyr/kernel.h>

void test_ite_fucntions(uint32_t opt);

#endif

#endif //_ITE_TEST_FUNCTIONS_H_