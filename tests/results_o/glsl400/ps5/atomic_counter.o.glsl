#version 400
#extension GL_ARB_shader_bit_encoding : require
#extension GL_ARB_shader_atomic_counters : enable
#extension GL_ARB_shader_storage_buffer_object : enable
#extension GL_ARB_shader_image_load_store : enable
#extension GL_ARB_shader_bit_encoding : enable
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
layout (binding = 1) uniform atomic_uint UAV1_counter;
struct s3_Type {
	uint unused2;
};
struct UAV1_Type {
	uint unused;
	s3_Type s3;
};
buffer Block1 {
	UAV1_Type UAV1[];
};
layout (binding = 1) uniform atomic_uint UAV2_counter;
struct UAV2_Type {
	uint unused;
};
buffer Block2 {
	UAV2_Type UAV2[];
};
layout (binding = 1) uniform atomic_uint UAV3_counter;
buffer Block3 {
	uint UAV3[];
};
layout (binding = 1) uniform atomic_uint UAV4_counter;
buffer Block4 {
	uint UAV4[];
};
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[3];
ivec4 Temp_int[3];
uvec4 Temp_uint[3];
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //IMM_ATOMIC_ALLOC
    Temp_int[0].x = int(atomicCounterIncrement(UAV1_counter));
    //Instruction 1
    //IMM_ATOMIC_CONSUME
    Temp_int[1].x = int(atomicCounterDecrement(UAV2_counter));
    //Instruction 2
    //IMM_ATOMIC_ALLOC
    Temp_int[2].x = int(atomicCounterIncrement(UAV3_counter));
    //Instruction 3
    //STORE_STRUCTURED
    UAV3[Temp_int[2].x] = (1u);
    //Instruction 4
    //IMM_ATOMIC_CONSUME
    Temp_int[2].x = int(atomicCounterDecrement(UAV4_counter));
    //Instruction 5
    //UTOF
    Temp_int[0].x = floatBitsToInt(vec4(Temp_int[0].x).x);
    //Instruction 6
    //MUL
    Output0.x = (intBitsToFloat(Temp_int[0]).x * 0.001000);
    //Instruction 7
    //UTOF
    Temp_int[0].x = floatBitsToInt(vec4(Temp_int[1].x).x);
    //Instruction 8
    //MUL
    Output0.y = (intBitsToFloat(Temp_int[0]).x * 0.001000);
    //Instruction 9
    //MOV
    Output0.zw = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x3F800000, 0x3F800000))).zw;
    //Instruction 10
    //RET
    return;
}
