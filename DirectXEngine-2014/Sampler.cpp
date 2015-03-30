#include "Sampler.h"
#include "Graphics.h"
#include "ReportError.h"


namespace DXEngine
{
	Sampler::Sampler()
	{
		m_samplerState = NULL;
	}

	void Sampler::SetAsCurrentSampler(UINT addr)
	{
		TheGraphics::Instance()->GetContext()->PSSetSamplers(addr, 1, &m_samplerState);
	}

	bool Sampler::Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texaddr, D3D11_COMPARISON_FUNC compfunc)
	{
		D3D11_SAMPLER_DESC samplerDesc;

		samplerDesc.Filter = filter;
		samplerDesc.AddressU = texaddr;
		samplerDesc.AddressV = texaddr;
		samplerDesc.AddressW = texaddr;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = compfunc;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		
		if (FAILED(TheGraphics::Instance()->GetDevice()->
			CreateSamplerState(&samplerDesc, &m_samplerState)))
		{
			ReportError("Could not create Sampler State.");
			return false;
		}

		return true;
	}

	void Sampler::Release()
	{
		m_samplerState->Release();
		m_samplerState = NULL;
	}
}