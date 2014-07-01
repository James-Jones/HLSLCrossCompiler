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
	int predicate;
} GlobalsPS;
subroutine uniform SubroutineType gAbstractColourChanger[1*1];
subroutine uniform SubroutineType gAbstractColourChangerB[1*1];
 in  vec4 VtxGeoOutput0;
vec4 Input0;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //INTERFACE_CALL
    gAbstractColourChanger[0*1+0]();
    //Instruction 1
    //INE
    Temp_int[0].w = (((GlobalsPS.predicate)!= (int(0x0))) ? int(0xFFFFFFFF) : 0);
    //Instruction 2
    //INTERFACE_CALL
    gAbstractColourChangerB[0*1+0]();
    //Instruction 3
    //MOVC
    if(ivec4(GlobalsPS.predicate).x != 0) {
        Output0.xyz = ivec4(Temp_int[1].xyzx).xyz;
    } else {
        Output0.xyz = ivec4(Temp_int[0].xyzx).xyz;
    }
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
    //MOV
    Temp_int[1].xyz = ivec4(Temp_int[0].xyzx).xyz;
    //Instruction 14
    //RETC
    if((Temp_int[0].w)!=0){return;}
    //Instruction 15
    //RET
    return;
    //Instruction 16
    //LABEL
}
subroutine(SubroutineType)
void cDoubleColour_Func1(){
    //Instruction 17
    //ADD
    Temp_int[1].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx + intBitsToFloat(Temp_int[0]).xyzx).xyz;
    //Instruction 18
    //RETC
    if((Temp_int[0].w)!=0){return;}
    //Instruction 19
    //RET
    return;
}
