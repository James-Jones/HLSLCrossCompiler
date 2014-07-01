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
layout(location = 2)  in  vec4 dcl_Input2;
vec4 Input2;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
 out  vec4 VtxGeoOutput2;
#define Output2 VtxGeoOutput2
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input1 = dcl_Input1;
    Input2 = dcl_Input2;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0 = vec4(Input0).xyzw;
    //Instruction 1
    //RCP
    Output1 = (vec4(1.0) / vec4(Input0)).xyzw;
    //Instruction 2
    //RCP
    Output2.xy = (vec4(1.0) / vec4(Input1.xyxx)).xy;
    //Instruction 3
    //RCP
    Output2.z = (vec4(1.0) / vec4(Input2.x)).x;
    //Instruction 4
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
