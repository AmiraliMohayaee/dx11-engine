#pragma once

#include "Shader.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include <string>
#include "ConstantBuffer.h"
#include "WVPBuffer.h"
#include "ShaderResourceView.h"
#include "RenderTargetView.h"
#include "Sampler.h"


namespace DXEngine
{
	class TestShader : public Shader
	{
	public:
		bool Load(const std::string &FPVSfilename, const std::string &FPPSfilename);

		ID3DBlob* GetVSBlob() override;
		ID3DBlob* GetPSBlob() override;
		void SetAsCurrentShader() override;

		void UpdateWVP(const WVPBuffer& wvpb);

		// Passing the shadowmap from the shadowshader as a 
		// shader resource view to have access
		void SetShadowMapShaderResourceView(ShaderResourceView* texresview);


	private:
		PixelShader m_ps;
		VertexShader m_vs;
		Sampler m_sampler;

		WVPConstBuffer m_wvpb;

		ShaderResourceView* m_shaderResView;	// For accessing shadowmap

		SharedTexture m_sharedTex;
	};
}