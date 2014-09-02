#version 150
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
uniform struct _ParamsPS_Type {
	int bOutside;
	int bDetail;
	int bShadow;
	int bOrtho;
} _ParamsPS;
uniform struct cbOnRenderPS_Type {
	vec3 g_LightDir;
	vec3 g_LightDirTex;
	vec4 g_LightDiffuse;
	vec4 g_mWorldViewProjection[4];
	vec4 g_mWorld[4];
	vec3 g_vTextureEyePt;
	vec4 g_mWorldToTerrain[4];
	vec4 g_mTexToViewProj[4];
	vec4 g_mLightViewProj[4];
	vec4 g_mTexToLightViewProj[4];
} cbOnRenderPS;
uniform struct cbConstantPS_Type {
	float g_InvMapSize;
	float g_MapSize;
	float g_InvDetailMapSize;
	float g_DetailMapSize;
	float g_HeightRatio;
} cbConstantPS;
uniform struct cbUIPS_Type {
	float g_DetailRepeat;
	float g_InvDetailRepeat;
	float g_DetailHeight;
	float g_ShadowBias;
	float g_DetailDistanceSq;
} cbUIPS;
uniform sampler2D g_txDetailDiffuse;
uniform sampler2D g_txDetailDiffuse1;
uniform sampler2D g_txDetailDiffuse2;
uniform sampler2D g_txDetailDiffuse3;
uniform sampler2D g_txDetailGrad_RedGreen;
uniform sampler2D g_txDetailGrad_BlueAlpha;
uniform sampler2D g_txHeight;
uniform sampler2D g_txMask;
uniform sampler2D g_txDetailHeight;
uniform sampler2DShadow hlslcc_zcmpg_txDepthMap;
uniform sampler2D g_txDepthMap;
 in  vec4 VtxGeoOutput0;
