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
in  vec4 VtxOutput0 [1];
vec4 Input0[1];
in  vec4 VtxOutput1 [1];
vec4 Input1[1];
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
layout(invocations = 24) in;
layout(points) in;
layout(stream = 0) out;
layout(points) out;
out vec4 VtxGeoOutput0;
#define Output0 VtxGeoOutput0
layout(max_vertices = 18) out;
void main()
{
    //--- Start Early Main ---
    Input1[0] = VtxOutput1[0];
    //--- End Early Main ---
    //Instruction 0
    //MUL
    Temp_int[0].xyz = floatBitsToInt(gl_in[0].gl_Position.xyzx * Input1[0].xyzx).xyz;
    //Instruction 1
//Warning. UTOF/ITOF on a src which is float. This is okay if ld_uav_typed last wrote to the src.
    //UTOF
    Temp_int[0].w = floatBitsToInt(vec4(uvec4(gl_InvocationID).x).w);
    //Instruction 2
    //MUL
    Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[0]).xyzx).xyz;
    //Instruction 3
    //MOV
    Output0.xyz = vec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
    //Instruction 4
    //EMIT_STREAM
    EmitStreamVertex(0);
    //Instruction 5
    //RET
    return;
}
