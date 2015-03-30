#pragma once

#include "Shader.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include <string>
#include "ConstantBuffer.h"
#include "WVPBuffer.h"
#include "LightBuffer.h"
#include "ShaderResourceView.h"
#include "RenderTargetView.h"
#include "Sampler.h"
#include "Light.h"


namespace DXEngine
{
	class ShadowMapShader : public Shader
	{
	public:
		bool Load(const std::string &FPVSfilename, const std::string &FPPSfilename,
			const std::string &SPVSfilename, const std::string &SPPSfilename);

		ID3DBlob* GetVSBlob() override;
		ID3DBlob* GetPSBlob() override;
		void SetAsCurrentShader() override;

		ShaderResourceView* GetShadowMapShader();

		void UpdateWVP(const WVPBuffer& wvpb);
		void UpdateLight(const LightBuffer& lightBuffer);
		void SetLight(Light *light);

		// First and second passes
		void FirstPassBegin();
		void FirstPassEnd();

		void SecondPassBegin();
		void SecondPassEnd();


	private:
		PixelShader m_ps;
		VertexShader m_vs;
		PixelShader m_spps;
		VertexShader m_spvs;
		Sampler m_sampler;

		WVPConstBuffer m_wvpb;
		LightConstBuffer m_lightBuffer;
		Light* m_light;

		RenderTargetView m_renderTargetView;	// For pointing at shadowmap
		ShaderResourceView m_shadowMapShaderResView;	// For accessing shadowmap

		SharedTexture m_sharedTex;
	};
}