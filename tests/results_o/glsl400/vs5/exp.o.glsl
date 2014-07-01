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
layout(location = 3)  in  vec4 dcl_Input3;
vec4 Input3;
layout(location = 4)  in  vec4 dcl_Input4;
vec4 Input4;
layout(location = 5)  in  vec4 dcl_Input5;
vec4 Input5;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
 out  uvec4 VtxGeoOutput2;
#define Output2 VtxGeoOutput2
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
    Input5 = dcl_Input5;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0 = vec4(Input0).xyzw;
    //Instruction 1
    //AND
    Temp_int[0].x = floatBitsToInt(Input1.x) & int(0x7F800000);
    //Instruction 2
    //IADD
    Temp_int[0].x = (Temp_int[0].x + int(0xC1000000));
    //Instruction 3
    //NE
    Temp_int[0].y = floatBitsToInt(((Input1.x)!= (0.000000)) ? int(0xFFFFFFFF) : 0);
    //Instruction 4
    //AND
    Temp_int[0].x = Temp_int[0].y & Temp_int[0].x;
    //Instruction 5
    //ISHR
    Temp_int[0].x = Temp_int[0].x >> int(0x17);
    //Instruction 6
    //ITOF
    Output1.y = (vec4(Temp_int[0].x).y);
    //Instruction 7
    //MUL
    Temp_int[0].x = floatBitsToInt(Input4.x * 1.442695);
    //Instruction 8
    //EXP
    Output1.z = (vec4(exp2(intBitsToFloat(Temp_int[0]).x)).z);
    //Instruction 9
    //BFI
    Temp_int[0].x = ivec1(bitfieldInsert(int(0x3F000000),ivec4(Input1).x,int(0x0),int(0x17)) ).x;
    //Instruction 10
    //AND
    Output1.x = Temp_int[0].y & Temp_int[0].x;
    //Instruction 11
    //EXP
    Output1.w = (vec4(exp2(Input5.x)).w);
    //Instruction 12
    //EXP
    Temp_int[0].x = floatBitsToInt(vec4(exp2(Input3.x)).x);
    //Instruction 13
    //MUL
    Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x * Input2.x);
    //Instruction 14
    //FTOU
    Output2.x = int(intBitsToFloat(Temp_int[0].x));
    //Instruction 15
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
