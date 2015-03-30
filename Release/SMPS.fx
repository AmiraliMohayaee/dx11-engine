struct PS_INPUT
{
    float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

struct PS_OUTPUT
{
	float4 Color : SV_TARGET;
};

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
PS_OUTPUT PS( PS_INPUT input)
//float4 PS( PS_INPUT input) : SV_Target
{
	PS_OUTPUT PixelOutput = (PS_OUTPUT)0;
	// Ensuring that w in vector pos is always 1
	input.Pos.w = 1;	// In x.y.z.w., the w is set to 1 by default

	PixelOutput.Color = float4(input.Pos.z, input.Pos.z, input.Pos.z, 1.0);	// Creating a depth buffer

	return PixelOutput;
}