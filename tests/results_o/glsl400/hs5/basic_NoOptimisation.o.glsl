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
layout(vertices=4) out;
//Control point phase declarations
in  vec4 VtxGeoOutput0 [4];
vec4 Input0[4];
#undef Output0
#define Output0 phase2_Output0
vec4 phase2_Output0;
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void control_point_phase()
{
    //Instruction 0
    //MOV
    Temp_int[0].x = ivec4(floatBitsToInt(gl_InvocationID)).x;
    //Instruction 1
    //MOV
    Temp_int[0] = ivec4(floatBitsToInt(gl_in[int(Temp_int[0].x)].gl_Position)).xyzw;
    //Instruction 2
    //MOV
    Output0 = vec4(intBitsToFloat(Temp_int[0])).xyzw;
    //Instruction 3
    //RET
    //--- Post shader code ---
    gl_out[gl_InvocationID].gl_Position = vec4(phase2_Output0);
    //--- End post shader code ---
    return;
}
//Join phase declarations
#undef Output0
#define Output0 phase3_Output0
vec4 phase3_Output0;
#undef Output1
#define Output1 phase3_Output1
vec4 phase3_Output1;
void join_phase()
{
    //Instruction 5
    //MOV
    Temp_int[0].x = ivec4(int(0x3F800000)).x;
    //Instruction 6
    //MOV
    Temp_int[0].y = ivec4(int(0x41000000)).y;
    //Instruction 7
    //MOV
    Output0.x = vec4(intBitsToFloat(Temp_int[0].x)).x;
    //Instruction 8
    //MOV
    Output1.x = vec4(intBitsToFloat(Temp_int[0].y)).x;
    //Instruction 9
    //RET
    //--- Post shader code ---
    gl_TessLevelOuter[0] = float(phase3_Output0.x);
    gl_TessLevelOuter[1] = float(phase3_Output1.x);
    //--- End post shader code ---
    return;
}
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    control_point_phase();
    barrier();
    join_phase();
}
