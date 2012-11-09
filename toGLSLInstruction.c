#include "toGLSLInstruction.h"
#include "toGLSLOperand.h"
#include "bstrlib.h"
#include "stdio.h"

#include <assert.h>
#define ASSERT(x) assert(x)

extern void AddIndentation(HLSLCrossCompilerContext* psContext);

void CallHLSLOpcodeFunc1(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = psContext->glsl;

    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1]);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc2(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[2]);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc3(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[1]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[2]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[3]);
    bcatcstr(glsl, ");\n");
}

void CallBinaryOp(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = psContext->glsl;
	uint32_t src1SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[2]);
	uint32_t src0SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[1]);
	uint32_t dstSwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[0]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest]);
		bcatcstr(glsl, " = ");
		TranslateOperand(psContext, &psInst->asOperands[src0]);
		bformata(glsl, " %s ", name);
		TranslateOperand(psContext, &psInst->asOperands[src1]);
		bcatcstr(glsl, ";\n");
	}
	else
	{
		TranslateOperand(psContext, &psInst->asOperands[dest]);
		bcatcstr(glsl, " = vec4(");
		TranslateOperand(psContext, &psInst->asOperands[src0]);
		bformata(glsl, " %s ", name);
		TranslateOperand(psContext, &psInst->asOperands[src1]);
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
	uint32_t src1SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[2]);
	uint32_t src0SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[1]);
	uint32_t dstSwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[0]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == dstSwizCount)
	{
		TranslateIntegerOperand(psContext, &psInst->asOperands[dest]);
		bcatcstr(glsl, " = int(");
		TranslateIntegerOperand(psContext, &psInst->asOperands[src0]);
		bformata(glsl, ") %s int(", name);
		TranslateIntegerOperand(psContext, &psInst->asOperands[src1]);
		bcatcstr(glsl, ");\n");
	}
	else
	{
		TranslateIntegerOperand(psContext, &psInst->asOperands[dest]);
		bcatcstr(glsl, " = vec4(int(");
		TranslateIntegerOperand(psContext, &psInst->asOperands[src0]);
		bformata(glsl, ") %s int(", name);
		TranslateIntegerOperand(psContext, &psInst->asOperands[src1]);
		bcatcstr(glsl, "))");
		AddSwizzleUsingElementCount(psContext, dstSwizCount);
		bcatcstr(glsl, ";\n");
	}
}

void CallTernaryOp(HLSLCrossCompilerContext* psContext, const char* op1, const char* op2, Instruction* psInst, 
 int dest, int src0, int src1, int src2)
{
    bstring glsl = psContext->glsl;
	uint32_t src2SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[3]);
	uint32_t src1SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[2]);
	uint32_t src0SwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[1]);
	uint32_t dstSwizCount = GetNumSwizzleElements(psContext, &psInst->asOperands[0]);

    AddIndentation(psContext);

	if(src1SwizCount == src0SwizCount == src2SwizCount == dstSwizCount)
	{
		TranslateOperand(psContext, &psInst->asOperands[dest]);
		bcatcstr(glsl, " = ");
		TranslateOperand(psContext, &psInst->asOperands[src0]);
		bformata(glsl, " %s ", op1);
		TranslateOperand(psContext, &psInst->asOperands[src1]);
		bformata(glsl, " %s ", op2);
		TranslateOperand(psContext, &psInst->asOperands[src2]);
		bcatcstr(glsl, ";\n");
	}
	else
	{
		TranslateOperand(psContext, &psInst->asOperands[dest]);
		bcatcstr(glsl, " = vec4(");
		TranslateOperand(psContext, &psInst->asOperands[src0]);
		bformata(glsl, " %s ", op1);
		TranslateOperand(psContext, &psInst->asOperands[src1]);
		bformata(glsl, " %s ", op2);
		TranslateOperand(psContext, &psInst->asOperands[src2]);
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

	TranslateOperand(psContext, &psInst->asOperands[dest]);

	bcatcstr(glsl, " = vec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src1]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src2]);
    bcatcstr(glsl, "))");
    AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[dest]));
    bcatcstr(glsl, ";\n");
}

void CallHelper2(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0, int src1)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest]);

	bcatcstr(glsl, " = vec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(psContext, &psInst->asOperands[src1]);
    bcatcstr(glsl, "))");
    AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[dest]));
    bcatcstr(glsl, ";\n");
}

