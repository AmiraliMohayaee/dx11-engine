struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float2 Texture : TEXCOORD0;
	float4 LightViewPos : TEXCOORD1;
};

// Using the shadowmap from the first pass
Texture2D shadowmap : register ( t0 );
//Texture2D shaderTexture : register ( t1 );

//----------
// Creating Sampler
//----------
// Clamp sampler used for sampling the depth buffer for shadowmap for
// sampling correct information
SamplerState SamplerSamClamp : register ( s1 );
//SamplerState SamplerSamWrap : register ( s2 );


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

	float bias;	// Biasing values used to aquire softer edges
	float4 color;
	float depthVal;	
	float lightDepthVal;
	float2 projectedTextureCoords;	// For calculating texture coords
	float4 textureColor;

	// Ensuring that w in vector pos is always 1 for correct matrix
	// calculation
	input.Pos.w = 1;

	// Setting Bias
	bias = 1000.0;

	projectedTextureCoords.x = ((input.LightViewPos.x / input.LightViewPos.w) * 0.5f) + 0.5f;
	projectedTextureCoords.y = ((-input.LightViewPos.y / input.LightViewPos.w) * 0.5f) + 0.5f;

	// Sampling the depthvalue of the depthmap
	depthVal = shadowmap.Sample(SamplerSamClamp, projectedTextureCoords).r;

	lightDepthVal = input.LightViewPos.z / input.LightViewPos.w;

	//lightDepthVal = lightDepthVal - bias;

	color = float4(1.0, 1.0, 1.0, 1.0);

	if (lightDepthVal < depthVal)
	{
		color = float4(0.1, 0.1, 0.1, 1.0);
	}

	//textureColor = shadowmap.Sample(SamplerSamWrap, input.Texture);

	//color = color * textureColor;

	//PixelOutput.Color = textureColor;

	PixelOutput.Color = color;

	return PixelOutput;
}