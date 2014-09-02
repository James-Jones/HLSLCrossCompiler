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
 in  vec4 VtxGeoOutput0;
vec4 Input0;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //DERIV_RTX
    Temp[0] = dFdx(Input0);
    //Instruction 1
    //DERIV_RTY
    Temp[1] = dFdy(Input0);
    //Instruction 2
    //MUL
    Output0 = Temp[0] * Temp[1];
    //Instruction 3
    //RET
    return;
}
