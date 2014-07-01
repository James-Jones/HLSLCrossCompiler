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
layout(location = 0)  in  vec4 dcl_Input0;
vec4 Input0;
layout(location = 1)  in  vec4 dcl_Input1;
vec4 Input1;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  uvec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input1 = dcl_Input1;
    //--- End Early Main ---
    //Instruction 0
    //ADD
    Output0 = (Input0 + Input1);
    //Instruction 1
    //MOV
    Output1.x = uvec4(int(0x1)).x;
    //Instruction 2
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
