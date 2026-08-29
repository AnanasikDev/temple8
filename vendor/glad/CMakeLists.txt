add_library(glad)

target_sources(glad
    PRIVATE
        src/gl.c
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/khrplatform.h
        ${CMAKE_CURRENT_LIST_DIR}/include/gl.h
)

target_include_directories(glad
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)