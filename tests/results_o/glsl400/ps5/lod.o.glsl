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
 in  vec4 VtxGeoOutput0;
vec4 Input0;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //LOD
    Temp_int[0].x = floatBitsToInt(textureQueryLod(TextureBase,Input0.xy).x);
    //Instruction 1
    //LOD
    Temp_int[0].y = floatBitsToInt(textureQueryLod(TextureBase,Input0.xy).y);
    //Instruction 2
    //ADD
    Temp_int[0].x = floatBitsToInt(-intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).y);
    //Instruction 3
    //SAMPLE
    Temp_int[1] = floatBitsToInt(texture(TextureBase, Input0.xy));
    //Instruction 4
    //ADD
    Output0.x = (intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[1]).x);
    //Instruction 5
    //MOV
    Output0.yzw = vec4(intBitsToFloat(Temp_int[1].yyzw)).yzw;
    //Instruction 6
    //RET
    return;
}
