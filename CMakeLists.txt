cmake_minimum_required(VERSION 3.10)

project(CrashReporter)
set(LIB_NAME ${PROJECT_NAME})
add_library(${LIB_NAME} STATIC "")

set(3RDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)

# Breakpad
add_subdirectory(${3RDPARTY_DIR}/breakpad)
add_dependencies(${LIB_NAME} breakpad)
get_target_property(BreakPadIncludeDirs breakpad INCLUDE_DIRECTORIES)
target_include_directories(${LIB_NAME}
    PRIVATE
    ${BreakPadIncludeDirs}
    )

target_sources(${LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include/${LIB_NAME}/CrashReporter.h
    ${CMAKE_CURRENT_LIST_DIR}/src/CrashReporter.cpp
    )

target_include_directories(${LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

target_link_libraries(${LIB_NAME}
    PUBLIC breakpad
    )

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
    )

install(TARGETS ${LIB_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    )
