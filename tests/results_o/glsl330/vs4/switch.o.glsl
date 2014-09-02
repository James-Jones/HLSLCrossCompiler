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
	int SwitchValue;
} GlobalsVS;
 in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //SWITCH
    switch(int(GlobalsVS.SwitchValue)){
            //Instruction 1
        //case
        case int(0x0):
            //Instruction 2
            //MOV
            Temp_int[0] = ivec4(ivec4(0x3F800000, 0x0, 0x0, 0x3F800000)).xyzw;
            //Instruction 3
            //BREAK
            break;
            //Instruction 4
        //case
        case int(0x1):
            //Instruction 5
            //MOV
            Temp_int[0] = ivec4(ivec4(0x3F800000, 0x3F800000, 0x0, 0x3F800000)).xyzw;
            //Instruction 6
            //BREAK
            break;
            //Instruction 7
        default:
            //Instruction 8
            //MOV
            Temp_int[0] = ivec4(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).xyzw;
            //Instruction 9
            //BREAK
            break;
            //Instruction 10
        //ENDIF
        }
        //Instruction 11
        //MOV
        Output1 = vec4(intBitsToFloat(Temp_int[0])).xyzw;
        //Instruction 12
        //MOV
        Output0 = vec4(Input0).xyzw;
        //Instruction 13
        //RET
        //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
        //--- End post shader code ---
        return;
}
