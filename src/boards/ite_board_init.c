/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

LOG_MODULE_REGISTER(ite_board_init, 4);

void board_init(void)
{
    printk("Board init");

    ite_gpio_init();
    
    ite_i2c_target_init();
}