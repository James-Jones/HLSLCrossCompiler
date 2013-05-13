CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(SubroutinesProj)

ADD_EXECUTABLE(Subroutines ${TESTS_ROOT}/subroutines/main.cpp)

add_dependencies(Subroutines fglib)

TARGET_LINK_LIBRARIES(Subroutines common opengl32.lib fglib glew libHLSLcc assimp)
