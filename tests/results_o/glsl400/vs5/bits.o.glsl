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
layout(location = 1)  in  uvec4 dcl_Input1;
uvec4 Input1;
layout(location = 2)  in  uvec4 dcl_Input2;
uvec4 Input2;
layout(location = 3)  in  uvec4 dcl_Input3;
uvec4 Input3;
layout(location = 4)  in  uvec4 dcl_Input4;
uvec4 Input4;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  uvec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input1 = dcl_Input1;
    Input2 = dcl_Input2;
    Input3 = dcl_Input3;
    Input4 = dcl_Input4;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0 = vec4(Input0).xyzw;
    //Instruction 1
    //FIRSTBIT_HI
    Temp_int[0].x = findMSB(Input2.x);
    //Instruction 2
    //IADD
    Temp_int[0].x = (-Temp_int[0].x + int(0x1F));
    //Instruction 3
    //MOVC
    if(ivec4(Input2.x).x != 0) {
        Output1.y = Temp_int[0].x;
    } else {
        Output1.y = int(0xFFFFFFFF);
    }
    //Instruction 4
    //COUNTBITS
    Output1.x = bitCount(ivec4(Input1).x);
    //Instruction 5
    //FIRSTBIT_LO
    Output1.z = findLSB(Input3.x);
    //Instruction 6
    //BFREV
    Output1.w = bitfieldReverse(ivec4(Input4).x);
    //Instruction 7
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
