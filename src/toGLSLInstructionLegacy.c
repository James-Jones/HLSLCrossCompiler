#include "internal_includes/toGLSLInstruction.h"
#include "internal_includes/toGLSLOperand.h"
#include "internal_includes/languages.h"
#include "bstrlib.h"
#include "stdio.h"
#include "internal_includes/debug.h"

extern void AddIndentation(HLSLCrossCompilerContext* psContext);

typedef enum
{
    CMP_EQ,
    CMP_LT,
    CMP_GE,
    CMP_NE,
} ComparisonType;

static void AddComparision(HLSLCrossCompilerContext* psContext, Instruction* psInst, ComparisonType eType,
						   uint32_t typeFlag)
{
    bstring glsl = *psContext->currentGLSLString;
    const uint32_t destElemCount = GetNumSwizzleElements(&psInst->asOperands[0]);
    const uint32_t s0ElemCount = GetNumSwizzleElements(&psInst->asOperands[1]);
    const uint32_t s1ElemCount = GetNumSwizzleElements(&psInst->asOperands[2]);

	SHADER_VARIABLE_TYPE eDestType = GetOperandDataType(psContext, &psInst->asOperands[0]);

    uint32_t minElemCount = destElemCount < s0ElemCount ? destElemCount : s0ElemCount;

    minElemCount = s1ElemCount < minElemCount ? s1ElemCount : minElemCount;

    if(destElemCount > 1)
    {
        const char* glslOpcode [] = {
            "equal",
            "lessThan",
            "greaterThanEqual",
            "notEqual",
        };
		char* constructor = "vec";

		if(typeFlag & TO_FLAG_INTEGER)
		{
			constructor = "ivec";
		}
		else if(typeFlag & TO_FLAG_UNSIGNED_INTEGER)
		{
			constructor = "uvec";
		}

        //Component-wise compare
        AddIndentation(psContext);
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
		if(eDestType == SVT_UINT)
		{
			bformata(glsl, " = uvec%d(%s(%s4(", minElemCount, glslOpcode[eType], constructor);
		}
		else
		{
			bformata(glsl, " = ivec%d(%s(%s4(", minElemCount, glslOpcode[eType], constructor);
		}
        TranslateOperand(psContext, &psInst->asOperands[1], typeFlag);
        bcatcstr(glsl, ")");
        AddSwizzleUsingElementCount(psContext, minElemCount);
        bformata(glsl, ", %s4(", constructor);
        TranslateOperand(psContext, &psInst->asOperands[2], typeFlag);
        bcatcstr(glsl, ")");
        AddSwizzleUsingElementCount(psContext, minElemCount);
    }
    else
    {
        const char* glslOpcode [] = {
            "==",
            "<",
            ">=",
            "!=",
        };

        //Scalar compare
        AddIndentation(psContext);
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
        bcatcstr(glsl, " = ((");

        TranslateOperand(psContext, &psInst->asOperands[1], typeFlag);
        bcatcstr(glsl, ")");
        if(s0ElemCount > minElemCount)
            AddSwizzleUsingElementCount(psContext, minElemCount);

        bformata(glsl, "%s (", glslOpcode[eType]);
        TranslateOperand(psContext, &psInst->asOperands[2], typeFlag);
        bcatcstr(glsl, ")");
        if(s1ElemCount > minElemCount)
            AddSwizzleUsingElementCount(psContext, minElemCount);
		bcatcstr(glsl, ") ? 1.0 : 0.0;\n");
    }
}

static
void CallBinaryOp(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1, uint32_t dataType)
{
    bstring glsl = *psContext->currentGLSLString;
	uint32_t src1SwizCount = GetNumSwizzleElements(&psInst->asOperands[src1]);
	uint32_t src0SwizCount = GetNumSwizzleElements(&psInst->asOperands[src0]);
	uint32_t dstSwizCount = GetNumSwizzleElements(&psInst->asOperands[dest]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION|dataType);
		bcatcstr(glsl, " = ");

		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE|dataType);

		bformata(glsl, " %s ", name);

		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE|dataType);
		bcatcstr(glsl, ";\n");
	}
	else
	{
        //Upconvert the inputs to vec4 then apply the dest swizzle.
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION|dataType);
		if(dataType == TO_FLAG_UNSIGNED_INTEGER)
		{
			bcatcstr(glsl, " = uvec4(");
		}
		else if(dataType == TO_FLAG_INTEGER)
		{
			bcatcstr(glsl, " = ivec4(");
		}
		else
		{
			bcatcstr(glsl, " = vec4(");
		}
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE|dataType);

		bformata(glsl, " %s ", name);

		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE|dataType);
		bcatcstr(glsl, ")");
		//Limit src swizzles based on dest swizzle
		//e.g. given hlsl asm: add r0.xy, v0.xyxx, l(0.100000, 0.000000, 0.000000, 0.000000)
		//the two sources must become vec2
		//Temp0.xy = Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000);
		//becomes
		//Temp0.xy = vec4(Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000)).xy;
		
        TranslateOperandSwizzle(psContext, &psInst->asOperands[dest]);
		bcatcstr(glsl, ";\n");
	}
}

