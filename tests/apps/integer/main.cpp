
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
	float vOutputColor[4];
	int ColorFactor[4];
};
const size_t GlobalsVec4Count = sizeof(Globals)/sizeof(float)/4;

using namespace Vectormath::Aos;

ShaderEffect mVertexShader;
ShaderEffect mSolidColour;
Matrix4 gWorld;
Matrix4 gView;
Matrix4 gProjection;
GLuint gIndexBuffer;
GLuint gVertexBuffer;
Globals gGlobals;

GLuint ubo;
GLuint feedbackBuffer;

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

	Vector4 color (0.1, 0.2, 0.3, 0.4);

    Matrix3 rotate;
    Vector4 vOutDir;
    rotate = Matrix3::rotationY(-2.0f * t);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_RASTERIZER_DISCARD);

    mVertexShader.Enable();

    SetFloatArray(gWorld, gGlobals.World);
    SetFloatArray(gView, gGlobals.View);
    SetFloatArray(gProjection, gGlobals.Projection);
	SetFloatArray(color, &gGlobals.vOutputColor[0]);

	gGlobals.ColorFactor[0] = 2;
	gGlobals.ColorFactor[1] = 3;
	gGlobals.ColorFactor[2] = 4;
	gGlobals.ColorFactor[3] = 5;

    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(gGlobals), &gGlobals);
    mVertexShader.SetUniformBlock(std::string("SharedConsts"), 0, ubo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex), (void*)(sizeof(float)*3));

	glBeginTransformFeedback(GL_POINTS);
    glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, 0);
	glEndTransformFeedback();

	glDisable(GL_RASTERIZER_DISCARD);

    float* capturedVaryings = (float*)glMapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, GL_READ_ONLY);

	printf("%.2f %.2f %.2f %.2f\n", capturedVaryings[0], capturedVaryings[1], capturedVaryings[2], capturedVaryings[3]);
	printf("%d\n", ((int*)capturedVaryings)[4]);

        /*if(capturedVaryings[i] != expectedProgramPointSize)
        {
            printf("FAILED %s: xfb point size %.2f instead of %.2f\n", desc, mappedPointSizes[i], expectedProgramPointSize);
        }*/
    glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);

    glutSwapBuffers();

	glutLeaveMainLoop();
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

glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

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

    mVertexShader.Create();
	mVertexShader.SetLanguage(LANG_400);
    mVertexShader.AddCompileFlags(HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT|HLSLCC_FLAG_INOUT_SEMANTIC_NAMES);
    mVertexShader.FromByteFile(std::string("shaders/IntegerVS.o"));
	const char* varyings [] = {"COLOR2", "FACTOR3"};
	mVertexShader.SetTransformFeedback(2, varyings);

    glGenBuffers(1, &feedbackBuffer);
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, feedbackBuffer);
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float)*4+sizeof(int)*4, NULL, GL_STATIC_DRAW);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, feedbackBuffer);

    mVertexShader.Link();

    mVertexShader.CreateUniformBlock(std::string("SharedConsts"), ubo);
    mVertexShader.SetUniformBlock(std::string("SharedConsts"), 0, ubo);

    gWorld = Matrix4::identity();

    Point3 Eye( 0.0f, 4.0f, -10.0f );
    Point3 At( 0.0f, 1.0f, 0.0f );
    Vector3 Up( 0.0f, 1.0f, 0.0f );

    gView = Matrix4::lookAt(Eye, At, Up);
    gProjection = Matrix4::perspective(3.14159f * 0.25f, WindowWidth / ( float )WindowHeight, 0.1f, 100.0f);


    uint32_t indices[] =
    {
        0,
    };

    glGenBuffers(1, &gIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 1,
        indices, GL_STATIC_DRAW);


    SimpleVertex vertices[] =
    {
        { { -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, 0.0f } },
    };

    glGenBuffers(1, &gVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SimpleVertex) * 1,
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
