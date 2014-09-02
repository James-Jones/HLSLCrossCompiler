#version 120
int RepCounter;
int LoopCounter;
int ZeroBasedCounter;
ivec4 Address;
varying vec4 OffsetColour;
varying vec4 BaseColour;
varying vec4 Fog;
varying vec4 TexCoord0;
varying vec4 TexCoord1;
varying vec4 TexCoord2;
varying vec4 TexCoord3;
varying vec4 TexCoord4;
varying vec4 TexCoord5;
varying vec4 TexCoord6;
varying vec4 TexCoord7;
struct vec1 {
	float x;
};
struct ivec1 {
	int x;
};
const vec4 ImmConst12 = vec4(0.999970, 0.500000, 6.283185, -3.141593);
const vec4 ImmConst13 = vec4(32.000000, -16.000000, 0.000000, 0.000000);
const vec4 ImmConst14 = vec4(-0.000002, -0.000022, 0.002604, 0.000260);
const vec4 ImmConst15 = vec4(-0.020833, -0.125000, 1.000000, 0.500000);
 attribute  vec4 dcl_Input0;
vec4 Input0;
 attribute  vec4 dcl_Input1;
vec4 Input1;
 attribute  vec4 dcl_Input2;
vec4 Input2;
vec4 Temp[3];
ivec4 Temp_int[3];
uniform struct GlobalsVS_Type {
	mat4 g_mProj;
	mat4 g_mView;
	mat4 g_mWorld;
	vec4 g_vBoxInstance_Color[120];
	vec4 g_vBoxInstance_Position[120];
} GlobalsVS;
vec4 ImmConstArray [4];
void main()
{
    //--- Start Early Main ---
    ImmConstArray[0] = ImmConst12;
    ImmConstArray[1] = ImmConst13;
    ImmConstArray[2] = ImmConst14;
    ImmConstArray[3] = ImmConst15;
    Input0 = dcl_Input0;
    Input1 = dcl_Input1;
    Input2 = dcl_Input2;
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //FRC
    Temp[0].x = fract(Input2.x);
    //Instruction 1
    //ADD
    Temp[0].x = (-Temp[0].x) + Input2.x;
    //Instruction 2
    //ROUND_NI
    Address.x = int(floor(Temp[0].x));
    //Instruction 3
    //MOV
    Temp[0] = GlobalsVS.g_vBoxInstance_Position[Address.x];
    //Instruction 4
    //MAD
    Temp[0].w = Temp[0].w * ImmConst12.x + ImmConst12.y;
    //Instruction 5
    //FRC
    Temp[0].w = fract(Temp[0].w);
    //Instruction 6
    //MAD
    Temp[0].w = Temp[0].w * ImmConst12.z + ImmConst12.w;
    //Instruction 7
    //SINCOS
    Temp[1].x = sin(Temp[0].w);
    Temp[1].y = cos(Temp[0].w);
    //Instruction 8
    //MUL
    Temp[1].yzw = Temp[1].xyy * Input0.xzx;
    //Instruction 9
    //MAD
    Temp[2].z = Input0.z * Temp[1].x + (-Temp[1].w);
    //Instruction 10
    //ADD
    Temp[2].x = Temp[1].z + Temp[1].y;
    //Instruction 11
    //MOV
    Temp[2].y = Input0.y;
    //Instruction 12
    //MAD
    Temp[0].xyz = Temp[0].xyz * ImmConst13.x + Temp[2].xyz;
    //Instruction 13
    //MOV
    BaseColour = GlobalsVS.g_vBoxInstance_Color[Address.x];
    //Instruction 14
    //MOV
    Temp[0].w = Input0.w;
    //Instruction 15
    //ADD
    Temp[0] = Temp[0] + ImmConst13.yyyz;
    //Instruction 16
    //DP4
    Temp[1].x = dot(Temp[0], GlobalsVS.g_mWorld[0]);
    //Instruction 17
    //DP4
    Temp[1].y = dot(Temp[0], GlobalsVS.g_mWorld[1]);
    //Instruction 18
    //DP4
    Temp[1].z = dot(Temp[0], GlobalsVS.g_mWorld[2]);
    //Instruction 19
    //DP4
    Temp[1].w = dot(Temp[0], GlobalsVS.g_mWorld[3]);
    //Instruction 20
    //DP4
    Temp[0].x = dot(Temp[1], GlobalsVS.g_mView[0]);
    //Instruction 21
    //DP4
    Temp[0].y = dot(Temp[1], GlobalsVS.g_mView[1]);
    //Instruction 22
    //DP4
    Temp[0].z = dot(Temp[1], GlobalsVS.g_mView[2]);
    //Instruction 23
    //DP4
    Temp[0].w = dot(Temp[1], GlobalsVS.g_mView[3]);
    //Instruction 24
    //DP4
    gl_Position.x = dot(Temp[0], GlobalsVS.g_mProj[0]);
    //Instruction 25
    //DP4
    gl_Position.y = dot(Temp[0], GlobalsVS.g_mProj[1]);
    //Instruction 26
    //DP4
    gl_Position.z = dot(Temp[0], GlobalsVS.g_mProj[2]);
    //Instruction 27
    //DP4
    gl_Position.w = dot(Temp[0], GlobalsVS.g_mProj[3]);
    //Instruction 28
    //MOV
    TexCoord0.xy = Input1.xy;
    //Instruction 29
    //RET
    return;
}
