#
# Copyright (c) 2023 ITE Corporation. All Rights Reserved.
# 
# SPDX-License-Identifier: Apache-2.0
# 

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/CORE_CHIPREGS.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CORE_CHIPREGS.h
    )

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/CORE_Memory.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CORE_Memory.h
    )

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/CORE_SLAVE_I2C.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CORE_SLAVE_I2C.h
    )

target_sources(app
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/CORE_TYPES.h
    )