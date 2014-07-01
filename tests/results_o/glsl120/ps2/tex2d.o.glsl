#version 120
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
struct ivec1 {
	int x;
};
uniform sampler2D g_samScene;
vec4 Temp[1];
ivec4 Temp_int[1];
uniform struct GlobalsPS_Type {
	vec4 ColOffset;
} GlobalsPS;
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //SAMPLE
    Temp[0] = (texture2D(g_samScene, TexCoord0.xy).xyzw);
    //Instruction 1
    //MAD
    Temp[0] = (vec4(Temp[0].xyzw * BaseColour.xyzw + GlobalsPS.ColOffset.xyzw));
    //Instruction 2
    //MOV
    Output0 = vec4(Temp[0].xyzw).xyzw;
    //Instruction 3
    //RET
    return;
}
