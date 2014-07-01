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
subroutine uniform SubroutineType gAbstractColourChanger[1*2];
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
    gAbstractColourChanger[0*2+0]();
    //Instruction 1
    //MOV
    Output0.yz = vec4(intBitsToFloat(Temp_int[0].yyzy)).yz;
    //Instruction 2
    //INTERFACE_CALL
    gAbstractColourChanger[0*2+1]();
    //Instruction 3
    //MOV
    Output0.x = vec4(intBitsToFloat(Temp_int[0].x)).x;
    //Instruction 4
    //MOV
    Output0.w = vec4(intBitsToFloat(int(0x3F800000))).w;
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
void cDoubleColour_Func0(){
    //Instruction 10
    //ADD
    Temp_int[0].xyz = floatBitsToInt(Input0.xyzx + Input0.xyzx).xyz;
    //Instruction 11
    //RET
    return;
    //Instruction 12
    //LABEL
}
subroutine(SubroutineType)
void cUnchangedColour_Func1(){
    //Instruction 13
    //RET
    return;
    //Instruction 14
    //LABEL
}
subroutine(SubroutineType)
void cDoubleColour_Func1(){
    //Instruction 15
    //ADD
    Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).x);
    //Instruction 16
    //RET
    return;
}