void CallHelper1(HLSLCrossCompilerContext* psContext, const char* name, Instruction* psInst, 
 int dest, int src0)
{
    bstring glsl = psContext->glsl;
    AddIndentation(psContext);

	TranslateOperand(psContext, &psInst->asOperands[dest]);

	bcatcstr(glsl, " = vec4(");

    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(psContext, &psInst->asOperands[src0]);
    bcatcstr(glsl, "))");
    AddSwizzleUsingElementCount(psContext, GetNumSwizzleElements(psContext, &psInst->asOperands[dest]));
    bcatcstr(glsl, ";\n");
}

void TranslateInstruction(HLSLCrossCompilerContext* psContext, Instruction* psInst)
{
    bstring glsl = psContext->glsl;
    switch(psInst->eOpcode)
    {
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
				TranslateOperand(psContext, &psInst->asOperands[0]);
				bcatcstr(glsl, " = ");
				if(intCast)
				{
					bcatcstr(glsl, "int(");
				}
				TranslateOperand(psContext, &psInst->asOperands[1]);
				if(intCast)
				{
					bcatcstr(glsl, ")");
				}
				bcatcstr(glsl, ";\n");
			}
			else
			{
				TranslateOperand(psContext, &psInst->asOperands[0]);
				bcatcstr(glsl, " = vec4(");
				TranslateOperand(psContext, &psInst->asOperands[1]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, " = vec4(");
            TranslateOperand(psContext, &psInst->asOperands[1]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, " = vec4(");
            TranslateOperand(psContext, &psInst->asOperands[1]);
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
            CallHLSLOpcodeFunc2(psContext, "HLSL_ge", psInst);
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
                TranslateOperand(psContext, &psInst->asOperands[0]);//Dest sin
                bcatcstr(glsl, " = sin(");
                TranslateOperand(psContext, &psInst->asOperands[2]);//angle
                bcatcstr(glsl, ");\n");
            }

            if(psInst->asOperands[1].eType != OPERAND_TYPE_NULL)
            {
                AddIndentation(psContext);
                TranslateOperand(psContext, &psInst->asOperands[1]);//Dest cos
                bcatcstr(glsl, " = cos(");
                TranslateOperand(psContext, &psInst->asOperands[2]);//angle
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, " = dot((");
            TranslateOperand(psContext, &psInst->asOperands[1]);
            bcatcstr(glsl, ").xy, (");
            TranslateOperand(psContext, &psInst->asOperands[2]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, " = dot((");
            TranslateOperand(psContext, &psInst->asOperands[1]);
            bcatcstr(glsl, ").xyz, (");
            TranslateOperand(psContext, &psInst->asOperands[2]);
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
        case OPCODE_NE:
        {
            //Scalar version. Use any() for vector with scalar 1
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//NE\n");
#endif
            AddIndentation(psContext);
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, " = (");
            TranslateOperand(psContext, &psInst->asOperands[1]);
            bcatcstr(glsl, " != ");
            TranslateOperand(psContext, &psInst->asOperands[2]);
            bcatcstr(glsl, ") ? 1 : 0;\n");
            break;
        }
        case OPCODE_IGE:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IGE\n");
#endif
            CallHLSLOpcodeFunc2(psContext, "HLSL_ige", psInst);
            break;
        }
        case OPCODE_LT:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//LT\n");
#endif
            CallHLSLOpcodeFunc2(psContext, "HLSL_lt", psInst);
            break;
        }
        case OPCODE_IEQ:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//IEQ\n");
#endif
            CallHLSLOpcodeFunc2(psContext, "HLSL_ieq", psInst);
            break;
        }
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
            AddIndentation(psContext);
            bcatcstr(glsl, "//FTOU. Use a MOV for now\n");
