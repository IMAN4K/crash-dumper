cmake_minimum_required(VERSION 3.10)

project(CrashReporterToolKit
    LANGUAGES C CXX ASM
    VERSION 1.0.0
    )

set(3RDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
add_subdirectory(crash-reporter)
#add_subdirectory(minidump-analyzer)
