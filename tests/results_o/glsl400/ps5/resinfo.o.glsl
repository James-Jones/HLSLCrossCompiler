#version 400
#extension GL_ARB_shader_bit_encoding : require
#extension GL_ARB_texture_query_levels : enable
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
uniform sampler1D T1D;
uniform sampler2D T2D;
uniform samplerCubeArray TCubeArray;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //RESINFO
    Temp_int[0].x = floatBitsToInt(vec1(textureSize(T1D, int(0x0))).x);
    //Instruction 1
    //FTOU
    Temp_int[0].x = int(intBitsToFloat(Temp_int[0].x));
    //Instruction 2
    //UTOF
    Output0.x = (vec4(Temp_int[0].x).x);
    //Instruction 3
    //RESINFO
    Temp_int[0].x = floatBitsToInt(ivec2(textureSize(T2D, int(0x0))).y);
    //Instruction 4
    //UTOF
    Output0.y = (vec4(Temp_int[0].x).y);
    //Instruction 5
    //RESINFO
    Temp_int[0].x = floatBitsToInt(textureQueryLevels(TCubeArray));
    //Instruction 6
    //UTOF
    Output0.z = (vec4(Temp_int[0].x).z);
    //Instruction 7
    //MOV
    Output0.w = vec4(intBitsToFloat(int(0x3F800000))).w;
    //Instruction 8
    //RET
    return;
}
