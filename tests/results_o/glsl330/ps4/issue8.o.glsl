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
uniform sampler2D Texture;
 in  vec4 VtxGeoOutput0;
vec4 Input0;
 in  vec4 VtxGeoOutput1;
vec4 Input1;
out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[3];
ivec4 Temp_int[3];
uvec4 Temp_uint[3];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    Input1 = VtxGeoOutput1;
    Input1 = VtxGeoOutput1;
    //--- End Early Main ---
    //Instruction 0
    //SAMPLE
    Temp_int[0] = floatBitsToInt(texture(Texture, Input0.yz));
    //Instruction 1
    //MUL
    Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * Input1.x);
    //Instruction 2
    //LT
    Temp_int[1].x = floatBitsToInt(((0.250980)< (intBitsToFloat(Temp_int[1]).x)) ? int(0xFFFFFFFF) : 0);
    //Instruction 3
    //AND
    Temp_int[0] = (Temp_int[0] & Temp_int[1].xxxx);
    //Instruction 4
    //ADD
    Temp_int[1].x = floatBitsToInt(-Input1.x + 1.000000);
    //Instruction 5
    //SAMPLE
    Temp_int[2] = floatBitsToInt(texture(Texture, Input0.xz));
    //Instruction 6
    //MUL
    Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).x * intBitsToFloat(Temp_int[2]).w);
    //Instruction 7
    //LT
    Temp_int[1].x = floatBitsToInt(((0.250980)< (intBitsToFloat(Temp_int[1]).x)) ? int(0xFFFFFFFF) : 0);
    //Instruction 8
    //MOVC
    if(ivec4(Temp_int[1].xxxx).x != 0) {
        Temp_int[0] = Temp_int[2];
    } else {
        Temp_int[0] = Temp_int[0];
    }
    //Instruction 9
    //SAMPLE
    Temp_int[1] = floatBitsToInt(texture(Texture, Input1.zw));
    //Instruction 10
    //MUL
    Temp_int[2].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).w * Input1.y);
    //Instruction 11
    //LT
    Temp_int[2].x = floatBitsToInt(((0.250980)< (intBitsToFloat(Temp_int[2]).x)) ? int(0xFFFFFFFF) : 0);
    //Instruction 12
    //MOVC
    if(ivec4(Temp_int[2].xxxx).x != 0) {
        Output0 = Temp_int[1];
    } else {
        Output0 = Temp_int[0];
    }
    //Instruction 13
    //RET
    return;
}
