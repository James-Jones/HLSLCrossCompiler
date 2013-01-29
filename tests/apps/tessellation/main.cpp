
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <Shader.h>
#include <vectormath_aos.h>
#include "common/debug.h"

using namespace Vectormath::Aos;

struct SimpleVertex
{
    float Pos[3];
    float Colour[3];
};

struct Globals
{
    float World[16];
    float View[16];
    float Projection[16];
    float InnerFactor;
    float OuterFactor;
    float unused[2];
};
const size_t GlobalsVec4Count = sizeof(Globals)/sizeof(float)/4;

ShaderEffect mTessEffect;
Matrix4 gWorld;
Matrix4 gView;
Matrix4 gProjection;
GLuint gIndexBuffer;
GLuint gVertexBuffer;
Globals gGlobals;

int WindowWidth = 640;
int WindowHeight = 480;

void display(void)
{
    // Update our time
    static float t = 0.0f;

    static uint32_t dwTimeStart = 0;
    uint32_t dwTimeCur = GetTickCount();
    if( dwTimeStart == 0 )
        dwTimeStart = dwTimeCur;
    t = ( dwTimeCur - dwTimeStart ) / 1000.0f;

    gWorld = Matrix4::identity(); //Matrix4::rotationY(t);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    mTessEffect.Enable();

    gGlobals.InnerFactor = 4;
    gGlobals.OuterFactor = 4;

    SetFloatArray(gWorld, gGlobals.World);
    SetFloatArray(gView, gGlobals.View);
    SetFloatArray(gProjection, gGlobals.Projection);

    mTessEffect.SetVec4(std::string("Globals"), GlobalsVec4Count, (float*)&gGlobals);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)(sizeof(float)*3));

    //glDrawElements(GL_PATCHES, 36, GL_UNSIGNED_INT, 0);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawArrays (GL_PATCHES, 0, 4);

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

    glutInitContextVersion (4, 0);
#ifdef _DEBUG
    glutInitContextFlags (GLUT_DEBUG);
#endif
    glutInitWindowSize (WindowWidth, WindowHeight); 
    glutInitWindowPosition (50, 50);
    glutCreateWindow (argv[0]);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc (keyboard);
    glutIdleFunc(display);

    glewInit();
#ifdef _DEBUG
    SetupOpenGLDebugCallback();
#endif

    //glFrontFace(GL_CW);
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.125f, 0.3f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mTessEffect.Create();
    mTessEffect.SetLanguage(LANG_400);
    mTessEffect.SetCompileFlags(HLSLCC_FLAG_TESS_ENABLED);
   
    mTessEffect.FromByteFile(std::string("shaders/tessellationVS.o"));
    mTessEffect.FromByteFile(std::string("shaders/tessellationHS.o"));
    mTessEffect.FromByteFile(std::string("shaders/tessellationDS.o"));
    mTessEffect.FromByteFile(std::string("shaders/tessellationPS.o"));

    gWorld = Matrix4::identity();

    Point3 Eye( 0.0f, 4.0f, -10.0f );
    Point3 At( 0.0f, 1.0f, 0.0f );
    Vector3 Up( 0.0f, 1.0f, 0.0f );

    gView = Matrix4::lookAt(Eye, At, Up);
    gProjection = Matrix4::perspective(3.14159f * 0.25f, WindowWidth / ( float )WindowHeight, 0.1f, 100.0f);


	SimpleVertex vertices[] =
    {
        {{-0.5,-0.5, 0}, {1, 0, 0}},
        {{0.5,-0.5, 0}, {1, 0, 0}},
        {{0.5,0.5, 0}, {1, 0, 0}},
        {{-0.5,0.5, 0}, {1, 0, 0}},
     };

	/*static GLfloat colors[] = {0.66f, 0.66f, 0.66f,0.0f,
							  0.33f, 0.33f, 0.33f,0.0f,
							  1.0f, 1.0f, 1.0f,0.0f,
							  1.0f, 0.4f, 0.4f,0.0f,};*/

    /*uint32_t indices[] =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };*/

    uint32_t indices[] =
    {
        0,1,3,
        3,1,2,

        5,4,6,
        6,4,7,

        8,9,11,
        11,9,10,

        13,12,14,
        14,12,15,

        16,17,19,
        19,17,18,

        21,20,22,
        22,20,23
    };

    glGenBuffers(1, &gIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 36,
        indices, GL_STATIC_DRAW);


    /*SimpleVertex vertices[] =
    {
        { { -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { 1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },

        { { -1.0f, -1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { 1.0f, -1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { -1.0f, -1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },

        { { -1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { -1.0f, 1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { -1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },

        { { 1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 1.0f, 1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },

        { { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f, 1.0f } },

        { { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
    };*/

    glGenBuffers(1, &gVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * 4,//24,
        vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)(sizeof(float)*3));
}

int main(int argc, char** argv)
{
    Init(argc, argv);
    glutMainLoop();

   return 0;
}
