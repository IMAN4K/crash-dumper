set(EXE_NAME minidump_dump)
add_executable(${EXE_NAME} "")

set(MOZ_CRASH_REPORTER_DIR ${3RDPARTY_DIR}/mozilla-crashreporter)
set(BREAKPAD_SRC_DIR ${MOZ_CRASH_REPORTER_DIR}/google-breakpad/src)

target_include_directories(${EXE_NAME}
    PRIVATE
    ${BREAKPAD_SRC_DIR}
    )

target_sources(${EXE_NAME}
    PRIVATE
    ${BREAKPAD_SRC_DIR}/processor/minidump_dump.cc
    ${BREAKPAD_SRC_DIR}/processor/minidump.cc
    ${BREAKPAD_SRC_DIR}/processor/logging.cc
    ${BREAKPAD_SRC_DIR}/common/path_helper.cc
    ${BREAKPAD_SRC_DIR}/processor/dump_object.cc
    ${BREAKPAD_SRC_DIR}/processor/dump_context.cc
    ${BREAKPAD_SRC_DIR}/processor/convert_old_arm64_context.cc
    ${BREAKPAD_SRC_DIR}/processor/basic_code_modules.cc
    ${BREAKPAD_SRC_DIR}/processor/proc_maps_linux.cc
    ${BREAKPAD_SRC_DIR}/processor/pathname_stripper.cc
    )

install(
    TARGETS ${EXE_NAME}
    RUNTIME DESTINATION bin
    )
