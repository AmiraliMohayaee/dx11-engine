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
	float4 LightViewPos : TEXCOORD1;
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
	output.Normal = mul( input.Normal, World );	// Updating normals
	
	// Finding the pixel pos in relation to the light's pov
	output.LightViewPos = mul( input.Pos, World );
	output.LightViewPos = mul( output.LightViewPos, LightView );
	output.LightViewPos = mul( output.LightViewPos, LightProj );

	output.Color = input.Color;
	output.Texture = input.Texture;

    return output;
}