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
uniform struct SharedConstsVS_Type {
	vec4 World[4];
	vec4 View[4];
	vec4 Projection[4];
	vec4 vOutputColor;
	int ColorFactor;
} SharedConstsVS;
layout(location = 0)  in  vec4 dcl_Input0;
vec4 Input0;
layout(location = 1)  in  vec4 dcl_Input1;
vec4 Input1;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
 out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
 out  vec4 VtxGeoOutput2;
#define Output2 VtxGeoOutput2
 out  ivec4 VtxGeoOutput3;
#define Output3 VtxGeoOutput3
 out  ivec4 VtxGeoOutput4;
#define Output4 VtxGeoOutput4
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input1 = dcl_Input1;
    //--- End Early Main ---
    //Instruction 0
    //DP4
    Temp[0].x = vec4(dot(Input0, SharedConstsVS.World[0])).x;
    //Instruction 1
    //DP4
    Temp[0].y = vec4(dot(Input0, SharedConstsVS.World[1])).y;
    //Instruction 2
    //DP4
    Temp[0].z = vec4(dot(Input0, SharedConstsVS.World[2])).z;
    //Instruction 3
    //DP4
    Temp[0].w = vec4(dot(Input0, SharedConstsVS.World[3])).w;
    //Instruction 4
    //DP4
    Temp[1].x = vec4(dot(Temp[0], SharedConstsVS.View[0])).x;
    //Instruction 5
    //DP4
    Temp[1].y = vec4(dot(Temp[0], SharedConstsVS.View[1])).y;
    //Instruction 6
    //DP4
    Temp[1].z = vec4(dot(Temp[0], SharedConstsVS.View[2])).z;
    //Instruction 7
    //DP4
    Temp[1].w = vec4(dot(Temp[0], SharedConstsVS.View[3])).w;
    //Instruction 8
    //DP4
    Output0.x = vec4(dot(Temp[1], SharedConstsVS.Projection[0])).x;
    //Instruction 9
    //DP4
    Output0.y = vec4(dot(Temp[1], SharedConstsVS.Projection[1])).y;
    //Instruction 10
    //DP4
    Output0.z = vec4(dot(Temp[1], SharedConstsVS.Projection[2])).z;
    //Instruction 11
    //DP4
    Output0.w = vec4(dot(Temp[1], SharedConstsVS.Projection[3])).w;
    //Instruction 12
    //DP3
    Output1.x = vec4(dot((Input1.xyzx).xyz, (SharedConstsVS.World[0].xyzx).xyz)).x;
    //Instruction 13
    //DP3
    Output1.y = vec4(dot((Input1.xyzx).xyz, (SharedConstsVS.World[1].xyzx).xyz)).y;
    //Instruction 14
    //DP3
    Output1.z = vec4(dot((Input1.xyzx).xyz, (SharedConstsVS.World[2].xyzx).xyz)).z;
    //Instruction 15
    //ITOF
    Temp[0].x = vec4(SharedConstsVS.ColorFactor).x;
    //Instruction 16
    //MUL
    Temp[0] = vec4(Temp[0].xxxx * SharedConstsVS.vOutputColor);
    //Instruction 17
    //MOV
    Output2 = vec4(Temp[0]).xyzw;
    //Instruction 18
    //MUL
    Temp[0] = vec4(Temp[0] * vec4(10.000000, 10.000000, 10.000000, 10.000000));
    //Instruction 19
    //ROUND_PI
    Temp[0] = vec4(ceil(Temp[0]));
    //Instruction 20
    //FTOI
    Temp_int[0] = ivec4(Temp[0]);
    //Instruction 21
    //IMAX
    Output3.y = ivec4(max(int(Temp_int[0].x), int(10))).y;
    //Instruction 22
    //ISHL
    Output4 = ivec4(Temp_int[0] << 1);
    //Instruction 23
    //MOV
    Output3.x = ivec4(SharedConstsVS.ColorFactor).x;
    //Instruction 24
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
