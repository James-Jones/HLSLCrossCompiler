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
uniform struct GlobalsHS_Type {
	vec4 MVP[4];
	float InnerFactor;
	float OuterFactor;
} GlobalsHS;
//Fork phase declarations
const int HullPhase0InstanceCount = 4;
#undef Output0
#define Output0 phase1_Output0
vec4 phase1_Output0[4];
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void fork_phase0()
{
    for(int forkInstanceID = 0; forkInstanceID < HullPhase0InstanceCount; ++forkInstanceID) {
        //Instruction 0
        //MOV
        Temp_int[0].x = ivec4(floatBitsToInt(forkInstanceID)).x;
        //Instruction 1
        //MOV
        Output0[int(Temp[0].x)].x = vec4(GlobalsHS.OuterFactor).x;
    }
    //--- Post shader code ---
    gl_TessLevelOuter[0] = float(phase1_Output0[0].x);
    gl_TessLevelOuter[1] = float(phase1_Output0[1].x);
    gl_TessLevelOuter[2] = float(phase1_Output0[2].x);
    gl_TessLevelOuter[3] = float(phase1_Output0[3].x);
    //--- End post shader code ---
}
//Fork phase declarations
const int HullPhase1InstanceCount = 2;
#undef Output4
#define Output4 phase1_Output4
vec4 phase1_Output4[2];
void fork_phase1()
{
    for(int forkInstanceID = 0; forkInstanceID < HullPhase1InstanceCount; ++forkInstanceID) {
        //Instruction 4
        //MOV
        Temp_int[0].x = ivec4(floatBitsToInt(forkInstanceID)).x;
        //Instruction 5
        //MOV
        Output4[int(Temp[0].x)].x = vec4(GlobalsHS.InnerFactor).x;
    }
    //--- Post shader code ---
    gl_TessLevelOuter[0] = float(phase1_Output0[0].x);
    gl_TessLevelOuter[1] = float(phase1_Output0[1].x);
    gl_TessLevelOuter[2] = float(phase1_Output0[2].x);
    gl_TessLevelOuter[3] = float(phase1_Output0[3].x);
    gl_TessLevelInner[0] = float(phase1_Output4[0].x);
    gl_TessLevelInner[1] = float(phase1_Output4[1].x);
    //--- End post shader code ---
}
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    fork_phase0();
    barrier();
    fork_phase1();
}
