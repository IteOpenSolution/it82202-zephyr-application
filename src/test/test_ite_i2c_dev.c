/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "../include/include.h"

#if ITE_I2C_DEV_TEST_EN

LOG_MODULE_REGISTER(test_ite_i2c_dev, 4);

uint8_t device_write[32];
uint8_t device_read[32];

#if DEBUG_I2C0_DEV_EN
const struct device *i2c0_bus = DEVICE_DT_GET(DT_NODELABEL(i2c0));
#else
const struct device *i2c0_bus = NULL;
#endif

#if DEBUG_I2C1_DEV_EN
const struct device *i2c1_bus = DEVICE_DT_GET(DT_NODELABEL(i2c1));
#else
const struct device *i2c1_bus = NULL;
#endif

#if DEBUG_I2C2_DEV_EN
const struct device *i2c2_bus = DEVICE_DT_GET(DT_NODELABEL(i2c2));
#else
const struct device *i2c2_bus = NULL;
#endif

#if DEBUG_I2C3_DEV_EN
const struct device *i2c3_bus = DEVICE_DT_GET(DT_NODELABEL(i2c3));
#else
const struct device *i2c3_bus = NULL;
#endif

#if DEBUG_I2C4_DEV_EN
const struct device *i2c4_bus = DEVICE_DT_GET(DT_NODELABEL(i2c4));
#else
const struct device *i2c4_bus = NULL;
#endif

#if DEBUG_I2C5_DEV_EN
const struct device *i2c5_bus = DEVICE_DT_GET(DT_NODELABEL(i2c5));
#else
const struct device *i2c5_bus = NULL;
#endif

struct i2c_bus_config {
    const struct device *i2c_dev;
};

static struct i2c_bus_config i2c_configs[6];

static void ite_i2c_init_configs(void) {
    i2c_configs[0].i2c_dev = i2c0_bus;
    i2c_configs[1].i2c_dev = i2c1_bus;
    i2c_configs[2].i2c_dev = i2c2_bus;
    i2c_configs[3].i2c_dev = i2c3_bus;
    i2c_configs[4].i2c_dev = i2c4_bus;
    i2c_configs[5].i2c_dev = i2c5_bus;
}

#define PIN_I2C5_CLK DT_NODELABEL(i2c5_clk_gpa4_default)
#define PIN_I2C5_DATA DT_NODELABEL(i2c5_data_gpa5_default)

int ite_i2c_device_pin_voltage_check(void)
{
#if 0
    typedef struct {
        const char* pin_name;
        const char* voltage_level;
    } PinConfig;

    PinConfig pin_configs[] = {
        {PIN_I2C5_CLK, BOARD_I2C2_VOLTAGE_LEVEL},
        {PIN_I2C5_DATA, BOARD_I2C2_VOLTAGE_LEVEL}
    };
    int num_pins = sizeof(pin_configs) / sizeof(pin_configs[0]);

    for (int i = 0; i < num_pins; i++) {
        if (DT_DROP(pin_configs[i].pin_name, gpio-voltage) != pin_configs[i].voltage_level) {
            DPRINTK(1, "I2C5 pin_%s_vlevel is %s\n", (i%2 == 0) ? "clk" : "data", pin_configs[i].voltage_level);
        }
    }
#endif
	return 0;
}

static int ite_i2c_device_init(void)
{
	ite_i2c_init_configs();

    for (int i = 0; i < ARRAY_SIZE(i2c_configs); ++i)
    {
        const struct device *dev = i2c_configs[i].i2c_dev;

		if( dev == NULL )
		{
			continue;
		}

        if (!device_is_ready(dev))
        {
            DPRINTK(1, "I2C%d device %s is not ready\n", i, dev->name);
            continue;
        }

        uint8_t ret = i2c_configure(dev, I2C_SPEED_SET(I2C_SPEED_FAST) | I2C_MODE_CONTROLLER);
        if (ret)
        {
            DPRINTK(1, "Failed to configure i2c%d device %s\n", i, dev->name);
        }
		else
		{
			DPRINTK(1, "I2C%d device %s is ready\n", i, dev->name);
		}
    }

	ite_i2c_device_pin_voltage_check();

    return 0;  // 或其他適當的返回值，如果需要
}

void test_ite_i2c_init(void)
{
	ite_i2c_target_init();

	ite_i2c_device_init();
}

