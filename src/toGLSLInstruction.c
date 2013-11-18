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

static void AddComparision(HLSLCrossCompilerContext* psContext, Instruction* psInst, ComparisonType eType)
{
    bstring glsl = *psContext->currentGLSLString;
    const uint32_t destElemCount = GetNumSwizzleElements(&psInst->asOperands[0]);
    const uint32_t s0ElemCount = GetNumSwizzleElements(&psInst->asOperands[1]);
    const uint32_t s1ElemCount = GetNumSwizzleElements(&psInst->asOperands[2]);

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

        //Component-wise compare
        AddIndentation(psContext);
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
        bformata(glsl, " = vec%d(%s((", minElemCount, glslOpcode[eType]);
        TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
        bcatcstr(glsl, ")");
        AddSwizzleUsingElementCount(psContext, minElemCount);
        bcatcstr(glsl, ", (");
        TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
        bcatcstr(glsl, ")");
        AddSwizzleUsingElementCount(psContext, minElemCount);
        bcatcstr(glsl, "));\n");
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
        TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
        bcatcstr(glsl, ")");
        if(s0ElemCount > minElemCount)
            AddSwizzleUsingElementCount(psContext, minElemCount);
        bformata(glsl, "%s (", glslOpcode[eType]);
        TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
        bcatcstr(glsl, ")");
        if(s1ElemCount > minElemCount)
            AddSwizzleUsingElementCount(psContext, minElemCount);
        bcatcstr(glsl, ") ? 1 : 0;\n");
    }
}

void CallHLSLOpcodeFunc1(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = *psContext->currentGLSLString;

    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc2(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc3(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
    bcatcstr(glsl, ");\n");
}

void CallHLSLIntegerOpcodeFunc2(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_INTEGER|TO_FLAG_DESTINATION);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_INTEGER);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_INTEGER);
    bcatcstr(glsl, ");\n");
}

void CallBinaryOp(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1, uint32_t dataType)
{
    bstring glsl = *psContext->currentGLSLString;
	uint32_t src1SwizCount = GetNumSwizzleElements(&psInst->asOperands[src1]);
	uint32_t src0SwizCount = GetNumSwizzleElements(&psInst->asOperands[src0]);
	uint32_t dstSwizCount = GetNumSwizzleElements(&psInst->asOperands[dest]);

    CheckOperandForTempTypeChange(psContext,
        &psInst->asOperands[dest],
        TO_FLAG_DESTINATION|dataType);
    CheckOperandForTempTypeChange(psContext,
        &psInst->asOperands[src0],
        dataType);
    CheckOperandForTempTypeChange(psContext,
        &psInst->asOperands[src1],
        dataType);

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
		bcatcstr(glsl, " = vec4(");
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

void CallTernaryOp(HLSLCrossCompilerContext* psContext, const char* op1, const char* op2, Instruction* psInst, 
 int dest, int src0, int src1, int src2)
{
    bstring glsl = *psContext->currentGLSLString;
	uint32_t src2SwizCount = GetNumSwizzleElements(&psInst->asOperands[src2]);
	uint32_t src1SwizCount = GetNumSwizzleElements(&psInst->asOperands[src1]);
	uint32_t src0SwizCount = GetNumSwizzleElements(&psInst->asOperands[src0]);
	uint32_t dstSwizCount = GetNumSwizzleElements(&psInst->asOperands[dest]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == src2SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);
		bcatcstr(glsl, " = ");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
		bformata(glsl, " %s ", op1);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE);
		bformata(glsl, " %s ", op2);
		TranslateOperand(psContext, &psInst->asOperands[src2], TO_FLAG_NONE);
		bcatcstr(glsl, ";\n");
	}
	else
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);
		bcatcstr(glsl, " = vec4(");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
		bformata(glsl, " %s ", op1);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE);
		bformata(glsl, " %s ", op2);
		TranslateOperand(psContext, &psInst->asOperands[src2], TO_FLAG_NONE);
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

void CallHelper2UInt(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);

	bcatcstr(glsl, " = uvec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(uint(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_INTEGER);
    bcatcstr(glsl, "), uint(");
    TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_INTEGER);
    bcatcstr(glsl, ")))");
    TranslateOperandSwizzle(psContext, &psInst->asOperands[dest]);
    bcatcstr(glsl, ";\n");
}

void CallHelper1(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0)
{
    bstring glsl = *psContext->currentGLSLString;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_DESTINATION);

	bcatcstr(glsl, " = vec4(");

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


