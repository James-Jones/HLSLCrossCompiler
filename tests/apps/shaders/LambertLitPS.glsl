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
uniform struct SharedConstsPS_Type {
	vec4 World[4];
	vec4 View[4];
	vec4 Projection[4];
	vec4 vLightDir[2];
	vec4 vLightColor[2];
	vec4 vOutputColor;
} SharedConstsPS;
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
    Input1 = VtxGeoOutput1;
    //--- End Early Main ---
    //Instruction 0
    //DP3
    Temp[0].x = vec4(dot((SharedConstsPS.vLightDir[0].xyzx).xyz, (Input1.xyzx).xyz)).x;
    //Instruction 1
    //MUL
    Temp[0].xyz = vec4(Temp[0].xxxx * SharedConstsPS.vLightColor[0].xyzx).xyz;
    Temp[0].xyz = clamp(Temp[0].xyz, 0, 1);
    //Instruction 2
    //DP3
    Temp[0].w = vec4(dot((SharedConstsPS.vLightDir[1].xyzx).xyz, (Input1.xyzx).xyz)).w;
    //Instruction 3
    //MUL
    Temp[1].xyz = vec4(Temp[0].wwww * SharedConstsPS.vLightColor[1].xyzx).xyz;
    Temp[1].xyz = clamp(Temp[1].xyz, 0, 1);
    //Instruction 4
    //ADD
    Output0.xyz = vec4(Temp[0].xyzx + Temp[1].xyzx).xyz;
    //Instruction 5
    //MOV
    Output0.w = vec4(1.000000).w;
    //Instruction 6
    //RET
    return;
}