uint8_t w_datas[256];
uint8_t r_datas[256];
uint8_t w_datas1[59];
uint8_t r_datas1[64];

static int test_i2c_host(void)
{
	uint8_t ret = 0;
	uint8_t target_addr = /*0x76*/AllI2cAddr[DEBUG_TARGET_SEL].addr;

	const struct device *dev = i2c_configs[5].i2c_dev;

	DPRINTK(1, "Target address : 0x%02x\n", target_addr * 2);

	DPRINTK(1, "[main]1.===write datas(<=255bytes FIFO mode allowed)===");
	for (int i = 0; i < sizeof(w_datas); i++) {
		w_datas[i] = i;
	}
	DPRINTK(1, "Device write\n");
	DPRINTK_DUMP_BUFF(1, w_datas, sizeof(w_datas));
	ret = i2c_write(dev, w_datas, sizeof(w_datas), target_addr);
	if (ret) {
		DPRINTK(1, "Fail to write: 0x%02x\n", ret);
		return -1;
	}

	DPRINTK(1, "\n[main]2.===read datas(<=255bytes FIFO mode allowed)===");
	if (i2c_read(dev, r_datas, sizeof(r_datas), target_addr)) {
		DPRINTK(1, "Fail to read");
		return -1;
	}
	DPRINTK(1, "Device read\n");
	DPRINTK_DUMP_BUFF(1, r_datas, sizeof(r_datas));

#if 0
	DPRINTK(1, "\n[main]3.===i2c_burst_read(<=255bytes FIFO mode allowed)===");
	(void)memset(&r_datas, 0, sizeof(r_datas));
	if (i2c_burst_read(dev, target_addr, 0xaa, r_datas, sizeof(r_datas))) {
		DPRINTK(1, "Fail to read");
		return -1;
	}

	DPRINTK(1, "\n[main]3-1.===i2c_burst_read(<=64bytes CQ mode allowed)===");
	if (i2c_burst_read(dev, target_addr, 0xaa, r_datas, sizeof(r_datas))) {
		DPRINTK(1, "Fail to read");
		return -1;
	}

	DPRINTK(1, "\n[main]4.===i2c_burst_write(CQ and FIFO mode don't allow)===");
	if (i2c_burst_write(dev, target_addr, 0xbb, w_datas, sizeof(w_datas)-1)) {
		DPRINTK(1, "Fail to write");
		return -1;
	}
#endif
#if 0
	DPRINTK(1, "\n[main]5.===Cros I2C: i2c_read_block(<=255bytes FIFO mode allowed)===");
	(void)memset(&r_datas, 0, sizeof(r_datas));
	if (i2c_read_block(1,0x52,0xcc,r_datas,sizeof(r_datas))) { //i2c_1-->port=1, i2c_4-->port=3
		DPRINTK(1, "Fail to read");
		return -1;
	}
	DPRINTK(1, "[i2c]axis raw data: %x %x %x %x %x %x\n",
				r_datas[0], r_datas[1], r_datas[2],
				r_datas[3], r_datas[4], r_datas[5]);
	DPRINTK(1, "\n[main]6.===Cros I2C: i2c_write_block(CQ and FIFO mode don't allow)===");
	if (i2c_write_block(1,0x52,0xdd,w_datas,sizeof(w_datas)-1)) {
		DPRINTK(1, "Fail to write");
		return -1;
	}
#endif
#if 0
	ret = i2c_target_driver_unregister(i2c_target_dev);
	if (ret) {
		DPRINTK(1, "I2C target unregister failed");
	}
#endif
	return 0;
}

int test_ite_i2c_hid(void)
{
	uint8_t ret = 0;
	uint8_t target_addr = /*0x76*/AllI2cAddr[DEBUG_TARGET_SEL].addr;

	const struct device *dev = i2c_configs[5].i2c_dev;

	memset(w_datas1, 0, sizeof(w_datas1));
	memset(r_datas, 0, sizeof(r_datas));

	w_datas1[0] = _HID_DESC_LAYOUT & 0xFF;
	w_datas1[1] = (_HID_DESC_LAYOUT & 0xFF00) >> 8;

	ret = i2c_write_read(dev, target_addr, w_datas1, 2, r_datas, sizeof(r_datas));
	if( ret )
	{
		DPRINTK(1, "Fail to read HID CMD 0x%02x: 0x%02x\n", _HID_DESC_LAYOUT, ret);
		return -1;
	}
	else
		DPRINTK_DUMP_BUFF(1, r_datas, sizeof(r_datas));

	return 0;
}

