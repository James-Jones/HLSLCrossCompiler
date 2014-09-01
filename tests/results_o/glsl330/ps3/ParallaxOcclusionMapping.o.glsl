#version 330
int RepCounter;
int LoopCounter;
int ZeroBasedCounter;
in vec4 OffsetColour;
in vec4 BaseColour;
in vec4 Fog;
in vec4 TexCoord0;
in vec4 TexCoord1;
in vec4 TexCoord2;
in vec4 TexCoord3;
in vec4 TexCoord4;
in vec4 TexCoord5;
in vec4 TexCoord6;
in vec4 TexCoord7;
out vec4 outFragData[8];
#define Output0 outFragData[0]
#define Output1 outFragData[1]
#define Output2 outFragData[2]
#define Output3 outFragData[3]
#define Output4 outFragData[4]
#define Output5 outFragData[5]
#define Output6 outFragData[6]
#define Output7 outFragData[7]
struct vec1 {
	float x;
};
struct uvec1 {
	uint x;
};
struct ivec1 {
	int x;
};
const vec4 ImmConst14 = vec4(2.000000, -1.000000, 0.000000, 0.000000);
const vec4 ImmConst15 = vec4(0.880000, 0.770000, -0.880000, -0.770000);
const vec4 ImmConst16 = vec4(0.660000, 0.550000, -0.660000, 4.000000);
const vec4 ImmConst17 = vec4(6.000000, 0.440000, 0.330000, -0.440000);
const vec4 ImmConst18 = vec4(8.000000, 10.000000, 0.220000, -0.220000);
const vec4 ImmConst19 = vec4(12.000000, 0.600000, 0.400000, 3.000000);
const vec4 ImmConst20 = vec4(0.500000, 0.000000, 1.000000, 0.000000);
const ivec4 IntImmConst0 = ivec4(0xFF, 0x0, 0x0, 0x0);
uniform sampler2D tBase;
uniform sampler2D tNormalHeightMap;
vec4 Temp[10];
ivec4 Temp_int[10];
uvec4 Temp_uint[10];
uniform struct GlobalsPS_Type {
	float g_bAddSpecular;
	float g_bDisplayShadows;
	float g_bVisualizeLOD;
	float g_bVisualizeMipLevel;
	float g_fHeightMapScale;
	float g_fShadowSoftening;
	float g_fSpecularExponent;
	vec4 g_materialAmbientColor;
	vec4 g_materialDiffuseColor;
	vec4 g_materialSpecularColor;
	float g_nLODThreshold;
	float g_nMaxSamples;
	float g_nMinSamples;
	vec2 g_vTextureDims;
} GlobalsPS;
vec4 ImmConstArray [7];
void main()
{
    //--- Start Early Main ---
    ImmConstArray[0] = ImmConst14;
    ImmConstArray[1] = ImmConst15;
    ImmConstArray[2] = ImmConst16;
    ImmConstArray[3] = ImmConst17;
    ImmConstArray[4] = ImmConst18;
    ImmConstArray[5] = ImmConst19;
    ImmConstArray[6] = ImmConst20;
    //--- End Early Main ---
    //Instruction 0
    //DP4
    Temp[0].xyz = vec3(dot(TexCoord2, TexCoord2));
    //Instruction 1
    //RSQ
    Temp[0].xyz = inversesqrt(Temp[0].xyz);
    //Instruction 2
    //DP4
    Temp[1].xyz = vec3(dot(TexCoord1, TexCoord1));
    //Instruction 3
    //RSQ
    Temp[1].xyz = inversesqrt(Temp[1].xyz);
    //Instruction 4
    //MUL
    Temp[2].xy = GlobalsPS.g_vTextureDims.xyxx.xy * TexCoord0.xy;
    //Instruction 5
    //DERIV_RTX
    Temp[2].zw = dFdx(Temp[2].xy);
    //Instruction 6
    //DERIV_RTY
    Temp[2].xy = dFdy(Temp[2].xy);
    //Instruction 7
    //MUL
    Temp[2].xy = Temp[2].xy * Temp[2].xy;
    //Instruction 8
    //MAD
    Temp[2].xy = Temp[2].zw * Temp[2].zw + Temp[2].xy;
    //Instruction 9
    //MAX
    Temp[0].w = max(Temp[2].x, Temp[2].y);
    //Instruction 10
    //LOG
    Temp[0].w = log2(Temp[0].w);
    //Instruction 11
    //MUL
    Temp[0].w = Temp[0].w * ImmConst20.x;
    //Instruction 12
    //MAX
    Temp[2].x = max(Temp[0].w, ImmConst20.y);
    //Instruction 13
    //ADD
    Temp[0].w = (-Temp[2].x) + GlobalsPS.g_nLODThreshold;
    //Instruction 14
    //IF
    if(GlobalsPS.g_nLODThreshold >= Temp[2].x){
        //Instruction 15
        //DERIV_RTX
        Temp[2].yz = dFdx(TexCoord0.xy);
        //Instruction 16
        //DERIV_RTY
        Temp[3].xy = dFdy(TexCoord0.xy);
        //Instruction 17
        //DP4
        Temp[4].xyz = vec3(dot(TexCoord5, TexCoord5));
        //Instruction 18
        //RSQ
        Temp[4].xyz = inversesqrt(Temp[4].xyz);
        //Instruction 19
        //DP4
        Temp[5].xyz = vec3(dot(TexCoord4, TexCoord4));
        //Instruction 20
        //RSQ
        Temp[5].xyz = inversesqrt(Temp[5].xyz);
        //Instruction 21
        //DP3
        Temp[2].w = dot(Temp[4].xyz, Temp[5].xyz);
        //Instruction 22
        //MOV
        Temp[4].x = GlobalsPS.g_nMaxSamples;
        //Instruction 23
        //ADD
        Temp[3].z = (-Temp[4].x) + GlobalsPS.g_nMinSamples;
        //Instruction 24
        //MUL
        Temp[3].w = Temp[2].w * Temp[3].z;
        //Instruction 25
        //MAD
        Temp[2].w = Temp[2].w * Temp[3].z + GlobalsPS.g_nMaxSamples;
        //Instruction 26
        //FRC
        Temp[3].z = fract(Temp[3].w);
        //Instruction 27
        //ADD
        Temp[3].w = Temp[2].w + (-Temp[3].z);
        //Instruction 28
        //MOVC
        Temp[3].z = ((-Temp[3].z) >= 0) ? ImmConst20.y : ImmConst20.z;
        //Instruction 29
        //MOVC
        Temp[2].w = (Temp[2].w >= 0) ? ImmConst20.y : Temp[3].z;
        //Instruction 30
        //ADD
        Temp[2].w = Temp[2].w + Temp[3].w;
        //Instruction 31
        //RCP
        Temp[3].z = (vec4(1.0) / vec4(Temp[2].w)).x;
        //Instruction 32
        //ADD
        Temp[3].w = Temp[2].w + ImmConst20.z;
        //Instruction 33
        //MOV
        Temp[4].xy = TexCoord0.xy;
        //Instruction 34
        //MOV
        Temp[4].z = ImmConst20.y;
        //Instruction 35
        //MOV
        Temp[5].zw = vec2(ImmConst20.z);
        //Instruction 36
        //MOV
        Temp[6] = vec4(ImmConst20.y);
        //Instruction 37
        //REP
        RepCounter = int(IntImmConst0.x);
        while(RepCounter!=0){
            //Instruction 38
            //MOV
            Temp[4].w = Temp[2].w;
            //Instruction 39
            //BREAKC
            if(Temp[4].z >= Temp[4].w){ break; }
            //Instruction 40
            //MAD
            Temp[4].xy = Temp[3].z * (-TexCoord3.xy) + Temp[4].xy;
            //Instruction 41
            //SAMPLE_D
            Temp[7] = textureGrad(tNormalHeightMap, Temp[4].xy, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 42
            //ADD
            Temp[5].x = (-Temp[3].z) + Temp[5].z;
            //Instruction 43
            //ADD
            Temp[4].w = (-Temp[7].w) + Temp[5].x;
            //Instruction 44
            //ADD
            Temp[7].x = Temp[4].z + ImmConst20.z;
            //Instruction 45
            //MOVC
            Temp[4].z = (Temp[4].w >= 0) ? Temp[7].x : Temp[3].w;
            //Instruction 46
            //MOV
            Temp[5].y = Temp[7].w;
            //Instruction 47
            //MOVC
            Temp[6] = (Temp[4].w >= 0) ? Temp[6] : Temp[5];
            //Instruction 48
            //MOV
            Temp[5].w = Temp[7].w;
            //Instruction 49
            //MOV
            Temp[5].z = Temp[5].x;
            //Instruction 50
            //ENDREP
            RepCounter--;
        }
        //Instruction 51
        //ADD
        Temp[2].w = (-Temp[6].w) + Temp[6].z;
        //Instruction 52
        //ADD
        Temp[3].z = (-Temp[6].y) + Temp[6].x;
        //Instruction 53
        //ADD
        Temp[3].w = Temp[2].w + (-Temp[3].z);
        //Instruction 54
        //MUL
        Temp[3].z = Temp[3].z * Temp[6].z;
        //Instruction 55
        //MAD
        Temp[2].w = Temp[6].x * Temp[2].w + (-Temp[3].z);
        //Instruction 56
        //RCP
        Temp[3].z = (vec4(1.0) / vec4(Temp[3].w)).x;
        //Instruction 57
        //MAD
        Temp[2].w = Temp[2].w * (-Temp[3].z) + ImmConst20.z;
        //Instruction 58
        //MOVC
        Temp[2].w = (-abs(Temp[3].w) >= 0) ? ImmConst20.z : Temp[2].w;
        //Instruction 59
        //MOV
        Temp[4].xy = TexCoord0.xy;
        //Instruction 60
        //MAD
        Temp[3].zw = TexCoord3.xy * (-Temp[2].w) + Temp[4].xy;
        //Instruction 61
        //ADD
        Temp[0].w = Temp[0].w + (-ImmConst20.z);
        //Instruction 62
        //FRC
        Temp[2].w = fract(Temp[2].x);
        //Instruction 63
        //ADD
        Temp[2].w = Temp[2].x + (-Temp[2].w);
        //Instruction 64
        //ADD
        Temp[2].w = (-Temp[2].w) + Temp[2].x;
        //Instruction 65
        //ADD
        Temp[4].x = Temp[2].w + Temp[2].w;
        //Instruction 66
        //MAX
        Temp[5].x = max(ImmConst20.z, Temp[4].x);
        //Instruction 67
        //MOV
        Temp[4].yz = ImmConst20.yz;
        //Instruction 68
        //MOVC
        Temp[4].x = ((-GlobalsPS.g_bVisualizeLOD) >= 0) ? Temp[4].z : Temp[5].x;
        //Instruction 69
        //LRP
        Temp[5].xy = mix(TexCoord0.xy, Temp[3].zw, Temp[2].w);
        //Instruction 70
        //MOVC
        Temp[6].x = (Temp[0].w >= 0) ? ImmConst20.z : Temp[4].x;
        //Instruction 71
        //MOVC
        Temp[4].xw = (Temp[0].w >= 0) ? Temp[3].zw : Temp[5].xy;
        //Instruction 72
        //ADD
        Temp[0].w = (-Temp[4].z) + GlobalsPS.g_bDisplayShadows;
        //Instruction 73
        //IF
        if((-Temp[0].w) != Temp[0].w){
            //Instruction 74
            //MOV
            Temp[0].w = ImmConst20.z;
            //Instruction 75
        //ELSE
        } else {
            //Instruction 76
            //MUL
            Temp[5].xy = Temp[1].xy * GlobalsPS.g_fHeightMapScale;
            //Instruction 77
            //SAMPLE_D
            Temp[7] = textureGrad(tNormalHeightMap, Temp[3].zw, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 78
            //MAD
            Temp[8] = Temp[5].xyxy * ImmConst15.xxyy + Temp[3].zwzw;
            //Instruction 79
            //SAMPLE_D
            Temp[9] = textureGrad(tNormalHeightMap, Temp[8].xy, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 80
            //ADD
            Temp[2].w = (-Temp[7].w) + Temp[9].w;
            //Instruction 81
            //ADD
            Temp[2].w = Temp[2].w + ImmConst15.z;
            //Instruction 82
            //SAMPLE_D
            Temp[8] = textureGrad(tNormalHeightMap, Temp[8].zw, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 83
            //ADD
            Temp[4].z = (-Temp[7].w) + Temp[8].w;
            //Instruction 84
            //ADD
            Temp[4].z = Temp[4].z + ImmConst15.w;
            //Instruction 85
            //DP2ADD
            Temp[4].y = dot(vec2(Temp[4].z), vec2(GlobalsPS.g_fShadowSoftening)) + Temp[4].y;
            //Instruction 86
            //MAD
            Temp[8] = Temp[5].xyxy * ImmConst16.xxyy + Temp[3].zwzw;
            //Instruction 87
            //SAMPLE_D
            Temp[9] = textureGrad(tNormalHeightMap, Temp[8].xy, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 88
            //ADD
            Temp[4].z = (-Temp[7].w) + Temp[9].w;
            //Instruction 89
            //ADD
            Temp[4].z = Temp[4].z + ImmConst16.z;
            //Instruction 90
            //MUL
            Temp[4].z = Temp[4].z * GlobalsPS.g_fShadowSoftening;
            //Instruction 91
            //MUL
            Temp[4].z = Temp[4].z * ImmConst16.w;
            //Instruction 92
            //SAMPLE_D
            Temp[8] = textureGrad(tNormalHeightMap, Temp[8].zw, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 93
            //ADD
            Temp[5].z = (-Temp[7].w) + Temp[8].w;
            //Instruction 94
            //ADD
            Temp[5].z = Temp[5].z + (-ImmConst16.y);
            //Instruction 95
            //MUL
            Temp[5].z = Temp[5].z * GlobalsPS.g_fShadowSoftening;
            //Instruction 96
            //MUL
            Temp[5].z = Temp[5].z * ImmConst17.x;
            //Instruction 97
            //MAD
            Temp[8] = Temp[5].xyxy * ImmConst17.yyzz + Temp[3].zwzw;
            //Instruction 98
            //SAMPLE_D
            Temp[9] = textureGrad(tNormalHeightMap, Temp[8].xy, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 99
            //ADD
            Temp[5].w = (-Temp[7].w) + Temp[9].w;
            //Instruction 100
            //ADD
            Temp[5].w = Temp[5].w + ImmConst17.w;
            //Instruction 101
            //MUL
            Temp[5].w = Temp[5].w * GlobalsPS.g_fShadowSoftening;
            //Instruction 102
            //MUL
            Temp[5].w = Temp[5].w * ImmConst18.x;
            //Instruction 103
            //SAMPLE_D
            Temp[8] = textureGrad(tNormalHeightMap, Temp[8].zw, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 104
            //ADD
            Temp[6].z = (-Temp[7].w) + Temp[8].w;
            //Instruction 105
            //ADD
            Temp[6].z = Temp[6].z + (-ImmConst17.z);
            //Instruction 106
            //MUL
            Temp[6].z = Temp[6].z * GlobalsPS.g_fShadowSoftening;
            //Instruction 107
            //MUL
            Temp[6].z = Temp[6].z * ImmConst18.y;
            //Instruction 108
            //MAD
            Temp[3].zw = Temp[5].xy * ImmConst18.z + Temp[3].zw;
            //Instruction 109
            //SAMPLE_D
            Temp[3] = textureGrad(tNormalHeightMap, Temp[3].zw, vec4(Temp[2].yzzw).xy, vec4(Temp[3]).xy);
            //Instruction 110
            //ADD
            Temp[2].y = (-Temp[7].w) + Temp[3].w;
            //Instruction 111
            //ADD
            Temp[2].y = Temp[2].y + ImmConst18.w;
            //Instruction 112
            //MUL
            Temp[2].yw = Temp[2].yw * GlobalsPS.g_fShadowSoftening;
            //Instruction 113
            //MUL
            Temp[2].y = Temp[2].y * ImmConst19.x;
            //Instruction 114
            //MAX
            Temp[3].x = max(Temp[2].w, Temp[4].y);
            //Instruction 115
            //MAX
            Temp[2].z = max(Temp[3].x, Temp[4].z);
            //Instruction 116
            //MAX
            Temp[3].x = max(Temp[2].z, Temp[5].z);
            //Instruction 117
            //MAX
            Temp[2].z = max(Temp[3].x, Temp[5].w);
            //Instruction 118
            //MAX
            Temp[3].x = max(Temp[2].z, Temp[6].z);
            //Instruction 119
            //MAX
            Temp[4].y = max(Temp[3].x, Temp[2].y);
            //Instruction 120
            //ADD
            Temp[2].y = (-Temp[4].y) + ImmConst20.z;
            //Instruction 121
            //MAD
            Temp[0].w = Temp[2].y * ImmConst19.y + ImmConst19.z;
            //Instruction 122
        //ENDIF
        }
        //Instruction 123
    //ELSE
    } else {
        //Instruction 124
        //MOV
        Temp[6].x = ImmConst19.w;
        //Instruction 125
        //MOV
        Temp[4].xw = TexCoord0.xy;
        //Instruction 126
        //MOV
        Temp[0].w = ImmConst20.z;
        //Instruction 127
    //ENDIF
    }
    //Instruction 128
    //SAMPLE
    Temp[3] = texture(tBase, Temp[4].xw);
    //Instruction 129
    //MAD
    Temp[3] = Temp[3] * ImmConst14.x + ImmConst14.y;
    //Instruction 130
    //DP4
    Temp[2].y = dot(Temp[3], Temp[3]);
    //Instruction 131
    //RSQ
    Temp[2].y = inversesqrt(Temp[2].y);
    //Instruction 132
    //MUL
    Temp[2].yzw = Temp[2].y * Temp[3].xyz;
    //Instruction 133
    //SAMPLE
    Temp[3] = texture(tBase, Temp[4].xw);
    //Instruction 134
    //MOV
    Temp[1].w = (-Temp[1].y);
    //Instruction 135
    //DP3
    Temp[1].y = dot(Temp[2].ywz, Temp[1].xzw);
    Temp[1].y = clamp(Temp[1], 0.0, 1.0);
    //Instruction 136
    //DP3
    Temp[4].x = dot(Temp[0].xyz, Temp[2].yzw);
    //Instruction 137
    //ADD
    Temp[4].x = Temp[4].x + Temp[4].x;
    //Instruction 138
    //MAD
    Temp[0].xyz = Temp[4].x * Temp[2].yzw + (-Temp[0].xyz);
    //Instruction 139
    //DP4
    Temp[4].xyz = vec3(dot(Temp[0], Temp[0]));
    //Instruction 140
    //RSQ
    Temp[4].xyz = inversesqrt(Temp[4].xyz);
    //Instruction 141
    //DP3
    Temp[0].x = dot(Temp[4].xzy, Temp[1].xzw);
    Temp[0].x = clamp(Temp[0], 0.0, 1.0);
    //Instruction 142
    //POW
    Temp[1].x = pow(abs(Temp[0].x), GlobalsPS.g_fSpecularExponent);
    Temp[1].x = clamp(Temp[1], 0.0, 1.0);
    //Instruction 143
    //MUL
    Temp[4] = Temp[1].x * GlobalsPS.g_materialSpecularColor;
    //Instruction 144
    //MOV
    Temp[0].y = ImmConst20.y;
    //Instruction 145
    //MOVC
    Temp[4] = ((-GlobalsPS.g_bAddSpecular) >= 0) ? vec4(Temp[0].y) : Temp[4];
    //Instruction 146
    //MOV
    Temp[5] = GlobalsPS.g_materialDiffuseColor;
    //Instruction 147
    //MAD
    Temp[1] = Temp[1].y * Temp[5] + GlobalsPS.g_materialAmbientColor;
    //Instruction 148
    //MAD
    Temp[1] = Temp[1] * Temp[3] + Temp[4];
    //Instruction 149
    //MUL
    Temp[0] = Temp[0].w * Temp[1];
    //Instruction 150
    //MOV
    Temp[6].y = ImmConst20.z;
    //Instruction 151
    //MUL
    Temp[1] = Temp[0] * Temp[6].yyxy;
    //Instruction 152
    //MOVC
    Temp[0] = ((-GlobalsPS.g_bVisualizeLOD) >= 0) ? Temp[0] : Temp[1];
    //Instruction 153
    //MOVC
    Output0 = ((-GlobalsPS.g_bVisualizeMipLevel) >= 0) ? Temp[0] : vec4(Temp[2].x);
    //Instruction 154
    //RET
    return;
}
