CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(ExtrudeGSProj)

ADD_EXECUTABLE(ExtrudeGS ${TESTS_ROOT}/extrudeGS/main.cpp)

add_dependencies(ExtrudeGS fglib assimp)

TARGET_LINK_LIBRARIES(ExtrudeGS common opengl32.lib fglib glew libHLSLcc assimp)