void TranslateInstruction(HLSLCrossCompilerContext* psContext, Instruction* psInst)
{
    bstring glsl = *psContext->currentGLSLString;

#ifdef _DEBUG
		AddIndentation(psContext);
		bformata(glsl, "//Instruction %d\n", psInst->id);
#if 0
		if(psInst->id == XYZ)
		{
			ASSERT(1); //Set breakpoint here to debug an instruction from its ID.
		}
#endif
#endif

    switch(psInst->eOpcode)
    {
        case OPCODE_FTOI: //Fall-through to MOV
		case OPCODE_FTOU: //Fall-through to MOV
        case OPCODE_MOV:
        {
			uint32_t srcCount = GetNumSwizzleElements(&psInst->asOperands[1]);
			uint32_t dstCount = GetNumSwizzleElements(&psInst->asOperands[0]);
			uint32_t ui32DstFlags = TO_FLAG_DESTINATION;

			if(psInst->eOpcode == OPCODE_FTOU)
			{
#ifdef _DEBUG
				AddIndentation(psContext);
				bcatcstr(glsl, "//FTOU\n");
#endif
				ui32DstFlags |= TO_FLAG_UNSIGNED_INTEGER;

				ASSERT(GetOperandDataType(psContext, &psInst->asOperands[1]) == SVT_FLOAT);
			}
			else if(psInst->eOpcode == OPCODE_FTOI)
			{
#ifdef _DEBUG
				AddIndentation(psContext);
				bcatcstr(glsl, "//FTOI\n");
#endif
				ui32DstFlags |= TO_FLAG_INTEGER;

				ASSERT(GetOperandDataType(psContext, &psInst->asOperands[1]) == SVT_FLOAT);
			}
			else
			{
#ifdef _DEBUG
				AddIndentation(psContext);
				bcatcstr(glsl, "//MOV\n");
#endif
			}

			AddIndentation(psContext);

			if(psInst->eOpcode == OPCODE_FTOU)
			{
				TranslateOperand(psContext, &psInst->asOperands[0], ui32DstFlags);

				if(srcCount == 1)
					bcatcstr(glsl, " = uint(");
				if(srcCount == 2)
					bcatcstr(glsl, " = uivec2(");
				if(srcCount == 3)
					bcatcstr(glsl, " = uivec3(");
				if(srcCount == 4)
					bcatcstr(glsl, " = uivec4(");

				TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
				if(srcCount != dstCount)
				{
					bcatcstr(glsl, ")");
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, ";\n");
				}
				else
				{
					bcatcstr(glsl, ");\n");
				}

				//Change type at the end in case dest and src are the same register.
				SetOperandDataType(psContext,
				&psInst->asOperands[0],
				SVT_UINT);
			}
			else
			if(psInst->eOpcode == OPCODE_FTOI)
			{
				TranslateOperand(psContext, &psInst->asOperands[0], ui32DstFlags);

				if(srcCount == 1)
					bcatcstr(glsl, " = int(");
				if(srcCount == 2)
					bcatcstr(glsl, " = ivec2(");
				if(srcCount == 3)
					bcatcstr(glsl, " = ivec3(");
				if(srcCount == 4)
					bcatcstr(glsl, " = ivec4(");

				TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);

				if(srcCount != dstCount)
				{
					bcatcstr(glsl, ")");
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, ";\n");
				}
				else
				{
					bcatcstr(glsl, ");\n");
				}

				//Change type at the end in case dest and src are the same register.
				SetOperandDataType(psContext,
				&psInst->asOperands[0],
				SVT_INT);
			}
			else
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
        case OPCODE_ITOF://signed to float
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ITOF\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = vec4(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_INTEGER);
            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_UTOF://unsigned to float
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//UTOF\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = vec4(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_UNSIGNED_INTEGER);
            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_MAD:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//MAD\n");
#endif
			CallTernaryOp(psContext, "*", "+", psInst, 0, 1, 2, 3);
            break;
        }
        case OPCODE_IMAD:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IMAD\n");
#endif
			CallTernaryOp(psContext, "*", "+", psInst, 0, 1, 2, 3);
            break;
        }
        case OPCODE_IADD:
        {
            uint32_t ui32Flags = TO_FLAG_INTEGER;
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IADD\n");
#endif
            //Is this a signed or unsigned add?
            if(GetOperandDataType(psContext, &psInst->asOperands[1]) == SVT_UINT)
            {
                ui32Flags = TO_FLAG_UNSIGNED_INTEGER;
            }
			CallBinaryOp(psContext, "+", psInst, 0, 1, 2, TO_FLAG_UNSIGNED_INTEGER);
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
        case OPCODE_OR:
        {
            /*Todo: vector version */
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//OR\n");
#endif
			CallBinaryOp(psContext, "|", psInst, 0, 1, 2, TO_FLAG_INTEGER);
            break;
        }
        case OPCODE_AND:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//AND\n");
#endif
			CallHLSLOpcodeFunc2(psContext, "HLSL_and", psInst);
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
            AddComparision(psContext, psInst, CMP_GE);
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
        case OPCODE_IMUL:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IMUL\n");
#endif
			CallBinaryOp(psContext, "*", psInst, 0, 1, 2, TO_FLAG_NONE);
            break;
        }
        case OPCODE_UDIV:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//UDIV\n");
