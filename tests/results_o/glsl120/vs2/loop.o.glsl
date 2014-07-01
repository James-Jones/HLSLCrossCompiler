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
	vec4 g_mW2C[4];
	vec4 vJointMatrix[4 * 48];
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
    Temp[1].xyz = vec4(ImmConst196.w).xyz;
    //Instruction 2
    //LOOP
    for(LoopCounter = IntImmConst0.xyzw.y, ZeroBasedCounter = 0;ZeroBasedCounter < IntImmConst0.xyzw.x;LoopCounter += IntImmConst0.xyzw.z, ZeroBasedCounter++){
        //Instruction 3
        //DP4
        Temp[1].w = (vec4(dot(Input3.xyzw, ImmConstArray[1 + LoopCounter].xyzw)).w);
        //Instruction 4
        //DP4
        Temp[2].x = (vec4(dot(Input4.xyzw, ImmConstArray[1 + LoopCounter].xyzw)).x);
        //Instruction 5
        //FRC
        Temp[2].y = (vec4(fract(Temp[1].w)).y);
        //Instruction 6
        //MOV
        Temp[2].y = vec4(-Temp[2].y).y;
        //Instruction 7
        //ADD
        Temp[1].w = (Temp[1].w + Temp[2].y);
        //Instruction 8
        //MUL
        Temp[1].w = (Temp[1].w * ImmConst200.x);
        //Instruction 9
        //ROUND_NI
        Address.x = (ivec4(floor(Temp[1].w)).x);
        //Instruction 10
        //MOV
        Temp[3] = vec4(GlobalsVS.vJointMatrix[Address.x].xyzw).xyzw;
        //Instruction 11
        //MOV
        Temp[4] = vec4(GlobalsVS.vJointMatrix[Address.x].xyzw).xyzw;
        //Instruction 12
        //MOV
        Temp[5] = vec4(GlobalsVS.vJointMatrix[Address.x].xyzw).xyzw;
        //Instruction 13
        //MOV
        Temp[6] = vec4(GlobalsVS.vJointMatrix[Address.x].xyzw).xyzw;
        //Instruction 14
        //DP4
        Temp[7].x = (vec4(dot(Input0.xyzw, Temp[3].xyzw)).x);
        //Instruction 15
        //DP4
        Temp[7].y = (vec4(dot(Input0.xyzw, Temp[4].xyzw)).y);
        //Instruction 16
        //DP4
        Temp[7].z = (vec4(dot(Input0.xyzw, Temp[5].xyzw)).z);
        //Instruction 17
        //DP4
        Temp[7].w = (vec4(dot(Input0.xyzw, Temp[6].xyzw)).w);
        //Instruction 18
        //MUL
        Temp[6] = (Temp[2].x * Temp[7].xyzw);
        //Instruction 19
        //ADD
        Temp[0] = (Temp[0].xyzw + Temp[6].xyzw);
        //Instruction 20
        //DP3
        Temp[3].x = (vec4(dot((Input1.xyzw).xyz, (Temp[3].xyzw).xyz)).x);
        //Instruction 21
        //DP3
        Temp[3].y = (vec4(dot((Input1.xyzw).xyz, (Temp[4].xyzw).xyz)).y);
        //Instruction 22
        //DP3
        Temp[3].z = (vec4(dot((Input1.xyzw).xyz, (Temp[5].xyzw).xyz)).z);
        //Instruction 23
        //MUL
        Temp[2].xyz = (Temp[2].x * Temp[3].xyzw).xyz;
        //Instruction 24
        //ADD
        Temp[1].xyz = (Temp[1].xyzw + Temp[2].xyzw).xyz;
        //Instruction 25
    //ENDLOOP
    }
    //Instruction 26
    //DP4
    Temp[2].x = (vec4(dot(Temp[0].xyzw, GlobalsVS.g_mW2C[0].xyzw)).x);
    //Instruction 27
    //DP4
    Temp[2].y = (vec4(dot(Temp[0].xyzw, GlobalsVS.g_mW2C[1].xyzw)).y);
    //Instruction 28
    //DP4
    Temp[2].z = (vec4(dot(Temp[0].xyzw, GlobalsVS.g_mW2C[2].xyzw)).z);
    //Instruction 29
    //DP4
    Temp[2].w = (vec4(dot(Temp[0].xyzw, GlobalsVS.g_mW2C[3].xyzw)).w);
    //Instruction 30
    //MOV
    Temp[0].xy = vec4(Input2.xyzw).xy;
    //Instruction 31
    //MOV
    Temp[0].y = vec4(-Temp[0].y).y;
    //Instruction 32
    //ADD
    Temp[0].y = (Temp[0].y + ImmConst196.x);
    //Instruction 33
    //MOV
    gl_Position = vec4(Temp[2].xyzw).xyzw;
    //Instruction 34
    //MOV
    TexCoord0.xyz = vec4(Temp[1].xyzw).xyz;
    //Instruction 35
    //MOV
    TexCoord2.x = vec4(Temp[0].x).x;
    //Instruction 36
    //MOV
    TexCoord2.y = vec4(Temp[0].y).y;
    //Instruction 37
    //RET
    return;
}
