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
struct StructuredRes0_Type {
	int i;
	float f;
};
layout(binding = 0) readonly buffer Block0 {
	StructuredRes0_Type StructuredRes0[];
};
struct StructuredRes1_Type {
	int i;
	float f;
};
layout(binding = 1) readonly buffer Block1 {
	StructuredRes1_Type StructuredRes1[];
};
struct UAV0_Type {
	int i;
	float f;
};
layout(binding = 0) buffer Block0 {
	UAV0_Type UAV0[];
};
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //LD_STRUCTURED
    Temp_int[0].xy.x = (StructuredRes0[gl_GlobalInvocationID.x].i);
    Temp_int[0].xy.y = floatBitsToInt(StructuredRes0[gl_GlobalInvocationID.x].f);
    //Instruction 1
    //LD_STRUCTURED
    Temp_int[0].zw.x = (StructuredRes1[gl_GlobalInvocationID.x].i);
    Temp_int[0].zw.y = floatBitsToInt(StructuredRes1[gl_GlobalInvocationID.x].f);
    //Instruction 2
    //IADD
    Temp_int[1].x = (Temp_int[0].x + Temp_int[0].z);
    //Instruction 3
    //ADD
    Temp_int[1].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[0]).y);
    //Instruction 4
    //STORE_STRUCTURED
    UAV0[gl_GlobalInvocationID.x].i = (Temp_int[1].xyxx.x);
    UAV0[gl_GlobalInvocationID.x].f = (Temp_int[1].xyxx.y);
    //Instruction 5
    //RET
    return;
}
