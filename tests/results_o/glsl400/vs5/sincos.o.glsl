#version 400
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
subroutine void SubroutineType();
uniform struct GlobalsVS_Type {
	float angle;
	vec2 angle2;
} GlobalsVS;
layout(location = 0)  in  vec4 dcl_Input0;
vec4 Input0;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //ADD
    Temp_int[0].x = floatBitsToInt(GlobalsVS.angle + GlobalsVS.angle);
    //Instruction 1
    //SINCOS
    Output0.x = (vec4(sin(intBitsToFloat(Temp_int[0]).x)).x);
    //Instruction 2
    //MOV
    Output0.y = vec4(Input0.y).y;
    //Instruction 3
    //SINCOS
    Temp_int[0].x = floatBitsToInt(vec4(sin(GlobalsVS.angle)).x);
    Temp_int[1].x = floatBitsToInt(vec4(cos(GlobalsVS.angle)).x);
    //Instruction 4
    //ADD
    Output0.z = (intBitsToFloat(Temp_int[1]).x + Input0.z);
    //Instruction 5
    //MOV
    Output0.w = vec4(intBitsToFloat(Temp_int[0].x)).w;
    //Instruction 6
    //SINCOS
    Output1.xy = (vec4(sin(GlobalsVS.angle2.xxyx.yzyy)).xy);
    //Instruction 7
    //SINCOS
    Output1.zw = (vec4(cos(GlobalsVS.angle2.xxyx.yyyz)).zw);
    //Instruction 8
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
