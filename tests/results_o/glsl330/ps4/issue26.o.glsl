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
uniform sampler2D ITex0_X_smpLinClamp;
uniform sampler2D ITex0;
 in  vec4 VtxGeoOutput0;
vec4 Input0;
 in  vec4 VtxGeoOutput1;
vec4 Input1;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    Input1 = VtxGeoOutput1;
    //--- End Early Main ---
    //Instruction 0
    //LT
    Temp[0].xy = uintBitsToFloat(uvec2(lessThan(vec4(0.000000, 0.000000, 0.000000, 0.000000), Input0.xyxx)) * 0xFFFFFFFFu);
    //Instruction 1
    //INOT
    Temp[0].zw = intBitsToFloat(~floatBitsToInt(Temp[0]).xy);
    //Instruction 2
    //IEQ
    Temp[0].z = uintBitsToFloat((floatBitsToInt(Temp[0]).z==floatBitsToInt(Temp[0]).w) ? 0xFFFFFFFFu : 0u);
    //Instruction 3
    //ADD
    Temp[1].xy = Input0.xx + vec2(7.000000, 12.000000);
    //Instruction 4
    //MOVC
    Temp[0].z = (floatBitsToInt(Temp[0]).z != 0) ? Temp[1].y : Input0.x;
    //Instruction 5
    //MOVC
    Temp[0].y = (floatBitsToInt(Temp[0]).y != 0) ? Input0.x : Temp[1].x;
    //Instruction 6
    //MOVC
    Temp[0].x = (floatBitsToInt(Temp[0]).x != 0) ? Temp[0].z : Temp[0].y;
    //Instruction 7
    //MOV
    Temp[0].y = Input0.y;
    //Instruction 8
    //SAMPLE
    Temp[0] = texture(ITex0_X_smpLinClamp, Temp[0].xy);
    //Instruction 9
    //MUL
    Output0 = Temp[0] * Input1;
    //Instruction 10
    //RET
    return;
}
