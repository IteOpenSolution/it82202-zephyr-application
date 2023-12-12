#
# Copyright (c) 2023, ITE TECH. INC.
#
cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(IT82202_Zephyr_Application)

# 其他的 CMake 指令
include(${CMAKE_CURRENT_LIST_DIR}/src/app/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/src/boards/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/src/core/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/src/misc/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/src/oem/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/src/test/CMakeLists.txt)
