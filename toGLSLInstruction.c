#include "toGLSLInstruction.h"
#include "toGLSLOperand.h"
#include "bstrlib.h"
#include "stdio.h"
#include "debug.h"

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
    bstring glsl = psContext->glsl;
    const uint32_t destElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[0]);
    const uint32_t s0ElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[1]);
    const uint32_t s1ElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[2]);

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
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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

static void AddEqual(HLSLCrossCompilerContext* psContext, Instruction* psInst)
{
    bstring glsl = psContext->glsl;
    const uint32_t destElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[0]);
    const uint32_t s0ElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[1]);
    const uint32_t s1ElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[2]);

    uint32_t minElemCount = destElemCount < s0ElemCount ? destElemCount : s0ElemCount;

    minElemCount = s1ElemCount < minElemCount ? s1ElemCount : minElemCount;

    if(destElemCount > 1)
    {
        //Component-wise compare
        AddIndentation(psContext);
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
        bformata(glsl, " = vec%d(equal((", minElemCount);
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
        //Scalar compare
        AddIndentation(psContext);
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
        bcatcstr(glsl, " = ((");
        TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
        bcatcstr(glsl, ")");
        if(s0ElemCount > minElemCount)
            AddSwizzleUsingElementCount(psContext, minElemCount);
        bcatcstr(glsl, "== (");
        TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
        bcatcstr(glsl, ")");
        if(s1ElemCount > minElemCount)
            AddSwizzleUsingElementCount(psContext, minElemCount);
        bcatcstr(glsl, ") ? 1 : 0;\n");
    }
}

void CallHLSLOpcodeFunc1(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = psContext->glsl;

    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc2(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc3(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_INTEGER);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_INTEGER);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_INTEGER);
    bcatcstr(glsl, ");\n");
}

void CallBinaryOp(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = psContext->glsl;
	uint32_t src1SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src1]);
	uint32_t src0SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src0]);
	uint32_t dstSwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[dest]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_NONE);
		bcatcstr(glsl, " = ");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
		bformata(glsl, " %s ", name);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE);
		bcatcstr(glsl, ";\n");
	}
	else
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_NONE);
		bcatcstr(glsl, " = vec4(");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
		bformata(glsl, " %s ", name);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE);
		bcatcstr(glsl, ")");
		//Limit src swizzles based on dest swizzle
		//e.g. given hlsl asm: add r0.xy, v0.xyxx, l(0.100000, 0.000000, 0.000000, 0.000000)
		//the two sources must become vec2
		//Temp0.xy = Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000);
		//becomes
		//Temp0.xy = vec4(Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000)).xy;
		AddSwizzleUsingElementCount(psContext, dstSwizCount);
		bcatcstr(glsl, ";\n");
	}
}

void CallIntegerBinaryOp(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = psContext->glsl;
	uint32_t src1SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src1]);
	uint32_t src0SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src0]);
	uint32_t dstSwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[dest]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_INTEGER);
		bcatcstr(glsl, " = int(");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_INTEGER);
		bformata(glsl, ") %s int(", name);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_INTEGER);
		bcatcstr(glsl, ");\n");
	}
	else
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_INTEGER);
		bcatcstr(glsl, " = vec4(int(");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_INTEGER);
		bformata(glsl, ") %s int(", name);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_INTEGER);
		bcatcstr(glsl, "))");
		AddSwizzleUsingElementCount(psContext, dstSwizCount);
		bcatcstr(glsl, ";\n");
	}
}

void CallUnsignedIntegerBinaryOp(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = psContext->glsl;
	uint32_t src1SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src1]);
	uint32_t src0SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src0]);
	uint32_t dstSwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[dest]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_INTEGER);
		bcatcstr(glsl, " = uint(");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_INTEGER);
		bformata(glsl, ") %s uint(", name);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_INTEGER);
		bcatcstr(glsl, ");\n");
	}
	else
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_INTEGER);
		bcatcstr(glsl, " = vec4(uint(");
		TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_INTEGER);
		bformata(glsl, ") %s uint(", name);
		TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_INTEGER);
		bcatcstr(glsl, "))");
		AddSwizzleUsingElementCount(psContext, dstSwizCount);
		bcatcstr(glsl, ";\n");
	}
}

