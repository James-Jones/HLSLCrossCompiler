#include "tokens.h"
#include "stdlib.h"
#include "stdio.h"

#define FOURCC(a, b, c, d) ((uint32_t)(uint8_t)(a) | ((uint32_t)(uint8_t)(b) << 8) | ((uint32_t)(uint8_t)(c) << 16) | ((uint32_t)(uint8_t)(d) << 24 ))
const uint32_t FOURCC_DXBC = FOURCC('D', 'X', 'B', 'C');
const uint32_t FOURCC_SHDR = FOURCC('S', 'H', 'D', 'R');
const uint32_t FOURCC_SHEX = FOURCC('S', 'H', 'E', 'X');

typedef struct DXBCContainerHeaderTAG
{
	unsigned fourcc;
	uint32_t unk[4];
	uint32_t one;
	uint32_t totalSize;
	uint32_t chunkCount;
} DXBCContainerHeader;

typedef struct DXBCChunkHeaderTAG
{
	unsigned fourcc;
	unsigned size;
} DXBCChunkHeader;

const uint32_t* DeocdeInstruction(const uint32_t* pui32Token)
{
    const uint32_t ui32TokenLength = DecodeInstructionLength(*pui32Token);
    const uint32_t bExtended = DecodeIsOpcodeExtended(*pui32Token);
    const OPCODE_TYPE opcode = DecodeOpcodeType(*pui32Token);
    switch (opcode)
    {
		case OPCODE_DCL_GLOBAL_FLAGS:
		{
			printf("dcl_globalFlags\n");
			break;
		}
		case OPCODE_DCL_INPUT:
		{
			printf("dcl_input.\n");
			break;
		}
		case OPCODE_DCL_OUTPUT_SIV:
		{
			printf("dcl_output_siv.\n");
			break;
		}
		case OPCODE_MOV:
		{
			printf("MOV.\n");
			break;
		}
		case OPCODE_RET:
		{
			printf("RET.\n");
			break;
		}
        default:
        {
			printf("Unkown opcode.\n");
            break;
        }
    }

    return pui32Token + ui32TokenLength;
}

void Decode(const uint32_t* pui32Tokens)
{
    const uint32_t* pui32CurrentToken = pui32Tokens;

    const uint32_t ui32MajorVersion = DecodeProgramMajorVersion(*pui32CurrentToken);
    const uint32_t ui32MinorVersion = DecodeProgramMinorVersion(*pui32CurrentToken);
    const SHADER_TYPE ui32ShaderType = DecodeShaderType(*pui32CurrentToken);
	uint32_t ui32ShaderLength;

    switch(ui32ShaderType)
    {
        case PIXEL_SHADER:
        {
            printf("It's a pixel shader.\nVersion %d dot %d.\n", ui32MajorVersion, ui32MinorVersion);
            break;
        }
        case VERTEX_SHADER:
        {
            printf("It's a vertex shader.\nVersion %d dot %d.\n", ui32MajorVersion, ui32MinorVersion);
            break;
        }
        case GEOMETRY_SHADER:
        {
            printf("It's a geometry shader.\nVersion %d dot %d.\n", ui32MajorVersion, ui32MinorVersion);
            break;
        }
        case HULL_SHADER:
        {
            printf("It's a hull shader.\nVersion %d dot %d\n", ui32MajorVersion, ui32MinorVersion);
            break;
        }
        case DOMAIN_SHADER:
        {
            printf("It's a domain shader.\nVersion %d dot %d.\n", ui32MajorVersion, ui32MinorVersion);
            break;
        }
        case COMPUTE_SHADER:
        {
            printf("It's a compute shader.\nVersion %d dot %d.\n", ui32MajorVersion, ui32MinorVersion);
            break;
        }
        default:
        {
            printf("Unknown shader type 0x%X.\n", ui32ShaderType);
            return;
        }
    }

    pui32CurrentToken++;

    ui32ShaderLength = *pui32CurrentToken;

    printf("It's %d dwords long.\n", ui32ShaderLength);

    pui32CurrentToken++;

    while (pui32CurrentToken < (pui32Tokens + ui32ShaderLength))
    {
        pui32CurrentToken = DeocdeInstruction(pui32CurrentToken);
    }

}

void DecodeDXBC(uint32_t* data)
{
	DXBCContainerHeader* header = (DXBCContainerHeader*)data;
	uint32_t i;
	uint32_t chunkCount;
	uint32_t* chunkOffsets;

	if(header->fourcc != FOURCC_DXBC)
	{
		printf("Bad fourcc\n");
		return;
	}

	chunkOffsets = (uint32_t*)(header + 1);

	chunkCount = header->chunkCount;

	for(i = 0; i < chunkCount; ++i)
	{
		uint32_t offset = chunkOffsets[i];

		DXBCChunkHeader* chunk = (DXBCChunkHeader*)((char*)data + offset);

		if(chunk->fourcc == FOURCC_SHDR ||
			chunk->fourcc == FOURCC_SHEX)
		{
			Decode((uint32_t*)(chunk + 1));
			printf("Success!\n");
			return;
		}
	}

	printf("Failed - No SHEX ro SHDR fourcc found.\n");
}

void main(int argc, char** argv)
{
    FILE* shaderFile;
    int length;
    int readLength;
    char* shader;
    uint32_t* tokens;

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

	DecodeDXBC(tokens);

    free(shader);
    shader = 0;
    tokens = 0;
}
