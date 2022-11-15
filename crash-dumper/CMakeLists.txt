# Copyright (c) 2022 Iman Ahmadvand

# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

set(LIB_NAME CrashReporter)
add_library(${LIB_NAME} STATIC "")

set(CMAKE_ASM_FLAGS "${CFLAGS} -x assembler-with-cpp")
set(MOZ_CRASH_REPORTER_DIR ${3RDPARTY_DIR}/mozilla-crashreporter)
set(BREAKPAD_SRC_DIR ${MOZ_CRASH_REPORTER_DIR}/google-breakpad/src)
set(BREAKPAD_CLIENT_DIR ${MOZ_CRASH_REPORTER_DIR}/breakpad-client)

target_sources(${LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include/${LIB_NAME}/CrashReporter.h
    )

target_include_directories(${LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

set(${LIB_NAME}_INCLUDE_DIRS
    ${BREAKPAD_SRC_DIR}
    ${BREAKPAD_CLIENT_DIR}
    )

target_include_directories(${LIB_NAME}
    PRIVATE
    ${${LIB_NAME}_INCLUDE_DIRS}
    )

if (UNIX)
    set(BREAKPAD_CLIENT_LINUX_DIR ${BREAKPAD_CLIENT_DIR}/linux)
    target_sources(${LIB_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/CrashReporter.cpp
        ${BREAKPAD_SRC_DIR}/common/convert_UTF.cc
        ${BREAKPAD_SRC_DIR}/common/string_conversion.cc
        ${BREAKPAD_SRC_DIR}/common/linux/elfutils.cc
        ${BREAKPAD_SRC_DIR}/common/linux/linux_libc_support.cc
        ${BREAKPAD_SRC_DIR}/common/linux/memory_mapped_file.cc
        ${BREAKPAD_SRC_DIR}/common/linux/safe_readlink.cc
        ${BREAKPAD_SRC_DIR}/common/linux/file_id.cc
        ${BREAKPAD_SRC_DIR}/common/linux/breakpad_getcontext.S
        ${BREAKPAD_CLIENT_DIR}/minidump_file_writer.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/crash_generation/crash_generation_client.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/dump_writer_common/thread_info.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/dump_writer_common/ucontext_reader.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/handler/exception_handler.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/handler/guid_generator.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/handler/minidump_descriptor.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/log/log.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/microdump_writer/microdump_writer.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/minidump_writer/linux_dumper.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/minidump_writer/linux_ptrace_dumper.cc
        ${BREAKPAD_CLIENT_LINUX_DIR}/minidump_writer/minidump_writer.cc
        )

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow -Wno-error=stack-protector")
    endif()
endif()

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
    )

install(TARGETS ${LIB_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    )
