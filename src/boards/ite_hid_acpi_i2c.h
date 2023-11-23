/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ITE_HID_ACPI_I2C_H_
#define _ITE_HID_ACPI_I2C_H_

typedef enum {
    HidOverI2c = 0,
    AcpiOverI2c,
} ProtocolType;

typedef enum  {
    Write = 0, 
    Read = 1,
} I2CCmdType;

void HidOverI2cReadCmdParser(uint8_t **rbuff, uint32_t *rlength);
void HidOverI2cWriteCmdParser(uint8_t wbuff[], uint32_t wlength);

void AcpiOverI2cReadCmdParser(uint8_t **rbuff, uint32_t *rlength);
void AcpiOverI2cWriteCmdParser(uint8_t wbuff[], uint32_t wlength);

#endif // _ITE_HID_ACPI_I2C_H_