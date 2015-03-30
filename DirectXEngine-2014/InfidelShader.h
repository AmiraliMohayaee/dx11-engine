#pragma once

#include "Shader.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include <string>
#include "ConstantBuffer.h"
#include "WVPBuffer.h"


namespace DXEngine
{
	class InfidelShader : public Shader
	{
	public:
		bool Load(const std::string &VSfilename, const std::string &PSfilename);

		ID3DBlob* GetVSBlob() override;
		ID3DBlob* GetPSBlob() override;
		void SetAsCurrentShader() override;

		void UpdateWVP(const WVPBuffer& wvpb);

	private:
		PixelShader m_ps;
		VertexShader m_vs;

		WVPConstBuffer m_wvpb;
	};
}