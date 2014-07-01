#version 400
#extension GL_ARB_shader_bit_encoding : require
struct vec1 {
	float x;
};
struct uvec1 {
	uint x;
};
struct ivec1 {
	int x;
};
subroutine void SubroutineType();
layout(isolines) in;
in  vec4 HullOutput0 [4];
vec4 Input0[4];
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //ADD
    Temp_int[0].x = floatBitsToInt(-gl_TessCoord.x + 1.000000);
    //Instruction 1
    //MUL
    Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).x * intBitsToFloat(Temp_int[0]).x);
    //Instruction 2
    //MUL
    Temp_int[0].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * gl_TessCoord.x);
    //Instruction 3
    //MUL
    Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[0]).x);
    //Instruction 4
    //MUL
    Temp_int[0].xz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xxzx * vec4(3.000000, 0.000000, 3.000000, 0.000000)).xz;
    //Instruction 5
    //MUL
    Temp_int[1].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).zzzz * gl_in[1].gl_Position.xyzx).xyz;
    //Instruction 6
    //MAD
    Temp_int[0].yzw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).yyyy * gl_in[0].gl_Position.xxyz + intBitsToFloat(Temp_int[1]).xxyz)).yzw;
    //Instruction 7
    //MUL
    Temp_int[1].x = floatBitsToInt(gl_TessCoord.x * gl_TessCoord.x);
    //Instruction 8
    //MUL
    Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x * intBitsToFloat(Temp_int[1]).x);
    //Instruction 9
    //MUL
    Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).x * gl_TessCoord.x);
    //Instruction 10
    //MAD
    Temp_int[0].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).xxxx * gl_in[2].gl_Position.xyzx + intBitsToFloat(Temp_int[0]).yzwy)).xyz;
    //Instruction 11
    //MAD
    Output0.xyz = (vec4(intBitsToFloat(Temp_int[1]).xxxx * gl_in[3].gl_Position.xyzx + intBitsToFloat(Temp_int[0]).xyzx)).xyz;
    //Instruction 12
    //MOV
    Output0.w = vec4(intBitsToFloat(int(0x3F800000))).w;
    //Instruction 13
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
