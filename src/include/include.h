/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ITE_INCLUDE_H_
#define _ITE_INCLUDE_H_

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "../app/cmdparser.h"
#include "../app/thermalmgm.h"
#include "../app/version.h"

#include "../boards/ite_board_config.h"
#include "../boards/ite_board_init.h"
#include "../boards/ite_gpio.h"
#include "../boards/ite_hid_acpi_i2c.h"
#include "../boards/ite_i2c_target.h"

#include "../core/CORE_CHIPREGS.h"
#include "../core/CORE_Memory.h"
#include "../core/CORE_SLAVE_I2C.h"
#include "../core/CORE_TYPES.h"

#include "../misc/ite_task_def.h"
#include "../misc/ite_task_handler.h"

#include "../oem/OEM_ACPI.h"
#include "../oem/OEM_Memory.h"
#include "../oem/OEM_PROJECT.h"
#include "../oem/OEM_VER.h"

#endif /* _ITE_INCLUDE_H_ */
