/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/dt-bindings/gpio/ite-it8xxx2-gpio.h>
#include "../include/include.h"

LOG_MODULE_REGISTER(ite_gpio, LOG_LEVEL_ERR);

#define USEC_PSEC (CONFIG_SYS_CLOCK_TICKS_PER_SEC * 1000)

#define HidIntDelay_1ms ((3 * USEC_PSEC) / 1000)	// 1ms, this delay time used for k_busy_waitms

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void Hid_Interrupt_Pin_Toggle(void)
{
	int ret;

	ret = gpio_pin_toggle_dt(&led);
	if (ret < 0) {
		LOG_ERR("gpio pin I2C1_INT toggle failed");
	}
	k_busy_wait(HidIntDelay_1ms);

	ret = gpio_pin_toggle_dt(&led);
	if (ret < 0) {
		LOG_ERR("gpio pin I2C1_INT toggle failed");
	}
}

void ite_gpio_init(void)
{
	int ret;

	if (!gpio_is_ready_dt(&led)) {
		LOG_ERR("gpio pin I2C1_INT not ready");
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		LOG_ERR("gpio pin I2C1_INT configure_dt failed");
	}
}

