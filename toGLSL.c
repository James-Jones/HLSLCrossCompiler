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
            bformata(glsl, "out vec4 %s;\n", psDecl->asOperands[0].pszSpecialName);

            bcatcstr(glsl, "#define ");
            TranslateOperand(&psDecl->asOperands[0]);
            bformata(glsl, " %s\n", psDecl->asOperands[0].pszSpecialName);
            break;
        }
        case OPCODE_DCL_INPUT:
        {
            bformata(glsl, "in vec4 Input%d;\n", psDecl->asOperands[0].ui32RegisterNumber);
            break;
        }
        case OPCODE_DCL_TEMPS:
        {
            uint32_t i = 0; 
            const uint32_t ui32NumTemps = psDecl->ui32NumTemps;

            for(i=0; i < ui32NumTemps; ++i)
            {
                 bformata(glsl, "vec4 Temp%d;\n", i);
            }

            break;
        }
        case OPCODE_DCL_RESOURCE:
        {
            switch(psDecl->eResourceDimension)
            {
                case RESOURCE_DIMENSION_BUFFER:
                {
                    bcatcstr(glsl, "uniform samplerBuffer ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE1D:
                {
                    bcatcstr(glsl, "uniform sampler1D ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2D:
                {
                    bcatcstr(glsl, "uniform sampler2D ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DMS:
                {
                    bcatcstr(glsl, "uniform sampler2DMS ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE3D:
                {
                    bcatcstr(glsl, "uniform sampler3D ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURECUBE:
                {
                    bcatcstr(glsl, "uniform samplerCube ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE1DARRAY:
                {
                    bcatcstr(glsl, "uniform sampler1DArray ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DARRAY:
                {
                    bcatcstr(glsl, "uniform sampler2DArray ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURE2DMSARRAY:
                {
                    bcatcstr(glsl, "uniform sampler3DArray ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
                case RESOURCE_DIMENSION_TEXTURECUBEARRAY:
                {
                    bcatcstr(glsl, "uniform samplerCuubeArray ");
                    TranslateOperand(&psDecl->asOperands[0]);
                    break;
                }
            }
            bcatcstr(glsl, ";\n");
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
            if(psOperand->iNumComponents == 1)
            {
                bformata(glsl, "%f",
                    psOperand->afImmediates[0]);
            }
            else
            if(psOperand->iNumComponents == 4)
            {
                bformata(glsl, "vec4(%f, %f, %f, %f)",
                    psOperand->afImmediates[0],
                    psOperand->afImmediates[1],
                    psOperand->afImmediates[2],
                    psOperand->afImmediates[3]);
            }
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
        case OPERAND_TYPE_TEMP:
        {
            bformata(glsl, "Temp%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_CONSTANT_BUFFER:
        {
            bformata(glsl, "Const%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_RESOURCE:
        {
            bformata(glsl, "Resource%d", psOperand->ui32RegisterNumber);
            break;
        }
        case OPERAND_TYPE_SAMPLER:
        {
            bformata(glsl, "Sampler%d", psOperand->ui32RegisterNumber);
            break;
        }
        default:
        {
            bformata(glsl, "%d %d", psOperand->eType, psOperand->ui32RegisterNumber);
            break;
        }
    }

    if(psOperand->iWriteMaskEnabled &&
       psOperand->iNumComponents == 4)
    {
    //Comonent Mask
    if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
    {
        bcatcstr(glsl, ".");
        if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_X)
        {
            bcatcstr(glsl, "x");
        }
        if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_Y)
        {
            bcatcstr(glsl, "y");
        }
        if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_Z)
        {
            bcatcstr(glsl, "z");
        }
        if(psOperand->ui32CompMask & OPERAND_4_COMPONENT_MASK_W)
        {
            bcatcstr(glsl, "w");
        }
    }
    else
    //Component Swizzle
    if(psOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
    {
        uint32_t i;

        bcatcstr(glsl, ".");

        for(i=0; i< 4; ++i)
        {
            if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_X)
            {
                bcatcstr(glsl, "x");
            }
            else
            if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_Y)
            {
                bcatcstr(glsl, "y");
            }
            else
            if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_Z)
            {
                bcatcstr(glsl, "z");
            }
            else
            if(psOperand->aui32Swizzle[i] == OPERAND_4_COMPONENT_W)
            {
                bcatcstr(glsl, "w");
            }
        }
    }

    //Component Select 1
    }
}

void TranslateInstruction(const Instruction* psInst)
{
    switch(psInst->eOpcode)
    {
        case OPCODE_MOV:
        {
            AddIndentation();
            bcatcstr(glsl, "//MOV\n");
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
            bcatcstr(glsl, "//MAD\n");
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
        case OPCODE_ADD:
        {
            AddIndentation();
            bcatcstr(glsl, "//ADD\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " + ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_MUL:
        {
            AddIndentation();
            bcatcstr(glsl, "//MUL\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " * ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_SINCOS:
        {
            AddIndentation();
            bcatcstr(glsl, "//SINCOS\n");
            if(psInst->asOperands[0].eType != OPERAND_TYPE_NULL)
            {
                AddIndentation();
                TranslateOperand(&psInst->asOperands[0]);//Dest sin
                bcatcstr(glsl, " = sin(");
                TranslateOperand(&psInst->asOperands[2]);//angle
                bcatcstr(glsl, ");\n");
            }

            if(psInst->asOperands[1].eType != OPERAND_TYPE_NULL)
            {
                AddIndentation();
                TranslateOperand(&psInst->asOperands[1]);//Dest cos
                bcatcstr(glsl, " = cos(");
                TranslateOperand(&psInst->asOperands[2]);//angle
                bcatcstr(glsl, ");\n");
            }
            break;
        }
        case OPCODE_DP4:
        {
            AddIndentation();
            bcatcstr(glsl, "//DP4\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = dot(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_NE:
        {
            //Scalar version. Use any() for vector with scalar 1
            AddIndentation();
            bcatcstr(glsl, "//NE\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = (");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " != ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ") ? 1 : 0;\n");
            break;
        }
        case OPCODE_MOVC:
        {
            //dest = (src0) ? src1 : src2;
            //Scalar version. Use any() for vector with scalar 1
            AddIndentation();
            bcatcstr(glsl, "//MOVC\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = (");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ") ? ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, " : ");
            TranslateOperand(&psInst->asOperands[3]);
            bcatcstr(glsl, ";\n");

                /*for each component in dest[.mask]
                    if the corresponding component in src0 (POS-swizzle)
                       has any bit set
                    {
                        copy this component (POS-swizzle) from src1 into dest
                    }
                    else
                    {
                        copy this component (POS-swizzle) from src2 into dest
                    }
                endfor*/
            break;
        }
		case OPCODE_LOG:
        {
            AddIndentation();
            bcatcstr(glsl, "//LOG\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = log(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_RSQ:
        {
            AddIndentation();
            bcatcstr(glsl, "//SQRT\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = inversesqrt(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_EXP:
        {
            AddIndentation();
            bcatcstr(glsl, "//EXP\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = exp(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_SQRT:
        {
            AddIndentation();
            bcatcstr(glsl, "//SQRT\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = sqrt(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_MAX:
        {
            AddIndentation();
            bcatcstr(glsl, "//MAX\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = max(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_MIN:
        {
            AddIndentation();
            bcatcstr(glsl, "//MIN\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = min(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_SAMPLE:
        {
            //dest, coords, tex, sampler
            AddIndentation();
            bcatcstr(glsl, "//SAMPLE\n");
            AddIndentation();//1=temp??
            TranslateOperand(&psInst->asOperands[1]);//??
            bcatcstr(glsl, " = texture2D(");

            TranslateOperand(&psInst->asOperands[3]);//resource
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);//in
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_RET:
		{
            AddIndentation();
            bcatcstr(glsl, "//RET\n");
            AddIndentation();
			bcatcstr(glsl, "return;\n");
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
}

void main(int argc, char** argv)
{
    FILE* shaderFile;
    FILE* outputFile;
    int length;
    int readLength;
    char* shader;
    uint32_t* tokens;
    Shader* psShader;
    char* glslcstr;

    if(argc < 2 || !(shaderFile = fopen(argv[1], "rb")))
    {
        printf("Bad args. Supply a valid shader path, optionaly followed by the output path\n");
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

        //Dump to console
        glslcstr = bstr2cstr(glsl, '\0');
        printf("%s\n", glslcstr);

        if(argc > 2)
        {
            //Dump to file
            outputFile = fopen(argv[2], "w");
            fprintf(outputFile, glslcstr);
            fclose(outputFile);
        }

        bcstrfree(glslcstr);
        bdestroy(glsl);

        free(psShader->psDecl);
        free(psShader->psInst);
        free(psShader);
    }

    free(shader);
    shader = 0;
    tokens = 0;
}