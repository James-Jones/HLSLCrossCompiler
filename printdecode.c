#include "tokens.h"
#include "structs.h"
#include "printdecode.h"
#include "decode.h"
#include "stdlib.h"
#include "stdio.h"

void PrintDecode(const Shader* psShader)
{
    switch(psShader->eShaderType)
    {
        case PIXEL_SHADER:
        {
            printf("It's a pixel shader.\nVersion %d dot %d.\n", psShader->ui32MajorVersion, psShader->ui32MinorVersion);
            break;
        }
        case VERTEX_SHADER:
        {
            printf("It's a vertex shader.\nVersion %d dot %d.\n", psShader->ui32MajorVersion, psShader->ui32MinorVersion);
            break;
        }
        case GEOMETRY_SHADER:
        {
            printf("It's a geometry shader.\nVersion %d dot %d.\n", psShader->ui32MajorVersion, psShader->ui32MinorVersion);
            break;
        }
        case HULL_SHADER:
        {
            printf("It's a hull shader.\nVersion %d dot %d\n", psShader->ui32MajorVersion, psShader->ui32MinorVersion);
            break;
        }
        case DOMAIN_SHADER:
        {
            printf("It's a domain shader.\nVersion %d dot %d.\n", psShader->ui32MajorVersion, psShader->ui32MinorVersion);
            break;
        }
        case COMPUTE_SHADER:
        {
            printf("It's a compute shader.\nVersion %d dot %d.\n", psShader->ui32MajorVersion, psShader->ui32MinorVersion);
            break;
        }
        default:
        {
            printf("Unknown shader type 0x%X.\n", psShader->eShaderType);
            return;
        }
    }

    printf("It's %d dwords long.\n", psShader->ui32ShaderLength);

    /*while (pui32CurrentToken < (pui32Tokens + ui32ShaderLength))
    {
        pui32CurrentToken = PrintDeocdeInstruction(psShader);
    }*/

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
        PrintDecode(psShader);
    }

    free(psShader->psDecl);
    free(psShader->psInst);
    free(psShader);
    free(shader);
    shader = 0;
    tokens = 0;
}
