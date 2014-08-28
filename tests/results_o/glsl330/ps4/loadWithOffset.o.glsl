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
uniform sampler2D Tex;
vec4 Input0;
out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0.xy = gl_FragCoord.xy;
    //--- End Early Main ---
    //Instruction 0
    //FTOI
    Temp_int[0].xy = ivec4((Input0.xyxx)).xy;
    //Instruction 1
    //MOV
    Temp_int[0].zw = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).zw;
    //Instruction 2
    //LD
    Output0 = texelFetchOffset(Tex, ivec2((Temp_int[0]).xy), 0, ivec2(-8, 7));
    //Instruction 3
    //RET
    return;
}
