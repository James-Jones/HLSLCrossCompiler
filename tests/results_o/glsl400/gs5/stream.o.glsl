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
in  vec4 VtxOutput0 [2];
vec4 Input0[2];
in  vec4 VtxOutput1 [2];
vec4 Input1[2];
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
layout(lines) in;
layout(stream = 0) out;
layout(points) out;
out vec4 VtxGeoOutput0;
#define Output0 VtxGeoOutput0
layout(stream = 1) out;
layout(points) out;
out ivec4 VtxGeoOutput0_S1;
#define Output0_S1 VtxGeoOutput0_S1
layout(max_vertices = 18) out;
void main()
{
    //--- Start Early Main ---
    Input1[1] = VtxOutput1[1];
    Input1[0] = VtxOutput1[0];
    //--- End Early Main ---
    //Instruction 0
    //MUL
    Temp_int[0].xyz = floatBitsToInt(gl_in[0].gl_Position.xyzx * Input1[0].xyzx).xyz;
    //Instruction 1
    //MOV
    Output0.xyz = vec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
    //Instruction 2
    //EMIT_STREAM
    EmitStreamVertex(0);
    //Instruction 3
    //MUL
    Temp_int[0].xyz = floatBitsToInt(gl_in[1].gl_Position.xyzx * Input1[1].xyzx).xyz;
    //Instruction 4
    //FTOI
    Temp_int[0].xyz = ivec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
    //Instruction 5
    //MOV
    Output0.xyz = vec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
    //Instruction 6
    //EMIT_STREAM
    EmitStreamVertex(1);
    //Instruction 7
    //RET
    return;
}
