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
	int g_bBoolParam;
	int g_IntParam;
} GlobalsVS;
 in  ivec4 dcl_Input0;
ivec4 Input0;
 out  vec4 VtxGeoOutput0;
#define Output0 VtxGeoOutput0
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //MOVC
    if(ivec4(GlobalsVS.g_bBoolParam).x != 0) {
        Temp_int[0] = Input0;
    } else {
        Temp_int[0] = ivec4(0x0, 0x0, 0x0, 0x0);
    }
    //Instruction 1
    //IADD
    Temp_int[0] = (Temp_int[0] + GlobalsVS.g_IntParam);
    //Instruction 2
    //ITOF
    Output0 = (vec4(Temp_int[0]));
    //Instruction 3
    //RET
    return;
}
