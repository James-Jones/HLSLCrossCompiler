#version 400
subroutine void SubroutineType();
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
uniform struct RenderTargetParamsVS_Type {
	int Width;
	int Height;
	float AspectRatio;
} RenderTargetParamsVS;
layout(location = 0)  in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //DP2
    Temp[0].x = (vec4(dot((Input0.xyxx).xy, (Input0.xyxx).xy)).x);
    //Instruction 1
    //MIN
    Temp[0].x = (vec4(min(Temp[0].x, 1.000000)).x);
    //Instruction 2
    //ADD
    Output0.xy = (-Temp[0].xxxx + vec4(1.000000, 1.000000, 0.000000, 0.000000)).xy;
    //Instruction 3
    //ISHL
    Temp[0].xy = uintBitsToFloat((uvec4(uvec4(RenderTargetParamsVS.Width)) << uvec4(uvec4(1u, 1u, 0u, 0u))).xy);
    //Instruction 4
    //ITOF
    Output0.zw = (vec4(floatBitsToUint(Temp[0].xxxy)).zw);
    //Instruction 5
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
