add_subdirectory(glad)
add_subdirectory(ImNodeFlow)
add_subdirectory(imviewguizmo)
add_subdirectory(imguizmo)
add_subdirectory(stb_image)
add_subdirectory(json)

include(FetchContent)

# glm
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	8d1fd52 #refs/tags/1.0.3
)
FetchContent_MakeAvailable(glm)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
FetchContent_Declare(glfw
    URL      https://github.com/glfw/glfw/archive/refs/tags/3.3.8.tar.gz
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
target_link_libraries(imnodeflow PUBLIC imgui_lib)
target_link_libraries(imviewguizmo INTERFACE imgui_lib)
target_link_libraries(imviewguizmo INTERFACE glm::glm)
target_link_libraries(imguizmo PUBLIC imgui_lib)
target_link_libraries(imguizmo PUBLIC glm::glm)
