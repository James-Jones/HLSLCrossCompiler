#version 150
#extension GL_ARB_shader_bit_encoding : require
#extension GL_ARB_texture_gather : enable
struct vec1 {
	float x;
};
struct uvec1 {
	uint x;
};
struct ivec1 {
	int x;
};
#define immediateConstBufferI(idx) immediateConstBufferInt[idx]
#define immediateConstBufferF(idx) immediateConstBuffer[idx]
vec4 immediateConstBuffer[40] = vec4[40] (
	vec4(0.000000, 0.000000, 1.000000, -1.000000), 
	vec4(0.000000, 0.000000, 0.000000, 1.000000), 
	vec4(0.000000, 0.000000, 0.000000, 3.000000), 
	vec4(0.000000, 0.000000, 2.000000, 1.000000), 
	vec4(5.308640, 0.000000, 3.000000, -1.000000), 
	vec4(11.396100, 0.000000, 1.000000, -3.000000), 
	vec4(17.926769, 0.000000, 1.000000, -5.000000), 
	vec4(24.936390, 0.000000, 3.000000, -3.000000), 
	vec4(0.000000, 0.000000, 5.000000, -1.000000), 
	vec4(0.000000, 0.000000, 4.000000, 1.000000), 
	vec4(0.000000, 0.000000, 2.000000, 3.000000), 
	vec4(0.000000, 0.000000, 0.000000, 5.000000), 
	vec4(0.000000, 0.000000, 0.000000, 7.000000), 
	vec4(0.000000, 0.000000, 2.000000, 5.000000), 
	vec4(0.000000, 0.000000, 4.000000, 3.000000), 
	vec4(0.000000, 0.000000, 6.000000, 1.000000), 
	vec4(0.000000, 0.000000, 7.000000, -1.000000), 
	vec4(0.000000, 0.000000, 5.000000, -3.000000), 
	vec4(0.000000, 0.000000, 3.000000, -5.000000), 
	vec4(0.000000, 0.000000, 1.000000, -7.000000), 
	vec4(1.000000, 0.500000, 0.447210, 0.707110), 
	vec4(0.500000, 0.447210, 0.707110, 1.000000), 
	vec4(0.300000, 0.291040, 0.379470, 0.400000), 
	vec4(0.424260, 0.332820, 0.379470, 0.536660), 
	vec4(0.400000, 0.300000, 0.291040, 0.379470), 
	vec4(0.536660, 0.424260, 0.332820, 0.379470), 
	vec4(0.315300, 0.290690, 0.241400, 0.254950), 
	vec4(0.360560, 0.290690, 0.260000, 0.306410), 
	vec4(0.260000, 0.216670, 0.213720, 0.254950), 
	vec4(0.290690, 0.241400, 0.254950, 0.315300), 
	vec4(0.290690, 0.260000, 0.306410, 0.360560), 
	vec4(0.216670, 0.213720, 0.254950, 0.260000), 
	vec4(0.175000, 0.173650, 0.197990, 0.200000), 
	vec4(0.221360, 0.208700, 0.240100, 0.259970), 
	vec4(0.247490, 0.218640, 0.240100, 0.280000), 
	vec4(0.221360, 0.192300, 0.197990, 0.230160), 
	vec4(0.200000, 0.175000, 0.173650, 0.197990), 
	vec4(0.259970, 0.221360, 0.208700, 0.240100), 
	vec4(0.280000, 0.247490, 0.218640, 0.240100), 
	vec4(0.230160, 0.221360, 0.192300, 0.197990)
);
ivec4 immediateConstBufferInt[40] = ivec4[40] (
	ivec4(1, 8, 1065353216, -1082130432), 
	ivec4(8, -1, 0, 1065353216), 
	ivec4(5, 4, 0, 1077936128), 
	ivec4(4, -4, 1073741824, 1065353216), 
	ivec4(1084874849, 0, 1077936128, -1082130432), 
	ivec4(1094080109, 0, 1065353216, -1069547520), 
	ivec4(1099917830, 0, 1065353216, -1063256064), 
	ivec4(1103592890, 0, 1077936128, -1069547520), 
	ivec4(0, 0, 1084227584, -1082130432), 
	ivec4(0, 0, 1082130432, 1065353216), 
	ivec4(0, 0, 1073741824, 1077936128), 
	ivec4(0, 0, 0, 1084227584), 
	ivec4(0, 0, 0, 1088421888), 
	ivec4(0, 0, 1073741824, 1084227584), 
	ivec4(0, 0, 1082130432, 1077936128), 
	ivec4(0, 0, 1086324736, 1065353216), 
	ivec4(0, 0, 1088421888, -1082130432), 
	ivec4(0, 0, 1084227584, -1069547520), 
	ivec4(0, 0, 1077936128, -1063256064), 
	ivec4(0, 0, 1065353216, -1059061760), 
	ivec4(1065353216, 1056964608, 1055193270, 1060439337), 
	ivec4(1056964608, 1055193270, 1060439337, 1065353216), 
	ivec4(1050253722, 1049953074, 1052920292, 1053609165), 
	ivec4(1054423195, 1051354978, 1052920292, 1057579661), 
	ivec4(1053609165, 1050253722, 1049953074, 1052920292), 
	ivec4(1057579661, 1054423195, 1051354978, 1052920292), 
	ivec4(1050767104, 1049941330, 1047998864, 1048742094), 
	ivec4(1052285778, 1049941330, 1048911544, 1050468806), 
	ivec4(1048911544, 1046339262, 1046141290, 1048742094), 
	ivec4(1049941330, 1047998864, 1048742094, 1050767104), 
	ivec4(1049941330, 1048911544, 1050468806, 1052285778), 
	ivec4(1046339262, 1046141290, 1048742094, 1048911544), 
	ivec4(1043542835, 1043452238, 1045085668, 1045220557), 
	ivec4(1046654002, 1045804404, 1047911622, 1048910538), 
	ivec4(1048407557, 1046471466, 1047911622, 1049582633), 
	ivec4(1046654002, 1044703819, 1045085668, 1047244560), 
	ivec4(1045220557, 1043542835, 1043452238, 1045085668), 
	ivec4(1048910538, 1046654002, 1045804404, 1047911622), 
	ivec4(1049582633, 1048407557, 1046471466, 1047911622), 
	ivec4(1047244560, 1046654002, 1044703819, 1045085668)
);
uniform struct _ParamsPS_Type {
	int b10_1;
	int iNumRingGathers;
	int iNumRings;
	int bUseNormals;
} _ParamsPS;
uniform struct cb0PS_Type {
	vec3 g_f3LightDir;
	vec3 g_f3EyePt;
	float g_fTime;
	vec4 g_f4x4World[4];
	vec4 g_f4x4View[4];
	vec4 g_f4x4WorldViewProjection[4];
	vec4 g_f4x4InvProjection[4];
	vec2 g_f2RTSize;
	float g_fHDAORejectRadius;
	float g_fHDAOIntensity;
	float g_fHDAOAcceptRadius;
	float g_fZFar;
	float g_fZNear;
	float g_fQ;
	float g_fQTimesZNear;
	float g_fNormalScale;
	float g_fAcceptAngle;
	vec4 g_f4MaterialDiffuse;
	vec4 g_f4MaterialSpecular;
	float g_fTanH;
	float g_fTanV;
} cb0PS;
uniform sampler2D g_txNormals;
uniform sampler2D g_txNormalsZ;
uniform sampler2D g_txNormalsXY;
uniform sampler2D g_txDepth;
 in  vec4 VtxGeoOutput1;
