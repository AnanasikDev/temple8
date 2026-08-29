add_library(imguizmo)

target_sources(imguizmo
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/ImGuizmo.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/ImGuizmo.h
)

target_include_directories(imguizmo
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)