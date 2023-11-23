#
# Copyright (c) 2023 ITE Corporation. All Rights Reserved.
# 
# SPDX-License-Identifier: Apache-2.0
# 

target_sources(app
      PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/ite_board_config.h
)

target_sources(app
      PRIVATE 
      ${CMAKE_CURRENT_LIST_DIR}/ite_board_init.c
      PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/ite_board_init.h
)

target_sources(app
      PRIVATE 
      ${CMAKE_CURRENT_LIST_DIR}/ite_gpio.c
      PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/ite_gpio.h
)

target_sources(app
      PRIVATE 
      ${CMAKE_CURRENT_LIST_DIR}/ite_hid_acpi_i2c.c
      PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/ite_hid_acpi_i2c.h
)

target_sources(app
      PRIVATE 
      ${CMAKE_CURRENT_LIST_DIR}/ite_i2c_target.c
      PUBLIC
      ${CMAKE_CURRENT_LIST_DIR}/ite_i2c_target.h
)