static
void CallTernaryOp(HLSLCrossCompilerContext* psContext, const char* op1, const char* op2, Instruction* psInst, 
 int dest, int src0, int src1, int src2, uint32_t dataType)
{
    bstring glsl = *psContext->currentGLSLString;
	uint32_t src2SwizCount = GetNumSwizzleElements(&psInst->asOperands[src2]);
	uint32_t src1SwizCount = GetNumSwizzleElements(&psInst->asOperands[src1]);
	uint32_t src0SwizCount = GetNumSwizzleElements(&psInst->asOperands[src0]);
	uint32_t dstSwizCount = GetNumSwizzleElements(&psInst->asOperands[dest]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == src2SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION|dataType);
		bcatcstr(glsl, " = ");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE|dataType);
		bformata(glsl, " %s ", op1);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE|dataType);
		bformata(glsl, " %s ", op2);
		TranslateOperand(psContext, &psInst->asOperands[src2], TO_FLAG_NONE|dataType);
		bcatcstr(glsl, ";\n");
	}
	else
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION|dataType);
		if(dataType == TO_FLAG_UNSIGNED_INTEGER)
		{
			bcatcstr(glsl, " = uvec4(");
		}
		else if(dataType == TO_FLAG_INTEGER)
		{
			bcatcstr(glsl, " = ivec4(");
		}
		else
		{
			bcatcstr(glsl, " = vec4(");
		}
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE|dataType);
		bformata(glsl, " %s ", op1);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE|dataType);
		bformata(glsl, " %s ", op2);
		TranslateOperand(psContext, &psInst->asOperands[src2], TO_FLAG_NONE|dataType);
		bcatcstr(glsl, ")");
		//Limit src swizzles based on dest swizzle
		//e.g. given hlsl asm: add r0.xy, v0.xyxx, l(0.100000, 0.000000, 0.000000, 0.000000)
		//the two sources must become vec2
		//Temp0.xy = Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000);
		//becomes
		//Temp0.xy = vec4(Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000)).xy;
		TranslateOperandSwizzle(psContext, &psInst->asOperands[dest]);
		bcatcstr(glsl, ";\n");
	}
}

static
void CallHelper3(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1, int src2)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);

	bcatcstr(glsl, " = vec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_DESTINATION);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src2], TO_FLAG_NONE);
    bcatcstr(glsl, "))");
    TranslateOperandSwizzle(psContext, &psInst->asOperands[dest]);
    bcatcstr(glsl, ";\n");
}

void CallHelper2(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);

	bcatcstr(glsl, " = vec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE);
    bcatcstr(glsl, "))");
    TranslateOperandSwizzle(psContext, &psInst->asOperands[dest]);
    bcatcstr(glsl, ";\n");
}

static
void CallHelper2Int(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);

	bcatcstr(glsl, " = ivec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(int(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_INTEGER);
    bcatcstr(glsl, "), int(");
    TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_INTEGER);
    bcatcstr(glsl, ")))");
    TranslateOperandSwizzle(psContext, &psInst->asOperands[dest]);
    bcatcstr(glsl, ";\n");
}

static
void CallHelper2UInt(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);

	bcatcstr(glsl, " = ivec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(int(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_UNSIGNED_INTEGER);
    bcatcstr(glsl, "), int(");
    TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_UNSIGNED_INTEGER);
    bcatcstr(glsl, ")))");
    TranslateOperandSwizzle(psContext, &psInst->asOperands[dest]);
    bcatcstr(glsl, ";\n");
}

static
void CallHelper1(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0)
{
    bstring glsl = *psContext->currentGLSLString;
	SHADER_VARIABLE_TYPE eDestDataType = GetOperandDataType(psContext, &psInst->asOperands[dest]);

    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);

	switch(eDestDataType)
	{
		case SVT_INT:
		{
			bcatcstr(glsl, " = ivec4(");
			break;
		}
		case SVT_UINT:
		{
			bcatcstr(glsl, " = uvec4(");
			break;
		}
		case SVT_FLOAT:
		default:
		{
			bcatcstr(glsl, " = vec4(");
			break;
		}
	}

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
    bcatcstr(glsl, "))");
    TranslateOperandSwizzle(psContext, &psInst->asOperands[dest]);
    bcatcstr(glsl, ";\n");
}


