set(PROJ_NAME dump_syms)
add_executable(${PROJ_NAME} "")

set(MOZ_CRASH_REPORTER_DIR ${3RDPARTY_DIR}/mozilla-crashreporter)
set(BREAKPAD_SRC_DIR ${MOZ_CRASH_REPORTER_DIR}/google-breakpad/src)

set(${PROJ_NAME}_INCLUDE_DIRS
    ${BREAKPAD_SRC_DIR}
    )

target_include_directories(${PROJ_NAME}
    PRIVATE
    ${${PROJ_NAME}_INCLUDE_DIRS}
    )

target_sources(${PROJ_NAME}
    PRIVATE
    ${BREAKPAD_SRC_DIR}/common/module.cc
    ${BREAKPAD_SRC_DIR}/common/path_helper.cc
    ${BREAKPAD_SRC_DIR}/common/stabs_reader.cc
    ${BREAKPAD_SRC_DIR}/common/stabs_to_module.cc
    ${BREAKPAD_SRC_DIR}/common/dwarf/dwarf2diehandler.cc
    ${BREAKPAD_SRC_DIR}/common/dwarf_cfi_to_module.cc
    ${BREAKPAD_SRC_DIR}/common/dwarf_cu_to_module.cc
    ${BREAKPAD_SRC_DIR}/common/dwarf_line_to_module.cc
    ${BREAKPAD_SRC_DIR}/common/dwarf_range_list_handler.cc
    ${BREAKPAD_SRC_DIR}/common/language.cc
    ${BREAKPAD_SRC_DIR}/common/dwarf/dwarf2reader.cc
    ${BREAKPAD_SRC_DIR}/common/dwarf/bytereader.cc
    ${BREAKPAD_SRC_DIR}/common/arm_ex_reader.cc
    ${BREAKPAD_SRC_DIR}/common/dwarf/elf_reader.cc
    ${BREAKPAD_SRC_DIR}/common/arm_ex_to_module.cc
    )

if (UNIX)
    add_definitions(-DN_UNDF=0x0)
    target_sources(${PROJ_NAME}
        PRIVATE
        ${BREAKPAD_SRC_DIR}/tools/linux/dump_syms/dump_syms.cc
        ${BREAKPAD_SRC_DIR}/common/linux/crc32.cc
        ${BREAKPAD_SRC_DIR}/common/linux/elfutils.cc
        ${BREAKPAD_SRC_DIR}/common/linux/elf_symbols_to_module.cc
        ${BREAKPAD_SRC_DIR}/common/linux/file_id.cc
        ${BREAKPAD_SRC_DIR}/common/linux/linux_libc_support.cc
        ${BREAKPAD_SRC_DIR}/common/linux/memory_mapped_file.cc
        ${BREAKPAD_SRC_DIR}/common/linux/dump_symbols.cc
        )
endif()

install(TARGETS ${PROJ_NAME}
    RUNTIME DESTINATION bin
    )
