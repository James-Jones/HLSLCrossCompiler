CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(TessellationProj)

ADD_EXECUTABLE(Tessellation ${TESTS_ROOT}/tessellation/main.cpp)

add_dependencies(Tessellation fglib)

TARGET_LINK_LIBRARIES(Tessellation common opengl32.lib fglib glew libHLSLcc)