#endif
			//destQuotient, destRemainder, src0, src1
			CallBinaryOp(psContext, "/", psInst, 0, 2, 3, TO_FLAG_UNSIGNED_INTEGER);
			CallHelper2UInt(psContext, "mod", psInst, 1, 2, 3);
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

        case OPCODE_DP2:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//DP2\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = vec4(dot((");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ").xy, (");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ").xy))");
            TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
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
        case OPCODE_INE:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//INE\n");
#endif
            AddComparision(psContext, psInst, CMP_NE);
            break;
        }
        case OPCODE_NE:
        {
            //Scalar version. Use any() for vector with scalar 1
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//NE\n");
#endif
            AddComparision(psContext, psInst, CMP_NE);
            break;
        }
        case OPCODE_IGE:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IGE\n");
#endif
            CallHLSLIntegerOpcodeFunc2(psContext, "HLSL_ige", psInst);
            break;
        }
        case OPCODE_ILT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ILT\n");
#endif
            CallHLSLIntegerOpcodeFunc2(psContext, "HLSL_ilt", psInst);
            break;
        }
        case OPCODE_LT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LT\n");
#endif
            AddComparision(psContext, psInst, CMP_LT);
            break;
        }
        case OPCODE_IEQ:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IEQ\n");
#endif
            CallHLSLIntegerOpcodeFunc2(psContext, "HLSL_ieq", psInst);
            break;
        }
        case OPCODE_ULT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ULT\n");
#endif
            CallHLSLIntegerOpcodeFunc2(psContext, "HLSL_ult", psInst);
            break;
        }
        case OPCODE_UGE:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//UGE\n");
#endif
            CallHLSLIntegerOpcodeFunc2(psContext, "HLSL_uge", psInst);
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
			if(s1ElemCount==1 || IsSwizzleReplacated(&psInst->asOperands[1]))
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
		case OPCODE_SQRT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SQRT\n");
#endif
			CallHelper1(psContext, "sqrt", psInst, 0, 1);
            break;
        }
        case OPCODE_ROUND_PI:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ROUND_PI\n");
#endif
			CallHelper1(psContext, "ceil", psInst, 0, 1);
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
		case OPCODE_ROUND_Z:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ROUND_Z\n");
#endif
			CallHelper1(psContext, "trunc", psInst, 0, 1);
            break;
        }
		case OPCODE_ROUND_NE:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ROUND_NE\n");
#endif
			CallHelper1(psContext, "roundEven", psInst, 0, 1);
            break;
        }
		case OPCODE_FRC:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//FRC\n");
#endif
			CallHelper1(psContext, "fract", psInst, 0, 1);
            break;
        }
		case OPCODE_IMAX:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IMAX\n");
