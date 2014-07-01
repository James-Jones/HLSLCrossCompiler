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
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
layout(location = 1) out  vec4 PixOutput1;
#define Output1 PixOutput1
layout(location = 2) out  vec4 PixOutput2;
#define Output2 PixOutput2
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //EVAL_CENTROID
    Output0 = interpolateAtCentroid(VtxGeoOutput0);
    //Instruction 1
    //EVAL_SAMPLE_INDEX
    Output1 = interpolateAtSample(VtxGeoOutput0, int(0x2));
    //Instruction 2
    //EVAL_SNAPPED
    Output2 = interpolateAtOffset(VtxGeoOutput0, ivec4(0x4, 0x7, 0x0, 0x0).xy);
    //Instruction 3
    //RET
    return;
}
