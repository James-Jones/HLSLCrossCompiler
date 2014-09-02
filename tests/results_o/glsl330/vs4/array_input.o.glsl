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
	uint arrayIndex;
	uint arrayIndexB;
} GlobalsVS;
 in  vec4 dcl_Input0;
vec4 Input0;
 in  vec4 dcl_Input1[6];
vec4 Input1[6];
 in  vec4 dcl_Input7[2];
vec4 Input7[2];
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
 out  vec4 VtxGeoOutput2;
#define Output2 VtxGeoOutput2
 out  vec4 VtxGeoOutput3;
#define Output3 VtxGeoOutput3
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input1[5] = dcl_Input1[5];
    Input1[4] = dcl_Input1[4];
    Input1[3] = dcl_Input1[3];
    Input1[2] = dcl_Input1[2];
    Input1[1] = dcl_Input1[1];
    Input1[0] = dcl_Input1[0];
    Input7[1] = dcl_Input7[1];
    Input7[0] = dcl_Input7[0];
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Output0 = vec4(Input0).xyzw;
    //Instruction 1
    //MOV
    Temp_int[0].x = ivec4(GlobalsVS.arrayIndex).x;
    //Instruction 2
    //MOV
    Output1 = vec4(Input1[int(Temp_int[0].x)]).xyzw;
    //Instruction 3
    //MOV
    Output2 = vec4(Input1[1]).xyzw;
    //Instruction 4
    //MOV
    Temp_int[0].x = ivec4(GlobalsVS.arrayIndexB).x;
    //Instruction 5
    //MOV
    Output3 = vec4(Input7[int(Temp_int[0].x)]).xyzw;
    //Instruction 6
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
