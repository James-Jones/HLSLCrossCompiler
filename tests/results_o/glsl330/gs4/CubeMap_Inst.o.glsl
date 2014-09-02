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
in  vec4 VtxOutput1 [3];
vec4 Input1[3];
in  uvec4 VtxOutput2 [3];
uvec4 Input2[3];
vec4 Temp[1];
ivec4 Temp_int[1];
uvec4 Temp_uint[1];
layout(triangles) in;
layout(triangle_strip) out;
#undef Output0
#define Output0 phase0_Output0
vec4 phase0_Output0;
out vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
#undef Output2
#define Output2 phase0_Output2
ivec4 phase0_Output2;
layout(max_vertices = 3) out;
void main()
{
    //--- Start Early Main ---
    Input1[2] = VtxOutput1[2];
    Input1[1] = VtxOutput1[1];
    Input1[0] = VtxOutput1[0];
    Input2[2] = VtxOutput2[2];
    Input2[1] = VtxOutput2[1];
    Input2[0] = VtxOutput2[0];
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Temp_int[0].x = 0x0;
    //Instruction 1
    //LOOP
    while(true){
        //Instruction 2
        //IGE
        // IGE+BREAKC opt
        if ((Temp_int[0].x>= 0x3)) { break; }
        Temp_int[0].y = int((Temp_int[0].x>=0x3) ? 0xFFFFFFFFu : 0u);
        //Instruction 3
        //Instruction 4
        //MOV
        Output0 = gl_in[Temp_int[0].x].gl_Position;
        //Instruction 5
        //MOV
        Output1.xy = Input1[Temp_int[0].x].xy;
        //Instruction 6
        //MOV
        Output2.x = int(Input2[Temp_int[0].x].x);
        //Instruction 7
        //EMIT
        //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    gl_Layer = int(phase0_Output2.x);
        //--- End post shader code ---
                EmitVertex();
        //Instruction 8
        //IADD
        Temp_int[0].x = Temp_int[0].x + 0x1;
        //Instruction 9
    //ENDLOOP
    }
    //Instruction 10
    //RET
    //--- Post shader code ---
    gl_Position = vec4(phase0_Output0);
    gl_Layer = int(phase0_Output2.x);
    //--- End post shader code ---
    return;
}