//Make sure the texture coordinate swizzle is appropriate for the texture type.
//i.e. vecX for X-dimension texture.
static void MaskOutTexCoordComponents(const RESOURCE_DIMENSION eResDim, Operand* psTexCoordOperand)
{
    switch(eResDim)
    {
        case RESOURCE_DIMENSION_TEXTURE1D:
        {
            //Vec1 texcoord. Mask out the other components.
            psTexCoordOperand->aui32Swizzle[1] = 0xFFFFFFFF;
            psTexCoordOperand->aui32Swizzle[2] = 0xFFFFFFFF;
            psTexCoordOperand->aui32Swizzle[3] = 0xFFFFFFFF;
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE2D:
        {
            //Vec2 texcoord. Mask out the other components.
            psTexCoordOperand->aui32Swizzle[2] = 0xFFFFFFFF;
            psTexCoordOperand->aui32Swizzle[3] = 0xFFFFFFFF;
            break;
        }
        case RESOURCE_DIMENSION_TEXTURECUBE:
        {
            //Vec2 texcoord. Mask out the other components.
            psTexCoordOperand->aui32Swizzle[2] = 0xFFFFFFFF;
            psTexCoordOperand->aui32Swizzle[3] = 0xFFFFFFFF;
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE3D:
        {
            //Vec3 texcoord. Mask out the other component.
            psTexCoordOperand->aui32Swizzle[3] = 0xFFFFFFFF;
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE1DARRAY:
        {
            //Vec2 texcoord. Mask out the other components.
            psTexCoordOperand->aui32Swizzle[2] = 0xFFFFFFFF;
            psTexCoordOperand->aui32Swizzle[3] = 0xFFFFFFFF;
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE2DARRAY:
        {
            //Vec3 texcoord. Mask out the other component.
            psTexCoordOperand->aui32Swizzle[3] = 0xFFFFFFFF;
            break;
        }
        case RESOURCE_DIMENSION_TEXTURECUBEARRAY:
        {
            break;
        }
        default:
        {
            ASSERT(0);
            break;
        }
    }
}

#define TEXSMP_FLAG_NONE 0x0
#define TEXSMP_FLAG_LOD 0x1 //LOD comes from operand
#define TEXSMP_FLAG_DEPTHCOMPARE 0x2
#define TEXSMP_FLAG_FIRSTLOD 0x4 //LOD is 0
#define TEXSMP_FLAG_BIAS 0x8
#define TEXSMP_FLAGS_GRAD 0x10
static void TranslateTextureSample(HLSLCrossCompilerContext* psContext, Instruction* psInst,
    uint32_t ui32Flags)
{
    bstring glsl = *psContext->currentGLSLString;

    const char* funcName = "texture";
    const char* offset = "";
    const char* coordType = "";
    const char* gradSwizzle = "";

    uint32_t ui32NumOffsets = 0;

    const RESOURCE_DIMENSION eResDim = psContext->psShader->aeResourceDims[psInst->asOperands[2].ui32RegisterNumber];

    const int iHaveOverloadedTexFuncs = HaveOverloadedTextureFuncs(psContext->psShader->eTargetLanguage);

    ASSERT(psInst->asOperands[2].ui32RegisterNumber < MAX_TEXTURES);

    MaskOutTexCoordComponents(eResDim, &psInst->asOperands[1]);

    if(psInst->bAddressOffset)
    {
        offset = "Offset";
    }

    switch(eResDim)
    {
        case RESOURCE_DIMENSION_TEXTURE1D:
        {
            coordType = "vec2";
            gradSwizzle = ".x";
            ui32NumOffsets = 1;
            if(!iHaveOverloadedTexFuncs)
            {
                funcName = "texture1D";
                if(ui32Flags & TEXSMP_FLAG_DEPTHCOMPARE)
                {
                    funcName = "shadow1D";
                }
            }
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE2D:
        {
            coordType = "vec3";
            gradSwizzle = ".xy";
            ui32NumOffsets = 2;
            if(!iHaveOverloadedTexFuncs)
            {
                funcName = "texture2D";
                if(ui32Flags & TEXSMP_FLAG_DEPTHCOMPARE)
                {
                    funcName = "shadow2D";
                }
            }
            break;
        }
        case RESOURCE_DIMENSION_TEXTURECUBE:
        {
            coordType = "vec3";
            gradSwizzle = ".xyz";
            ui32NumOffsets = 3;
            if(!iHaveOverloadedTexFuncs)
            {
                funcName = "textureCube";
            }
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE3D:
        {
            coordType = "vec4";
            gradSwizzle = ".xyz";
            ui32NumOffsets = 3;
            if(!iHaveOverloadedTexFuncs)
            {
                funcName = "texture3D";
            }
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE1DARRAY:
        {
            coordType = "vec3";
            gradSwizzle = ".x";
            ui32NumOffsets = 1;
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE2DARRAY:
        {
            coordType = "vec4";
            gradSwizzle = ".xy";
            ui32NumOffsets = 2;
            break;
        }
        case RESOURCE_DIMENSION_TEXTURECUBEARRAY:
        {
            gradSwizzle = ".xyz";
            ui32NumOffsets = 3;
            if(ui32Flags & TEXSMP_FLAG_DEPTHCOMPARE)
            {
                //Special. Reference is a separate argument.
			    AddIndentation(psContext);
			    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
                if(ui32Flags & (TEXSMP_FLAG_LOD|TEXSMP_FLAG_FIRSTLOD))
                {
                    bcatcstr(glsl, "= (vec4(textureLod(");
                }
                else
                {
			        bcatcstr(glsl, "= (vec4(texture(");
                }
			    TextureName(psContext, psInst->asOperands[2].ui32RegisterNumber, 1);
			    bcatcstr(glsl, ",");
			    TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
			    bcatcstr(glsl, ",");
			    //.z = reference.
			    TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_NONE);

                if(ui32Flags & TEXSMP_FLAG_FIRSTLOD)
                {
                    bcatcstr(glsl, ", 0");
                }

			    bcatcstr(glsl, "))");
                // iWriteMaskEnabled is forced off during DecodeOperand because swizzle on sampler uniforms
                // does not make sense. But need to re-enable to correctly swizzle this particular instruction.
                psInst->asOperands[2].iWriteMaskEnabled = 1;
                TranslateOperandSwizzle(psContext, &psInst->asOperands[2]);
                bcatcstr(glsl, ")");

                TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
                bcatcstr(glsl, ";\n");
                return;
            }

            break;
        }
        default:
        {
            ASSERT(0);
            break;
        }
    }

    if(ui32Flags & TEXSMP_FLAG_DEPTHCOMPARE)
    {
		//For non-cubeMap Arrays the reference value comes from the
		//texture coord vector in GLSL. For cubmap arrays there is a
		//separate parameter.
		//It is always separate paramter in HLSL.
		AddIndentation(psContext);
		TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);

        if(ui32Flags & (TEXSMP_FLAG_LOD|TEXSMP_FLAG_FIRSTLOD))
        {
            bformata(glsl, " =(vec4(%sLod%s(", funcName, offset);
        }
        else
        {
            bformata(glsl, " =(vec4(%s%s(", funcName, offset);
        }
		TextureName(psContext, psInst->asOperands[2].ui32RegisterNumber, 1);
		bformata(glsl, ", %s(", coordType);
		TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
		bcatcstr(glsl, ",");
		//.z = reference.
		TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_NONE);
		bcatcstr(glsl, ")");

        if(ui32Flags & TEXSMP_FLAG_FIRSTLOD)
        {
            bcatcstr(glsl, ", 0");
        }

        bcatcstr(glsl, "))");
    }
    else
    {
        AddIndentation(psContext);
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
        if(ui32Flags & (TEXSMP_FLAG_LOD|TEXSMP_FLAG_FIRSTLOD))
        {
            bformata(glsl, " = (%sLod%s(", funcName, offset);
        }
        else
        if(ui32Flags & TEXSMP_FLAGS_GRAD)
        {
             bformata(glsl, " = (%sGrad%s(", funcName, offset);
        }
        else
        {
            bformata(glsl, " = (%s%s(", funcName, offset);
        }
        TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);//resource
        bcatcstr(glsl, ", ");
        TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);//texcoord

        if(ui32Flags & (TEXSMP_FLAG_LOD))
        {
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_NONE);
			if(psContext->psShader->ui32MajorVersion < 4)
			{
				bcatcstr(glsl, ".w");
			}
        }
        else
        if(ui32Flags & TEXSMP_FLAG_FIRSTLOD)
        {
            bcatcstr(glsl, ", 0");
        }
        else
        if(ui32Flags & TEXSMP_FLAGS_GRAD)
        {
            bcatcstr(glsl, ", vec4(");
            TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_NONE);//dx
            bcatcstr(glsl, ")");
            bcatcstr(glsl, gradSwizzle);
            bcatcstr(glsl, ", vec4(");
            TranslateOperand(psContext, &psInst->asOperands[5], TO_FLAG_NONE);//dy
            bcatcstr(glsl, ")");
            bcatcstr(glsl, gradSwizzle);
        }

        if(psInst->bAddressOffset)
        {
            if(ui32NumOffsets == 1)
            {
                bformata(glsl, ", %d",
                    psInst->iUAddrOffset);
            }
            else
            if(ui32NumOffsets == 2)
            {
                bformata(glsl, ", ivec2(%d, %d)",
                    psInst->iUAddrOffset,
                    psInst->iVAddrOffset);
            }
            else
            if(ui32NumOffsets == 3)
            {
                bformata(glsl, ", ivec3(%d, %d, %d)",
                    psInst->iUAddrOffset,
                    psInst->iVAddrOffset,
                    psInst->iWAddrOffset);
            }
        }

        if(ui32Flags & (TEXSMP_FLAG_BIAS))
        {
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_NONE);
        }

        bcatcstr(glsl, ")");
    }

    // iWriteMaskEnabled is forced off during DecodeOperand because swizzle on sampler uniforms
    // does not make sense. But need to re-enable to correctly swizzle this particular instruction.
    psInst->asOperands[2].iWriteMaskEnabled = 1;
    TranslateOperandSwizzle(psContext, &psInst->asOperands[2]);
    bcatcstr(glsl, ")");

    TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
    bcatcstr(glsl, ";\n");
}

