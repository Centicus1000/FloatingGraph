cmake_minimum_required(VERSION 3.14.0)
project(FloatGraph)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# external dependencies
add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/imgui)
add_subdirectory(extern/vml)

# add source files
set(FLOAT_GRAPH_SOURCE_FILES
    main.cpp
    FloatGraph.cpp
    support/imgui_impl_glfw.cpp
    support/imgui_impl_opengl3.cpp
    support/timer.cpp
)


add_executable(FloatGraph ${FLOAT_GRAPH_SOURCE_FILES})
target_include_directories(FloatGraph PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/extern ${CMAKE_CURRENT_SOURCE_DIR}/support)
target_link_libraries(FloatGraph PUBLIC vml imgui glfw glad)

# default startup project for Visual Studio
if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT FloatGraph)
	set_property(TARGET FloatGraph PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()
