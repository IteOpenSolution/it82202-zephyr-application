#
# Copyright (c) 2023 ITE Corporation. All Rights Reserved.
# 
# SPDX-License-Identifier: Apache-2.0
# 

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/test_ite_functions.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/test_ite_functions.h
    )

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/test_ite_i2c_dev.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/test_ite_i2c_dev.h
    )

# target_sources(app
#     PRIVATE 
#     ${CMAKE_CURRENT_LIST_DIR}/debug_test.c
#     PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/debug_it82202.h
#     )