void SetDataTypesLegacy(HLSLCrossCompilerContext* psContext, Instruction* psInst, const int32_t i32InstCount)
{
	int32_t i;

	SHADER_VARIABLE_TYPE aeTempVecType[MAX_TEMP_VEC4 * 4];
	SHADER_VARIABLE_TYPE eNewType;

    for(i=0; i < MAX_TEMP_VEC4 * 4; ++i)
    {
        aeTempVecType[i] = SVT_FLOAT;
    }

	for(i=0; i < i32InstCount; ++i, psInst++)
	{
		int k = 0;

		if(psInst->ui32NumOperands == 0)
			continue;

		//Preserve the current type on sources.
		for(k = psInst->ui32NumOperands-1; k >= (int)psInst->ui32FirstSrc; --k)
		{
			int32_t subOperand;
			Operand* psOperand = &psInst->asOperands[k];

			if(psOperand->eType == OPERAND_TYPE_TEMP)
            {
				const uint32_t ui32RegIndex = psOperand->ui32RegisterNumber*4;

				if(psOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
				{
					psOperand->aeDataType[psOperand->aui32Swizzle[0]] = aeTempVecType[ui32RegIndex+psOperand->aui32Swizzle[0]];
				}
				else if(psOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
				{
					if(psOperand->ui32Swizzle == (NO_SWIZZLE))
					{
						psOperand->aeDataType[0] = aeTempVecType[ui32RegIndex];
						psOperand->aeDataType[1] = aeTempVecType[ui32RegIndex];
						psOperand->aeDataType[2] = aeTempVecType[ui32RegIndex];
						psOperand->aeDataType[3] = aeTempVecType[ui32RegIndex];
					}
					else
					{
						psOperand->aeDataType[psOperand->aui32Swizzle[0]] = aeTempVecType[ui32RegIndex+psOperand->aui32Swizzle[0]];
					}
				}
				else if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
				{
					int c = 0;
					uint32_t ui32CompMask = psOperand->ui32CompMask;
					if(!psOperand->ui32CompMask)
					{
						ui32CompMask = OPERAND_4_COMPONENT_MASK_ALL;
					}

					for(;c<4;++c)
					{
						if(ui32CompMask & (1<<c))
						{
							psOperand->aeDataType[c] = aeTempVecType[ui32RegIndex+c];
						}
					}
				}
			}

			for(subOperand=0; subOperand < MAX_SUB_OPERANDS; subOperand++)
			{
				if(psOperand->psSubOperand[subOperand] != 0)
				{
					Operand* psSubOperand = psOperand->psSubOperand[subOperand];
					if(psSubOperand->eType == OPERAND_TYPE_TEMP)
					{
						const uint32_t ui32RegIndex = psSubOperand->ui32RegisterNumber*4;

						if(psSubOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
						{
							psSubOperand->aeDataType[psSubOperand->aui32Swizzle[0]] = aeTempVecType[ui32RegIndex+psSubOperand->aui32Swizzle[0]];
						}
						else if(psSubOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
						{
							if(psSubOperand->ui32Swizzle == (NO_SWIZZLE))
							{
								psSubOperand->aeDataType[0] = aeTempVecType[ui32RegIndex];
								psSubOperand->aeDataType[1] = aeTempVecType[ui32RegIndex];
								psSubOperand->aeDataType[2] = aeTempVecType[ui32RegIndex];
								psSubOperand->aeDataType[3] = aeTempVecType[ui32RegIndex];
							}
							else
							{
								psSubOperand->aeDataType[psSubOperand->aui32Swizzle[0]] = aeTempVecType[ui32RegIndex+psSubOperand->aui32Swizzle[0]];
							}
						}
						else if(psSubOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
						{
							int c = 0;
							uint32_t ui32CompMask = psSubOperand->ui32CompMask;
							if(!psSubOperand->ui32CompMask)
							{
								ui32CompMask = OPERAND_4_COMPONENT_MASK_ALL;
							}


							for(;c<4;++c)
							{
								if(ui32CompMask & (1<<c))
								{
									psSubOperand->aeDataType[c] = aeTempVecType[ui32RegIndex+c];
								}
							}
						}
					}
				}
			}
		}


		switch(psInst->eOpcode)
		{
		case OPCODE_MOV:
		{
			//Inherit the type of the source operand
			const Operand* psOperand = &psInst->asOperands[0];
			if(psOperand->eType == OPERAND_TYPE_TEMP)
			{
				eNewType = GetOperandDataType(psContext, &psInst->asOperands[1]);
			}
			break;
		}
		case OPCODE_MOVC:
		{
			//Inherit the type of the source operand
			const Operand* psOperand = &psInst->asOperands[0];
			if(psOperand->eType == OPERAND_TYPE_TEMP)
			{
				eNewType = GetOperandDataType(psContext, &psInst->asOperands[2]);
				//Check assumption that both the values which MOVC might pick have the same basic data type.
				ASSERT(GetOperandDataType(psContext, &psInst->asOperands[2]) == GetOperandDataType(psContext, &psInst->asOperands[3]));
			}
			break;
		}

		case OPCODE_IF:
		case OPCODE_BREAKC:
			{
				const Operand* psOperand = &psInst->asOperands[0];
				if(psOperand->eType == OPERAND_TYPE_TEMP)
				{
					const uint32_t ui32RegIndex = psOperand->ui32RegisterNumber*4;

					if(psOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
					{
						eNewType = aeTempVecType[ui32RegIndex+psOperand->aui32Swizzle[0]];
					}
					else if(psOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
					{
						if(psOperand->ui32Swizzle == (NO_SWIZZLE))
						{
							eNewType = aeTempVecType[ui32RegIndex];
						}
						else
						{
							eNewType = aeTempVecType[ui32RegIndex+psOperand->aui32Swizzle[0]];
						}
					}
					else if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
					{
						uint32_t ui32CompMask = psOperand->ui32CompMask;
						if(!psOperand->ui32CompMask)
						{
							ui32CompMask = OPERAND_4_COMPONENT_MASK_ALL;
						}
						for(;k<4;++k)
						{
							if(ui32CompMask & (1<<k))
							{
								eNewType = aeTempVecType[ui32RegIndex+k];
							}
						}
					}
				}
			break;
			}
		default:
			{
				eNewType = SVT_FLOAT;
				break;
			}
		}

		if(eNewType == SVT_UINT && HaveUVec(psContext->psShader->eTargetLanguage)==0)
		{
			//Fallback to signed int if unsigned int is not supported.
			eNewType = SVT_INT;
		}

		//Process the destination last in order to handle instructions
		//where the destination register is also used as a source.
		for(k = 0; k < (int)psInst->ui32FirstSrc; ++k)
		{
			Operand* psOperand = &psInst->asOperands[k];
			if(psOperand->eType == OPERAND_TYPE_TEMP)
			{
				const uint32_t ui32RegIndex = psOperand->ui32RegisterNumber*4;

				if(psOperand->eSelMode == OPERAND_4_COMPONENT_SELECT_1_MODE)
				{
					aeTempVecType[ui32RegIndex+psOperand->aui32Swizzle[0]] = eNewType;
					psOperand->aeDataType[psOperand->aui32Swizzle[0]] = eNewType;
				}
				else if(psOperand->eSelMode == OPERAND_4_COMPONENT_SWIZZLE_MODE)
				{
					if(psOperand->ui32Swizzle == (NO_SWIZZLE))
					{
						aeTempVecType[ui32RegIndex] = eNewType; 
						psOperand->aeDataType[0] = eNewType;
						psOperand->aeDataType[1] = eNewType;
						psOperand->aeDataType[2] = eNewType;
						psOperand->aeDataType[3] = eNewType;
					}
					else
					{
						aeTempVecType[ui32RegIndex+psOperand->aui32Swizzle[0]] = eNewType;
						psOperand->aeDataType[psOperand->aui32Swizzle[0]] = eNewType;
					}
				}
				else if(psOperand->eSelMode == OPERAND_4_COMPONENT_MASK_MODE)
				{
					int c = 0;
					uint32_t ui32CompMask = psOperand->ui32CompMask;
					if(!psOperand->ui32CompMask)
					{
						ui32CompMask = OPERAND_4_COMPONENT_MASK_ALL;
					}

					for(;c<4;++c)
					{
						if(ui32CompMask & (1<<c))
						{
							aeTempVecType[ui32RegIndex+c] = eNewType;
							psOperand->aeDataType[c] = eNewType;
						}
					}
				}
			}
		}

#if 0
		//Set immediates
		if(IsIntegerOpcode(psInst->eOpcode))
		{
			for(; k < (int)psInst->ui32NumOperands; ++k)
			{
				Operand* psOperand = &psInst->asOperands[k];
				if(psOperand->eType == OPERAND_TYPE_IMMEDIATE32)
				{
					psOperand->iIntegerImmediate = 1;
				}
			}
		}
#endif
	}
}

void TranslateInstructionLegacy(HLSLCrossCompilerContext* psContext, Instruction* psInst)
{
    bstring glsl = *psContext->currentGLSLString;

#ifdef _DEBUG
		AddIndentation(psContext);
		bformata(glsl, "//Instruction %d\n", psInst->id);
#if 0
		if(psInst->id == 73)
		{
			ASSERT(1); //Set breakpoint here to debug an instruction from its ID.
		}
#endif
#endif

    switch(psInst->eOpcode)
    {
        case OPCODE_MOV:
        {
			uint32_t srcCount = GetNumSwizzleElements(&psInst->asOperands[1]);
			uint32_t dstCount = GetNumSwizzleElements(&psInst->asOperands[0]);
			uint32_t ui32DstFlags = TO_FLAG_DESTINATION;

#ifdef _DEBUG
			AddIndentation(psContext);
			bcatcstr(glsl, "//MOV\n");
#endif

			AddIndentation(psContext);

			{
				const SHADER_VARIABLE_TYPE eDestType = GetOperandDataType(psContext, &psInst->asOperands[0]);
				const SHADER_VARIABLE_TYPE eSrcType = GetOperandDataType(psContext, &psInst->asOperands[1]);

				if(eDestType != eSrcType)
				{
					bcatcstr(glsl, "//WARNING: type mismatch on MOV. Could indicate incorrect data-type handling.\n");
					AddIndentation(psContext);
				}

				TranslateOperand(psContext, &psInst->asOperands[0], ui32DstFlags);

				if(eDestType == SVT_UINT)
				{
					bcatcstr(glsl, " = uvec4(");
				}
				else if(eDestType == SVT_INT)
				{
					bcatcstr(glsl, " = ivec4(");
				}
				else
				{
					bcatcstr(glsl, " = vec4(");
				}

				TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
				bcatcstr(glsl, ")");
				//Mismatched element count or destination has any swizzle
				if(srcCount != dstCount || (GetFirstOperandSwizzle(psContext, &psInst->asOperands[0]) != -1))
				{
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
				}
				else
				{
					AddSwizzleUsingElementCount(psContext, dstCount);
				}
				bcatcstr(glsl, ";\n");
			}
            break;
        }
        case OPCODE_MAD:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//MAD\n");
#endif
			CallTernaryOp(psContext, "*", "+", psInst, 0, 1, 2, 3, TO_FLAG_NONE);
            break;
        }
        case OPCODE_ADD:
        {

#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ADD\n");
#endif
			CallBinaryOp(psContext, "+", psInst, 0, 1, 2, TO_FLAG_NONE);
            break;
        }
        case OPCODE_GE:
        {
            /*
                dest = vec4(greaterThanEqual(vec4(srcA), vec4(srcB));
                Caveat: The result is a boolean but HLSL asm returns 0xFFFFFFFF/0x0 instead.
             */
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//GE\n");
#endif
            AddComparision(psContext, psInst, CMP_GE, TO_FLAG_NONE);
            break;
        }
        case OPCODE_MUL:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//MUL\n");
#endif
			CallBinaryOp(psContext, "*", psInst, 0, 1, 2, TO_FLAG_NONE);
            break;
        }
        case OPCODE_DIV:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//DIV\n");
#endif
			CallBinaryOp(psContext, "/", psInst, 0, 1, 2, TO_FLAG_NONE);
            break;
        }
        case OPCODE_SINCOS:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SINCOS\n");
#endif
            if(psInst->asOperands[0].eType != OPERAND_TYPE_NULL)
            {
                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);//Dest sin
                bcatcstr(glsl, " = sin(");
                TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);//angle
                bcatcstr(glsl, ");\n");
            }

            if(psInst->asOperands[1].eType != OPERAND_TYPE_NULL)
            {
                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);//Dest cos
                bcatcstr(glsl, " = cos(");
                TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);//angle
                bcatcstr(glsl, ");\n");
            }
            break;
        }
        case OPCODE_DP3:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//DP3\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = vec4(dot((");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ").xyz, (");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ").xyz))");
            TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_DP4:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//DP4\n");
#endif
			CallHelper2(psContext, "dot", psInst, 0, 1, 2);
            break;
        }
        case OPCODE_LT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LT\n");
