struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float2 Texture : TEXCOORD0;
};

// Using the shadowmap from the first pass
Texture2D shadowmap : register ( t0 );
//Texture2D depthmap : register ( t1 );

//----------
// Creating Sampler
//----------
// Clamp sampler used for sampling the depth buffer for shadowmap for
// sampling correct information
SamplerState SamplerSamClamp : register ( s1 );
SamplerState SamplerSamWrap : register ( s2 );

struct PS_OUTPUT
{
	float4 Color : SV_TARGET;
};


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
PS_OUTPUT PS( PS_INPUT input)
{
	PS_OUTPUT PixelOutput = (PS_OUTPUT)0;

	// Ensuring that w in vector pos is always 1 for correct matrix
	// calculation
	input.Pos.w = 1;

	float4 textureColor;

	textureColor = shadowmap.Sample(SamplerSamClamp, input.Texture);

	PixelOutput.Color = textureColor;

	//return textureColor;

	return PixelOutput;
	
//	return float4(1, 0, 0, 1);
}