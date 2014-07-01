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
uniform sampler2D Tex2d;
uniform sampler2DArray Tex2dArray;
uniform samplerCube TexCube;
uniform samplerCubeArray TexCubeArray;
vec4 Input0;
layout(location = 0) out  ivec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = gl_FragCoord;
    //--- End Early Main ---
    //Instruction 0
    //GATHER4
    Temp_int[0] = floatBitsToInt(textureGather(Tex2d, Input0.xy));
    //Instruction 1
    //GATHER4
    Temp_int[1] = floatBitsToInt(textureGather(Tex2d, Input0.xy));
    //Instruction 2
    //IADD
    Temp_int[0] = (Temp_int[0] + Temp_int[1]);
    //Instruction 3
    //GATHER4
    Temp_int[1] = floatBitsToInt(textureGather(Tex2dArray, Input0.xyz));
    //Instruction 4
    //IADD
    Temp_int[0] = (Temp_int[0] + Temp_int[1]);
    //Instruction 5
    //GATHER4
    Temp_int[1] = floatBitsToInt(textureGather(Tex2dArray, Input0.xyz));
    //Instruction 6
    //IADD
    Temp_int[0] = (Temp_int[0] + Temp_int[1]);
    //Instruction 7
    //GATHER4
    Temp_int[1] = floatBitsToInt(textureGather(TexCube, Input0.xyz));
    //Instruction 8
    //IADD
    Temp_int[0] = (Temp_int[0] + Temp_int[1]);
    //Instruction 9
    //GATHER4
    Temp_int[1] = floatBitsToInt(textureGather(TexCubeArray, Input0));
    //Instruction 10
    //FTOI
    Temp_int[1] = ivec4(intBitsToFloat(Temp_int[1]));
    //Instruction 11
    //IADD
    Output0 = (Temp_int[0] + Temp_int[1]);
    //Instruction 12
    //RET
    return;
}
