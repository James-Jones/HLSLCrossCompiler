
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string>
#include <toGLSL.h>
#include <Shader.h>
#include <vectormath_aos.h>
#include <debug.h>
#include <model.h>
#include <iostream>

using namespace Vectormath::Aos;

Matrix4 gWorld;
Matrix4 gView;
Matrix4 gProjection;
Model gModel;
ShaderEffect gExtrudeShader;

int WindowWidth = 640;
int WindowHeight = 480;

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

struct cbChangesEveryFrame
{
	float World[16];
	float View[16];
	float Projection[16];
	float Time;
	float padding[3];
};

struct cbUserChanges
{
    float Explode;
	float padding[3];
};

cbConstant gConstant;
cbChangesEveryFrame gChangesEveryFrame;
cbUserChanges gUserChanges;

GLuint gConstantUBO;
GLuint gChangesEveryFrameUBO;
GLuint gUserChangesUBO;

void UpdateConstantUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, gConstantUBO);
	//cbConstant* ptr = static_cast<cbConstant*>(glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(cbConstant), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
	cbConstant* ptr = static_cast<cbConstant*>(glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY));
	*ptr = gConstant;
	glUnmapBuffer(GL_UNIFORM_BUFFER);
	
}
void UpdateChangesEveryFrameUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, gChangesEveryFrameUBO);
	cbChangesEveryFrame* ptr = static_cast<cbChangesEveryFrame*>(glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(cbChangesEveryFrame), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
	*ptr = gChangesEveryFrame;
	glUnmapBuffer(GL_UNIFORM_BUFFER);
}
void UpdateUserChangesUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, gUserChangesUBO);
	cbUserChanges* ptr = static_cast<cbUserChanges*>(glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(cbUserChanges), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
	*ptr = gUserChanges;
	glUnmapBuffer(GL_UNIFORM_BUFFER);
}

void SetFloatArray(Vector4& vec, float* farray)
{
    farray[0] = vec.getX();
    farray[1] = vec.getY();
    farray[2] = vec.getZ();
    farray[3] = vec.getW();
}
void SetFloatArray(Matrix4& matrix, float* farray)
{
    for(int row = 0; row < 4; row++)
    {
        Vector4 r = matrix.getRow(row);
        SetFloatArray(r, &farray[row*4]);
    }
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gExtrudeShader.Enable();

    SetFloatArray(gWorld, gChangesEveryFrame.World);
    SetFloatArray(gView, gChangesEveryFrame.View);
    SetFloatArray(gProjection, gChangesEveryFrame.Projection);

	UpdateConstantUBO();
	UpdateChangesEveryFrameUBO();
	UpdateUserChangesUBO();

	std::string cbConstantString("cbConstant");
	std::string cbChangesEveryFrameString("cbChangesEveryFrame");
	std::string cbUserChangesString("cbUserChanges");

	gExtrudeShader.SetUniformBlock(cbConstantString, 0, gConstantUBO);
	gExtrudeShader.SetUniformBlock(cbChangesEveryFrameString, 1, gChangesEveryFrameUBO);
	gExtrudeShader.SetUniformBlock(cbUserChangesString, 2, gUserChangesUBO);

	gModel.Draw();

    glutSwapBuffers();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    gProjection = Matrix4::perspective(3.14159f * 0.25f, w / ( float )h, 0.1f, 5000.0f);
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

    glutInitContextVersion (3, 2);
#ifdef _DEBUG
    glutInitContextFlags (GLUT_DEBUG);
#endif
    glutInitWindowSize (WindowWidth, WindowHeight); 
    glutInitWindowPosition (0, 100);
    glutCreateWindow (argv[0]);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc (keyboard);
    glutIdleFunc(display);

    glewInit();
#ifdef _DEBUG
    SetupOpenGLDebugCallback();
#endif

	std::cout << "Loading model" <<std::endl;
	gModel.Import3DFromFile("../models/tiny.x");

	gConstant.vLightDir[0] = -0.577;
	gConstant.vLightDir[1] = 0.577;
	gConstant.vLightDir[2] = -0.577;

	gUserChanges.Explode = 0.0f;

    gExtrudeShader.Create();

	gExtrudeShader.SetCompileFlags(HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT | HLSLCC_FLAG_GS_ENABLED);

	std::cout << "Compiling shaders" <<std::endl;
    gExtrudeShader.FromVertexByteFile(std::string("../shaders/ExtrudeVS.o"));
    gExtrudeShader.FromPixelByteFile(std::string("../shaders/ExtrudePS.o"));
	gExtrudeShader.FromGeometryByteFile(std::string("../shaders/ExtrudeGS.o"));

    glGenBuffers(1, &gConstantUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, gConstantUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(cbConstant),
                    NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &gChangesEveryFrameUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, gChangesEveryFrameUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(cbChangesEveryFrame),
                    NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &gUserChangesUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, gUserChangesUBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(cbUserChanges),
                    NULL, GL_DYNAMIC_DRAW);

	gExtrudeShader.CreateUniformBlock(std::string("cbConstant"), gConstantUBO);
	gExtrudeShader.CreateUniformBlock(std::string("cbChangesEveryFrame"), gChangesEveryFrameUBO);
	gExtrudeShader.CreateUniformBlock(std::string("cbUserChanges"), gUserChangesUBO);

    gWorld = Matrix4::identity();

    Point3 Eye( 0.0f, 0.0f, -800.0f );
    Point3 At( 0.0f, 0.0f, 0.0f );
    Vector3 Up( 0.0f, 1.0f, 0.0f );

    gView = Matrix4::lookAt(Eye, At, Up);
    gProjection = Matrix4::perspective(3.14159f * 0.25f, WindowWidth / ( float )WindowHeight, 0.1f, 5000.0f);


    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.125f, 0.3f, 1.0f);

	std::cout << "Finished init" <<std::endl;
}

int main(int argc, char** argv)
{
    Init(argc, argv);
    glutMainLoop();

   return 0;
}
