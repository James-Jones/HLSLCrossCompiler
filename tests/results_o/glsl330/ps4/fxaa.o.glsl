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
uniform struct cbFxaaPS_Type {
	vec4 rcpFrame;
} cbFxaaPS;
uniform sampler2D inputTexture;
 in  vec4 VtxGeoOutput1;
vec4 Input1;
out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[8];
ivec4 Temp_int[8];
uvec4 Temp_uint[8];
void main()
{
    //--- Start Early Main ---
    Input1 = VtxGeoOutput1;
    //--- End Early Main ---
    //Instruction 0
    //SAMPLE_L
    Temp_int[0].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(0, -1))).xyz;
    //Instruction 1
    //SAMPLE_L
    Temp_int[1].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(-1, 0))).xyz;
    //Instruction 2
    //SAMPLE_L
    Temp_int[2].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(0, 0))).xyz;
    //Instruction 3
    //SAMPLE_L
    Temp_int[3].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(1, 0))).xyz;
    //Instruction 4
    //SAMPLE_L
    Temp_int[4].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(0, 1))).xyz;
    //Instruction 5
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * 1.963211 + intBitsToFloat(Temp_int[0]).x);
    //Instruction 6
    //MAD
    Temp_int[1].w = floatBitsToInt(intBitsToFloat(Temp_int[1]).y * 1.963211 + intBitsToFloat(Temp_int[1]).x);
    //Instruction 7
    //MAD
    Temp_int[2].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).y * 1.963211 + intBitsToFloat(Temp_int[2]).x);
    //Instruction 8
    //MAD
    Temp_int[3].w = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * 1.963211 + intBitsToFloat(Temp_int[3]).x);
    //Instruction 9
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).y * 1.963211 + intBitsToFloat(Temp_int[4]).x);
    //Instruction 10
    //MIN
    Temp_int[5].x = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[0]).w, intBitsToFloat(Temp_int[1]).w)).x);
    //Instruction 11
    //MIN
    Temp_int[5].y = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[3]).w, intBitsToFloat(Temp_int[4]).w)).y);
    //Instruction 12
    //MIN
    Temp_int[5].x = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[5]).y, intBitsToFloat(Temp_int[5]).x)).x);
    //Instruction 13
    //MIN
    Temp_int[5].x = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[2]).w, intBitsToFloat(Temp_int[5]).x)).x);
    //Instruction 14
    //MAX
    Temp_int[5].y = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[0]).w, intBitsToFloat(Temp_int[1]).w)).y);
    //Instruction 15
    //MAX
    Temp_int[5].z = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[3]).w, intBitsToFloat(Temp_int[4]).w)).z);
    //Instruction 16
    //MAX
    Temp_int[5].y = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[5]).z, intBitsToFloat(Temp_int[5]).y)).y);
    //Instruction 17
    //MAX
    Temp_int[5].y = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[2]).w, intBitsToFloat(Temp_int[5]).y)).y);
    //Instruction 18
    //ADD
    Temp_int[5].x = floatBitsToInt(-intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[5]).y);
    //Instruction 19
    //MUL
    Temp_int[5].y = floatBitsToInt(intBitsToFloat(Temp_int[5]).y * 0.125000);
    //Instruction 20
    //MAX
    Temp_int[5].y = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[5]).y, 0.041667)).y);
    //Instruction 21
    //GE
    Temp_int[5].y = floatBitsToInt(((Temp_int[5].x)>= (Temp_int[5].y)) ? int(0xFFFFFFFF) : 0);
    //Instruction 22
    //IF
    if((Temp_int[5].y)!=0){
        //Instruction 23
        //ADD
        Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx + intBitsToFloat(Temp_int[1]).xyzx).xyz;
        //Instruction 24
        //ADD
        Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[2]).xyzx + intBitsToFloat(Temp_int[0]).xyzx).xyz;
        //Instruction 25
        //ADD
        Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[3]).xyzx + intBitsToFloat(Temp_int[0]).xyzx).xyz;
        //Instruction 26
        //ADD
        Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[4]).xyzx + intBitsToFloat(Temp_int[0]).xyzx).xyz;
        //Instruction 27
        //ADD
        Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[1]).w);
        //Instruction 28
        //ADD
        Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).w + intBitsToFloat(Temp_int[1]).x);
        //Instruction 29
        //ADD
        Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).x);
        //Instruction 30
        //MAD
        Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).x * 0.250000 + -intBitsToFloat(Temp_int[2]).w);
        //Instruction 31
        //DIV
        Temp_int[1].x = floatBitsToInt(abs(intBitsToFloat(Temp_int[1]).x) / intBitsToFloat(Temp_int[5]).x);
        //Instruction 32
        //ADD
        Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).x + -0.250000);
        //Instruction 33
        //MAX
        Temp_int[1].x = floatBitsToInt(vec4(max(intBitsToFloat(Temp_int[1]).x, 0.000000)).x);
        //Instruction 34
        //MUL
        Temp_int[1].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).x * 1.333333);
        //Instruction 35
        //MIN
        Temp_int[1].x = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[1]).x, 0.750000)).x);
        //Instruction 36
        //SAMPLE_L
        Temp_int[3].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(-1, -1))).xyz;
        //Instruction 37
        //SAMPLE_L
        Temp_int[4].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(1, -1))).xyz;
        //Instruction 38
        //SAMPLE_L
        Temp_int[5].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(-1, 1))).xyz;
        //Instruction 39
        //SAMPLE_L
        Temp_int[6].xyz = floatBitsToInt(textureLodOffset(inputTexture, Input1.xy, 0.000000, ivec2(1, 1))).xyz;
        //Instruction 40
        //ADD
        Temp_int[7].xyz = floatBitsToInt(intBitsToFloat(Temp_int[3]).xyzx + intBitsToFloat(Temp_int[4]).xyzx).xyz;
        //Instruction 41
        //ADD
        Temp_int[7].xyz = floatBitsToInt(intBitsToFloat(Temp_int[5]).xyzx + intBitsToFloat(Temp_int[7]).xyzx).xyz;
        //Instruction 42
        //ADD
        Temp_int[7].xyz = floatBitsToInt(intBitsToFloat(Temp_int[6]).xyzx + intBitsToFloat(Temp_int[7]).xyzx).xyz;
        //Instruction 43
        //ADD
        Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyzx + intBitsToFloat(Temp_int[7]).xyzx).xyz;
        //Instruction 44
        //MUL
        Temp_int[0].xyz = floatBitsToInt(intBitsToFloat(Temp_int[1]).xxxx * intBitsToFloat(Temp_int[0]).xyzx).xyz;
        //Instruction 45
        //MAD
        Temp_int[1].y = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * 1.963211 + intBitsToFloat(Temp_int[3]).x);
        //Instruction 46
        //MAD
        Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).y * 1.963211 + intBitsToFloat(Temp_int[4]).x);
        //Instruction 47
        //MAD
        Temp_int[3].x = floatBitsToInt(intBitsToFloat(Temp_int[5]).y * 1.963211 + intBitsToFloat(Temp_int[5]).x);
        //Instruction 48
        //MAD
        Temp_int[3].y = floatBitsToInt(intBitsToFloat(Temp_int[6]).y * 1.963211 + intBitsToFloat(Temp_int[6]).x);
        //Instruction 49
        //MUL
        Temp_int[3].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * -0.500000);
        //Instruction 50
        //MAD
        Temp_int[3].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).y * 0.250000 + intBitsToFloat(Temp_int[3]).z);
        //Instruction 51
        //MAD
        Temp_int[3].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * 0.250000 + intBitsToFloat(Temp_int[3]).z);
        //Instruction 52
        //MUL
        Temp_int[4].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).w * -0.500000);
        //Instruction 53
        //MAD
        Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[1]).w * 0.500000 + -intBitsToFloat(Temp_int[2]).w);
        //Instruction 54
        //MUL
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[3]).w * -0.500000);
        //Instruction 55
        //MAD
        Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[3]).w * 0.500000 + intBitsToFloat(Temp_int[4]).y);
        //Instruction 56
        //ADD
        Temp_int[3].z = floatBitsToInt(abs(intBitsToFloat(Temp_int[3]).z) + abs(intBitsToFloat(Temp_int[4]).y));
        //Instruction 57
        //MUL
        Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[4]).w * -0.500000);
        //Instruction 58
        //MAD
        Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[3]).x * 0.250000 + intBitsToFloat(Temp_int[4]).y);
        //Instruction 59
        //MAD
        Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * 0.250000 + intBitsToFloat(Temp_int[4]).y);
        //Instruction 60
        //ADD
        Temp_int[3].z = floatBitsToInt(intBitsToFloat(Temp_int[3]).z + abs(intBitsToFloat(Temp_int[4]).y));
        //Instruction 61
        //MAD
        Temp_int[1].y = floatBitsToInt(intBitsToFloat(Temp_int[1]).y * 0.250000 + intBitsToFloat(Temp_int[4]).x);
        //Instruction 62
        //MAD
        Temp_int[1].y = floatBitsToInt(intBitsToFloat(Temp_int[3]).x * 0.250000 + intBitsToFloat(Temp_int[1]).y);
        //Instruction 63
        //MAD
        Temp_int[3].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.500000 + -intBitsToFloat(Temp_int[2]).w);
        //Instruction 64
        //MAD
        Temp_int[3].x = floatBitsToInt(intBitsToFloat(Temp_int[4]).w * 0.500000 + intBitsToFloat(Temp_int[3]).x);
        //Instruction 65
        //ADD
        Temp_int[1].y = floatBitsToInt(abs(intBitsToFloat(Temp_int[1]).y) + abs(intBitsToFloat(Temp_int[3]).x));
        //Instruction 66
        //MAD
        Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * 0.250000 + intBitsToFloat(Temp_int[4]).z);
        //Instruction 67
        //MAD
        Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * 0.250000 + intBitsToFloat(Temp_int[1]).z);
        //Instruction 68
        //ADD
        Temp_int[1].y = floatBitsToInt(abs(intBitsToFloat(Temp_int[1]).z) + intBitsToFloat(Temp_int[1]).y);
        //Instruction 69
        //GE
        Temp_int[1].y = floatBitsToInt(((Temp_int[1].y)>= (Temp_int[3].z)) ? int(0xFFFFFFFF) : 0);
        //Instruction 70
        //MOVC
        if(ivec4(Temp_int[1].y).x != 0) {
            Temp_int[1].z = floatBitsToInt(-cbFxaaPS.rcpFrame.y);
        } else {
            Temp_int[1].z = floatBitsToInt(-cbFxaaPS.rcpFrame.x);
        }
        //Instruction 71
        //MOVC
        if(ivec4(Temp_int[1].y).x != 0) {
            Temp_int[0].w = Temp_int[0].w;
        } else {
            Temp_int[0].w = Temp_int[1].w;
        }
        //Instruction 72
        //MOVC
        if(ivec4(Temp_int[1].y).x != 0) {
            Temp_int[1].w = Temp_int[4].w;
        } else {
            Temp_int[1].w = Temp_int[3].w;
        }
        //Instruction 73
        //ADD
        Temp_int[3].x = floatBitsToInt(-intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[0]).w);
        //Instruction 74
        //ADD
        Temp_int[3].y = floatBitsToInt(-intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[1]).w);
        //Instruction 75
        //ADD
        Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[0]).w);
        //Instruction 76
        //MUL
        Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * 0.500000);
        //Instruction 77
        //ADD
        Temp_int[1].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[1]).w);
        //Instruction 78
        //MUL
        Temp_int[1].w = floatBitsToInt(intBitsToFloat(Temp_int[1]).w * 0.500000);
        //Instruction 79
        //GE
        Temp_int[3].z = floatBitsToInt(((abs(Temp_int[3].x))>= (abs(Temp_int[3].y))) ? int(0xFFFFFFFF) : 0);
        //Instruction 80
        //MOVC
        if(ivec4(Temp_int[3].z).x != 0) {
            Temp_int[0].w = Temp_int[0].w;
        } else {
            Temp_int[0].w = Temp_int[1].w;
        }
        //Instruction 81
        //MAX
        Temp_int[1].w = floatBitsToInt(vec4(max(abs(intBitsToFloat(Temp_int[3]).y), abs(intBitsToFloat(Temp_int[3]).x))).w);
        //Instruction 82
        //MOVC
        if(ivec4(Temp_int[3].z).x != 0) {
            Temp_int[1].z = Temp_int[1].z;
        } else {
            Temp_int[1].z = -Temp_int[1].z;
        }
        //Instruction 83
        //MUL
        Temp_int[3].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * 0.500000);
        //Instruction 84
        //MOVC
        if(ivec4(Temp_int[1].y).x != 0) {
            Temp_int[3].y = int(0x0);
        } else {
            Temp_int[3].y = Temp_int[3].x;
        }
        //Instruction 85
        //AND
        Temp_int[3].x = Temp_int[1].y & Temp_int[3].x;
        //Instruction 86
        //ADD
        Temp_int[4].xy = floatBitsToInt(intBitsToFloat(Temp_int[3]).yxyy + Input1.xyxx).xy;
        //Instruction 87
        //MUL
        Temp_int[1].w = floatBitsToInt(intBitsToFloat(Temp_int[1]).w * 0.250000);
        //Instruction 88
        //MOV
        Temp_int[3].yz = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).yz;
        //Instruction 89
        //MOV
        Temp_int[3].xw = ivec4(floatBitsToInt(cbFxaaPS.rcpFrame.xxxy)).xw;
        //Instruction 90
        //MOVC
        if(ivec4(Temp_int[1].yyyy).x != 0) {
            Temp_int[3].xy = ivec4(Temp_int[3].xyxx).xy;
        } else {
            Temp_int[3].xy = ivec4(Temp_int[3].zwzz).xy;
        }
        //Instruction 91
        //ADD
        Temp_int[3].zw = floatBitsToInt(-intBitsToFloat(Temp_int[3]).xxxy + intBitsToFloat(Temp_int[4]).xxxy).zw;
        //Instruction 92
        //ADD
        Temp_int[4].xy = floatBitsToInt(intBitsToFloat(Temp_int[3]).xyxx + intBitsToFloat(Temp_int[4]).xyxx).xy;
        //Instruction 93
        //MOV
        Temp_int[4].zw = ivec4(Temp_int[3].zzzw).zw;
        //Instruction 94
        //MOV
        Temp_int[5].xy = ivec4(Temp_int[4].xyxx).xy;
        //Instruction 95
        //MOV
        Temp_int[5].zw = ivec4(Temp_int[0].wwww).zw;
        //Instruction 96
        //MOV
        Temp_int[6].xyz = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xyz;
        //Instruction 97
        //LOOP
        while(true){
            //Instruction 98
            //IGE
            Temp_int[6].w = (((Temp_int[6].z)>= (int(0x10))) ? int(0xFFFFFFFF) : 0);
            //Instruction 99
            //BREAKC
            if((Temp_int[6].w)!=0){break;}
            //Instruction 100
            //IF
            if((Temp_int[6].x)==0){
                //Instruction 101
                //SAMPLE_L
                Temp_int[7].xy = floatBitsToInt(textureLod(inputTexture, intBitsToFloat(Temp_int[4]).zw, 0.000000)).xy;
                //Instruction 102
                //MAD
                Temp_int[6].w = floatBitsToInt(intBitsToFloat(Temp_int[7]).y * 1.963211 + intBitsToFloat(Temp_int[7]).x);
                //Instruction 103
            //ELSE
            } else {
                //Instruction 104
                //MOV
                Temp_int[6].w = ivec4(Temp_int[5].z).w;
                //Instruction 105
            //ENDIF
            }
            //Instruction 106
            //IF
            if((Temp_int[6].y)==0){
                //Instruction 107
                //SAMPLE_L
                Temp_int[7].xy = floatBitsToInt(textureLod(inputTexture, intBitsToFloat(Temp_int[5]).xy, 0.000000)).xy;
                //Instruction 108
                //MAD
                Temp_int[7].x = floatBitsToInt(intBitsToFloat(Temp_int[7]).y * 1.963211 + intBitsToFloat(Temp_int[7]).x);
                //Instruction 109
            //ELSE
            } else {
                //Instruction 110
                //MOV
                Temp_int[7].x = ivec4(Temp_int[5].w).x;
                //Instruction 111
            //ENDIF
            }
            //Instruction 112
            //ADD
            Temp_int[7].y = floatBitsToInt(-intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[6]).w);
            //Instruction 113
            //GE
            Temp_int[7].y = floatBitsToInt(((abs(Temp_int[7].y))>= (Temp_int[1].w)) ? int(0xFFFFFFFF) : 0);
            //Instruction 114
            //OR
            Temp_int[6].x = Temp_int[6].x | Temp_int[7].y;
            //Instruction 115
            //ADD
            Temp_int[7].y = floatBitsToInt(-intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[7]).x);
            //Instruction 116
            //GE
            Temp_int[7].y = floatBitsToInt(((abs(Temp_int[7].y))>= (Temp_int[1].w)) ? int(0xFFFFFFFF) : 0);
            //Instruction 117
            //OR
            Temp_int[6].y = Temp_int[6].y | Temp_int[7].y;
            //Instruction 118
            //AND
            Temp_int[7].y = Temp_int[6].y & Temp_int[6].x;
            //Instruction 119
            //IF
            if((Temp_int[7].y)!=0){
                //Instruction 120
                //MOV
                Temp_int[5].z = ivec4(Temp_int[6].w).z;
                //Instruction 121
                //MOV
                Temp_int[5].w = ivec4(Temp_int[7].x).w;
                //Instruction 122
                //BREAK
                break;
                //Instruction 123
            //ENDIF
            }
            //Instruction 124
            //ADD
            Temp_int[7].yz = floatBitsToInt(-intBitsToFloat(Temp_int[3]).xxyx + intBitsToFloat(Temp_int[4]).zzwz).yz;
            //Instruction 125
            //MOVC
            if(ivec4(Temp_int[6].xxxx).x != 0) {
                Temp_int[4].zw = ivec4(Temp_int[4].zzzw).xy;
            } else {
                Temp_int[4].zw = ivec4(Temp_int[7].yyyz).xy;
            }
            //Instruction 126
            //ADD
            Temp_int[7].yz = floatBitsToInt(intBitsToFloat(Temp_int[3]).xxyx + intBitsToFloat(Temp_int[5]).xxyx).yz;
            //Instruction 127
            //MOVC
            if(ivec4(Temp_int[6].yyyy).x != 0) {
                Temp_int[5].xy = ivec4(Temp_int[5].xyxx).xy;
            } else {
                Temp_int[5].xy = ivec4(Temp_int[7].yzyy).xy;
            }
            //Instruction 128
            //IADD
            Temp_int[6].z = (Temp_int[6].z + int(0x1));
            //Instruction 129
            //MOV
            Temp_int[5].z = ivec4(Temp_int[6].w).z;
            //Instruction 130
            //MOV
            Temp_int[5].w = ivec4(Temp_int[7].x).w;
            //Instruction 131
        //ENDLOOP
        }
        //Instruction 132
        //ADD
        Temp_int[3].xy = floatBitsToInt(-intBitsToFloat(Temp_int[4]).zwzz + Input1.xyxx).xy;
        //Instruction 133
        //MOVC
        if(ivec4(Temp_int[1].y).x != 0) {
            Temp_int[1].w = Temp_int[3].x;
        } else {
            Temp_int[1].w = Temp_int[3].y;
        }
        //Instruction 134
        //ADD
        Temp_int[3].xy = floatBitsToInt(intBitsToFloat(Temp_int[5]).xyxx + -Input1.xyxx).xy;
        //Instruction 135
        //MOVC
        if(ivec4(Temp_int[1].y).x != 0) {
            Temp_int[3].x = Temp_int[3].x;
        } else {
            Temp_int[3].x = Temp_int[3].y;
        }
        //Instruction 136
        //LT
        Temp_int[3].y = floatBitsToInt(((intBitsToFloat(Temp_int[1]).w)< (intBitsToFloat(Temp_int[3]).x)) ? int(0xFFFFFFFF) : 0);
        //Instruction 137
        //MOVC
        if(ivec4(Temp_int[3].y).x != 0) {
            Temp_int[3].y = Temp_int[5].z;
        } else {
            Temp_int[3].y = Temp_int[5].w;
        }
        //Instruction 138
        //ADD
        Temp_int[2].w = floatBitsToInt(-intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[2]).w);
        //Instruction 139
        //LT
        Temp_int[2].w = floatBitsToInt(((intBitsToFloat(Temp_int[2]).w)< (0.000000)) ? int(0xFFFFFFFF) : 0);
        //Instruction 140
        //ADD
        Temp_int[0].w = floatBitsToInt(-intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[3]).y);
        //Instruction 141
        //LT
        Temp_int[0].w = floatBitsToInt(((intBitsToFloat(Temp_int[0]).w)< (0.000000)) ? int(0xFFFFFFFF) : 0);
        //Instruction 142
        //IEQ
        Temp_int[0].w = (((Temp_int[2].w)== (Temp_int[0].w)) ? int(0xFFFFFFFF) : 0);
        //Instruction 143
        //MOVC
        if(ivec4(Temp_int[0].w).x != 0) {
            Temp_int[0].w = int(0x0);
        } else {
            Temp_int[0].w = Temp_int[1].z;
        }
        //Instruction 144
        //ADD
        Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).w + intBitsToFloat(Temp_int[3]).x);
        //Instruction 145
        //MIN
        Temp_int[1].w = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[1]).w, intBitsToFloat(Temp_int[3]).x)).w);
        //Instruction 146
        //DIV
        Temp_int[1].z = floatBitsToInt(-1.000000 / intBitsToFloat(Temp_int[1]).z);
        //Instruction 147
        //MAD
        Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).w * intBitsToFloat(Temp_int[1]).z + 0.500000);
        //Instruction 148
        //MUL
        Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * intBitsToFloat(Temp_int[1]).z);
        //Instruction 149
        //MOVC
        if(ivec4(Temp_int[1].y).x != 0) {
            Temp_int[1].z = int(0x0);
        } else {
            Temp_int[1].z = Temp_int[0].w;
        }
        //Instruction 150
        //ADD
        Temp_int[3].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).z + Input1.x);
        //Instruction 151
        //AND
        Temp_int[0].w = Temp_int[0].w & Temp_int[1].y;
        //Instruction 152
        //ADD
        Temp_int[3].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + Input1.y);
        //Instruction 153
        //SAMPLE_L
        Temp_int[1].yzw = floatBitsToInt(textureLod(inputTexture, intBitsToFloat(Temp_int[3]).xy, 0.000000).wxyz).yzw;
        //Instruction 154
        //MAD
        Temp_int[0].xyz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).xyzx * vec4(0.111111, 0.111111, 0.111111, 0.000000) + intBitsToFloat(Temp_int[1]).yzwy)).xyz;
        //Instruction 155
        //MAD
        Temp_int[2].xyz = floatBitsToInt(vec4(-intBitsToFloat(Temp_int[1]).xxxx * intBitsToFloat(Temp_int[1]).yzwy + intBitsToFloat(Temp_int[0]).xyzx)).xyz;
        //Instruction 156
    //ENDIF
    }
    //Instruction 157
    //MOV
    Output0.xyz = vec4(intBitsToFloat(Temp_int[2].xyzx)).xyz;
    //Instruction 158
    //MOV
    Output0.w = vec4(intBitsToFloat(int(0x3F800000))).w;
    //Instruction 159
    //RET
    return;
}
