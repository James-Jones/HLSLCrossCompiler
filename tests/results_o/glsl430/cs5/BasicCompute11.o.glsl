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
buffer Block0 {
	uint RawRes0[];
};
buffer Block1 {
	uint RawRes1[];
};
buffer Block0 {
	uint UAV0[];
};
vec4 Temp[3];
ivec4 Temp_int[3];
uvec4 Temp_uint[3];
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //ISHL
    Temp_int[0].x = int(gl_GlobalInvocationID.x) << int(0x3);
    //Instruction 1
    //LD_RAW
    Temp_int[0].yz.x = floatBitsToInt(RawRes0[Temp_int[0].x + 0]);
    Temp_int[0].yz.y = floatBitsToInt(RawRes0[Temp_int[0].x + 1]);
    //Instruction 2
    //LD_RAW
    Temp_int[1].xy.x = floatBitsToInt(RawRes1[Temp_int[0].x + 0]);
    Temp_int[1].xy.y = floatBitsToInt(RawRes1[Temp_int[0].x + 1]);
    //Instruction 3
    //IADD
    Temp_int[2].x = (Temp_int[0].y + Temp_int[1].x);
    //Instruction 4
    //ADD
    Temp_int[2].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).z + intBitsToFloat(Temp_int[1]).y);
    //Instruction 5
    //STORE_RAW
    UAV0[Temp_int[0].x + 0] = (Temp_int[2].xyxx.x);
    UAV0[Temp_int[0].x + 1] = (Temp_int[2].xyxx.y);
    //Instruction 6
    //RET
    return;
}
