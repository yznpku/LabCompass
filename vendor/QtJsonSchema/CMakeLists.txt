set(TARGET_NAME QtJsonSchema)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        *.cpp *.h
        )

add_library(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME} PUBLIC
        Qt5::Core
        )

target_include_directories(${TARGET_NAME} PUBLIC
        include
        )