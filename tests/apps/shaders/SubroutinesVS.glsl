#version 430
struct vec1 {
	float x;
};
struct uvec1 {
	uint x;
};
struct ivec1 {
	int x;
};
out gl_PerVertex {
vec4 gl_Position;
float gl_PointSize;
float gl_ClipDistance[];};
subroutine void SubroutineType();
layout(location = 0) uniform struct cbChangesEveryFrameVS_Type {
	vec4 World[4];
	vec4 View[4];
	vec4 Projection[4];
	float Time;
} cbChangesEveryFrameVS;
layout(location = 0)  in  vec4 dcl_Input0;
vec4 Input0;
layout(location = 1)  in  vec4 dcl_Input1;
vec4 Input1;
layout(location = 2)  in  vec4 dcl_Input2;
vec4 Input2;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
layout(location = 1)  out  vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
layout(location = 2)  out  vec4 VtxGeoOutput2;
#define Output2 VtxGeoOutput2
vec4 Temp[2];
ivec4 Temp_int[2];
uvec4 Temp_uint[2];
void main()
{
    //--- Start Early Main ---
    Input0 = dcl_Input0;
    Input1 = dcl_Input1;
    Input2 = dcl_Input2;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Temp[0].xyz = vec4(Input0.xyzx).xyz;
    //Instruction 1
    //MOV
    Temp[0].w = vec4(1.000000).w;
    //Instruction 2
    //DP4
    Temp[1].x = vec4(dot(Temp[0], cbChangesEveryFrameVS.World[0])).x;
    //Instruction 3
    //DP4
    Temp[1].y = vec4(dot(Temp[0], cbChangesEveryFrameVS.World[1])).y;
    //Instruction 4
    //DP4
    Temp[1].z = vec4(dot(Temp[0], cbChangesEveryFrameVS.World[2])).z;
    //Instruction 5
    //DP4
    Temp[1].w = vec4(dot(Temp[0], cbChangesEveryFrameVS.World[3])).w;
    //Instruction 6
    //DP4
    Temp[0].x = vec4(dot(Temp[1], cbChangesEveryFrameVS.View[0])).x;
    //Instruction 7
    //DP4
    Temp[0].y = vec4(dot(Temp[1], cbChangesEveryFrameVS.View[1])).y;
    //Instruction 8
    //DP4
    Temp[0].z = vec4(dot(Temp[1], cbChangesEveryFrameVS.View[2])).z;
    //Instruction 9
    //DP4
    Temp[0].w = vec4(dot(Temp[1], cbChangesEveryFrameVS.View[3])).w;
    //Instruction 10
    //DP4
    Output0.x = vec4(dot(Temp[0], cbChangesEveryFrameVS.Projection[0])).x;
    //Instruction 11
    //DP4
    Output0.y = vec4(dot(Temp[0], cbChangesEveryFrameVS.Projection[1])).y;
    //Instruction 12
    //DP4
    Output0.z = vec4(dot(Temp[0], cbChangesEveryFrameVS.Projection[2])).z;
    //Instruction 13
    //DP4
    Output0.w = vec4(dot(Temp[0], cbChangesEveryFrameVS.Projection[3])).w;
    //Instruction 14
    //DP3
    Output1.x = vec4(dot((Input1.xyzx).xyz, (cbChangesEveryFrameVS.World[0].xyzx).xyz)).x;
    //Instruction 15
    //DP3
    Output1.y = vec4(dot((Input1.xyzx).xyz, (cbChangesEveryFrameVS.World[1].xyzx).xyz)).y;
    //Instruction 16
    //DP3
    Output1.z = vec4(dot((Input1.xyzx).xyz, (cbChangesEveryFrameVS.World[2].xyzx).xyz)).z;
    //Instruction 17
    //MOV
    Output1.w = vec4(1.000000).w;
    //Instruction 18
    //MOV
    Output2.xy = vec4(Input2.xyxx).xy;
    //Instruction 19
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    //--- End post shader code ---
    return;
}
