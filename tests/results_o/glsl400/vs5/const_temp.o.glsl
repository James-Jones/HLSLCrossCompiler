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
uniform struct GlobalsVS_Type {
	vec4 mWorldViewProj[4];
} GlobalsVS;
layout(location = 0)  in  vec4 dcl_Input0;
vec4 Input0;
layout(location = 1)  in  vec4 dcl_Input1;
vec4 Input1;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input1 = dcl_Input1;
    //--- End Early Main ---
    //Instruction 0
    //MUL
    Temp_int[0] = floatBitsToInt(Input0.yyyy * GlobalsVS.mWorldViewProj[1]);
    //Instruction 1
    //MAD
    Temp_int[0] = floatBitsToInt(vec4(Input0.xxxx * GlobalsVS.mWorldViewProj[0] + intBitsToFloat(Temp_int[0])));
    //Instruction 2
    //MAD
    Temp_int[0] = floatBitsToInt(vec4(Input0.zzzz * GlobalsVS.mWorldViewProj[2] + intBitsToFloat(Temp_int[0])));
    //Instruction 3
    //MAD
    Temp_int[0] = floatBitsToInt(vec4(Input0.wwww * GlobalsVS.mWorldViewProj[3] + intBitsToFloat(Temp_int[0])));
    //Instruction 4
    //ADD
    Output0 = (intBitsToFloat(Temp_int[0]) + Input1);
    //Instruction 5
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
