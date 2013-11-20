//--------------------------------------------------------------------------------------
// File: Tutorial06.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer SharedConsts
{
   matrix World;
   matrix View;
   matrix Projection;
   float4 vOutputColor;
   int ColorFactor;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
	float4 Color: COLOR0;
	int Factor : FACTOR;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT main( VS_INPUT input )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Norm = mul( input.Norm, World );
	output.Color = vOutputColor * ColorFactor;
	output.Factor = ColorFactor;
    
    return output;
}

