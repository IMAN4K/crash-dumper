set(PROJ_NAME ${PROJECT_NAME})
#add_library(${PROJ_NAME} STATIC "")

#set(MOZ_CRASH_REPORTER_DIR ${3RDPARTY_DIR}/mozilla-crashreporter)
#set(BREAKPAD_SRC_DIR ${MOZ_CRASH_REPORTER_DIR}/google-breakpad/src)
#set(BREAKPAD_CLIENT_DIR ${MOZ_CRASH_REPORTER_DIR}/breakpad-client)

#target_sources(${PROJ_NAME}
#    PRIVATE
#    ${CMAKE_CURRENT_LIST_DIR}/include/${PROJ_NAME}/CrashReporter.h
#    ${CMAKE_CURRENT_LIST_DIR}/src/CrashReporter.cpp
#    )

#target_include_directories(${PROJ_NAME}
#    PRIVATE
#    ${CMAKE_CURRENT_LIST_DIR}/include
#    )

#set(${PROJ_NAME}_INCLUDE_DIRS
#    ${BREAKPAD_SRC_DIR}
#    ${BREAKPAD_CLIENT_DIR}
#    )

#target_include_directories(${PROJ_NAME}
#    PRIVATE
#    ${${PROJ_NAME}_INCLUDE_DIRS}
#    )

# Platform specifics
if (UNIX)
endif()

install(TARGETS ${PROJ_NAME}
    RUNTIME DESTINATION bin
    )
