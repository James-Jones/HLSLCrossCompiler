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
uniform struct GlobalsVS_Type {
	int AConstantInt;
} GlobalsVS;
layout(location = 1)  in  ivec4 dcl_Input1;
ivec4 Input1;
layout(location = 2)  in  ivec4 dcl_Input2;
ivec4 Input2;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  ivec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
vec4 TempArray0[2];
ivec4 TempArray0_int[2];
uvec4 TempArray0_uint[2];
vec4 TempArray1[2];
ivec4 TempArray1_int[2];
uvec4 TempArray1_uint[2];
void main()
{
    //--- Start Early Main ---
    Input1 = dcl_Input1;
    Input2 = dcl_Input2;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    TempArray0[0].xy = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).xy;
    //Instruction 1
    //MOV
    TempArray0[1].xy = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).xy;
    //Instruction 2
    //MOV
    TempArray1[0].xy = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).xy;
    //Instruction 3
    //MOV
    TempArray1[1].xy = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).xy;
    //Instruction 4
    //MOV
    Temp_int[0].x = ivec4(Input1.x).x;
    //Instruction 5
    //MOV
    TempArray0[0+Temp_int[0].x].xy = vec4(intBitsToFloat(ivec4(0x3F800000, 0x3F800000, 0x0, 0x0))).xy;
    //Instruction 6
    //IADD
    Temp_int[0].x = (Input1.x + int(0x1));
    //Instruction 7
    //MOV
    TempArray0[0+Temp_int[0].x].xy = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).xy;
    //Instruction 8
    //MOV
    Temp_int[0].x = ivec4(Input2.x).x;
    //Instruction 9
    //MOV
    TempArray1[0+Temp_int[0].x].xy = vec4(intBitsToFloat(GlobalsVS.AConstantInt)).xy;
    //Instruction 10
    //IADD
    Temp_int[0].x = (Input2.x + int(0x2));
    //Instruction 11
    //MOV
    TempArray1[0+Temp_int[0].x].xy = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).xy;
    //Instruction 12
    //AND
    Temp_int[0].x = Input1.x & int(0x1);
    //Instruction 13
    //MOV
    Temp_int[0].xy = ivec4(floatBitsToInt(TempArray0[0+Temp_int[0].x].xyxx)).xy;
    //Instruction 14
    //MOV
    Output0 = vec4(intBitsToFloat(Temp_int[0].xxyy)).xyzw;
    //Instruction 15
    //AND
    Temp_int[0].x = Input2.x & int(0x1);
    //Instruction 16
    //MOV
    Temp_int[0].xy = ivec4(floatBitsToInt(TempArray1[0+Temp_int[0].x].xyxx)).xy;
    //Instruction 17
    //MOV
    Output1 = ivec4(Temp_int[0].xxyy).xyzw;
    //Instruction 18
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
