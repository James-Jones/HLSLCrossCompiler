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
	int ShiftValue;
} GlobalsVS;
 in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
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
    //ISHL
    Temp_int[0].x = int(0x1) << GlobalsVS.ShiftValue;
    //Instruction 2
    //ITOF
    Output1.y = (vec4(Temp_int[0].x).y);
    //Instruction 3
    //USHR
    Temp_int[0].x = int(0x1) >> GlobalsVS.ShiftValue;
    //Instruction 4
    //ITOF
    Output1.z = (vec4(Temp_int[0].x).z);
    //Instruction 5
    //MOV
    Output1.xw = vec4(intBitsToFloat(ivec4(0x3F800000, 0x0, 0x0, 0x3F800000))).xw;
    //Instruction 6
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