#endif
			CallHelper2(psContext, "max", psInst, 0, 1, 2);
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
        case OPCODE_GATHER4:
        {
            //dest, coords, tex, sampler
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//GATHER4\n");
#endif
//gather4 r7.xyzw, r3.xyxx, t3.xyzw, s0.x
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = (textureGather(");

            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[1].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[1].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ")");
            // iWriteMaskEnabled is forced off during DecodeOperand because swizzle on sampler uniforms
            // does not make sense. But need to re-enable to correctly swizzle this particular instruction.
            psInst->asOperands[2].iWriteMaskEnabled = 1;
            TranslateOperandSwizzle(psContext, &psInst->asOperands[2]);
            bcatcstr(glsl, ")");

            TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_GATHER4_PO_C:
        {
            //dest, coords, offset, tex, sampler, srcReferenceValue
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//GATHER4_PO_C\n");
#endif

            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = (textureGatherOffset(");

            TextureName(psContext, psInst->asOperands[3].ui32RegisterNumber, 1);

            bcatcstr(glsl, ", ");
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[1].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[1].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);

            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[5], TO_FLAG_NONE);

            bcatcstr(glsl, ", ivec2(");
            //ivec2 offset
            psInst->asOperands[2].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[2].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, "))");
            // iWriteMaskEnabled is forced off during DecodeOperand because swizzle on sampler uniforms
            // does not make sense. But need to re-enable to correctly swizzle this particular instruction.
            psInst->asOperands[2].iWriteMaskEnabled = 1;
            TranslateOperandSwizzle(psContext, &psInst->asOperands[3]);
            bcatcstr(glsl, ")");

            TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_GATHER4_PO:
        {
            //dest, coords, offset, tex, sampler
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//GATHER4_PO\n");
#endif

            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = (textureGatherOffset(");

            TextureName(psContext, psInst->asOperands[3].ui32RegisterNumber, 0);

            bcatcstr(glsl, ", ");
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[1].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[1].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);

            bcatcstr(glsl, ", ivec2(");
            //ivec2 offset
            psInst->asOperands[2].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[2].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, "))");
            // iWriteMaskEnabled is forced off during DecodeOperand because swizzle on sampler uniforms
            // does not make sense. But need to re-enable to correctly swizzle this particular instruction.
            psInst->asOperands[2].iWriteMaskEnabled = 1;
            TranslateOperandSwizzle(psContext, &psInst->asOperands[3]);
            bcatcstr(glsl, ")");

            TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_GATHER4_C:
        {
            //dest, coords, tex, sampler srcReferenceValue
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//GATHER4_C\n");
#endif

            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = (textureGather(");

            TextureName(psContext, psInst->asOperands[2].ui32RegisterNumber, 1);

            bcatcstr(glsl, ", ");
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[1].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[1].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);

            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_NONE);
            bcatcstr(glsl, ")");
            // iWriteMaskEnabled is forced off during DecodeOperand because swizzle on sampler uniforms
            // does not make sense. But need to re-enable to correctly swizzle this particular instruction.
            psInst->asOperands[2].iWriteMaskEnabled = 1;
            TranslateOperandSwizzle(psContext, &psInst->asOperands[2]);
            bcatcstr(glsl, ")");

            TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
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
		case OPCODE_SAMPLE_C:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SAMPLE_C\n");
#endif

            TranslateTextureSample(psContext, psInst, TEXSMP_FLAG_DEPTHCOMPARE);
			break;
		}
		case OPCODE_SAMPLE_C_LZ:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SAMPLE_C_LZ\n");
#endif

            TranslateTextureSample(psContext, psInst, TEXSMP_FLAG_DEPTHCOMPARE | TEXSMP_FLAG_FIRSTLOD);
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
		case OPCODE_SAMPLE_B:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SAMPLE_B\n");
#endif

            TranslateTextureSample(psContext, psInst, TEXSMP_FLAG_BIAS);
			break;
		}
		case OPCODE_RET:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//RET\n");
#endif
            if(psContext->haveOutputBuiltins[psContext->currentPhase])
            {
#ifdef _DEBUG
                AddIndentation(psContext);
                bcatcstr(glsl, "//--- Start builtin outputs ---\n");
#endif
                bconcat(glsl, psContext->writeBuiltins[psContext->currentPhase]);
#ifdef _DEBUG
                AddIndentation(psContext);
                bcatcstr(glsl, "//--- End builtin outputs ---\n");
#endif
            }
            AddIndentation(psContext);
			bcatcstr(glsl, "return;\n");
			break;
		}
        case OPCODE_INTERFACE_CALL:
        {
            const char* name;
            ShaderVar* psVar;
            uint32_t varFound;

            uint32_t funcPointer;
            uint32_t funcTableIndex;
            uint32_t funcTable;
            uint32_t funcBodyIndex;
            uint32_t funcBody;
            uint32_t ui32NumBodiesPerTable;

#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//INTERFACE_CALL\n");
#endif

            ASSERT(psInst->asOperands[0].eIndexRep[0] == OPERAND_INDEX_IMMEDIATE32);

            funcPointer = psInst->asOperands[0].aui32ArraySizes[0];
            funcTableIndex = psInst->asOperands[0].aui32ArraySizes[1];
            funcBodyIndex = psInst->ui32FuncIndexWithinInterface;

            ui32NumBodiesPerTable = psContext->psShader->funcPointer[funcPointer].ui32NumBodiesPerTable;

            funcTable = psContext->psShader->funcPointer[funcPointer].aui32FuncTables[funcTableIndex];

            funcBody = psContext->psShader->funcTable[funcTable].aui32FuncBodies[funcBodyIndex];

            varFound = GetInterfaceVarFromOffset(funcPointer, &psContext->psShader->sInfo, &psVar);

            ASSERT(varFound);

            name = &psVar->Name[0];

            AddIndentation(psContext);
            bcatcstr(glsl, name);
            TranslateOperandIndexMAD(psContext, &psInst->asOperands[0], 1, ui32NumBodiesPerTable, funcBodyIndex);
            //bformata(glsl, "[%d]", funcBodyIndex);
            bcatcstr(glsl, "();\n");
            break;
        }
        case OPCODE_LABEL:
        {
    #ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LABEL\n");
#endif
            --psContext->indent;
            AddIndentation(psContext);
            bcatcstr(glsl, "}\n"); //Closing brace ends the previous function.
            AddIndentation(psContext);

            bcatcstr(glsl, "subroutine(SubroutineType)\n");
            bcatcstr(glsl, "void ");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, "(){\n");
            ++psContext->indent;
            break;
        }
        case OPCODE_COUNTBITS:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//COUNTBITS\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_INTEGER|TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = bitCount(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_INTEGER);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_HI:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//FIRSTBIT_HI\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_UNSIGNED_INTEGER|TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = findMSB(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_UNSIGNED_INTEGER);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_LO:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//FIRSTBIT_LO\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_UNSIGNED_INTEGER|TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = findLSB(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_UNSIGNED_INTEGER);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_SHI: //signed high
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//FIRSTBIT_SHI\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_INTEGER|TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = findMSB(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_INTEGER);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_BFREV:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//BFREV\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_INTEGER|TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = bitfieldReverse(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_INTEGER);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_BFI:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//BFI\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_INTEGER|TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = bitfieldInsert(");
            TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_INTEGER);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_INTEGER);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_INTEGER);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_INTEGER);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_CUT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//CUT\n");
