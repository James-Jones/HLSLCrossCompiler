#version 400
subroutine void SubroutineType();
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
layout(location = 0)  in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //DP4
    Temp[0].x = (vec4(dot(Input0, Input0)).x);
    //Instruction 1
    //NE
    Temp[0].x = uintBitsToFloat(((Temp[0].x)!= (0.000000)) ? 0xFFFFFFFFu : 0u);
    //Instruction 2
    //MOVC
    if(ivec4(floatBitsToInt(Temp[0].x)).x != 0) {
        Output0.z = vec4(intBitsToFloat(int(0x40000000)));
    } else {
        Output0.z = Input0.z;
    }
    //Instruction 3
    //MOV
    Output0.xyw = vec4(Input0.xyxw).xyw;
    //Instruction 4
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