#endif
            AddComparision(psContext, psInst, CMP_LT, TO_FLAG_NONE);
            break;
        }
        case OPCODE_MOVC:
        {
            uint32_t destElemCount = GetNumSwizzleElements(&psInst->asOperands[0]);
            uint32_t s0ElemCount = GetNumSwizzleElements(&psInst->asOperands[1]);
            uint32_t s1ElemCount = GetNumSwizzleElements(&psInst->asOperands[2]);
            uint32_t s2ElemCount = GetNumSwizzleElements(&psInst->asOperands[3]);
            uint32_t destElem;
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//MOVC\n");
#endif
/*
            for each component in dest[.mask]
                if the corresponding component in src0 (POS-swizzle)
                    has any bit set
                {
                    copy this component (POS-swizzle) from src1 into dest
                }
                else
                {
                    copy this component (POS-swizzle) from src2 into dest
                }
            endfor
*/

			/* Single-component conditional variable (src0) */
			if(s0ElemCount==1 || IsSwizzleReplacated(&psInst->asOperands[1]))
			{
                AddIndentation(psContext);
                bcatcstr(glsl, "if(vec4(");

                TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);

				bcatcstr(glsl, ").x");

				if(psContext->psShader->ui32MajorVersion < 4)
				{
					//cmp opcode uses >= 0
					bcatcstr(glsl, " >= 0) {\n");
				}
				else
				{
					bcatcstr(glsl, " != 0) {\n");
				}

                psContext->indent++;
                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
                bcatcstr(glsl, " = ");
				if(destElemCount != s1ElemCount)
				{
					bcatcstr(glsl, "vec4(");
				}
                TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
				if(destElemCount != s1ElemCount)
				{
					bcatcstr(glsl, ")");
					AddSwizzleUsingElementCount(psContext, destElemCount);
				}
                bcatcstr(glsl, ";\n");

                psContext->indent--;
                AddIndentation(psContext);
                bcatcstr(glsl, "} else {\n");
                psContext->indent++;
                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
                bcatcstr(glsl, " = ");
				if(destElemCount != s2ElemCount)
				{
					bcatcstr(glsl, "vec4(");
				}
                TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
				if(destElemCount != s2ElemCount)
				{
					bcatcstr(glsl, ")");
					AddSwizzleUsingElementCount(psContext, destElemCount);
				}
                bcatcstr(glsl, ";\n");
                psContext->indent--;
                AddIndentation(psContext);
                bcatcstr(glsl, "}\n");
			}
			else
            for(destElem=0; destElem < destElemCount; ++destElem)
            {
                const char* swizzle[] = {".x", ".y", ".z", ".w"};

                AddIndentation(psContext);
                bcatcstr(glsl, "if(");
                TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
                if(s0ElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);

				if(psContext->psShader->ui32MajorVersion < 4)
				{
					//cmp opcode uses >= 0
					bcatcstr(glsl, " >= 0) {\n");
				}
				else
				{
					bcatcstr(glsl, " != 0) {\n");
				}

                psContext->indent++;
                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
                if(destElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);
                bcatcstr(glsl, " = ");
                TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
                if(s1ElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);
                bcatcstr(glsl, ";\n");

                psContext->indent--;
                AddIndentation(psContext);
                bcatcstr(glsl, "} else {\n");
                psContext->indent++;
                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
                if(destElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);
                bcatcstr(glsl, " = ");
                TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
                if(s2ElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);
                bcatcstr(glsl, ";\n");
                psContext->indent--;
                AddIndentation(psContext);
                bcatcstr(glsl, "}\n");
            }
            break;
        }
		case OPCODE_LOG:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LOG\n");
