#version 400
subroutine void SubroutineType();
#extension GL_ARB_shader_bit_encoding : require
#extension GL_ARB_gpu_shader5 : enable
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
#define immediateConstBufferF(idx) intBitsToFloat(immediateConstBufferInt[idx])
ivec4 immediateConstBufferInt[121] = ivec4[121] (
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 1061997773, 0), 
	ivec4(1065353216, 1065353216, 1061997773, 0), 
	ivec4(1065353216, 1065353216, 1061997773, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 1061997773, 0), 
	ivec4(1065353216, 1065353216, 1065353216, 0), 
	ivec4(1065353216, 1065353216, 1061997773, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 1061997773, 0), 
	ivec4(1065353216, 1065353216, 1061997773, 0), 
	ivec4(1065353216, 1065353216, 1061997773, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1065353216, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1065353216, 1045220557, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(1045220557, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0), 
	ivec4(0, 0, 0, 0)
);
uniform struct cbConstantsPS_Type {
	mat4 g_f4x4WorldViewProjection;
	mat4 g_f4x4WorldViewProjLight;
	vec4 g_vShadowMapDimensions;
	vec4 g_f4LightDir;
	float g_fSunWidth;
	vec3 g_f3Padding;
} cbConstantsPS;
uniform sampler2D g_txScene_X_g_SampleLinear;
uniform sampler2D g_txScene;
uniform sampler2DShadow hlslcc_zcmpg_txShadowMap_X_g_SamplePoint;
uniform sampler2DShadow hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp;
uniform sampler2D g_txShadowMap_X_g_SamplePoint;
uniform sampler2D g_txShadowMap_X_g_SamplePointCmp;
uniform sampler2DShadow hlslcc_zcmpg_txShadowMap;
uniform sampler2D g_txShadowMap;
 in  vec4 VtxGeoOutput1;
vec4 Input1;
 in  vec4 VtxGeoOutput2;
vec4 Input2;
 in  vec4 VtxGeoOutput3;
