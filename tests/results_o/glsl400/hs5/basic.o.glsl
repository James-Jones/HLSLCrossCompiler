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
#define immediateConstBufferI(idx) immediateConstBufferInt[idx]
#define immediateConstBufferF(idx) intBitsToFloat(immediateConstBufferInt[idx])
ivec4 immediateConstBufferInt[2] = ivec4[2] (
	ivec4(1065353216, 0, 0, 0), 
	ivec4(1090519040, 0, 0, 0)
);
//Fork phase declarations
const int HullPhase0InstanceCount = 2;
#undef Output0
#define Output0 phase1_Output0
vec4 phase1_Output0[2];
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
        Output0[int(Temp[0].x)].x = vec4(immediateConstBufferF(int(Temp_int[0].x)).x).x;
    }
    //--- Post shader code ---
    gl_TessLevelOuter[0] = float(phase1_Output0[0].x);
    gl_TessLevelOuter[1] = float(phase1_Output0[1].x);
    //--- End post shader code ---
}
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    fork_phase0();
}