#endif
			CallHelper1(psContext, "log", psInst, 0, 1);
            break;
        }
		case OPCODE_RSQ:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//RSQ\n");
#endif
			CallHelper1(psContext, "inversesqrt", psInst, 0, 1);
            break;
        }
        case OPCODE_EXP:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EXP\n");
#endif
			CallHelper1(psContext, "exp", psInst, 0, 1);
            break;
        }
		case OPCODE_ROUND_NI:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ROUND_NI\n");
#endif
			CallHelper1(psContext, "floor", psInst, 0, 1);
            break;
        }
		case OPCODE_MAX:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//MAX\n");
#endif
			CallHelper2(psContext, "max", psInst, 0, 1, 2);
            break;
        }
		case OPCODE_MIN:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//MIN\n");
#endif
			CallHelper2(psContext, "min", psInst, 0, 1, 2);
            break;
        }
		case OPCODE_SAMPLE:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SAMPLE\n");
#endif
            TranslateTextureSample(psContext, psInst, TEXSMP_FLAG_NONE);
            break;
        }
        case OPCODE_SAMPLE_L:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SAMPLE_L\n");
#endif
            TranslateTextureSample(psContext, psInst, TEXSMP_FLAG_LOD);
            break;
        }
		case OPCODE_SAMPLE_D:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SAMPLE_D\n");
