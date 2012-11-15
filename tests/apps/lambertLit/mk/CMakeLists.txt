CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# Project Name
PROJECT(LambertLitProj)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin" )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "../lib" )

SET(TEST_DIR ${CMAKE_SOURCE_DIR}/../)
SET(APP_DIR ${CMAKE_SOURCE_DIR}/../../)
SET(HLSLCC_ROOT ${CMAKE_SOURCE_DIR}/../../../../)

INCLUDE_DIRECTORIES(${APP_DIR}/common/)
INCLUDE_DIRECTORIES(${APP_DIR}/common/glew/)
INCLUDE_DIRECTORIES(${APP_DIR}/common/vectormath/SSE/cpp/)

INCLUDE_DIRECTORIES(${HLSLCC_ROOT}/)
LINK_DIRECTORIES(${HLSLCC_ROOT}/lib/Debug/)
LINK_DIRECTORIES(${TEST_DIR}/lib/Debug/)

#GLUT

ADD_DEFINITIONS(-DFREEGLUT_STATIC)

ADD_DEFINITIONS(-DGLEW_STATIC)

SET(GLUT_DIR ${APP_DIR}/common/glut)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR} ${GLUT_DIR} ${GLUT_DIR}/include)

ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)#-DHAVE_CONFIG_H)

#${GLUT_DIR}/src/freeglutdll.def
ADD_LIBRARY(fglib STATIC 
			${GLUT_DIR}/src/freeglut_callbacks ${GLUT_DIR}/src/freeglut_cursor ${GLUT_DIR}/src/freeglut_display
			${GLUT_DIR}/src/freeglut_ext ${GLUT_DIR}/src/freeglut_font ${GLUT_DIR}/src/freeglut_font_data
			${GLUT_DIR}/src/freeglut_gamemode ${GLUT_DIR}/src/freeglut_geometry ${GLUT_DIR}/src/freeglut_glutfont_definitions
			${GLUT_DIR}/src/freeglut_init ${GLUT_DIR}/src/freeglut_input_devices ${GLUT_DIR}/src/freeglut_internal ${GLUT_DIR}/src/freeglut_joystick
			${GLUT_DIR}/src/freeglut_main ${GLUT_DIR}/src/freeglut_menu ${GLUT_DIR}/src/freeglut_misc ${GLUT_DIR}/src/freeglut_overlay ${GLUT_DIR}/src/freeglut_spaceball
			${GLUT_DIR}/src/freeglut_state ${GLUT_DIR}/src/freeglut_stroke_mono_roman ${GLUT_DIR}/src/freeglut_stroke_roman
			${GLUT_DIR}/src/freeglut_structure ${GLUT_DIR}/src/freeglut_teapot ${GLUT_DIR}/src/freeglut_teapot_data ${GLUT_DIR}/src/freeglut_videoresize
			${GLUT_DIR}/src/freeglut_window)

#SET_TARGET_PROPERTIES(FREEGLUT PROPERTIES OUTPUT_NAME "FREEGLUT.lib")


ADD_EXECUTABLE(LambertLit ${TEST_DIR}/main.cpp ${APP_DIR}/common/debug.cpp ${APP_DIR}/common/Shader.cpp ${APP_DIR}/common/glew/glew.c)

add_dependencies(LambertLit fglib)

TARGET_LINK_LIBRARIES(LambertLit opengl32.lib fglib HLSLByteCodeToGLSL)