#endif
		}
        case OPCODE_MOVC:
        {
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//MOVC\n");
#endif
            CallHLSLOpcodeFunc1(psContext, "HLSL_movc", psInst);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, " = textureGather(");

            TranslateOperand(psContext, &psInst->asOperands[2]);
            bcatcstr(glsl, ", ");
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[1].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[1].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(psContext, &psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_SAMPLE:
        {
            //dest, coords, tex, sampler
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SAMPLE\n");
#endif
            AddIndentation(psContext);//1=temp??
            TranslateOperand(psContext, &psInst->asOperands[0]);//??
            bcatcstr(glsl, " = texture2D(");

            TranslateOperand(psContext, &psInst->asOperands[2]);//resource
            bcatcstr(glsl, ", ");
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[1].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[1].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(psContext, &psInst->asOperands[1]);//in
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_SAMPLE_L:
        {
            //dest, coords, tex, sampler, lod

			

#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//SAMPLE_L\n");
#endif
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[1].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[1].aui32Swizzle[3] = 0xFFFFFFFF;
			CallHelper3(psContext, "texture2DLod", psInst, 0, 2, 1, 4);

            /*AddIndentation(psContext);
            bcatcstr(glsl, "HLSL_sample_l");
            bcatcstr(glsl, "(");
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2]);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[4]);
            bcatcstr(glsl, ");\n");*/
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
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//INTERFACE_CALL\n");
#endif
            AddIndentation(psContext);
            bformata(glsl, "InterfaceVar%d();\n", psInst->ui32FunctionIDToCall);
            break;
        }
        case OPCODE_LABEL:
        {
            uint32_t funcID = psInst->asOperands[0].ui32RegisterNumber;
            --psContext->indent;
            AddIndentation(psContext);
            bcatcstr(glsl, "}\n"); //Closing brace ends the previous function.
            AddIndentation(psContext);

            bformata(glsl, "subroutine(Interface%d)\n", psContext->psShader->functionToInterfaceRemap[funcID]);
            

            bcatcstr(glsl, "void "); //Closing brace ends the previous function.
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, "(){\n");
            ++psContext->indent;
            break;
        }
        case OPCODE_COUNTBITS:
        {
            bcatcstr(glsl, "bitCount(");
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_HI:
        {
            bcatcstr(glsl, "findMSB(");
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_LO:
        {
            bcatcstr(glsl, "findLSB(");
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_FIRSTBIT_SHI:
        {
            bcatcstr(glsl, "findMSB(");
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_BFREV:
        {
            bcatcstr(glsl, "bitfieldReverse(");
            TranslateOperand(psContext, &psInst->asOperands[0]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[2]);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[3]);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[4]);
            bcatcstr(glsl, ", ");
            TranslateOperand(psContext, &psInst->asOperands[5]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
			bcatcstr(glsl, "EndStreamPrimitive(");
            TranslateOperand(psContext, &psInst->asOperands[0]);
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
                TranslateOperand(psContext, &psInst->asOperands[0]);
                bcatcstr(glsl, ")==0){break;}\n");
            }
            else
            {
                ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
                bcatcstr(glsl, "if((");
                TranslateOperand(psContext, &psInst->asOperands[0]);
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
                TranslateOperand(psContext, &psInst->asOperands[0]);
                bcatcstr(glsl, ")==0){\n");
            }
            else
            {
                ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
                bcatcstr(glsl, "if((");
                TranslateOperand(psContext, &psInst->asOperands[0]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
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
            TranslateOperand(psContext, &psInst->asOperands[0]);
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
            CallHLSLOpcodeFunc2(psContext, "HLSL_eq", psInst);
			break;
		}
		case OPCODE_ISHL:
		{
#ifdef _DEBUG
            AddIndentation(psContext);
            bcatcstr(glsl, "//ISH - TODO\n");
#endif
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
					TranslateOperand(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2]);
					bcatcstr(glsl, ", int((");
					TranslateOperand(psContext, &psInst->asOperands[1]);
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
					TranslateOperand(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2]);
					bcatcstr(glsl, ", ivec3((");
					TranslateOperand(psContext, &psInst->asOperands[1]);
					bcatcstr(glsl, ").xyz), 0)");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_TEXTURE2D:
				{
					//texelFetch(samplerBuffer, ivec2 coord, level)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2]);
					bcatcstr(glsl, ", ivec2((");
					TranslateOperand(psContext, &psInst->asOperands[1]);
					bcatcstr(glsl, ").xy), 0)");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_BUFFER:
				{
					//texelFetch(samplerBuffer, scalar integer coord)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2]);
					bcatcstr(glsl, ", int((");
					TranslateOperand(psContext, &psInst->asOperands[1]);
					bcatcstr(glsl, ").x))");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_TEXTURE2DMS:
				{
					//texelFetch(samplerBuffer, ivec2 coord, sample)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2]);
					bcatcstr(glsl, ", ivec2((");
					TranslateOperand(psContext, &psInst->asOperands[1]);
					bcatcstr(glsl, ").xy), 0)");
					AddSwizzleUsingElementCount(psContext, dstSwizCount);
					bcatcstr(glsl, ";\n");
					break;
				}
				case RESOURCE_DIMENSION_TEXTURE2DMSARRAY:
				{
					//texelFetch(samplerBuffer, ivec3 coord, sample)
					AddIndentation(psContext);
					TranslateOperand(psContext, &psInst->asOperands[0]);
					bcatcstr(glsl, " = texelFetch(");

					TranslateOperand(psContext, &psInst->asOperands[2]);
					bcatcstr(glsl, ", ivec3((");
					TranslateOperand(psContext, &psInst->asOperands[1]);
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
        default:
        {
            ASSERT(0);
            break;
        }
    }
}
