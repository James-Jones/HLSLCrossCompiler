#version 430
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
#extension GL_ARB_gpu_shader_fp64 : enable
struct StructuredRes0_Type {
	int i;
	float f;
	double d;
};
layout(binding = 0) readonly buffer Block0 {
	StructuredRes0_Type StructuredRes0[];
};
struct StructuredRes1_Type {
	int i;
	float f;
	double d;
};
layout(binding = 1) readonly buffer Block1 {
	StructuredRes1_Type StructuredRes1[];
};
struct UAV0_Type {
	int i;
	float f;
	double d;
};
layout(binding = 0) buffer Block0 {
	UAV0_Type UAV0[];
};
vec4 Temp[3];
ivec4 Temp_int[3];
uvec4 Temp_uint[3];
dvec4 Temp_double[3];
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //LD_STRUCTURED
    Temp_int[0].x = floatBitsToInt(StructuredRes0[gl_GlobalInvocationID.x].d);
    Temp_int[0].y = (StructuredRes0[gl_GlobalInvocationID.x].i);
    Temp_int[0].z = floatBitsToInt(StructuredRes0[gl_GlobalInvocationID.x].f);
    //Instruction 1
    //LD_STRUCTURED
    Temp_int[1].x = floatBitsToInt(StructuredRes1[gl_GlobalInvocationID.x].d);
    Temp_int[1].y = (StructuredRes1[gl_GlobalInvocationID.x].i);
    Temp_int[1].z = floatBitsToInt(StructuredRes1[gl_GlobalInvocationID.x].f);
    //Instruction 2
    //DADD
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyxy + intBitsToFloat(Temp_int[1]).xyxy).zw;
    //Instruction 3
    //IADD
    Temp_int[2].x = (Temp_int[0].z + Temp_int[1].z);
    //Instruction 4
    //ADD
    Temp_int[2].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[1]).w);
    //Instruction 5
    //STORE_STRUCTURED
    UAV0[gl_GlobalInvocationID.x].i = (Temp_int[2].x);
    UAV0[gl_GlobalInvocationID.x].f = (Temp_int[2].y);
    UAV0[gl_GlobalInvocationID.x].d = (Temp_int[2].z);
    //Instruction 6
    //RET
    return;
}
