set(PROJ_NAME minidump_stackwalk)
add_executable(${PROJ_NAME} "")

set(MOZ_CRASH_REPORTER_DIR ${3RDPARTY_DIR}/mozilla-crashreporter)
set(BREAKPAD_SRC_DIR ${MOZ_CRASH_REPORTER_DIR}/google-breakpad/src)
set(LIB_DISASM_DIR ${BREAKPAD_SRC_DIR}/third_party/libdisasm)

set(${PROJ_NAME}_INCLUDE_DIRS
    ${BREAKPAD_SRC_DIR}
    )

target_include_directories(${PROJ_NAME}
    PRIVATE
    ${${PROJ_NAME}_INCLUDE_DIRS}
    )

file(GLOB_RECURSE LIB_DISASM_SRCS ${LIB_DISASM_DIR}/*.c)

target_sources(${PROJ_NAME}
    PRIVATE
    ${BREAKPAD_SRC_DIR}/common/path_helper.cc
    ${BREAKPAD_SRC_DIR}/processor/minidump_stackwalk.cc
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

install(TARGETS ${PROJ_NAME}
    RUNTIME DESTINATION bin
    )
