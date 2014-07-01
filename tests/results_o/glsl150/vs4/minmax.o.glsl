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
uniform struct GlobalsVS_Type {
	int iValue;
	float fValue;
} GlobalsVS;
 in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  ivec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
 out  vec4 VtxGeoOutput2;
#define Output2 VtxGeoOutput2
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0 = vec4(Input0).xyzw;
    //Instruction 1
    //IMIN
    Temp_int[0].x = (ivec4(min(int(GlobalsVS.iValue), int(int(0x7)))).x);
    //Instruction 2
    //IMAX
    Output1.x = (ivec4(max(int(Temp_int[0].x), int(int(0x1)))).x);
    //Instruction 3
    //MIN
    Temp_int[0].x = floatBitsToInt(vec4(min(GlobalsVS.fValue, 8.100000)).x);
    //Instruction 4
    //MAX
    Output2.x = (vec4(max(intBitsToFloat(Temp_int[0]).x, 0.100000)).x);
    //Instruction 5
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
