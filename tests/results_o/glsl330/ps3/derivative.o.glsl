#version 330
int RepCounter;
int LoopCounter;
int ZeroBasedCounter;
in vec4 OffsetColour;
in vec4 BaseColour;
in vec4 Fog;
in vec4 TexCoord0;
in vec4 TexCoord1;
in vec4 TexCoord2;
in vec4 TexCoord3;
in vec4 TexCoord4;
in vec4 TexCoord5;
in vec4 TexCoord6;
in vec4 TexCoord7;
out vec4 outFragData[8];
#define Output0 outFragData[0]
#define Output1 outFragData[1]
#define Output2 outFragData[2]
#define Output3 outFragData[3]
#define Output4 outFragData[4]
#define Output5 outFragData[5]
#define Output6 outFragData[6]
#define Output7 outFragData[7]
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
    Temp[0] = dFdx(TexCoord0);
    //Instruction 1
    //DERIV_RTY
    Temp[1] = dFdy(TexCoord0);
    //Instruction 2
    //MUL
    Output0 = Temp[0] * Temp[1];
    //Instruction 3
    //RET
    return;
}
