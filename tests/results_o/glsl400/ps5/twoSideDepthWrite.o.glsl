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
uniform struct GlobalsPS_Type {
	float FrontDepth;
	float BackDepth;
} GlobalsPS;
uniform sampler2D TextureBase;
 in  vec4 VtxGeoOutput0;
vec4 Input0;
uvec4 Input1;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    Input1.x = int(gl_FrontFacing);
    //--- End Early Main ---
    //Instruction 0
    //IF
    if((Input1.x)!=0u){
        //Instruction 1
        //SAMPLE
        Output0 = (texture(TextureBase, Input0.xy));
        //Instruction 2
        //MOV
        gl_FragDepth = vec4(GlobalsPS.FrontDepth).x;
        //Instruction 3
    //ELSE
    } else {
        //Instruction 4
        //SAMPLE
        Output0 = (texture(TextureBase, Input0.xy));
        //Instruction 5
        //MOV
        gl_FragDepth = vec4(GlobalsPS.BackDepth).x;
        //Instruction 6
    //ENDIF
    }
    //Instruction 7
    //RET
    return;
}