void CallTernaryOp(HLSLCrossCompilerContext* psContext, const char* op1, const char* op2, Instruction* psInst, 
 int dest, int src0, int src1, int src2)
{
    bstring glsl = psContext->glsl;
	uint32_t src2SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src2]);
	uint32_t src1SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src1]);
	uint32_t src0SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[src0]);
	uint32_t dstSwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[dest]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == src2SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_NONE);
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
		TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_NONE);
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
		AddSwizzleUsingElementCount(psContext, dstSwizCount);
		bcatcstr(glsl, ";\n");
	}
}

void CallHelper3(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1, int src2)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_NONE);

	bcatcstr(glsl, " = vec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src2], TO_FLAG_NONE);
    bcatcstr(glsl, "))");
    AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[dest]));
    bcatcstr(glsl, ";\n");
}

void CallHelper2(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_NONE);

	bcatcstr(glsl, " = vec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_NONE);
    bcatcstr(glsl, "))");
    AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[dest]));
    bcatcstr(glsl, ";\n");
}

void CallHelper2UInt(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_NONE);

	bcatcstr(glsl, " = uvec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(uint(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_INTEGER);
    bcatcstr(glsl, "), uint(");
    TranslateOperand(psContext, &psInst->asOperands[src1], TO_FLAG_INTEGER);
    bcatcstr(glsl, ")))");
    AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[dest]));
    bcatcstr(glsl, ";\n");
}

void CallHelper1(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest], TO_FLAG_NONE);

	bcatcstr(glsl, " = vec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0], TO_FLAG_NONE);
    bcatcstr(glsl, "))");
    AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[dest]));
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
static void TranslateTextureSample(HLSLCrossCompilerContext* psContext, Instruction* psInst,
    uint32_t ui32Flags)
{
    bstring glsl = psContext->glsl;

    const char* funcName = "";
    const char* coordType = "";

    const RESOURCE_DIMENSION eResDim = psContext->psShader->aeResourceDims[psInst->asOperands[2].ui32RegisterNumber];

    ASSERT(psInst->asOperands[2].ui32RegisterNumber < MAX_TEXTURES);

    MaskOutTexCoordComponents(eResDim, &psInst->asOperands[1]);

    switch(eResDim)
    {
        case RESOURCE_DIMENSION_TEXTURE1D:
        {
            coordType = "vec2";
            funcName = "texture1D";
            if(ui32Flags & TEXSMP_FLAG_DEPTHCOMPARE)
            {
                funcName = "shadow1D";
            }
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE2D:
        {
            coordType = "vec3";
            funcName = "texture2D";
            if(ui32Flags & TEXSMP_FLAG_DEPTHCOMPARE)
            {
                funcName = "shadow2D";
            }
            break;
        }
        case RESOURCE_DIMENSION_TEXTURECUBE:
        {
            coordType = "vec3";
            funcName = "textureCube";
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE3D:
        {
            coordType = "vec4";
            funcName = "texture3D";
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE1DARRAY:
        {
            coordType = "vec3";
            funcName = "texture";
            break;
        }
        case RESOURCE_DIMENSION_TEXTURE2DARRAY:
        {
            coordType = "vec4";
            funcName = "texture";
            break;
        }
        case RESOURCE_DIMENSION_TEXTURECUBEARRAY:
        {
            funcName = "texture";

            if(ui32Flags & TEXSMP_FLAG_DEPTHCOMPARE)
            {
                //Special. Reference is a separate argument.
			    AddIndentation(psContext);
			    TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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

                AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[0]));
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
		TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);

        if(ui32Flags & (TEXSMP_FLAG_LOD|TEXSMP_FLAG_FIRSTLOD))
        {
            bformata(glsl, " =(vec4(%sLod(", funcName);
        }
        else
        {
            bformata(glsl, " =(vec4(%s(", funcName);
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
        TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
        if(ui32Flags & (TEXSMP_FLAG_LOD|TEXSMP_FLAG_FIRSTLOD))
        {
            bformata(glsl, " = (%sLod(", funcName);
        }
        else
        {
            bformata(glsl, " = (%s(", funcName);
        }
        TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);//resource
        bcatcstr(glsl, ", ");
        TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);//texcoord

        if(ui32Flags & TEXSMP_FLAG_LOD)
        {
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_NONE);//lod
        }
        if(ui32Flags & TEXSMP_FLAG_FIRSTLOD)
        {
            bcatcstr(glsl, ", 0");
        }

        bcatcstr(glsl, ")");
    }

    // iWriteMaskEnabled is forced off during DecodeOperand because swizzle on sampler uniforms
    // does not make sense. But need to re-enable to correctly swizzle this particular instruction.
    psInst->asOperands[2].iWriteMaskEnabled = 1;
    TranslateOperandSwizzle(psContext, &psInst->asOperands[2]);
    bcatcstr(glsl, ")");

    AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[0]));
    bcatcstr(glsl, ";\n");
}


