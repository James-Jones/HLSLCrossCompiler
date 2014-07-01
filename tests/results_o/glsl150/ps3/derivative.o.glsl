#version 150
int RepCounter;
int LoopCounter;
int ZeroBasedCounter;
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
#define Output0 gl_FragData[0]
#define Output1 gl_FragData[1]
#define Output2 gl_FragData[2]
#define Output3 gl_FragData[3]
#define Output4 gl_FragData[4]
#define Output5 gl_FragData[5]
#define Output6 gl_FragData[6]
#define Output7 gl_FragData[7]
struct vec1 {
	float x;
};
struct uvec1 {
	uint x;
};
struct ivec1 {
	int x;
};
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //DERIV_RTX
    Temp[0] = (vec4(dFdx(TexCoord0.xyzw)));
    //Instruction 1
    //DERIV_RTY
    Temp[1] = (vec4(dFdy(TexCoord0.xyzw)));
    //Instruction 2
    //MUL
    Output0 = (Temp[0].xyzw * Temp[1].xyzw);
    //Instruction 3
    //RET
    return;
}
