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
uniform sampler2D Texture_X_Texture;
uniform sampler2D Texture;
 in  vec4 VtxGeoOutput0;
vec4 Input0;
 in  vec4 VtxGeoOutput1;
vec4 Input1;
layout(location = 0) out  vec4 PixOutput0;
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
    Temp[0] = texture(Texture_X_Texture, Input0.yz);
    //Instruction 1
    //MUL
    Temp[1].x = Temp[0].w * Input1.x;
    //Instruction 2
    //LT
    Temp[1].x = uintBitsToFloat((0.250980<Temp[1].x) ? 0xFFFFFFFFu : 0u);
    //Instruction 3
    //AND
    Temp[0] = uintBitsToFloat(floatBitsToUint(Temp[0]) & floatBitsToUint(Temp[1]).xxxx);
    //Instruction 4
    //ADD
    Temp[1].x = (-Input1.x) + 1.000000;
    //Instruction 5
    //SAMPLE
    Temp[2] = texture(Texture_X_Texture, Input0.xz);
    //Instruction 6
    //MUL
    Temp[1].x = Temp[1].x * Temp[2].w;
    //Instruction 7
    //LT
    Temp[1].x = uintBitsToFloat((0.250980<Temp[1].x) ? 0xFFFFFFFFu : 0u);
    //Instruction 8
    //MOVC
    Temp[0] = (floatBitsToInt(Temp[1]).xxxx.x != 0) ? Temp[2] : Temp[0];
    //Instruction 9
    //SAMPLE
    Temp[1] = texture(Texture_X_Texture, Input1.zw);
    //Instruction 10
    //MUL
    Temp[2].x = Temp[1].w * Input1.y;
    //Instruction 11
    //LT
    Temp[2].x = uintBitsToFloat((0.250980<Temp[2].x) ? 0xFFFFFFFFu : 0u);
    //Instruction 12
    //MOVC
    Output0 = (floatBitsToInt(Temp[2]).xxxx.x != 0) ? Temp[1] : Temp[0];
    //Instruction 13
    //RET
    return;
}
