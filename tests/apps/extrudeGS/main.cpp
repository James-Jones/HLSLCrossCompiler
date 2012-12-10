
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
#include <model.h>
#include <itransform.h>

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

struct cbUserChanges
{
    float Explode;
	float padding[3];
};

const size_t UserChangesVec4Count = sizeof(cbUserChanges)/sizeof(float)/4;

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
		gProjection = Matrix4::perspective(3.14159f * 0.25f, w / ( float )h, 0.1f, 100.0f);
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
		//gTime = gChangesEveryFrame.Time;
		gChangesEveryFrame.Time = gTime;
		mExtrudeEffect.SetVec4(std::string("cbChangesEveryFrame"), ChangesEveryFrameVec4Count, (float*)&gChangesEveryFrame);

		SetFloatArray(vLightDirs, &gConstant.vLightDir[0]);
		mExtrudeEffect.SetVec4(std::string("cbConstant"), ConstantVec4Count, (float*)&gConstant);

		//gExplode = gUserChanges.Explode;
		gUserChanges.Explode = gExplode;
		mExtrudeEffect.SetVec4(std::string("cbUserChanges"), UserChangesVec4Count, (float*)&gUserChanges);

        mExtrudeEffect.SetTexture(std::string("g_txDiffuse"), 0);
	}
private:
	ShaderEffect mExtrudeEffect;
	Matrix4 gWorld;
	Matrix4 gView;
	Matrix4 gProjection;
	GLuint gIndexBuffer;
	GLuint gVertexBuffer;

	cbConstant gConstant;
	cbChangesEveryFrame gChangesEveryFrame;
	cbUserChanges gUserChanges;

	Model gModel;

	Vector4 vLightDirs;
	float gExplode;
	float gTime;

	GLuint mColTex;
	GLuint mDepthTex;
	GLuint mFramebuffer;
};

Demo gDemo;

void Demo::Display(float t) {

	glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
	gWorld = Matrix4::rotationY(t);

	gTime = t;
	gExplode = 0.001 * t;

    vLightDirs = Vector4(-0.577f, 0.577f, -0.577f, 1.0f);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

    mExtrudeEffect.Enable();

	gModel.Draw(*this);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glBlitFramebuffer(0, 0, WindowWidth, WindowHeight,
						 0, 0, WindowWidth, WindowHeight,
						 GL_COLOR_BUFFER_BIT, GL_NEAREST);
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

	glGenTextures(1, &mColTex);
	glBindTexture(GL_TEXTURE_2D, mColTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WindowWidth, WindowHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glGenTextures(1, &mDepthTex);
	glBindTexture(GL_TEXTURE_2D, mDepthTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, WindowWidth, WindowHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);

	glGenFramebuffers(1, &mFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTex, 0);

	ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.125f, 0.3f, 1.0f);

    mExtrudeEffect.Create();
	mExtrudeEffect.SetCompileFlags(HLSLCC_FLAG_GS_ENABLED);
    mExtrudeEffect.FromVertexByteFile(std::string("../shaders/ExtrudeVS.o"));
    mExtrudeEffect.FromPixelByteFile(std::string("../shaders/ExtrudePS.o"));
	mExtrudeEffect.FromGeometryByteFile(std::string("../shaders/ExtrudeGS.o"));

    gWorld = Matrix4::identity();

	Point3 Eye( 0.0f, 0.0f, 3.0f );

	Point3 At( 0.0f, 0.0f, -5.0f );
    Vector3 Up( 0.0f, 1.0f, 0.0f );

    gView = Matrix4::lookAt(Eye, At, Up);
    gProjection = Matrix4::perspective(3.14159f * 0.25f, WindowWidth / ( float )WindowHeight, 0.1f, 5000.0f);

	gModel.Import3DFromFile("../models/Tiny.x");
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
