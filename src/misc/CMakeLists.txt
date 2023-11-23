#
# Copyright (c) 2023 ITE Corporation. All Rights Reserved.
# 
# SPDX-License-Identifier: Apache-2.0
# 
target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/ite_task_handler.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/ite_task_handler.h
    )

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/ite_task_def.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/ite_task_def.h
    )   