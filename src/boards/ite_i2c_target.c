/*
 * Copyright (c) 2023 ITE Corporation. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT ite_target_i2c

#include <zephyr/drivers/i2c.h>
#include "../include/include.h"

LOG_MODULE_REGISTER(i2c_ite_target, LOG_LEVEL_DBG);

#define I2C_TARGET_NODE_0 DT_NODELABEL(i2c0_target)
#define I2C_TARGET_NODE_1 DT_NODELABEL(i2c1_target)
#define I2C_TARGET_NODE_2 DT_NODELABEL(i2c2_target)

const struct device *i2c0_target_dev = DEVICE_DT_GET(I2C_TARGET_NODE_0);
const struct device *i2c1_target_dev = DEVICE_DT_GET(I2C_TARGET_NODE_1);
const struct device *i2c2_target_dev = DEVICE_DT_GET(I2C_TARGET_NODE_2);

struct i2c_addr AllI2cAddr[3] = {
    {0x5b, 0xF04300}, // I2C0 target address
    {0x3a, 0xF04380}, // I2C1 target address
    {0x76, 0xF04400}  // I2C2 target address
};

#define GetI2cIdMatchStatus(base) ((IT8XXX2_I2C_STR2(base) & 0xF0) >> 4) // 1 ~ 4: ID1 ~ ID4
#define GetI2cRWBit(base) ((IT8XXX2_I2C_CMD_ADDL(base) & 0x40) >> 6)     // 0: read; 1: write

#define PIN_I2C0_CLK DT_NODELABEL(i2c0_clk_gpb3_default)
#define PIN_I2C0_DATA DT_NODELABEL(i2c0_data_gpb4_default)

#define PIN_I2C1_CLK DT_NODELABEL(i2c1_clk_gpc1_default)
#define PIN_I2C1_DATA DT_NODELABEL(i2c1_data_gpc2_default)

#define PIN_I2C2_CLK DT_NODELABEL(i2c2_clk_gpf6_default)
#define PIN_I2C2_DATA DT_NODELABEL(i2c2_data_gpf7_default)

static struct I2cAddressInfo get_i2c_address(struct i2c_target_config *config)
{
    struct I2cAddressInfo address_info = {0};

    for (uint8_t i = 0; i < sizeof(AllI2cAddr) / sizeof(AllI2cAddr[0]); i++)
    {
        if (config->address == AllI2cAddr[i].addr)
        {
            address_info.main_address = config->address;
            address_info.id = GetI2cIdMatchStatus(AllI2cAddr[i].base);
            return address_info;
        }
    }
    return address_info;
}

struct i2c_target_dev_config {
	/* I2C alternate configuration */
	struct i2c_dt_spec bus;
};

struct i2c_target_data {
	struct i2c_target_config config;
};

static int i2c_ite_target_write_requested(struct i2c_target_config *config)
{
	return 0;
}

static int i2c_ite_target_read_requested(struct i2c_target_config *config,
					 uint8_t *val)
{
	return 0;
}

static int i2c_ite_target_write_received(struct i2c_target_config *config,
					 uint8_t val)
{
	return 0;
}

static int i2c_ite_target_read_processed(struct i2c_target_config *config,
					 uint8_t *val)
{
	return 0;
}

static int i2c_ite_target_stop(struct i2c_target_config *config)
{
	LOG_DBG("[target]: target stop");

	return 0;
}

