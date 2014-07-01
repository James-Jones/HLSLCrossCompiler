#version 400
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
subroutine void SubroutineType();
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
	vec4 g_f4x4WorldViewProjection[4];
	vec4 g_f4x4WorldViewProjLight[4];
	vec4 g_vShadowMapDimensions;
	vec4 g_f4LightDir;
	float g_fSunWidth;
	vec3 g_f3Padding;
} cbConstantsPS;
uniform sampler2D g_txScene;
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
    Temp_int[0].xyz = floatBitsToInt(Input3.xyzx / Input3.wwww).xyz;
    //Instruction 1
    //MAD
    Temp_int[1].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).xyxx * vec4(0.500000, 0.500000, 0.000000, 0.000000) + vec4(0.500000, 0.500000, 0.000000, 0.000000))).xy;
    //Instruction 2
    //ADD
    Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).z + -0.005000);
    //Instruction 3
    //ADD
    Temp_int[1].z = floatBitsToInt(-intBitsToFloat(Temp_int[1]).y + 1.000000);
    //Instruction 4
    //MAD
    Temp_int[0].yz = floatBitsToInt(vec4(cbConstantsPS.g_vShadowMapDimensions.xxyx * intBitsToFloat(Temp_int[1]).xxzx + vec4(0.000000, 0.500000, 0.500000, 0.000000))).yz;
    //Instruction 5
    //ROUND_NI
    Temp_int[1].yw = (ivec4(floor(intBitsToFloat(Temp_int[0]).yyyz)).yw);
    //Instruction 6
    //ADD
    Temp_int[0].yz = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyzy + -intBitsToFloat(Temp_int[1]).yywy).yz;
    //Instruction 7
    //MAD
    Temp_int[1].xy = floatBitsToInt(vec4(-intBitsToFloat(Temp_int[0]).yzyy * cbConstantsPS.g_vShadowMapDimensions.zwzz + intBitsToFloat(Temp_int[1]).xzxx)).xy;
    //Instruction 8
    //MOV
    Temp_int[1].zw = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).zw;
    //Instruction 9
    //MOV
    Temp_int[2].y = ivec4(int(0xFFFFFFFB)).y;
    //Instruction 10
    //LOOP
    while(true){
        //Instruction 11
        //ILT
        Temp_int[0].w = (((int(0x5))< (Temp_int[2].y)) ? int(0xFFFFFFFF) : 0);
        //Instruction 12
        //BREAKC
        if((Temp_int[0].w)!=0){break;}
        //Instruction 13
        //MOV
        Temp_int[2].zw = ivec4(Temp_int[1].zzzw).zw;
        //Instruction 14
        //MOV
        Temp_int[2].x = ivec4(int(0xFFFFFFFB)).x;
        //Instruction 15
        //LOOP
        while(true){
            //Instruction 16
            //ILT
            Temp_int[0].w = (((int(0x5))< (Temp_int[2].x)) ? int(0xFFFFFFFF) : 0);
            //Instruction 17
            //BREAKC
            if((Temp_int[0].w)!=0){break;}
            //Instruction 18
            //GATHER4_PO
            Temp_int[3] = floatBitsToInt(textureGatherOffset(g_txShadowMap, Temp_int[1].xy, ivec2(Temp_int[2].xy)));
            //Instruction 19
            //GE
            Temp_int[4] = floatBitsToInt(ivec4(greaterThanEqual(vec4(Temp_int[3]).xyzw, vec4(Temp_int[0].xxxx).xyzw)) * int(0xFFFFFFFF));
            //Instruction 20
            //MOVC
            if(Temp_int[4].x != 0) {
                Temp_int[4].x=(ivec4(0x0, 0x0, 0x0, 0x0).x);
            } else {
                Temp_int[4].x=(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000).x);
            }
            if(Temp_int[4].y != 0) {
                Temp_int[4].y=(ivec4(0x0, 0x0, 0x0, 0x0).y);
            } else {
                Temp_int[4].y=(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000).y);
            }
            if(Temp_int[4].z != 0) {
                Temp_int[4].z=(ivec4(0x0, 0x0, 0x0, 0x0).z);
            } else {
                Temp_int[4].z=(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000).z);
            }
            if(Temp_int[4].w != 0) {
                Temp_int[4].w=(ivec4(0x0, 0x0, 0x0, 0x0).w);
            } else {
                Temp_int[4].w=(ivec4(0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000).w);
            }
            //Instruction 21
            //DP4
            Temp_int[0].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[4]), vec4(1.000000, 1.000000, 1.000000, 1.000000))).w);
            //Instruction 22
            //ADD
            Temp_int[2].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[2]).w);
            //Instruction 23
            //DP4
            Temp_int[0].w = floatBitsToInt(vec4(dot(intBitsToFloat(Temp_int[3]), intBitsToFloat(Temp_int[4]))).w);
            //Instruction 24
            //ADD
            Temp_int[2].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[2]).z);
            //Instruction 25
            //IADD
            Temp_int[2].x = (Temp_int[2].x + int(0x2));
            //Instruction 26
        //ENDLOOP
        }
        //Instruction 27
        //MOV
        Temp_int[1].zw = ivec4(Temp_int[2].zzzw).zw;
        //Instruction 28
        //IADD
        Temp_int[2].y = (Temp_int[2].y + int(0x2));
        //Instruction 29
    //ENDLOOP
    }
    //Instruction 30
    //LT
    Temp_int[0].w = floatBitsToInt(((0.000000)< (intBitsToFloat(Temp_int[1]).w)) ? int(0xFFFFFFFF) : 0);
    //Instruction 31
    //DIV
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).z / intBitsToFloat(Temp_int[1]).w);
    //Instruction 32
    //ADD
    Temp_int[1].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).x + -intBitsToFloat(Temp_int[1]).z);
    //Instruction 33
    //MUL
    Temp_int[1].w = floatBitsToInt(intBitsToFloat(Temp_int[1]).w * cbConstantsPS.g_fSunWidth);
    //Instruction 34
    //DIV
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).w / intBitsToFloat(Temp_int[1]).z);
    Temp_int[1].z = floatBitsToInt(clamp(intBitsToFloat(Temp_int[1]).z, 0, 1));
    //Instruction 35
    //MUL
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * intBitsToFloat(Temp_int[1]).z);
    //Instruction 36
    //AND
    Temp_int[0].w = Temp_int[0].w & Temp_int[1].z;
    //Instruction 37
    //MUL
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * intBitsToFloat(Temp_int[0]).w);
    //Instruction 38
    //MUL
    Temp_int[1].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * intBitsToFloat(Temp_int[1]).z);
    //Instruction 39
    //MUL
    Temp_int[2].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * 3.000000);
    //Instruction 40
    //ADD
    Temp_int[2].y = floatBitsToInt(-intBitsToFloat(Temp_int[0]).w + 1.000000);
    //Instruction 41
    //MUL
    Temp_int[2].zw = floatBitsToInt(intBitsToFloat(Temp_int[2]).yyyy * intBitsToFloat(Temp_int[2]).xxxy).zw;
    //Instruction 42
    //MUL
    Temp_int[3].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).w * intBitsToFloat(Temp_int[2]).w);
    //Instruction 43
    //MUL
    Temp_int[3].yz = floatBitsToInt(intBitsToFloat(Temp_int[3]).xxxx * vec4(0.000000, 3.000000, 0.600000, 0.000000)).yz;
    //Instruction 44
    //MUL
    Temp_int[3].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).y * intBitsToFloat(Temp_int[2]).w);
    //Instruction 45
    //MOV
    Temp_int[4].xy = ivec4(ivec4(0x0, 0x0, 0x0, 0x0)).xy;
    //Instruction 46
    //LOOP
    while(true){
        //Instruction 47
        //IGE
        Temp_int[4].z = (((Temp_int[4].x)>= (int(0xB))) ? int(0xFFFFFFFF) : 0);
        //Instruction 48
        //BREAKC
        if((Temp_int[4].z)!=0){break;}
        //Instruction 49
        //MAD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[4]).y);
        //Instruction 50
        //IMUL
        Temp_int[4].w = (Temp_int[4].x * int(0xB));
        //Instruction 51
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[1]).w);
        //Instruction 52
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[5]).x);
        //Instruction 53
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * immediateConstBufferF(int(Temp_int[4].w)).y + intBitsToFloat(Temp_int[1]).w);
        //Instruction 54
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[5]).x);
        //Instruction 55
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[5]).x);
        //Instruction 56
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * immediateConstBufferF(int(Temp_int[4].w)).y + intBitsToFloat(Temp_int[1]).w);
        //Instruction 57
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[5]).x);
        //Instruction 58
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[5]).x);
        //Instruction 59
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).w * immediateConstBufferF(int(Temp_int[4].w)).z + intBitsToFloat(Temp_int[1]).w);
        //Instruction 60
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * immediateConstBufferF(int(Temp_int[4].w)).y + intBitsToFloat(Temp_int[5]).x);
        //Instruction 61
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[5]).x);
        //Instruction 62
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[5]).x);
        //Instruction 63
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).w * immediateConstBufferF(int(Temp_int[4].w)).z + intBitsToFloat(Temp_int[1]).w);
        //Instruction 64
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * immediateConstBufferF(int(Temp_int[4].w)).y + intBitsToFloat(Temp_int[5]).x);
        //Instruction 65
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[5]).x);
        //Instruction 66
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[5]).x);
        //Instruction 67
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).w * immediateConstBufferF(int(Temp_int[4].w)).z + intBitsToFloat(Temp_int[1]).w);
        //Instruction 68
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * immediateConstBufferF(int(Temp_int[4].w)).y + intBitsToFloat(Temp_int[5]).x);
        //Instruction 69
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[5]).x);
        //Instruction 70
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[5]).x);
        //Instruction 71
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * immediateConstBufferF(int(Temp_int[4].w)).y + intBitsToFloat(Temp_int[1]).w);
        //Instruction 72
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[5]).x);
        //Instruction 73
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[5]).x);
        //Instruction 74
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).y * immediateConstBufferF(int(Temp_int[4].w)).y + intBitsToFloat(Temp_int[1]).w);
        //Instruction 75
        //MAD
        Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[5]).x);
        //Instruction 76
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).z + intBitsToFloat(Temp_int[5]).x);
        //Instruction 77
        //MAD
        Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * immediateConstBufferF(int(Temp_int[4].w)).x + intBitsToFloat(Temp_int[1]).w);
        //Instruction 78
        //ADD
        Temp_int[4].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[4]).z);
        //Instruction 79
        //MAD
        Temp_int[4].y = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[4]).z);
        //Instruction 80
        //IADD
        Temp_int[4].x = (Temp_int[4].x + int(0x1));
        //Instruction 81
    //ENDLOOP
    }
    //Instruction 82
    //GATHER4_C
    Temp_int[5] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 83
    //ADD
    Temp_int[4].x = floatBitsToInt(-intBitsToFloat(Temp_int[0]).z + 1.000000);
    //Instruction 84
    //MAD
    Temp_int[4].z = floatBitsToInt(-intBitsToFloat(Temp_int[1]).w * intBitsToFloat(Temp_int[0]).y + intBitsToFloat(Temp_int[1]).w);
    //Instruction 85
    //MUL
    Temp_int[5].xw = floatBitsToInt(intBitsToFloat(Temp_int[4]).zzzz * intBitsToFloat(Temp_int[5]).wwwx).xw;
    //Instruction 86
    //MAD
    Temp_int[5].xz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[5]).zzyz * intBitsToFloat(Temp_int[1]).wwww + intBitsToFloat(Temp_int[5]).xxwx)).xz;
    //Instruction 87
    //MUL
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).z);
    //Instruction 88
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 89
    //GATHER4_C
    Temp_int[6] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 90
    //DP2
    Temp_int[5].x = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[6]).wzww).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).x);
    //Instruction 91
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 92
    //DP2
    Temp_int[5].x = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[6]).xyxx).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).x);
    //Instruction 93
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 94
    //GATHER4_C
    Temp_int[7] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 95
    //DP2
    Temp_int[5].x = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[7]).wzww).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).x);
    //Instruction 96
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 97
    //DP2
    Temp_int[5].x = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[7]).xyxx).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).x);
    //Instruction 98
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 99
    //GATHER4_C
    Temp_int[8] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 100
    //DP2
    Temp_int[5].x = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[8]).wzww).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).x);
    //Instruction 101
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 102
    //DP2
    Temp_int[5].x = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[8]).xyxx).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).x);
    //Instruction 103
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 104
    //GATHER4_C
    Temp_int[9] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 105
    //DP2
    Temp_int[5].x = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[9]).wzww).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).x);
    //Instruction 106
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 107
    //DP2
    Temp_int[5].x = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[9]).xyxx).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).x);
    //Instruction 108
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[4]).w);
    //Instruction 109
    //GATHER4_C
    Temp_int[10] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 110
    //MUL
    Temp_int[5].xz = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyyy * intBitsToFloat(Temp_int[10]).zzyz).xz;
    //Instruction 111
    //MUL
    Temp_int[5].xz = floatBitsToInt(intBitsToFloat(Temp_int[1]).wwww * intBitsToFloat(Temp_int[5]).xxzx).xz;
    //Instruction 112
    //MAD
    Temp_int[6].zw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[10]).wwwx * intBitsToFloat(Temp_int[1]).wwww + intBitsToFloat(Temp_int[5]).xxxz)).zw;
    //Instruction 113
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).z + intBitsToFloat(Temp_int[4]).w);
    //Instruction 114
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[4]).w);
    //Instruction 115
    //GATHER4_C
    Temp_int[11] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 116
    //MUL
    Temp_int[2].z = floatBitsToInt(intBitsToFloat(Temp_int[2]).z * 0.200000);
    //Instruction 117
    //MAD
    Temp_int[5].x = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[2]).z);
    //Instruction 118
    //MAD
    Temp_int[6].z = floatBitsToInt(intBitsToFloat(Temp_int[1]).z * intBitsToFloat(Temp_int[0]).w + -intBitsToFloat(Temp_int[5]).x);
    //Instruction 119
    //MAD
    Temp_int[6].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[6]).z + intBitsToFloat(Temp_int[5]).x);
    //Instruction 120
    //MUL
    Temp_int[7].zw = floatBitsToInt(intBitsToFloat(Temp_int[6]).zzzz * intBitsToFloat(Temp_int[11]).yyyz).zw;
    //Instruction 121
    //MAD
    Temp_int[7].zw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[11]).xxxw * intBitsToFloat(Temp_int[4]).zzzz + intBitsToFloat(Temp_int[7]).zzzw)).zw;
    //Instruction 122
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[7]).w + intBitsToFloat(Temp_int[4]).w);
    //Instruction 123
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[7]).z + intBitsToFloat(Temp_int[4]).w);
    //Instruction 124
    //MAD
    Temp_int[5].y = floatBitsToInt(intBitsToFloat(Temp_int[5]).y * intBitsToFloat(Temp_int[6]).z + intBitsToFloat(Temp_int[5]).w);
    //Instruction 125
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).y + intBitsToFloat(Temp_int[4]).w);
    //Instruction 126
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[7]).w + intBitsToFloat(Temp_int[4]).w);
    //Instruction 127
    //GATHER4_C
    Temp_int[11] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 128
    //MAD
    Temp_int[3].yz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[1]).zzzz * intBitsToFloat(Temp_int[0]).wwww + intBitsToFloat(Temp_int[3]).yyzy)).yz;
    //Instruction 129
    //MAD
    Temp_int[3].yz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[2]).xxxx * intBitsToFloat(Temp_int[2]).yyyy + intBitsToFloat(Temp_int[3]).yyzy)).yz;
    //Instruction 130
    //ADD
    Temp_int[0].w = floatBitsToInt(-intBitsToFloat(Temp_int[3]).z + intBitsToFloat(Temp_int[5]).x);
    //Instruction 131
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[0]).w + intBitsToFloat(Temp_int[3]).z);
    //Instruction 132
    //MUL
    Temp_int[5].yw = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[11]).wwwx).yw;
    //Instruction 133
    //MAD
    Temp_int[8].zw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[11]).zzzy * intBitsToFloat(Temp_int[3]).zzzz + intBitsToFloat(Temp_int[5]).yyyw)).zw;
    //Instruction 134
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[8]).z + intBitsToFloat(Temp_int[4]).w);
    //Instruction 135
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[8]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 136
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[6]).xyxx).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).w);
    //Instruction 137
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 138
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[11]).wzww).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).w);
    //Instruction 139
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 140
    //GATHER4_C
    Temp_int[12] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 141
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[12]).wzww).xy, (intBitsToFloat(Temp_int[3]).zzzz).xy)).w);
    //Instruction 142
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 143
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[12]).xyxx).xy, (intBitsToFloat(Temp_int[3]).zzzz).xy)).w);
    //Instruction 144
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 145
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[7]).xyxx).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).w);
    //Instruction 146
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 147
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[12]).wzww).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).w);
    //Instruction 148
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 149
    //GATHER4_C
    Temp_int[13] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 150
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[13]).wzww).xy, (intBitsToFloat(Temp_int[3]).zzzz).xy)).w);
    //Instruction 151
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 152
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[13]).xyxx).xy, (intBitsToFloat(Temp_int[3]).zzzz).xy)).w);
    //Instruction 153
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 154
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[8]).xyxx).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).w);
    //Instruction 155
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 156
    //DP2
    Temp_int[4].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[13]).wzww).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).w);
    //Instruction 157
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 158
    //GATHER4_C
    Temp_int[8] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 159
    //ADD
    Temp_int[4].w = floatBitsToInt(-intBitsToFloat(Temp_int[5]).x + intBitsToFloat(Temp_int[3]).z);
    //Instruction 160
    //MAD
    Temp_int[4].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[4]).w + intBitsToFloat(Temp_int[5]).x);
    //Instruction 161
    //MUL
    Temp_int[6].xy = floatBitsToInt(intBitsToFloat(Temp_int[4]).wwww * intBitsToFloat(Temp_int[8]).zyzz).xy;
    //Instruction 162
    //MAD
    Temp_int[6].xw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[8]).wwwx * intBitsToFloat(Temp_int[3]).zzzz + intBitsToFloat(Temp_int[6]).xxxy)).xw;
    //Instruction 163
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 164
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 165
    //DP2
    Temp_int[5].y = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[9]).xyxx).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).y);
    //Instruction 166
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 167
    //DP2
    Temp_int[5].y = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[8]).wzww).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).y);
    //Instruction 168
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 169
    //GATHER4_C
    Temp_int[9] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 170
    //MAD
    Temp_int[2].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[2]).z + intBitsToFloat(Temp_int[1]).w);
    //Instruction 171
    //MUL
    Temp_int[6].xw = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyyy * intBitsToFloat(Temp_int[9]).yyyz).xw;
    //Instruction 172
    //MUL
    Temp_int[6].xw = floatBitsToInt(intBitsToFloat(Temp_int[1]).wwww * intBitsToFloat(Temp_int[6]).xxxw).xw;
    //Instruction 173
    //MAD
    Temp_int[6].xw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[9]).xxxw * intBitsToFloat(Temp_int[2]).zzzz + intBitsToFloat(Temp_int[6]).xxxw)).xw;
    //Instruction 174
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 175
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 176
    //MAD
    Temp_int[5].y = floatBitsToInt(intBitsToFloat(Temp_int[10]).x * intBitsToFloat(Temp_int[2]).z + intBitsToFloat(Temp_int[5]).z);
    //Instruction 177
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 178
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 179
    //GATHER4_C
    Temp_int[9] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 180
    //MUL
    Temp_int[5].yz = floatBitsToInt(intBitsToFloat(Temp_int[6]).zzzz * intBitsToFloat(Temp_int[9]).yyzy).yz;
    //Instruction 181
    //MAD
    Temp_int[5].yz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[9]).xxwx * intBitsToFloat(Temp_int[4]).zzzz + intBitsToFloat(Temp_int[5]).yyzy)).yz;
    //Instruction 182
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 183
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 184
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[7]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 185
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 186
    //GATHER4_C
    Temp_int[7] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 187
    //ADD
    Temp_int[8].yz = floatBitsToInt(-intBitsToFloat(Temp_int[3]).yyzy + intBitsToFloat(Temp_int[3]).zzyz).yz;
    //Instruction 188
    //MAD
    Temp_int[8].yz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).yyyy * intBitsToFloat(Temp_int[8]).yyzy + intBitsToFloat(Temp_int[3]).yyzy)).yz;
    //Instruction 189
    //MUL
    Temp_int[7].yz = floatBitsToInt(intBitsToFloat(Temp_int[7]).yyzy * intBitsToFloat(Temp_int[8]).yyyy).yz;
    //Instruction 190
    //MAD
    Temp_int[7].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[7]).xwxx * intBitsToFloat(Temp_int[0]).wwww + intBitsToFloat(Temp_int[7]).yzyy)).xy;
    //Instruction 191
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[7]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 192
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[7]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 193
    //MAD
    Temp_int[5].z = floatBitsToInt(intBitsToFloat(Temp_int[11]).y * intBitsToFloat(Temp_int[8]).y + intBitsToFloat(Temp_int[5]).w);
    //Instruction 194
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 195
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[7]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 196
    //GATHER4_C
    Temp_int[9] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 197
    //MAD
    Temp_int[3].w = floatBitsToInt(intBitsToFloat(Temp_int[3]).w * 0.800000 + intBitsToFloat(Temp_int[1]).w);
    //Instruction 198
    //MAD
    Temp_int[3].w = floatBitsToInt(intBitsToFloat(Temp_int[3]).x * 3.000000 + intBitsToFloat(Temp_int[3]).w);
    //Instruction 199
    //MAD
    Temp_int[3].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).x * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[3]).w);
    //Instruction 200
    //ADD
    Temp_int[5].z = floatBitsToInt(-intBitsToFloat(Temp_int[3]).w + intBitsToFloat(Temp_int[3]).y);
    //Instruction 201
    //MAD
    Temp_int[5].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[5]).z + intBitsToFloat(Temp_int[3]).w);
    //Instruction 202
    //MUL
    Temp_int[7].yz = floatBitsToInt(intBitsToFloat(Temp_int[5]).zzzz * intBitsToFloat(Temp_int[9]).wwxw).yz;
    //Instruction 203
    //MAD
    Temp_int[7].yw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[9]).zzzy * intBitsToFloat(Temp_int[3]).wwww + intBitsToFloat(Temp_int[7]).yyyz)).yw;
    //Instruction 204
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[7]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 205
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[7]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 206
    //DP2
    Temp_int[5].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[12]).xyxx).xy, (intBitsToFloat(Temp_int[3]).yyyy).xy)).w);
    //Instruction 207
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 208
    //DP2
    Temp_int[5].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[9]).wzww).xy, (intBitsToFloat(Temp_int[3]).yyyy).xy)).w);
    //Instruction 209
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 210
    //GATHER4_C
    Temp_int[10] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 211
    //ADD
    Temp_int[5].w = floatBitsToInt(-intBitsToFloat(Temp_int[3]).y + intBitsToFloat(Temp_int[3]).w);
    //Instruction 212
    //MAD
    Temp_int[5].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[5]).w + intBitsToFloat(Temp_int[3]).y);
    //Instruction 213
    //MUL
    Temp_int[7].yw = floatBitsToInt(intBitsToFloat(Temp_int[5]).wwww * intBitsToFloat(Temp_int[10]).zzzy).yw;
    //Instruction 214
    //MAD
    Temp_int[9].xz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[10]).wwxw * intBitsToFloat(Temp_int[3]).wwww + intBitsToFloat(Temp_int[7]).yywy)).xz;
    //Instruction 215
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[9]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 216
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[9]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 217
    //DP2
    Temp_int[6].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[13]).xyxx).xy, (intBitsToFloat(Temp_int[3]).yyyy).xy)).w);
    //Instruction 218
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 219
    //DP2
    Temp_int[6].w = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[10]).wzww).xy, (intBitsToFloat(Temp_int[3]).yyyy).xy)).w);
    //Instruction 220
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 221
    //GATHER4_C
    Temp_int[11] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 222
    //MUL
    Temp_int[9].xz = floatBitsToInt(intBitsToFloat(Temp_int[4]).wwww * intBitsToFloat(Temp_int[11]).yyzy).xz;
    //Instruction 223
    //MAD
    Temp_int[9].xz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[11]).xxwx * intBitsToFloat(Temp_int[8]).zzzz + intBitsToFloat(Temp_int[9]).xxzx)).xz;
    //Instruction 224
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[9]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 225
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[9]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 226
    //MAD
    Temp_int[6].y = floatBitsToInt(intBitsToFloat(Temp_int[8]).x * intBitsToFloat(Temp_int[8]).z + intBitsToFloat(Temp_int[6]).y);
    //Instruction 227
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 228
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[9]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 229
    //GATHER4_C
    Temp_int[11] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 230
    //MUL
    Temp_int[6].yw = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyyy * intBitsToFloat(Temp_int[11]).yyyz).yw;
    //Instruction 231
    //MUL
    Temp_int[6].yw = floatBitsToInt(intBitsToFloat(Temp_int[1]).wwww * intBitsToFloat(Temp_int[6]).yyyw).yw;
    //Instruction 232
    //MAD
    Temp_int[6].yw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[11]).xxxw * intBitsToFloat(Temp_int[2]).zzzz + intBitsToFloat(Temp_int[6]).yyyw)).yw;
    //Instruction 233
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 234
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 235
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 236
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 237
    //GATHER4_C
    Temp_int[11] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 238
    //MUL
    Temp_int[6].xw = floatBitsToInt(intBitsToFloat(Temp_int[6]).zzzz * intBitsToFloat(Temp_int[11]).yyyz).xw;
    //Instruction 239
    //MAD
    Temp_int[6].xw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[11]).xxxw * intBitsToFloat(Temp_int[4]).zzzz + intBitsToFloat(Temp_int[6]).xxxw)).xw;
    //Instruction 240
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 241
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 242
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 243
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[6]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 244
    //GATHER4_C
    Temp_int[11] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 245
    //MUL
    Temp_int[8].xw = floatBitsToInt(intBitsToFloat(Temp_int[8]).yyyy * intBitsToFloat(Temp_int[11]).yyyz).xw;
    //Instruction 246
    //MAD
    Temp_int[8].xw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[11]).xxxw * intBitsToFloat(Temp_int[0]).wwww + intBitsToFloat(Temp_int[8]).xxxw)).xw;
    //Instruction 247
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[8]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 248
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[8]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 249
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[7]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 250
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[8]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 251
    //GATHER4_C
    Temp_int[11] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 252
    //MUL
    Temp_int[5].yz = floatBitsToInt(intBitsToFloat(Temp_int[5]).zzzz * intBitsToFloat(Temp_int[11]).wwxw).yz;
    //Instruction 253
    //MAD
    Temp_int[7].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[11]).zyzz * intBitsToFloat(Temp_int[3]).wwww + intBitsToFloat(Temp_int[5]).yzyy)).xy;
    //Instruction 254
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[7]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 255
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[7]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 256
    //MAD
    Temp_int[2].w = floatBitsToInt(intBitsToFloat(Temp_int[2]).w * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[1]).w);
    //Instruction 257
    //MAD
    Temp_int[2].w = floatBitsToInt(intBitsToFloat(Temp_int[3]).x * 3.000000 + intBitsToFloat(Temp_int[2]).w);
    //Instruction 258
    //MAD
    Temp_int[2].x = floatBitsToInt(intBitsToFloat(Temp_int[2]).x * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[2]).w);
    //Instruction 259
    //ADD
    Temp_int[2].y = floatBitsToInt(-intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[3]).w);
    //Instruction 260
    //MAD
    Temp_int[2].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[2]).x);
    //Instruction 261
    //MAD
    Temp_int[2].w = floatBitsToInt(intBitsToFloat(Temp_int[9]).y * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[7]).z);
    //Instruction 262
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 263
    //MAD
    Temp_int[2].y = floatBitsToInt(intBitsToFloat(Temp_int[11]).z * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[5]).y);
    //Instruction 264
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 265
    //GATHER4_C
    Temp_int[12] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 266
    //MUL
    Temp_int[2].yw = floatBitsToInt(intBitsToFloat(Temp_int[5]).wwww * intBitsToFloat(Temp_int[12]).zzzy).yw;
    //Instruction 267
    //MAD
    Temp_int[5].yz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[12]).wwxw * intBitsToFloat(Temp_int[3]).wwww + intBitsToFloat(Temp_int[2]).yywy)).yz;
    //Instruction 268
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 269
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 270
    //ADD
    Temp_int[2].x = floatBitsToInt(-intBitsToFloat(Temp_int[3]).w + intBitsToFloat(Temp_int[2]).x);
    //Instruction 271
    //MAD
    Temp_int[2].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).y * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[3]).w);
    //Instruction 272
    //MAD
    Temp_int[2].w = floatBitsToInt(intBitsToFloat(Temp_int[10]).x * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[7]).w);
    //Instruction 273
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 274
    //MAD
    Temp_int[2].x = floatBitsToInt(intBitsToFloat(Temp_int[12]).w * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[2]).y);
    //Instruction 275
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 276
    //GATHER4_C
    Temp_int[7] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 277
    //MUL
    Temp_int[2].xy = floatBitsToInt(intBitsToFloat(Temp_int[4]).wwww * intBitsToFloat(Temp_int[7]).yzyy).xy;
    //Instruction 278
    //MAD
    Temp_int[2].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[7]).xwxx * intBitsToFloat(Temp_int[8]).zzzz + intBitsToFloat(Temp_int[2]).xyxx)).xy;
    //Instruction 279
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 280
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 281
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[9]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 282
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 283
    //GATHER4_C
    Temp_int[7] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 284
    //MUL
    Temp_int[2].yw = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyyy * intBitsToFloat(Temp_int[7]).yyyz).yw;
    //Instruction 285
    //MUL
    Temp_int[2].yw = floatBitsToInt(intBitsToFloat(Temp_int[1]).wwww * intBitsToFloat(Temp_int[2]).yyyw).yw;
    //Instruction 286
    //MAD
    Temp_int[2].yw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[7]).xxxw * intBitsToFloat(Temp_int[2]).zzzz + intBitsToFloat(Temp_int[2]).yyyw)).yw;
    //Instruction 287
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 288
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 289
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).y + intBitsToFloat(Temp_int[1]).z);
    //Instruction 290
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 291
    //GATHER4_C
    Temp_int[7] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 292
    //MUL
    Temp_int[3].xw = floatBitsToInt(intBitsToFloat(Temp_int[6]).zzzz * intBitsToFloat(Temp_int[7]).yyyz).xw;
    //Instruction 293
    //MAD
    Temp_int[3].xw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[7]).xxxw * intBitsToFloat(Temp_int[4]).zzzz + intBitsToFloat(Temp_int[3]).xxxw)).xw;
    //Instruction 294
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[3]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 295
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[3]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 296
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[6]).x + intBitsToFloat(Temp_int[1]).z);
    //Instruction 297
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[3]).w + intBitsToFloat(Temp_int[1]).z);
    //Instruction 298
    //GATHER4_C
    Temp_int[7] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 299
    //MUL
    Temp_int[5].yz = floatBitsToInt(intBitsToFloat(Temp_int[0]).wwww * intBitsToFloat(Temp_int[7]).wwxw).yz;
    //Instruction 300
    //MAD
    Temp_int[5].zw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[7]).zzzy * intBitsToFloat(Temp_int[3]).zzzz + intBitsToFloat(Temp_int[5]).yyyz)).zw;
    //Instruction 301
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[5]).z + intBitsToFloat(Temp_int[1]).z);
    //Instruction 302
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[5]).w + intBitsToFloat(Temp_int[0]).w);
    //Instruction 303
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[8]).x + intBitsToFloat(Temp_int[0]).w);
    //Instruction 304
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[7]).z * intBitsToFloat(Temp_int[8]).y + intBitsToFloat(Temp_int[5]).y);
    //Instruction 305
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 306
    //GATHER4_C
    Temp_int[9] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 307
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[9]).wzww).xy, (intBitsToFloat(Temp_int[3]).zzzz).xy)).z);
    //Instruction 308
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 309
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[9]).xyxx).xy, (intBitsToFloat(Temp_int[3]).zzzz).xy)).z);
    //Instruction 310
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 311
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[11]).xyxx).xy, (intBitsToFloat(Temp_int[3]).yyyy).xy)).z);
    //Instruction 312
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 313
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[9]).wzww).xy, (intBitsToFloat(Temp_int[3]).yyyy).xy)).z);
    //Instruction 314
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 315
    //GATHER4_C
    Temp_int[10] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 316
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[10]).wzww).xy, (intBitsToFloat(Temp_int[3]).zzzz).xy)).z);
    //Instruction 317
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 318
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[10]).xyxx).xy, (intBitsToFloat(Temp_int[3]).zzzz).xy)).z);
    //Instruction 319
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 320
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[12]).xyxx).xy, (intBitsToFloat(Temp_int[3]).yyyy).xy)).z);
    //Instruction 321
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 322
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[10]).wzww).xy, (intBitsToFloat(Temp_int[3]).yyyy).xy)).z);
    //Instruction 323
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 324
    //GATHER4_C
    Temp_int[11] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 325
    //MUL
    Temp_int[3].yw = floatBitsToInt(intBitsToFloat(Temp_int[4]).wwww * intBitsToFloat(Temp_int[11]).zzzy).yw;
    //Instruction 326
    //MAD
    Temp_int[3].zw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[11]).wwwx * intBitsToFloat(Temp_int[3]).zzzz + intBitsToFloat(Temp_int[3]).yyyw)).zw;
    //Instruction 327
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[3]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 328
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[3]).w + intBitsToFloat(Temp_int[0]).w);
    //Instruction 329
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[0]).w);
    //Instruction 330
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[11]).w * intBitsToFloat(Temp_int[8]).z + intBitsToFloat(Temp_int[3]).y);
    //Instruction 331
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 332
    //GATHER4_C
    Temp_int[8] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 333
    //MUL
    Temp_int[2].xw = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyyy * intBitsToFloat(Temp_int[8]).yyyz).xw;
    //Instruction 334
    //MUL
    Temp_int[2].xw = floatBitsToInt(intBitsToFloat(Temp_int[1]).wwww * intBitsToFloat(Temp_int[2]).xxxw).xw;
    //Instruction 335
    //MAD
    Temp_int[2].xw = floatBitsToInt(vec4(intBitsToFloat(Temp_int[8]).xxxw * intBitsToFloat(Temp_int[2]).zzzz + intBitsToFloat(Temp_int[2]).xxxw)).xw;
    //Instruction 336
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[0]).w);
    //Instruction 337
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[0]).w);
    //Instruction 338
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[2]).y + intBitsToFloat(Temp_int[0]).w);
    //Instruction 339
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[2]).w + intBitsToFloat(Temp_int[0]).w);
    //Instruction 340
    //GATHER4_C
    Temp_int[8] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 341
    //MUL
    Temp_int[2].yw = floatBitsToInt(intBitsToFloat(Temp_int[4]).zzzz * intBitsToFloat(Temp_int[8]).wwwx).yw;
    //Instruction 342
    //MAD
    Temp_int[3].yz = floatBitsToInt(vec4(intBitsToFloat(Temp_int[8]).zzyz * intBitsToFloat(Temp_int[1]).wwww + intBitsToFloat(Temp_int[2]).yywy)).yz;
    //Instruction 343
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[3]).y + intBitsToFloat(Temp_int[0]).w);
    //Instruction 344
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[3]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 345
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[3]).x + intBitsToFloat(Temp_int[0]).w);
    //Instruction 346
    //MAD
    Temp_int[1].z = floatBitsToInt(intBitsToFloat(Temp_int[8]).z * intBitsToFloat(Temp_int[6]).z + intBitsToFloat(Temp_int[2]).y);
    //Instruction 347
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 348
    //GATHER4_C
    Temp_int[3] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 349
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).wzww).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).z);
    //Instruction 350
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 351
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).xyxx).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).z);
    //Instruction 352
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 353
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[7]).xyxx).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).z);
    //Instruction 354
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 355
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).wzww).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).z);
    //Instruction 356
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 357
    //GATHER4_C
    Temp_int[3] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 358
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).wzww).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).z);
    //Instruction 359
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 360
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).xyxx).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).z);
    //Instruction 361
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 362
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[9]).xyxx).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).z);
    //Instruction 363
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 364
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).wzww).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).z);
    //Instruction 365
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 366
    //GATHER4_C
    Temp_int[3] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 367
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).wzww).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).z);
    //Instruction 368
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 369
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).xyxx).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).z);
    //Instruction 370
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 371
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[10]).xyxx).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).z);
    //Instruction 372
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 373
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).wzww).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).z);
    //Instruction 374
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 375
    //GATHER4_C
    Temp_int[3] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 376
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).wzww).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).z);
    //Instruction 377
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 378
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).xyxx).xy, (intBitsToFloat(Temp_int[1]).wwww).xy)).z);
    //Instruction 379
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 380
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[11]).xyxx).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).z);
    //Instruction 381
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 382
    //DP2
    Temp_int[1].z = floatBitsToInt(ivec4(dot((intBitsToFloat(Temp_int[3]).wzww).xy, (intBitsToFloat(Temp_int[5]).xxxx).xy)).z);
    //Instruction 383
    //MAD
    Temp_int[0].w = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).z + intBitsToFloat(Temp_int[0]).w);
    //Instruction 384
    //GATHER4_C
    Temp_int[3] = floatBitsToInt(textureGather(hlslcc_zcmpg_txShadowMap, Temp_int[1].xy, Temp_int[0].x));
    //Instruction 385
    //MUL
    Temp_int[0].xy = floatBitsToInt(intBitsToFloat(Temp_int[0]).yyyy * intBitsToFloat(Temp_int[3]).zyzz).xy;
    //Instruction 386
    //MUL
    Temp_int[0].xy = floatBitsToInt(intBitsToFloat(Temp_int[1]).wwww * intBitsToFloat(Temp_int[0]).xyxx).xy;
    //Instruction 387
    //MAD
    Temp_int[1].xy = floatBitsToInt(vec4(intBitsToFloat(Temp_int[3]).wxww * intBitsToFloat(Temp_int[1]).wwww + intBitsToFloat(Temp_int[0]).xyxx)).xy;
    //Instruction 388
    //MAD
    Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[1]).x + intBitsToFloat(Temp_int[0]).w);
    //Instruction 389
    //MAD
    Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[1]).y + intBitsToFloat(Temp_int[0]).y);
    //Instruction 390
    //MAD
    Temp_int[0].y = floatBitsToInt(intBitsToFloat(Temp_int[4]).x * intBitsToFloat(Temp_int[2]).x + intBitsToFloat(Temp_int[0]).y);
    //Instruction 391
    //MAD
    Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[3]).w * intBitsToFloat(Temp_int[2]).z + intBitsToFloat(Temp_int[0]).x);
    //Instruction 392
    //MAD
    Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).z * intBitsToFloat(Temp_int[0]).x + intBitsToFloat(Temp_int[0]).y);
    //Instruction 393
    //DIV
    Temp_int[0].x = floatBitsToInt(intBitsToFloat(Temp_int[0]).x / intBitsToFloat(Temp_int[4]).y);
    //Instruction 394
    //MAD
    Temp_int[0] = floatBitsToInt(vec4(intBitsToFloat(Temp_int[0]).xxxx * Input1 + vec4(0.300000, 0.300000, 0.300000, 0.000000)));
    Temp_int[0] = floatBitsToInt(clamp(intBitsToFloat(Temp_int[0]), 0, 1));
    //Instruction 395
    //SAMPLE
    Temp_int[1] = floatBitsToInt(texture(g_txScene, Input2.xy));
    //Instruction 396
    //MUL
    Output0 = (intBitsToFloat(Temp_int[0]) * intBitsToFloat(Temp_int[1]));
    //Instruction 397
    //RET
    return;
}
