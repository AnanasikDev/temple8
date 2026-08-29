# ImNodeFlow
add_library(imnodeflow STATIC
    ${CMAKE_SOURCE_DIR}/vendor/ImNodeFlow/src/context_wrapper.h
    ${CMAKE_SOURCE_DIR}/vendor/ImNodeFlow/src/imgui_bezier_math.h
    ${CMAKE_SOURCE_DIR}/vendor/ImNodeFlow/src/imgui_bezier_math.inl
    ${CMAKE_SOURCE_DIR}/vendor/ImNodeFlow/src/imgui_extra_math.h
    ${CMAKE_SOURCE_DIR}/vendor/ImNodeFlow/src/imgui_extra_math.inl
    ${CMAKE_SOURCE_DIR}/vendor/ImNodeFlow/src/ImNodeFlow.cpp
    ${CMAKE_SOURCE_DIR}/vendor/ImNodeFlow/src/ImNodeFlow.inl
)
target_compile_definitions(imnodeflow PRIVATE IMGUI_DEFINE_MATH_OPERATORS)

target_include_directories(imnodeflow PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor/ImNodeFlow/include
)