#version 400
#extension GL_ARB_shader_bit_encoding : require
#extension GL_ARB_shader_atomic_counters : enable
#extension GL_ARB_shader_storage_buffer_object : enable
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
uniform sampler2D TextureA;
uniform sampler2D TextureB;
struct UAV1_Type {
	uint pixDiff;
	uint pixDiff2;
};
buffer Block1 {
	UAV1_Type UAV1[];
};
 in  vec4 VtxGeoOutput0;
vec4 Input0;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[4];
ivec4 Temp_int[4];
uvec4 Temp_uint[4];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //SAMPLE
    Temp_int[0] = floatBitsToInt(texture(TextureA, Input0.xy));
    //Instruction 1
    //SAMPLE
    Temp_int[1] = floatBitsToInt(texture(TextureB, Input0.xy));
    //Instruction 2
    //ADD
    Temp_int[0] = floatBitsToInt(intBitsToFloat(Temp_int[0]) + -intBitsToFloat(Temp_int[1]));
    //Instruction 3
    //DP4
    Temp_int[0].x = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[0]), intBitsToFloat(Temp_int[0]))).x);
    //Instruction 4
    //NE
    Temp_int[0].x = floatBitsToInt(((intBitsToFloat(Temp_int[0]).x)!= (0.000000)) ? int(0xFFFFFFFF) : 0);
    //Instruction 5
    //IF
    if((Temp_int[0].x)!=0){
        //Instruction 6
        //ATOMIC_IADD
        atomicAdd(UAV1[0].pixDiff, 1u);
        //Instruction 7
        //IMM_ATOMIC_IADD
        Temp_int[0].x = (atomicAdd(UAV1[0].pixDiff, 3u));
        //Instruction 8
    //ELSE
    } else {
        //Instruction 9
        //IMM_ATOMIC_AND
        Temp_int[0].x = (atomicAnd(UAV1[0].pixDiff, 3u));
        //Instruction 10
    //ENDIF
    }
    //Instruction 11
    //IMM_ATOMIC_UMIN
    Temp_int[1].x = (atomicMin(UAV1[0].pixDiff, 6u));
    //Instruction 12
    //IMM_ATOMIC_UMAX
    Temp_int[2].x = (atomicMax(UAV1[0].pixDiff, 6u));
    //Instruction 13
    //ATOMIC_CMP_STORE
    atomicCompSwap(UAV1[0].pixDiff, 2u, uvec4(Temp_int[1]).x);
    //Instruction 14
    //IMM_ATOMIC_XOR
    Temp_int[3].x = (atomicXor(UAV1[0].pixDiff, 15u));
    //Instruction 15
    //ATOMIC_OR
    atomicOr(UAV1[0].pixDiff, uvec4(Temp_int[3]).x);
    //Instruction 16
    //UTOF
    Output0.y = (vec4(Temp_int[0].x).y);
    //Instruction 17
    //UTOF
    Output0.z = (vec4(Temp_int[1].x).z);
    //Instruction 18
    //UTOF
    Output0.w = (vec4(Temp_int[2].x).w);
    //Instruction 19
    //MOV
    Output0.x = vec4(intBitsToFloat(int(0x3F800000))).x;
    //Instruction 20
    //RET
    return;
}
