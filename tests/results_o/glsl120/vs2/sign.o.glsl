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
 attribute  vec4 dcl_Input0;
vec4 Input0;
vec4 Temp[1];
ivec4 Temp_int[1];
uniform struct GlobalsVS_Type {
	float factor;
} GlobalsVS;
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //LT
    Temp[0].x = (((-GlobalsVS.factor)< (GlobalsVS.factor)) ? 1.0 : 0.0);
    //Instruction 1
    //LT
    Temp[0].y = (((GlobalsVS.factor)< (-GlobalsVS.factor)) ? 1.0 : 0.0);
    //Instruction 2
    //ADD
    Temp[0].x = (-Temp[0].y + Temp[0].x);
    //Instruction 3
    //MUL
    gl_Position = (Temp[0].x * Input0.xyzw);
    //Instruction 4
    //RET
    return;
}
