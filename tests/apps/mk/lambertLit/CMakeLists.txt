CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(LambertLitProj)

ADD_EXECUTABLE(LambertLit ${TESTS_ROOT}/lambertLit/main.cpp)

add_dependencies(LambertLit fglib)

TARGET_LINK_LIBRARIES(LambertLit common opengl32.lib fglib glew libHLSLcc)