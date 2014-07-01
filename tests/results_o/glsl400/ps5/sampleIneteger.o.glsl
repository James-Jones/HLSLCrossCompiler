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
flat in  ivec4 VtxGeoOutput0;
ivec4 Input0;
layout(location = 0) out  ivec4 PixOutput0;
#define Output0 PixOutput0
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //LD
    Output0 = floatBitsToInt(texelFetch(TextureBase, ivec2((Input0.xyzz).xy), 0));
    //Instruction 1
    //RET
    return;
}