#ifdef CONFIG_I2C_TARGET_BUFFER_MODE
static void i2c_ite_target_buf_write_received(struct i2c_target_config *config,
					      uint8_t *ptr, uint32_t len)
{
#if ITE_I2C_DEV_TEST_EN
	LOG_DBG("[target]: w-ptr=%p, len=%d", (void *)ptr, len);

#else
	struct I2cAddressInfo TargetInfor = get_i2c_address(config);
    LOG_DBG("i2c_ite_target_buf_write_received");
    LOG_DBG("\tTargetInfor: main_address = %x, id = %x", TargetInfor.main_address, TargetInfor.id);  
    LOG_DBG("\tbuffer addr: %p, lenth: %d", (void *)ptr, len);
    // in the design of it8987, the function - main_service(), 
    // via some conditions to process  or service_SlaveI2C_B()
    // here we depend on the address and id to determine which function to call
    // the difference is service_SlaveI2C_A()/B() to I2C0/1 in it8987, 
    // but here is HID to HidOverI2cWriteCmdParser, 
    // acpi to AcpiWCmdParser

    if (TargetInfor.main_address == AllI2cAddr[0].addr && TargetInfor.id == 1)
    {   // we do not receive cmd after pre-define function enable 
		LOG_DBG("\tpre-define function");
    }
    else if (TargetInfor.main_address == AllI2cAddr[1].addr && TargetInfor.id == 1)
    {   // HID write
        LOG_DBG("\tHidOverI2cWriteCmdParser");
        // HidOverI2cWriteCmdParser() is similiar to Write_HID_DeviceB()
        // deal HID write cmd
        HidOverI2cWriteCmdParser(ptr, len);
    }
    // else if ((TargetInfor.main_address == AllI2cAddr[0].addr || TargetInfor.main_address == AllI2cAddr[1].addr) &&
    //          TargetInfor.id == 2)
    else if ( TargetInfor.main_address == 0xEC || TargetInfor.main_address == 0x76 || 1 )
    {   // ACPI write
        LOG_DBG("\tAcpiOverI2cWriteCmdParser");
        // AcpiWCmdParser() is similiar to Write_ACPI_DeviceB()
        // deal acpi write cmd
        AcpiOverI2cWriteCmdParser(ptr, len);
    }
#endif
}

static int i2c_ite_target_buf_read_requested(struct i2c_target_config *config,
					     uint8_t **ptr, uint32_t *len)
{
#if ITE_I2C_DEV_TEST_EN
	*len = 256;
	uint8_t r_datas[*len];

	for (int i = 0; i < *len; i++) {
		r_datas[i] = 0xcc;
	}
	*ptr = r_datas;
	LOG_DBG("[target]: r-ptr=%p", (void *)*ptr);

	return 0;

#else
    struct I2cAddressInfo TargetInfor = get_i2c_address(config);
    LOG_DBG("i2c_ite_target_buf_read_requested");
    if (TargetInfor.main_address == AllI2cAddr[0].addr && TargetInfor.id == 1)
    {   // we do not receive cmd after pre-define function enable 
		LOG_DBG("\tpre-define function");
    }
    else if (TargetInfor.main_address == AllI2cAddr[1].addr && TargetInfor.id == 1)
    {   // HID read
        LOG_DBG("\tHidOverI2cReadCmdParser");
        // HidOverI2cWriteCmdParser() is similiar to Write_HID_DeviceB()
        // deal HID write cmd
        HidOverI2cReadCmdParser(&*ptr, len);
    }
    // else if ((TargetInfor.main_address == AllI2cAddr[0].addr || TargetInfor.main_address == AllI2cAddr[1].addr) &&
            //  TargetInfor.id == 2)
    else
    {   // ACPI read
        LOG_DBG("\tAcpiOverI2cReadCmdParser");
        // AcpiWCmdParser() is similiar to Write_ACPI_DeviceB()
        // deal acpi write cmd
        AcpiOverI2cReadCmdParser(&*ptr, len);
    }

    return 0;
#endif
}
#endif

static const struct i2c_target_callbacks target_callbacks = {
	.write_requested = i2c_ite_target_write_requested,
	.read_requested = i2c_ite_target_read_requested,
	.write_received = i2c_ite_target_write_received,
	.read_processed = i2c_ite_target_read_processed,
#ifdef CONFIG_I2C_TARGET_BUFFER_MODE
	.buf_write_received = i2c_ite_target_buf_write_received,
	.buf_read_requested = i2c_ite_target_buf_read_requested,
#endif
	.stop = i2c_ite_target_stop,
};

static int i2c_ite_target_register(const struct device *dev)
{
	const struct i2c_target_dev_config *cfg = dev->config;
	struct i2c_target_data *data = dev->data;

	LOG_DBG("[target]i2c target register");

	return i2c_target_register(cfg->bus.bus, &data->config);
}