vec4 Input1;
out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[12];
ivec4 Temp_int[12];
uvec4 Temp_uint[12];
void main()
{
    //--- Start Early Main ---
    Input1 = VtxGeoOutput1;
    //--- End Early Main ---
    //Instruction 0
    //MUL
    Temp_int[0].xy = floatBitsToInt(Input1.xyxx * cb0PS.g_f2RTSize.xyxx.xyxx).xy;
    //Instruction 1
    //FTOI
    Temp_int[0].zw = ivec4(intBitsToFloat(Temp_int[0].xxxy)).zw;
    //Instruction 2
    //ADD
    Temp_int[1].xy = floatBitsToInt(cb0PS.g_f2RTSize.xyxx.xyxx + vec4(-1.000000, -1.000000, 0.000000, 0.000000)).xy;
    //Instruction 3
    //MOV
    Temp_int[2].zw = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).zw;
    //Instruction 4
    //MOV
    Temp_int[3].zw = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).zw;
    //Instruction 5
    //MOV
    Temp_int[1].zw = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).zw;
    //Instruction 6
    //LOOP
    while(true){
        //Instruction 7
        //IGE
        Temp_int[4].x = (((Temp_int[1].w)>= (int(0x4))) ? int(0xFFFFFFFF) : 0);
        //Instruction 8
        //BREAKC
        if((Temp_int[4].x)!=0){break;}
        //Instruction 9
        //IADD
        Temp_int[4].xy = (-ivec4(immediateConstBufferF(int(Temp_int[1].w))).xyxx + Temp_int[0].zwzz).xy;
        //Instruction 10
        //IADD
        Temp_int[4].zw = (Temp_int[0].zzzw + ivec4(immediateConstBufferF(int(Temp_int[1].w))).xxxy).zw;
        //Instruction 11
        //IADD
        Temp_int[4].xy = (ivec4(0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0) + Temp_int[4].xyxx).xy;
        //Instruction 12
        //ITOF
        Temp_int[4] = floatBitsToInt(vec4(Temp_int[4]));
        //Instruction 13
        //MIN
        Temp_int[4] = floatBitsToInt(vec4(min(intBitsToFloat(Temp_int[1]).xyxy, intBitsToFloat(Temp_int[4]))));
        //Instruction 14
        //FTOI
        Temp_int[4] = ivec4(intBitsToFloat(Temp_int[4]));
        //Instruction 15
        //IMAX
        Temp_int[2].xy = (ivec4(max(int(Temp_int[4].zwzz), int(ivec4(0x0, 0x0, 0x0, 0x0)))).xy);
        //Instruction 16
        //IMAX
        Temp_int[3].xy = (ivec4(max(int(Temp_int[4].xyxx), int(ivec4(0x0, 0x0, 0x0, 0x0)))).xy);
        //Instruction 17
        //IF
        if((_ParamsPS.b10_1)!=0){
            //Instruction 18
            //LD
            Temp_int[4].z = floatBitsToInt(texelFetch(g_txNormalsZ, ivec2((Temp_int[2].xyzz).xy), 0).z);
            //Instruction 19
            //LD
            Temp_int[5].z = floatBitsToInt(texelFetch(g_txNormalsZ, ivec2((Temp_int[3].xyzz).xy), 0).z);
            //Instruction 20
            //LD
            Temp_int[4].xy = floatBitsToInt(texelFetch(g_txNormalsXY, ivec2((Temp_int[2].xyzz).xy), 0).xy);
            //Instruction 21
            //LD
            Temp_int[5].xy = floatBitsToInt(texelFetch(g_txNormalsXY, ivec2((Temp_int[3].xyzz).xy), 0).xy);
            //Instruction 22
        //ELSE
        } else {
            //Instruction 23
            //LD
            Temp_int[4].xyz = floatBitsToInt(texelFetch(g_txNormals, ivec2((Temp_int[2].xyww).xy), 0).xyz);
            //Instruction 24
            //LD
            Temp_int[5].xyz = floatBitsToInt(texelFetch(g_txNormals, ivec2((Temp_int[3].xyww).xy), 0).xyz);
            //Instruction 25
        //ENDIF
        }
        //Instruction 26
        //DP3
        Temp_int[2].x = floatBitsToInt(vec4(dot((intBitsToFloat(Temp_int[4]).xyzx).xyz, (intBitsToFloat(Temp_int[5]).xyzx).xyz)).x);
        //Instruction 27
        //LT
        Temp_int[2].y = floatBitsToInt(((cb0PS.g_fAcceptAngle)< (intBitsToFloat(Temp_int[2]).x)) ? int(0xFFFFFFFF) : 0);
        //Instruction 28
        //MAD
        Temp_int[2].x = floatBitsToInt(-abs(intBitsToFloat(Temp_int[2]).x) * 0.250000 + 1.000000);
        //Instruction 29
        //MOVC
        if(ivec4(Temp_int[2].y).x != 0) {
            Temp_int[2].x = int(0x0);
        } else {
            Temp_int[2].x = Temp_int[2].x;
        }
        //Instruction 30
        //ADD
        Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[2]).x);
        //Instruction 31
        //IADD
        Temp_int[1].w = (Temp_int[1].w + int(0x1));
        //Instruction 32
    //ENDLOOP
    }
    //Instruction 33
    //MAD
    Temp_int[0].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * 0.250000 + 0.500000);
    //Instruction 34
    //LT
    Temp_int[0].w = floatBitsToInt(((0.500000)< (intBitsToFloat(Temp_int[0]).z)) ? int(0xFFFFFFFF) : 0);
    //Instruction 35
    //IF
    if((Temp_int[0].w)!=0){
        //Instruction 36
        //MUL
        Temp_int[1].xy = floatBitsToInt(cb0PS.g_f2RTSize.xyxx.xyxx * vec4(0.000977, 0.001302, 0.000000, 0.000000)).xy;
        //Instruction 37
        //DIV
        Temp_int[1].zw = floatBitsToInt(vec4(1.000000, 1.000000, 1.000000, 1.000000) / cb0PS.g_f2RTSize.xyxx.xxxy).zw;
        //Instruction 38
        //ROUND_Z
        Temp_int[2].xy = floatBitsToInt(vec4(trunc(intBitsToFloat(Temp_int[0]).xyxx)).xy);
        //Instruction 39
        //MUL
        Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[1]).zzzw * intBitsToFloat(Temp_int[2]).xxxy).zw;
        //Instruction 40
        //MUL
        Temp_int[3].xy = floatBitsToInt(intBitsToFloat(Temp_int[0]).xyxx * intBitsToFloat(Temp_int[1]).zwzz).xy;
        //Instruction 41
        //MOVC
        if(ivec4(_ParamsPS.b10_1).x != 0) {
            Temp_int[2].zw = ivec4(Temp_int[2].zzzw).xy;
        } else {
            Temp_int[2].zw = ivec4(Temp_int[3].xxxy).xy;
        }
        //Instruction 42
        //SAMPLE_L
        Temp_int[0].w = floatBitsToInt(textureLod(g_txDepth, intBitsToFloat(Temp_int[2]).zw, 0.000000).yzwx).w;
        //Instruction 43
        //ADD
        Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + -cb0PS.g_fQ);
        //Instruction 44
        //DIV
        Temp_int[0].w = floatBitsToInt(-cb0PS.g_fQTimesZNear / intBitsToFloat(Temp_int[0]).w);
        //Instruction 45
        //IF
        if((_ParamsPS.bUseNormals)!=0){
            //Instruction 46
            //IF
            if((_ParamsPS.b10_1)!=0){
                //Instruction 47
                //SAMPLE_L
                Temp_int[3].x = floatBitsToInt(textureLod(g_txNormalsZ, intBitsToFloat(Temp_int[2]).zw, 0.000000)).x;
                //Instruction 48
            //ELSE
            } else {
                //Instruction 49
                //SAMPLE_L
                Temp_int[3].x = floatBitsToInt(textureLod(g_txNormals, intBitsToFloat(Temp_int[2]).zw, 0.000000)).x;
                //Instruction 50
            //ENDIF
            }
            //Instruction 51
            //MAD
            Temp_int[2].z = floatBitsToInt(intBitsToFloat(Temp_int[3]).x * cb0PS.g_fNormalScale + intBitsToFloat(Temp_int[0]).w);
            //Instruction 52
        //ENDIF
        }
        //Instruction 53
        //MOV
        Temp_int[3] = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xyzw;
        //Instruction 54
        //MOV
        Temp_int[4] = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xyzw;
        //Instruction 55
        //MOV
        Temp_int[2].w = ivec4(int(0x0)).w;
        //Instruction 56
        //LOOP
        while(true){
            //Instruction 57
            //IGE
            Temp_int[5].x = (((Temp_int[2].w)>= (_ParamsPS.iNumRingGathers)) ? int(0xFFFFFFFF) : 0);
            //Instruction 58
            //BREAKC
            if((Temp_int[5].x)!=0){break;}
            //Instruction 59
            //MAD
            Temp_int[5].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).xyxx * immediateConstBufferF(int(Temp_int[2].w)).zwzz + vec4(1.000000, 1.000000, 0.000000, 0.000000))).xy;
            //Instruction 60
            //MAD
            Temp_int[5].zw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).xxxy * immediateConstBufferF(int(Temp_int[2].w)).zzzw + intBitsToFloat(Temp_int[0]).xxxy)).zw;
            //Instruction 61
            //MUL
            Temp_int[5].zw = floatBitsToInt(intBitsToFloat(Temp_int[1]).zzzw * intBitsToFloat(Temp_int[5]).zzzw).zw;
            //Instruction 62
            //MAD
            Temp_int[6].xy = floatBitsToInt(vec4(Input1.xyxx * cb0PS.g_f2RTSize.xyxx.xyxx + -intBitsToFloat(Temp_int[5]).xyxx)).xy;
            //Instruction 63
            //MUL
            Temp_int[6].xy = floatBitsToInt(intBitsToFloat(Temp_int[1]).zwzz * intBitsToFloat(Temp_int[6]).xyxx).xy;
            //Instruction 64
            //IF
            if((_ParamsPS.b10_1)!=0){
                //Instruction 65
                //ADD
                Temp_int[6].zw = floatBitsToInt(intBitsToFloat(Temp_int[2]).xxxy + intBitsToFloat(Temp_int[5]).xxxy).zw;
                //Instruction 66
                //MUL
                Temp_int[3].xy = floatBitsToInt(intBitsToFloat(Temp_int[1]).zwzz * intBitsToFloat(Temp_int[6]).zwzz).xy;
                //Instruction 67
                //ADD
                Temp_int[5].xy = floatBitsToInt(intBitsToFloat(Temp_int[2]).xyxx + -intBitsToFloat(Temp_int[5]).xyxx).xy;
                //Instruction 68
                //ADD
                Temp_int[5].xy = floatBitsToInt(intBitsToFloat(Temp_int[5]).xyxx + vec4(1.000000, 1.000000, 0.000000, 0.000000)).xy;
                //Instruction 69
                //MUL
                Temp_int[3].zw = floatBitsToInt(intBitsToFloat(Temp_int[1]).zzzw * intBitsToFloat(Temp_int[5]).xxxy).zw;
                //Instruction 70
                //GATHER4
                Temp_int[7] = floatBitsToInt(textureGather(g_txDepth, intBitsToFloat(Temp_int[3]).xy));
                //Instruction 71
                //ADD
                Temp_int[7] = floatBitsToInt(intBitsToFloat(Temp_int[7]) + -cb0PS.g_fQ);
                //Instruction 72
                //DIV
                Temp_int[7] = floatBitsToInt(-cb0PS.g_fQTimesZNear / intBitsToFloat(Temp_int[7]));
                //Instruction 73
                //GATHER4
                Temp_int[8] = floatBitsToInt(textureGather(g_txDepth, intBitsToFloat(Temp_int[3]).zw));
                //Instruction 74
                //ADD
                Temp_int[8] = floatBitsToInt(intBitsToFloat(Temp_int[8]) + -cb0PS.g_fQ);
                //Instruction 75
                //DIV
                Temp_int[8] = floatBitsToInt(-cb0PS.g_fQTimesZNear / intBitsToFloat(Temp_int[8]));
                //Instruction 76
            //ELSE
            } else {
                //Instruction 77
                //SAMPLE_L
                Temp_int[9].x = floatBitsToInt(textureLodOffset(g_txDepth, intBitsToFloat(Temp_int[5]).zw, 0.000000, ivec2(0, 1))).x;
                //Instruction 78
                //SAMPLE_L
                Temp_int[9].y = floatBitsToInt(textureLodOffset(g_txDepth, intBitsToFloat(Temp_int[5]).zw, 0.000000, ivec2(1, 1)).yxzw).y;
                //Instruction 79
                //SAMPLE_L
                Temp_int[9].z = floatBitsToInt(textureLodOffset(g_txDepth, intBitsToFloat(Temp_int[5]).zw, 0.000000, ivec2(1, 0)).yzxw).z;
                //Instruction 80
                //SAMPLE_L
                Temp_int[9].w = floatBitsToInt(textureLodOffset(g_txDepth, intBitsToFloat(Temp_int[5]).zw, 0.000000, ivec2(0, 0)).yzwx).w;
                //Instruction 81
                //ADD
                Temp_int[9] = floatBitsToInt(intBitsToFloat(Temp_int[9]) + -cb0PS.g_fQ);
                //Instruction 82
                //DIV
                Temp_int[7] = floatBitsToInt(-cb0PS.g_fQTimesZNear / intBitsToFloat(Temp_int[9]));
                //Instruction 83
                //SAMPLE_L
                Temp_int[9].x = floatBitsToInt(textureLodOffset(g_txDepth, intBitsToFloat(Temp_int[6]).xy, 0.000000, ivec2(0, 1))).x;
                //Instruction 84
                //SAMPLE_L
                Temp_int[9].y = floatBitsToInt(textureLodOffset(g_txDepth, intBitsToFloat(Temp_int[6]).xy, 0.000000, ivec2(1, 1)).yxzw).y;
                //Instruction 85
                //SAMPLE_L
                Temp_int[9].z = floatBitsToInt(textureLodOffset(g_txDepth, intBitsToFloat(Temp_int[6]).xy, 0.000000, ivec2(1, 0)).yzxw).z;
                //Instruction 86
                //SAMPLE_L
                Temp_int[9].w = floatBitsToInt(textureLodOffset(g_txDepth, intBitsToFloat(Temp_int[6]).xy, 0.000000, ivec2(0, 0)).yzwx).w;
                //Instruction 87
                //ADD
                Temp_int[9] = floatBitsToInt(intBitsToFloat(Temp_int[9]) + -cb0PS.g_fQ);
                //Instruction 88
                //DIV
                Temp_int[8] = floatBitsToInt(-cb0PS.g_fQTimesZNear / intBitsToFloat(Temp_int[9]));
                //Instruction 89
            //ENDIF
            }
            //Instruction 90
            //ADD
            Temp_int[9] = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww + -intBitsToFloat(Temp_int[7]));
            //Instruction 91
            //LT
            Temp_int[10] = floatBitsToInt(ivec4(lessThan(vec4(intBitsToFloat(Temp_int[9])).xyzw, vec4(cb0PS.g_fHDAORejectRadius).xyzw)) * int(0xFFFFFFFF));
            //Instruction 92
            //AND
            Temp_int[10] = (Temp_int[10] & ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000));
            //Instruction 93
            //LT
            Temp_int[9] = floatBitsToInt(ivec4(lessThan(vec4(cb0PS.g_fHDAOAcceptRadius).xyzw, vec4(intBitsToFloat(Temp_int[9])).xyzw)) * int(0xFFFFFFFF));
            //Instruction 94
            //AND
            Temp_int[9] = (Temp_int[9] & ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000));
            //Instruction 95
            //MUL
            Temp_int[9] = floatBitsToInt(intBitsToFloat(Temp_int[9]) * intBitsToFloat(Temp_int[10]));
            //Instruction 96
            //ADD
            Temp_int[10] = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww + -intBitsToFloat(Temp_int[8]).zwxy);
            //Instruction 97
            //LT
            Temp_int[11] = floatBitsToInt(ivec4(lessThan(vec4(intBitsToFloat(Temp_int[10])).xyzw, vec4(cb0PS.g_fHDAORejectRadius).xyzw)) * int(0xFFFFFFFF));
            //Instruction 98
            //AND
            Temp_int[11] = (Temp_int[11] & ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000));
            //Instruction 99
            //LT
            Temp_int[10] = floatBitsToInt(ivec4(lessThan(vec4(cb0PS.g_fHDAOAcceptRadius).xyzw, vec4(intBitsToFloat(Temp_int[10])).xyzw)) * int(0xFFFFFFFF));
            //Instruction 100
            //AND
            Temp_int[10] = (Temp_int[10] & ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000));
            //Instruction 101
            //MUL
            Temp_int[10] = floatBitsToInt(intBitsToFloat(Temp_int[10]) * intBitsToFloat(Temp_int[11]));
            //Instruction 102
            //MUL
            Temp_int[9] = floatBitsToInt(intBitsToFloat(Temp_int[9]) * intBitsToFloat(Temp_int[10]));
            //Instruction 103
            //MUL
            Temp_int[9] = floatBitsToInt(intBitsToFloat(Temp_int[9]) * immediateConstBufferF(int(Temp_int[2].w)));
            //Instruction 104
            //MAD
            Temp_int[4] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[9]) * intBitsToFloat(Temp_int[0]).zzzz + intBitsToFloat(Temp_int[4])));
            //Instruction 105
            //IF
            if((_ParamsPS.bUseNormals)!=0){
                //Instruction 106
                //IF
                if((_ParamsPS.b10_1)!=0){
                    //Instruction 107
                    //GATHER4
                    Temp_int[9] = floatBitsToInt(textureGather(g_txNormalsZ, intBitsToFloat(Temp_int[3]).xy));
                    //Instruction 108
                    //GATHER4
                    Temp_int[10] = floatBitsToInt(textureGather(g_txNormalsZ, intBitsToFloat(Temp_int[3]).zw));
                    //Instruction 109
                //ELSE
                } else {
                    //Instruction 110
                    //SAMPLE_L
                    Temp_int[9].x = floatBitsToInt(textureLodOffset(g_txNormals, intBitsToFloat(Temp_int[5]).zw, 0.000000, ivec2(0, 1))).x;
                    //Instruction 111
                    //SAMPLE_L
                    Temp_int[9].y = floatBitsToInt(textureLodOffset(g_txNormals, intBitsToFloat(Temp_int[5]).zw, 0.000000, ivec2(1, 1)).yxzw).y;
                    //Instruction 112
                    //SAMPLE_L
                    Temp_int[9].z = floatBitsToInt(textureLodOffset(g_txNormals, intBitsToFloat(Temp_int[5]).zw, 0.000000, ivec2(1, 0)).yzxw).z;
                    //Instruction 113
                    //SAMPLE_L
                    Temp_int[9].w = floatBitsToInt(textureLodOffset(g_txNormals, intBitsToFloat(Temp_int[5]).zw, 0.000000, ivec2(0, 0)).yzwx).w;
                    //Instruction 114
                    //SAMPLE_L
                    Temp_int[10].x = floatBitsToInt(textureLodOffset(g_txNormals, intBitsToFloat(Temp_int[6]).xy, 0.000000, ivec2(0, 1))).x;
                    //Instruction 115
                    //SAMPLE_L
                    Temp_int[10].y = floatBitsToInt(textureLodOffset(g_txNormals, intBitsToFloat(Temp_int[6]).xy, 0.000000, ivec2(1, 1)).yxzw).y;
                    //Instruction 116
                    //SAMPLE_L
                    Temp_int[10].z = floatBitsToInt(textureLodOffset(g_txNormals, intBitsToFloat(Temp_int[6]).xy, 0.000000, ivec2(1, 0)).yzxw).z;
                    //Instruction 117
                    //SAMPLE_L
                    Temp_int[10].w = floatBitsToInt(textureLodOffset(g_txNormals, intBitsToFloat(Temp_int[6]).xy, 0.000000, ivec2(0, 0)).yzwx).w;
                    //Instruction 118
                //ENDIF
                }
                //Instruction 119
                //MAD
                Temp_int[5] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[9]) * cb0PS.g_fNormalScale + intBitsToFloat(Temp_int[7])));
                //Instruction 120
                //MAD
                Temp_int[6] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[10]).zwxy * cb0PS.g_fNormalScale + intBitsToFloat(Temp_int[8]).zwxy));
                //Instruction 121
                //ADD
                Temp_int[5] = floatBitsToInt(intBitsToFloat(Temp_int[2]).zzzz + -intBitsToFloat(Temp_int[5]));
                //Instruction 122
                //LT
                Temp_int[7] = floatBitsToInt(ivec4(lessThan(vec4(intBitsToFloat(Temp_int[5])).xyzw, vec4(cb0PS.g_fHDAORejectRadius).xyzw)) * int(0xFFFFFFFF));
                //Instruction 123
                //AND
                Temp_int[7] = (Temp_int[7] & ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000));
                //Instruction 124
                //LT
                Temp_int[5] = floatBitsToInt(ivec4(lessThan(vec4(cb0PS.g_fHDAOAcceptRadius).xyzw, vec4(intBitsToFloat(Temp_int[5])).xyzw)) * int(0xFFFFFFFF));
                //Instruction 125
                //AND
                Temp_int[5] = (Temp_int[5] & ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000));
                //Instruction 126
                //MUL
                Temp_int[5] = floatBitsToInt(intBitsToFloat(Temp_int[5]) * intBitsToFloat(Temp_int[7]));
                //Instruction 127
                //ADD
                Temp_int[6] = floatBitsToInt(intBitsToFloat(Temp_int[2]).zzzz + -intBitsToFloat(Temp_int[6]));
                //Instruction 128
                //LT
                Temp_int[7] = floatBitsToInt(ivec4(lessThan(vec4(intBitsToFloat(Temp_int[6])).xyzw, vec4(cb0PS.g_fHDAORejectRadius).xyzw)) * int(0xFFFFFFFF));
                //Instruction 129
                //AND
                Temp_int[7] = (Temp_int[7] & ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000));
                //Instruction 130
                //LT
                Temp_int[6] = floatBitsToInt(ivec4(lessThan(vec4(cb0PS.g_fHDAOAcceptRadius).xyzw, vec4(intBitsToFloat(Temp_int[6])).xyzw)) * int(0xFFFFFFFF));
                //Instruction 131
                //AND
                Temp_int[6] = (Temp_int[6] & ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000));
                //Instruction 132
                //MUL
                Temp_int[6] = floatBitsToInt(intBitsToFloat(Temp_int[6]) * intBitsToFloat(Temp_int[7]));
                //Instruction 133
                //MUL
                Temp_int[5] = floatBitsToInt(intBitsToFloat(Temp_int[5]) * intBitsToFloat(Temp_int[6]));
                //Instruction 134
                //MUL
                Temp_int[5] = floatBitsToInt(intBitsToFloat(Temp_int[5]) * immediateConstBufferF(int(Temp_int[2].w)));
                //Instruction 135
                //MAD
                Temp_int[4] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[5]) * intBitsToFloat(Temp_int[0]).zzzz + intBitsToFloat(Temp_int[4])));
                //Instruction 136
            //ENDIF
            }
            //Instruction 137
            //IADD
            Temp_int[2].w = (Temp_int[2].w + int(0x1));
            //Instruction 138
        //ENDLOOP
        }
        //Instruction 139
    //ELSE
    } else {
        //Instruction 140
        //MOV
        Temp_int[4] = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xyzw;
        //Instruction 141
    //ENDIF
    }
    //Instruction 142
    //IF
    if((_ParamsPS.bUseNormals)!=0){
        //Instruction 143
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[4]).y + intBitsToFloat(Temp_int[4]).x);
        //Instruction 144
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[0]).x);
        //Instruction 145
        //ADD
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[0]).x);
        //Instruction 146
        //IADD
        Temp_int[0].y = (_ParamsPS.iNumRings + int(0xFFFFFFFF));
        //Instruction 147
        //MUL
        Temp_int[0].y = floatBitsToInt(3.000000 * immediateConstBufferF(int(Temp_int[0].y)).x);
        //Instruction 148
        //DIV
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x / intBitsToFloat(Temp_int[0]).y);
        //Instruction 149
    //ELSE
    } else {
        //Instruction 150
        //ADD
        Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[4]).y + intBitsToFloat(Temp_int[4]).x);
        //Instruction 151
        //ADD
        Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[0]).y);
        //Instruction 152
        //ADD
        Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[0]).y);
        //Instruction 153
        //IADD
        Temp_int[0].z = (_ParamsPS.iNumRings + int(0xFFFFFFFF));
        //Instruction 154
        //ADD
        Temp_int[0].z = floatBitsToInt(immediateConstBufferF(int(Temp_int[0].z)).x + immediateConstBufferF(int(Temp_int[0].z)).x);
        //Instruction 155
        //DIV
        Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).y / intBitsToFloat(Temp_int[0]).z);
        //Instruction 156
    //ENDIF
    }
    //Instruction 157
    //MUL
    Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x * cb0PS.g_fHDAOIntensity);
    Temp_int[0].x = floatBitsToInt(clamp(intBitsToFloat(Temp_int[0]).x, 0, 1));
    //Instruction 158
    //ADD
    Output0.x = (-intBitsToFloat(Temp_int[0]).x + 1.000000);
    //Instruction 159
    //RET
    return;
}
