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
uniform struct GlobalsPS_Type {
	int alphaIndex;
} GlobalsPS;
subroutine uniform SubroutineType gAbstractColourChanger[2*1];
subroutine uniform SubroutineType gAbstractColourChangerB[1*1];
subroutine uniform SubroutineType gAlphaChooser[3*1];
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
    gAbstractColourChanger[1*1+0]();
    //Instruction 1
    //INTERFACE_CALL
    gAbstractColourChangerB[0*1+0]();
    //Instruction 2
    //MOV
    Output0.xyz = vec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
    //Instruction 3
    //MOV
    Temp_int[0].x = ivec4(GlobalsPS.alphaIndex).x;
    //Instruction 4
    //INTERFACE_CALL
    gAlphaChooser[int(Temp_int[0].x)*1+0]();
    //Instruction 5
    //MOV
    Output0.w = vec4(intBitsToFloat(Temp_int[0].x)).w;
    //Instruction 6
    //RET
    return;
    //Instruction 7
    //LABEL
}
subroutine(SubroutineType)
void cUnchangedColour_Func0(){
    //Instruction 8
    //MOV
    Temp_int[0].xyz = ivec4(floatBitsToInt(Input0.xyzx)).xyz;
    //Instruction 9
    //RET
    return;
    //Instruction 10
    //LABEL
}
subroutine(SubroutineType)
void cHalfColour_Func0(){
    //Instruction 11
    //MUL
    Temp_int[0].xyz = floatBitsToInt(Input0.xyzx * vec4(0.500000, 0.500000, 0.500000, 0.000000)).xyz;
    //Instruction 12
    //RET
    return;
    //Instruction 13
    //LABEL
}
subroutine(SubroutineType)
void cDoubleColour_Func0(){
    //Instruction 14
    //ADD
    Temp_int[0].xyz = floatBitsToInt(Input0.xyzx + Input0.xyzx).xyz;
    //Instruction 15
    //RET
    return;
    //Instruction 16
    //LABEL
}
subroutine(SubroutineType)
void cUnchangedColour_Func1(){
    //Instruction 17
    //RET
    return;
    //Instruction 18
    //LABEL
}
subroutine(SubroutineType)
void cHalfColour_Func1(){
    //Instruction 19
    //MUL
    Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx * vec4(0.500000, 0.500000, 0.500000, 0.000000)).xyz;
    //Instruction 20
    //RET
    return;
    //Instruction 21
    //LABEL
}
subroutine(SubroutineType)
void cDoubleColour_Func1(){
    //Instruction 22
    //ADD
    Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx + intBitsToFloat(Temp_int[0]).xyzx).xyz;
    //Instruction 23
    //RET
    return;
    //Instruction 24
    //LABEL
}
subroutine(SubroutineType)
void TwoThirdsAlpha_Func0(){
    //Instruction 25
    //MOV
    Temp_int[0].x = ivec4(int(0x3F28F5C3)).x;
    //Instruction 26
    //RET
    return;
    //Instruction 27
    //LABEL
}
subroutine(SubroutineType)
void OneAlpha_Func0(){
    //Instruction 28
    //MOV
    Temp_int[0].x = ivec4(int(0x3F800000)).x;
    //Instruction 29
    //RET
    return;
}