#endif

            TranslateTextureSample(psContext, psInst, TEXSMP_FLAGS_GRAD);
			break;
		}
		case OPCODE_RET:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//RET\n");
#endif
            if(psContext->havePostShaderCode[psContext->currentPhase])
            {
#ifdef _DEBUG
                AddIndentation(psContext);
                bcatcstr(glsl, "//--- Post shader code ---\n");
#endif
                bconcat(glsl, psContext->postShaderCode[psContext->currentPhase]);
#ifdef _DEBUG
                AddIndentation(psContext);
                bcatcstr(glsl, "//--- End post shader code ---\n");
#endif
            }
            AddIndentation(psContext);
			bcatcstr(glsl, "return;\n");
			break;
		}
		case OPCODE_REP:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//REP\n");
#endif
			//Need to handle nesting.
			//Max of 4 for rep - 'Flow Control Limitations' http://msdn.microsoft.com/en-us/library/windows/desktop/bb219848(v=vs.85).aspx

			AddIndentation(psContext);
			bcatcstr(glsl, "RepCounter = ");
			TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
			bcatcstr(glsl, ".x;\n");

            AddIndentation(psContext);
            bcatcstr(glsl, "while(RepCounter!=0){\n");
            ++psContext->indent;
            break;
		}
		case OPCODE_ENDREP:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ENDREP\n");
#endif
            AddIndentation(psContext);
            bcatcstr(glsl, "RepCounter--;\n");

			--psContext->indent;

            AddIndentation(psContext);
			bcatcstr(glsl, "}\n");
            break;
		}
        case OPCODE_LOOP:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LOOP\n");
