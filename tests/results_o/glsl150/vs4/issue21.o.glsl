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
 in  vec4 dcl_Input0;
vec4 Input0;
 out  vec4 VtxGeoOutput0;
#define Output0 VtxGeoOutput0
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //EQ
    Temp_int[0].xy = floatBitsToInt(ivec2(equal(vec4(Input0.xyxx).xy, vec4(vec4(1.000000, 1.000000, 0.000000, 0.000000)).xy)) * int(0xFFFFFFFF));
    //Instruction 1
    //AND
    Temp_int[0].x = Temp_int[0].y & Temp_int[0].x;
    //Instruction 2
    //MOVC
    if(ivec4(Temp_int[0].xxxx).x != 0) {
        Output0 = ivec4(0x0, 0x0, 0x0, 0x0);
    } else {
        Output0 = ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000);
    }
    //Instruction 3
    //RET
    return;
}
