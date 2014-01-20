
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

typedef struct
{
    char* vertexFile;
	char* fragmentFile;
	char* computeFile;
	char* postprocessFile;
} Options;

void InitOptions(Options* psOptions)
{
    psOptions->vertexFile = 0;
	psOptions->fragmentFile = 0;
    psOptions->computeFile = 0;
    psOptions->postprocessFile = 0;
}
int GetOptions(int argc, char** argv, Options* psOptions)
{
	int i;
    int fullShaderChain = -1;
    int hashOut = 0;

	InitOptions(psOptions);

	for(i=1; i<argc; i++)
	{
		char *option;

		option = strstr(argv[i],"-vertex=");
		if(option != NULL) 
        {
			psOptions->vertexFile = option + strlen("-vertex=");
		}
		option = strstr(argv[i],"-fragment=");
		if(option != NULL) 
        {
			psOptions->fragmentFile = option + strlen("-fragment=");
		}
		option = strstr(argv[i],"-compute=");
		if(option != NULL) 
        {
			psOptions->computeFile = option + strlen("-compute=");
		}
		option = strstr(argv[i],"-postprocess=");
		if(option != NULL) 
        {
			psOptions->postprocessFile = option + strlen("-postprocess=");
		}
	}

	return 1;
}

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
	void Init(const Options* options);
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

		mEffect.SetVec4(std::string("cbChangesEveryFrameVS.World"), 4, gChangesEveryFrame.World);
		mEffect.SetVec4(std::string("cbChangesEveryFrameVS.View"), 4, gChangesEveryFrame.View);
		mEffect.SetVec4(std::string("cbChangesEveryFrameVS.Projection"), 4, gChangesEveryFrame.Projection);
		mEffect.SetFloat(std::string("cbChangesEveryFrameVS.Time"), 1, &gChangesEveryFrame.Time);

		SetFloatArray(vLightDirs, &gConstant.vLightDir[0]);
		mEffect.SetVec4(std::string("cbConstantPS.vLightDir"), 1, &gConstant.vLightDir[0]);

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

	GLuint mColTex;
	GLuint mDepthTex;
	GLuint mFramebuffer;

    bool mPostFXEnabled;
    ShaderEffect mPostProcessEffect;
    GLuint mPostFXIndexBuffer;
    GLuint mPostFXVertexBuffer;
    GLuint mPostFXVAO;

	bool mComputeEnabled;
	ShaderEffect mCompute;
};

Demo gDemo;

void Demo::Display(float t) {

	if(mComputeEnabled)
	{
		mCompute.Enable();
		mCompute.SetFloat(std::string("GlobalsCS.Time"), 1, &gChangesEveryFrame.Time);
		glDispatchCompute(32, 32, 1);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    gWorld = Matrix4::rotationY(180.0f * 3.14159f / 180.f);
    
    gWorld *= Matrix4::rotationX(-90.0f * 3.14159f / 180.f);

	gTime = t;

    vLightDirs = Vector4(-0.577f, 0.577f, -0.577f, 1.0f);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

    mEffect.Enable();

	gModel.Draw(*this);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    if(mPostFXEnabled)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glDisable(GL_DEPTH_TEST);

        mPostProcessEffect.Enable();
        //Make the colour and depth buffers available to shaders.
        glBindTexture(GL_TEXTURE_2D, mColTex);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        mPostProcessEffect.SetTexture("g_txColourBuffer", 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mDepthTex);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glActiveTexture(GL_TEXTURE0);
        mPostProcessEffect.SetTexture("g_txDepthBuffer", 1);

        //Draw post processing quad.
        glBindVertexArray(mPostFXVAO);
        glEnableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mPostFXIndexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, mPostFXVertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(PostProcessVertex), 0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    else
    {
	    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebuffer);
	    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, WindowWidth, WindowHeight,
						        0, 0, WindowWidth, WindowHeight,
						        GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
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

void Demo::Init(const Options* options) {

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

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.125f, 0.3f, 1.0f);

    mEffect.Create();
    mEffect.FromByteFile(std::string(options->fragmentFile));
    mEffect.FromByteFile(std::string(options->vertexFile));
    mEffect.Link();

    gWorld = Matrix4::identity();

    Point3 Eye( 0.0f, 0.0f, -800 );

    Point3 At( 0.0f, 0.0f, 0.0f );

    Vector3 Up( 0.0f, 1.0f, 0.0f );

    gView = Matrix4::lookAt(Eye, At, Up);

    ResizeDisplay(WindowWidth, WindowHeight);

    gModel.Import3DFromFile("models/Tiny.x");

    mPostFXEnabled = false;

    if(options->postprocessFile)
    {
        mPostFXEnabled = true;

        mPostProcessEffect.Create();
        mPostProcessEffect.FromByteFile(std::string(options->postprocessFile));
        mPostProcessEffect.FromByteFile(std::string("shaders/generic/templatePostFXVS.o"));
        mPostProcessEffect.Link();

        glGenVertexArrays(1, &mPostFXVAO);
        glBindVertexArray(mPostFXVAO);

        //Vertex setup for post-process quad
        uint32_t indices[] =
        {
            1, 0, 3,
            2, 3, 0
        };

        glGenBuffers(1, &mPostFXIndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mPostFXIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6,
            indices, GL_STATIC_DRAW);

        PostProcessVertex vertices[] =
        {
            {-1, -1, 0},
            {1, -1, 0},
            {-1, 1, 0},
            {1,  1, 0}
        };

        glGenBuffers(1, &mPostFXVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, mPostFXVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(PostProcessVertex) * 4,
            vertices, GL_STATIC_DRAW);
    }

	mComputeEnabled = false;
	if(options->computeFile)
	{
        mComputeEnabled = true;

        mCompute.Create();
		mCompute.SetLanguage(LANG_430);
        mCompute.FromByteFile(std::string(options->computeFile));
        mCompute.Link();
		gModel.GetMaterial().BindForLoadStore(GL_WRITE_ONLY);
	}
}

void Init(int argc, char** argv)
{
	Options options;

	printf("arguments: -vertex=Path -fragment=Path [-postposcess=Path -compute=Path]\n");
	printf("compute modifies texture used by fragment shader\n");
	GetOptions(argc, argv, &options);

	if(options.vertexFile == 0 || options.fragmentFile == 0)
	{
		printf("Missing vertex and/or fragment shader\n");
		exit(0);
	}

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

	gDemo.Init(&options);
}

int main(int argc, char** argv)
{
    Init(argc, argv);
    glutMainLoop();

   return 0;
}
