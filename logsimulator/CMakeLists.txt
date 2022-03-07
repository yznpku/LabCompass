set(TARGET_NAME logsimulator)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        *.cpp *.h *.ui
        )

add_executable(${TARGET_NAME} WIN32 ${SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE
        src
        )

target_precompile_headers(${TARGET_NAME} PRIVATE
        src/stdafx.h
        )

target_link_libraries(${TARGET_NAME} PRIVATE
        common
        Qt5::Widgets
        )
