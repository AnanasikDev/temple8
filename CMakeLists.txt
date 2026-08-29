# temple8 is a cross-platform template project for creating graphical applications.
# It combines my older projects (NEM, Nanoite, SIF) and unifies their experience 
# into this one, clean solution. No AI was used.
#
# AnanaSeek4Jam, 2026.08
# 

# ------------------------------
# General
# ------------------------------

cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(temple8 LANGUAGES C CXX)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Apps")

if (SHOW_CONSOLE)
    set(SybSystem "/SUBSYSTEM:CONSOLE")
else()
    set(SybSystem "/SUBSYSTEM:WINDOWS")
endif()

# ------------------------------
# Libraries
# ------------------------------

add_subdirectory(vendor)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glad
        imgui_lib
        imnodeflow
        stb_image
        glm::glm

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

# shipping exe
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/out/ship
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_SOURCE_DIR}/out/ship/${PROJECT_NAME}.exe
    COMMENT "Shipped"
)