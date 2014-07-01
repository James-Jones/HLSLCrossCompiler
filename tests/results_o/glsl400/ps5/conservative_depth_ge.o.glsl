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
 in  vec4 VtxGeoOutput0;
vec4 Input0;
 in  vec4 VtxGeoOutput1;
vec4 Input1;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
#ifdef GL_ARB_conservative_depth
#extension GL_ARB_conservative_depth : enable
layout (depth_greater) out float gl_FragDepth;
#endif
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    Input1 = VtxGeoOutput1;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0.x = vec4(Input0.x).x;
    //Instruction 1
    //MOV
    gl_FragDepth = vec4(Input1.x).x;
    //Instruction 2
    //RET
    return;
}
