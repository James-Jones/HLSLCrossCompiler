
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <Shader.h>
#include <vectormath_aos.h>
#include "common/debug.h"

struct SimpleVertex
{
    float Pos[3];
    float Normal[3];
};

struct Globals
{
    float World[16];
    float View[16];
    float Projection[16];
    float vLightDir[8];
    float vLightColor[8];
    float vOutputColor[4];
};
const size_t GlobalsVec4Count = sizeof(Globals)/sizeof(float)/4;

using namespace Vectormath::Aos;

ShaderEffect mLambertLitEffect;
ShaderEffect mSolidColour;
Matrix4 gWorld;
Matrix4 gView;
Matrix4 gProjection;
GLuint gIndexBuffer;
GLuint gVertexBuffer;
Globals gGlobals;

#define UBO 1

GLuint ubo;
GLuint ubo2;

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

    gWorld = Matrix4::rotationY(t);

    Vector4 vLightDirs[2] =
    {
        Vector4(-0.577f, 0.577f, -0.577f, 1.0f),
        Vector4(0.0f, 0.0f, -1.0f, 1.0f),
    };
    Vector4 vLightColors[2] =
    {
        Vector4(0.5f, 0.5f, 0.5f, 1.0f),
        Vector4(0.5f, 0.0f, 0.0f, 1.0f),
    };

    Matrix3 rotate;
    Vector4 vOutDir;
    rotate = Matrix3::rotationY(-2.0f * t);
    vLightDirs[1].setXYZ(rowMul (vLightDirs[1].getXYZ(), rotate));

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mLambertLitEffect.Enable();

    SetFloatArray(gWorld, gGlobals.World);
    SetFloatArray(gView, gGlobals.View);
    SetFloatArray(gProjection, gGlobals.Projection);
    SetFloatArray(vLightDirs[0], &gGlobals.vLightDir[0]);
    SetFloatArray(vLightDirs[1], &gGlobals.vLightDir[4]);
    SetFloatArray(vLightColors[0], &gGlobals.vLightColor[0]);
    SetFloatArray(vLightColors[1], &gGlobals.vLightColor[4]);

#if UBO
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(gGlobals), &gGlobals);
    mLambertLitEffect.SetUniformBlock(std::string("SharedConsts"), 0, ubo);
#else
    mLambertLitEffect.SetVec4(std::string("Globals"), GlobalsVec4Count, (float*)&gGlobals);
#endif 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)(sizeof(float)*3));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    mSolidColour.Link();
    mSolidColour.Enable();

    for(int m = 0; m < 2; m++)
    {
        Matrix4 light;
        Matrix4 lightScale;
        Vector4 vLightPos = vLightDirs[m] * 5.0f;
        light = Matrix4::translation(vLightPos.getXYZ());
        lightScale = Matrix4::scale(Vector3(2.0f, 2.0f, 2.0f));
        light = lightScale * light;

        SetFloatArray(light, gGlobals.World);
        SetFloatArray(vLightColors[m], &gGlobals.vOutputColor[0]);

#if UBO
        glBindBuffer(GL_UNIFORM_BUFFER, ubo2);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(gGlobals), &gGlobals);
        mSolidColour.SetUniformBlock(std::string("SharedConsts"), 1, ubo2);
#else
        mSolidColour.SetVec4(std::string("Globals"), GlobalsVec4Count, (float*)&gGlobals);
#endif
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   /*if (w <= h) {
      loadOrtho2Df (projectionMatrix, 0.0f, 30.0f, 0.0f, 30.0f * (GLfloat) h/(GLfloat) w);
   } else {
      loadOrtho2Df (projectionMatrix, 0.0f, 30.0f * (GLfloat) w/(GLfloat) h, 0.0f, 30.0f);
   }*/

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

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.125f, 0.3f, 1.0f);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    mLambertLitEffect.Create();
#if UBO
    mLambertLitEffect.AddCompileFlags(HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT);
    mLambertLitEffect.FromByteFile(std::string("shaders/LambertLitPS.o"));
    mLambertLitEffect.FromByteFile(std::string("shaders/LambertLitVS.o"));

#else
	mLambertLitEffect.FromByteFile(std::string("shaders/LambertLitDX9PS.o"));
    mLambertLitEffect.FromByteFile(std::string("shaders/LambertLitDX9VS.o"));
#endif
    
    mLambertLitEffect.Link();

    mSolidColour.Create();
#if UBO
    mSolidColour.AddCompileFlags(HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT);
    mSolidColour.FromByteFile(std::string("shaders/LambertLitSolidPS.o"));
    mSolidColour.FromByteFile(std::string("shaders/LambertLitVS.o"));
#else
    mSolidColour.FromByteFile(std::string("shaders/LambertLitDX9SolidPS.o"));
    mSolidColour.FromByteFile(std::string("shaders/LambertLitDX9VS.o"));
#endif
	mSolidColour.Link();

#if UBO
    mLambertLitEffect.CreateUniformBlock(std::string("SharedConsts"), ubo);
    mLambertLitEffect.SetUniformBlock(std::string("SharedConsts"), 0, ubo);

    mSolidColour.CreateUniformBlock(std::string("SharedConsts"), ubo2);
    mSolidColour.SetUniformBlock(std::string("SharedConsts"), 1, ubo2);
#endif

    gWorld = Matrix4::identity();

    Point3 Eye( 0.0f, 4.0f, -10.0f );
    Point3 At( 0.0f, 1.0f, 0.0f );
    Vector3 Up( 0.0f, 1.0f, 0.0f );

    gView = Matrix4::lookAt(Eye, At, Up);
    gProjection = Matrix4::perspective(3.14159f * 0.25f, WindowWidth / ( float )WindowHeight, 0.1f, 100.0f);


    uint32_t indices[] =
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
    };

    glGenBuffers(1, &gIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 36,
        indices, GL_STATIC_DRAW);


    SimpleVertex vertices[] =
    {
        { { -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { 1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },
        { { -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f } },

        { { -1.0f, -1.0f, -1.0f }, { 0.0f, -1.0f, 0.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 0.0f, -1.0f, 0.0f } },
        { { 1.0f, -1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },
        { { -1.0f, -1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f } },

        { { -1.0f, -1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -1.0f, -1.0f, -1.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -1.0f, 1.0f, -1.0f }, { -1.0f, 0.0f, 0.0f } },
        { { -1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f } },

        { { 1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 1.0f, 1.0f, -1.0f }, { 1.0f, 0.0f, 0.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f } },

        { { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, -1.0f } },
        { { 1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f, -1.0f } },
        { { 1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f, -1.0f } },
        { { -1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f, -1.0f } },

        { { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
        { { -1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
    };

    glGenBuffers(1, &gVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * 24,
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
