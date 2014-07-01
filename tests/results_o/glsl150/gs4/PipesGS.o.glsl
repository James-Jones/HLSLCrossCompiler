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
uniform struct cb0GS_Type {
	vec4 g_mWorldViewProj[4];
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
    Temp_int[0].x = floatBitsToInt(((0.000000)== (Input3[0].y)) ? int(0xFFFFFFFF) : 0);
    //Instruction 1
    //IF
    if((Temp_int[0].x)!=0){
        //Instruction 2
        //EQ
        Temp_int[0].x = floatBitsToInt(((0.000000)== (Input3[0].x)) ? int(0xFFFFFFFF) : 0);
        //Instruction 3
        //IF
        if((Temp_int[0].x)!=0){
            //Instruction 4
            //ISHL
            Temp_int[0].x = int(Input5[0].x) << int(0x1);
            //Instruction 5
            //LD
            Temp_int[1] = floatBitsToInt(texelFetch(g_triCenterBuffer, int((Temp_int[0].xxxx).x)));
            //Instruction 6
            //IADD
            Temp_int[0].x = (Temp_int[0].x + int(0x1));
            //Instruction 7
            //LD
            Temp_int[0] = floatBitsToInt(texelFetch(g_triCenterBuffer, int((Temp_int[0].xxxx).x)));
            //Instruction 8
            //UTOF
            Temp_int[0].w = floatBitsToInt(vec4(Input5[0].x).w);
            //Instruction 9
            //ADD
            Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + cb0GS.g_fGlobalTime);
            //Instruction 10
            //MUL
            Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.000977);
            //Instruction 11
            //SAMPLE_L
            Temp_int[2] = floatBitsToInt(textureLod(g_txRandom, intBitsToFloat(Temp_int[0]).w, 0.000000));
            //Instruction 12
            //DP3
            Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[2]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
            //Instruction 13
            //RSQ
            Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
            //Instruction 14
            //MUL
            Temp_int[2].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[2]).xyzx).xyz;
            //Instruction 15
            //MUL
            Temp_int[3].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).zxyz * intBitsToFloat(Temp_int[2]).xyzx).xyz;
            //Instruction 16
            //MAD
            Temp_int[2].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[2]).zxyz * intBitsToFloat(Temp_int[0]).xyzx + -intBitsToFloat(Temp_int[3]).xyzx)).xyz;
            //Instruction 17
            //MUL
            Temp_int[3].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).zxyz * intBitsToFloat(Temp_int[2]).xyzx).xyz;
            //Instruction 18
            //MAD
            Temp_int[2].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).yzxy * intBitsToFloat(Temp_int[2]).yzxy + -intBitsToFloat(Temp_int[3]).xyzx)).xyz;
            //Instruction 19
            //DP3
            Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[2]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
            //Instruction 20
            //RSQ
            Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
            //Instruction 21
            //MUL
            Temp_int[2].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[2]).xyzx).xyz;
            //Instruction 22
            //IADD
            Temp_int[0].w = (int(0x64) + ivec4(Input5[0]).x);
            //Instruction 23
            //UTOF
            Temp_int[0].w = floatBitsToInt(vec4(Temp_int[0].w).w);
            //Instruction 24
            //ADD
            Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + cb0GS.g_fGlobalTime);
            //Instruction 25
            //MUL
            Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.000977);
            //Instruction 26
            //SAMPLE_L
            Temp_int[3] = floatBitsToInt(textureLod(g_txRandom, intBitsToFloat(Temp_int[0]).w, 0.000000));
            //Instruction 27
            //DP3
            Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[3]).xyzx).xyz, (intBitsToFloat(Temp_int[3]).xyzx).xyz)).w);
            //Instruction 28
            //RSQ
            Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
            //Instruction 29
            //MUL
            Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * intBitsToFloat(Temp_int[3]).x);
            //Instruction 30
            //MUL
            Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 10.000000);
            //Instruction 31
            //MOV
            Temp_int[3].z = ivec4(-Temp_int[0].w).z;
            //Instruction 32
            //MOV
            Temp_int[4].xyz = ivec4(Temp_int[1].xyzx).xyz;
            //Instruction 33
            //ADD
            Temp_int[3].x = floatBitsToInt(cbUIUpdatesGS.g_fLifeSpan + 1.000000);
            //Instruction 34
            //MOV
            Temp_int[3].y = ivec4(int(0x3F800000)).y;
            //Instruction 35
        //ELSE
        } else {
            //Instruction 36
            //MOV
            Temp_int[4].xyz = ivec4(floatBitsToInt(gl_in[0].gl_Position.xyzx)).xyz;
            //Instruction 37
            //MOV
            Temp_int[0].xyz = ivec4(floatBitsToInt(Input1[0].xyzx)).xyz;
            //Instruction 38
            //MOV
            Temp_int[2].xyz = ivec4(floatBitsToInt(Input2[0].xyzx)).xyz;
            //Instruction 39
            //ADD
            Temp_int[3].xz = floatBitsToInt(vec4(-1.000000, 0.000000, 0.000000, 0.000000) + Input3[0].xxzx).xz;
            //Instruction 40
            //MOV
            Temp_int[3].y = ivec4(int(0x0)).y;
            //Instruction 41
            //MOV
            Temp_int[1].xyz = ivec4(floatBitsToInt(Input4[0].xyzx)).xyz;
            //Instruction 42
        //ENDIF
        }
        //Instruction 43
        //MOV
        Output0.xyz = vec4(intBitsToFloat(Temp_int[4].xyzx)).xyz;
        //Instruction 44
        //MOV
        Output1.xyz = vec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
        //Instruction 45
        //MOV
        Output2.xyz = vec4(intBitsToFloat(Temp_int[2].xyzx)).xyz;
        //Instruction 46
        //MOV
        Output3.xyz = vec4(intBitsToFloat(Temp_int[3].xyzx)).xyz;
        //Instruction 47
        //MOV
        Output4.xyz = vec4(intBitsToFloat(Temp_int[1].xyzx)).xyz;
        //Instruction 48
        //MOV
        Output5.xy = uvec4(Input5[0].xyxx).xy;
        //Instruction 49
        //EMIT
        EmitVertex();
        //Instruction 50
    //ELSE
    } else {
        //Instruction 51
        //EQ
        Temp_int[0].x = floatBitsToInt(((1.000000)== (Input3[0].y)) ? int(0xFFFFFFFF) : 0);
        //Instruction 52
        //IF
        if((Temp_int[0].x)!=0){
            //Instruction 53
            //ADD
            Temp_int[0].xyz = floatBitsToInt(gl_in[0].gl_Position.xyzx + -Input4[0].xyzx).xyz;
            //Instruction 54
            //DP3
            Temp_int[0].x = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).xyzx).xyz, (intBitsToFloat(Temp_int[0]).xyzx).xyz)).x);
            //Instruction 55
            //SQRT
            Temp_int[0].x = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[0]).x)).x);
            //Instruction 56
            //LT
            Temp_int[0].x = floatBitsToInt(((intBitsToFloat(Temp_int[0]).x)< (cbUIUpdatesGS.g_fStepSize)) ? int(0xFFFFFFFF) : 0);
            //Instruction 57
            //IF
            if((Temp_int[0].x)!=0){
                //Instruction 58
                //IMUL
                Temp_int[0].x = (int(0x3) * ivec4(Input5[0]).x);
                //Instruction 59
                //LD
                Temp_int[0] = floatBitsToInt(texelFetch(g_adjBuffer, int((Temp_int[0].xxxx).x)));
                //Instruction 60
                //IMAD
                Temp_int[0].yz = (ivec4(ivec4(Input5[0]).xxxx * ivec4(0x0, 0x3, 0x3, 0x0) + ivec4(0x0, 0x1, 0x2, 0x0))).yz;
                //Instruction 61
                //LD
                Temp_int[1] = floatBitsToInt(texelFetch(g_adjBuffer, int((Temp_int[0].yyyy).x)));
                //Instruction 62
                //LD
                Temp_int[2] = floatBitsToInt(texelFetch(g_adjBuffer, int((Temp_int[0].zzzz).x)));
                //Instruction 63
                //ADD
                Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).x);
                //Instruction 64
                //FTOI
                Temp_int[0].y = int(intBitsToFloat(Temp_int[0].y));
                //Instruction 65
                //LD
                Temp_int[3] = floatBitsToInt(texelFetch(g_triCenterBuffer, int((Temp_int[0].yyyy).x)));
                //Instruction 66
                //MAD
                Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).x * 2.000000 + 1.000000);
                //Instruction 67
                //FTOI
                Temp_int[0].y = int(intBitsToFloat(Temp_int[0].y));
                //Instruction 68
                //LD
                Temp_int[4] = floatBitsToInt(texelFetch(g_triCenterBuffer, int((Temp_int[0].yyyy).x)));
                //Instruction 69
                //ADD
                Temp_int[0].yzw = floatBitsToInt(intBitsToFloat(Temp_int[3]).xxyz + -Input4[0].xxyz).yzw;
                //Instruction 70
                //ADD
                Temp_int[1].y = floatBitsToInt(intBitsToFloat(Temp_int[1]).x + intBitsToFloat(Temp_int[1]).x);
                //Instruction 71
                //FTOI
                Temp_int[1].y = int(intBitsToFloat(Temp_int[1].y));
                //Instruction 72
                //LD
                Temp_int[5] = floatBitsToInt(texelFetch(g_triCenterBuffer, int((Temp_int[1].yyyy).x)));
                //Instruction 73
                //MAD
                Temp_int[1].y = floatBitsToInt(intBitsToFloat(Temp_int[1]).x * 2.000000 + 1.000000);
                //Instruction 74
                //FTOI
                Temp_int[1].y = int(intBitsToFloat(Temp_int[1].y));
                //Instruction 75
                //LD
                Temp_int[6] = floatBitsToInt(texelFetch(g_triCenterBuffer, int((Temp_int[1].yyyy).x)));
                //Instruction 76
                //ADD
                Temp_int[1].yzw = floatBitsToInt(intBitsToFloat(Temp_int[5]).xxyz + -Input4[0].xxyz).yzw;
                //Instruction 77
                //ADD
                Temp_int[2].y = floatBitsToInt(intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[2]).x);
                //Instruction 78
                //FTOI
                Temp_int[2].y = int(intBitsToFloat(Temp_int[2].y));
                //Instruction 79
                //LD
                Temp_int[7] = floatBitsToInt(texelFetch(g_triCenterBuffer, int((Temp_int[2].yyyy).x)));
                //Instruction 80
                //MAD
                Temp_int[2].y = floatBitsToInt(intBitsToFloat(Temp_int[2]).x * 2.000000 + 1.000000);
                //Instruction 81
                //FTOI
                Temp_int[2].y = int(intBitsToFloat(Temp_int[2].y));
                //Instruction 82
                //LD
                Temp_int[8] = floatBitsToInt(texelFetch(g_triCenterBuffer, int((Temp_int[2].yyyy).x)));
                //Instruction 83
                //ADD
                Temp_int[2].yzw = floatBitsToInt(intBitsToFloat(Temp_int[7]).xxyz + -Input4[0].xxyz).yzw;
                //Instruction 84
                //UTOF
                Temp_int[4].w = floatBitsToInt(vec4(Input5[0].x).w);
                //Instruction 85
                //ADD
                Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).w + cb0GS.g_fGlobalTime);
                //Instruction 86
                //MUL
                Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).w * 0.000977);
                //Instruction 87
                //SAMPLE_L
                Temp_int[9] = floatBitsToInt(textureLod(g_txRandom, intBitsToFloat(Temp_int[4]).w, 0.000000));
                //Instruction 88
                //DP3
                Temp_int[4].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[9]).xyzx).xyz, (intBitsToFloat(Temp_int[9]).xyzx).xyz)).w);
                //Instruction 89
                //RSQ
                Temp_int[4].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[4]).w)).w);
                //Instruction 90
                //MUL
                Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).w * intBitsToFloat(Temp_int[9]).x);
                //Instruction 91
                //LT
                Temp_int[4].w = floatBitsToInt(((abs(intBitsToFloat(Temp_int[4]).w))< (cbUIUpdatesGS.g_fTurnRate)) ? int(0xFFFFFFFF) : 0);
                //Instruction 92
                //IF
                if((Temp_int[4].w)!=0){
                    //Instruction 93
                    //ADD
                    Temp_int[4].w = floatBitsToInt(cb0GS.g_fGlobalTime + 15.000000);
                    //Instruction 94
                    //MUL
                    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).w * 0.000977);
                    //Instruction 95
                    //SAMPLE_L
                    Temp_int[9] = floatBitsToInt(textureLod(g_txRandom, intBitsToFloat(Temp_int[4]).w, 0.000000));
                    //Instruction 96
                //ELSE
                } else {
                    //Instruction 97
                    //MOV
                    Temp_int[9].xyz = ivec4(floatBitsToInt(Input2[0].xyzx)).xyz;
                    //Instruction 98
                //ENDIF
                }
                //Instruction 99
                //DP3
                Temp_int[4].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).yzwy).xyz, (intBitsToFloat(Temp_int[0]).yzwy).xyz)).w);
                //Instruction 100
                //RSQ
                Temp_int[4].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[4]).w)).w);
                //Instruction 101
                //MUL
                Temp_int[0].yzw = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyzw * intBitsToFloat(Temp_int[4]).wwww).yzw;
                //Instruction 102
                //DP3
                Temp_int[0].y = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[9]).xyzx).xyz, (intBitsToFloat(Temp_int[0]).yzwy).xyz)).y);
                //Instruction 103
                //DP3
                Temp_int[0].z = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[1]).yzwy).xyz, (intBitsToFloat(Temp_int[1]).yzwy).xyz)).z);
                //Instruction 104
                //RSQ
                Temp_int[0].z = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).z)).z);
                //Instruction 105
                //MUL
                Temp_int[1].yzw = floatBitsToInt(intBitsToFloat(Temp_int[0]).zzzz * intBitsToFloat(Temp_int[1]).yyzw).yzw;
                //Instruction 106
                //DP3
                Temp_int[0].z = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[9]).xyzx).xyz, (intBitsToFloat(Temp_int[1]).yzwy).xyz)).z);
                //Instruction 107
                //DP3
                Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[2]).yzwy).xyz, (intBitsToFloat(Temp_int[2]).yzwy).xyz)).w);
                //Instruction 108
                //RSQ
                Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
                //Instruction 109
                //MUL
                Temp_int[1].yzw = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[2]).yyzw).yzw;
                //Instruction 110
                //DP3
                Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[9]).xyzx).xyz, (intBitsToFloat(Temp_int[1]).yzwy).xyz)).w);
                //Instruction 111
                //LT
                Temp_int[1].y = floatBitsToInt(((intBitsToFloat(Temp_int[0]).x)< (40000000.000000)) ? int(0xFFFFFFFF) : 0);
                //Instruction 112
                //LT
                Temp_int[1].z = floatBitsToInt(((intBitsToFloat(Temp_int[0]).z)< (intBitsToFloat(Temp_int[0]).y)) ? int(0xFFFFFFFF) : 0);
                //Instruction 113
                //AND
                Temp_int[1].y = Temp_int[1].z & Temp_int[1].y;
                //Instruction 114
                //MUL
                Temp_int[2].yzw = floatBitsToInt(intBitsToFloat(Temp_int[4]).zzxy * intBitsToFloat(Temp_int[9]).xxyz).yzw;
                //Instruction 115
                //MAD
                Temp_int[2].yzw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[9]).zzxy * intBitsToFloat(Temp_int[4]).xxyz + -intBitsToFloat(Temp_int[2]).yyzw)).yzw;
                //Instruction 116
                //MUL
                Temp_int[10].xyz = floatBitsToInt(intBitsToFloat(Temp_int[2]).yzwy * intBitsToFloat(Temp_int[4]).zxyz).xyz;
                //Instruction 117
                //MAD
                Temp_int[2].yzw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[4]).yyzx * intBitsToFloat(Temp_int[2]).zzwy + -intBitsToFloat(Temp_int[10]).xxyz)).yzw;
                //Instruction 118
                //DP3
                Temp_int[1].z = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[2]).yzwy).xyz, (intBitsToFloat(Temp_int[2]).yzwy).xyz)).z);
                //Instruction 119
                //RSQ
                Temp_int[1].z = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[1]).z)).z);
                //Instruction 120
                //MUL
                Temp_int[2].yzw = floatBitsToInt(intBitsToFloat(Temp_int[1]).zzzz * intBitsToFloat(Temp_int[2]).yyzw).yzw;
                //Instruction 121
                //FTOU
                Temp_int[3].w = int(intBitsToFloat(Temp_int[0].x));
                //Instruction 122
                //LT
                Temp_int[0].x = floatBitsToInt(((intBitsToFloat(Temp_int[1]).x)< (40000000.000000)) ? int(0xFFFFFFFF) : 0);
                //Instruction 123
                //LT
                Temp_int[0].y = floatBitsToInt(((intBitsToFloat(Temp_int[0]).y)< (intBitsToFloat(Temp_int[0]).z)) ? int(0xFFFFFFFF) : 0);
                //Instruction 124
                //AND
                Temp_int[0].x = Temp_int[0].y & Temp_int[0].x;
                //Instruction 125
                //LT
                Temp_int[0].y = floatBitsToInt(((intBitsToFloat(Temp_int[0]).w)< (intBitsToFloat(Temp_int[0]).z)) ? int(0xFFFFFFFF) : 0);
                //Instruction 126
                //AND
                Temp_int[0].x = Temp_int[0].y & Temp_int[0].x;
                //Instruction 127
                //MUL
                Temp_int[0].yzw = floatBitsToInt(intBitsToFloat(Temp_int[6]).zzxy * intBitsToFloat(Temp_int[9]).xxyz).yzw;
                //Instruction 128
                //MAD
                Temp_int[0].yzw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[9]).zzxy * intBitsToFloat(Temp_int[6]).xxyz + -intBitsToFloat(Temp_int[0]).yyzw)).yzw;
                //Instruction 129
                //MUL
                Temp_int[10].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).yzwy * intBitsToFloat(Temp_int[6]).zxyz).xyz;
                //Instruction 130
                //MAD
                Temp_int[0].yzw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[6]).yyzx * intBitsToFloat(Temp_int[0]).zzwy + -intBitsToFloat(Temp_int[10]).xxyz)).yzw;
                //Instruction 131
                //DP3
                Temp_int[1].z = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).yzwy).xyz, (intBitsToFloat(Temp_int[0]).yzwy).xyz)).z);
                //Instruction 132
                //RSQ
                Temp_int[1].z = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[1]).z)).z);
                //Instruction 133
                //MUL
                Temp_int[0].yzw = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyzw * intBitsToFloat(Temp_int[1]).zzzz).yzw;
                //Instruction 134
                //FTOU
                Temp_int[5].w = int(intBitsToFloat(Temp_int[1].x));
                //Instruction 135
                //MUL
                Temp_int[1].xzw = floatBitsToInt(intBitsToFloat(Temp_int[8]).zzxy * intBitsToFloat(Temp_int[9]).xxyz).xzw;
                //Instruction 136
                //MAD
                Temp_int[1].xzw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[9]).zzxy * intBitsToFloat(Temp_int[8]).xxyz + -intBitsToFloat(Temp_int[1]).xxzw)).xzw;
                //Instruction 137
                //MUL
                Temp_int[9].xyz = floatBitsToInt(intBitsToFloat(Temp_int[1]).xzwx * intBitsToFloat(Temp_int[8]).zxyz).xyz;
                //Instruction 138
                //MAD
                Temp_int[1].xzw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[8]).yyzx * intBitsToFloat(Temp_int[1]).zzwx + -intBitsToFloat(Temp_int[9]).xxyz)).xzw;
                //Instruction 139
                //DP3
                Temp_int[4].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[1]).xzwx).xyz, (intBitsToFloat(Temp_int[1]).xzwx).xyz)).w);
                //Instruction 140
                //RSQ
                Temp_int[4].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[4]).w)).w);
                //Instruction 141
                //MUL
                Temp_int[1].xzw = floatBitsToInt(intBitsToFloat(Temp_int[1]).xxzw * intBitsToFloat(Temp_int[4]).wwww).xzw;
                //Instruction 142
                //FTOU
                Temp_int[7].w = int(intBitsToFloat(Temp_int[2].x));
                //Instruction 143
                //MOVC
                if(ivec4(Temp_int[0].xxxx).x != 0) {
                    Temp_int[5] = Temp_int[5];
                } else {
                    Temp_int[5] = Temp_int[7];
                }
                //Instruction 144
                //MOVC
                if(ivec4(Temp_int[0].xxxx).x != 0) {
                    Temp_int[6].xyz = ivec4(Temp_int[6].xyzx).xyz;
                } else {
                    Temp_int[6].xyz = ivec4(Temp_int[8].xyzx).xyz;
                }
                //Instruction 145
                //MOVC
                if(ivec4(Temp_int[0].xxxx).x != 0) {
                    Temp_int[0].xyz = ivec4(Temp_int[0].yzwy).xyz;
                } else {
                    Temp_int[0].xyz = ivec4(Temp_int[1].xzwx).xyz;
                }
                //Instruction 146
                //MOVC
                if(ivec4(Temp_int[1].yyyy).x != 0) {
                    Temp_int[1].xzw = ivec4(Temp_int[4].xxyz).xyz;
                } else {
                    Temp_int[1].xzw = ivec4(Temp_int[6].xxyz).xyz;
                }
                //Instruction 147
                //MOVC
                if(ivec4(Temp_int[1].yyyy).x != 0) {
                    Temp_int[0].xyz = ivec4(Temp_int[2].yzwy).xyz;
                } else {
                    Temp_int[0].xyz = ivec4(Temp_int[0].xyzx).xyz;
                }
                //Instruction 148
                //MOVC
                if(ivec4(Temp_int[1].yyyy).x != 0) {
                    Temp_int[2] = Temp_int[3];
                } else {
                    Temp_int[2] = Temp_int[5];
                }
                //Instruction 149
                //MOV
                Output0.xyz = vec4(Input4[0].xyzx).xyz;
                //Instruction 150
                //MOV
                Output1.xyz = vec4(intBitsToFloat(Temp_int[1].xzwx)).xyz;
                //Instruction 151
                //MOV
                Output2.xyz = vec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
                //Instruction 152
                //MOV
                Output3.xz = vec4(Input3[0].xxzx).xz;
                //Instruction 153
                //MOV
                Output3.y = vec4(intBitsToFloat(int(0x3F800000))).y;
                //Instruction 154
                //MOV
                Output4.xyz = vec4(intBitsToFloat(Temp_int[2].xyzx)).xyz;
                //Instruction 155
                //MOV
                Output5.x = uvec4(Temp_int[2].w).x;
                //Instruction 156
                //MOV
                Output5.y = uvec4(Input5[0].y).y;
                //Instruction 157
                //EMIT
                EmitVertex();
                //Instruction 158
            //ELSE
            } else {
                //Instruction 159
                //ADD
                Temp_int[0].xyz = floatBitsToInt(-gl_in[0].gl_Position.xyzx + Input4[0].xyzx).xyz;
                //Instruction 160
                //DP3
                Temp_int[0].x = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).xyzx).xyz, (intBitsToFloat(Temp_int[0]).xyzx).xyz)).x);
                //Instruction 161
                //SQRT
                Temp_int[0].x = floatBitsToInt(vec4(sqrt(intBitsToFloat(Temp_int[0]).x)).x);
                //Instruction 162
                //MAD
                Temp_int[0].xyz = floatBitsToInt(vec4(Input2[0].xyzx * intBitsToFloat(Temp_int[0]).xxxx + gl_in[0].gl_Position.xyzx)).xyz;
                //Instruction 163
                //ADD
                Temp_int[1].xyz = floatBitsToInt(-intBitsToFloat(Temp_int[0]).xyzx + Input4[0].xyzx).xyz;
                //Instruction 164
                //MAD
                Temp_int[0].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).xyzx * vec4(0.500000, 0.500000, 0.500000, 0.000000) + intBitsToFloat(Temp_int[0]).xyzx)).xyz;
                //Instruction 165
                //ADD
                Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx + -gl_in[0].gl_Position.xyzx).xyz;
                //Instruction 166
                //DP3
                Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[0]).xyzx).xyz, (intBitsToFloat(Temp_int[0]).xyzx).xyz)).w);
                //Instruction 167
                //RSQ
                Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
                //Instruction 168
                //MUL
                Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[0]).xyzx).xyz;
                //Instruction 169
                //MAD
                Temp_int[1].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).xyzx * cbUIUpdatesGS.g_fStepSize + gl_in[0].gl_Position.xyzx)).xyz;
                //Instruction 170
                //MUL
                Temp_int[2].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).zxyz * Input1[0].xyzx).xyz;
                //Instruction 171
                //MAD
                Temp_int[2].xyz = floatBitsToInt(vec4(Input1[0].zxyz * intBitsToFloat(Temp_int[0]).xyzx + -intBitsToFloat(Temp_int[2]).xyzx)).xyz;
                //Instruction 172
                //MUL
                Temp_int[3].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).zxyz * intBitsToFloat(Temp_int[2]).xyzx).xyz;
                //Instruction 173
                //MAD
                Temp_int[2].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).yzxy * intBitsToFloat(Temp_int[2]).yzxy + -intBitsToFloat(Temp_int[3]).xyzx)).xyz;
                //Instruction 174
                //DP3
                Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[2]).xyzx).xyz, (intBitsToFloat(Temp_int[2]).xyzx).xyz)).w);
                //Instruction 175
                //RSQ
                Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
                //Instruction 176
                //MUL
                Temp_int[2].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[2]).xyzx).xyz;
                //Instruction 177
                //UTOF
                Temp_int[0].w = floatBitsToInt(vec4(Input5[0].x).w);
                //Instruction 178
                //ADD
                Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + cb0GS.g_fGlobalTime);
                //Instruction 179
                //MUL
                Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.000977);
                //Instruction 180
                //SAMPLE_L
                Temp_int[3] = floatBitsToInt(textureLod(g_txRandom, intBitsToFloat(Temp_int[0]).w, 0.000000));
                //Instruction 181
                //DP3
                Temp_int[0].w = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[3]).xyzx).xyz, (intBitsToFloat(Temp_int[3]).xyzx).xyz)).w);
                //Instruction 182
                //RSQ
                Temp_int[0].w = floatBitsToInt(vec4(inversesqrt(intBitsToFloat(Temp_int[0]).w)).w);
                //Instruction 183
                //MUL
                Temp_int[3].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[3]).xyzx).xyz;
                //Instruction 184
                //LT
                Temp_int[0].w = floatBitsToInt(((abs(intBitsToFloat(Temp_int[3]).x))< (cbUIUpdatesGS.g_fLeafRate)) ? int(0xFFFFFFFF) : 0);
                //Instruction 185
                //MUL
                Temp_int[1].w = floatBitsToInt(abs(intBitsToFloat(Temp_int[3]).y) * 2000.000000);
                //Instruction 186
                //FTOU
                Temp_int[1].w = int(intBitsToFloat(Temp_int[1].w));
                //Instruction 187
                //AND
                Temp_int[0].w = Temp_int[0].w & Temp_int[1].w;
                //Instruction 188
                //LT
                Temp_int[1].w = floatBitsToInt(((cbUIUpdatesGS.g_fLifeSpan)< (Input3[0].z)) ? int(0xFFFFFFFF) : 0);
                //Instruction 189
                //UTOF
                Temp_int[2].w = floatBitsToInt(vec4(cbUIUpdatesGS.g_uMaxFaces).w);
                //Instruction 190
                //MUL
                Temp_int[2].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).w * abs(intBitsToFloat(Temp_int[3]).z));
                //Instruction 191
                //FTOU
                Temp_int[3].z = int(intBitsToFloat(Temp_int[2].w));
                //Instruction 192
                //MOV
                Temp_int[3].xyw = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xyw;
                //Instruction 193
                //MOV
                Temp_int[4].x = ivec4(floatBitsToInt(cbUIUpdatesGS.g_fLifeSpan)).x;
                //Instruction 194
                //MOV
                Temp_int[4].y = ivec4(int(0x3F800000)).y;
                //Instruction 195
                //MOV
                Temp_int[4].z = ivec4(Input5[0].x).z;
                //Instruction 196
                //MOV
                Temp_int[4].w = ivec4(floatBitsToInt(Input3[0].z)).w;
                //Instruction 197
                //MOVC
                if(ivec4(Temp_int[1].wwww).x != 0) {
                    Temp_int[3] = Temp_int[3];
                } else {
                    Temp_int[3] = Temp_int[4];
                }
                //Instruction 198
                //MOV
                Output0.xyz = vec4(intBitsToFloat(Temp_int[1].xyzx)).xyz;
                //Instruction 199
                //MOV
                Output1.xyz = vec4(intBitsToFloat(Temp_int[2].xyzx)).xyz;
                //Instruction 200
                //MOV
                Output2.xyz = vec4(intBitsToFloat(Temp_int[0].xyzx)).xyz;
                //Instruction 201
                //MOV
                Output3.xyz = vec4(intBitsToFloat(Temp_int[3].xywx)).xyz;
                //Instruction 202
                //MOV
                Output4.xyz = vec4(Input4[0].xyzx).xyz;
                //Instruction 203
                //MOV
                Output5.x = uvec4(Temp_int[3].z).x;
                //Instruction 204
                //MOV
                Output5.y = uvec4(Temp_int[0].w).y;
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
        Temp_int[0].xy = floatBitsToInt(vec4(-1.000000, 1.000000, 0.000000, 0.000000) + Input3[0].xzxx).xy;
        //Instruction 209
        //NE
        Temp_int[0].z = floatBitsToInt(((intBitsToFloat(Temp_int[0]).x)!= (0.000000)) ? int(0xFFFFFFFF) : 0);
        //Instruction 210
        //LT
        Temp_int[0].w = floatBitsToInt(((intBitsToFloat(Temp_int[0]).y)< (cbUIUpdatesGS.g_fLifeSpan)) ? int(0xFFFFFFFF) : 0);
        //Instruction 211
        //AND
        Temp_int[0].z = Temp_int[0].w & Temp_int[0].z;
        //Instruction 212
        //IF
        if((Temp_int[0].z)!=0){
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
            Output3.xz = vec4(intBitsToFloat(Temp_int[0].xxyx)).xz;
            //Instruction 217
            //MOV
            Output3.y = vec4(intBitsToFloat(int(0x40400000))).y;
            //Instruction 218
            //MOV
            Output4.xyz = vec4(Input4[0].xyzx).xyz;
            //Instruction 219
            //MOV
            Output5.xy = uvec4(Input5[0].xyxx).xy;
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
