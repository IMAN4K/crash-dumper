# Copyright (c) 2022 Iman Ahmadvand

# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.10)

project(CrashDumperToolkit
    LANGUAGES C CXX ASM
    VERSION 1.0.0
    )

set(3RDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
add_subdirectory(crash-dumper)
add_subdirectory(minidump-dump)

if (UNIX)
    add_subdirectory(minidump-2core)
endif()
