# Copyright (c) 2022 Iman Ahmadvand

# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

set(EXE_NAME minidump_2core)
add_executable(${EXE_NAME} "")

set(MOZ_CRASH_REPORTER_DIR ${3RDPARTY_DIR}/mozilla-crashreporter)
set(BREAKPAD_SRC_DIR ${MOZ_CRASH_REPORTER_DIR}/google-breakpad/src)
set(LIB_DISASM_DIR ${BREAKPAD_SRC_DIR}/third_party/libdisasm)

target_include_directories(${EXE_NAME}
    PRIVATE
    ${BREAKPAD_SRC_DIR}
    )

file(GLOB_RECURSE LIB_DISASM_SRCS ${LIB_DISASM_DIR}/*.c)

target_sources(${EXE_NAME}
    PRIVATE
    ${BREAKPAD_SRC_DIR}/tools/linux/md2core/minidump-2-core.cc
    ${BREAKPAD_SRC_DIR}/tools/linux/md2core/minidump_memory_range.h
    ${BREAKPAD_SRC_DIR}/common/linux/memory_mapped_file.cc
    ${BREAKPAD_SRC_DIR}/common/path_helper.cc
    ${BREAKPAD_SRC_DIR}/processor/simple_symbol_supplier.cc
    ${BREAKPAD_SRC_DIR}/processor/basic_source_line_resolver.cc
    ${BREAKPAD_SRC_DIR}/processor/simple_symbol_supplier.cc
    ${BREAKPAD_SRC_DIR}/processor/minidump_processor.cc
    ${BREAKPAD_SRC_DIR}/processor/minidump.cc
    ${BREAKPAD_SRC_DIR}/processor/source_line_resolver_base.cc
    ${BREAKPAD_SRC_DIR}/processor/logging.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalk_common.cc
    ${BREAKPAD_SRC_DIR}/processor/process_state.cc
    ${BREAKPAD_SRC_DIR}/processor/pathname_stripper.cc
    ${BREAKPAD_SRC_DIR}/processor/tokenize.cc
    ${BREAKPAD_SRC_DIR}/processor/stack_frame_symbolizer.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker.cc
    ${BREAKPAD_SRC_DIR}/processor/exploitability.cc
    ${BREAKPAD_SRC_DIR}/processor/symbolic_constants_win.cc
    ${BREAKPAD_SRC_DIR}/processor/call_stack.cc
    ${BREAKPAD_SRC_DIR}/processor/dump_object.cc
    ${BREAKPAD_SRC_DIR}/processor/dump_context.cc
    ${BREAKPAD_SRC_DIR}/processor/convert_old_arm64_context.cc
    ${BREAKPAD_SRC_DIR}/processor/basic_code_modules.cc
    ${BREAKPAD_SRC_DIR}/processor/proc_maps_linux.cc
    ${BREAKPAD_SRC_DIR}/processor/cfi_frame_info.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker_x86.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker_ppc.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker_ppc64.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker_amd64.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker_sparc.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker_mips.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker_arm.cc
    ${BREAKPAD_SRC_DIR}/processor/stackwalker_arm64.cc
    ${BREAKPAD_SRC_DIR}/processor/exploitability_win.cc
    ${BREAKPAD_SRC_DIR}/processor/exploitability_linux.cc
    ${BREAKPAD_SRC_DIR}/processor/disassembler_x86.cc
    ${LIB_DISASM_SRCS}
    )

install(
    TARGETS ${EXE_NAME}
    RUNTIME DESTINATION bin
    )
