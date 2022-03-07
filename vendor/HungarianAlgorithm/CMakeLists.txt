set(TARGET_NAME HungarianAlgorithm)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        *.cpp *.h
        )

add_library(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC
        .
        )