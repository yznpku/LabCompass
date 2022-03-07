set(TARGET_NAME QtSuperMacros)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        *.cpp *.h
        )

add_library(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME} PUBLIC
        Qt5::Core
        Qt5::Qml
        )

target_include_directories(${TARGET_NAME} PUBLIC
        .
        )