#endif
            AddIndentation(psContext);
			bcatcstr(glsl, "EndPrimitive();\n");
			break;
        }
        case OPCODE_EMIT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EMIT\n");
#endif
            if(psContext->haveOutputBuiltins[psContext->currentPhase])
            {
#ifdef _DEBUG
                AddIndentation(psContext);
                bcatcstr(glsl, "//--- Start builtin outputs ---\n");
#endif
                bconcat(glsl, psContext->writeBuiltins[psContext->currentPhase]);
#ifdef _DEBUG
                AddIndentation(psContext);
                bcatcstr(glsl, "//--- End builtin outputs ---\n");
#endif
                AddIndentation(psContext);
            }

            AddIndentation(psContext);
			bcatcstr(glsl, "EmitVertex();\n");
			break;
        }
        case OPCODE_EMITTHENCUT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EMITTHENCUT\n");
#endif
            AddIndentation(psContext);
			bcatcstr(glsl, "EmitVertex();\nEndPrimitive();\n");
			break;
        }

        case OPCODE_CUT_STREAM:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//CUT\n");
#endif
            AddIndentation(psContext);
			bcatcstr(glsl, "EndStreamPrimitive(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, ");\n");

			break;
        }
        case OPCODE_EMIT_STREAM:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EMIT\n");
#endif
            AddIndentation(psContext);
			bcatcstr(glsl, "EmitStreamVertex(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, ");\n");
			break;
        }
        case OPCODE_EMITTHENCUT_STREAM:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EMITTHENCUT\n");
#endif
            AddIndentation(psContext);
			bcatcstr(glsl, "EmitStreamVertex(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, ");\n");
			bcatcstr(glsl, "EndStreamPrimitive(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, ");\n");
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

			if(psContext->psShader->ui32MajorVersion < 4)
			{
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
			}
			else
			{
				if(psInst->eBooleanTestType == INSTRUCTION_TEST_ZERO)
				{
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ")==0){break;}\n");
				}
				else
				{
					ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ")!=0){break;}\n");
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

			if(psContext->psShader->ui32MajorVersion < 4)
			{
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
			}
			else
			{
				if(psInst->eBooleanTestType == INSTRUCTION_TEST_ZERO)
				{
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ")==0){\n");
				}
				else
				{
					ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
					bcatcstr(glsl, "if((");
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, ")!=0){\n");
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
        case OPCODE_ENDSWITCH:
        case OPCODE_ENDIF:
        {
            --psContext->indent;
            AddIndentation(psContext);
            bcatcstr(glsl, "//ENDIF\n");
            AddIndentation(psContext);
            bcatcstr(glsl, "}\n");
            break;
        }
        case OPCODE_CONTINUE:
        {
            AddIndentation(psContext);
            bcatcstr(glsl, "continue;\n");
            break;
        }
        case OPCODE_DEFAULT:
        {
            --psContext->indent;
            AddIndentation(psContext);
            bcatcstr(glsl, "default:\n");
            ++psContext->indent;
            break;
        }
        case OPCODE_NOP:
        {
            break;
        }
        case OPCODE_SYNC:
        {
            const uint32_t ui32SyncFlags = psInst->ui32SyncFlags;

#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SYNC\n");
#endif

            AddIndentation(psContext);

            if(ui32SyncFlags & SYNC_THREADS_IN_GROUP)
            {
                bcatcstr(glsl, "groupMemoryBarrier();\n");
            }
            if(ui32SyncFlags & SYNC_THREAD_GROUP_SHARED_MEMORY)
            {
                bcatcstr(glsl, "memoryBarrierShared();\n");
            }
            if(ui32SyncFlags & (SYNC_UNORDERED_ACCESS_VIEW_MEMORY_GROUP|SYNC_UNORDERED_ACCESS_VIEW_MEMORY_GLOBAL))
            {
                bcatcstr(glsl, "memoryBarrier();\n");
            }
            break;
        }
        case OPCODE_SWITCH:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SWITCH\n");
#endif
            AddIndentation(psContext);
            bcatcstr(glsl, "switch(int(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ")){\n");

            psContext->indent += 2;
            break;
        }
        case OPCODE_CASE:
        {
            --psContext->indent;
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//case\n");
#endif
            AddIndentation(psContext);

            bcatcstr(glsl, "case ");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ":\n");

            ++psContext->indent;
            break;
        }
		case OPCODE_EQ:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EQ\n");
