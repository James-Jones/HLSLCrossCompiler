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
uvec4 Input1;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    Input1.x = gl_SampleID;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0 = vec4(Input0).xyzw;
    //Instruction 1
    //ISHL
    Temp_int[0].x = int(0x1) << int(Input1.x);
    //Instruction 2
    //AND
    Temp_int[0].x = Temp_int[0].x & floatBitsToInt(gl_SampleMaskIn[0]);
    //Instruction 3
    //AND
    Temp_int[0].x = Temp_int[0].x & int(0x1);
    //Instruction 4
    //INE
    gl_SampleMask[0] = (((Temp_int[0].x)!= (int(0x0))) ? int(0xFFFFFFFF) : 0);
    //Instruction 5
    //RET
    return;
}
