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
	vec4 g_mWorld[4];
	vec4 g_mView[4];
	vec4 g_mProj[4];
	vec4 g_BoxInstance_Position;
	vec4 g_BoxInstance_Color;
	vec4 g_vBoxInstance_Position[120];
	vec4 g_vBoxInstance_Color[120];
} GlobalsVS;
 in  vec4 dcl_Input0;
vec4 Input0;
 in  vec4 dcl_Input2;
vec4 Input2;
 in  vec4 dcl_Input3;
vec4 Input3;
 out  vec4 VtxGeoOutput0;
#define Output0 VtxGeoOutput0
 out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
 out  vec4 VtxGeoOutput2;
#define Output2 VtxGeoOutput2
vec4 Temp[3];
ivec4 Temp_int[3];
uvec4 Temp_uint[3];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input2 = dcl_Input2;
    Input3 = dcl_Input3;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Temp_int[0].y = ivec4(floatBitsToInt(Input0.y)).y;
    //Instruction 1
    //FTOU
    Temp_int[0].w = int((Input3.x));
    //Instruction 2
    //MUL
    Temp_int[1].x = floatBitsToInt(6.283000 * GlobalsVS.g_vBoxInstance_Position[Temp_int[0].w + 0].w);
    //Instruction 3
    //SINCOS
    Temp_int[1].x = floatBitsToInt(vec4(sin(intBitsToFloat(Temp_int[1]).x)).x);
    Temp_int[2].x = floatBitsToInt(vec4(cos(intBitsToFloat(Temp_int[1]).x)).x);
    //Instruction 4
    //MUL
    Temp_int[1].xy = floatBitsToInt(intBitsToFloat(Temp_int[1]).xxxx * Input0.zxzz).xy;
    //Instruction 5
    //MAD
    Temp_int[0].x = floatBitsToInt(Input0.x * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[1]).x);
    //Instruction 6
    //MAD
    Temp_int[0].z = floatBitsToInt(Input0.z * intBitsToFloat(Temp_int[2]).x + -intBitsToFloat(Temp_int[1]).y);
    //Instruction 7
    //MAD
    Temp_int[1].xyz = floatBitsToInt(vec4(GlobalsVS.g_vBoxInstance_Position[Temp_int[0].w + 0].xyzx * vec4(32.000000, 32.000000, 32.000000, 0.000000) + intBitsToFloat(Temp_int[0]).xyzx)).xyz;
    //Instruction 8
    //MOV
    Output1 = vec4(GlobalsVS.g_vBoxInstance_Color[Temp_int[0].w + 0]).xyzw;
    //Instruction 9
    //MOV
    Temp_int[1].w = ivec4(floatBitsToInt(Input0.w)).w;
    //Instruction 10
    //ADD
    Temp_int[0] = floatBitsToInt(intBitsToFloat(Temp_int[1]) + vec4(-16.000000, -16.000000, -16.000000, 0.000000));
    //Instruction 11
    //DP4
    Temp_int[1].x = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[0]), GlobalsVS.g_mWorld[0])).x);
    //Instruction 12
    //DP4
    Temp_int[1].y = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[0]), GlobalsVS.g_mWorld[1])).y);
    //Instruction 13
    //DP4
    Temp_int[1].z = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[0]), GlobalsVS.g_mWorld[2])).z);
    //Instruction 14
    //DP4
    Temp_int[1].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[0]), GlobalsVS.g_mWorld[3])).w);
    //Instruction 15
    //DP4
    Temp_int[0].x = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[1]), GlobalsVS.g_mView[0])).x);
    //Instruction 16
    //DP4
    Temp_int[0].y = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[1]), GlobalsVS.g_mView[1])).y);
    //Instruction 17
    //DP4
    Temp_int[0].z = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[1]), GlobalsVS.g_mView[2])).z);
    //Instruction 18
    //DP4
    Temp_int[0].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[1]), GlobalsVS.g_mView[3])).w);
    //Instruction 19
    //DP4
    Output0.x = (vec4(dot(intBitsToFloat(Temp_int[0]), GlobalsVS.g_mProj[0])).x);
    //Instruction 20
    //DP4
    Output0.y = (vec4(dot(intBitsToFloat(Temp_int[0]), GlobalsVS.g_mProj[1])).y);
    //Instruction 21
    //DP4
    Output0.z = (vec4(dot(intBitsToFloat(Temp_int[0]), GlobalsVS.g_mProj[2])).z);
    //Instruction 22
    //DP4
    Output0.w = (vec4(dot(intBitsToFloat(Temp_int[0]), GlobalsVS.g_mProj[3])).w);
    //Instruction 23
    //MOV
    Output2.xy = vec4(Input2.xyxx).xy;
    //Instruction 24
    //RET
    return;
}
