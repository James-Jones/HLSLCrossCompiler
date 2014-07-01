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
layout(location = 0) uniform sampler2D Input;
writeonly uniform image2D UAV0;
vec4 Temp[3];
ivec4 Temp_int[3];
uvec4 Temp_uint[3];
shared struct {float value[4];}TGSM0[64];
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Temp_int[0].xy = ivec4(gl_GlobalInvocationID.xyxx).xy;
    //Instruction 1
    //MOV
    Temp_int[0].zw = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).zw;
    //Instruction 2
    //LD
    Temp_int[0] = floatBitsToInt(texelFetch(Input, ivec2((Temp_int[0]).xy), 0));
    //Instruction 3
    //STORE_STRUCTURED
    TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
    TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1] = intBitsToFloat(Temp_int[0].y);
    TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2] = intBitsToFloat(Temp_int[0].z);
    TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3] = intBitsToFloat(Temp_int[0].w);
    //Instruction 4
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 5
    //ULT
    Temp_int[1] = (ivec4(lessThan(uvec4(gl_LocalInvocationIndex.xxxx).xyzw, uvec4(uvec4(32u, 16u, 8u, 4u)).xyzw)) * int(0xFFFFFFFF));
    //Instruction 6
    //IF
    if((Temp_int[1].x)!=0){
        //Instruction 7
        //IADD
        Temp_int[1].x = (ivec4(gl_LocalInvocationIndex).x + int(0x20));
        //Instruction 8
        //LD_STRUCTURED
        Temp_int[2].x = floatBitsToInt(TGSM0[Temp_int[1].x].value[0u/4u  + 0]);
        Temp_int[2].y = floatBitsToInt(TGSM0[Temp_int[1].x].value[0u/4u  + 1]);
        Temp_int[2].z = floatBitsToInt(TGSM0[Temp_int[1].x].value[0u/4u  + 2]);
        Temp_int[2].w = floatBitsToInt(TGSM0[Temp_int[1].x].value[0u/4u  + 3]);
        //Instruction 9
        //ADD
        Temp_int[0] = floatBitsToInt(intBitsToFloat(Temp_int[0]) + intBitsToFloat(Temp_int[2]));
        //Instruction 10
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1] = intBitsToFloat(Temp_int[0].y);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2] = intBitsToFloat(Temp_int[0].z);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3] = intBitsToFloat(Temp_int[0].w);
        //Instruction 11
    //ENDIF
    }
    //Instruction 12
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 13
    //IF
    if((Temp_int[1].y)!=0){
        //Instruction 14
        //IADD
        Temp_int[0].x = (ivec4(gl_LocalInvocationIndex).x + int(0x10));
        //Instruction 15
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 0]);
        Temp_int[0].y = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 1]);
        Temp_int[0].z = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 2]);
        Temp_int[0].w = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 3]);
        //Instruction 16
        //LD_STRUCTURED
        Temp_int[2].x = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0]);
        Temp_int[2].y = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1]);
        Temp_int[2].z = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2]);
        Temp_int[2].w = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3]);
        //Instruction 17
        //ADD
        Temp_int[0] = floatBitsToInt(intBitsToFloat(Temp_int[0]) + intBitsToFloat(Temp_int[2]));
        //Instruction 18
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1] = intBitsToFloat(Temp_int[0].y);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2] = intBitsToFloat(Temp_int[0].z);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3] = intBitsToFloat(Temp_int[0].w);
        //Instruction 19
    //ENDIF
    }
    //Instruction 20
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 21
    //IF
    if((Temp_int[1].z)!=0){
        //Instruction 22
        //IADD
        Temp_int[0].x = (ivec4(gl_LocalInvocationIndex).x + int(0x8));
        //Instruction 23
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 0]);
        Temp_int[0].y = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 1]);
        Temp_int[0].z = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 2]);
        Temp_int[0].w = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 3]);
        //Instruction 24
        //LD_STRUCTURED
        Temp_int[2].x = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0]);
        Temp_int[2].y = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1]);
        Temp_int[2].z = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2]);
        Temp_int[2].w = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3]);
        //Instruction 25
        //ADD
        Temp_int[0] = floatBitsToInt(intBitsToFloat(Temp_int[0]) + intBitsToFloat(Temp_int[2]));
        //Instruction 26
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1] = intBitsToFloat(Temp_int[0].y);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2] = intBitsToFloat(Temp_int[0].z);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3] = intBitsToFloat(Temp_int[0].w);
        //Instruction 27
    //ENDIF
    }
    //Instruction 28
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 29
    //IF
    if((Temp_int[1].w)!=0){
        //Instruction 30
        //IADD
        Temp_int[0].x = (ivec4(gl_LocalInvocationIndex).x + int(0x4));
        //Instruction 31
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 0]);
        Temp_int[0].y = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 1]);
        Temp_int[0].z = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 2]);
        Temp_int[0].w = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 3]);
        //Instruction 32
        //LD_STRUCTURED
        Temp_int[1].x = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0]);
        Temp_int[1].y = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1]);
        Temp_int[1].z = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2]);
        Temp_int[1].w = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3]);
        //Instruction 33
        //ADD
        Temp_int[0] = floatBitsToInt(intBitsToFloat(Temp_int[0]) + intBitsToFloat(Temp_int[1]));
        //Instruction 34
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1] = intBitsToFloat(Temp_int[0].y);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2] = intBitsToFloat(Temp_int[0].z);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3] = intBitsToFloat(Temp_int[0].w);
        //Instruction 35
    //ENDIF
    }
    //Instruction 36
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 37
    //ULT
    Temp_int[0].xy = (ivec2(lessThan(uvec4(gl_LocalInvocationIndex.xxxx).xy, uvec4(uvec4(2u, 1u, 0u, 0u)).xy)) * int(0xFFFFFFFF));
    //Instruction 38
    //IF
    if((Temp_int[0].x)!=0){
        //Instruction 39
        //IADD
        Temp_int[0].x = (ivec4(gl_LocalInvocationIndex).x + int(0x2));
        //Instruction 40
        //LD_STRUCTURED
        Temp_int[1].x = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 0]);
        Temp_int[1].y = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 1]);
        Temp_int[1].z = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 2]);
        Temp_int[1].w = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 3]);
        //Instruction 41
        //LD_STRUCTURED
        Temp_int[2].x = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0]);
        Temp_int[2].y = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1]);
        Temp_int[2].z = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2]);
        Temp_int[2].w = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3]);
        //Instruction 42
        //ADD
        Temp_int[1] = floatBitsToInt(intBitsToFloat(Temp_int[1]) + intBitsToFloat(Temp_int[2]));
        //Instruction 43
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[1].x);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 1] = intBitsToFloat(Temp_int[1].y);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 2] = intBitsToFloat(Temp_int[1].z);
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 3] = intBitsToFloat(Temp_int[1].w);
        //Instruction 44
    //ENDIF
    }
    //Instruction 45
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 46
    //IF
    if((Temp_int[0].y)!=0){
        //Instruction 47
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[1u].value[0u/4u  + 0]);
        Temp_int[0].y = floatBitsToInt(TGSM0[1u].value[0u/4u  + 1]);
        Temp_int[0].z = floatBitsToInt(TGSM0[1u].value[0u/4u  + 2]);
        Temp_int[0].w = floatBitsToInt(TGSM0[1u].value[0u/4u  + 3]);
        //Instruction 48
        //LD_STRUCTURED
        Temp_int[1].x = floatBitsToInt(TGSM0[0u].value[0u/4u  + 0]);
        Temp_int[1].y = floatBitsToInt(TGSM0[0u].value[0u/4u  + 1]);
        Temp_int[1].z = floatBitsToInt(TGSM0[0u].value[0u/4u  + 2]);
        Temp_int[1].w = floatBitsToInt(TGSM0[0u].value[0u/4u  + 3]);
        //Instruction 49
        //ADD
        Temp_int[0] = floatBitsToInt(intBitsToFloat(Temp_int[0]) + intBitsToFloat(Temp_int[1]));
        //Instruction 50
        //STORE_STRUCTURED
        TGSM0[0u].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        TGSM0[0u].value[0u/4u  + 1] = intBitsToFloat(Temp_int[0].y);
        TGSM0[0u].value[0u/4u  + 2] = intBitsToFloat(Temp_int[0].z);
        TGSM0[0u].value[0u/4u  + 3] = intBitsToFloat(Temp_int[0].w);
        //Instruction 51
    //ENDIF
    }
    //Instruction 52
    //IF
    if((gl_LocalInvocationIndex.x)==0u){
        //Instruction 53
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[0u].value[0u/4u  + 0]);
        Temp_int[0].y = floatBitsToInt(TGSM0[0u].value[0u/4u  + 1]);
        Temp_int[0].z = floatBitsToInt(TGSM0[0u].value[0u/4u  + 2]);
        Temp_int[0].w = floatBitsToInt(TGSM0[0u].value[0u/4u  + 3]);
        //Instruction 54
        //MUL
        Temp_int[0] = floatBitsToInt(intBitsToFloat(Temp_int[0]) * vec4(0.015625, 0.015625, 0.015625, 0.015625));
        //Instruction 55
        //STORE_UAV_TYPED
        imageStore(UAV0, ivec2(gl_LocalInvocationID.xy), Temp_int[0]);
        //Instruction 56
    //ENDIF
    }
    //Instruction 57
    //RET
    return;
}