#endif
            AddComparision(psContext, psInst, CMP_EQ);
			break;
		}
		case OPCODE_USHR:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//USHR\n");
#endif
			CallBinaryOp(psContext, ">>", psInst, 0, 1, 2, TO_FLAG_UNSIGNED_INTEGER);
			break;
		}
		case OPCODE_ISHL:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ISHL\n");
#endif
			CallBinaryOp(psContext, "<<", psInst, 0, 1, 2, TO_FLAG_INTEGER);
			break;
		}
		case OPCODE_ISHR:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ISHR\n");
#endif
			CallBinaryOp(psContext, ">>", psInst, 0, 1, 2, TO_FLAG_INTEGER);
			break;
		}
		case OPCODE_LD:
		case OPCODE_LD_MS:
		{
			ResourceBinding* psBinding = 0;
			uint32_t dstSwizCount = GetNumSwizzleElements(&psInst->asOperands[0]);
#ifdef _DEBUG
            AddIndentation(psContext);
            if(psInst->eOpcode == OPCODE_LD)
                bcatcstr(glsl, "//LD\n");
            else
                bcatcstr(glsl, "//LD_MS\n");
#endif

            GetResourceFromBindingPoint(RTYPE_TEXTURE, psInst->asOperands[2].ui32RegisterNumber, &psContext->psShader->sInfo, &psBinding);

			switch(psBinding->eDimension)
			{
				case REFLECT_RESOURCE_DIMENSION_TEXTURE1D:
				case REFLECT_RESOURCE_DIMENSION_TEXTURE1DARRAY:
				{
					//texelFetch(samplerBuffer, int coord, level)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", int((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").x), 0)");
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, ";\n");
					break;
				}
				case REFLECT_RESOURCE_DIMENSION_TEXTURE2DARRAY:
				case REFLECT_RESOURCE_DIMENSION_TEXTURE3D:
				{
					//texelFetch(samplerBuffer, ivec3 coord, level)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", ivec3((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").xyz), 0)");
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, ";\n");
					break;
				}
				case REFLECT_RESOURCE_DIMENSION_TEXTURE2D:
				{
					//texelFetch(samplerBuffer, ivec2 coord, level)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", ivec2((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").xy), 0)");
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, ";\n");
					break;
				}
				case REFLECT_RESOURCE_DIMENSION_BUFFER:
				{
					//texelFetch(samplerBuffer, scalar integer coord)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", int((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").x))");
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, ";\n");
					break;
				}
				case REFLECT_RESOURCE_DIMENSION_TEXTURE2DMS:
				{
					//texelFetch(samplerBuffer, ivec2 coord, sample)

                    ASSERT(psInst->eOpcode == OPCODE_LD_MS);

					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", ivec2((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").xy), ");
                    TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
                    bcatcstr(glsl, ")");
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, ";\n");
					break;
				}
				case REFLECT_RESOURCE_DIMENSION_TEXTURE2DMSARRAY:
				{
					//texelFetch(samplerBuffer, ivec3 coord, sample)

                    ASSERT(psInst->eOpcode == OPCODE_LD_MS);

					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", ivec3((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").xyz), ");
                    TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
                    bcatcstr(glsl, ")");
					TranslateOperandSwizzle(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, ";\n");
					break;
				}
				case REFLECT_RESOURCE_DIMENSION_TEXTURECUBE:
				case REFLECT_RESOURCE_DIMENSION_TEXTURECUBEARRAY:
				case REFLECT_RESOURCE_DIMENSION_BUFFEREX:
				default:
				{
					break;
				}
			}
			break;
		}
		case OPCODE_DISCARD:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//DISCARD\n");
#endif
            AddIndentation(psContext);
			if(psContext->psShader->ui32MajorVersion <= 3)
			{
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
			}
            else if(psInst->eBooleanTestType == INSTRUCTION_TEST_ZERO)
            {
                bcatcstr(glsl, "if((");
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
                bcatcstr(glsl, ")==0){discard;}\n");
            }
            else
            {
                ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
                bcatcstr(glsl, "if((");
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
                bcatcstr(glsl, ")!=0){discard;}\n");
            }
			break;
		}
        case OPCODE_LOD:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LOD\n");
