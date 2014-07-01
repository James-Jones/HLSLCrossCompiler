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
uniform sampler2D Texture0;
out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    //Instruction 0
    //SAMPLE
    Temp_int[0] = floatBitsToInt(texture(Texture0, vec4(0.500000, 0.500000, 0.000000, 0.000000).xy));
    //Instruction 1
    //MOV
    Output0 = vec4(intBitsToFloat(Temp_int[0].xxxx)).xyzw;
    //Instruction 2
    //RET
    return;
}
