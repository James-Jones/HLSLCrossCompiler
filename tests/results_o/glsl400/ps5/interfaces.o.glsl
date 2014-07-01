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
subroutine uniform SubroutineType gAbstractColourChanger[1*1];
subroutine uniform SubroutineType gAbstractColourChangerB[1*1];
subroutine uniform SubroutineType gAlphaChooser[1*1];
 in  vec4 VtxGeoOutput0;
vec4 Input0;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //INTERFACE_CALL
    gAbstractColourChanger[0*1+0]();
    //Instruction 1
    //INTERFACE_CALL
    gAbstractColourChangerB[0*1+0]();
    //Instruction 2
    //MOV
    Output0.xyz = vec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
    //Instruction 3
    //INTERFACE_CALL
    gAlphaChooser[0*1+0]();
    //Instruction 4
    //MOV
    Output0.w = vec4(intBitsToFloat(Temp_int[0].x)).w;
    //Instruction 5
    //RET
    return;
    //Instruction 6
    //LABEL
}
subroutine(SubroutineType)
void cUnchangedColour_Func0(){
    //Instruction 7
    //MOV
    Temp_int[0].xyz = ivec4(floatBitsToInt(Input0.xyzx)).xyz;
    //Instruction 8
    //RET
    return;
    //Instruction 9
    //LABEL
}
subroutine(SubroutineType)
void cHalfColour_Func0(){
    //Instruction 10
    //MUL
    Temp_int[0].xyz = floatBitsToInt(Input0.xyzx * vec4(0.500000, 0.500000, 0.500000, 0.000000)).xyz;
    //Instruction 11
    //RET
    return;
    //Instruction 12
    //LABEL
}
subroutine(SubroutineType)
void cDoubleColour_Func0(){
    //Instruction 13
    //ADD
    Temp_int[0].xyz = floatBitsToInt(Input0.xyzx + Input0.xyzx).xyz;
    //Instruction 14
    //RET
    return;
    //Instruction 15
    //LABEL
}
subroutine(SubroutineType)
void cUnchangedColour_Func1(){
    //Instruction 16
    //RET
    return;
    //Instruction 17
    //LABEL
}
subroutine(SubroutineType)
void cHalfColour_Func1(){
    //Instruction 18
    //MUL
    Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx * vec4(0.500000, 0.500000, 0.500000, 0.000000)).xyz;
    //Instruction 19
    //RET
    return;
    //Instruction 20
    //LABEL
}
subroutine(SubroutineType)
void cDoubleColour_Func1(){
    //Instruction 21
    //ADD
    Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx + intBitsToFloat(Temp_int[0]).xyzx).xyz;
    //Instruction 22
    //RET
    return;
    //Instruction 23
    //LABEL
}
subroutine(SubroutineType)
void TwoThirdsAlpha_Func0(){
    //Instruction 24
    //MOV
    Temp_int[0].x = ivec4(int(0x3F28F5C3)).x;
    //Instruction 25
    //RET
    return;
    //Instruction 26
    //LABEL
}
subroutine(SubroutineType)
void OneAlpha_Func0(){
    //Instruction 27
    //MOV
    Temp_int[0].x = ivec4(int(0x3F800000)).x;
    //Instruction 28
    //RET
    return;
}
