CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(GenericProj)

ADD_EXECUTABLE(Generic ${TESTS_ROOT}/generic/main.cpp)

add_dependencies(Generic fglib)

TARGET_LINK_LIBRARIES(Generic common opengl32.lib fglib glew libHLSLcc assimp)
