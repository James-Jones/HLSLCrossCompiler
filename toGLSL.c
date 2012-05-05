#include "tokens.h"
#include "structs.h"
#include "decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "bstrlib.h"

bstring glsl;
int indent;

void TranslateOperand(const Operand* psOperand);

void AddIndentation()
{
    int i;
    for(i=0; i < indent; ++i)
    {
        bcatcstr(glsl, "    ");
    }
}

void TranslateDeclaration(const Declaration* psDecl)
{
    switch(psDecl->eOpcode)
    {
        case OPCODE_DCL_OUTPUT_SIV:
        {
            bformata(glsl, "vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

            bcatcstr(glsl, "#define ");
            TranslateOperand(&psDecl->asOperands[0]);
            bformata(glsl, " %s\n", psDecl->asOperands[0].pszSpecialName);
            break;
        }
        default:
        {
            break;
        }
    }
}

void TranslateOperand(const Operand* psOperand)
{
    switch(psOperand->eType)
    {
        case OPERAND_TYPE_IMMEDIATE32:
        {
            bformata(glsl, "vec4(%f, %f, %f, %f)",
                psOperand->afImmediates[0],
                psOperand->afImmediates[1],
                psOperand->afImmediates[2],
                psOperand->afImmediates[3]);
            break;
        }
        case OPERAND_TYPE_INPUT:
        {
            bformata(glsl, "Input%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_OUTPUT:
        {
            bformata(glsl, "Output%d", psOperand->ui32RegisterNumber);
            break;
        }
        default:
        {
            bformata(glsl, "%d %d", psOperand->eType, psOperand->ui32RegisterNumber);
            break;
        }
    }
}

void TranslateInstruction(const Instruction* psInst)
{
    switch(psInst->eOpcode)
    {
        case OPCODE_MOV:
        {
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_MAD:
        {
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " * ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, " + ");
            TranslateOperand(&psInst->asOperands[3]);
            bcatcstr(glsl, ";\n");
            break;
        }
        default:
        {
            break;
        }
    }
}

void TranslateToGLSL(const Shader* psShader)
{
    char* glslcstr;
    uint32_t i;
    const uint32_t ui32InstCount = psShader->ui32InstCount;
    const uint32_t ui32DeclCount = psShader->ui32DeclCount;

    indent = 0;

	if(psShader->ui32MajorVersion == 5)
	{
        glsl = bfromcstralloc (1024, "#version 420\n");
	}
	else
	if(psShader->ui32MajorVersion == 4)
	{
        glsl = bfromcstralloc (1024, "#version 330\n");
	}

    for(i=0; i < ui32DeclCount; ++i)
    {
        TranslateDeclaration(psShader->psDecl+i);
    }

    bcatcstr(glsl, "void main()\n");
    bcatcstr(glsl, "{\n");

    indent++;

    for(i=0; i < ui32InstCount; ++i)
    {
        TranslateInstruction(psShader->psInst+i);
    }

    indent--;

    bcatcstr(glsl, "}\n");

    //Dump to console
    glslcstr = bstr2cstr(glsl, '\0');
    printf("%s\n", glslcstr);
    bcstrfree(glslcstr);


    bdestroy(glsl);
}

void main(int argc, char** argv)
{
    FILE* shaderFile;
    int length;
    int readLength;
    char* shader;
    uint32_t* tokens;
    Shader* psShader;

    if(argc != 2 || !(shaderFile = fopen(argv[1], "rb")))
    {
        printf("Bad args. Supply a valid shader path\n");
        return;
    }

    fseek(shaderFile, 0, SEEK_END);
    length = ftell(shaderFile);
    fseek(shaderFile, 0, SEEK_SET);

    shader = (char*)malloc(length+1);

    readLength = fread(shader, 1, length, shaderFile);

    fclose(shaderFile);
    shaderFile = 0;

    shader[readLength] = '\0';

    tokens = (uint32_t*)shader;

    psShader = DecodeDXBC(tokens);

	if(psShader)
    {
        TranslateToGLSL(psShader);
    }

    free(psShader->psDecl);
    free(psShader->psInst);
    free(psShader);
    free(shader);
    shader = 0;
    tokens = 0;
}