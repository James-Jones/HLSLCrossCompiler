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
uniform sampler2D TextureBase;
uniform sampler2D TextureDetail;
 in  vec4 VtxGeoOutput0;
vec4 Input0;
 in  vec4 VtxGeoOutput1;
vec4 Input1;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    Input1 = VtxGeoOutput1;
    //--- End Early Main ---
    //Instruction 0
    //SAMPLE
    Temp_int[0] = floatBitsToInt(texture(TextureBase, Input0.xy));
    //Instruction 1
    //SAMPLE
    Temp_int[1] = floatBitsToInt(texture(TextureDetail, Input0.xy));
    //Instruction 2
    //MAD
    Temp_int[0] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]) * intBitsToFloat(Temp_int[1]) + Input1));
    //Instruction 3
    //MOV
    Output0 = vec4(intBitsToFloat(Temp_int[0])).xyzw;
    //Instruction 4
    //RET
    return;
}
