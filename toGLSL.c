#include "tokens.h"
#include "structs.h"
#include "decode.h"
#include "stdlib.h"
#include "stdio.h"
#include "bstrlib.h"

bstring glsl;

void TranslateInstruction(const Instruction* psInst)
{
    switch(psInst->eOpcode)
    {
        case OPCODE_MOV:
        {
            if(psInst->asOperands[0].eType == OPERAND_TYPE_OUTPUT)
            {
            }
            bformata(glsl, "x%d = y%d;\n", psInst->asOperands[0].ui32RegisterNumber, psInst->asOperands[1].ui32RegisterNumber);
            break;
        }
        case OPCODE_MAD:
        {
            if(psInst->asOperands[0].eType == OPERAND_TYPE_OUTPUT)
            {
            }
            bformata(glsl, "x%d = y%d * z%d + w%d;\n", psInst->asOperands[0].ui32RegisterNumber,
                psInst->asOperands[1].ui32RegisterNumber,
                psInst->asOperands[2].ui32RegisterNumber,
                psInst->asOperands[3].ui32RegisterNumber);
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

	if(psShader->ui32MajorVersion == 5)
	{
        glsl = bfromcstralloc (1024, "#version 420\n");
	}
	else
	if(psShader->ui32MajorVersion == 4)
	{
        glsl = bfromcstralloc (1024, "#version 330\n");
	}

    bcatcstr(glsl, "void main()\n");
    bcatcstr(glsl, "{\n");

    for(i=0; i < ui32InstCount; ++i)
    {
        TranslateInstruction(psShader->psInst+i);
    }

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

    free(shader);
    shader = 0;
    tokens = 0;
}