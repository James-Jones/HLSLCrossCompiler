#version 430
subroutine void SubroutineType();
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
buffer Block0 {
	uint RawRes0[];
};
buffer Block1 {
	uint RawRes1[];
};
buffer Block0 {
	uint BufferOut[];
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
    Temp[0].x = uintBitsToFloat(gl_GlobalInvocationID.xyzz.x << 3u);
    //Instruction 1
    //LD_RAW
    Temp[0].yz.x = (RawRes0[ivec4(Temp[0]).x + 0]);
    Temp[0].yz.y = (RawRes0[ivec4(Temp[0]).x + 1]);
    //Instruction 2
    //LD_RAW
    Temp[1].xy.x = (RawRes1[ivec4(Temp[0]).x + 0]);
    Temp[1].xy.y = (RawRes1[ivec4(Temp[0]).x + 1]);
    //Instruction 3
    //IADD
    Temp_int[2].x = (floatBitsToInt(Temp[0].y) + floatBitsToInt(Temp[1].x));
    //Instruction 4
    //ADD
    Temp[2].y = (Temp[0].z + Temp[1].y);
    //Instruction 5
    //STORE_RAW
    BufferOut[ivec4(Temp[0]).x + 0] = (Temp_int[2].xyxx.x);
    BufferOut[ivec4(Temp[0]).x + 1] = (Temp_int[2].xyxx.y);
    //Instruction 6
    //RET
    return;
}