vec4 Input0;
out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[16];
ivec4 Temp_int[16];
uvec4 Temp_uint[16];
void main()
{
    //--- Start Early Main ---
    Input0 = VtxGeoOutput0;
    //--- End Early Main ---
    //Instruction 0
    //MAD
    Temp_int[0].xyz = floatBitsToInt(vec4(cbOnRenderPS.g_LightDirTex.xyzx.xyzx * vec4(2.000000, 2.000000, 2.000000, 0.000000) + Input0.xyzx)).xyz;
    //Instruction 1
    //MOVC
    if(ivec4(_ParamsPS.bOrtho).x != 0) {
        Temp_int[0].xyz = ivec4(Temp_int[0].xyzx).xyz;
    } else {
        Temp_int[0].xyz = ivec4(floatBitsToInt(cbOnRenderPS.g_vTextureEyePt.xyzx.xzyx)).xyz;
    }
    //Instruction 2
    //ADD
    Temp_int[1].xyz = floatBitsToInt(-intBitsToFloat(Temp_int[0]).xyzx + Input0.xyzx).xyz;
    //Instruction 3
    //LT
    Temp_int[2].xyz = floatBitsToInt(ivec3(lessThan(vec4(vec4(0.000000, 0.000000, 0.000000, 0.000000)).xyz, vec4(intBitsToFloat(Temp_int[1]).xyzx).xyz)) * int(0xFFFFFFFF));
    //Instruction 4
    //DIV
    Temp_int[3].xyz = floatBitsToInt(-intBitsToFloat(Temp_int[0]).xyzx / intBitsToFloat(Temp_int[1]).xyzx).xyz;
    //Instruction 5
    //MAX
    Temp_int[0].w = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[3]).x, -1.000000)).w);
    //Instruction 6
    //MOVC
    if(ivec4(Temp_int[2].x).x != 0) {
        Temp_int[0].w = Temp_int[0].w;
    } else {
        Temp_int[0].w = int(0xBF800000);
    }
    //Instruction 7
    //LT
    Temp_int[4].xyz = floatBitsToInt(ivec3(lessThan(vec4(intBitsToFloat(Temp_int[1]).xyzx).xyz, vec4(vec4(0.000000, 0.000000, 0.000000, 0.000000)).xyz)) * int(0xFFFFFFFF));
    //Instruction 8
    //ADD
    Temp_int[5].xyz = floatBitsToInt(-intBitsToFloat(Temp_int[0]).xyzx + vec4(1.000000, 1.000000, 1.000000, 0.000000)).xyz;
    //Instruction 9
    //DIV
    Temp_int[5].xyz = floatBitsToInt(intBitsToFloat(Temp_int[5]).xyzx / intBitsToFloat(Temp_int[1]).xyzx).xyz;
    //Instruction 10
    //MAX
    Temp_int[1].w = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[0]).w, intBitsToFloat(Temp_int[5]).x)).w);
    //Instruction 11
    //MOVC
    if(ivec4(Temp_int[4].x).x != 0) {
        Temp_int[0].w = Temp_int[1].w;
    } else {
        Temp_int[0].w = Temp_int[0].w;
    }
    //Instruction 12
    //MAX
    Temp_int[1].w = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[0]).w, intBitsToFloat(Temp_int[3]).y)).w);
    //Instruction 13
    //MOVC
    if(ivec4(Temp_int[2].y).x != 0) {
        Temp_int[0].w = Temp_int[1].w;
    } else {
        Temp_int[0].w = Temp_int[0].w;
    }
    //Instruction 14
    //MAX
    Temp_int[1].w = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[0]).w, intBitsToFloat(Temp_int[5]).y)).w);
    //Instruction 15
    //MOVC
    if(ivec4(Temp_int[4].y).x != 0) {
        Temp_int[0].w = Temp_int[1].w;
    } else {
        Temp_int[0].w = Temp_int[0].w;
    }
    //Instruction 16
    //MAX
    Temp_int[1].w = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[0]).w, intBitsToFloat(Temp_int[3]).z)).w);
    //Instruction 17
    //MOVC
    if(ivec4(Temp_int[2].z).x != 0) {
        Temp_int[0].w = Temp_int[1].w;
    } else {
        Temp_int[0].w = Temp_int[0].w;
    }
    //Instruction 18
    //MAX
    Temp_int[1].w = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[0]).w, intBitsToFloat(Temp_int[5]).z)).w);
    //Instruction 19
    //MOVC
    if(ivec4(Temp_int[4].z).x != 0) {
        Temp_int[0].w = Temp_int[1].w;
    } else {
        Temp_int[0].w = Temp_int[0].w;
    }
    //Instruction 20
    //MAD
    Temp_int[2].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).xyzx * intBitsToFloat(Temp_int[0]).wwww + intBitsToFloat(Temp_int[0]).xyzx)).xyz;
    //Instruction 21
    //ADD
    Temp_int[3].xyz = floatBitsToInt(-intBitsToFloat(Temp_int[2]).xyzx + Input0.xyzx).xyz;
    //Instruction 22
    //MOVC
    if(ivec4(_ParamsPS.bOutside).x != 0) {
        Temp_int[2].xyz = ivec4(Temp_int[2].xyzx).xyz;
    } else {
        Temp_int[2].xyz = ivec4(Temp_int[0].xyzx).xyz;
    }
    //Instruction 23
    //MOVC
    if(ivec4(_ParamsPS.bOutside).x != 0) {
        Temp_int[1].xyz = ivec4(Temp_int[3].xyzx).xyz;
    } else {
        Temp_int[1].xyz = ivec4(Temp_int[1].xyzx).xyz;
    }
    //Instruction 24
    //DP3
    Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[1]).xyzx).xyz, (intBitsToFloat(Temp_int[1]).xyzx).xyz)).w);
    //Instruction 25
    //SQRT
    Temp_int[0].w = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[0]).w)).w);
    //Instruction 26
    //DIV
    Temp_int[1].xyz = floatBitsToInt(intBitsToFloat(Temp_int[1]).xyzx / intBitsToFloat(Temp_int[0]).wwww).xyz;
    //Instruction 27
    //MAD
    Temp_int[1].w = floatBitsToInt(-intBitsToFloat(Temp_int[1]).z * intBitsToFloat(Temp_int[1]).z + 1.000000);
    //Instruction 28
    //SQRT
    Temp_int[1].w = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[1]).w)).w);
    //Instruction 29
    //SAMPLE_L
    Temp_int[3] = floatBitsToInt(textureLod(g_txHeight, intBitsToFloat(Temp_int[2]).xy, 0.000000));
    //Instruction 30
    //MOV
    Temp_int[4].xyz = ivec4(Temp_int[2].xyzx).xyz;
    //Instruction 31
    //MOV
    Temp_int[7].y = ivec4(int(0x0)).y;
    //Instruction 32
    //MOV
    Temp_int[6] = ivec4(Temp_int[3].zwxy).xyzw;
    //Instruction 33
    //MOV
    Temp_int[2].w = ivec4(int(0x0)).w;
    //Instruction 34
    //MOV
    Temp_int[4].w = ivec4(int(0x0)).w;
    //Instruction 35
    //MOV
    Temp_int[5].xyw = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xyw;
    //Instruction 36
    //MOV
    Temp_int[8].x = ivec4(int(0x0)).x;
    //Instruction 37
    //LOOP
    while(true){
        //Instruction 38
        //GE
        Temp_int[8].y = floatBitsToInt(((Temp_int[6].z)>= (Temp_int[4].z)) ? int(0xFFFFFFFF) : 0);
        //Instruction 39
        //MOV
        Temp_int[8].x = ivec4(int(0x0)).x;
        //Instruction 40
        //BREAKC
        if((Temp_int[8].y)!=0){break;}
        //Instruction 41
        //MUL
        Temp_int[8].y = floatBitsToInt(intBitsToFloat(Temp_int[6]).w * intBitsToFloat(Temp_int[6]).w);
        //Instruction 42
        //DIV
        Temp_int[8].y = floatBitsToInt(intBitsToFloat(Temp_int[1]).w / intBitsToFloat(Temp_int[8]).y);
        //Instruction 43
        //ADD
        Temp_int[8].y = floatBitsToInt(-intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[8]).y);
        //Instruction 44
        //DIV
        Temp_int[8].y = floatBitsToInt(vec4(1.000000, 1.000000, 1.000000, 1.000000) / intBitsToFloat(Temp_int[8]).y).y;
        //Instruction 45
        //ADD
        Temp_int[8].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + -intBitsToFloat(Temp_int[6]).z);
        //Instruction 46
        //MUL
        Temp_int[8].y = floatBitsToInt(intBitsToFloat(Temp_int[8]).y * intBitsToFloat(Temp_int[8]).z);
        //Instruction 47
        //MAX
        Temp_int[8].y = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[8]).y, cbConstantPS.g_InvMapSize)).y);
        //Instruction 48
        //ADD
        Temp_int[2].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[8]).y);
        //Instruction 49
        //MAD
        Temp_int[9].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).xyzx * intBitsToFloat(Temp_int[8]).yyyy + intBitsToFloat(Temp_int[4]).xyzx)).xyz;
        //Instruction 50
        //LT
        Temp_int[8].z = floatBitsToInt(((intBitsToFloat(Temp_int[0]).w)< (intBitsToFloat(Temp_int[2]).w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 51
        //IF
        if((Temp_int[8].z)!=0){
            //Instruction 52
            //MOV
            Temp_int[5].xy = ivec4(ivec4(0xBF800000, 0xBF800000, 0x0, 0x0)).xy;
            //Instruction 53
            //MOV
            Temp_int[4].xyz = ivec4(Temp_int[9].xyzx).xyz;
            //Instruction 54
            //MOV
            Temp_int[7].y = ivec4(int(0xBF800000)).y;
            //Instruction 55
            //MOV
            Temp_int[4].w = ivec4(Temp_int[8].y).w;
            //Instruction 56
            //MOV
            Temp_int[8].x = ivec4(int(0xFFFFFFFF)).x;
            //Instruction 57
            //BREAK
            break;
            //Instruction 58
        //ENDIF
        }
        //Instruction 59
        //ILT
        Temp_int[8].w = (((int(0x200))< (Temp_int[5].w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 60
        //IF
        if((Temp_int[8].w)!=0){
            //Instruction 61
            //MOV
            Temp_int[5].xy = ivec4(ivec4(0xBF800000, 0xBF800000, 0x0, 0x0)).xy;
            //Instruction 62
            //MOV
            Temp_int[4].xyz = ivec4(Temp_int[9].xyzx).xyz;
            //Instruction 63
            //MOV
            Temp_int[7].y = ivec4(int(0xBF800000)).y;
            //Instruction 64
            //MOV
            Temp_int[4].w = ivec4(Temp_int[8].y).w;
            //Instruction 65
            //MOV
            Temp_int[8].x = ivec4(int(0xFFFFFFFF)).x;
            //Instruction 66
            //BREAK
            break;
            //Instruction 67
        //ENDIF
        }
        //Instruction 68
        //SAMPLE_L
        Temp_int[6] = floatBitsToInt(textureLod(g_txHeight, intBitsToFloat(Temp_int[9]).xy, 0.000000).zwxy);
        //Instruction 69
        //IADD
        Temp_int[5].w = (Temp_int[5].w + int(0x1));
        //Instruction 70
        //OR
        Temp_int[8].x = Temp_int[8].z | Temp_int[8].w;
        //Instruction 71
        //MOV
        Temp_int[4].xyz = ivec4(Temp_int[9].xyzx).xyz;
        //Instruction 72
        //MOV
        Temp_int[4].w = ivec4(Temp_int[8].y).w;
        //Instruction 73
        //MOV
        Temp_int[5].xy = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xy;
        //Instruction 74
        //MOV
        Temp_int[7].y = ivec4(int(0x0)).y;
        //Instruction 75
    //ENDLOOP
    }
    //Instruction 76
    //IF
    if((Temp_int[8].x)==0){
        //Instruction 77
        //IF
        if((_ParamsPS.bDetail)!=0){
            //Instruction 78
            //ADD
            Temp_int[0].xyz = floatBitsToInt(-intBitsToFloat(Temp_int[0]).xyzx + intBitsToFloat(Temp_int[4]).xyzx).xyz;
            //Instruction 79
            //MUL
            Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * cbConstantPS.g_HeightRatio);
            //Instruction 80
            //DP3
            Temp_int[0].x = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).xywx).xyz, (intBitsToFloat(Temp_int[0]).xywx).xyz)).x);
            //Instruction 81
            //LT
            Temp_int[0].x = floatBitsToInt(((intBitsToFloat(Temp_int[0]).x)< (cbUIPS.g_DetailDistanceSq)) ? int(0xFFFFFFFF) : 0);
            //Instruction 82
            //IF
            if((Temp_int[0].x)!=0){
                //Instruction 83
                //MAD
                Temp_int[0].yzw = floatBitsToInt(vec4(-intBitsToFloat(Temp_int[4]).wwww * intBitsToFloat(Temp_int[1]).xxyz + intBitsToFloat(Temp_int[4]).xxyz)).yzw;
                //Instruction 84
                //ADD
                Temp_int[2].xyz = floatBitsToInt(-intBitsToFloat(Temp_int[0]).yzwy + Input0.xyzx).xyz;
                //Instruction 85
                //DP3
                Temp_int[1].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[2]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
                //Instruction 86
                //SQRT
                Temp_int[1].w = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[1]).w)).w);
                //Instruction 87
                //DIV
                Temp_int[2].xyz = floatBitsToInt(intBitsToFloat(Temp_int[2]).xyzx / intBitsToFloat(Temp_int[1]).wwww).xyz;
                //Instruction 88
                //SAMPLE_L
                Temp_int[3] = floatBitsToInt(textureLod(g_txHeight, intBitsToFloat(Temp_int[0]).yz, 0.000000));
                //Instruction 89
                //SAMPLE_L
                Temp_int[8] = floatBitsToInt(textureLod(g_txMask, intBitsToFloat(Temp_int[0]).yz, 0.000000));
                //Instruction 90
                //MUL
                Temp_int[9].xy = floatBitsToInt(intBitsToFloat(Temp_int[0]).yzyy * cbUIPS.g_DetailRepeat).xy;
                //Instruction 91
                //SAMPLE_L
                Temp_int[9] = floatBitsToInt(textureLod(g_txDetailHeight, intBitsToFloat(Temp_int[9]).xy, 0.000000));
                //Instruction 92
                //DP4
                Temp_int[2].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[9]), intBitsToFloat(Temp_int[8]))).w);
                //Instruction 93
                //ADD
                Temp_int[2].w = floatBitsToInt(-intBitsToFloat(Temp_int[2]).w + 1.000000);
                //Instruction 94
                //MAD
                Temp_int[2].w = floatBitsToInt(-intBitsToFloat(Temp_int[2]).w * cbUIPS.g_DetailHeight + intBitsToFloat(Temp_int[3]).x);
                //Instruction 95
                //MUL
                Temp_int[3].x = floatBitsToInt(cbConstantPS.g_InvDetailMapSize * cbUIPS.g_InvDetailRepeat);
                //Instruction 96
                //MUL
                Temp_int[3].y = floatBitsToInt(intBitsToFloat(Temp_int[3]).x * 4.000000);
                //Instruction 97
                //MUL
                Temp_int[9].xyz = floatBitsToInt(intBitsToFloat(Temp_int[2]).xyzx * intBitsToFloat(Temp_int[3]).yyyy).xyz;
                //Instruction 98
                //MOV
                Temp_int[10] = ivec4(Temp_int[8]).xyzw;
                //Instruction 99
                //MOV
                Temp_int[7].xyz = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xyz;
                //Instruction 100
                //MOV
                Temp_int[12].xy = ivec4(Temp_int[6].xyxx).xy;
                //Instruction 101
                //MOV
                Temp_int[13].xy = ivec4(Temp_int[3].zwzz).xy;
                //Instruction 102
                //MOV
                Temp_int[11].xyz = ivec4(Temp_int[0].yzwy).xyz;
                //Instruction 103
                //MOV
                Temp_int[5].w = ivec4(Temp_int[2].w).w;
                //Instruction 104
                //MOV
                Temp_int[6].w = ivec4(int(0x0)).w;
                //Instruction 105
                //MOV
                Temp_int[9].w = ivec4(int(0x0)).w;
                //Instruction 106
                //MOV
                Temp_int[11].w = ivec4(int(0x0)).w;
                //Instruction 107
                //LOOP
                while(true){
                    //Instruction 108
                    //GE
                    Temp_int[12].z = floatBitsToInt(((Temp_int[5].w)>= (Temp_int[11].z)) ? int(0xFFFFFFFF) : 0);
                    //Instruction 109
                    //MOV
                    Temp_int[11].w = ivec4(int(0x0)).w;
                    //Instruction 110
                    //BREAKC
                    if((Temp_int[12].z)!=0){break;}
                    //Instruction 111
                    //MAD
                    Temp_int[6].w = floatBitsToInt(intBitsToFloat(Temp_int[3]).x * 4.000000 + intBitsToFloat(Temp_int[6]).w);
                    //Instruction 112
                    //MAD
                    Temp_int[14].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[2]).xyzx * intBitsToFloat(Temp_int[3]).yyyy + intBitsToFloat(Temp_int[11]).xyzx)).xyz;
                    //Instruction 113
                    //LT
                    Temp_int[12].z = floatBitsToInt(((intBitsToFloat(Temp_int[1]).w)< (intBitsToFloat(Temp_int[6]).w)) ? int(0xFFFFFFFF) : 0);
                    //Instruction 114
                    //ILT
                    Temp_int[12].w = (((int(0x80))< (Temp_int[9].w)) ? int(0xFFFFFFFF) : 0);
                    //Instruction 115
                    //OR
                    Temp_int[12].z = Temp_int[12].w | Temp_int[12].z;
                    //Instruction 116
                    //IF
                    if((Temp_int[12].z)!=0){
                        //Instruction 117
                        //MOV
                        Temp_int[7].xyz = ivec4(Temp_int[14].xzyx).xyz;
                        //Instruction 118
                        //MOV
                        Temp_int[12].xy = ivec4(Temp_int[13].xyxx).xy;
                        //Instruction 119
                        //MOV
                        Temp_int[11].xyz = ivec4(Temp_int[14].xyzx).xyz;
                        //Instruction 120
                        //MOV
                        Temp_int[11].w = ivec4(int(0xFFFFFFFF)).w;
                        //Instruction 121
                        //BREAK
                        break;
                        //Instruction 122
                    //ENDIF
                    }
                    //Instruction 123
                    //SAMPLE_L
                    Temp_int[13] = floatBitsToInt(textureLod(g_txHeight, intBitsToFloat(Temp_int[14]).xy, 0.000000).zwxy);
                    //Instruction 124
                    //SAMPLE_L
                    Temp_int[10] = floatBitsToInt(textureLod(g_txMask, intBitsToFloat(Temp_int[14]).xy, 0.000000));
                    //Instruction 125
                    //MUL
                    Temp_int[15].xy = floatBitsToInt(intBitsToFloat(Temp_int[14]).xyxx * cbUIPS.g_DetailRepeat).xy;
                    //Instruction 126
                    //SAMPLE_L
                    Temp_int[15] = floatBitsToInt(textureLod(g_txDetailHeight, intBitsToFloat(Temp_int[15]).xy, 0.000000));
                    //Instruction 127
                    //DP4
                    Temp_int[12].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[15]), intBitsToFloat(Temp_int[10]))).w);
                    //Instruction 128
                    //ADD
                    Temp_int[12].w = floatBitsToInt(-intBitsToFloat(Temp_int[12]).w + 1.000000);
                    //Instruction 129
                    //MAD
                    Temp_int[5].w = floatBitsToInt(-intBitsToFloat(Temp_int[12]).w * cbUIPS.g_DetailHeight + intBitsToFloat(Temp_int[13]).z);
                    //Instruction 130
                    //IADD
                    Temp_int[9].w = (Temp_int[9].w + int(0x1));
                    //Instruction 131
                    //MOV
                    Temp_int[11].xyz = ivec4(Temp_int[14].xyzx).xyz;
                    //Instruction 132
                    //MOV
                    Temp_int[11].w = ivec4(Temp_int[12].z).w;
                    //Instruction 133
                    //MOV
                    Temp_int[7].xyz = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xyz;
                    //Instruction 134
                //ENDLOOP
                }
                //Instruction 135
                //MOV
                Temp_int[6].xy = ivec4(Temp_int[12].xyxx).xy;
                //Instruction 136
                //IF
                if((Temp_int[11].w)==0){
                    //Instruction 137
                    //MAD
                    Temp_int[0].yzw = floatBitsToInt(vec4(-intBitsToFloat(Temp_int[2]).xxyz * intBitsToFloat(Temp_int[3]).yyyy + intBitsToFloat(Temp_int[11]).xxyz)).yzw;
                    //Instruction 138
                    //MOV
                    Temp_int[2] = ivec4(Temp_int[10]).xyzw;
                    //Instruction 139
                    //MOV
                    Temp_int[7].xyz = ivec4(Temp_int[11].xzyx).xyz;
                    //Instruction 140
                    //MOV
                    Temp_int[6].xy = ivec4(Temp_int[13].xyxx).xy;
                    //Instruction 141
                    //MOV
                    Temp_int[6].z = ivec4(int(0x3F000000)).z;
                    //Instruction 142
                    //MOV
                    Temp_int[1].w = ivec4(int(0x3E800000)).w;
                    //Instruction 143
                    //MOV
                    Temp_int[3].x = ivec4(int(0x0)).x;
                    //Instruction 144
                    //LOOP
                    while(true){
                        //Instruction 145
                        //IGE
                        Temp_int[3].y = (((Temp_int[3].x)>= (int(0x8))) ? int(0xFFFFFFFF) : 0);
                        //Instruction 146
                        //BREAKC
                        if((Temp_int[3].y)!=0){break;}
                        //Instruction 147
                        //MAD
                        Temp_int[3].yzw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[6]).zzzz * intBitsToFloat(Temp_int[9]).xxyz + intBitsToFloat(Temp_int[0]).yyzw)).yzw;
                        //Instruction 148
                        //SAMPLE_L
                        Temp_int[8] = floatBitsToInt(textureLod(g_txHeight, intBitsToFloat(Temp_int[3]).yz, 0.000000).zwxy);
                        //Instruction 149
                        //SAMPLE_L
                        Temp_int[12] = floatBitsToInt(textureLod(g_txMask, intBitsToFloat(Temp_int[3]).yz, 0.000000));
                        //Instruction 150
                        //MUL
                        Temp_int[13].zw = floatBitsToInt(intBitsToFloat(Temp_int[3]).yyyz * cbUIPS.g_DetailRepeat).zw;
                        //Instruction 151
                        //SAMPLE_L
                        Temp_int[14] = floatBitsToInt(textureLod(g_txDetailHeight, intBitsToFloat(Temp_int[13]).zw, 0.000000));
                        //Instruction 152
                        //DP4
                        Temp_int[5].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[14]), intBitsToFloat(Temp_int[12]))).w);
                        //Instruction 153
                        //ADD
                        Temp_int[5].w = floatBitsToInt(-intBitsToFloat(Temp_int[5]).w + 1.000000);
                        //Instruction 154
                        //MAD
                        Temp_int[5].w = floatBitsToInt(-intBitsToFloat(Temp_int[5]).w * cbUIPS.g_DetailHeight + intBitsToFloat(Temp_int[8]).z);
                        //Instruction 155
                        //GE
                        Temp_int[5].w = floatBitsToInt(((Temp_int[5].w)>= (Temp_int[3].w)) ? int(0xFFFFFFFF) : 0);
                        //Instruction 156
                        //MAD
                        Temp_int[8].z = floatBitsToInt(-intBitsToFloat(Temp_int[1]).w * 2.000000 + intBitsToFloat(Temp_int[6]).z);
                        //Instruction 157
                        //MOVC
                        if(ivec4(Temp_int[5].wwww).x != 0) {
                            Temp_int[2] = Temp_int[12];
                        } else {
                            Temp_int[2] = Temp_int[2];
                        }
                        //Instruction 158
                        //MOVC
                        if(ivec4(Temp_int[5].wwww).x != 0) {
                            Temp_int[7].xyz = ivec4(Temp_int[3].ywzy).xyz;
                        } else {
                            Temp_int[7].xyz = ivec4(Temp_int[7].xyzx).xyz;
                        }
                        //Instruction 159
                        //MOVC
                        if(ivec4(Temp_int[5].wwww).x != 0) {
                            Temp_int[6].xyz = ivec4(Temp_int[8].xyzx).xyz;
                        } else {
                            Temp_int[6].xyz = ivec4(Temp_int[6].xyzx).xyz;
                        }
                        //Instruction 160
                        //ADD
                        Temp_int[6].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).w + intBitsToFloat(Temp_int[6]).z);
                        //Instruction 161
                        //MUL
                        Temp_int[1].w = floatBitsToInt(intBitsToFloat(Temp_int[1]).w * 0.500000);
                        //Instruction 162
                        //IADD
                        Temp_int[3].x = (Temp_int[3].x + int(0x1));
                        //Instruction 163
                    //ENDLOOP
                    }
                    //Instruction 164
                    //MOV
                    Temp_int[10] = ivec4(Temp_int[2]).xyzw;
                    //Instruction 165
                    //MOV
                    Temp_int[5].xy = ivec4(Temp_int[7].xzxx).xy;
                    //Instruction 166
                //ELSE
                } else {
                    //Instruction 167
                    //MOV
                    Temp_int[5].xy = ivec4(Temp_int[7].xzxx).xy;
                    //Instruction 168
                //ENDIF
                }
                //Instruction 169
            //ELSE
            } else {
                //Instruction 170
                //SAMPLE_L
                Temp_int[10] = floatBitsToInt(textureLod(g_txMask, intBitsToFloat(Temp_int[4]).xy, 0.000000));
                //Instruction 171
            //ENDIF
            }
            //Instruction 172
        //ELSE
        } else {
            //Instruction 173
            //MOV
            Temp_int[10] = ivec4(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).xyzw;
            //Instruction 174
            //MOV
            Temp_int[0].x = ivec4(int(0x0)).x;
            //Instruction 175
        //ENDIF
        }
        //Instruction 176
        //IF
        if((Temp_int[0].x)==0){
            //Instruction 177
            //MUL
            Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[1]).xyzx * intBitsToFloat(Temp_int[4]).wwww).xyz;
            //Instruction 178
            //MAD
            Temp_int[1].xyz = floatBitsToInt(vec4(-intBitsToFloat(Temp_int[4]).wwww * intBitsToFloat(Temp_int[1]).xyzx + intBitsToFloat(Temp_int[4]).xyzx)).xyz;
            //Instruction 179
            //MOV
            Temp_int[7].xyz = ivec4(Temp_int[4].xzyx).xyz;
            //Instruction 180
            //MOV
            Temp_int[2].xy = ivec4(Temp_int[6].xyxx).xy;
            //Instruction 181
            //MOV
            Temp_int[2].z = ivec4(int(0x3F000000)).z;
            //Instruction 182
            //MOV
            Temp_int[0].w = ivec4(int(0x3E800000)).w;
            //Instruction 183
            //MOV
            Temp_int[1].w = ivec4(int(0x0)).w;
            //Instruction 184
            //LOOP
            while(true){
                //Instruction 185
                //IGE
                Temp_int[2].w = (((Temp_int[1].w)>= (int(0x8))) ? int(0xFFFFFFFF) : 0);
                //Instruction 186
                //BREAKC
                if((Temp_int[2].w)!=0){break;}
                //Instruction 187
                //MAD
                Temp_int[3].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[2]).zzzz * intBitsToFloat(Temp_int[0]).xyzx + intBitsToFloat(Temp_int[1]).xyzx)).xyz;
                //Instruction 188
                //SAMPLE_L
                Temp_int[8] = floatBitsToInt(textureLod(g_txHeight, intBitsToFloat(Temp_int[3]).xy, 0.000000).zwxy);
                //Instruction 189
                //GE
                Temp_int[2].w = floatBitsToInt(((Temp_int[8].z)>= (Temp_int[3].z)) ? int(0xFFFFFFFF) : 0);
                //Instruction 190
                //MAD
                Temp_int[8].z = floatBitsToInt(-intBitsToFloat(Temp_int[0]).w * 2.000000 + intBitsToFloat(Temp_int[2]).z);
                //Instruction 191
                //MOVC
                if(ivec4(Temp_int[2].wwww).x != 0) {
                    Temp_int[7].xyz = ivec4(Temp_int[3].xzyx).xyz;
                } else {
                    Temp_int[7].xyz = ivec4(Temp_int[7].xyzx).xyz;
                }
                //Instruction 192
                //MOVC
                if(ivec4(Temp_int[2].wwww).x != 0) {
                    Temp_int[2].xyz = ivec4(Temp_int[8].xyzx).xyz;
                } else {
                    Temp_int[2].xyz = ivec4(Temp_int[2].xyzx).xyz;
                }
                //Instruction 193
                //ADD
                Temp_int[2].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[2]).z);
                //Instruction 194
                //MUL
                Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.500000);
                //Instruction 195
                //IADD
                Temp_int[1].w = (Temp_int[1].w + int(0x1));
                //Instruction 196
            //ENDLOOP
            }
            //Instruction 197
            //MOV
            Temp_int[6].xy = ivec4(Temp_int[2].xyxx).xy;
            //Instruction 198
            //MOV
            Temp_int[5].xy = ivec4(Temp_int[7].xzxx).xy;
            //Instruction 199
        //ENDIF
        }
        //Instruction 200
    //ELSE
    } else {
        //Instruction 201
        //MOV
        Temp_int[10] = ivec4(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).xyzw;
        //Instruction 202
        //MOV
        Temp_int[6].xy = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xy;
        //Instruction 203
    //ENDIF
    }
    //Instruction 204
    //GE
    Temp_int[0].x = floatBitsToInt(((Temp_int[5].x)>= (0.000000)) ? int(0xFFFFFFFF) : 0);
    //Instruction 205
    //IF
    if((Temp_int[0].x)!=0){
        //Instruction 206
        //ADD
        Temp_int[0].xy = floatBitsToInt(intBitsToFloat(Temp_int[6]).xyxx + vec4(-0.500000, -0.500000, 0.000000, 0.000000)).xy;
        //Instruction 207
        //ADD
        Temp_int[0].xz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xxyx + intBitsToFloat(Temp_int[0]).xxyx).xz;
        //Instruction 208
        //MAD
        Temp_int[0].w = floatBitsToInt(-intBitsToFloat(Temp_int[6]).x * intBitsToFloat(Temp_int[6]).x + 1.000000);
        //Instruction 209
        //MAD
        Temp_int[0].w = floatBitsToInt(-intBitsToFloat(Temp_int[6]).y * intBitsToFloat(Temp_int[6]).y + intBitsToFloat(Temp_int[0]).w);
        //Instruction 210
        //SQRT
        Temp_int[0].w = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[0]).w)).w);
        //Instruction 211
        //MUL
        Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.500000);
        //Instruction 212
        //DP3
        Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).xyzx).xyz, (intBitsToFloat(Temp_int[0]).xyzx).xyz)).w);
        //Instruction 213
        //RSQ
        Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
        //Instruction 214
        //MUL
        Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[0]).xyzx).xyz;
        //Instruction 215
        //IF
        if((_ParamsPS.bDetail)!=0){
            //Instruction 216
            //ADD
            Temp_int[5].z = floatBitsToInt(-intBitsToFloat(Temp_int[5]).y + 1.000000);
            //Instruction 217
            //MUL
            Temp_int[1].xy = floatBitsToInt(intBitsToFloat(Temp_int[5]).xzxx * cbUIPS.g_DetailRepeat).xy;
            //Instruction 218
            //SAMPLE_L
            Temp_int[2] = floatBitsToInt(textureLod(g_txDetailGrad_RedGreen, intBitsToFloat(Temp_int[1]).xy, 0.000000));
            //Instruction 219
            //SAMPLE_L
            Temp_int[1] = floatBitsToInt(textureLod(g_txDetailGrad_BlueAlpha, intBitsToFloat(Temp_int[1]).xy, 0.000000));
            //Instruction 220
            //MUL
            Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[10]).yyyy * intBitsToFloat(Temp_int[2]).zzzw).zw;
            //Instruction 221
            //MAD
            Temp_int[2].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[2]).xyxx * intBitsToFloat(Temp_int[10]).xxxx + intBitsToFloat(Temp_int[2]).zwzz)).xy;
            //Instruction 222
            //MAD
            Temp_int[1].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).xyxx * intBitsToFloat(Temp_int[10]).zzzz + intBitsToFloat(Temp_int[2]).xyxx)).xy;
            //Instruction 223
            //MAD
            Temp_int[1].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).zwzz * intBitsToFloat(Temp_int[10]).wwww + intBitsToFloat(Temp_int[1]).xyxx)).xy;
            //Instruction 224
            //ADD
            Temp_int[1].xy = floatBitsToInt(intBitsToFloat(Temp_int[1]).xyxx + vec4(-0.500000, -0.500000, 0.000000, 0.000000)).xy;
            //Instruction 225
            //MUL
            Temp_int[1].xy = floatBitsToInt(intBitsToFloat(Temp_int[1]).xyxx * cbConstantPS.g_DetailMapSize).xy;
            //Instruction 226
            //MUL
            Temp_int[1].xy = floatBitsToInt(intBitsToFloat(Temp_int[1]).xyxx * cbUIPS.g_DetailRepeat).xy;
            //Instruction 227
            //MUL
            Temp_int[1].xy = floatBitsToInt(intBitsToFloat(Temp_int[1]).xyxx * cbUIPS.g_DetailHeight).xy;
            //Instruction 228
            //MOV
            Temp_int[1].z = ivec4(-Temp_int[1].x).z;
            //Instruction 229
            //ADD
            Temp_int[1].w = floatBitsToInt(-cbUIPS.g_DetailHeight + 1.000000);
            //Instruction 230
            //MUL
            Temp_int[2].xyz = floatBitsToInt(intBitsToFloat(Temp_int[1]).xwyx * vec4(-1.000000, 1.000000, 1.000000, 0.000000)).xyz;
            //Instruction 231
            //DP3
            Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[1]).zwyz).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
            //Instruction 232
            //RSQ
            Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
            //Instruction 233
            //MUL
            Temp_int[1].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[2]).xyzx).xyz;
            //Instruction 234
            //MAD
            Temp_int[1].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).xyzx * vec4(0.500000, 0.500000, 0.500000, 0.000000) + intBitsToFloat(Temp_int[0]).xyzx)).xyz;
            //Instruction 235
            //DP3
            Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[1]).xyzx).xyz, (intBitsToFloat(Temp_int[1]).xyzx).xyz)).w);
            //Instruction 236
            //RSQ
            Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
            //Instruction 237
            //MUL
            Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[1]).xyzx).xyz;
            //Instruction 238
        //ENDIF
        }
        //Instruction 239
        //DP3
        Temp_int[0].x = floatBitsToInt(vec4(dot((cbOnRenderPS.g_LightDir.xyzx.xyzx).xyz, (intBitsToFloat(Temp_int[0]).xyzx).xyz)).x);
        Temp_int[0].x = floatBitsToInt(clamp(intBitsToFloat(Temp_int[0]).x, 0, 1));
        //Instruction 240
        //IF
        if((_ParamsPS.bDetail)!=0){
            //Instruction 241
            //MUL
            Temp_int[0].yz = floatBitsToInt(intBitsToFloat(Temp_int[5]).xxyx * cbUIPS.g_DetailRepeat).yz;
            //Instruction 242
            //SAMPLE_L
            Temp_int[1] = floatBitsToInt(textureLod(g_txDetailDiffuse, intBitsToFloat(Temp_int[0]).yz, 0.000000));
            //Instruction 243
            //SAMPLE_L
            Temp_int[2] = floatBitsToInt(textureLod(g_txDetailDiffuse1, intBitsToFloat(Temp_int[0]).yz, 0.000000));
            //Instruction 244
            //MUL
            Temp_int[2] = floatBitsToInt(intBitsToFloat(Temp_int[10]).yyyy * intBitsToFloat(Temp_int[2]));
            //Instruction 245
            //MAD
            Temp_int[1] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]) * intBitsToFloat(Temp_int[10]).xxxx + intBitsToFloat(Temp_int[2])));
            //Instruction 246
            //SAMPLE_L
            Temp_int[2] = floatBitsToInt(textureLod(g_txDetailDiffuse2, intBitsToFloat(Temp_int[0]).yz, 0.000000));
            //Instruction 247
            //MAD
            Temp_int[1] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[2]) * intBitsToFloat(Temp_int[10]).zzzz + intBitsToFloat(Temp_int[1])));
            //Instruction 248
            //SAMPLE_L
            Temp_int[2] = floatBitsToInt(textureLod(g_txDetailDiffuse3, intBitsToFloat(Temp_int[0]).yz, 0.000000));
            //Instruction 249
            //MAD
            Temp_int[1] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[2]) * intBitsToFloat(Temp_int[10]).wwww + intBitsToFloat(Temp_int[1])));
            //Instruction 250
        //ELSE
        } else {
            //Instruction 251
            //MOV
            Temp_int[1] = ivec4(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).xyzw;
            //Instruction 252
        //ENDIF
        }
        //Instruction 253
        //IF
        if((_ParamsPS.bShadow)!=0){
            //Instruction 254
            //MOV
            Temp_int[7].xz = ivec4(Temp_int[5].xxyx).xz;
            //Instruction 255
            //MOV
            Temp_int[7].w = ivec4(int(0x3F800000)).w;
            //Instruction 256
            //DP4
            Temp_int[2].x = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[7]), cbOnRenderPS.g_mTexToLightViewProj[0])).x);
            //Instruction 257
            //DP4
            Temp_int[2].y = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[7]), cbOnRenderPS.g_mTexToLightViewProj[1])).y);
            //Instruction 258
            //DP4
            Temp_int[0].y = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[7]), cbOnRenderPS.g_mTexToLightViewProj[2])).y);
            //Instruction 259
            //DP4
            Temp_int[0].z = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[7]), cbOnRenderPS.g_mTexToLightViewProj[3])).z);
            //Instruction 260
            //DIV
            Temp_int[2].xy = floatBitsToInt(intBitsToFloat(Temp_int[2]).xyxx / intBitsToFloat(Temp_int[0]).zzzz).xy;
            //Instruction 261
            //MAD
            Temp_int[2].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[2]).xyxx * vec4(0.500000, 0.500000, 0.000000, 0.000000) + vec4(0.500000, 0.500000, 0.000000, 0.000000))).xy;
            //Instruction 262
            //DIV
            Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).y / intBitsToFloat(Temp_int[0]).z);
            //Instruction 263
            //ADD
            Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).y + -cbUIPS.g_ShadowBias);
            //Instruction 264
            //ADD
            Temp_int[2].z = floatBitsToInt(-intBitsToFloat(Temp_int[2]).y + 1.000000);
            //Instruction 265
            //SAMPLE_C_LZ
            Temp_int[0].y = floatBitsToInt(vec4(textureLod(hlslcc_zcmpg_txDepthMap, vec3(intBitsToFloat(Temp_int[2]).xz,intBitsToFloat(Temp_int[0]).y), 0)).xxxx).y;
            //Instruction 266
        //ELSE
        } else {
            //Instruction 267
            //MOV
            Temp_int[0].y = ivec4(int(0x3F800000)).y;
            //Instruction 268
        //ENDIF
        }
        //Instruction 269
        //MUL
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[0]).x);
        //Instruction 270
        //MAX
        Temp_int[0].x = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[0]).x, 0.100000)).x);
        //Instruction 271
        //MUL
        Output0 = (intBitsToFloat(Temp_int[0]).xxxx * intBitsToFloat(Temp_int[1]));
        //Instruction 272
    //ELSE
    } else {
        //Instruction 273
        //DISCARD
        if((int(0xFFFFFFFF))!=0){discard;}
        //Instruction 274
        //MOV
        Output0 = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).xyzw;
        //Instruction 275
    //ENDIF
    }
    //Instruction 276
    //MOV
    Temp_int[7].xz = ivec4(Temp_int[5].xxyx).xz;
    //Instruction 277
    //MOV
    Temp_int[7].w = ivec4(int(0x3F800000)).w;
    //Instruction 278
    //DP4
    Temp_int[0].x = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[7]), cbOnRenderPS.g_mTexToViewProj[2])).x);
    //Instruction 279
    //DP4
    Temp_int[0].y = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[7]), cbOnRenderPS.g_mTexToViewProj[3])).y);
    //Instruction 280
    //DIV
    gl_FragDepth = (intBitsToFloat(Temp_int[0]).x / intBitsToFloat(Temp_int[0]).y);
    //Instruction 281
    //RET
    return;
}
