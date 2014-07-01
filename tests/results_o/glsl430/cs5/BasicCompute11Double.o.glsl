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
buffer Block0 {
	uint RawRes0[];
};
buffer Block1 {
	uint RawRes1[];
};
buffer Block0 {
	uint UAV0[];
};
vec4 Temp[4];
ivec4 Temp_int[4];
uvec4 Temp_uint[4];
dvec4 Temp_double[4];
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //ISHL
    Temp_int[0].x = int(gl_GlobalInvocationID.x) << int(0x4);
    //Instruction 1
    //LD_RAW
    Temp_int[1].x = floatBitsToInt(RawRes0[Temp_int[0].x + 2]);
    Temp_int[1].y = floatBitsToInt(RawRes0[Temp_int[0].x + 3]);
    Temp_int[1].z = floatBitsToInt(RawRes0[Temp_int[0].x + 0]);
    Temp_int[1].w = floatBitsToInt(RawRes0[Temp_int[0].x + 1]);
    //Instruction 2
    //LD_RAW
    Temp_int[2].x = floatBitsToInt(RawRes1[Temp_int[0].x + 2]);
    Temp_int[2].y = floatBitsToInt(RawRes1[Temp_int[0].x + 3]);
    Temp_int[2].z = floatBitsToInt(RawRes1[Temp_int[0].x + 0]);
    Temp_int[2].w = floatBitsToInt(RawRes1[Temp_int[0].x + 1]);
    //Instruction 3
    //DADD
    Temp_int[3].zw = floatBitsToInt(intBitsToFloat(Temp_int[1]).xyxy + intBitsToFloat(Temp_int[2]).xyxy).zw;
    //Instruction 4
    //IADD
    Temp_int[3].x = (Temp_int[1].z + Temp_int[2].z);
    //Instruction 5
    //ADD
    Temp_int[3].y = floatBitsToInt(intBitsToFloat(Temp_int[1]).w + intBitsToFloat(Temp_int[2]).w);
    //Instruction 6
    //STORE_RAW
    UAV0[Temp_int[0].x + 0] = (Temp_int[3].x);
    UAV0[Temp_int[0].x + 1] = (Temp_int[3].y);
    UAV0[Temp_int[0].x + 2] = (Temp_int[3].z);
    UAV0[Temp_int[0].x + 3] = (Temp_int[3].w);
    //Instruction 7
    //RET
    return;
}
