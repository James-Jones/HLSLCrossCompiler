
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <toGLSL.h>
#include <Shader.h>
#include <vectormath_aos.h>
#include <debug.h>

using namespace Vectormath::Aos;

Matrix4 gWorld;
Matrix4 gView;
Matrix4 gProjection;

int WindowWidth = 640;
int WindowHeight = 480;

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    gProjection = Matrix4::perspective(3.14159f * 0.25f, w / ( float )h, 0.1f, 100.0f);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void Init(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glewInit();

    glutInitContextVersion (3, 1);
#ifdef _DEBUG
    glutInitContextFlags (GLUT_DEBUG);
#endif
    glutInitWindowSize (WindowWidth, WindowHeight); 
    glutInitWindowPosition (0, 0);
    glutCreateWindow (argv[0]);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc (keyboard);
    glutIdleFunc(display);

    glewInit();
#ifdef _DEBUG
    SetupOpenGLDebugCallback();
#endif

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.125f, 0.3f, 1.0f);
}

int main(int argc, char** argv)
{
    Init(argc, argv);
    glutMainLoop();

   return 0;
}
