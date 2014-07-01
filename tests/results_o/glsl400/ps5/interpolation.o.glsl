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
centroid in  vec4 VtxGeoOutput1;
vec4 Input1;
sample in  vec4 VtxGeoOutput2;
vec4 Input2;
flat in  vec4 VtxGeoOutput3;
vec4 Input3;
noperspective in  vec4 VtxGeoOutput4;
vec4 Input4;
noperspective centroid in  vec4 VtxGeoOutput5;
vec4 Input5;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
layout(location = 1) out  vec4 PixOutput1;
#define Output1 PixOutput1
layout(location = 2) out  vec4 PixOutput2;
#define Output2 PixOutput2
layout(location = 3) out  vec4 PixOutput3;
#define Output3 PixOutput3
layout(location = 4) out  vec4 PixOutput4;
#define Output4 PixOutput4
void main()
{
    //--- Start Early Main ---
    Input1 = VtxGeoOutput1;
    Input2 = VtxGeoOutput2;
    Input3 = VtxGeoOutput3;
    Input4 = VtxGeoOutput4;
    Input5 = VtxGeoOutput5;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0 = vec4(Input1).xyzw;
    //Instruction 1
    //MOV
    Output1 = vec4(Input2).xyzw;
    //Instruction 2
    //MOV
    Output2 = vec4(Input3).xyzw;
    //Instruction 3
    //MOV
    Output3 = vec4(Input4).xyzw;
    //Instruction 4
    //MOV
    Output4 = vec4(Input5).xyzw;
    //Instruction 5
    //RET
    return;
}
