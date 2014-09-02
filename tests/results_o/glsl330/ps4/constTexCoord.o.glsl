#version 330
struct vec1 {
	float x;
};
struct uvec1 {
	uint x;
};
struct ivec1 {
	int x;
};
uniform sampler2D Texture0_X_TextureSampler;
uniform sampler2D Texture0;
layout(location = 0) out  vec4 PixOutput0;
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
    Temp[0] = texture(Texture0_X_TextureSampler, vec2(0.500000, 0.500000));
    //Instruction 1
    //MOV
    Output0 = Temp[0].xxxx;
    //Instruction 2
    //RET
    return;
}
