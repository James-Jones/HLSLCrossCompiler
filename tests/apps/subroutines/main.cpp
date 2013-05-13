
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <Shader.h>
#include <vectormath_aos.h>
#include "common/debug.h"
#include <model.h>
#include <itransform.h>

struct PostProcessVertex
{
    float Pos[3];
};

struct Vertex
{
    float Pos[3];
    float Normal[3];
	float TexCoord[3];
};

struct cbConstant
{
	float vLightDir[3];
	float padding;
};

const size_t ConstantVec4Count = sizeof(cbConstant)/sizeof(float)/4;

struct cbChangesEveryFrame
{
	float World[16];
	float View[16];
	float Projection[16];
	float Time;
	float padding[3];
};

const size_t ChangesEveryFrameVec4Count = sizeof(cbChangesEveryFrame)/sizeof(float)/4;

using namespace Vectormath::Aos;

int WindowWidth = 640;
int WindowHeight = 480;

class Demo : public ITransform
{
public:
	void Init();
	void Display(float t);
	void ResizeDisplay(int w, int h) {
	   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
        //D3D clip space (z = 0, +1) to GL (z = -1 to +1)
        gProjection = Matrix4::scale(Vector3(1, -1, 2));
        gProjection *= Matrix4::translation(Vector3(0, 0, -0.5));
		gProjection *= Matrix4::perspective(3.14159f * 0.25f, w / ( float )h, 0.1f, 5000.0f);

	}
	const Matrix4& GetWorldMatrix() const {
		return gWorld;
	}
	void SetWorldMatrix(Matrix4& newWorld) {
		gWorld = newWorld;
		UpdateShaderConstants();
	}

	void UpdateShaderConstants() {

		SetFloatArray(gWorld, gChangesEveryFrame.World);
		SetFloatArray(gView, gChangesEveryFrame.View);
		SetFloatArray(gProjection, gChangesEveryFrame.Projection);

		gChangesEveryFrame.Time = gTime;

		mEffect.SetVec4(std::string("cbChangesEveryFrame"), ChangesEveryFrameVec4Count, (float*)&gChangesEveryFrame);

		SetFloatArray(vLightDirs, &gConstant.vLightDir[0]);
		mEffect.SetVec4(std::string("cbConstant"), ConstantVec4Count, (float*)&gConstant);

        mEffect.SetTexture(std::string("g_txDiffuse"), 0);
	}
private:
	ShaderEffect mEffect;

	Matrix4 gWorld;
	Matrix4 gView;
	Matrix4 gProjection;
	GLuint gIndexBuffer;
	GLuint gVertexBuffer;

	cbConstant gConstant;
	cbChangesEveryFrame gChangesEveryFrame;

	Model gModel;

	Vector4 vLightDirs;
	float gTime;
};

Demo gDemo;

void Demo::Display(float t) {

    SubroutineLink slink;
    int subroutineIndex;
    const char* subroutines[] = {
        "cRedColour_Func0",
        "cGreenColour_Func0",
        "cBlueColour_Func0",
        "cMonochromeColour_Func0",
        "cFullColour_Func0",
    };

    gWorld = Matrix4::rotationY(180.0f * 3.14159f / 180.f);
    
    gWorld *= Matrix4::rotationX(-90.0f * 3.14159f / 180.f);

	gTime = t;

    vLightDirs = Vector4(-0.577f, 0.577f, -0.577f, 1.0f);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

    mEffect.Enable();

    subroutineIndex = (int)t;
    subroutineIndex = subroutineIndex % 5;

    slink.FunctionName = subroutines[subroutineIndex];
    slink.UniformName = "gAbstractColourChanger";

    mEffect.SetSubroutineUniforms(GL_FRAGMENT_SHADER, &slink, 1);

	gModel.Draw(*this);
}

void display(void)
{
    // Update our time
    static float t = 0.0f;

    static uint32_t dwTimeStart = 0;
    uint32_t dwTimeCur = GetTickCount();
    if( dwTimeStart == 0 )
        dwTimeStart = dwTimeCur;
    t = ( dwTimeCur - dwTimeStart ) / 1000.0f;

	gDemo.Display(t);

    glutSwapBuffers();
}

void reshape (int w, int h)
{
	gDemo.ResizeDisplay(w, h);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void Demo::Init() {

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.125f, 0.3f, 1.0f);

    mEffect.Create();
    mEffect.SetLanguage(LANG_400);
    mEffect.FromByteFile(std::string("shaders/SubroutinesPS.o"));
    mEffect.FromByteFile(std::string("shaders/SubroutinesVS.o"));
    mEffect.Link();

    gWorld = Matrix4::identity();

    Point3 Eye( 0.0f, 0.0f, -800 );

    Point3 At( 0.0f, 0.0f, 0.0f );

    Vector3 Up( 0.0f, 1.0f, 0.0f );

    gView = Matrix4::lookAt(Eye, At, Up);

    ResizeDisplay(WindowWidth, WindowHeight);

    gModel.Import3DFromFile("models/Tiny.x");
}

void Init(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glewInit();

    glutInitContextVersion (3, 2);
#ifdef _DEBUG
    glutInitContextFlags (GLUT_DEBUG);
#endif
    glutInitWindowSize (WindowWidth, WindowHeight); 
    glutInitWindowPosition(50, 50);
    glutCreateWindow (argv[0]);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc (keyboard);
    glutIdleFunc(display);

    glewInit();
#ifdef _DEBUG
    SetupOpenGLDebugCallback();
#endif

	gDemo.Init();
}

int main(int argc, char** argv)
{
    Init(argc, argv);
    glutMainLoop();

   return 0;
}
