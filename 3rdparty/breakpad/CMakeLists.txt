set(LIB_NAME breakpad)
add_library(${LIB_NAME} STATIC "")

set(MOZ_CRASH_REPORTER_DIR ${3RDPARTY_DIR}/mozilla-crashreporter)
set(BREAKPAD_SRC_DIR ${MOZ_CRASH_REPORTER_DIR}/google-breakpad/src)
set(BREAKPAD_CLIENT_DIR ${MOZ_CRASH_REPORTER_DIR}/breakpad-client)

target_sources(${LIB_NAME}
    PRIVATE
    ${BREAKPAD_CLIENT_DIR}/minidump_file_writer.cc
    #    ${BREAKPAD_CLIENT_DIR}/minidump_file_writer.h
    #    ${BREAKPAD_CLIENT_DIR}/minidump_file_writer-inl.h
    )

set(${LIB_NAME}_INCLUDE_DIRS
    ${BREAKPAD_SRC_DIR}
    ${BREAKPAD_CLIENT_DIR}
    )

target_include_directories(${LIB_NAME}
    PRIVATE
    ${${LIB_NAME}_INCLUDE_DIRS}
    )

# Platform specifics
if (UNIX)
    set(BREAKPAD_CLIENT_LINUX_DIR ${BREAKPAD_CLIENT_DIR}/linux)
    #    file(GLOB_RECURSE hxxFiles ${BREAKPAD_CLIENT_LINUX_DIR}/*.h)
    #    file(GLOB_RECURSE cxxFiles ${BREAKPAD_CLIENT_LINUX_DIR}/*.cc)
    #    list(FILTER cxxFiles EXCLUDE REGEX "(.*)crash_generation_server.cc|(.*)unittest(.*)$")
    #    list(FILTER hxxFiles EXCLUDE REGEX "(.*)crash_generation_server.h|(.*)unittest(.*)$")
    set(cxxFiles
        ${BREAKPAD_SRC_DIR}/common/convert_UTF.cc
        ${BREAKPAD_SRC_DIR}/common/string_conversion.cc
        ${BREAKPAD_SRC_DIR}/common/linux/elfutils.cc
        ${BREAKPAD_SRC_DIR}/common/linux/linux_libc_support.cc
        ${BREAKPAD_SRC_DIR}/common/linux/memory_mapped_file.cc
        ${BREAKPAD_SRC_DIR}/common/linux/safe_readlink.cc
        ${BREAKPAD_SRC_DIR}/common/linux/file_id.cc
        ${BREAKPAD_SRC_DIR}/common/linux/breakpad_getcontext.S
        ${BREAKPAD_CLIENT_LINUX_DIR}/crash_generation/crash_generation_client.cc
        #        ${BREAKPAD_CLIENT_LINUX_DIR}/crash_generation/crash_generation_server.cc
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
    target_sources(${LIB_NAME}
        PRIVATE
        #        ${hxxFiles}
        ${cxxFiles}
        )

    # override the guid_creator.h header
    #    add_definitions(-DCOMMON_LINUX_GUID_CREATOR_H__=1)

    install(
        DIRECTORY ${BREAKPAD_CLIENT_LINUX_DIR}
        DESTINATION include/breakpad
        FILES_MATCHING PATTERN "*.h*"
        )

    install(TARGETS ${LIB_NAME}
        ARCHIVE DESTINATION lib
        )

    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow -Wno-error=stack-protector")
    endif()
endif()