void TranslateInstruction(HLSLCrossCompilerContext* psContext, Instruction* psInst)
{
    bstring glsl = psContext->glsl;
    switch(psInst->eOpcode)
    {
        case OPCODE_FTOI:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//FTOI.  Use a MOV for now\n");
#endif
            // Rounding is always performed towards zero
            //Use int constructor - int(float). This drops the fractional part.
        }
		case OPCODE_FTOU:
		{
#ifdef _DEBUG
            if(psInst->eOpcode == OPCODE_FTOU) //Check for fallthrough from OPCODE_FTOI
            {
                AddIndentation(psContext);
                bcatcstr(glsl, "//FTOU. Use a MOV for now\n");
            }
#endif
		}
        case OPCODE_MOV:
        {
			uint32_t srcCount = GetNumSwizzleElements(psContext, &psInst->asOperands[1]);
			uint32_t dstCount = GetNumSwizzleElements(psContext, &psInst->asOperands[0]);
			int intCast = 0;

			if(psInst->asOperands[0].eType == OPERAND_TYPE_OUTPUT)
			{
				if(psContext->psShader->abScalarOutput[psInst->asOperands[0].ui32RegisterNumber])
				{
					intCast = 1;
				}
			}
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//MOV\n");
#endif
			AddIndentation(psContext);

			if(srcCount == dstCount)
			{
				TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
				bcatcstr(glsl, " = ");
				if(intCast)
				{
					bcatcstr(glsl, "int(");
				}
				TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
				if(intCast)
				{
					bcatcstr(glsl, ")");
				}
				bcatcstr(glsl, ";\n");
			}
			else
			{
				TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
				bcatcstr(glsl, " = vec4(");
				TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
				bcatcstr(glsl, ")");
				AddSwizzleUsingElementCount(psContext, dstCount);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, " = vec4(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, " = vec4(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
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
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IADD\n");
#endif
			CallIntegerBinaryOp(psContext, "+", psInst, 0, 1, 2);
            break;
        }
        case OPCODE_ADD:
        {

#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ADD\n");
#endif
			CallBinaryOp(psContext, "+", psInst, 0, 1, 2);
            break;
        }
        case OPCODE_OR:
        {
            /*Todo: vector version */
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//OR\n");
#endif
			CallIntegerBinaryOp(psContext, "|", psInst, 0, 1, 2);
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
			CallBinaryOp(psContext, "*", psInst, 0, 1, 2);
            break;
        }
        case OPCODE_IMUL:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IMUL\n");
#endif
			CallBinaryOp(psContext, "*", psInst, 0, 1, 2);
            break;
        }
        case OPCODE_UDIV:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//UDIV\n");
#endif
			//destQuotient, destRemainder, src0, src1
			CallUnsignedIntegerBinaryOp(psContext, "/", psInst, 0, 2, 3);
			CallHelper2UInt(psContext, "mod", psInst, 1, 2, 3);
            break;
        }
        case OPCODE_DIV:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//DIV\n");
#endif
			CallBinaryOp(psContext, "/", psInst, 0, 1, 2);
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
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);//Dest sin
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, " = dot((");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ").xy, (");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ").xy);\n");
            break;
        }
        case OPCODE_DP3:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//DP3\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, " = dot((");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ").xyz, (");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ").xyz);\n");
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
        case OPCODE_MOVC:
        {
            const uint32_t destElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[0]);
            const uint32_t s0ElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[1]);
            const uint32_t s1ElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[2]);
            const uint32_t s2ElemCount = GetNumSwizzleElements(psContext, &psInst->asOperands[3]);
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
            for(destElem=0; destElem < destElemCount; ++destElem)
            {
                const char* swizzle[] = {".x", ".y", ".z", ".w"};

                AddIndentation(psContext);
                bcatcstr(glsl, "if(");
                TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
                if(s0ElemCount>1)
                    bcatcstr(glsl, swizzle[destElem]);
                bcatcstr(glsl, " != 0) {\n");

                psContext->indent++;
                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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
                TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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

            AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[0]));
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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

            AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[0]));
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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

            AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[0]));
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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

            AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[0]));
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
		case OPCODE_RET:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//RET\n");