#endif
            //LOD computes the following vector (ClampedLOD, NonClampedLOD, 0, 0)

            MaskOutTexCoordComponents(psContext->psShader->aeResourceDims[psInst->asOperands[2].ui32RegisterNumber],
                &psInst->asOperands[1]);

            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = textureQueryLOD(");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ",");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ")");

            //The swizzle on srcResource allows the returned values to be swizzled arbitrarily before they are written to the destination.

            // iWriteMaskEnabled is forced off during DecodeOperand because swizzle on sampler uniforms
            // does not make sense. But need to re-enable to correctly swizzle this particular instruction.
            psInst->asOperands[2].iWriteMaskEnabled = 1;
            TranslateOperandSwizzle(psContext, &psInst->asOperands[2]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_EVAL_CENTROID:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EVAL_CENTROID\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = interpolateAtCentroid(");
            //interpolateAtCentroid accepts in-qualified variables.
            //As long as bytecode only writes vX registers in declarations
            //we should be able to use the declared name directly.
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_DECLARATION_NAME);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_EVAL_SAMPLE_INDEX:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EVAL_SAMPLE_INDEX\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = interpolateAtSample(");
            //interpolateAtSample accepts in-qualified variables.
            //As long as bytecode only writes vX registers in declarations
            //we should be able to use the declared name directly.
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_DECLARATION_NAME);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_INTEGER);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_EVAL_SNAPPED:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//EVAL_SNAPPED\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = interpolateAtOffset(");
            //interpolateAtOffset accepts in-qualified variables.
            //As long as bytecode only writes vX registers in declarations
            //we should be able to use the declared name directly.
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_DECLARATION_NAME);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_INTEGER);
            bcatcstr(glsl, ".xy);\n");
            break;
        }
        case OPCODE_LD_UAV_TYPED:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LD_UAV_TYPED\n");
