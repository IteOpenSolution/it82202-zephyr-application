/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _I2C_ITE_TARGET_H_
#define _I2C_ITE_TARGET_H_

struct i2c_addr {
    uint32_t addr;
    uint32_t base;
};

extern struct i2c_addr AllI2cAddr[3];

struct I2cAddressInfo {
    uint8_t main_address;   // bit15 ~ bit8 : I2Cx main address
    uint8_t id;             // bit2 ~ bit0  : IDx, x = 1 ~ 4
};

int ite_i2c_target_init(void);
int ite_i2c_target_deinit(void);

#endif /* _I2C_ITE_TARGET_H_ */