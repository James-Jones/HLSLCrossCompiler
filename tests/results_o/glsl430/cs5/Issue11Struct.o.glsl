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
shared struct {float value[7];}TGSM0[64];
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
    Temp_int[0].x = floatBitsToInt(texelFetch(Input, ivec2((Temp_int[0]).xy), 0).x);
    //Instruction 3
    //STORE_STRUCTURED
    TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
    //Instruction 4
    //ADD
    Temp_int[0].yz = floatBitsToInt(-intBitsToFloat(Temp_int[0]).xxxx + vec4(0.000000, 1.000000, 0.500000, 0.000000)).yz;
    //Instruction 5
    //STORE_STRUCTURED
    TGSM0[gl_LocalInvocationIndex.x].value[20u/4u  + 0] = intBitsToFloat(Temp_int[0].yzyy.x);
    TGSM0[gl_LocalInvocationIndex.x].value[20u/4u  + 1] = intBitsToFloat(Temp_int[0].yzyy.y);
    //Instruction 6
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 7
    //ULT
    Temp_int[1] = (ivec4(lessThan(uvec4(gl_LocalInvocationIndex.xxxx).xyzw, uvec4(uvec4(32u, 16u, 8u, 4u)).xyzw)) * int(0xFFFFFFFF));
    //Instruction 8
    //IF
    if((Temp_int[1].x)!=0){
        //Instruction 9
        //IADD
        Temp_int[0].w = (ivec4(gl_LocalInvocationIndex).x + int(0x20));
        //Instruction 10
        //LD_STRUCTURED
        Temp_int[1].x = floatBitsToInt(TGSM0[Temp_int[0].w].value[0u/4u  + 0]);
        //Instruction 11
        //LD_STRUCTURED
        Temp_int[2].xy.x = floatBitsToInt(TGSM0[Temp_int[0].w].value[20u/4u  + 0]);
        Temp_int[2].xy.y = floatBitsToInt(TGSM0[Temp_int[0].w].value[20u/4u  + 1]);
        //Instruction 12
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[1]).x);
        //Instruction 13
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        //Instruction 14
        //ADD
        Temp_int[0].xy = floatBitsToInt(intBitsToFloat(Temp_int[0]).yzyy + intBitsToFloat(Temp_int[2]).xyxx).xy;
        //Instruction 15
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[20u/4u  + 0] = intBitsToFloat(Temp_int[0].xyxx.x);
        TGSM0[gl_LocalInvocationIndex.x].value[20u/4u  + 1] = intBitsToFloat(Temp_int[0].xyxx.y);
        //Instruction 16
    //ENDIF
    }
    //Instruction 17
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 18
    //IF
    if((Temp_int[1].y)!=0){
        //Instruction 19
        //IADD
        Temp_int[0].x = (ivec4(gl_LocalInvocationIndex).x + int(0x10));
        //Instruction 20
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 0]);
        //Instruction 21
        //LD_STRUCTURED
        Temp_int[0].y = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0]);
        //Instruction 22
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).y);
        //Instruction 23
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        //Instruction 24
    //ENDIF
    }
    //Instruction 25
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 26
    //IF
    if((Temp_int[1].z)!=0){
        //Instruction 27
        //IADD
        Temp_int[0].x = (ivec4(gl_LocalInvocationIndex).x + int(0x8));
        //Instruction 28
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 0]);
        //Instruction 29
        //LD_STRUCTURED
        Temp_int[0].y = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0]);
        //Instruction 30
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).y);
        //Instruction 31
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        //Instruction 32
    //ENDIF
    }
    //Instruction 33
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 34
    //IF
    if((Temp_int[1].w)!=0){
        //Instruction 35
        //IADD
        Temp_int[0].x = (ivec4(gl_LocalInvocationIndex).x + int(0x4));
        //Instruction 36
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 0]);
        //Instruction 37
        //LD_STRUCTURED
        Temp_int[0].y = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0]);
        //Instruction 38
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).y);
        //Instruction 39
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        //Instruction 40
    //ENDIF
    }
    //Instruction 41
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 42
    //ULT
    Temp_int[0].xy = (ivec2(lessThan(uvec4(gl_LocalInvocationIndex.xxxx).xy, uvec4(uvec4(2u, 1u, 0u, 0u)).xy)) * int(0xFFFFFFFF));
    //Instruction 43
    //IF
    if((Temp_int[0].x)!=0){
        //Instruction 44
        //IADD
        Temp_int[0].x = (ivec4(gl_LocalInvocationIndex).x + int(0x2));
        //Instruction 45
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[Temp_int[0].x].value[0u/4u  + 0]);
        //Instruction 46
        //LD_STRUCTURED
        Temp_int[0].z = floatBitsToInt(TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0]);
        //Instruction 47
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).z);
        //Instruction 48
        //STORE_STRUCTURED
        TGSM0[gl_LocalInvocationIndex.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        //Instruction 49
    //ENDIF
    }
    //Instruction 50
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 51
    //IF
    if((Temp_int[0].y)!=0){
        //Instruction 52
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[1u].value[0u/4u  + 0]);
        //Instruction 53
        //LD_STRUCTURED
        Temp_int[0].y = floatBitsToInt(TGSM0[0u].value[0u/4u  + 0]);
        //Instruction 54
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).y);
        //Instruction 55
        //STORE_STRUCTURED
        TGSM0[0u].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
        //Instruction 56
    //ENDIF
    }
    //Instruction 57
    //IF
    if((gl_LocalInvocationIndex.x)==0u){
        //Instruction 58
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[0u].value[0u/4u  + 0]);
        //Instruction 59
        //LD_STRUCTURED
        Temp_int[0].yz.x = floatBitsToInt(TGSM0[0u].value[20u/4u  + 0]);
        Temp_int[0].yz.y = floatBitsToInt(TGSM0[0u].value[20u/4u  + 1]);
        //Instruction 60
        //MAD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[0]).z + intBitsToFloat(Temp_int[0]).x);
        //Instruction 61
        //MUL
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x * 0.015625);
        //Instruction 62
        //STORE_UAV_TYPED
        imageStore(UAV0, ivec2(gl_LocalInvocationID.xy), Temp_int[0].xxxx);
        //Instruction 63
    //ENDIF
    }
    //Instruction 64
    //RET
    return;
}
