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
const vec4 ImmConst0 = vec4(-1.000000, -0.000000, 1.000000, 0.000000);
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
vec4 ImmConstArray [1];
void main()
{
    //--- Start Early Main ---
    ImmConstArray[0] = ImmConst0;
    //--- End Early Main ---
    //Instruction 0
    //ADD
    Temp[0].x = (ImmConst0.x + TexCoord0.w);
    //Instruction 1
    //MOVC
    if(ivec4(-abs(Temp[0].x)).x >= 0) {
        Temp[0] = vec4(ImmConst0.x);
    } else {
        Temp[0] = vec4(ImmConst0.y);
    }
    //Instruction 2
    //DISCARD
    if(any(lessThan((Temp[0]), vec4(0)))){discard;}
    //Instruction 3
    //MOV
    Output0 = vec4(ImmConst0.z);
    //Instruction 4
    //RET
    return;
}