#endif

            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = imageLoad(");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NAME_ONLY);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(psContext, &psInst->asOperands[2]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_STORE_UAV_TYPED:
        {
            break;
        }
        case OPCODE_LD_RAW:
        case OPCODE_STORE_RAW:
        case OPCODE_LD_STRUCTURED:
        case OPCODE_STORE_STRUCTURED:
        {
            break;
        }
        case OPCODE_ATOMIC_CMP_STORE:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ATOMIC_CMP_STORE\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = atomicCompSwap(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
            break;
        }
        case OPCODE_ATOMIC_AND:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ATOMIC_AND\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = atomicAnd(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_ATOMIC_IADD:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ATOMIC_IADD\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = atomicAdd(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_ATOMIC_OR:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ATOMIC_OR");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = atomicOr(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_ATOMIC_XOR:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ATOMIC_XOR\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = atomicXor(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_ATOMIC_IMAX:
        case OPCODE_ATOMIC_UMAX:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            if(psInst->eOpcode == OPCODE_ATOMIC_IMAX)
                bcatcstr(glsl, "//OPCODE_ATOMIC_IMAX\n");
            else
                bcatcstr(glsl, "//OPCODE_ATOMIC_UMAX\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = atomicMax(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_ATOMIC_IMIN:
        case OPCODE_ATOMIC_UMIN:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            if(psInst->eOpcode == OPCODE_ATOMIC_IMIN)
                bcatcstr(glsl, "//OPCODE_ATOMIC_IMIN\n");
            else
                bcatcstr(glsl, "//OPCODE_ATOMIC_UMIN\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = atomicMin(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_UBFE:
        case OPCODE_IBFE:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            if(psInst->eOpcode == OPCODE_UBFE)
                bcatcstr(glsl, "//OPCODE_UBFE\n");
            else
                bcatcstr(glsl, "//OPCODE_IBFE\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
            bcatcstr(glsl, " = bitfieldExtract(");
            TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
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
        case OPCODE_F32TOF16:
        {
            const uint32_t destElemCount = GetNumSwizzleElements(&psInst->asOperands[0]);
            const uint32_t s0ElemCount = GetNumSwizzleElements(&psInst->asOperands[1]);
            uint32_t destElem;
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//F32TOF16\n");
#endif
            for(destElem=0; destElem < destElemCount; ++destElem)
            {
                const char* swizzle[] = {".x", ".y", ".z", ".w"};

                //unpackHalf2x16 converts two f16s packed into uint to two f32s.

                //dest.swiz.x = unpackHalf2x16(src.swiz.x).x
                //dest.swiz.y = unpackHalf2x16(src.swiz.y).x
                //dest.swiz.z = unpackHalf2x16(src.swiz.z).x
                //dest.swiz.w = unpackHalf2x16(src.swiz.w).x

                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION);
                if(destElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);

                bcatcstr(glsl, " = unpackHalf2x16(");
                TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_UNSIGNED_INTEGER);
                if(s0ElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);
                bcatcstr(glsl, ").x;\n");

            }
            break;
        }
        case OPCODE_F16TOF32:
        {
            const uint32_t destElemCount = GetNumSwizzleElements(&psInst->asOperands[0]);
            const uint32_t s0ElemCount = GetNumSwizzleElements(&psInst->asOperands[1]);
            uint32_t destElem;
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//F16TOF32\n");
#endif
            for(destElem=0; destElem < destElemCount; ++destElem)
            {
                const char* swizzle[] = {".x", ".y", ".z", ".w"};

                //packHalf2x16 converts two f32s to two f16s packed into a uint.

                //dest.swiz.x = packHalf2x16(vec2(src.swiz.x)) & 0xFFFF
                //dest.swiz.y = packHalf2x16(vec2(src.swiz.y)) & 0xFFFF
                //dest.swiz.z = packHalf2x16(vec2(src.swiz.z)) & 0xFFFF
                //dest.swiz.w = packHalf2x16(vec2(src.swiz.w)) & 0xFFFF

                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION|TO_FLAG_UNSIGNED_INTEGER);
                if(destElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);

                bcatcstr(glsl, " = packHalf2x16(vec2(");
                TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
                if(s0ElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);
                bcatcstr(glsl, ")) & 0xFFFF;\n");

            }
            break;
        }
        case OPCODE_INEG:
		{
#ifdef _DEBUG
			AddIndentation(psContext);
			bcatcstr(glsl, "//INEG\n");
#endif
			//dest = 0 - src0
			AddIndentation(psContext);
			TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_DESTINATION|TO_FLAG_INTEGER);
			bcatcstr(glsl, " = 0 - ");
			TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE|TO_FLAG_INTEGER);
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

        case OPCODE_SWAPC:
        case OPCODE_IMM_ATOMIC_ALLOC:
        case OPCODE_IMM_ATOMIC_CONSUME:
        case OPCODE_IMM_ATOMIC_IADD:
        case OPCODE_IMM_ATOMIC_AND:
        case OPCODE_IMM_ATOMIC_OR:
        case OPCODE_IMM_ATOMIC_XOR:
        case OPCODE_IMM_ATOMIC_EXCH:
        case OPCODE_IMM_ATOMIC_CMP_EXCH:
        case OPCODE_IMM_ATOMIC_IMAX:
        case OPCODE_IMM_ATOMIC_IMIN:
        case OPCODE_IMM_ATOMIC_UMAX:
        case OPCODE_IMM_ATOMIC_UMIN:
        case OPCODE_DADD:
        case OPCODE_DMAX:
        case OPCODE_DMIN:
        case OPCODE_DMUL:
        case OPCODE_DEQ:
        case OPCODE_DGE:
        case OPCODE_DLT:
        case OPCODE_DNE:
        case OPCODE_DMOV:
        case OPCODE_DMOVC:
        case OPCODE_DTOF:
        case OPCODE_FTOD:
        case OPCODE_DDIV:
        case OPCODE_DFMA:
        case OPCODE_DRCP:
        case OPCODE_MSAD:
        case OPCODE_DTOI:
        case OPCODE_DTOU:
        case OPCODE_ITOD:
        case OPCODE_UTOD:
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

static int IsIntegerOpcode(OPCODE_TYPE eOpcode)
{
    switch(eOpcode)
    {
        case OPCODE_IADD:
        case OPCODE_IF:
        case OPCODE_IEQ:
        case OPCODE_IGE:
        case OPCODE_ILT:
        case OPCODE_IMAD:
        case OPCODE_IMAX:
        case OPCODE_IMIN:
        case OPCODE_IMUL:
        case OPCODE_INE:
        case OPCODE_INEG:
        case OPCODE_ISHL:
        case OPCODE_ISHR:
        case OPCODE_ITOF:
        {
            return 1;
        }
        default:
        {
            return 0;
        }
    }
}

int InstructionUsesRegister(const Instruction* psInst, const Operand* psOperand)
{
    uint32_t operand;
    for(operand=0; operand < psInst->ui32NumOperands; ++operand)
    {
        if(psInst->asOperands[operand].eType == psOperand->eType)
        {
            if(psInst->asOperands[operand].ui32RegisterNumber == psOperand->ui32RegisterNumber)
            {
                if(CompareOperandSwizzles(&psInst->asOperands[operand], psOperand))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void MarkIntegerImmediates(HLSLCrossCompilerContext* psContext)
{
    const uint32_t count = psContext->psShader->ui32InstCount;
    Instruction* psInst = psContext->psShader->psInst;
    uint32_t i;

    for(i=0; i < count;)
    {
        if(psInst[i].eOpcode == OPCODE_MOV && psInst[i].asOperands[1].eType == OPERAND_TYPE_IMMEDIATE32 &&
            psInst[i].asOperands[0].eType == OPERAND_TYPE_TEMP)
        {
            uint32_t k;

            for(k=i+1; k < count; ++k)
            {
                if(psInst[k].eOpcode == OPCODE_ILT)
                {
                    k = k;
                }
                if(InstructionUsesRegister(&psInst[k], &psInst[i].asOperands[0]))
                {
                    if(IsIntegerOpcode(psInst[k].eOpcode))
                    {
                        psInst[i].asOperands[1].iIntegerImmediate = 1;
                    }

                    goto next_iteration;
                }
            }
        }
next_iteration:
        ++i;
    }
}
