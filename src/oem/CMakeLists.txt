#
# Copyright (c) 2023 ITE Corporation. All Rights Reserved.
# 
# SPDX-License-Identifier: Apache-2.0
# 

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/OEM_ACPI.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/OEM_ACPI.h
    )


target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/OEM_Memory.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/OEM_Memory.h
    )

target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/OEM_NIST.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/OEM_NIST.h
    )
    
target_sources(app
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/OEM_PROJECT.h
    )
    
    target_sources(app
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/OEM_VER.c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/OEM_VER.h
    )
    
