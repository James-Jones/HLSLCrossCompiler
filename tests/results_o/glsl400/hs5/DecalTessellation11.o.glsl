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
layout(vertices=3) out;
uniform struct cbInitHS_Type {
	vec4 g_vMaterialColor;
	vec4 g_vAmbientColor;
	vec4 g_vSpecularColor;
	vec4 g_vScreenSize;
	vec4 g_vFlags;
} cbInitHS;
uniform struct cbUpdateHS_Type {
	vec4 g_mWorld[4];
	vec4 g_mViewProjection[4];
	vec4 g_mWorldViewProjection[4];
	vec4 g_vTessellationFactor;
	vec4 g_vDisplacementScaleBias;
	vec4 g_vLightPosition;
	vec4 g_vEyePosition;
} cbUpdateHS;
uniform struct cbDamageHS_Type {
	vec4 g_vNormal[50];
	vec4 g_vBinormal[50];
	vec4 g_vTangent[50];
	vec4 g_vDecalPositionSize[50];
} cbDamageHS;
//Fork phase declarations
in  vec4 VtxGeoOutput0 [3];
vec4 Input0[3];
#undef Output0
#define Output0 phase1_Output0
vec4 phase1_Output0;
#undef Output1
#define Output1 phase1_Output1
vec4 phase1_Output1;
#undef Output2
#define Output2 phase1_Output2
vec4 phase1_Output2;
#undef Output3
#define Output3 phase1_Output3
vec4 phase1_Output3;
vec4 Temp[13];
ivec4 Temp_int[13];
uvec4 Temp_uint[13];
void fork_phase0()
{
    //Instruction 0
    //ADD
    Temp_int[0].xyz = floatBitsToInt(-gl_in[1].gl_Position.xyzx + gl_in[2].gl_Position.xyzx).xyz;
    //Instruction 1
    //ADD
    Temp_int[1].xyz = floatBitsToInt(-gl_in[1].gl_Position.xyzx + gl_in[0].gl_Position.xyzx).xyz;
    //Instruction 2
    //NE
    Temp_int[0].w = floatBitsToInt(((vec4(0.000000, 0.000000, 0.000000, 0.000000)).x!= (cbUpdateHS.g_vTessellationFactor.z)) ? int(0xFFFFFFFF) : 0);
    //Instruction 3
    //IF
    if((Temp_int[0].w)!=0){
        //Instruction 4
        //MUL
        Temp_int[2].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).yzxy * intBitsToFloat(Temp_int[1]).zxyz).xyz;
        //Instruction 5
        //MAD
        Temp_int[2].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).yzxy * intBitsToFloat(Temp_int[0]).zxyz + -intBitsToFloat(Temp_int[2]).xyzx)).xyz;
        //Instruction 6
        //DP3
        Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[2]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
        //Instruction 7
        //RSQ
        Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
        //Instruction 8
        //MUL
        Temp_int[2].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[2]).xyzx).xyz;
        //Instruction 9
        //ADD
        Temp_int[3].xyz = floatBitsToInt(-cbUpdateHS.g_vEyePosition.xyzx + gl_in[1].gl_Position.xyzx).xyz;
        //Instruction 10
        //DP3
        Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[3]).xyzx).xyz, (intBitsToFloat(Temp_int[3]).xyzx).xyz)).w);
        //Instruction 11
        //RSQ
        Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
        //Instruction 12
        //MUL
        Temp_int[3].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[3]).xyzx).xyz;
        //Instruction 13
        //DP3
        Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[3]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
        //Instruction 14
        //LT
        Temp_int[0].w = floatBitsToInt(((-0.250000)< (intBitsToFloat(Temp_int[0]).w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 15
        //IF
        if((Temp_int[0].w)==0){
            //Instruction 16
            //MOV
            Output0.x = vec4(intBitsToFloat(int(0x0))).x;
            //Instruction 17
            //MOV
            Output1.x = vec4(intBitsToFloat(int(0x0))).x;
            //Instruction 18
            //MOV
            Output2.x = vec4(intBitsToFloat(int(0x0))).x;
            //Instruction 19
            //MOV
            Output3.x = vec4(intBitsToFloat(int(0x0))).x;
            //Instruction 20
            //RET
            //--- Post shader code ---
    gl_TessLevelOuter[0] = float(phase1_Output0.x);
    gl_TessLevelOuter[1] = float(phase1_Output1.x);
    gl_TessLevelOuter[2] = float(phase1_Output2.x);
    gl_TessLevelInner[0] = float(phase1_Output3.x);
            //--- End post shader code ---
            return;
            //Instruction 21
        //ENDIF
        }
        //Instruction 22
    //ENDIF
    }
    //Instruction 23
    //NE
    Temp_int[2].xy = floatBitsToInt(ivec2(notEqual(vec4(vec4(0.000000, 0.000000, 0.000000, 0.000000)).xy, vec4(cbUpdateHS.g_vTessellationFactor.ywyy).xy)) * int(0xFFFFFFFF));
    //Instruction 24
    //MOV
    Temp_int[3].xyz = ivec4(floatBitsToInt(gl_in[1].gl_Position.xyzx)).xyz;
    //Instruction 25
    //MOV
    Temp_int[3].w = ivec4(int(0x3F800000)).w;
    //Instruction 26
    //DP4
    Temp_int[4].x = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[3]), cbUpdateHS.g_mViewProjection[0])).x);
    //Instruction 27
    //DP4
    Temp_int[4].y = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[3]), cbUpdateHS.g_mViewProjection[1])).y);
    //Instruction 28
    //DP4
    Temp_int[0].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[3]), cbUpdateHS.g_mViewProjection[3])).w);
    //Instruction 29
    //DIV
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[4]).xxxy / intBitsToFloat(Temp_int[0]).wwww).zw;
    //Instruction 30
    //ADD
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[2]).zzzw + vec4(0.000000, 0.000000, 1.000000, 1.000000)).zw;
    //Instruction 31
    //MOV
    Temp_int[3].x = ivec4(floatBitsToInt(cbInitHS.g_vScreenSize.x)).x;
    //Instruction 32
    //MOV
    Temp_int[3].y = ivec4(int(0x3F000000)).y;
    //Instruction 33
    //MUL
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[2]).zzzw * intBitsToFloat(Temp_int[3]).xxxy).zw;
    //Instruction 34
    //MUL
    Temp_int[3].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * 0.500000);
    //Instruction 35
    //MUL
    Temp_int[3].y = floatBitsToInt(intBitsToFloat(Temp_int[2]).w * -cbInitHS.g_vScreenSize.y);
    //Instruction 36
    //MOV
    Temp_int[4].xyz = ivec4(floatBitsToInt(gl_in[2].gl_Position.xyzx)).xyz;
    //Instruction 37
    //MOV
    Temp_int[4].w = ivec4(int(0x3F800000)).w;
    //Instruction 38
    //DP4
    Temp_int[5].x = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[4]), cbUpdateHS.g_mViewProjection[0])).x);
    //Instruction 39
    //DP4
    Temp_int[5].y = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[4]), cbUpdateHS.g_mViewProjection[1])).y);
    //Instruction 40
    //DP4
    Temp_int[0].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[4]), cbUpdateHS.g_mViewProjection[3])).w);
    //Instruction 41
    //DIV
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[5]).xxxy / intBitsToFloat(Temp_int[0]).wwww).zw;
    //Instruction 42
    //ADD
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[2]).zzzw + vec4(0.000000, 0.000000, 1.000000, 1.000000)).zw;
    //Instruction 43
    //MUL
    Temp_int[4].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * cbInitHS.g_vScreenSize.x);
    //Instruction 44
    //MUL
    Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[2]).w * -cbInitHS.g_vScreenSize.y);
    //Instruction 45
    //MOV
    Temp_int[5].xyz = ivec4(floatBitsToInt(gl_in[0].gl_Position.xyzx)).xyz;
    //Instruction 46
    //MOV
    Temp_int[5].w = ivec4(int(0x3F800000)).w;
    //Instruction 47
    //DP4
    Temp_int[6].x = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[5]), cbUpdateHS.g_mViewProjection[0])).x);
    //Instruction 48
    //DP4
    Temp_int[6].y = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[5]), cbUpdateHS.g_mViewProjection[1])).y);
    //Instruction 49
    //DP4
    Temp_int[0].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[5]), cbUpdateHS.g_mViewProjection[3])).w);
    //Instruction 50
    //DIV
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[6]).xxxy / intBitsToFloat(Temp_int[0]).wwww).zw;
    //Instruction 51
    //ADD
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[2]).zzzw + vec4(0.000000, 0.000000, 1.000000, 1.000000)).zw;
    //Instruction 52
    //MUL
    Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * cbInitHS.g_vScreenSize.x);
    //Instruction 53
    //MUL
    Temp_int[5].y = floatBitsToInt(intBitsToFloat(Temp_int[2]).w * -cbInitHS.g_vScreenSize.y);
    //Instruction 54
    //MUL
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[5]).xxxy * vec4(0.000000, 0.000000, 0.500000, 0.500000)).zw;
    //Instruction 55
    //MAD
    Temp_int[3].zw = floatBitsToInt(vec4(-intBitsToFloat(Temp_int[4]).xxxy * vec4(0.000000, 0.000000, 0.500000, 0.500000) + intBitsToFloat(Temp_int[3]).xxxy)).zw;
    //Instruction 56
    //DP2
    Temp_int[0].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).zwzz).xy, (intBitsToFloat(Temp_int[3]).zwzz).xy)).w);
    //Instruction 57
    //SQRT
    Temp_int[0].w = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[0]).w)).w);
    //Instruction 58
    //MUL
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.062500);
    //Instruction 59
    //DIV
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w / cbUpdateHS.g_vTessellationFactor.x);
    Temp_int[0].w = floatBitsToInt(clamp(intBitsToFloat(Temp_int[0]).w, 0, 1));
    //Instruction 60
    //MUL
    Temp_int[6].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * cbUpdateHS.g_vTessellationFactor.x);
    //Instruction 61
    //MAD
    Temp_int[2].zw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[4]).xxxy * vec4(0.000000, 0.000000, 0.500000, 0.500000) + -intBitsToFloat(Temp_int[2]).zzzw)).zw;
    //Instruction 62
    //DP2
    Temp_int[0].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[2]).zwzz).xy, (intBitsToFloat(Temp_int[2]).zwzz).xy)).w);
    //Instruction 63
    //SQRT
    Temp_int[0].w = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[0]).w)).w);
    //Instruction 64
    //MUL
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.062500);
    //Instruction 65
    //DIV
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w / cbUpdateHS.g_vTessellationFactor.x);
    Temp_int[0].w = floatBitsToInt(clamp(intBitsToFloat(Temp_int[0]).w, 0, 1));
    //Instruction 66
    //MUL
    Temp_int[6].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * cbUpdateHS.g_vTessellationFactor.x);
    //Instruction 67
    //MAD
    Temp_int[2].zw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[5]).xxxy * vec4(0.000000, 0.000000, 0.500000, 0.500000) + -intBitsToFloat(Temp_int[3]).xxxy)).zw;
    //Instruction 68
    //DP2
    Temp_int[0].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[2]).zwzz).xy, (intBitsToFloat(Temp_int[2]).zwzz).xy)).w);
    //Instruction 69
    //SQRT
    Temp_int[0].w = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[0]).w)).w);
    //Instruction 70
    //MUL
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.062500);
    //Instruction 71
    //DIV
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w / cbUpdateHS.g_vTessellationFactor.x);
    Temp_int[0].w = floatBitsToInt(clamp(intBitsToFloat(Temp_int[0]).w, 0, 1));
    //Instruction 72
    //MUL
    Temp_int[6].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * cbUpdateHS.g_vTessellationFactor.x);
    //Instruction 73
    //MAX
    Temp_int[0].w = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[6]).z, intBitsToFloat(Temp_int[6]).y)).w);
    //Instruction 74
    //MAX
    Temp_int[6].w = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[0]).w, intBitsToFloat(Temp_int[6]).x)).w);
    //Instruction 75
    //MOVC
    if(ivec4(Temp_int[2].xxxx).x != 0) {
        Temp_int[3] = Temp_int[6];
    } else {
        Temp_int[3] = floatBitsToInt(cbUpdateHS.g_vTessellationFactor.xxxx);
    }
    //Instruction 76
    //IF
    if((Temp_int[2].y)==0){
        //Instruction 77
        //MIN
        Temp_int[2] = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[3]), vec4(64.000000, 64.000000, 64.000000, 64.000000))));
        //Instruction 78
        //MOV
        Output0.x = vec4(intBitsToFloat(Temp_int[2].x)).x;
        //Instruction 79
        //MOV
        Output1.x = vec4(intBitsToFloat(Temp_int[2].y)).x;
        //Instruction 80
        //MOV
        Output2.x = vec4(intBitsToFloat(Temp_int[2].z)).x;
        //Instruction 81
        //MOV
        Output3.x = vec4(intBitsToFloat(Temp_int[2].w)).x;
        //Instruction 82
        //RET
        //--- Post shader code ---
    gl_TessLevelOuter[0] = float(phase1_Output0.x);
    gl_TessLevelOuter[1] = float(phase1_Output1.x);
    gl_TessLevelOuter[2] = float(phase1_Output2.x);
    gl_TessLevelInner[0] = float(phase1_Output3.x);
        //--- End post shader code ---
        return;
        //Instruction 83
    //ENDIF
    }
    //Instruction 84
    //DP3
    Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).xyzx).xyz, (intBitsToFloat(Temp_int[0]).xyzx).xyz)).w);
    //Instruction 85
    //ADD
    Temp_int[2].xyz = floatBitsToInt(-gl_in[2].gl_Position.xyzx + gl_in[0].gl_Position.xyzx).xyz;
    //Instruction 86
    //DP3
    Temp_int[1].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[2]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
    //Instruction 87
    //DP3
    Temp_int[2].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[1]).xyzx).xyz, (intBitsToFloat(Temp_int[1]).xyzx).xyz)).w);
    //Instruction 88
    //DP3
    Temp_int[4].x = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).xyzx).xyz, (intBitsToFloat(Temp_int[1]).xyzx).xyz)).x);
    //Instruction 89
    //MUL
    Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[4]).x);
    //Instruction 90
    //MAD
    Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * intBitsToFloat(Temp_int[2]).w + -intBitsToFloat(Temp_int[4]).y);
    //Instruction 91
    //DIV
    Temp_int[4].y = floatBitsToInt(vec4(1.000000, 1.000000, 1.000000, 1.000000) / intBitsToFloat(Temp_int[4]).y).y;
    //Instruction 92
    //MUL
    Temp_int[5].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).zxyz * intBitsToFloat(Temp_int[1]).yzxy).xyz;
    //Instruction 93
    //MAD
    Temp_int[5].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).yzxy * intBitsToFloat(Temp_int[1]).zxyz + -intBitsToFloat(Temp_int[5]).xyzx)).xyz;
    //Instruction 94
    //DP3
    Temp_int[4].z = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[5]).xyzx).xyz, (intBitsToFloat(Temp_int[5]).xyzx).xyz)).z);
    //Instruction 95
    //RSQ
    Temp_int[4].z = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[4]).z)).z);
    //Instruction 96
    //MUL
    Temp_int[5].xyz = floatBitsToInt(intBitsToFloat(Temp_int[4]).zzzz * intBitsToFloat(Temp_int[5]).xyzx).xyz;
    //Instruction 97
    //MOV
    Temp_int[6].xz = ivec4(Temp_int[3].xxyx).xz;
    //Instruction 98
    //MOV
    Temp_int[6].yw = ivec4(ivec4(0x0, 0xFFFFFFFF, 0x0, 0xFFFFFFFF)).yw;
    //Instruction 99
    //MOV
    Temp_int[7].x = ivec4(Temp_int[3].z).x;
    //Instruction 100
    //MOV
    Temp_int[7].y = ivec4(int(0xFFFFFFFF)).y;
    //Instruction 101
    //MOV
    Temp_int[8] = ivec4(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).xyzw;
    //Instruction 102
    //MOV
    Temp_int[3].y = ivec4(int(0x0)).y;
    //Instruction 103
    //LOOP
    while(true){
        //Instruction 104
        //IGE
        Temp_int[3].z = (((Temp_int[3].y)>= (int(0x32))) ? int(0xFFFFFFFF) : 0);
        //Instruction 105
        //BREAKC
        if((Temp_int[3].z)!=0){break;}
        //Instruction 106
        //EQ
        Temp_int[9].xyz = floatBitsToInt(ivec3(equal(vec4(cbDamageHS.g_vNormal[Temp_int[3].y + 0].xyzx).xyz, vec4(vec4(0.000000, 0.000000, 0.000000, 0.000000)).xyz)) * int(0xFFFFFFFF));
        //Instruction 107
        //AND
        Temp_int[3].z = Temp_int[9].y & Temp_int[9].x;
        //Instruction 108
        //AND
        Temp_int[3].z = Temp_int[9].z & Temp_int[3].z;
        //Instruction 109
        //IF
        if((Temp_int[3].z)!=0){
            //Instruction 110
            //BREAK
            break;
            //Instruction 111
        //ENDIF
        }
        //Instruction 112
        //MUL
        Temp_int[3].z = floatBitsToInt(cbDamageHS.g_vDecalPositionSize[Temp_int[3].y + 0].w * cbDamageHS.g_vDecalPositionSize[Temp_int[3].y + 0].w);
        //Instruction 113
        //ADD
        Temp_int[9].xyz = floatBitsToInt(cbDamageHS.g_vDecalPositionSize[Temp_int[3].y + 0].xyzx + -gl_in[1].gl_Position.xyzx).xyz;
        //Instruction 114
        //DP3
        Temp_int[4].z = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[9]).xyzx).xyz, (intBitsToFloat(Temp_int[9]).xyzx).xyz)).z);
        //Instruction 115
        //ADD
        Temp_int[10].xyz = floatBitsToInt(cbDamageHS.g_vDecalPositionSize[Temp_int[3].y + 0].xyzx + -gl_in[2].gl_Position.xyzx).xyz;
        //Instruction 116
        //DP3
        Temp_int[4].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[10]).xyzx).xyz, (intBitsToFloat(Temp_int[10]).xyzx).xyz)).w);
        //Instruction 117
        //ADD
        Temp_int[11].xyz = floatBitsToInt(cbDamageHS.g_vDecalPositionSize[Temp_int[3].y + 0].xyzx + -gl_in[0].gl_Position.xyzx).xyz;
        //Instruction 118
        //DP3
        Temp_int[5].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[11]).xyzx).xyz, (intBitsToFloat(Temp_int[11]).xyzx).xyz)).w);
        //Instruction 119
        //GE
        Temp_int[7].zw = floatBitsToInt(ivec2(greaterThanEqual(vec4(Temp_int[3].zzzz).xy, vec4(Temp_int[4].zzzw).xy)) * int(0xFFFFFFFF));
        //Instruction 120
        //OR
        Temp_int[9].w = Temp_int[7].w | Temp_int[7].z;
        //Instruction 121
        //DP3
        Temp_int[10].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[9]).xyzx).xyz, (intBitsToFloat(Temp_int[0]).xyzx).xyz)).w);
        //Instruction 122
        //DIV
        Temp_int[11].w = floatBitsToInt(intBitsToFloat(Temp_int[10]).w / intBitsToFloat(Temp_int[0]).w);
        //Instruction 123
        //MUL
        Temp_int[12].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx * intBitsToFloat(Temp_int[11]).wwww).xyz;
        //Instruction 124
        //DP3
        Temp_int[11].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[12]).xyzx).xyz, (intBitsToFloat(Temp_int[12]).xyzx).xyz)).w);
        //Instruction 125
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + -intBitsToFloat(Temp_int[11]).w);
        //Instruction 126
        //GE
        Temp_int[4].z = floatBitsToInt(((Temp_int[3].z)>= (Temp_int[4].z)) ? int(0xFFFFFFFF) : 0);
        //Instruction 127
        //DP3
        Temp_int[12].x = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[12]).xyzx).xyz, (intBitsToFloat(Temp_int[0]).xyzx).xyz)).x);
        //Instruction 128
        //GE
        Temp_int[12].x = floatBitsToInt(((Temp_int[12].x)>= (0.000000)) ? int(0xFFFFFFFF) : 0);
        //Instruction 129
        //AND
        Temp_int[4].z = Temp_int[4].z & Temp_int[12].x;
        //Instruction 130
        //GE
        Temp_int[11].w = floatBitsToInt(((Temp_int[0].w)>= (Temp_int[11].w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 131
        //AND
        Temp_int[12].y = Temp_int[4].z & Temp_int[11].w;
        //Instruction 132
        //MOVC
        if(ivec4(Temp_int[12].y).x != 0) {
            Temp_int[12].x = Temp_int[3].x;
        } else {
            Temp_int[12].x = Temp_int[8].x;
        }
        //Instruction 133
        //MOVC
        if(ivec4(Temp_int[9].wwww).x != 0) {
            Temp_int[12].xy = ivec4(Temp_int[6].xyxx).xy;
        } else {
            Temp_int[12].xy = ivec4(Temp_int[12].xyxx).xy;
        }
        //Instruction 134
        //GE
        Temp_int[4].z = floatBitsToInt(((Temp_int[3].z)>= (Temp_int[5].w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 135
        //OR
        Temp_int[7].w = Temp_int[4].z | Temp_int[7].w;
        //Instruction 136
        //DP3
        Temp_int[9].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[10]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
        //Instruction 137
        //DIV
        Temp_int[9].w = floatBitsToInt(intBitsToFloat(Temp_int[9]).w / intBitsToFloat(Temp_int[1]).w);
        //Instruction 138
        //MUL
        Temp_int[10].xyz = floatBitsToInt(intBitsToFloat(Temp_int[2]).xyzx * intBitsToFloat(Temp_int[9]).wwww).xyz;
        //Instruction 139
        //DP3
        Temp_int[9].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[10]).xyzx).xyz, (intBitsToFloat(Temp_int[10]).xyzx).xyz)).w);
        //Instruction 140
        //ADD
        Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).w + -intBitsToFloat(Temp_int[9]).w);
        //Instruction 141
        //GE
        Temp_int[4].w = floatBitsToInt(((Temp_int[3].z)>= (Temp_int[4].w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 142
        //DP3
        Temp_int[10].x = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[10]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).x);
        //Instruction 143
        //GE
        Temp_int[10].x = floatBitsToInt(((Temp_int[10].x)>= (0.000000)) ? int(0xFFFFFFFF) : 0);
        //Instruction 144
        //AND
        Temp_int[4].w = Temp_int[4].w & Temp_int[10].x;
        //Instruction 145
        //GE
        Temp_int[9].w = floatBitsToInt(((Temp_int[1].w)>= (Temp_int[9].w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 146
        //AND
        Temp_int[4].w = Temp_int[4].w & Temp_int[9].w;
        //Instruction 147
        //OR
        Temp_int[4].zw = (Temp_int[4].zzzw | Temp_int[7].zzzw).zw;
        //Instruction 148
        //MOV
        Temp_int[12].z = ivec4(Temp_int[8].y).z;
        //Instruction 149
        //MOVC
        if(ivec4(Temp_int[4].wwww).x != 0) {
            Temp_int[8].xy = ivec4(Temp_int[6].wzww).xy;
        } else {
            Temp_int[8].xy = ivec4(Temp_int[12].yzyy).xy;
        }
        //Instruction 150
        //DP3
        Temp_int[4].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[11]).xyzx).xyz, (-intBitsToFloat(Temp_int[1]).xyzx).xyz)).w);
        //Instruction 151
        //DIV
        Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).w / intBitsToFloat(Temp_int[2]).w);
        //Instruction 152
        //MUL
        Temp_int[10].xyz = floatBitsToInt(-intBitsToFloat(Temp_int[1]).xyzx * intBitsToFloat(Temp_int[4]).wwww).xyz;
        //Instruction 153
        //DP3
        Temp_int[4].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[10]).xyzx).xyz, (intBitsToFloat(Temp_int[10]).xyzx).xyz)).w);
        //Instruction 154
        //ADD
        Temp_int[5].w = floatBitsToInt(-intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[5]).w);
        //Instruction 155
        //GE
        Temp_int[3].z = floatBitsToInt(((Temp_int[3].z)>= (Temp_int[5].w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 156
        //DP3
        Temp_int[5].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[10]).xyzx).xyz, (-intBitsToFloat(Temp_int[1]).xyzx).xyz)).w);
        //Instruction 157
        //GE
        Temp_int[5].w = floatBitsToInt(((Temp_int[5].w)>= (0.000000)) ? int(0xFFFFFFFF) : 0);
        //Instruction 158
        //AND
        Temp_int[3].z = Temp_int[3].z & Temp_int[5].w;
        //Instruction 159
        //GE
        Temp_int[4].w = floatBitsToInt(((Temp_int[2].w)>= (Temp_int[4].w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 160
        //AND
        Temp_int[3].z = Temp_int[3].z & Temp_int[4].w;
        //Instruction 161
        //OR
        Temp_int[3].z = Temp_int[4].z | Temp_int[3].z;
        //Instruction 162
        //MOVC
        if(ivec4(Temp_int[3].zzzz).x != 0) {
            Temp_int[8].xz = ivec4(Temp_int[7].yyxy).xy;
        } else {
            Temp_int[8].xz = ivec4(Temp_int[8].xxzx).xy;
        }
        //Instruction 163
        //DP3
        Temp_int[3].z = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[5]).xyzx).xyz, (intBitsToFloat(Temp_int[9]).xyzx).xyz)).z);
        //Instruction 164
        //GE
        Temp_int[3].z = floatBitsToInt(((cbDamageHS.g_vDecalPositionSize[Temp_int[3].y + 0].w)>= (abs(Temp_int[3].z))) ? int(0xFFFFFFFF) : 0);
        //Instruction 165
        //DP3
        Temp_int[4].z = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[1]).xyzx).xyz, (intBitsToFloat(Temp_int[9]).xyzx).xyz)).z);
        //Instruction 166
        //MUL
        Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).z * intBitsToFloat(Temp_int[4]).x);
        //Instruction 167
        //MAD
        Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).w * intBitsToFloat(Temp_int[10]).w + -intBitsToFloat(Temp_int[4]).w);
        //Instruction 168
        //MUL
        Temp_int[5].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).y * intBitsToFloat(Temp_int[4]).w);
        //Instruction 169
        //MUL
        Temp_int[7].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[10]).w);
        //Instruction 170
        //MAD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * intBitsToFloat(Temp_int[4]).z + -intBitsToFloat(Temp_int[7]).z);
        //Instruction 171
        //MUL
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).y * intBitsToFloat(Temp_int[4]).z);
        //Instruction 172
        //LT
        Temp_int[5].w = floatBitsToInt(((0.000000)< (intBitsToFloat(Temp_int[5]).w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 173
        //LT
        Temp_int[7].z = floatBitsToInt(((0.000000)< (intBitsToFloat(Temp_int[4]).z)) ? int(0xFFFFFFFF) : 0);
        //Instruction 174
        //AND
        Temp_int[5].w = Temp_int[5].w & Temp_int[7].z;
        //Instruction 175
        //MAD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).w * intBitsToFloat(Temp_int[4]).y + intBitsToFloat(Temp_int[4]).z);
        //Instruction 176
        //LT
        Temp_int[4].z = floatBitsToInt(((intBitsToFloat(Temp_int[4]).z)< (1.000000)) ? int(0xFFFFFFFF) : 0);
        //Instruction 177
        //AND
        Temp_int[4].z = Temp_int[4].z & Temp_int[5].w;
        //Instruction 178
        //OR
        Temp_int[4].z = Temp_int[8].x | Temp_int[4].z;
        //Instruction 179
        //MOVC
        if(ivec4(Temp_int[4].z).x != 0) {
            Temp_int[4].z = Temp_int[3].w;
        } else {
            Temp_int[4].z = Temp_int[8].w;
        }
        //Instruction 180
        //MOVC
        if(ivec4(Temp_int[3].z).x != 0) {
            Temp_int[8].w = Temp_int[4].z;
        } else {
            Temp_int[8].w = Temp_int[8].w;
        }
        //Instruction 181
        //IADD
        Temp_int[3].y = (Temp_int[3].y + int(0x1));
        //Instruction 182
        //MOV
        Temp_int[8].x = ivec4(Temp_int[12].x).x;
        //Instruction 183
    //ENDLOOP
    }
    //Instruction 184
    //MIN
    Temp_int[0] = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[8]), vec4(64.000000, 64.000000, 64.000000, 64.000000))));
    //Instruction 185
    //MOV
    Output0.x = vec4(intBitsToFloat(Temp_int[0].x)).x;
    //Instruction 186
    //MOV
    Output1.x = vec4(intBitsToFloat(Temp_int[0].y)).x;
    //Instruction 187
    //MOV
    Output2.x = vec4(intBitsToFloat(Temp_int[0].z)).x;
    //Instruction 188
    //MOV
    Output3.x = vec4(intBitsToFloat(Temp_int[0].w)).x;
}
void main()
{
    //--- Start Early Main ---
    //--- End Early Main ---
    fork_phase0();
}
