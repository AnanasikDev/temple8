# temple8 is a cross-platform template project for creating graphical applications.
# It combines my older projects (NEM, Nanoite, SIF) and unifies their experience 
# into this one, clean solution.
#
# AnanaSeek4Jam, 2026.08
# 

# ------------------------------
# General
# ------------------------------

cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(temple8 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Apps")

if (SHOW_CONSOLE)
    set(SybSystem "/SUBSYSTEM:CONSOLE")
else()
    set(SybSystem "/SUBSYSTEM:WINDOWS")
endif()

# ------------------------------
# Libraries
# ------------------------------

# GLAD (compiled)
add_library(glad STATIC
    ${CMAKE_SOURCE_DIR}/vendor/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
)

# stb_image (header-only)
add_library(stb_image INTERFACE)

target_include_directories(stb_image INTERFACE
    ${CMAKE_SOURCE_DIR}/vendor/stb_image
)

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

target_link_libraries(imnodeflow PUBLIC imgui_lib)

include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.8-docking
)
FetchContent_MakeAvailable(imgui)

# ImGui wrapper
add_library(imgui_lib STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui_lib PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_lib PUBLIC glfw)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glad
        imgui_lib
        imnodeflow
        stb_image

        kernel32
        user32
        gdi32
        opengl32
        winmm
        dwmapi
)

# ------------------------------
# Utilities
# ------------------------------

# build statistics
function(add_build_stats target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -DTARGET_NAME=${target}
            -DTARGET_FILE=$<TARGET_FILE:${target}>
            -DBUILD_CONFIG=$<CONFIG>
            -DSTATS_FILE=${CMAKE_SOURCE_DIR}/.buildstats
            -P ${CMAKE_SOURCE_DIR}/cmake/WriteBuildStats.cmake
        COMMENT "Recording build stats for ${target}"
    )
endfunction()

add_build_stats(${PROJECT_NAME})