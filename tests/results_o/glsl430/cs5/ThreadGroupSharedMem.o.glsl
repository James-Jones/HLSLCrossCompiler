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
layout(binding = 0) buffer Block0 {
	float UAV0[];
};
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
shared struct {float value[1];}TGSM0[128];
layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //IMAD
    Temp_int[0].x = (ivec4(gl_LocalInvocationID).x * int(0x80) + ivec4(gl_WorkGroupID).x);
    //Instruction 1
    //LD_STRUCTURED
    Temp_int[0].x = floatBitsToInt(UAV0[Temp_int[0].x]);
    //Instruction 2
    //STORE_STRUCTURED
    TGSM0[gl_WorkGroupID.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].x);
    //Instruction 3
    //SYNC
    groupMemoryBarrier();
    memoryBarrierShared();
    //Instruction 4
    //MOV
    Temp_int[0].x = ivec4(int(0x1)).x;
    //Instruction 5
    //LOOP
    while(true){
        //Instruction 6
        //UGE
        Temp_int[0].y = (((uvec4(Temp_int[0]).x)>= (128u)) ? int(0xFFFFFFFF) : 0);
        //Instruction 7
        //BREAKC
        if((Temp_int[0].y)!=0){break;}
        //Instruction 8
        //ISHL
        Temp_int[0].y = Temp_int[0].x << int(0x1);
        //Instruction 9
        //UDIV
        //null = (gl_WorkGroupID.x / uvec4(Temp_int[0]).y);
        Temp_int[0].z = (ivec4(mod(int(gl_WorkGroupID.x), int(uvec4(Temp_int[0]).y))).z);
        //Instruction 10
        //IF
        if((Temp_int[0].z)==0){
            //Instruction 11
            //IADD
            Temp_int[0].z = (Temp_int[0].x + ivec4(gl_WorkGroupID).x);
            //Instruction 12
            //LD_STRUCTURED
            Temp_int[0].z = floatBitsToInt(TGSM0[Temp_int[0].z].value[0u/4u  + 0]);
            //Instruction 13
            //LD_STRUCTURED
            Temp_int[0].w = floatBitsToInt(TGSM0[gl_WorkGroupID.x].value[0u/4u  + 0]);
            //Instruction 14
            //ADD
            Temp_int[0].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z + intBitsToFloat(Temp_int[0]).w);
            //Instruction 15
            //STORE_STRUCTURED
            TGSM0[gl_WorkGroupID.x].value[0u/4u  + 0] = intBitsToFloat(Temp_int[0].z);
            //Instruction 16
        //ENDIF
        }
        //Instruction 17
        //SYNC
        groupMemoryBarrier();
        memoryBarrierShared();
        //Instruction 18
        //MOV
        Temp_int[0].x = ivec4(Temp_int[0].y).x;
        //Instruction 19
    //ENDLOOP
    }
    //Instruction 20
    //IF
    if((gl_WorkGroupID.x)==0u){
        //Instruction 21
        //LD_STRUCTURED
        Temp_int[0].x = floatBitsToInt(TGSM0[0u].value[0u/4u  + 0]);
        //Instruction 22
        //STORE_STRUCTURED
        UAV0[gl_LocalInvocationID.x] = (Temp_int[0].x);
        //Instruction 23
    //ENDIF
    }
    //Instruction 24
    //RET
    return;
}