vec4 Input3;
layout(location = 0) out  vec4 PixOutput0;
#define Output0 PixOutput0
vec4 Temp[14];
ivec4 Temp_int[14];
uvec4 Temp_uint[14];
void main()
{
    //--- Start Early Main ---
    Input1 = VtxGeoOutput1;
    Input2 = VtxGeoOutput2;
    Input3 = VtxGeoOutput3;
    //--- End Early Main ---
    //Instruction 0
    //DIV
    Temp[0].xyz = (Input3.xyzx / Input3.wwww).xyz;
    //Instruction 1
    //MAD
    Temp[1].xy = (vec4(Temp[0].xyxx * vec4(0.500000, 0.500000, 0.000000, 0.000000) + vec4(0.500000, 0.500000, 0.000000, 0.000000))).xy;
    //Instruction 2
    //ADD
    Temp[0].x = (Temp[0].z + -0.005000);
    //Instruction 3
    //ADD
    Temp[1].z = (-Temp[1].y + 1.000000);
    //Instruction 4
    //MAD
    Temp[0].yz = (vec4(cbConstantsPS.g_vShadowMapDimensions.xxyx * Temp[1].xxzx + vec4(0.000000, 0.500000, 0.500000, 0.000000))).yz;
    //Instruction 5
    //ROUND_NI
    Temp[1].yw = intBitsToFloat(ivec4(floor(Temp[0].yyyz)).yw);
    //Instruction 6
    //ADD
    Temp[0].yz = (Temp[0].yyzy + -Temp[1].yywy).yz;
    //Instruction 7
    //MAD
    Temp[1].xy = (vec4(-Temp[0].yzyy * cbConstantsPS.g_vShadowMapDimensions.zwzz + Temp[1].xzxx)).xy;
    //Instruction 8
    //MOV
    Temp[1].zw = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).zw;
    //Instruction 9
    //MOV
    Temp[2].y = vec4(intBitsToFloat(int(0xFFFFFFFB)));
    //Instruction 10
    //LOOP
    while(true){
        //Instruction 11
        //ILT
        Temp[0].w = uintBitsToFloat(((0x5)< (floatBitsToInt(Temp[2].y))) ? 0xFFFFFFFFu : 0u);
        //Instruction 12
        //BREAKC
        if((floatBitsToUint(Temp[0].w))!=0u){break;}
        //Instruction 13
        //MOV
        Temp[2].zw = vec4(Temp[1].zzzw).zw;
        //Instruction 14
        //MOV
        Temp[2].x = vec4(intBitsToFloat(int(0xFFFFFFFB)));
        //Instruction 15
        //LOOP
        while(true){
            //Instruction 16
            //ILT
            Temp[0].w = uintBitsToFloat(((0x5)< (floatBitsToInt(Temp[2].x))) ? 0xFFFFFFFFu : 0u);
            //Instruction 17
            //BREAKC
            if((floatBitsToUint(Temp[0].w))!=0u){break;}
            //Instruction 18
            //GATHER4_PO
            Temp[3] = (textureGatherOffset(g_txShadowMap_X_g_SamplePoint, Temp[1].xy, ivec2(Temp[2].xy)));
            //Instruction 19
            //GE
            Temp[4] = uintBitsToFloat(uvec4(greaterThanEqual(vec4(Temp[3]), vec4(Temp[0].xxxx))) * 0xFFFFFFFFu);
            //Instruction 20
            //MOVC
            if(floatBitsToInt(Temp[4].x) != 0) {
                Temp[4].x=(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0)).x);
            } else {
                Temp[4].x=(intBitsToFloat(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).x);
            }
            if(floatBitsToInt(Temp[4].y) != 0) {
                Temp[4].y=(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0)).y);
            } else {
                Temp[4].y=(intBitsToFloat(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).y);
            }
            if(floatBitsToInt(Temp[4].z) != 0) {
                Temp[4].z=(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0)).z);
            } else {
                Temp[4].z=(intBitsToFloat(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).z);
            }
            if(floatBitsToInt(Temp[4].w) != 0) {
                Temp[4].w=(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0)).w);
            } else {
                Temp[4].w=(intBitsToFloat(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000)).w);
            }
            //Instruction 21
            //DP4
            Temp[0].w = (vec4(dot(Temp[4], vec4(1.000000, 1.000000, 1.000000, 1.000000))).w);
            //Instruction 22
            //ADD
            Temp[2].w = (Temp[0].w + Temp[2].w);
            //Instruction 23
            //DP4
            Temp[0].w = (vec4(dot(Temp[3], Temp[4])).w);
            //Instruction 24
            //ADD
            Temp[2].z = (Temp[0].w + Temp[2].z);
            //Instruction 25
            //IADD
            Temp[2].x = intBitsToFloat(floatBitsToInt(Temp[2].x) + 0x2);
            //Instruction 26
        //ENDLOOP
        }
        //Instruction 27
        //MOV
        Temp[1].zw = vec4(Temp[2].zzzw).zw;
        //Instruction 28
        //IADD
        Temp[2].y = intBitsToFloat(floatBitsToInt(Temp[2].y) + 0x2);
        //Instruction 29
    //ENDLOOP
    }
    //Instruction 30
    //LT
    Temp[0].w = uintBitsToFloat(((0.000000)< (Temp[1].w)) ? 0xFFFFFFFFu : 0u);
    //Instruction 31
    //DIV
    Temp[1].z = (Temp[1].z / Temp[1].w);
    //Instruction 32
    //ADD
    Temp[1].w = (Temp[0].x + -Temp[1].z);
    //Instruction 33
    //MUL
    Temp[1].w = (Temp[1].w * cbConstantsPS.g_fSunWidth);
    //Instruction 34
    //DIV
    Temp[1].z = (Temp[1].w / Temp[1].z);
    Temp[1].z = (clamp(Temp[1].z, 0.0, 1.0));
    //Instruction 35
    //MUL
    Temp[1].z = (Temp[1].z * Temp[1].z);
    //Instruction 36
    //AND
    Temp[0].w = uintBitsToFloat(floatBitsToUint(Temp[0].w) & floatBitsToUint(Temp[1].z));
    //Instruction 37
    //MUL
    Temp[1].z = (Temp[0].w * Temp[0].w);
    //Instruction 38
    //MUL
    Temp[1].w = (Temp[0].w * Temp[1].z);
    //Instruction 39
    //MUL
    Temp[2].x = (Temp[1].z * 3.000000);
    //Instruction 40
    //ADD
    Temp[2].y = (-Temp[0].w + 1.000000);
    //Instruction 41
    //MUL
    Temp[2].zw = (Temp[2].yyyy * Temp[2].xxxy).zw;
    //Instruction 42
    //MUL
    Temp[3].x = (Temp[0].w * Temp[2].w);
    //Instruction 43
    //MUL
    Temp[3].yz = (Temp[3].xxxx * vec4(0.000000, 3.000000, 0.600000, 0.000000)).yz;
    //Instruction 44
    //MUL
    Temp[3].w = (Temp[2].y * Temp[2].w);
    //Instruction 45
    //MOV
    Temp[4].xy = vec4(intBitsToFloat(ivec4(0x0, 0x0, 0x0, 0x0))).xy;
    //Instruction 46
    //LOOP
    while(true){
        //Instruction 47
        //IGE
        // IGE+BREAKC opt
        if (((floatBitsToInt(Temp[4].x))>= (0xB))) { break; }
        Temp[4].z = uintBitsToFloat(((floatBitsToInt(Temp[4].x))>= (0xB)) ? 0xFFFFFFFFu : 0u);
        //Instruction 48
        //Instruction 49
        //MAD
        Temp[4].z = (Temp[1].z * Temp[0].w + Temp[4].y);
        //Instruction 50
        //IMUL
        Temp[4].w = intBitsToFloat(floatBitsToInt(Temp[4].x) * 0xB);
        //Instruction 51
        //MAD
        Temp[5].x = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[1].w);
        //Instruction 52
        //ADD
        Temp[4].z = (Temp[4].z + Temp[5].x);
        //Instruction 53
        //MAD
        Temp[5].x = (Temp[3].y * immediateConstBufferF(int(Temp[4].w)).y + Temp[1].w);
        //Instruction 54
        //MAD
        Temp[5].x = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[5].x);
        //Instruction 55
        //ADD
        Temp[4].z = (Temp[4].z + Temp[5].x);
        //Instruction 56
        //MAD
        Temp[5].x = (Temp[3].y * immediateConstBufferF(int(Temp[4].w)).y + Temp[1].w);
        //Instruction 57
        //MAD
        Temp[5].x = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[5].x);
        //Instruction 58
        //ADD
        Temp[4].z = (Temp[4].z + Temp[5].x);
        //Instruction 59
        //MAD
        Temp[5].x = (Temp[3].w * immediateConstBufferF(int(Temp[4].w)).z + Temp[1].w);
        //Instruction 60
        //MAD
        Temp[5].x = (Temp[3].y * immediateConstBufferF(int(Temp[4].w)).y + Temp[5].x);
        //Instruction 61
        //MAD
        Temp[5].x = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[5].x);
        //Instruction 62
        //ADD
        Temp[4].z = (Temp[4].z + Temp[5].x);
        //Instruction 63
        //MAD
        Temp[5].x = (Temp[3].w * immediateConstBufferF(int(Temp[4].w)).z + Temp[1].w);
        //Instruction 64
        //MAD
        Temp[5].x = (Temp[3].y * immediateConstBufferF(int(Temp[4].w)).y + Temp[5].x);
        //Instruction 65
        //MAD
        Temp[5].x = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[5].x);
        //Instruction 66
        //ADD
        Temp[4].z = (Temp[4].z + Temp[5].x);
        //Instruction 67
        //MAD
        Temp[5].x = (Temp[3].w * immediateConstBufferF(int(Temp[4].w)).z + Temp[1].w);
        //Instruction 68
        //MAD
        Temp[5].x = (Temp[3].y * immediateConstBufferF(int(Temp[4].w)).y + Temp[5].x);
        //Instruction 69
        //MAD
        Temp[5].x = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[5].x);
        //Instruction 70
        //ADD
        Temp[4].z = (Temp[4].z + Temp[5].x);
        //Instruction 71
        //MAD
        Temp[5].x = (Temp[3].y * immediateConstBufferF(int(Temp[4].w)).y + Temp[1].w);
        //Instruction 72
        //MAD
        Temp[5].x = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[5].x);
        //Instruction 73
        //ADD
        Temp[4].z = (Temp[4].z + Temp[5].x);
        //Instruction 74
        //MAD
        Temp[5].x = (Temp[3].y * immediateConstBufferF(int(Temp[4].w)).y + Temp[1].w);
        //Instruction 75
        //MAD
        Temp[5].x = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[5].x);
        //Instruction 76
        //ADD
        Temp[4].z = (Temp[4].z + Temp[5].x);
        //Instruction 77
        //MAD
        Temp[4].w = (Temp[2].z * immediateConstBufferF(int(Temp[4].w)).x + Temp[1].w);
        //Instruction 78
        //ADD
        Temp[4].z = (Temp[4].w + Temp[4].z);
        //Instruction 79
        //MAD
        Temp[4].y = (Temp[1].z * Temp[0].w + Temp[4].z);
        //Instruction 80
        //IADD
        Temp[4].x = intBitsToFloat(floatBitsToInt(Temp[4].x) + 0x1);
        //Instruction 81
    //ENDLOOP
    }
    //Instruction 82
    //GATHER4_C
    Temp[5] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 83
    //ADD
    Temp[4].x = (-Temp[0].z + 1.000000);
    //Instruction 84
    //MAD
    Temp[4].z = (-Temp[1].w * Temp[0].y + Temp[1].w);
    //Instruction 85
    //MUL
    Temp[5].xw = (Temp[4].zzzz * Temp[5].wwwx).xw;
    //Instruction 86
    //MAD
    Temp[5].xz = (vec4(Temp[5].zzyz * Temp[1].wwww + Temp[5].xxwx)).xz;
    //Instruction 87
    //MUL
    Temp[4].w = (Temp[0].z * Temp[5].z);
    //Instruction 88
    //MAD
    Temp[4].w = (Temp[4].x * Temp[5].x + Temp[4].w);
    //Instruction 89
    //GATHER4_C
    Temp[6] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 90
    //DP2
    Temp[5].x = (vec4(dot((Temp[6].wzww).xy, (Temp[1].wwww).xy)).x);
    //Instruction 91
    //MAD
    Temp[4].w = (Temp[4].x * Temp[5].x + Temp[4].w);
    //Instruction 92
    //DP2
    Temp[5].x = (vec4(dot((Temp[6].xyxx).xy, (Temp[1].wwww).xy)).x);
    //Instruction 93
    //MAD
    Temp[4].w = (Temp[0].z * Temp[5].x + Temp[4].w);
    //Instruction 94
    //GATHER4_C
    Temp[7] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 95
    //DP2
    Temp[5].x = (vec4(dot((Temp[7].wzww).xy, (Temp[1].wwww).xy)).x);
    //Instruction 96
    //MAD
    Temp[4].w = (Temp[4].x * Temp[5].x + Temp[4].w);
    //Instruction 97
    //DP2
    Temp[5].x = (vec4(dot((Temp[7].xyxx).xy, (Temp[1].wwww).xy)).x);
    //Instruction 98
    //MAD
    Temp[4].w = (Temp[0].z * Temp[5].x + Temp[4].w);
    //Instruction 99
    //GATHER4_C
    Temp[8] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 100
    //DP2
    Temp[5].x = (vec4(dot((Temp[8].wzww).xy, (Temp[1].wwww).xy)).x);
    //Instruction 101
    //MAD
    Temp[4].w = (Temp[4].x * Temp[5].x + Temp[4].w);
    //Instruction 102
    //DP2
    Temp[5].x = (vec4(dot((Temp[8].xyxx).xy, (Temp[1].wwww).xy)).x);
    //Instruction 103
    //MAD
    Temp[4].w = (Temp[0].z * Temp[5].x + Temp[4].w);
    //Instruction 104
    //GATHER4_C
    Temp[9] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 105
    //DP2
    Temp[5].x = (vec4(dot((Temp[9].wzww).xy, (Temp[1].wwww).xy)).x);
    //Instruction 106
    //MAD
    Temp[4].w = (Temp[4].x * Temp[5].x + Temp[4].w);
    //Instruction 107
    //DP2
    Temp[5].x = (vec4(dot((Temp[9].xyxx).xy, (Temp[1].wwww).xy)).x);
    //Instruction 108
    //MAD
    Temp[4].w = (Temp[0].z * Temp[5].x + Temp[4].w);
    //Instruction 109
    //GATHER4_C
    Temp[10] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 110
    //MUL
    Temp[5].xz = (Temp[0].yyyy * Temp[10].zzyz).xz;
    //Instruction 111
    //MUL
    Temp[5].xz = (Temp[1].wwww * Temp[5].xxzx).xz;
    //Instruction 112
    //MAD
    Temp[6].zw = (vec4(Temp[10].wwwx * Temp[1].wwww + Temp[5].xxxz)).zw;
    //Instruction 113
    //MAD
    Temp[4].w = (Temp[4].x * Temp[6].z + Temp[4].w);
    //Instruction 114
    //MAD
    Temp[4].w = (Temp[0].z * Temp[6].w + Temp[4].w);
    //Instruction 115
    //GATHER4_C
    Temp[11] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 116
    //MUL
    Temp[2].z = (Temp[2].z * 0.200000);
    //Instruction 117
    //MAD
    Temp[5].x = (Temp[1].z * Temp[0].w + Temp[2].z);
    //Instruction 118
    //MAD
    Temp[6].z = (Temp[1].z * Temp[0].w + -Temp[5].x);
    //Instruction 119
    //MAD
    Temp[6].z = (Temp[0].y * Temp[6].z + Temp[5].x);
    //Instruction 120
    //MUL
    Temp[7].zw = (Temp[6].zzzz * Temp[11].yyyz).zw;
    //Instruction 121
    //MAD
    Temp[7].zw = (vec4(Temp[11].xxxw * Temp[4].zzzz + Temp[7].zzzw)).zw;
    //Instruction 122
    //MAD
    Temp[4].w = (Temp[4].x * Temp[7].w + Temp[4].w);
    //Instruction 123
    //MAD
    Temp[4].w = (Temp[0].z * Temp[7].z + Temp[4].w);
    //Instruction 124
    //MAD
    Temp[5].y = (Temp[5].y * Temp[6].z + Temp[5].w);
    //Instruction 125
    //MAD
    Temp[4].w = (Temp[4].x * Temp[5].y + Temp[4].w);
    //Instruction 126
    //MAD
    Temp[4].w = (Temp[0].z * Temp[7].w + Temp[4].w);
    //Instruction 127
    //GATHER4_C
    Temp[11] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 128
    //MAD
    Temp[3].yz = (vec4(Temp[1].zzzz * Temp[0].wwww + Temp[3].yyzy)).yz;
    //Instruction 129
    //MAD
    Temp[3].yz = (vec4(Temp[2].xxxx * Temp[2].yyyy + Temp[3].yyzy)).yz;
    //Instruction 130
    //ADD
    Temp[0].w = (-Temp[3].z + Temp[5].x);
    //Instruction 131
    //MAD
    Temp[0].w = (Temp[0].y * Temp[0].w + Temp[3].z);
    //Instruction 132
    //MUL
    Temp[5].yw = (Temp[0].wwww * Temp[11].wwwx).yw;
    //Instruction 133
    //MAD
    Temp[8].zw = (vec4(Temp[11].zzzy * Temp[3].zzzz + Temp[5].yyyw)).zw;
    //Instruction 134
    //MAD
    Temp[1].z = (Temp[4].x * Temp[8].z + Temp[4].w);
    //Instruction 135
    //MAD
    Temp[1].z = (Temp[0].z * Temp[8].w + Temp[1].z);
    //Instruction 136
    //DP2
    Temp[4].w = (vec4(dot((Temp[6].xyxx).xy, (Temp[5].xxxx).xy)).w);
    //Instruction 137
    //MAD
    Temp[1].z = (Temp[4].x * Temp[4].w + Temp[1].z);
    //Instruction 138
    //DP2
    Temp[4].w = (vec4(dot((Temp[11].wzww).xy, (Temp[5].xxxx).xy)).w);
    //Instruction 139
    //MAD
    Temp[1].z = (Temp[0].z * Temp[4].w + Temp[1].z);
    //Instruction 140
    //GATHER4_C
    Temp[12] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 141
    //DP2
    Temp[4].w = (vec4(dot((Temp[12].wzww).xy, (Temp[3].zzzz).xy)).w);
    //Instruction 142
    //MAD
    Temp[1].z = (Temp[4].x * Temp[4].w + Temp[1].z);
    //Instruction 143
    //DP2
    Temp[4].w = (vec4(dot((Temp[12].xyxx).xy, (Temp[3].zzzz).xy)).w);
    //Instruction 144
    //MAD
    Temp[1].z = (Temp[0].z * Temp[4].w + Temp[1].z);
    //Instruction 145
    //DP2
    Temp[4].w = (vec4(dot((Temp[7].xyxx).xy, (Temp[5].xxxx).xy)).w);
    //Instruction 146
    //MAD
    Temp[1].z = (Temp[4].x * Temp[4].w + Temp[1].z);
    //Instruction 147
    //DP2
    Temp[4].w = (vec4(dot((Temp[12].wzww).xy, (Temp[5].xxxx).xy)).w);
    //Instruction 148
    //MAD
    Temp[1].z = (Temp[0].z * Temp[4].w + Temp[1].z);
    //Instruction 149
    //GATHER4_C
    Temp[13] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 150
    //DP2
    Temp[4].w = (vec4(dot((Temp[13].wzww).xy, (Temp[3].zzzz).xy)).w);
    //Instruction 151
    //MAD
    Temp[1].z = (Temp[4].x * Temp[4].w + Temp[1].z);
    //Instruction 152
    //DP2
    Temp[4].w = (vec4(dot((Temp[13].xyxx).xy, (Temp[3].zzzz).xy)).w);
    //Instruction 153
    //MAD
    Temp[1].z = (Temp[0].z * Temp[4].w + Temp[1].z);
    //Instruction 154
    //DP2
    Temp[4].w = (vec4(dot((Temp[8].xyxx).xy, (Temp[5].xxxx).xy)).w);
    //Instruction 155
    //MAD
    Temp[1].z = (Temp[4].x * Temp[4].w + Temp[1].z);
    //Instruction 156
    //DP2
    Temp[4].w = (vec4(dot((Temp[13].wzww).xy, (Temp[5].xxxx).xy)).w);
    //Instruction 157
    //MAD
    Temp[1].z = (Temp[0].z * Temp[4].w + Temp[1].z);
    //Instruction 158
    //GATHER4_C
    Temp[8] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 159
    //ADD
    Temp[4].w = (-Temp[5].x + Temp[3].z);
    //Instruction 160
    //MAD
    Temp[4].w = (Temp[0].y * Temp[4].w + Temp[5].x);
    //Instruction 161
    //MUL
    Temp[6].xy = (Temp[4].wwww * Temp[8].zyzz).xy;
    //Instruction 162
    //MAD
    Temp[6].xw = (vec4(Temp[8].wwwx * Temp[3].zzzz + Temp[6].xxxy)).xw;
    //Instruction 163
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].x + Temp[1].z);
    //Instruction 164
    //MAD
    Temp[1].z = (Temp[0].z * Temp[6].w + Temp[1].z);
    //Instruction 165
    //DP2
    Temp[5].y = (vec4(dot((Temp[9].xyxx).xy, (Temp[5].xxxx).xy)).y);
    //Instruction 166
    //MAD
    Temp[1].z = (Temp[4].x * Temp[5].y + Temp[1].z);
    //Instruction 167
    //DP2
    Temp[5].y = (vec4(dot((Temp[8].wzww).xy, (Temp[5].xxxx).xy)).y);
    //Instruction 168
    //MAD
    Temp[1].z = (Temp[0].z * Temp[5].y + Temp[1].z);
    //Instruction 169
    //GATHER4_C
    Temp[9] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 170
    //MAD
    Temp[2].z = (Temp[0].y * Temp[2].z + Temp[1].w);
    //Instruction 171
    //MUL
    Temp[6].xw = (Temp[0].yyyy * Temp[9].yyyz).xw;
    //Instruction 172
    //MUL
    Temp[6].xw = (Temp[1].wwww * Temp[6].xxxw).xw;
    //Instruction 173
    //MAD
    Temp[6].xw = (vec4(Temp[9].xxxw * Temp[2].zzzz + Temp[6].xxxw)).xw;
    //Instruction 174
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].w + Temp[1].z);
    //Instruction 175
    //MAD
    Temp[1].z = (Temp[0].z * Temp[6].x + Temp[1].z);
    //Instruction 176
    //MAD
    Temp[5].y = (Temp[10].x * Temp[2].z + Temp[5].z);
    //Instruction 177
    //MAD
    Temp[1].z = (Temp[4].x * Temp[5].y + Temp[1].z);
    //Instruction 178
    //MAD
    Temp[1].z = (Temp[0].z * Temp[6].w + Temp[1].z);
    //Instruction 179
    //GATHER4_C
    Temp[9] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 180
    //MUL
    Temp[5].yz = (Temp[6].zzzz * Temp[9].yyzy).yz;
    //Instruction 181
    //MAD
    Temp[5].yz = (vec4(Temp[9].xxwx * Temp[4].zzzz + Temp[5].yyzy)).yz;
    //Instruction 182
    //MAD
    Temp[1].z = (Temp[4].x * Temp[5].z + Temp[1].z);
    //Instruction 183
    //MAD
    Temp[1].z = (Temp[0].z * Temp[5].y + Temp[1].z);
    //Instruction 184
    //MAD
    Temp[1].z = (Temp[4].x * Temp[7].z + Temp[1].z);
    //Instruction 185
    //MAD
    Temp[1].z = (Temp[0].z * Temp[5].z + Temp[1].z);
    //Instruction 186
    //GATHER4_C
    Temp[7] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 187
    //ADD
    Temp[8].yz = (-Temp[3].yyzy + Temp[3].zzyz).yz;
    //Instruction 188
    //MAD
    Temp[8].yz = (vec4(Temp[0].yyyy * Temp[8].yyzy + Temp[3].yyzy)).yz;
    //Instruction 189
    //MUL
    Temp[7].yz = (Temp[7].yyzy * Temp[8].yyyy).yz;
    //Instruction 190
    //MAD
    Temp[7].xy = (vec4(Temp[7].xwxx * Temp[0].wwww + Temp[7].yzyy)).xy;
    //Instruction 191
    //MAD
    Temp[1].z = (Temp[4].x * Temp[7].y + Temp[1].z);
    //Instruction 192
    //MAD
    Temp[1].z = (Temp[0].z * Temp[7].x + Temp[1].z);
    //Instruction 193
    //MAD
    Temp[5].z = (Temp[11].y * Temp[8].y + Temp[5].w);
    //Instruction 194
    //MAD
    Temp[1].z = (Temp[4].x * Temp[5].z + Temp[1].z);
    //Instruction 195
    //MAD
    Temp[1].z = (Temp[0].z * Temp[7].y + Temp[1].z);
    //Instruction 196
    //GATHER4_C
    Temp[9] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 197
    //MAD
    Temp[3].w = (Temp[3].w * 0.800000 + Temp[1].w);
    //Instruction 198
    //MAD
    Temp[3].w = (Temp[3].x * 3.000000 + Temp[3].w);
    //Instruction 199
    //MAD
    Temp[3].w = (Temp[2].x * Temp[2].y + Temp[3].w);
    //Instruction 200
    //ADD
    Temp[5].z = (-Temp[3].w + Temp[3].y);
    //Instruction 201
    //MAD
    Temp[5].z = (Temp[0].y * Temp[5].z + Temp[3].w);
    //Instruction 202
    //MUL
    Temp[7].yz = (Temp[5].zzzz * Temp[9].wwxw).yz;
    //Instruction 203
    //MAD
    Temp[7].yw = (vec4(Temp[9].zzzy * Temp[3].wwww + Temp[7].yyyz)).yw;
    //Instruction 204
    //MAD
    Temp[1].z = (Temp[4].x * Temp[7].y + Temp[1].z);
    //Instruction 205
    //MAD
    Temp[1].z = (Temp[0].z * Temp[7].w + Temp[1].z);
    //Instruction 206
    //DP2
    Temp[5].w = (vec4(dot((Temp[12].xyxx).xy, (Temp[3].yyyy).xy)).w);
    //Instruction 207
    //MAD
    Temp[1].z = (Temp[4].x * Temp[5].w + Temp[1].z);
    //Instruction 208
    //DP2
    Temp[5].w = (vec4(dot((Temp[9].wzww).xy, (Temp[3].yyyy).xy)).w);
    //Instruction 209
    //MAD
    Temp[1].z = (Temp[0].z * Temp[5].w + Temp[1].z);
    //Instruction 210
    //GATHER4_C
    Temp[10] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 211
    //ADD
    Temp[5].w = (-Temp[3].y + Temp[3].w);
    //Instruction 212
    //MAD
    Temp[5].w = (Temp[0].y * Temp[5].w + Temp[3].y);
    //Instruction 213
    //MUL
    Temp[7].yw = (Temp[5].wwww * Temp[10].zzzy).yw;
    //Instruction 214
    //MAD
    Temp[9].xz = (vec4(Temp[10].wwxw * Temp[3].wwww + Temp[7].yywy)).xz;
    //Instruction 215
    //MAD
    Temp[1].z = (Temp[4].x * Temp[9].x + Temp[1].z);
    //Instruction 216
    //MAD
    Temp[1].z = (Temp[0].z * Temp[9].z + Temp[1].z);
    //Instruction 217
    //DP2
    Temp[6].w = (vec4(dot((Temp[13].xyxx).xy, (Temp[3].yyyy).xy)).w);
    //Instruction 218
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].w + Temp[1].z);
    //Instruction 219
    //DP2
    Temp[6].w = (vec4(dot((Temp[10].wzww).xy, (Temp[3].yyyy).xy)).w);
    //Instruction 220
    //MAD
    Temp[1].z = (Temp[0].z * Temp[6].w + Temp[1].z);
    //Instruction 221
    //GATHER4_C
    Temp[11] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 222
    //MUL
    Temp[9].xz = (Temp[4].wwww * Temp[11].yyzy).xz;
    //Instruction 223
    //MAD
    Temp[9].xz = (vec4(Temp[11].xxwx * Temp[8].zzzz + Temp[9].xxzx)).xz;
    //Instruction 224
    //MAD
    Temp[1].z = (Temp[4].x * Temp[9].z + Temp[1].z);
    //Instruction 225
    //MAD
    Temp[1].z = (Temp[0].z * Temp[9].x + Temp[1].z);
    //Instruction 226
    //MAD
    Temp[6].y = (Temp[8].x * Temp[8].z + Temp[6].y);
    //Instruction 227
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].y + Temp[1].z);
    //Instruction 228
    //MAD
    Temp[1].z = (Temp[0].z * Temp[9].z + Temp[1].z);
    //Instruction 229
    //GATHER4_C
    Temp[11] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 230
    //MUL
    Temp[6].yw = (Temp[0].yyyy * Temp[11].yyyz).yw;
    //Instruction 231
    //MUL
    Temp[6].yw = (Temp[1].wwww * Temp[6].yyyw).yw;
    //Instruction 232
    //MAD
    Temp[6].yw = (vec4(Temp[11].xxxw * Temp[2].zzzz + Temp[6].yyyw)).yw;
    //Instruction 233
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].w + Temp[1].z);
    //Instruction 234
    //MAD
    Temp[1].z = (Temp[0].z * Temp[6].y + Temp[1].z);
    //Instruction 235
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].x + Temp[1].z);
    //Instruction 236
    //MAD
    Temp[1].z = (Temp[0].z * Temp[6].w + Temp[1].z);
    //Instruction 237
    //GATHER4_C
    Temp[11] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 238
    //MUL
    Temp[6].xw = (Temp[6].zzzz * Temp[11].yyyz).xw;
    //Instruction 239
    //MAD
    Temp[6].xw = (vec4(Temp[11].xxxw * Temp[4].zzzz + Temp[6].xxxw)).xw;
    //Instruction 240
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].w + Temp[1].z);
    //Instruction 241
    //MAD
    Temp[1].z = (Temp[0].z * Temp[6].x + Temp[1].z);
    //Instruction 242
    //MAD
    Temp[1].z = (Temp[4].x * Temp[5].y + Temp[1].z);
    //Instruction 243
    //MAD
    Temp[1].z = (Temp[0].z * Temp[6].w + Temp[1].z);
    //Instruction 244
    //GATHER4_C
    Temp[11] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 245
    //MUL
    Temp[8].xw = (Temp[8].yyyy * Temp[11].yyyz).xw;
    //Instruction 246
    //MAD
    Temp[8].xw = (vec4(Temp[11].xxxw * Temp[0].wwww + Temp[8].xxxw)).xw;
    //Instruction 247
    //MAD
    Temp[1].z = (Temp[4].x * Temp[8].w + Temp[1].z);
    //Instruction 248
    //MAD
    Temp[1].z = (Temp[0].z * Temp[8].x + Temp[1].z);
    //Instruction 249
    //MAD
    Temp[1].z = (Temp[4].x * Temp[7].x + Temp[1].z);
    //Instruction 250
    //MAD
    Temp[1].z = (Temp[0].z * Temp[8].w + Temp[1].z);
    //Instruction 251
    //GATHER4_C
    Temp[11] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 252
    //MUL
    Temp[5].yz = (Temp[5].zzzz * Temp[11].wwxw).yz;
    //Instruction 253
    //MAD
    Temp[7].xy = (vec4(Temp[11].zyzz * Temp[3].wwww + Temp[5].yzyy)).xy;
    //Instruction 254
    //MAD
    Temp[1].z = (Temp[4].x * Temp[7].x + Temp[1].z);
    //Instruction 255
    //MAD
    Temp[1].z = (Temp[0].z * Temp[7].y + Temp[1].z);
    //Instruction 256
    //MAD
    Temp[2].w = (Temp[2].w * Temp[2].y + Temp[1].w);
    //Instruction 257
    //MAD
    Temp[2].w = (Temp[3].x * 3.000000 + Temp[2].w);
    //Instruction 258
    //MAD
    Temp[2].x = (Temp[2].x * Temp[2].y + Temp[2].w);
    //Instruction 259
    //ADD
    Temp[2].y = (-Temp[2].x + Temp[3].w);
    //Instruction 260
    //MAD
    Temp[2].y = (Temp[0].y * Temp[2].y + Temp[2].x);
    //Instruction 261
    //MAD
    Temp[2].w = (Temp[9].y * Temp[2].y + Temp[7].z);
    //Instruction 262
    //MAD
    Temp[1].z = (Temp[4].x * Temp[2].w + Temp[1].z);
    //Instruction 263
    //MAD
    Temp[2].y = (Temp[11].z * Temp[2].y + Temp[5].y);
    //Instruction 264
    //MAD
    Temp[1].z = (Temp[0].z * Temp[2].y + Temp[1].z);
    //Instruction 265
    //GATHER4_C
    Temp[12] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 266
    //MUL
    Temp[2].yw = (Temp[5].wwww * Temp[12].zzzy).yw;
    //Instruction 267
    //MAD
    Temp[5].yz = (vec4(Temp[12].wwxw * Temp[3].wwww + Temp[2].yywy)).yz;
    //Instruction 268
    //MAD
    Temp[1].z = (Temp[4].x * Temp[5].y + Temp[1].z);
    //Instruction 269
    //MAD
    Temp[1].z = (Temp[0].z * Temp[5].z + Temp[1].z);
    //Instruction 270
    //ADD
    Temp[2].x = (-Temp[3].w + Temp[2].x);
    //Instruction 271
    //MAD
    Temp[2].x = (Temp[0].y * Temp[2].x + Temp[3].w);
    //Instruction 272
    //MAD
    Temp[2].w = (Temp[10].x * Temp[2].x + Temp[7].w);
    //Instruction 273
    //MAD
    Temp[1].z = (Temp[4].x * Temp[2].w + Temp[1].z);
    //Instruction 274
    //MAD
    Temp[2].x = (Temp[12].w * Temp[2].x + Temp[2].y);
    //Instruction 275
    //MAD
    Temp[1].z = (Temp[0].z * Temp[2].x + Temp[1].z);
    //Instruction 276
    //GATHER4_C
    Temp[7] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 277
    //MUL
    Temp[2].xy = (Temp[4].wwww * Temp[7].yzyy).xy;
    //Instruction 278
    //MAD
    Temp[2].xy = (vec4(Temp[7].xwxx * Temp[8].zzzz + Temp[2].xyxx)).xy;
    //Instruction 279
    //MAD
    Temp[1].z = (Temp[4].x * Temp[2].y + Temp[1].z);
    //Instruction 280
    //MAD
    Temp[1].z = (Temp[0].z * Temp[2].x + Temp[1].z);
    //Instruction 281
    //MAD
    Temp[1].z = (Temp[4].x * Temp[9].x + Temp[1].z);
    //Instruction 282
    //MAD
    Temp[1].z = (Temp[0].z * Temp[2].y + Temp[1].z);
    //Instruction 283
    //GATHER4_C
    Temp[7] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 284
    //MUL
    Temp[2].yw = (Temp[0].yyyy * Temp[7].yyyz).yw;
    //Instruction 285
    //MUL
    Temp[2].yw = (Temp[1].wwww * Temp[2].yyyw).yw;
    //Instruction 286
    //MAD
    Temp[2].yw = (vec4(Temp[7].xxxw * Temp[2].zzzz + Temp[2].yyyw)).yw;
    //Instruction 287
    //MAD
    Temp[1].z = (Temp[4].x * Temp[2].w + Temp[1].z);
    //Instruction 288
    //MAD
    Temp[1].z = (Temp[0].z * Temp[2].y + Temp[1].z);
    //Instruction 289
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].y + Temp[1].z);
    //Instruction 290
    //MAD
    Temp[1].z = (Temp[0].z * Temp[2].w + Temp[1].z);
    //Instruction 291
    //GATHER4_C
    Temp[7] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 292
    //MUL
    Temp[3].xw = (Temp[6].zzzz * Temp[7].yyyz).xw;
    //Instruction 293
    //MAD
    Temp[3].xw = (vec4(Temp[7].xxxw * Temp[4].zzzz + Temp[3].xxxw)).xw;
    //Instruction 294
    //MAD
    Temp[1].z = (Temp[4].x * Temp[3].w + Temp[1].z);
    //Instruction 295
    //MAD
    Temp[1].z = (Temp[0].z * Temp[3].x + Temp[1].z);
    //Instruction 296
    //MAD
    Temp[1].z = (Temp[4].x * Temp[6].x + Temp[1].z);
    //Instruction 297
    //MAD
    Temp[1].z = (Temp[0].z * Temp[3].w + Temp[1].z);
    //Instruction 298
    //GATHER4_C
    Temp[7] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 299
    //MUL
    Temp[5].yz = (Temp[0].wwww * Temp[7].wwxw).yz;
    //Instruction 300
    //MAD
    Temp[5].zw = (vec4(Temp[7].zzzy * Temp[3].zzzz + Temp[5].yyyz)).zw;
    //Instruction 301
    //MAD
    Temp[0].w = (Temp[4].x * Temp[5].z + Temp[1].z);
    //Instruction 302
    //MAD
    Temp[0].w = (Temp[0].z * Temp[5].w + Temp[0].w);
    //Instruction 303
    //MAD
    Temp[0].w = (Temp[4].x * Temp[8].x + Temp[0].w);
    //Instruction 304
    //MAD
    Temp[1].z = (Temp[7].z * Temp[8].y + Temp[5].y);
    //Instruction 305
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 306
    //GATHER4_C
    Temp[9] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 307
    //DP2
    Temp[1].z = (vec4(dot((Temp[9].wzww).xy, (Temp[3].zzzz).xy)).z);
    //Instruction 308
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 309
    //DP2
    Temp[1].z = (vec4(dot((Temp[9].xyxx).xy, (Temp[3].zzzz).xy)).z);
    //Instruction 310
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 311
    //DP2
    Temp[1].z = (vec4(dot((Temp[11].xyxx).xy, (Temp[3].yyyy).xy)).z);
    //Instruction 312
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 313
    //DP2
    Temp[1].z = (vec4(dot((Temp[9].wzww).xy, (Temp[3].yyyy).xy)).z);
    //Instruction 314
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 315
    //GATHER4_C
    Temp[10] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 316
    //DP2
    Temp[1].z = (vec4(dot((Temp[10].wzww).xy, (Temp[3].zzzz).xy)).z);
    //Instruction 317
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 318
    //DP2
    Temp[1].z = (vec4(dot((Temp[10].xyxx).xy, (Temp[3].zzzz).xy)).z);
    //Instruction 319
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 320
    //DP2
    Temp[1].z = (vec4(dot((Temp[12].xyxx).xy, (Temp[3].yyyy).xy)).z);
    //Instruction 321
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 322
    //DP2
    Temp[1].z = (vec4(dot((Temp[10].wzww).xy, (Temp[3].yyyy).xy)).z);
    //Instruction 323
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 324
    //GATHER4_C
    Temp[11] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 325
    //MUL
    Temp[3].yw = (Temp[4].wwww * Temp[11].zzzy).yw;
    //Instruction 326
    //MAD
    Temp[3].zw = (vec4(Temp[11].wwwx * Temp[3].zzzz + Temp[3].yyyw)).zw;
    //Instruction 327
    //MAD
    Temp[0].w = (Temp[4].x * Temp[3].z + Temp[0].w);
    //Instruction 328
    //MAD
    Temp[0].w = (Temp[0].z * Temp[3].w + Temp[0].w);
    //Instruction 329
    //MAD
    Temp[0].w = (Temp[4].x * Temp[2].x + Temp[0].w);
    //Instruction 330
    //MAD
    Temp[1].z = (Temp[11].w * Temp[8].z + Temp[3].y);
    //Instruction 331
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 332
    //GATHER4_C
    Temp[8] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 333
    //MUL
    Temp[2].xw = (Temp[0].yyyy * Temp[8].yyyz).xw;
    //Instruction 334
    //MUL
    Temp[2].xw = (Temp[1].wwww * Temp[2].xxxw).xw;
    //Instruction 335
    //MAD
    Temp[2].xw = (vec4(Temp[8].xxxw * Temp[2].zzzz + Temp[2].xxxw)).xw;
    //Instruction 336
    //MAD
    Temp[0].w = (Temp[4].x * Temp[2].w + Temp[0].w);
    //Instruction 337
    //MAD
    Temp[0].w = (Temp[0].z * Temp[2].x + Temp[0].w);
    //Instruction 338
    //MAD
    Temp[0].w = (Temp[4].x * Temp[2].y + Temp[0].w);
    //Instruction 339
    //MAD
    Temp[0].w = (Temp[0].z * Temp[2].w + Temp[0].w);
    //Instruction 340
    //GATHER4_C
    Temp[8] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 341
    //MUL
    Temp[2].yw = (Temp[4].zzzz * Temp[8].wwwx).yw;
    //Instruction 342
    //MAD
    Temp[3].yz = (vec4(Temp[8].zzyz * Temp[1].wwww + Temp[2].yywy)).yz;
    //Instruction 343
    //MAD
    Temp[0].w = (Temp[4].x * Temp[3].y + Temp[0].w);
    //Instruction 344
    //MAD
    Temp[0].w = (Temp[0].z * Temp[3].z + Temp[0].w);
    //Instruction 345
    //MAD
    Temp[0].w = (Temp[4].x * Temp[3].x + Temp[0].w);
    //Instruction 346
    //MAD
    Temp[1].z = (Temp[8].z * Temp[6].z + Temp[2].y);
    //Instruction 347
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 348
    //GATHER4_C
    Temp[3] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 349
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].wzww).xy, (Temp[1].wwww).xy)).z);
    //Instruction 350
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 351
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].xyxx).xy, (Temp[1].wwww).xy)).z);
    //Instruction 352
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 353
    //DP2
    Temp[1].z = (vec4(dot((Temp[7].xyxx).xy, (Temp[5].xxxx).xy)).z);
    //Instruction 354
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 355
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].wzww).xy, (Temp[5].xxxx).xy)).z);
    //Instruction 356
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 357
    //GATHER4_C
    Temp[3] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 358
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].wzww).xy, (Temp[1].wwww).xy)).z);
    //Instruction 359
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 360
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].xyxx).xy, (Temp[1].wwww).xy)).z);
    //Instruction 361
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 362
    //DP2
    Temp[1].z = (vec4(dot((Temp[9].xyxx).xy, (Temp[5].xxxx).xy)).z);
    //Instruction 363
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 364
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].wzww).xy, (Temp[5].xxxx).xy)).z);
    //Instruction 365
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 366
    //GATHER4_C
    Temp[3] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 367
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].wzww).xy, (Temp[1].wwww).xy)).z);
    //Instruction 368
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 369
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].xyxx).xy, (Temp[1].wwww).xy)).z);
    //Instruction 370
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 371
    //DP2
    Temp[1].z = (vec4(dot((Temp[10].xyxx).xy, (Temp[5].xxxx).xy)).z);
    //Instruction 372
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 373
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].wzww).xy, (Temp[5].xxxx).xy)).z);
    //Instruction 374
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 375
    //GATHER4_C
    Temp[3] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 376
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].wzww).xy, (Temp[1].wwww).xy)).z);
    //Instruction 377
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 378
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].xyxx).xy, (Temp[1].wwww).xy)).z);
    //Instruction 379
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 380
    //DP2
    Temp[1].z = (vec4(dot((Temp[11].xyxx).xy, (Temp[5].xxxx).xy)).z);
    //Instruction 381
    //MAD
    Temp[0].w = (Temp[4].x * Temp[1].z + Temp[0].w);
    //Instruction 382
    //DP2
    Temp[1].z = (vec4(dot((Temp[3].wzww).xy, (Temp[5].xxxx).xy)).z);
    //Instruction 383
    //MAD
    Temp[0].w = (Temp[0].z * Temp[1].z + Temp[0].w);
    //Instruction 384
    //GATHER4_C
    Temp[3] = (textureGather(hlslcc_zcmpg_txShadowMap_X_g_SamplePointCmp, Temp[1].xy, Temp[0].x));
    //Instruction 385
    //MUL
    Temp[0].xy = (Temp[0].yyyy * Temp[3].zyzz).xy;
    //Instruction 386
    //MUL
    Temp[0].xy = (Temp[1].wwww * Temp[0].xyxx).xy;
    //Instruction 387
    //MAD
    Temp[1].xy = (vec4(Temp[3].wxww * Temp[1].wwww + Temp[0].xyxx)).xy;
    //Instruction 388
    //MAD
    Temp[0].y = (Temp[4].x * Temp[1].x + Temp[0].w);
    //Instruction 389
    //MAD
    Temp[0].y = (Temp[0].z * Temp[1].y + Temp[0].y);
    //Instruction 390
    //MAD
    Temp[0].y = (Temp[4].x * Temp[2].x + Temp[0].y);
    //Instruction 391
    //MAD
    Temp[0].x = (Temp[3].w * Temp[2].z + Temp[0].x);
    //Instruction 392
    //MAD
    Temp[0].x = (Temp[0].z * Temp[0].x + Temp[0].y);
    //Instruction 393
    //DIV
    Temp[0].x = (Temp[0].x / Temp[4].y);
    //Instruction 394
    //MAD
    Temp[0] = (vec4(Temp[0].xxxx * Input1 + vec4(0.300000, 0.300000, 0.300000, 0.000000)));
    Temp[0] = (clamp(Temp[0], 0.0, 1.0));
    //Instruction 395
    //SAMPLE
    Temp[1] = (texture(g_txScene_X_g_SampleLinear, Input2.xy));
    //Instruction 396
    //MUL
    Output0 = (Temp[0] * Temp[1]);
    //Instruction 397
    //RET
    return;
}
