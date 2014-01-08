CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(IntegerProj)

ADD_EXECUTABLE(Integer ${TESTS_ROOT}/integer/main.cpp)

add_dependencies(Integer fglib)

TARGET_LINK_LIBRARIES(Integer common opengl32.lib fglib glew libHLSLcc assimp)