static int i2c_ite_target_unregister(const struct device *dev)
{
	const struct i2c_target_dev_config *cfg = dev->config;
	struct i2c_target_data *data = dev->data;

	LOG_DBG("[target]i2c target unregister");

	return i2c_target_unregister(cfg->bus.bus, &data->config);
}

static const struct i2c_target_driver_api api_funcs = {
	.driver_register = i2c_ite_target_register,
	.driver_unregister = i2c_ite_target_unregister,
};

static int i2c_ite_target_init(const struct device *dev)
{
	const struct i2c_target_dev_config *cfg = dev->config;
	struct i2c_target_data *data = dev->data;

	LOG_DBG("[target]i2c_target_init i2c target bus=%p",cfg->bus.bus); //I2C5 node
	LOG_DBG("[target]i2c_target_init i2c target dev=%p",dev); //I2C target

	/* Check I2C controller ready. */
	if (!device_is_ready(cfg->bus.bus)) {
		LOG_ERR("I2C controller device not ready");
		return -ENODEV;
	}

	data->config.address = cfg->bus.addr;
	data->config.callbacks = &target_callbacks;

	return 0;
}

#define I2C_ITE_TARGET_INIT(inst)                                               \
	static const struct i2c_target_dev_config i2c_target_cfg_##inst = {     \
		.bus = I2C_DT_SPEC_INST_GET(inst),			        \
	};                                                                      \
	static struct i2c_target_data i2c_target_data_##inst;                   \
	I2C_DEVICE_DT_INST_DEFINE(inst, i2c_ite_target_init,                    \
				  NULL,                                         \
				  &i2c_target_data_##inst,                      \
				  &i2c_target_cfg_##inst,                       \
				  POST_KERNEL,                                  \
				  CONFIG_I2C_TARGET_INIT_PRIORITY,              \
				  &api_funcs);                                  \

DT_INST_FOREACH_STATUS_OKAY(I2C_ITE_TARGET_INIT)

/**
 * @brief Initialize the I2C target devices
 *
 * @return 0 on success, negative error code on failure
 */

int ite_i2c_target_init(void)
{
    uint32_t ret;
    LOG_DBG("ite_i2c_target_init");
#if 0
    struct i2c_bus_config
    {
        const struct device *target_dev;
    };

    struct i2c_bus_config i2c_configs[] =
    {
        {
            i2c0_target_dev,
        },
        // {
        //     i2c1_target_dev,
        // },
        // {
        //     i2c2_target_dev,
        // }
    };

    for (int i = 0; i < sizeof(i2c_configs) / sizeof(struct i2c_bus_config); i++)
    {
        ret = i2c_target_driver_register(i2c_configs[i].target_dev);
        if (ret)
        {
            // Handle target registration failure
            LOG_DBG("I2C%d target register failed\n", i);
        }
        else
        {
            LOG_DBG("I2C%d target register success, address: 0x%02x\n", i, AllI2cAddr[i].addr);
        }
    }
#else
    ret = i2c_target_driver_register(i2c0_target_dev);
    if (ret)
    {
        // Handle target registration failure
        LOG_DBG("I2C%d target register failed\n", 0);
    }
    else
    {
        LOG_DBG("I2C%d target register success, address: 0x%02x\n", 0, AllI2cAddr[0].addr);
    }

    ret = i2c_target_driver_register(i2c1_target_dev);
    if (ret)
    {
        // Handle target registration failure
        LOG_DBG("I2C%d target register failed\n", 1);
    }
    else
    {
        LOG_DBG("I2C%d target register success, address: 0x%02x\n", 1, AllI2cAddr[1].addr);
    }
#endif
    return 0;
}

/*
 * Deinitialize the I2C target.
 * Returns: 0 on success
 */
int ite_i2c_target_deinit(void)
{
    /*
     * It is impossible to disable the I2C target, so we don't need to unregister the I2C target driver.
     * But keep the code to prevent future changes.
     */
#if 0
    const struct device *const i2c_target_dev;
    uint8_t ret = 0;
    LOG_DBG("i2c_target_driver_unregister");

    for ( uint8_t i = 0; i < 5; i++)
    {
        ret = i2c_target_driver_unregister(i2c_target_dev);
        if (ret)
        {
            LOG_DBG("I2C target unregister failed");
            return ret;
        }
    }

#endif
    return 0;
}