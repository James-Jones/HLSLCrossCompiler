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
struct StructuredRes0_Type {
	float r;
	float g;
	float b;
	float a;
};
readonly buffer Block0 {
	StructuredRes0_Type StructuredRes0[];
};
buffer Block1 {
	uint RawRes1[];
};
struct UAV1_Type {
	float r;
	float g;
	float b;
	float a;
};
buffer Block1 {
	UAV1_Type UAV1[];
};
buffer Block2 {
	uint UAV2[];
};
coherent layout(rgba32f) uniform image1D UAV3;
layout(rgba32f) uniform image2D UAV4;
layout(rgba32f) uniform image3D UAV5;
layout(rgba32f) uniform image1DArray UAV6;
coherent layout(rgba32f) uniform image2DArray UAV7;
coherent layout(rgba32ui) uniform image1D UAV8;
flat in  ivec4 VtxGeoOutput0;
ivec4 Input0;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //LD_UAV_TYPED
    Temp_int[0].x = imageLoad(UAV3, (Input0.xxxx).x).x;
    //Instruction 1
    //STORE_UAV_TYPED
    imageStore(UAV3, int(Input0), vec4(0.200000, 0.200000, 0.200000, 0.200000));
    //Instruction 2
    //STORE_UAV_TYPED
    imageStore(UAV8, int(Input0), vec4(0.000000, 0.000000, 0.000000, 0.000000));
    //Instruction 3
    //LD_STRUCTURED
    Temp_int[0].y = floatBitsToInt(StructuredRes0[Input0.x].r);
    //Instruction 4
    //IMUL
    Temp_int[0].z = (Input0.x * int(0x3));
    //Instruction 5
    //STORE_RAW
    UAV2[Temp_int[0].z + 0] = (Temp_int[0].y);
    //Instruction 6
    //IMAD
    Temp_int[0].yw = (ivec4(Input0.xxxx * ivec4(0x0, 0x3, 0x0, 0x3) + ivec4(0x0, 0x1, 0x0, 0x2))).yw;
    //Instruction 7
    //STORE_RAW
    UAV2[Temp_int[0].y + 0] = (Temp_int[0].x);
    //Instruction 8
    //ITOF
    Temp_int[0].x = floatBitsToInt(vec4(Input0.x).x);
    //Instruction 9
    //FTOU
    Temp_int[0].x = int(intBitsToFloat(Temp_int[0].x));
    //Instruction 10
    //LD_UAV_TYPED
    Temp_int[1].x = imageLoad(UAV4, (Temp_int[0].xxxx).xy).x;
    //Instruction 11
    //STORE_RAW
    UAV2[Temp_int[0].w + 0] = (Temp_int[1].x);
    //Instruction 12
    //LD_UAV_TYPED
    Temp_int[1].x = imageLoad(UAV5, (Temp_int[0].xxxx).xyz).x;
    //Instruction 13
    //UTOF
    Temp_int[1].x = floatBitsToInt(vec4(Temp_int[1].x).x);
    //Instruction 14
    //STORE_STRUCTURED
    UAV1[Temp_int[0].z].r = (Temp_int[1].x);
    //Instruction 15
    //LD_UAV_TYPED
    Temp_int[0].z = imageLoad(UAV6, (Temp_int[0].xxxx).xy).z;
    //Instruction 16
    //LD_UAV_TYPED
    Temp_int[0].x = imageLoad(UAV7, (Temp_int[0].xxxx).xyz).x;
    //Instruction 17
    //UTOF
    Temp_int[0].xz = floatBitsToInt(vec4(Temp_int[0].xxzx).xz);
    //Instruction 18
    //STORE_STRUCTURED
    UAV1[Temp_int[0].y].g = (Temp_int[0].z);
    //Instruction 19
    //STORE_STRUCTURED
    UAV1[Temp_int[0].w].b = (Temp_int[0].x);
    //Instruction 20
    //LD_RAW
    Temp_int[0].x = floatBitsToInt(RawRes1[Input0.x + 0]);
    //Instruction 21
    //MOV
    Output0 = vec4(intBitsToFloat(Temp_int[0].xxxx)).xyzw;
    //Instruction 22
    //RET
    return;
}
