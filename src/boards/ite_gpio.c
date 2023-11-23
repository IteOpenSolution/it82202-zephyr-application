/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/dt-bindings/gpio/ite-it8xxx2-gpio.h>
#include "../include/include.h"

#define USEC_PSEC (CONFIG_SYS_CLOCK_TICKS_PER_SEC * 1000)

#define HidIntDelay_1ms ((3 * USEC_PSEC) / 1000)	// 1ms, this delay time used for k_busy_waitms

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void Hid_Interrupt_Pin_Toggle(void)
{
	int ret;

	DPRINTK(1, "Hid_Interrupt_Pin_Toggle");

	ret = gpio_pin_toggle_dt(&led);
	if (ret < 0) {
		DPRINTK(1, "gpio pin I2C1_INT toggle failed");
	}
	k_busy_wait(HidIntDelay_1ms);

	ret = gpio_pin_toggle_dt(&led);
	if (ret < 0) {
		DPRINTK(1, "gpio pin I2C1_INT toggle failed");
	}
#if 0
	k_busy_wait(HidIntDelay_1ms);
#endif
}

void ite_gpio_init(void)
{
	int ret;

	DPRINTK(1, "ite_gpio_init");

	if (!gpio_is_ready_dt(&led)) {
		DPRINTK(1, "gpio pin I2C1_INT not ready");
		// return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		DPRINTK(1, "gpio pin I2C1_INT configure_dt failed");
		// return 0;
	}
}

