set(LIB_NAME breakpad_client)
add_library(${LIB_NAME} STATIC "")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/dist)

set(MOZ_CRASH_REPORTER_DIR ${3RDPARTY_DIR}/mozilla-crashreporter)
set(BREAKPAD_SRC_DIR ${MOZ_CRASH_REPORTER_DIR}/google-breakpad)
set(BREAKPAD_CLIENT_DIR ${MOZ_CRASH_REPORTER_DIR}/breakpad-client)

target_sources(${LIB_NAME}
    PRIVATE
    ${BREAKPAD_CLIENT_DIR}/minidump_file_writer.cc
    ${BREAKPAD_CLIENT_DIR}/minidump_file_writer.h
    ${BREAKPAD_CLIENT_DIR}/minidump_file_writer-inl.h
    )

target_include_directories(${LIB_NAME}
    PRIVATE
    ${BREAKPAD_SRC_DIR}/src
    ${BREAKPAD_CLIENT_DIR}
    )

# Platform specifics
if (UNIX)
    set(BREAKPAD_CLIENT_LINUX_DIR ${BREAKPAD_CLIENT_DIR}/linux)
    file(GLOB_RECURSE hxxFiles ${BREAKPAD_CLIENT_LINUX_DIR}/*.h)
    file(GLOB_RECURSE cxxFiles ${BREAKPAD_CLIENT_LINUX_DIR}/*.cc)
    list(FILTER cxxFiles EXCLUDE REGEX "(.*)crash_generation_server.cc|(.*)unittest(.*)$")
    list(FILTER hxxFiles EXCLUDE REGEX "(.*)crash_generation_server.h|(.*)unittest(.*)$")
    message(${hxxFiles})
    message(${cxxFiles})
    target_sources(${LIB_NAME}
        PRIVATE
        ${hxxFiles}
        ${cxxFiles}
        )

    # override the guid_creator.h header
    add_definitions(-DCOMMON_LINUX_GUID_CREATOR_H__=1)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-shadow -Wno-error=stack-protector")
endif()