#endif
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
            --psContext->indent;
            AddIndentation(psContext);
            bcatcstr(glsl, "}\n"); //Closing brace ends the previous function.
            AddIndentation(psContext);

            bcatcstr(glsl, "subroutine(SubroutineType)\n");
            bcatcstr(glsl, "void ");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, "(){\n");
            ++psContext->indent;
            break;
        }
        case OPCODE_COUNTBITS:
        {
            bcatcstr(glsl, "bitCount(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_HI:
        {
            bcatcstr(glsl, "findMSB(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_LO:
        {
            bcatcstr(glsl, "findLSB(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_SHI:
        {
            bcatcstr(glsl, "findMSB(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_BFREV:
        {
            bcatcstr(glsl, "bitfieldReverse(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_BFI:
        {
            //FIXME
/*src0
[in] The bitfield width to take from src2.
src1
[in] The bitfield offset for replacing bits in src3.
src2
[in] The number the bits are taken from.
src3
[in] The number with bits to be replaced.
*/
            /*
            glsl:
            base, instert, offset, bits
            */
            bcatcstr(glsl, "bitfieldInsert(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[3], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[4], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[5], TO_FLAG_NONE);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
			bcatcstr(glsl, "EndStreamPrimitive(");
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, ");\n");
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
            break;
        }
        case OPCODE_IF:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IF\n");
#endif
            AddIndentation(psContext);
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
			CallUnsignedIntegerBinaryOp(psContext, ">>", psInst, 0, 1, 2);
			break;
		}
		case OPCODE_ISHL:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ISHL\n");
#endif
			CallIntegerBinaryOp(psContext, "<<", psInst, 0, 1, 2);
			break;
		}
		case OPCODE_ISHR:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ISHR\n");
#endif
			CallIntegerBinaryOp(psContext, ">>", psInst, 0, 1, 2);
			break;
		}
		case OPCODE_LD:
		{
			ResourceBinding* psBinding = 0;
			uint32_t dstSwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[0]);
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LD\n");
#endif

            
            GetResourceFromBindingPoint(RTYPE_TEXTURE, psInst->asOperands[2].ui32RegisterNumber, &psContext->psShader->sInfo, &psBinding);

			switch(psBinding->eDimension)
			{
				case RESOURCE_DIMENSION_TEXTURE1D:
				case RESOURCE_DIMENSION_TEXTURE1DARRAY:
				{
					//texelFetch(samplerBuffer, int coord, level)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", int((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").x), 0)");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_TEXTURE2DARRAY:
				case RESOURCE_DIMENSION_TEXTURE3D:
				{
					//texelFetch(samplerBuffer, ivec3 coord, level)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", ivec3((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").xyz), 0)");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_TEXTURE2D:
				{
					//texelFetch(samplerBuffer, ivec2 coord, level)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", ivec2((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").xy), 0)");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_BUFFER:
				{
					//texelFetch(samplerBuffer, scalar integer coord)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", int((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").x))");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_TEXTURE2DMS:
				{
					//texelFetch(samplerBuffer, ivec2 coord, sample)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", ivec2((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").xy), 0)");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_TEXTURE2DMSARRAY:
				{
					//texelFetch(samplerBuffer, ivec3 coord, sample)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_NONE);
					bcatcstr(glsl, ", ivec3((");
					TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
					bcatcstr(glsl, ").xyz), 0)");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_TEXTURECUBE:
				case RESOURCE_DIMENSION_TEXTURECUBEARRAY:
				case RESOURCE_DIMENSION_RAW_BUFFER:
				case RESOURCE_DIMENSION_STRUCTURED_BUFFER:
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
            if(psInst->eBooleanTestType == INSTRUCTION_TEST_ZERO)
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, " = interpolateAtCentroid(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, " = interpolateAtSample(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
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
            TranslateOperand(psContext, &psInst->asOperands[0], TO_FLAG_NONE);
            bcatcstr(glsl, " = interpolateAtOffset(");
            TranslateOperand(psContext, &psInst->asOperands[1], TO_FLAG_NONE);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2], TO_FLAG_INTEGER);
            bcatcstr(glsl, ".xy);\n");
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
