#
# Copyright (c) 2023 ITE Corporation. All Rights Reserved.
# 
# SPDX-License-Identifier: Apache-2.0
# 

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/app.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/version.h
    )   

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/cmdparser.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/cmdparser.h
    )

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/thermalmgm.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/thermalmgm.h
    )