#version 150
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
 in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0 = vec4(Input0).xyzw;
    //Instruction 1
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
