#include "toGLSLInstruction.h"
#include "toGLSLOperand.h"
#include "bstrlib.h"
#include "stdio.h"

#include <assert.h>
#define ASSERT(x) assert(x)

extern bstring glsl;
extern int indent;
extern void AddIndentation();

void CallHLSLOpcodeFunc1(const char* name, Instruction* psInst)
{
    AddIndentation();
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(&psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[1]);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc2(const char* name, Instruction* psInst)
{
    AddIndentation();
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(&psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[1]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[2]);
    bcatcstr(glsl, ");\n");
}

void CallHLSLOpcodeFunc3(const char* name, Instruction* psInst)
{
    AddIndentation();
    bcatcstr(glsl, name);
    bcatcstr(glsl, "(");
    TranslateOperand(&psInst->asOperands[0]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[1]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[2]);
    bcatcstr(glsl, ", ");
    TranslateOperand(&psInst->asOperands[3]);
    bcatcstr(glsl, ");\n");
}

void TranslateInstruction(Shader* psShader, Instruction* psInst)
{
    switch(psInst->eOpcode)
    {
        case OPCODE_MOV:
        {
            AddIndentation();
            bcatcstr(glsl, "//MOV\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = vec4(");


            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(&psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_UTOF://unsigned to float
        {
            AddIndentation();
            bcatcstr(glsl, "//UTOF\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = vec4(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(&psInst->asOperands[0]);
            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_MAD:
        {
            AddIndentation();
            bcatcstr(glsl, "//MAD\n");
            CallHLSLOpcodeFunc3("HLSL_mad", psInst);
            break;
        }
        case OPCODE_IADD:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//IADD\n");
#endif
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");

            bcatcstr(glsl, "vec4(");

            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " + ");
            TranslateOperand(&psInst->asOperands[2]);

            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(&psInst->asOperands[0]);

            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_ADD:
        {
            //Limit src swizzles based on dest swizzle
            //e.g. given hlsl asm: add r0.xy, v0.xyxx, l(0.100000, 0.000000, 0.000000, 0.000000)
            //the two sources must become vec2
            //Temp0.xy = Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000);
            //becomes
            //Temp0.xy = vec4(Input0.xyxx + vec4(0.100000, 0.000000, 0.000000, 0.000000)).xy;

            AddIndentation();
            bcatcstr(glsl, "//ADD\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");

            bcatcstr(glsl, "vec4(");

            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " + ");
            TranslateOperand(&psInst->asOperands[2]);

            bcatcstr(glsl, ")");
            TranslateOperandSwizzle(&psInst->asOperands[0]);

            bcatcstr(glsl, ";\n");
            break;
        }
        case OPCODE_OR:
        {
            /*Todo: vector version */
            AddIndentation();
            bcatcstr(glsl, "//OR\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = int(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ") | int(");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_AND:
        {
            /* Todo: vector version*/
            AddIndentation();
            bcatcstr(glsl, "//AND\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = int(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ") & int(");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_GE:
        {
            /*
                dest = vec4(greaterThanEqual(vec4(srcA), vec4(srcB));
                Caveat: The result is a boolean but HLSL asm returns 0xFFFFFFFF/0x0 instead.
             */
            AddIndentation();
            bcatcstr(glsl, "//GE\n");
            CallHLSLOpcodeFunc2("HLSL_ge", psInst);
            break;
        }
        case OPCODE_MUL:
        {
            AddIndentation();
            bcatcstr(glsl, "//MUL\n");
            CallHLSLOpcodeFunc2("HLSL_mul", psInst);
            break;
        }
        case OPCODE_DIV:
        {
            AddIndentation();
            bcatcstr(glsl, "//DIV\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, " / ");
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

        case OPCODE_DP2:
        {
            AddIndentation();
            bcatcstr(glsl, "//DP2\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = dot((");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ").xy);\n");
            break;
        }
        case OPCODE_DP3:
        {
            AddIndentation();
            bcatcstr(glsl, "//DP3\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = dot((");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ").xyz);\n");
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
        case OPCODE_IGE:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//IGE\n");
#endif
            CallHLSLOpcodeFunc2("HLSL_ige", psInst);
            break;
        }
        case OPCODE_LT:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//LT\n");
#endif
            CallHLSLOpcodeFunc2("HLSL_lt", psInst);
            break;
        }
        case OPCODE_IEQ:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//IEQ\n");
#endif
            CallHLSLOpcodeFunc2("HLSL_ieq", psInst);
            break;
        }
        case OPCODE_FTOI:
        {
            // Rounding is always performed towards zero

            //Use int constructor - int(float). This drops the fractional part.
        }
        case OPCODE_MOVC:
        {
            AddIndentation();
            bcatcstr(glsl, "//MOVC\n");
            CallHLSLOpcodeFunc1("HLSL_movc", psInst);
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
            bcatcstr(glsl, "//RSQ\n");
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
        case OPCODE_ROUND_PI:
        {
            AddIndentation();
            bcatcstr(glsl, "//ROUND_PI\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = ceil(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_ROUND_NI:
        {
            AddIndentation();
            bcatcstr(glsl, "//ROUND_NI\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = floor(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_ROUND_Z:
        {
            AddIndentation();
            bcatcstr(glsl, "//ROUND_Z\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = trunc(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_ROUND_NE:
        {
            AddIndentation();
            bcatcstr(glsl, "//ROUND_NE\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = roundEven(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ");\n");
            break;
        }
		case OPCODE_FRC:
        {
            AddIndentation();
            bcatcstr(glsl, "//FRC\n");
            AddIndentation();
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, " = fract(");
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
            //Texture coord cannot be vec4
            //Determining if it is a vec3 for vec2 yet to be done.
            psInst->asOperands[2].aui32Swizzle[2] = 0xFFFFFFFF;
            psInst->asOperands[2].aui32Swizzle[3] = 0xFFFFFFFF;
            TranslateOperand(&psInst->asOperands[2]);//in
            bcatcstr(glsl, ");\n");
            break;
        }
        case OPCODE_SAMPLE_L:
        {
            //dest, coords, tex, sampler, lod
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//SAMPLE_L\n");
#endif
            AddIndentation();
            bcatcstr(glsl, "HLSL_sample_l");
            bcatcstr(glsl, "(");
            TranslateOperand(&psInst->asOperands[1]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[3]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[2]);
            bcatcstr(glsl, ", ");
            TranslateOperand(&psInst->asOperands[5]);
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
        case OPCODE_CUT:
        {
            AddIndentation();
            bcatcstr(glsl, "//CUT\n");
            AddIndentation();
			bcatcstr(glsl, "EndPrimitive();\n");
			break;
        }
        case OPCODE_EMIT:
        {
            AddIndentation();
            bcatcstr(glsl, "//EMIT\n");
            AddIndentation();
			bcatcstr(glsl, "EmitVertex();\n");
			break;
        }
        case OPCODE_EMITTHENCUT:
        {
            AddIndentation();
            bcatcstr(glsl, "//EMITTHENCUT\n");
            AddIndentation();
			bcatcstr(glsl, "EmitVertex();\nEndPrimitive();\n");
			break;
        }

        case OPCODE_CUT_STREAM:
        {
            AddIndentation();
            bcatcstr(glsl, "//CUT\n");
            AddIndentation();
			bcatcstr(glsl, "EndStreamPrimitive(");
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");

			break;
        }
        case OPCODE_EMIT_STREAM:
        {
            AddIndentation();
            bcatcstr(glsl, "//EMIT\n");
            AddIndentation();
			bcatcstr(glsl, "EmitStreamVertex(");
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
			break;
        }
        case OPCODE_EMITTHENCUT_STREAM:
        {
            AddIndentation();
            bcatcstr(glsl, "//EMITTHENCUT\n");
            AddIndentation();
			bcatcstr(glsl, "EmitStreamVertex(");
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
			bcatcstr(glsl, "EndStreamPrimitive(");
            TranslateOperand(&psInst->asOperands[0]);
            bcatcstr(glsl, ");\n");
			break;
        }
        case OPCODE_LOOP:
        {
            AddIndentation();
            bcatcstr(glsl, "//LOOP\n");
            AddIndentation();
            bcatcstr(glsl, "while(true){\n");
            ++indent;
            break;
        }
        case OPCODE_ENDLOOP:
        {
            --indent;
            AddIndentation();
            bcatcstr(glsl, "//ENDLOOP\n");
            AddIndentation();
            bcatcstr(glsl, "}\n");
            break;
        }
        case OPCODE_BREAK:
        {
           AddIndentation();
            bcatcstr(glsl, "//BREAK\n");
            AddIndentation();
            bcatcstr(glsl, "break;\n");
            break;
        }
        case OPCODE_BREAKC:
        {
#ifdef _DEBUG
            AddIndentation();
            bcatcstr(glsl, "//BREAKC\n");
#endif
            AddIndentation();
            if(psInst->eBooleanTestType == INSTRUCTION_TEST_ZERO)
            {
                bcatcstr(glsl, "if((");
                TranslateOperand(&psInst->asOperands[0]);
                bcatcstr(glsl, ")==0){break;}\n");
            }
            else
            {
                ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
                bcatcstr(glsl, "if((");
                TranslateOperand(&psInst->asOperands[0]);
                bcatcstr(glsl, ")!=0){break;}\n");
            }
            break;
        }
        case OPCODE_IF:
        {
           AddIndentation();
            bcatcstr(glsl, "//IF\n");
            AddIndentation();
            if(psInst->eBooleanTestType == INSTRUCTION_TEST_ZERO)
            {
                bcatcstr(glsl, "if((");
                TranslateOperand(&psInst->asOperands[0]);
                bcatcstr(glsl, ")==0){\n");
            }
            else
            {
                ASSERT(psInst->eBooleanTestType == INSTRUCTION_TEST_NONZERO);
                bcatcstr(glsl, "if((");
                TranslateOperand(&psInst->asOperands[0]);
                bcatcstr(glsl, ")!=0){\n");
            }
            ++indent;
            break;
        }
        case OPCODE_ELSE:
        {
            --indent;
           AddIndentation();
            bcatcstr(glsl, "//ELSE\n");
            AddIndentation();
            bcatcstr(glsl, "} else {\n");
            indent++;
            break;
        }
        case OPCODE_ENDIF:
        {
            --indent;
           AddIndentation();
            bcatcstr(glsl, "//ENDIF\n");
            AddIndentation();
            bcatcstr(glsl, "}\n");
            break;
        }
        default:
        {
            AddIndentation();
            bcatcstr(glsl, "//Unknown opcode\n");
#ifdef _DEBUG
            printf("Unknown opcode (toGLSL).\n");
#endif
            break;
        }
    }
}
