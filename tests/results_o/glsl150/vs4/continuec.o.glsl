#version 150
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
uniform struct GlobalsVS_Type {
	int p0;
	int p1;
	int p2;
} GlobalsVS;
 in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
vec4 Temp[3];
ivec4 Temp_int[3];
uvec4 Temp_uint[3];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Temp_int[1].xy = ivec4(GlobalsVS.p1).xy;
    //Instruction 1
    //MOV
    Temp_int[0] = ivec4(floatBitsToInt(Input0)).xyzw;
    //Instruction 2
    //LOOP
    while(true){
        //Instruction 3
        //LT
        Temp_int[1].z = floatBitsToInt(((100.000000)< (intBitsToFloat(Temp_int[0]).x)) ? int(0xFFFFFFFF) : 0);
        //Instruction 4
        //BREAKC
        if((Temp_int[1].z)!=0){break;}
        //Instruction 5
        //CONTINUEC
        if((Temp_int[1].x)==0){continue;}
        //Instruction 6
        //ADD
        Temp_int[2] = floatBitsToInt(intBitsToFloat(Temp_int[0]) + intBitsToFloat(Temp_int[0]));
        //Instruction 7
        //INE
        Temp_int[1].z = (((Temp_int[1].y)!= (int(0x0))) ? int(0xFFFFFFFF) : 0);
        //Instruction 8
        //MOVC
        if(ivec4(Temp_int[1].y).x != 0) {
            Temp_int[1].w = Temp_int[1].y;
        } else {
            Temp_int[1].w = int(0x0);
        }
        //Instruction 9
        //MOV
        Temp_int[0] = ivec4(Temp_int[2]).xyzw;
        //Instruction 10
        //MOV
        Temp_int[1].y = ivec4(Temp_int[1].w).y;
        //Instruction 11
        //CONTINUEC
        if((Temp_int[1].z)!=0){continue;}
        //Instruction 12
        //MOV
        Temp_int[0] = ivec4(Temp_int[2]).xyzw;
        //Instruction 13
    //ENDLOOP
    }
    //Instruction 14
    //MOV
    Output0 = vec4(intBitsToFloat(Temp_int[0])).xyzw;
    //Instruction 15
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
