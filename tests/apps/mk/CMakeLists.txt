CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(HLSLCCTestsProj)

IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE "Release")
ENDIF(NOT CMAKE_BUILD_TYPE)

SET(HLSLCC_ROOT ${HLSLCCTestsProj_SOURCE_DIR}/../../../)
SET(TESTS_ROOT ${HLSLCC_ROOT}/tests/apps/)
SET(GLEW_DIR ${TESTS_ROOT}/common/glew/)
SET(GLUT_DIR ${TESTS_ROOT}/common/glut/)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TESTS_ROOT}/bin )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TESTS_ROOT}/lib )

INCLUDE_DIRECTORIES(${HLSLCC_ROOT}/include/)
INCLUDE_DIRECTORIES(${TESTS_ROOT})
INCLUDE_DIRECTORIES(${TESTS_ROOT}/common/)
INCLUDE_DIRECTORIES(${TESTS_ROOT}/common/glew/)
INCLUDE_DIRECTORIES(${TESTS_ROOT}/common/glut/include/)
INCLUDE_DIRECTORIES(${TESTS_ROOT}/common/vectormath/SSE/cpp/)

#Search normal dir as well as the debug and release dirs that visual studio generates.
LINK_DIRECTORIES(${HLSLCC_ROOT}/lib/)
LINK_DIRECTORIES(${TEST_DIR}/lib/)
IF( MSVC )
   LINK_DIRECTORIES(${HLSLCC_ROOT}/lib/$(ConfigurationName)/)
   LINK_DIRECTORIES(${TEST_DIR}/lib/$(ConfigurationName)/)
ENDIF()

#Common libs
#-glew
ADD_DEFINITIONS(-DGLEW_STATIC)
ADD_LIBRARY(glew STATIC ${GLEW_DIR}/glew.c)
#-Freeglut
ADD_DEFINITIONS(-DFREEGLUT_STATIC)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)#-DHAVE_CONFIG_H)
ADD_LIBRARY(fglib STATIC 
			${GLUT_DIR}/src/freeglut_callbacks ${GLUT_DIR}/src/freeglut_cursor ${GLUT_DIR}/src/freeglut_display
			${GLUT_DIR}/src/freeglut_ext ${GLUT_DIR}/src/freeglut_font ${GLUT_DIR}/src/freeglut_font_data
			${GLUT_DIR}/src/freeglut_gamemode ${GLUT_DIR}/src/freeglut_geometry ${GLUT_DIR}/src/freeglut_glutfont_definitions
			${GLUT_DIR}/src/freeglut_init ${GLUT_DIR}/src/freeglut_input_devices ${GLUT_DIR}/src/freeglut_internal ${GLUT_DIR}/src/freeglut_joystick
			${GLUT_DIR}/src/freeglut_main ${GLUT_DIR}/src/freeglut_menu ${GLUT_DIR}/src/freeglut_misc ${GLUT_DIR}/src/freeglut_overlay ${GLUT_DIR}/src/freeglut_spaceball
			${GLUT_DIR}/src/freeglut_state ${GLUT_DIR}/src/freeglut_stroke_mono_roman ${GLUT_DIR}/src/freeglut_stroke_roman
			${GLUT_DIR}/src/freeglut_structure ${GLUT_DIR}/src/freeglut_teapot ${GLUT_DIR}/src/freeglut_teapot_data ${GLUT_DIR}/src/freeglut_videoresize
			${GLUT_DIR}/src/freeglut_window)
#-Assimp
SET(ASSIMP_DIR ${TESTS_ROOT}/common/assimp)
INCLUDE_DIRECTORIES(${ASSIMP_DIR}/include/ ${ASSIMP_DIR}/code/BoostWorkaround)
ADD_DEFINITIONS(-DBOOST_WORKAROUND)
file(GLOB ASSIMP_CPPFILES ${ASSIMP_DIR}/code/*.cpp ${ASSIMP_DIR}/contrib/irrXML/*.cpp ${ASSIMP_DIR}/contrib/clipper/*.cpp ${ASSIMP_DIR}/contrib/poly2tri/poly2tri/sweep/*.cc ${ASSIMP_DIR}/contrib/poly2tri/poly2tri/common/*.cc)
file(GLOB ASSIMP_CFILES ${ASSIMP_DIR}/contrib/ConvertUTF/*.c ${ASSIMP_DIR}/contrib/zlib/*.c ${ASSIMP_DIR}/contrib/unzip/*.c)
ADD_LIBRARY(assimp STATIC ${ASSIMP_CPPFILES} ${ASSIMP_CFILES})

SET(COMMON_CODE ${TESTS_ROOT}/common/debug.cpp ${TESTS_ROOT}/common/Shader.cpp ${TESTS_ROOT}/common/Image.cpp ${TESTS_ROOT}/common/Model.cpp
${TESTS_ROOT}/common/debug.h ${TESTS_ROOT}/common/Shader.h ${TESTS_ROOT}/common/Image.h ${TESTS_ROOT}/common/Model.h ${TESTS_ROOT}/common/pstdint.h ${TESTS_ROOT}/common/itransform.h)
ADD_LIBRARY(common STATIC ${COMMON_CODE})

#Each test
add_subdirectory(lambertLit/)
add_subdirectory(extrudeGS/)
add_subdirectory(tessellation/)
add_subdirectory(generic/)
add_subdirectory(subroutines/)