#include "../oem/OEM_ACPI.h"
uint8_t test_ite_i2c_acpi(void)
{
	struct TEST_ACPI_CMD {
		uint8_t wlength;
		uint8_t wcmd[128];
		uint8_t rlength;
		uint8_t rcmd[128];
	};

	struct TEST_ACPI_CMD test_acpi_cmd_byte[] = {
		// {0x05, {0x20, 0x01, 0x02, 0xC5, 0x01}, 0, {0}},  // 0x20
		// {0x02, {0x21, 0x01}, 1, {0}},                    // 0x21
		// {0x02, {0x21, 0x02}, 1, {0}},                    // 0x21
		// {0x02, {0x22, 0x01}, 3, {0}},                    // 0x22
		// {0x02, {0x22, 0x02}, 3, {0}},                    // 0x22
		// {0x02, {0x23, 0x00}, 0, {0}},                    // 0x23
		// {0x02, {0x23, 0x01}, 0, {0}},                    // 0x23
		{0x02, {0x24, 0x07}, 1, {0}},                    // 0x24
		{0x05, {0x25, 0x21, 0x02, 0xB8, 0x0B}, 3, {0}},  // 0x25
		{0x05, {0x25, 0x22, 0x02, 0xB8, 0x0B}, 3, {0}},  // 0x25
		{0x02, {0x26, 0x01}, 2, {0}},                    // 0x26
		{0x02, {0x26, 0x02}, 2, {0}},                    // 0x26
		{0x02, {0x27, 0x61}, 1, {0}},                    // 0x27
		{0x02, {0x27, 0x62}, 1, {0}},                    // 0x27
		{0x03, {0x28, 0x61, 0x01}, 65, {0}},              // 0x28
	};


	uint8_t target_addr = /*0x76*/AllI2cAddr[DEBUG_TARGET_SEL].addr;
	uint8_t ret = 0;
	const struct device *dev = i2c_configs[5].i2c_dev;

	uint8_t wbuff[255] = {0};
	uint32_t wlength = 0;

	uint8_t rbuff[255] = {0};
	uint32_t rlength = 0;

	for (int i = 0; i < sizeof(test_acpi_cmd_byte) / sizeof(test_acpi_cmd_byte[0]); i++)
	{
		DPRINTK(1, "target addr: 0x%02x, wcmd 0x%2X", target_addr, test_acpi_cmd_byte[i].wcmd[0]);

		memcpy(wbuff, test_acpi_cmd_byte[i].wcmd, test_acpi_cmd_byte[i].wlength);
		wlength = test_acpi_cmd_byte[i].wlength;
			
		AcpiWriteData_I2C_AB(wbuff, wlength);
		AcpiReadData_I2C_AB(rbuff, &rlength);
		DPRINTK(2, "wcmd");
		DPRINTK_DUMP_BUFF(2, wbuff, wlength);
		DPRINTK(2, "read");
		DPRINTK_DUMP_BUFF(2, rbuff, rlength);

		DPRINTK(2, "--------------------------------------");
	}

	return ret;
}

void test_ite_i2c(uint32_t opt)
{
	int ret;

	if ( (opt & MASK_I2C_DEV_TEST ) )
	{
		test_ite_i2c_init();

		if( opt & ITE_I2C_DEV_TEST_COMM )
		{
		DPRINTK(1, "[main]===test_i2c_host to target===");
		ret = test_i2c_host();
		if(ret)
			DPRINTK(1, "[main]fail to access");
		else
			DPRINTK(1, "[main]i2c transfer sucess!\n\n");
		}
		
		if ( opt & ITE_I2C_DEV_TEST_HID_PROT )
		{
			DPRINTK(1, "[main]===test i2c hid ===");
			ret = test_ite_i2c_hid();
			if(ret)
				DPRINTK(1, "[main]fail to access");
			else
				DPRINTK(1, "[main]i2c hid descriptor read sucess!\n\n");
		}

		if ( opt & ITE_I2C_DEV_TEST_ACPI )
		{
			DPRINTK(1, "[main]===test i2c acpi ===");
			ret = test_ite_i2c_acpi();
			if(ret)
				DPRINTK(1, "[main]fail to access");
			else
				DPRINTK(1, "[main]i2c acpi protocol test sucess!\n\n");
		}
	}


}

#endif // ITE_I2C_DEV_TEST_EN