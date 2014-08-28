#version 150
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
ivec4 Input0;
out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0.x = gl_PrimitiveID;
    //--- End Early Main ---
    //Instruction 0
    //UTOF
    Temp_int[0].x = floatBitsToInt(vec4(Input0.x).x);
    //Instruction 1
    //MUL
    Output0.yzw = (intBitsToFloat(Temp_int[0]).xxxx * vec4(0.000000, 2.000000, 0.015625, 0.031250)).yzw;
    //Instruction 2
    //MOV
    Output0.x = vec4(intBitsToFloat(Temp_int[0].x)).x;
    //Instruction 3
    //RET
    return;
}
