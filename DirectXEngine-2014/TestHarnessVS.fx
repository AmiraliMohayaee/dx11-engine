cbuffer WPM : register( b0 )
{
    matrix View;
	matrix World;
	matrix Proj;
};

cbuffer LightBuff : register ( b1 )
{
	matrix LightView;
	matrix LightProj;
	float3 LightPos;
	float padding;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float2 Texture : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float2 Texture : TEXCOORD0;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
	// Setting up the view proj matrix from main camera POV
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Proj );
	output.Color = input.Color;
	output.Texture = input.Texture;
    
    return output;
}