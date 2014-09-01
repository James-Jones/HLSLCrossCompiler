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
uniform struct cb0GS_Type {
	mat4 g_mWorldViewProj;
	float g_fGlobalTime;
	float g_fUndulate;
	vec4 vMaterialSpec;
	vec4 vMaterialDiff;
} cb0GS;
uniform struct cbUIUpdatesGS_Type {
	float g_fLifeSpan;
	float g_fLifeSpanVar;
	float g_fRadiusMin;
	float g_fRadiusMax;
	float g_fGrowTime;
	float g_fStepSize;
	float g_fTurnRate;
	float g_fTurnSpeed;
	float g_fLeafRate;
	float g_fShrinkTime;
	uint g_uMaxFaces;
} cbUIUpdatesGS;
uniform sampler1D g_txRandom_X_g_samPoint;
uniform sampler1D g_txRandom;
uniform samplerBuffer g_adjBuffer;
uniform samplerBuffer g_triCenterBuffer;
in  vec4 VtxOutput0 [1];
vec4 Input0[1];
in  vec4 VtxOutput1 [1];
vec4 Input1[1];
in  vec4 VtxOutput2 [1];
vec4 Input2[1];
in  vec4 VtxOutput3 [1];
vec4 Input3[1];
in  vec4 VtxOutput4 [1];
vec4 Input4[1];
in  uvec4 VtxOutput5 [1];
uvec4 Input5[1];
vec4 Temp[11];
ivec4 Temp_int[11];
uvec4 Temp_uint[11];
layout(points) in;
layout(points) out;
out vec4 VtxGeoOutput0;
#define Output0 VtxGeoOutput0
out vec4 VtxGeoOutput1;
#define Output1 VtxGeoOutput1
out vec4 VtxGeoOutput2;
#define Output2 VtxGeoOutput2
out vec4 VtxGeoOutput3;
#define Output3 VtxGeoOutput3
out vec4 VtxGeoOutput4;
#define Output4 VtxGeoOutput4
out uvec4 VtxGeoOutput5;
#define Output5 VtxGeoOutput5
layout(max_vertices = 2) out;
void main()
{
    //--- Start Early Main ---
    Input1[0] = VtxOutput1[0];
    Input2[0] = VtxOutput2[0];
    Input3[0] = VtxOutput3[0];
    Input3[0] = VtxOutput3[0];
    Input4[0] = VtxOutput4[0];
    Input5[0] = VtxOutput5[0];
    Input5[0] = VtxOutput5[0];
    //--- End Early Main ---
    //Instruction 0
    //EQ
    Temp[0].x = uintBitsToFloat(((0.000000)== (Input3[0].y)) ? 0xFFFFFFFFu : 0u);
    //Instruction 1
    //IF
    if((floatBitsToUint(Temp[0].x))!=0u){
        //Instruction 2
        //EQ
        Temp[0].x = uintBitsToFloat(((0.000000)== (Input3[0].x)) ? 0xFFFFFFFFu : 0u);
        //Instruction 3
        //IF
        if((floatBitsToUint(Temp[0].x))!=0u){
            //Instruction 4
            //ISHL
            Temp[0].x = uintBitsToFloat(Input5[0].x << 1u);
            //Instruction 5
            //LD
            Temp[1] = (texelFetch(g_triCenterBuffer, int((ivec4(Temp[0]).xxxx).x)));
            //Instruction 6
            //IADD
            Temp[0].x = intBitsToFloat(floatBitsToInt(Temp[0].x) + int(0x1));
            //Instruction 7
            //LD
            Temp[0] = (texelFetch(g_triCenterBuffer, int((ivec4(Temp[0]).xxxx).x)));
            //Instruction 8
            //UTOF
            Temp[0].w = (float(Input5[0].x));
            //Instruction 9
            //ADD
            Temp[0].w = (Temp[0].w + cb0GS.g_fGlobalTime);
            //Instruction 10
            //MUL
            Temp[0].w = (Temp[0].w * 0.000977);
            //Instruction 11
            //SAMPLE_L
            Temp[2] = (textureLod(g_txRandom_X_g_samPoint, Temp[0].w, 0.000000));
            //Instruction 12
            //DP3
            Temp[0].w = (vec4(dot((Temp[2].xyzx).xyz, (Temp[2].xyzx).xyz)).w);
            //Instruction 13
            //RSQ
            Temp[0].w = (vec4(inversesqrt(Temp[0].w)).w);
            //Instruction 14
            //MUL
            Temp[2].xyz = (Temp[0].wwww * Temp[2].xyzx).xyz;
            //Instruction 15
            //MUL
            Temp[3].xyz = (Temp[0].zxyz * Temp[2].xyzx).xyz;
            //Instruction 16
            //MAD
            Temp[2].xyz = (vec4(Temp[2].zxyz * Temp[0].xyzx + -Temp[3].xyzx)).xyz;
            //Instruction 17
            //MUL
            Temp[3].xyz = (Temp[0].zxyz * Temp[2].xyzx).xyz;
            //Instruction 18
            //MAD
            Temp[2].xyz = (vec4(Temp[0].yzxy * Temp[2].yzxy + -Temp[3].xyzx)).xyz;
            //Instruction 19
            //DP3
            Temp[0].w = (vec4(dot((Temp[2].xyzx).xyz, (Temp[2].xyzx).xyz)).w);
            //Instruction 20
            //RSQ
            Temp[0].w = (vec4(inversesqrt(Temp[0].w)).w);
            //Instruction 21
            //MUL
            Temp[2].xyz = (Temp[0].wwww * Temp[2].xyzx).xyz;
            //Instruction 22
            //IADD
            Temp[0].w = intBitsToFloat(int(0x64) + int(ivec4(Input5[0]).x));
            //Instruction 23
            //UTOF
            Temp[0].w = (float(floatBitsToUint(Temp[0].w)));
            //Instruction 24
            //ADD
            Temp[0].w = (Temp[0].w + cb0GS.g_fGlobalTime);
            //Instruction 25
            //MUL
            Temp[0].w = (Temp[0].w * 0.000977);
            //Instruction 26
            //SAMPLE_L
            Temp[3] = (textureLod(g_txRandom_X_g_samPoint, Temp[0].w, 0.000000));
            //Instruction 27
            //DP3
            Temp[0].w = (vec4(dot((Temp[3].xyzx).xyz, (Temp[3].xyzx).xyz)).w);
            //Instruction 28
            //RSQ
            Temp[0].w = (vec4(inversesqrt(Temp[0].w)).w);
            //Instruction 29
            //MUL
            Temp[0].w = (Temp[0].w * Temp[3].x);
            //Instruction 30
            //MUL
            Temp[0].w = (Temp[0].w * 10.000000);
            //Instruction 31
            //MOV
            Temp[3].z = vec4(-Temp[0].w).z;
            //Instruction 32
            //MOV
            Temp[4].xyz = vec4(Temp[1].xyzx).xyz;
            //Instruction 33
            //ADD
            Temp[3].x = (cbUIUpdatesGS.g_fLifeSpan + 1.000000);
            //Instruction 34
            //MOV
            Temp[3].y = vec4(intBitsToFloat(int(0x3F800000))).y;
            //Instruction 35
        //ELSE
        } else {
            //Instruction 36
            //MOV
            Temp[4].xyz = vec4(gl_in[0].gl_Position.xyzx).xyz;
            //Instruction 37
            //MOV
            Temp[0].xyz = vec4(Input1[0].xyzx).xyz;
            //Instruction 38
            //MOV
            Temp[2].xyz = vec4(Input2[0].xyzx).xyz;
            //Instruction 39
            //ADD
            Temp[3].xz = (vec4(-1.000000, 0.000000, 0.000000, 0.000000) + Input3[0].xxzx).xz;
            //Instruction 40
            //MOV
            Temp[3].y = vec4(intBitsToFloat(int(0x0))).y;
            //Instruction 41
            //MOV
            Temp[1].xyz = vec4(Input4[0].xyzx).xyz;
            //Instruction 42
        //ENDIF
        }
        //Instruction 43
        //MOV
        Output0.xyz = vec4(Temp[4].xyzx).xyz;
        //Instruction 44
        //MOV
        Output1.xyz = vec4(Temp[0].xyzx).xyz;
        //Instruction 45
        //MOV
        Output2.xyz = vec4(Temp[2].xyzx).xyz;
        //Instruction 46
        //MOV
        Output3.xyz = vec4(Temp[3].xyzx).xyz;
        //Instruction 47
        //MOV
        Output4.xyz = vec4(Temp[1].xyzx).xyz;
        //Instruction 48
        //MOV
        Output5.xy = uvec4(ivec4(Input5[0].xyxx)).xy;
        //Instruction 49
        //EMIT
        EmitVertex();
        //Instruction 50
    //ELSE
    } else {
        //Instruction 51
        //EQ
        Temp[0].x = uintBitsToFloat(((1.000000)== (Input3[0].y)) ? 0xFFFFFFFFu : 0u);
        //Instruction 52
        //IF
        if((floatBitsToUint(Temp[0].x))!=0u){
            //Instruction 53
            //ADD
            Temp[0].xyz = (gl_in[0].gl_Position.xyzx + -Input4[0].xyzx).xyz;
            //Instruction 54
            //DP3
            Temp[0].x = (vec4(dot((Temp[0].xyzx).xyz, (Temp[0].xyzx).xyz)).x);
            //Instruction 55
            //SQRT
            Temp[0].x = (vec4(sqrt(Temp[0].x)).x);
            //Instruction 56
            //LT
            Temp[0].x = uintBitsToFloat(((Temp[0].x)< (cbUIUpdatesGS.g_fStepSize)) ? 0xFFFFFFFFu : 0u);
            //Instruction 57
            //IF
            if((floatBitsToUint(Temp[0].x))!=0u){
                //Instruction 58
                //IMUL
                Temp[0].x = intBitsToFloat(int(0x3) * int(ivec4(Input5[0]).x));
                //Instruction 59
                //LD
                Temp[0] = (texelFetch(g_adjBuffer, int((ivec4(Temp[0]).xxxx).x)));
                //Instruction 60
                //IMAD
                Temp[0].yz = intBitsToFloat(ivec4(ivec4(Input5[0]).xxxx * ivec4(int(0x0), int(0x3), int(0x3), int(0x0)) + ivec4(int(0x0), int(0x1), int(0x2), int(0x0)))).yz;
                //Instruction 61
                //LD
                Temp[1] = (texelFetch(g_adjBuffer, int((ivec4(Temp[0]).yyyy).x)));
                //Instruction 62
                //LD
                Temp[2] = (texelFetch(g_adjBuffer, int((ivec4(Temp[0]).zzzz).x)));
                //Instruction 63
                //ADD
                Temp[0].y = (Temp[0].x + Temp[0].x);
                //Instruction 64
                //FTOI
                Temp[0].y = intBitsToFloat(int(Temp[0].y));
                //MOV
                Temp[0].y = vec4(Temp[0].y).y;
                //Instruction 65
                //LD
                Temp[3] = (texelFetch(g_triCenterBuffer, int((ivec4(Temp[0]).yyyy).x)));
                //Instruction 66
                //MAD
                Temp[0].y = (Temp[0].x * 2.000000 + 1.000000);
                //Instruction 67
                //FTOI
                Temp[0].y = intBitsToFloat(int(Temp[0].y));
                //MOV
                Temp[0].y = vec4(Temp[0].y).y;
                //Instruction 68
                //LD
                Temp[4] = (texelFetch(g_triCenterBuffer, int((ivec4(Temp[0]).yyyy).x)));
                //Instruction 69
                //ADD
                Temp[0].yzw = (Temp[3].xxyz + -Input4[0].xxyz).yzw;
                //Instruction 70
                //ADD
                Temp[1].y = (Temp[1].x + Temp[1].x);
                //Instruction 71
                //FTOI
                Temp[1].y = intBitsToFloat(int(Temp[1].y));
                //MOV
                Temp[1].y = vec4(Temp[1].y).y;
                //Instruction 72
                //LD
                Temp[5] = (texelFetch(g_triCenterBuffer, int((ivec4(Temp[1]).yyyy).x)));
                //Instruction 73
                //MAD
                Temp[1].y = (Temp[1].x * 2.000000 + 1.000000);
                //Instruction 74
                //FTOI
                Temp[1].y = intBitsToFloat(int(Temp[1].y));
                //MOV
                Temp[1].y = vec4(Temp[1].y).y;
                //Instruction 75
                //LD
                Temp[6] = (texelFetch(g_triCenterBuffer, int((ivec4(Temp[1]).yyyy).x)));
                //Instruction 76
                //ADD
                Temp[1].yzw = (Temp[5].xxyz + -Input4[0].xxyz).yzw;
                //Instruction 77
                //ADD
                Temp[2].y = (Temp[2].x + Temp[2].x);
                //Instruction 78
                //FTOI
                Temp[2].y = intBitsToFloat(int(Temp[2].y));
                //MOV
                Temp[2].y = vec4(Temp[2].y).y;
                //Instruction 79
                //LD
                Temp[7] = (texelFetch(g_triCenterBuffer, int((ivec4(Temp[2]).yyyy).x)));
                //Instruction 80
                //MAD
                Temp[2].y = (Temp[2].x * 2.000000 + 1.000000);
                //Instruction 81
                //FTOI
                Temp[2].y = intBitsToFloat(int(Temp[2].y));
                //MOV
                Temp[2].y = vec4(Temp[2].y).y;
                //Instruction 82
                //LD
                Temp[8] = (texelFetch(g_triCenterBuffer, int((ivec4(Temp[2]).yyyy).x)));
                //Instruction 83
                //ADD
                Temp[2].yzw = (Temp[7].xxyz + -Input4[0].xxyz).yzw;
                //Instruction 84
                //UTOF
                Temp[4].w = (float(Input5[0].x));
                //Instruction 85
                //ADD
                Temp[4].w = (Temp[4].w + cb0GS.g_fGlobalTime);
                //Instruction 86
                //MUL
                Temp[4].w = (Temp[4].w * 0.000977);
                //Instruction 87
                //SAMPLE_L
                Temp[9] = (textureLod(g_txRandom_X_g_samPoint, Temp[4].w, 0.000000));
                //Instruction 88
                //DP3
                Temp[4].w = (vec4(dot((Temp[9].xyzx).xyz, (Temp[9].xyzx).xyz)).w);
                //Instruction 89
                //RSQ
                Temp[4].w = (vec4(inversesqrt(Temp[4].w)).w);
                //Instruction 90
                //MUL
                Temp[4].w = (Temp[4].w * Temp[9].x);
                //Instruction 91
                //LT
                Temp[4].w = uintBitsToFloat(((abs(Temp[4].w))< (cbUIUpdatesGS.g_fTurnRate)) ? 0xFFFFFFFFu : 0u);
                //Instruction 92
                //IF
                if((floatBitsToUint(Temp[4].w))!=0u){
                    //Instruction 93
                    //ADD
                    Temp[4].w = (cb0GS.g_fGlobalTime + 15.000000);
                    //Instruction 94
                    //MUL
                    Temp[4].w = (Temp[4].w * 0.000977);
                    //Instruction 95
                    //SAMPLE_L
                    Temp[9] = (textureLod(g_txRandom_X_g_samPoint, Temp[4].w, 0.000000));
                    //Instruction 96
                //ELSE
                } else {
                    //Instruction 97
                    //MOV
                    Temp[9].xyz = vec4(Input2[0].xyzx).xyz;
                    //Instruction 98
                //ENDIF
                }
                //Instruction 99
                //DP3
                Temp[4].w = (vec4(dot((Temp[0].yzwy).xyz, (Temp[0].yzwy).xyz)).w);
                //Instruction 100
                //RSQ
                Temp[4].w = (vec4(inversesqrt(Temp[4].w)).w);
                //Instruction 101
                //MUL
                Temp[0].yzw = (Temp[0].yyzw * Temp[4].wwww).yzw;
                //Instruction 102
                //DP3
                Temp[0].y = (vec4(dot((Temp[9].xyzx).xyz, (Temp[0].yzwy).xyz)).y);
                //Instruction 103
                //DP3
                Temp[0].z = (vec4(dot((Temp[1].yzwy).xyz, (Temp[1].yzwy).xyz)).z);
                //Instruction 104
                //RSQ
                Temp[0].z = (vec4(inversesqrt(Temp[0].z)).z);
                //Instruction 105
                //MUL
                Temp[1].yzw = (Temp[0].zzzz * Temp[1].yyzw).yzw;
                //Instruction 106
                //DP3
                Temp[0].z = (vec4(dot((Temp[9].xyzx).xyz, (Temp[1].yzwy).xyz)).z);
                //Instruction 107
                //DP3
                Temp[0].w = (vec4(dot((Temp[2].yzwy).xyz, (Temp[2].yzwy).xyz)).w);
                //Instruction 108
                //RSQ
                Temp[0].w = (vec4(inversesqrt(Temp[0].w)).w);
                //Instruction 109
                //MUL
                Temp[1].yzw = (Temp[0].wwww * Temp[2].yyzw).yzw;
                //Instruction 110
                //DP3
                Temp[0].w = (vec4(dot((Temp[9].xyzx).xyz, (Temp[1].yzwy).xyz)).w);
                //Instruction 111
                //LT
                Temp[1].y = uintBitsToFloat(((Temp[0].x)< (40000000.000000)) ? 0xFFFFFFFFu : 0u);
                //Instruction 112
                //LT
                Temp[1].z = uintBitsToFloat(((Temp[0].z)< (Temp[0].y)) ? 0xFFFFFFFFu : 0u);
                //Instruction 113
                //AND
                Temp[1].y = uintBitsToFloat(floatBitsToUint(Temp[1].z) & floatBitsToUint(Temp[1].y));
                //Instruction 114
                //MUL
                Temp[2].yzw = (Temp[4].zzxy * Temp[9].xxyz).yzw;
                //Instruction 115
                //MAD
                Temp[2].yzw = (vec4(Temp[9].zzxy * Temp[4].xxyz + -Temp[2].yyzw)).yzw;
                //Instruction 116
                //MUL
                Temp[10].xyz = (Temp[2].yzwy * Temp[4].zxyz).xyz;
                //Instruction 117
                //MAD
                Temp[2].yzw = (vec4(Temp[4].yyzx * Temp[2].zzwy + -Temp[10].xxyz)).yzw;
                //Instruction 118
                //DP3
                Temp[1].z = (vec4(dot((Temp[2].yzwy).xyz, (Temp[2].yzwy).xyz)).z);
                //Instruction 119
                //RSQ
                Temp[1].z = (vec4(inversesqrt(Temp[1].z)).z);
                //Instruction 120
                //MUL
                Temp[2].yzw = (Temp[1].zzzz * Temp[2].yyzw).yzw;
                //Instruction 121
                //FTOU
                Temp[3].w = uintBitsToFloat(uint(Temp[0].x));
                //MOV
                Temp[3].w = vec4(Temp[0].x).w;
                //Instruction 122
                //LT
                Temp[0].x = uintBitsToFloat(((Temp[1].x)< (40000000.000000)) ? 0xFFFFFFFFu : 0u);
                //Instruction 123
                //LT
                Temp[0].y = uintBitsToFloat(((Temp[0].y)< (Temp[0].z)) ? 0xFFFFFFFFu : 0u);
                //Instruction 124
                //AND
                Temp[0].x = uintBitsToFloat(floatBitsToUint(Temp[0].y) & floatBitsToUint(Temp[0].x));
                //Instruction 125
                //LT
                Temp[0].y = uintBitsToFloat(((Temp[0].w)< (Temp[0].z)) ? 0xFFFFFFFFu : 0u);
                //Instruction 126
                //AND
                Temp[0].x = uintBitsToFloat(floatBitsToUint(Temp[0].y) & floatBitsToUint(Temp[0].x));
                //Instruction 127
                //MUL
                Temp[0].yzw = (Temp[6].zzxy * Temp[9].xxyz).yzw;
                //Instruction 128
                //MAD
                Temp[0].yzw = (vec4(Temp[9].zzxy * Temp[6].xxyz + -Temp[0].yyzw)).yzw;
                //Instruction 129
                //MUL
                Temp[10].xyz = (Temp[0].yzwy * Temp[6].zxyz).xyz;
                //Instruction 130
                //MAD
                Temp[0].yzw = (vec4(Temp[6].yyzx * Temp[0].zzwy + -Temp[10].xxyz)).yzw;
                //Instruction 131
                //DP3
                Temp[1].z = (vec4(dot((Temp[0].yzwy).xyz, (Temp[0].yzwy).xyz)).z);
                //Instruction 132
                //RSQ
                Temp[1].z = (vec4(inversesqrt(Temp[1].z)).z);
                //Instruction 133
                //MUL
                Temp[0].yzw = (Temp[0].yyzw * Temp[1].zzzz).yzw;
                //Instruction 134
                //FTOU
                Temp[5].w = uintBitsToFloat(uint(Temp[1].x));
                //MOV
                Temp[5].w = vec4(Temp[1].x).w;
                //Instruction 135
                //MUL
                Temp[1].xzw = (Temp[8].zzxy * Temp[9].xxyz).xzw;
                //Instruction 136
                //MAD
                Temp[1].xzw = (vec4(Temp[9].zzxy * Temp[8].xxyz + -Temp[1].xxzw)).xzw;
                //Instruction 137
                //MUL
                Temp[9].xyz = (Temp[1].xzwx * Temp[8].zxyz).xyz;
                //Instruction 138
                //MAD
                Temp[1].xzw = (vec4(Temp[8].yyzx * Temp[1].zzwx + -Temp[9].xxyz)).xzw;
                //Instruction 139
                //DP3
                Temp[4].w = (vec4(dot((Temp[1].xzwx).xyz, (Temp[1].xzwx).xyz)).w);
                //Instruction 140
                //RSQ
                Temp[4].w = (vec4(inversesqrt(Temp[4].w)).w);
                //Instruction 141
                //MUL
                Temp[1].xzw = (Temp[1].xxzw * Temp[4].wwww).xzw;
                //Instruction 142
                //FTOU
                Temp[7].w = uintBitsToFloat(uint(Temp[2].x));
                //MOV
                Temp[7].w = vec4(Temp[2].x).w;
                //Instruction 143
                //MOVC
                if(ivec4(floatBitsToInt(Temp[0].xxxx)).x != 0) {
                    Temp[5] = vec4(Temp[5]).xyzw;
                } else {
                    Temp[5] = vec4(Temp[7]).xyzw;
                }
                //Instruction 144
                //MOVC
                if(ivec4(floatBitsToInt(Temp[0].xxxx)).x != 0) {
                    Temp[6].xyz = vec4(Temp[6].xyzx).xyz;
                } else {
                    Temp[6].xyz = vec4(Temp[8].xyzx).xyz;
                }
                //Instruction 145
                //MOVC
                if(ivec4(floatBitsToInt(Temp[0].xxxx)).x != 0) {
                    Temp[0].xyz = vec4(Temp[0].yzwy).xyz;
                } else {
                    Temp[0].xyz = vec4(Temp[1].xzwx).xyz;
                }
                //Instruction 146
                //MOVC
                if(ivec4(floatBitsToInt(Temp[1].yyyy)).x != 0) {
                    Temp[1].xzw = vec4(Temp[4].xxyz).xzw;
                } else {
                    Temp[1].xzw = vec4(Temp[6].xxyz).xzw;
                }
                //Instruction 147
                //MOVC
                if(ivec4(floatBitsToInt(Temp[1].yyyy)).x != 0) {
                    Temp[0].xyz = vec4(Temp[2].yzwy).xyz;
                } else {
                    Temp[0].xyz = vec4(Temp[0].xyzx).xyz;
                }
                //Instruction 148
                //MOVC
                if(ivec4(floatBitsToInt(Temp[1].yyyy)).x != 0) {
                    Temp[2] = vec4(Temp[3]).xyzw;
                } else {
                    Temp[2] = vec4(Temp[5]).xyzw;
                }
                //Instruction 149
                //MOV
                Output0.xyz = vec4(Input4[0].xyzx).xyz;
                //Instruction 150
                //MOV
                Output1.xyz = vec4(Temp[1].xzwx).xyz;
                //Instruction 151
                //MOV
                Output2.xyz = vec4(Temp[0].xyzx).xyz;
                //Instruction 152
                //MOV
                Output3.xz = vec4(Input3[0].xxzx).xz;
                //Instruction 153
                //MOV
                Output3.y = vec4(intBitsToFloat(int(0x3F800000))).y;
                //Instruction 154
                //MOV
                Output4.xyz = vec4(Temp[2].xyzx).xyz;
                //Instruction 155
                //MOV
                Output5.x = uvec4(floatBitsToInt(Temp[2].w)).x;
                //Instruction 156
                //MOV
                Output5.y = uvec4(int(Input5[0].y)).y;
                //Instruction 157
                //EMIT
                EmitVertex();
                //Instruction 158
            //ELSE
            } else {
                //Instruction 159
                //ADD
                Temp[0].xyz = (-gl_in[0].gl_Position.xyzx + Input4[0].xyzx).xyz;
                //Instruction 160
                //DP3
                Temp[0].x = (vec4(dot((Temp[0].xyzx).xyz, (Temp[0].xyzx).xyz)).x);
                //Instruction 161
                //SQRT
                Temp[0].x = (vec4(sqrt(Temp[0].x)).x);
                //Instruction 162
                //MAD
                Temp[0].xyz = (vec4(Input2[0].xyzx * Temp[0].xxxx + gl_in[0].gl_Position.xyzx)).xyz;
                //Instruction 163
                //ADD
                Temp[1].xyz = (-Temp[0].xyzx + Input4[0].xyzx).xyz;
                //Instruction 164
                //MAD
                Temp[0].xyz = (vec4(Temp[1].xyzx * vec4(0.500000, 0.500000, 0.500000, 0.000000) + Temp[0].xyzx)).xyz;
                //Instruction 165
                //ADD
                Temp[0].xyz = (Temp[0].xyzx + -gl_in[0].gl_Position.xyzx).xyz;
                //Instruction 166
                //DP3
                Temp[0].w = (vec4(dot((Temp[0].xyzx).xyz, (Temp[0].xyzx).xyz)).w);
                //Instruction 167
                //RSQ
                Temp[0].w = (vec4(inversesqrt(Temp[0].w)).w);
                //Instruction 168
                //MUL
                Temp[0].xyz = (Temp[0].wwww * Temp[0].xyzx).xyz;
                //Instruction 169
                //MAD
                Temp[1].xyz = (vec4(Temp[0].xyzx * cbUIUpdatesGS.g_fStepSize + gl_in[0].gl_Position.xyzx)).xyz;
                //Instruction 170
                //MUL
                Temp[2].xyz = (Temp[0].zxyz * Input1[0].xyzx).xyz;
                //Instruction 171
                //MAD
                Temp[2].xyz = (vec4(Input1[0].zxyz * Temp[0].xyzx + -Temp[2].xyzx)).xyz;
                //Instruction 172
                //MUL
                Temp[3].xyz = (Temp[0].zxyz * Temp[2].xyzx).xyz;
                //Instruction 173
                //MAD
                Temp[2].xyz = (vec4(Temp[0].yzxy * Temp[2].yzxy + -Temp[3].xyzx)).xyz;
                //Instruction 174
                //DP3
                Temp[0].w = (vec4(dot((Temp[2].xyzx).xyz, (Temp[2].xyzx).xyz)).w);
                //Instruction 175
                //RSQ
                Temp[0].w = (vec4(inversesqrt(Temp[0].w)).w);
                //Instruction 176
                //MUL
                Temp[2].xyz = (Temp[0].wwww * Temp[2].xyzx).xyz;
                //Instruction 177
                //UTOF
                Temp[0].w = (float(Input5[0].x));
                //Instruction 178
                //ADD
                Temp[0].w = (Temp[0].w + cb0GS.g_fGlobalTime);
                //Instruction 179
                //MUL
                Temp[0].w = (Temp[0].w * 0.000977);
                //Instruction 180
                //SAMPLE_L
                Temp[3] = (textureLod(g_txRandom_X_g_samPoint, Temp[0].w, 0.000000));
                //Instruction 181
                //DP3
                Temp[0].w = (vec4(dot((Temp[3].xyzx).xyz, (Temp[3].xyzx).xyz)).w);
                //Instruction 182
                //RSQ
                Temp[0].w = (vec4(inversesqrt(Temp[0].w)).w);
                //Instruction 183
                //MUL
                Temp[3].xyz = (Temp[0].wwww * Temp[3].xyzx).xyz;
                //Instruction 184
                //LT
                Temp[0].w = uintBitsToFloat(((abs(Temp[3].x))< (cbUIUpdatesGS.g_fLeafRate)) ? 0xFFFFFFFFu : 0u);
                //Instruction 185
                //MUL
                Temp[1].w = (abs(Temp[3].y) * 2000.000000);
                //Instruction 186
                //FTOU
                Temp[1].w = uintBitsToFloat(uint(Temp[1].w));
                //MOV
                Temp[1].w = vec4(Temp[1].w).w;
                //Instruction 187
                //AND
                Temp[0].w = uintBitsToFloat(floatBitsToUint(Temp[0].w) & floatBitsToUint(Temp[1].w));
                //Instruction 188
                //LT
                Temp[1].w = uintBitsToFloat(((cbUIUpdatesGS.g_fLifeSpan)< (Input3[0].z)) ? 0xFFFFFFFFu : 0u);
                //Instruction 189
                //UTOF
                Temp[2].w = (float(cbUIUpdatesGS.g_uMaxFaces));
                //Instruction 190
                //MUL
                Temp[2].w = (Temp[2].w * abs(Temp[3].z));
                //Instruction 191
                //FTOU
                Temp[3].z = uintBitsToFloat(uint(Temp[2].w));
                //MOV
                Temp[3].z = vec4(Temp[2].w).z;
                //Instruction 192
                //MOV
                Temp[3].xyw = vec4(intBitsToFloat(ivec4(int(0x0), int(0x0), int(0x0), int(0x0)))).xyw;
                //Instruction 193
                //MOV
                Temp[4].x = vec4(cbUIUpdatesGS.g_fLifeSpan).x;
                //Instruction 194
                //MOV
                Temp[4].y = vec4(intBitsToFloat(int(0x3F800000))).y;
                //Instruction 195
                //MOV
                Temp[4].z = vec4(uintBitsToFloat(Input5[0]).x).z;
                //Instruction 196
                //MOV
                Temp[4].w = vec4(Input3[0].z).w;
                //Instruction 197
                //MOVC
                if(ivec4(floatBitsToInt(Temp[1].wwww)).x != 0) {
                    Temp[3] = vec4(Temp[3]).xyzw;
                } else {
                    Temp[3] = vec4(Temp[4]).xyzw;
                }
                //Instruction 198
                //MOV
                Output0.xyz = vec4(Temp[1].xyzx).xyz;
                //Instruction 199
                //MOV
                Output1.xyz = vec4(Temp[2].xyzx).xyz;
                //Instruction 200
                //MOV
                Output2.xyz = vec4(Temp[0].xyzx).xyz;
                //Instruction 201
                //MOV
                Output3.xyz = vec4(Temp[3].xywx).xyz;
                //Instruction 202
                //MOV
                Output4.xyz = vec4(Input4[0].xyzx).xyz;
                //Instruction 203
                //MOV
                Output5.x = uvec4(floatBitsToInt(Temp[3].z)).x;
                //Instruction 204
                //MOV
                Output5.y = uvec4(floatBitsToInt(Temp[0].w)).y;
                //Instruction 205
                //EMIT
                EmitVertex();
                //Instruction 206
            //ENDIF
            }
            //Instruction 207
        //ENDIF
        }
        //Instruction 208
        //ADD
        Temp[0].xy = (vec4(-1.000000, 1.000000, 0.000000, 0.000000) + Input3[0].xzxx).xy;
        //Instruction 209
        //NE
        Temp[0].z = uintBitsToFloat(((Temp[0].x)!= (0.000000)) ? 0xFFFFFFFFu : 0u);
        //Instruction 210
        //LT
        Temp[0].w = uintBitsToFloat(((Temp[0].y)< (cbUIUpdatesGS.g_fLifeSpan)) ? 0xFFFFFFFFu : 0u);
        //Instruction 211
        //AND
        Temp[0].z = uintBitsToFloat(floatBitsToUint(Temp[0].w) & floatBitsToUint(Temp[0].z));
        //Instruction 212
        //IF
        if((floatBitsToUint(Temp[0].z))!=0u){
            //Instruction 213
            //MOV
            Output0.xyz = vec4(gl_in[0].gl_Position.xyzx).xyz;
            //Instruction 214
            //MOV
            Output1.xyz = vec4(Input1[0].xyzx).xyz;
            //Instruction 215
            //MOV
            Output2.xyz = vec4(Input2[0].xyzx).xyz;
            //Instruction 216
            //MOV
            Output3.xz = vec4(Temp[0].xxyx).xz;
            //Instruction 217
            //MOV
            Output3.y = vec4(intBitsToFloat(int(0x40400000))).y;
            //Instruction 218
            //MOV
            Output4.xyz = vec4(Input4[0].xyzx).xyz;
            //Instruction 219
            //MOV
            Output5.xy = uvec4(ivec4(Input5[0].xyxx)).xy;
            //Instruction 220
            //EMIT
            EmitVertex();
            //Instruction 221
        //ENDIF
        }
        //Instruction 222
    //ENDIF
    }
    //Instruction 223
    //RET
    return;
}
