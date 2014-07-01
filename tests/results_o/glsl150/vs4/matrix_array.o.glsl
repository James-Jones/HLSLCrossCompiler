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
	vec4 transforms[4 * 2];
	int transformsIndex;
} GlobalsVS;
 in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //ISHL
    Temp_int[0].x = GlobalsVS.transformsIndex << int(0x2);
    //Instruction 1
    //DP4
    Output0.x = (vec4(dot(Input0, GlobalsVS.transforms[Temp_int[0].x + 0])).x);
    //Instruction 2
    //DP4
    Output0.y = (vec4(dot(Input0, GlobalsVS.transforms[Temp_int[0].x + 1])).y);
    //Instruction 3
    //DP4
    Output0.z = (vec4(dot(Input0, GlobalsVS.transforms[Temp_int[0].x + 2])).z);
    //Instruction 4
    //DP4
    Output0.w = (vec4(dot(Input0, GlobalsVS.transforms[Temp_int[0].x + 3])).w);
    //Instruction 5
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
