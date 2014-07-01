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
	vec4 diffuse;
} GlobalsVS;
uniform struct transformsAVS_Type {
	vec4 modelview[4];
	int unusedTestA;
} transformsAVS;
uniform struct transformsBVS_Type {
	int unusedTestB;
	vec4 projection[4];
} transformsBVS;
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
    //MUL
    Temp_int[0] = floatBitsToInt(transformsAVS.modelview[0] * transformsBVS.projection[0]);
    //Instruction 1
    //DP4
    Output0.x = (vec4(dot(Input0, intBitsToFloat(Temp_int[0]))).x);
    //Instruction 2
    //MUL
    Temp_int[0] = floatBitsToInt(transformsAVS.modelview[1] * transformsBVS.projection[1]);
    //Instruction 3
    //DP4
    Output0.y = (vec4(dot(Input0, intBitsToFloat(Temp_int[0]))).y);
    //Instruction 4
    //MUL
    Temp_int[0] = floatBitsToInt(transformsAVS.modelview[2] * transformsBVS.projection[2]);
    //Instruction 5
    //DP4
    Output0.z = (vec4(dot(Input0, intBitsToFloat(Temp_int[0]))).z);
    //Instruction 6
    //MUL
    Temp_int[0] = floatBitsToInt(transformsAVS.modelview[3] * transformsBVS.projection[3]);
    //Instruction 7
    //DP4
    Output0.w = (vec4(dot(Input0, intBitsToFloat(Temp_int[0]))).w);
    //Instruction 8
    //MOV
    Output1 = vec4(GlobalsVS.diffuse).xyzw;
    //Instruction 9
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
