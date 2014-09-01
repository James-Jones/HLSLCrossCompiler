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
const vec4 ImmConst1 = vec4(0.000000, -1.000000, 1.000000, 1.963211);
const vec4 ImmConst2 = vec4(0.125000, -0.041667, 0.250000, -0.250000);
const vec4 ImmConst3 = vec4(1.333333, 0.750000, -0.500000, 0.500000);
const vec4 ImmConst4 = vec4(0.000000, 0.111111, 0.000000, 0.000000);
const ivec4 IntImmConst0 = ivec4(0x10, 0x0, 0x0, 0x0);
uniform sampler2D g_samScene;
vec4 Temp[9];
ivec4 Temp_int[9];
uvec4 Temp_uint[9];
uniform struct GlobalsPS_Type {
	vec4 rcpFrame;
} GlobalsPS;
vec4 ImmConstArray [4];
void main()
{
    //--- Start Early Main ---
    ImmConstArray[0] = ImmConst1;
    ImmConstArray[1] = ImmConst2;
    ImmConstArray[2] = ImmConst3;
    ImmConstArray[3] = ImmConst4;
    //--- End Early Main ---
    //Instruction 0
    //MOV
    Temp[0].xyz = ImmConst1.xyz;
    //Instruction 1
    //MAD
    Temp[1] = GlobalsPS.rcpFrame.xyxy * Temp[0].xyyx + TexCoord1.xyxy;
    //Instruction 2
    //MUL
    Temp[2] = Temp[1].xyxx * ImmConst1.zzxx;
    //Instruction 3
    //SAMPLE_L
    Temp[2] = textureLod(g_samScene, Temp[2].xy, Temp[2].w);
    //Instruction 4
    //MUL
    Temp[1] = Temp[1].zwxx * ImmConst1.zzxx;
    //Instruction 5
    //SAMPLE_L
    Temp[1] = textureLod(g_samScene, Temp[1].xy, Temp[1].w);
    //Instruction 6
    //MUL
    Temp[3] = ImmConst1.zzxx * TexCoord1.xyxx;
    //Instruction 7
    //SAMPLE_L
    Temp[3] = textureLod(g_samScene, Temp[3].xy, Temp[3].w);
    //Instruction 8
    //MAD
    Temp[4] = GlobalsPS.rcpFrame.xyxy * Temp[0].zxxz + TexCoord1.xyxy;
    //Instruction 9
    //MUL
    Temp[5] = Temp[4].xyxx * ImmConst1.zzxx;
    //Instruction 10
    //SAMPLE_L
    Temp[5] = textureLod(g_samScene, Temp[5].xy, Temp[5].w);
    //Instruction 11
    //MUL
    Temp[4] = Temp[4].zwxx * ImmConst1.zzxx;
    //Instruction 12
    //SAMPLE_L
    Temp[4] = textureLod(g_samScene, Temp[4].xy, Temp[4].w);
    //Instruction 13
    //MAD
    Temp[0].w = Temp[2].y * ImmConst1.w + Temp[2].x;
    //Instruction 14
    //MAD
    Temp[1].w = Temp[1].y * ImmConst1.w + Temp[1].x;
    //Instruction 15
    //MAD
    Temp[2].w = Temp[3].y * ImmConst1.w + Temp[3].x;
    //Instruction 16
    //MAD
    Temp[3].w = Temp[5].y * ImmConst1.w + Temp[5].x;
    //Instruction 17
    //MAD
    Temp[4].w = Temp[4].y * ImmConst1.w + Temp[4].x;
    //Instruction 18
    //MIN
    Temp[5].w = min(Temp[1].w, Temp[0].w);
    //Instruction 19
    //MIN
    Temp[6].x = min(Temp[3].w, Temp[4].w);
    //Instruction 20
    //MIN
    Temp[7].x = min(Temp[6].x, Temp[5].w);
    //Instruction 21
    //MIN
    Temp[5].w = min(Temp[7].x, Temp[2].w);
    //Instruction 22
    //MAX
    Temp[6].x = max(Temp[0].w, Temp[1].w);
    //Instruction 23
    //MAX
    Temp[6].y = max(Temp[4].w, Temp[3].w);
    //Instruction 24
    //MAX
    Temp[7].x = max(Temp[6].x, Temp[6].y);
    //Instruction 25
    //MAX
    Temp[6].x = max(Temp[2].w, Temp[7].x);
    //Instruction 26
    //ADD
    Temp[5].w = (-Temp[5].w) + Temp[6].x;
    //Instruction 27
    //MUL
    Temp[6].x = Temp[6].x * ImmConst2.x;
    //Instruction 28
    //MIN
    Temp[7].x = min((-Temp[6].x), ImmConst2.y);
    //Instruction 29
    //IF
    if(Temp[5].w < (-Temp[7].x)){
        //Instruction 30
    //ELSE
    } else {
        //Instruction 31
        //ADD
        Temp[1].xyz = Temp[1].xyz + Temp[2].xyz;
        //Instruction 32
        //ADD
        Temp[1].xyz = Temp[3].xyz + Temp[1].xyz;
        //Instruction 33
        //ADD
        Temp[1].xyz = Temp[5].xyz + Temp[1].xyz;
        //Instruction 34
        //ADD
        Temp[1].xyz = Temp[4].xyz + Temp[1].xyz;
        //Instruction 35
        //ADD
        Temp[2].x = Temp[0].w + Temp[1].w;
        //Instruction 36
        //ADD
        Temp[2].x = Temp[3].w + Temp[2].x;
        //Instruction 37
        //ADD
        Temp[2].x = Temp[4].w + Temp[2].x;
        //Instruction 38
        //MAD
        Temp[2].x = Temp[2].x * ImmConst2.z + (-Temp[2].w);
        //Instruction 39
        //RCP
        Temp[2].y = (vec4(1.0) / vec4(Temp[5].w)).x;
        //Instruction 40
        //MAD
        Temp[2].x = abs(Temp[2].x) * Temp[2].y + ImmConst2.w;
        //Instruction 41
        //MUL
        Temp[2].y = Temp[2].x * ImmConst3.x;
        //Instruction 42
        //MOVC
        Temp[2].x = (Temp[2].x >= 0) ? Temp[2].y : ImmConst1.x;
        //Instruction 43
        //MIN
        Temp[4].x = min(Temp[2].x, ImmConst3.y);
        //Instruction 44
        //ADD
        Temp[5].xy = (-GlobalsPS.rcpFrame.xy) + TexCoord1.xy;
        //Instruction 45
        //MOV
        Temp[5].zw = vec2(ImmConst1.x);
        //Instruction 46
        //SAMPLE_L
        Temp[5] = textureLod(g_samScene, Temp[5].xy, Temp[5].w);
        //Instruction 47
        //MAD
        Temp[6] = GlobalsPS.rcpFrame.xyxy * Temp[0].zyyz + TexCoord1.xyxy;
        //Instruction 48
        //MUL
        Temp[7] = Temp[6].xyxx * ImmConst1.zzxx;
        //Instruction 49
        //SAMPLE_L
        Temp[7] = textureLod(g_samScene, Temp[7].xy, Temp[7].w);
        //Instruction 50
        //MUL
        Temp[6] = Temp[6].zwxx * ImmConst1.zzxx;
        //Instruction 51
        //SAMPLE_L
        Temp[6] = textureLod(g_samScene, Temp[6].xy, Temp[6].w);
        //Instruction 52
        //ADD
        Temp[8].xy = GlobalsPS.rcpFrame.xy + TexCoord1.xy;
        //Instruction 53
        //MOV
        Temp[8].zw = vec2(ImmConst1.x);
        //Instruction 54
        //SAMPLE_L
        Temp[8] = textureLod(g_samScene, Temp[8].xy, Temp[8].w);
        //Instruction 55
        //ADD
        Temp[2].xyz = Temp[5].xyz + Temp[7].xyz;
        //Instruction 56
        //ADD
        Temp[2].xyz = Temp[6].xyz + Temp[2].xyz;
        //Instruction 57
        //ADD
        Temp[2].xyz = Temp[8].xyz + Temp[2].xyz;
        //Instruction 58
        //ADD
        Temp[1].xyz = Temp[1].xyz + Temp[2].xyz;
        //Instruction 59
        //MUL
        Temp[1].xyz = Temp[4].x * Temp[1].xyz;
        //Instruction 60
        //MAD
        Temp[0].y = Temp[5].y * ImmConst1.w + Temp[5].x;
        //Instruction 61
        //MAD
        Temp[2].x = Temp[7].y * ImmConst1.w + Temp[7].x;
        //Instruction 62
        //MAD
        Temp[2].y = Temp[6].y * ImmConst1.w + Temp[6].x;
        //Instruction 63
        //MAD
        Temp[2].z = Temp[8].y * ImmConst1.w + Temp[8].x;
        //Instruction 64
        //MUL
        Temp[4].y = Temp[0].w * ImmConst3.z;
        //Instruction 65
        //MAD
        Temp[4].y = Temp[0].y * ImmConst2.z + Temp[4].y;
        //Instruction 66
        //MAD
        Temp[4].y = Temp[2].x * ImmConst2.z + Temp[4].y;
        //Instruction 67
        //MUL
        Temp[4].z = Temp[1].w * ImmConst3.z;
        //Instruction 68
        //MAD
        Temp[5].x = Temp[1].w * ImmConst3.w + (-Temp[2].w);
        //Instruction 69
        //MUL
        Temp[5].y = Temp[3].w * ImmConst3.z;
        //Instruction 70
        //MAD
        Temp[5].x = Temp[3].w * ImmConst3.w + Temp[5].x;
        //Instruction 71
        //ADD
        Temp[4].y = abs(Temp[4].y) + abs(Temp[5].x);
        //Instruction 72
        //MUL
        Temp[5].x = Temp[4].w * ImmConst3.z;
        //Instruction 73
        //MAD
        Temp[5].x = Temp[2].y * ImmConst2.z + Temp[5].x;
        //Instruction 74
        //MAD
        Temp[5].x = Temp[2].z * ImmConst2.z + Temp[5].x;
        //Instruction 75
        //ADD
        Temp[4].y = Temp[4].y + abs(Temp[5].x);
        //Instruction 76
        //MAD
        Temp[0].y = Temp[0].y * ImmConst2.z + Temp[4].z;
        //Instruction 77
        //MAD
        Temp[0].y = Temp[2].y * ImmConst2.z + Temp[0].y;
        //Instruction 78
        //MAD
        Temp[2].y = Temp[0].w * ImmConst3.w + (-Temp[2].w);
        //Instruction 79
        //MAD
        Temp[2].y = Temp[4].w * ImmConst3.w + Temp[2].y;
        //Instruction 80
        //ADD
        Temp[0].y = abs(Temp[0].y) + abs(Temp[2].y);
        //Instruction 81
        //MAD
        Temp[2].x = Temp[2].x * ImmConst2.z + Temp[5].y;
        //Instruction 82
        //MAD
        Temp[2].x = Temp[2].z * ImmConst2.z + Temp[2].x;
        //Instruction 83
        //ADD
        Temp[0].y = Temp[0].y + abs(Temp[2].x);
        //Instruction 84
        //ADD
        Temp[0].y = (-Temp[4].y) + Temp[0].y;
        //Instruction 85
        //MOVC
        Temp[2].x = (Temp[0].y >= 0) ? (-GlobalsPS.rcpFrame.y) : (-GlobalsPS.rcpFrame.x);
        //Instruction 86
        //MOVC
        Temp[0].w = (Temp[0].y >= 0) ? Temp[0].w : Temp[1].w;
        //Instruction 87
        //MOVC
        Temp[1].w = (Temp[0].y >= 0) ? Temp[4].w : Temp[3].w;
        //Instruction 88
        //ADD
        Temp[2].y = (-Temp[2].w) + Temp[0].w;
        //Instruction 89
        //ADD
        Temp[2].z = (-Temp[2].w) + Temp[1].w;
        //Instruction 90
        //ADD
        Temp[0].w = Temp[2].w + Temp[0].w;
        //Instruction 91
        //MUL
        Temp[0].w = Temp[0].w * ImmConst3.w;
        //Instruction 92
        //ADD
        Temp[1].w = Temp[2].w + Temp[1].w;
        //Instruction 93
        //MUL
        Temp[1].w = Temp[1].w * ImmConst3.w;
        //Instruction 94
        //ADD
        Temp[3].w = -abs(Temp[2].z) + abs(Temp[2].y);
        //Instruction 95
        //MOVC
        Temp[0].w = (Temp[3].w >= 0) ? Temp[0].w : Temp[1].w;
        //Instruction 96
        //MAX
        Temp[1].w = max(abs(Temp[2].y), abs(Temp[2].z));
        //Instruction 97
        //MOVC
        Temp[2].x = (Temp[3].w >= 0) ? Temp[2].x : (-Temp[2].x);
        //Instruction 98
        //MUL
        Temp[2].y = Temp[2].x * ImmConst3.w;
        //Instruction 99
        //MOVC
        Temp[2].z = (Temp[0].y >= 0) ? ImmConst1.x : Temp[2].y;
        //Instruction 100
        //MOVC
        Temp[2].y = (Temp[0].y >= 0) ? Temp[2].y : ImmConst1.x;
        //Instruction 101
        //ADD
        Temp[5].xy = Temp[2].zy + TexCoord1.xy;
        //Instruction 102
        //MUL
        Temp[6] = Temp[0].zxxz * GlobalsPS.rcpFrame.xxxy;
        //Instruction 103
        //MOVC
        Temp[0].xz = (Temp[0].y >= 0) ? Temp[6].xy : Temp[6].zw;
        //Instruction 104
        //ADD
        Temp[2].yz = (-Temp[0].xz) + Temp[5].xy;
        //Instruction 105
        //ADD
        Temp[4].yz = Temp[0].xz + Temp[5].xy;
        //Instruction 106
        //MOV
        Temp[5].xy = Temp[2].yz;
        //Instruction 107
        //MOV
        Temp[5].zw = Temp[4].yz;
        //Instruction 108
        //MOV
        Temp[3].w = Temp[0].w;
        //Instruction 109
        //MOV
        Temp[4].w = Temp[0].w;
        //Instruction 110
        //MOV
        Temp[6].xy = vec2(ImmConst1.x);
        //Instruction 111
        //REP
        RepCounter = int(IntImmConst0.x);
        while(RepCounter!=0){
            //Instruction 112
            //IF
            if(Temp[6].x != (-Temp[6].x)){
                //Instruction 113
                //MOV
                Temp[6].z = Temp[3].w;
                //Instruction 114
            //ELSE
            } else {
                //Instruction 115
                //MUL
                Temp[7] = Temp[5].xyxx * ImmConst1.zzxx;
                //Instruction 116
                //SAMPLE_L
                Temp[7] = textureLod(g_samScene, Temp[7].xy, Temp[7].w);
                //Instruction 117
                //MAD
                Temp[6].z = Temp[7].y * ImmConst1.w + Temp[7].x;
                //Instruction 118
            //ENDIF
            }
            //Instruction 119
            //IF
            if(Temp[6].y != (-Temp[6].y)){
                //Instruction 120
                //MOV
                Temp[6].w = Temp[4].w;
                //Instruction 121
            //ELSE
            } else {
                //Instruction 122
                //MUL
                Temp[7] = Temp[5].zwzz * ImmConst1.zzxx;
                //Instruction 123
                //SAMPLE_L
                Temp[7] = textureLod(g_samScene, Temp[7].xy, Temp[7].w);
                //Instruction 124
                //MAD
                Temp[6].w = Temp[7].y * ImmConst1.w + Temp[7].x;
                //Instruction 125
            //ENDIF
            }
            //Instruction 126
            //ADD
            Temp[7].xy = (-Temp[0].w) + Temp[6].zw;
            //Instruction 127
            //MAD
            Temp[7].x = Temp[1].w * (-ImmConst2.z) + abs(Temp[7].x);
            //Instruction 128
            //MOVC
            Temp[7].x = (Temp[7].x >= 0) ? ImmConst1.z : ImmConst1.x;
            //Instruction 129
            //MAD
            Temp[7].y = Temp[1].w * (-ImmConst2.z) + abs(Temp[7].y);
            //Instruction 130
            //MOVC
            Temp[7].y = (Temp[7].y >= 0) ? ImmConst1.z : ImmConst1.x;
            //Instruction 131
            //ADD
            Temp[7].xy = Temp[6].xy + Temp[7].xy;
            //Instruction 132
            //MOVC
            Temp[6].x = ((-Temp[7].x) >= 0) ? ImmConst1.x : ImmConst1.z;
            Temp[6].y = ((-Temp[7].y) >= 0) ? ImmConst1.x : ImmConst1.z;
            //Instruction 133
            //MUL
            Temp[7].z = Temp[6].y * Temp[6].x;
            //Instruction 134
            //IF
            if(Temp[7].z != (-Temp[7].z)){
                //Instruction 135
                //MOV
                Temp[3].w = Temp[6].z;
                //Instruction 136
                //MOV
                Temp[4].w = Temp[6].w;
                //Instruction 137
                //BREAKC
                if(ImmConst1.z != (-ImmConst1.z)){ break; }
                //Instruction 138
            //ENDIF
            }
            //Instruction 139
            //ADD
            Temp[7].zw = (-Temp[0].xz) + Temp[5].xy;
            //Instruction 140
            //MOVC
            Temp[5].xy = ((-Temp[7].x) >= 0) ? Temp[7].zw : Temp[5].xy;
            //Instruction 141
            //ADD
            Temp[7].xz = Temp[0].xz + Temp[5].zw;
            //Instruction 142
            //MOVC
            Temp[5].zw = ((-Temp[7].y) >= 0) ? Temp[7].xz : Temp[5].zw;
            //Instruction 143
            //MOV
            Temp[3].w = Temp[6].z;
            //Instruction 144
            //MOV
            Temp[4].w = Temp[6].w;
            //Instruction 145
            //ENDREP
            RepCounter--;
        }
        //Instruction 146
        //ADD
        Temp[0].xz = (-Temp[5].xy) + TexCoord1.xy;
        //Instruction 147
        //MOVC
        Temp[0].x = (Temp[0].y >= 0) ? Temp[0].x : Temp[0].z;
        //Instruction 148
        //ADD
        Temp[2].yz = Temp[5].zw + (-TexCoord1.xy);
        //Instruction 149
        //MOVC
        Temp[0].z = (Temp[0].y >= 0) ? Temp[2].y : Temp[2].z;
        //Instruction 150
        //ADD
        Temp[1].w = (-Temp[0].z) + Temp[0].x;
        //Instruction 151
        //MOVC
        Temp[1].w = (Temp[1].w >= 0) ? Temp[4].w : Temp[3].w;
        //Instruction 152
        //ADD
        Temp[2].y = (-Temp[0].w) + Temp[2].w;
        //Instruction 153
        //MOVC
        Temp[2].y = (Temp[2].y >= 0) ? ImmConst1.x : ImmConst1.z;
        //Instruction 154
        //ADD
        Temp[0].w = (-Temp[0].w) + Temp[1].w;
        //Instruction 155
        //MOVC
        Temp[0].w = (Temp[0].w >= 0) ? (-ImmConst1.x) : (-ImmConst1.z);
        //Instruction 156
        //ADD
        Temp[0].w = Temp[0].w + Temp[2].y;
        //Instruction 157
        //MOVC
        Temp[0].w = (-abs(Temp[0].w) >= 0) ? ImmConst1.x : Temp[2].x;
        //Instruction 158
        //ADD
        Temp[1].w = Temp[0].x + Temp[0].z;
        //Instruction 159
        //MIN
        Temp[2].x = min(Temp[0].z, Temp[0].x);
        //Instruction 160
        //RCP
        Temp[0].x = (vec4(1.0) / vec4(Temp[1].w)).x;
        //Instruction 161
        //MAD
        Temp[0].x = Temp[2].x * (-Temp[0].x) + ImmConst3.w;
        //Instruction 162
        //MUL
        Temp[0].x = Temp[0].w * Temp[0].x;
        //Instruction 163
        //MOVC
        Temp[0].z = (Temp[0].y >= 0) ? ImmConst1.x : Temp[0].x;
        //Instruction 164
        //MOVC
        Temp[0].x = (Temp[0].y >= 0) ? Temp[0].x : ImmConst1.x;
        //Instruction 165
        //ADD
        Temp[2].xy = Temp[0].zx + TexCoord1.xy;
        //Instruction 166
        //MOV
        Temp[2].zw = vec2(ImmConst1.x);
        //Instruction 167
        //SAMPLE_L
        Temp[0] = textureLod(g_samScene, Temp[2].xy, Temp[2].w);
        //Instruction 168
        //MAD
        Temp[1].xyz = Temp[1].xyz * ImmConst4.y + Temp[0].xyz;
        //Instruction 169
        //MAD
        Temp[3].xyz = (-Temp[4].x) * Temp[0].xyz + Temp[1].xyz;
        //Instruction 170
    //ENDIF
    }
    //Instruction 171
    //MOV
    Output0.xyz = Temp[3].xyz;
    //Instruction 172
    //MOV
    Output0.w = ImmConst1.z;
    //Instruction 173
    //RET
    return;
}
