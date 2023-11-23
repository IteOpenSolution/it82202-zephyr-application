/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

#if ITE_TEST_FUNCTIONS_EN

void test_ite_fucntions(uint32_t opt)
{
    test_ite_i2c(opt);
}

#endif // ITE_TEST_FUNCTIONS_EN