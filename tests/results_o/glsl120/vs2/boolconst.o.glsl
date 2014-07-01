#version 120
int RepCounter;
int LoopCounter;
int ZeroBasedCounter;
ivec4 Address;
varying vec4 OffsetColour;
varying vec4 BaseColour;
varying vec4 Fog;
varying vec4 TexCoord0;
varying vec4 TexCoord1;
varying vec4 TexCoord2;
varying vec4 TexCoord3;
varying vec4 TexCoord4;
varying vec4 TexCoord5;
varying vec4 TexCoord6;
varying vec4 TexCoord7;
struct vec1 {
	float x;
};
struct ivec1 {
	int x;
};
const vec4 ImmConst0 = vec4(2.000000, 1.000000, 0.500000, 0.000000);
 attribute  vec4 dcl_Input0;
vec4 Input0;
vec4 Temp[2];
ivec4 Temp_int[2];
uniform struct GlobalsVS_Type {
	int LOOP_COUNT;
} GlobalsVS;
vec4 ImmConstArray [1];
void main()
{
    //--- Start Early Main ---
    ImmConstArray[0] = ImmConst0;
    Input0 = dcl_Input0;
    Input0 = dcl_Input0;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Temp[0] = vec4(Input0.xyzw).xyzw;
    //Instruction 1
    //IF
    if(GlobalsVS.LOOP_COUNT != 0){
        //Instruction 2
        //MUL
        Temp[1] = (Temp[0].xyzw * ImmConst0.xyzy);
        //Instruction 3
    //ELSE
    } else {
        //Instruction 4
        //MUL
        Temp[1] = (Temp[0].xyzw * ImmConst0.xyyy);
        //Instruction 5
    //ENDIF
    }
    //Instruction 6
    //MOV
    gl_Position = vec4(Temp[1].xyzw).xyzw;
    //Instruction 7
    //RET
    return;
}
