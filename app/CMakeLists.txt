set(TARGET_NAME app)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        *.cpp *.h *.qrc
        )

add_executable(${TARGET_NAME} WIN32 ${SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE
        src
        )

target_precompile_headers(${TARGET_NAME} PRIVATE
        src/stdafx.h
        )

target_link_libraries(${TARGET_NAME} PUBLIC
        common
        qhotkey
        )