#endif
            AddIndentation(psContext);
            bcatcstr(glsl, "while(true){\n");
            ++psContext->indent;
            break;
        }
        case OPCODE_ENDLOOP:
        {
            --psContext->indent;
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ENDLOOP\n");
#endif
            AddIndentation(psContext);
            bcatcstr(glsl, "}\n");
            break;
        }
        case OPCODE_BREAK:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//BREAK\n");
#endif
            AddIndentation(psContext);
            bcatcstr(glsl, "break;\n");
            break;
        }
        case OPCODE_BREAKC:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//BREAKC\n");
#endif
            AddIndentation(psContext);

			switch(psInst->eDX9TestType)
			{
				case D3DSPC_GT:
				{
					bcatcstr(glsl, "if(");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " > ");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, "){ break; }\n");
					break;
				}
				case D3DSPC_EQ:
				{
					bcatcstr(glsl, "if(");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " == ");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, "){ break; }\n");
					break;
				}
				case D3DSPC_GE:
				{
					bcatcstr(glsl, "if(");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " >= ");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, "){ break; }\n");
					break;
				}
				case D3DSPC_LT:
				{
					bcatcstr(glsl, "if(");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " < ");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, "){ break; }\n");
					break;
				}
				case D3DSPC_NE:
				{
					bcatcstr(glsl, "if(");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " != ");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, "){ break; }\n");
					break;
				}
				case D3DSPC_LE:
				{
					bcatcstr(glsl, "if(");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " <= ");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, "){ break; }\n");
					break;
				}
				default:
				{
					break;
				}
			}
            break;
        }
        case OPCODE_IF:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IF\n");
#endif
            AddIndentation(psContext);

			switch(psInst->eDX9TestType)
			{
				case D3DSPC_LT:
				{
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ") < (");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ")){\n");
					break;
				}
				case D3DSPC_NE:
				{
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ") != (");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ")){\n");
					break;
				}
				case D3DSPC_LE:
				{
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ") <= (");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ")){\n");
					break;
				}
				case D3DSPC_GE:
				{
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ") >= (");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ")){\n");
					break;
				}
				case D3DSPC_GT:
				{
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ") > (");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ")){\n");
					break;
				}
				case D3DSPC_EQ:
				{
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ") == (");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ")){\n");
					break;
				}
				default:
				{
					ASSERT(0);
					break;
				}
			}
            ++psContext->indent;
            break;
        }
        case OPCODE_ELSE:
        {
            --psContext->indent;
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ELSE\n");
#endif
            AddIndentation(psContext);
            bcatcstr(glsl, "} else {\n");
            psContext->indent++;
            break;
        }
        case OPCODE_ENDIF:
        {
            --psContext->indent;
            AddIndentation(psContext);
            bcatcstr(glsl, "//ENDIF\n");
            AddIndentation(psContext);
            bcatcstr(glsl, "}\n");
            break;
        }
        case OPCODE_NOP:
        {
            break;
        }
		case OPCODE_DISCARD:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//DISCARD\n");
#endif
            AddIndentation(psContext);

			bcatcstr(glsl, "if(any(lessThan((");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);

			if(psContext->psShader->ui32MajorVersion == 1)
			{
				/* SM1.X only kills based on the rgb channels */
				bcatcstr(glsl, ").xyz, vec3(0)))){discard;}\n");
			}
			else
			{
				bcatcstr(glsl, "), vec4(0)))){discard;}\n");
			}

			break;
		}
        case OPCODE_RCP:
        {
            const uint32_t destElemCount = GetNumSwizzleElements(&psInst->asOperands[0]);
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//RCP\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = (vec4(1.0) / vec4(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, "))");
            AddSwizzleUsingElementCount(psContext, destElemCount);
            bcatcstr(glsl, ";\n");
            break;
        }
		case OPCODE_DERIV_RTX:
		{
#ifdef _DEBUG
			AddIndentation(psContext);
			bcatcstr(glsl, "//DERIV_RTX\n");
#endif
			CallHelper1(psContext, "dFdx", psInst, 0, 1);
			break;
		}
		case OPCODE_DERIV_RTY:
		{
#ifdef _DEBUG
			AddIndentation(psContext);
			bcatcstr(glsl, "//DERIV_RTY\n");
#endif
			CallHelper1(psContext, "dFdy", psInst, 0, 1);
			break;
		}
		case OPCODE_LRP:
		{
#ifdef _DEBUG
			AddIndentation(psContext);
			bcatcstr(glsl, "//LRP\n");
#endif
			CallHelper3(psContext, "mix", psInst, 0, 2, 3, 1);
			break;
		}
		case OPCODE_DP2ADD:
		{
#ifdef _DEBUG
			AddIndentation(psContext);
			bcatcstr(glsl, "//DP2ADD\n");
#endif
			AddIndentation(psContext);
			TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
			bcatcstr(glsl, " = dot(vec2(");
			TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
			bcatcstr(glsl, "), vec2(");
			TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
			bcatcstr(glsl, ")) + ");
			TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
			bcatcstr(glsl, ";\n");
			break;
		}
		case OPCODE_POW:
		{
#ifdef _DEBUG
			AddIndentation(psContext);
			bcatcstr(glsl, "//POW\n");
#endif
			AddIndentation(psContext);
			TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
			bcatcstr(glsl, " = pow(abs(");
			TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
			bcatcstr(glsl, "), ");
			TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
			bcatcstr(glsl, ");\n");
			break;
		}
        default:
        {
            ASSERT(0);
            break;
        }
    }

    if(psInst->bSaturate)
    {
        AddIndentation(psContext);
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
        bcatcstr(glsl ," = clamp(");
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
        bcatcstr(glsl, ", 0, 1);\n");
    }
}

