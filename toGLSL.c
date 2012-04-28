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

const uint32_t* ProcessDCLTokens(const uint32_t* pui32Token)
{
	while(1)
	{
		const uint32_t ui32TokenLength = DecodeInstructionLength(*pui32Token);
		const uint32_t bExtended = DecodeIsOpcodeExtended(*pui32Token);
		const OPCODE_TYPE opcode = DecodeOpcodeType(*pui32Token);
		const OPERAND_INDEX_DIMENSION dim = DecodeOperandIndexDimension(*pui32Token);

		switch (opcode)
		{
			case OPCODE_DCL_RESOURCE:
			{
				break;
			}
			case OPCODE_DCL_CONSTANT_BUFFER:
			{
				break;
			}
			case OPCODE_DCL_SAMPLER:
			{
				break;
			}
			case OPCODE_DCL_INDEX_RANGE:
			{
				break;
			}
			case OPCODE_DCL_GS_OUTPUT_PRIMITIVE_TOPOLOGY:
			{
				break;
			}
			case OPCODE_DCL_GS_INPUT_PRIMITIVE:
			{
				break;
			}
			case OPCODE_DCL_MAX_OUTPUT_VERTEX_COUNT:
			{
				break;
			}
			case OPCODE_DCL_INPUT:
			{
				printf("in vec4 v0;\n");
				break;
			}
			case OPCODE_DCL_INPUT_SGV:
			{
				break;
			}
			case OPCODE_DCL_INPUT_SIV:
			{
				break;
			}
			case OPCODE_DCL_INPUT_PS:
			{
				break;
			}
			case OPCODE_DCL_INPUT_PS_SGV:
			{
				break;
			}
			case OPCODE_DCL_INPUT_PS_SIV:
			{
				break;
			}
			case OPCODE_DCL_OUTPUT:
			{
				break;
			}
			case OPCODE_DCL_OUTPUT_SGV:
			{
				break;
			}
			case OPCODE_DCL_OUTPUT_SIV:
			{
				//Use preprocessor to map output register
				//indices to system-value names
				printf("#define o0 gl_Position\n");
				break;
			}
			case OPCODE_DCL_TEMPS:
			{
				break;
			}
			case OPCODE_DCL_INDEXABLE_TEMP:
			{
				break;
			}
			case OPCODE_DCL_GLOBAL_FLAGS:
			{
				break;
			}
			default:
			{
				return pui32Token;
			}
		}

		pui32Token += ui32TokenLength;
	}
}

const void ProcessMOV(const uint32_t* pui32Token)
{
	printf("X = Y\n");
}

const uint32_t* DeocdeInstruction(const uint32_t* pui32Token)
{
    const uint32_t ui32TokenLength = DecodeInstructionLength(*pui32Token);
    const uint32_t bExtended = DecodeIsOpcodeExtended(*pui32Token);
    const OPCODE_TYPE opcode = DecodeOpcodeType(*pui32Token);
    switch (opcode)
    {
		case OPCODE_MOV:
		{
			//printf("MOV.\n");
			ProcessMOV(pui32Token);
			break;
		}
		case OPCODE_RET:
		{
			printf("return;\n");
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

	if(ui32MajorVersion == 5)
	{
		printf("#version 420\n");
	}
	else
	if(ui32MajorVersion == 4)
	{
		printf("#version 330\n");
	}

#if 0
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
#endif

    pui32CurrentToken++;

    ui32ShaderLength = *pui32CurrentToken;

    //printf("It's %d dwords long.\n", ui32ShaderLength);

    pui32CurrentToken++;

	pui32CurrentToken = ProcessDCLTokens(pui32CurrentToken);

	printf("void main()\n");
	printf("{\n");

    while (pui32CurrentToken < (pui32Tokens + ui32ShaderLength))
    {
        pui32CurrentToken = DeocdeInstruction(pui32CurrentToken);
    }

	printf("}\n");

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
			//printf("Success!\n");
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

