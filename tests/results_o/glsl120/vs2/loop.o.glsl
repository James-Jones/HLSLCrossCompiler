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
const vec4 ImmConst200 = vec4(4.000000, 0.000000, 1.000000, 0.000000);
const vec4 ImmConst196 = vec4(1.000000, 0.000000, 0.000000, 0.000000);
const vec4 ImmConst197 = vec4(0.000000, 1.000000, 0.000000, 0.000000);
const vec4 ImmConst198 = vec4(0.000000, 0.000000, 1.000000, 0.000000);
const vec4 ImmConst199 = vec4(0.000000, 0.000000, 0.000000, 1.000000);
const ivec4 IntImmConst0 = ivec4(0x4, 0x0, 0x1, 0x0);
 attribute  vec4 dcl_Input0;
vec4 Input0;
 attribute  vec4 dcl_Input1;
vec4 Input1;
 attribute  vec4 dcl_Input2;
vec4 Input2;
 attribute  vec4 dcl_Input3;
vec4 Input3;
 attribute  vec4 dcl_Input4;
vec4 Input4;
vec4 Temp[8];
ivec4 Temp_int[8];
uniform struct GlobalsVS_Type {
	mat4 g_mW2C;
	mat4 vJointMatrix[48];
} GlobalsVS;
vec4 ImmConstArray [5];
void main()
{
    //--- Start Early Main ---
    ImmConstArray[0] = ImmConst200;
    ImmConstArray[1] = ImmConst196;
    ImmConstArray[2] = ImmConst197;
    ImmConstArray[3] = ImmConst198;
    ImmConstArray[4] = ImmConst199;
    Input0 = dcl_Input0;
    Input1 = dcl_Input1;
    Input2 = dcl_Input2;
    Input3 = dcl_Input3;
    Input4 = dcl_Input4;
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Temp[0] = vec4(ImmConst196.w);
    //Instruction 1
    //MOV
    Temp[1].xyz = vec3(ImmConst196.w);
    //Instruction 2
    //LOOP
    for(LoopCounter = IntImmConst0.y, ZeroBasedCounter = 0;ZeroBasedCounter < IntImmConst0.x;LoopCounter += IntImmConst0.z, ZeroBasedCounter++){
        //Instruction 3
        //DP4
        Temp[1].w = dot(Input3, ImmConstArray[1 + LoopCounter]);
        //Instruction 4
        //DP4
        Temp[2].x = dot(Input4, ImmConstArray[1 + LoopCounter]);
        //Instruction 5
        //FRC
        Temp[2].y = fract(Temp[1].w);
        //Instruction 6
        //MOV
        Temp[2].y = (-Temp[2].y);
        //Instruction 7
        //ADD
        Temp[1].w = Temp[1].w + Temp[2].y;
        //Instruction 8
        //MUL
        Temp[1].w = Temp[1].w * ImmConst200.x;
        //Instruction 9
        //ROUND_NI
        Address.x = int(floor(Temp[1].w));
        //Instruction 10
        //MOV
        Temp[3] = GlobalsVS.vJointMatrix[(Address.x) / 4][int(mod(float(Address.x), 4.0))];
        //Instruction 11
        //MOV
        Temp[4] = GlobalsVS.vJointMatrix[(Address.x) / 4][int(mod(float(Address.x), 4.0))];
        //Instruction 12
        //MOV
        Temp[5] = GlobalsVS.vJointMatrix[(Address.x) / 4][int(mod(float(Address.x), 4.0))];
        //Instruction 13
        //MOV
        Temp[6] = GlobalsVS.vJointMatrix[(Address.x) / 4][int(mod(float(Address.x), 4.0))];
        //Instruction 14
        //DP4
        Temp[7].x = dot(Input0, Temp[3]);
        //Instruction 15
        //DP4
        Temp[7].y = dot(Input0, Temp[4]);
        //Instruction 16
        //DP4
        Temp[7].z = dot(Input0, Temp[5]);
        //Instruction 17
        //DP4
        Temp[7].w = dot(Input0, Temp[6]);
        //Instruction 18
        //MUL
        Temp[6] = Temp[2].x * Temp[7];
        //Instruction 19
        //ADD
        Temp[0] = Temp[0] + Temp[6];
        //Instruction 20
        //DP3
        Temp[3].x = dot(Input1.xyz, Temp[3].xyz);
        //Instruction 21
        //DP3
        Temp[3].y = dot(Input1.xyz, Temp[4].xyz);
        //Instruction 22
        //DP3
        Temp[3].z = dot(Input1.xyz, Temp[5].xyz);
        //Instruction 23
        //MUL
        Temp[2].xyz = Temp[2].x * Temp[3].xyz;
        //Instruction 24
        //ADD
        Temp[1].xyz = Temp[1].xyz + Temp[2].xyz;
        //Instruction 25
    //ENDLOOP
    }
    //Instruction 26
    //DP4
    Temp[2].x = dot(Temp[0], GlobalsVS.g_mW2C[0]);
    //Instruction 27
    //DP4
    Temp[2].y = dot(Temp[0], GlobalsVS.g_mW2C[1]);
    //Instruction 28
    //DP4
    Temp[2].z = dot(Temp[0], GlobalsVS.g_mW2C[2]);
    //Instruction 29
    //DP4
    Temp[2].w = dot(Temp[0], GlobalsVS.g_mW2C[3]);
    //Instruction 30
    //MOV
    Temp[0].xy = Input2.xy;
    //Instruction 31
    //MOV
    Temp[0].y = (-Temp[0].y);
    //Instruction 32
    //ADD
    Temp[0].y = Temp[0].y + ImmConst196.x;
    //Instruction 33
    //MOV
    gl_Position = Temp[2];
    //Instruction 34
    //MOV
    TexCoord0.xyz = Temp[1].xyz;
    //Instruction 35
    //MOV
    TexCoord2.x = Temp[0].x;
    //Instruction 36
    //MOV
    TexCoord2.y = Temp[0].y;
    //Instruction 37
    //RET
    return;
}
