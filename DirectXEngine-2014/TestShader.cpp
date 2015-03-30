#include "TestShader.h"
#include "Colour.h"
#include "ShadowMapShader.h"


namespace DXEngine
{
	ID3DBlob* TestShader::GetVSBlob()
	{
		return m_vs.GetBlob();
	}

	ID3DBlob* TestShader::GetPSBlob()
	{
		return m_ps.GetBlob();
	}

	void TestShader::SetAsCurrentShader()
	{
		m_vs.SetAsCurrentVertexShader();
		m_ps.SetAsCurrentPixelShader();
		m_wvpb.SetAsVSConstantBuffer(0);	// Setting the address of the constant buffer in the VS
		m_sampler.SetAsCurrentSampler(1);
		m_shaderResView->SetAsCurrentResourceView(0);
	}

	void TestShader::SetShadowMapShaderResourceView(ShaderResourceView* texresview)
	{
		m_shaderResView = texresview;
	}

	bool TestShader::Load(const std::string &FPVSfilename, const std::string &FPPSfilename)
	{
		if (!m_vs.Load(FPVSfilename))
			return false;

		if (!m_ps.Load(FPPSfilename))
			return false;

		if (!m_sampler.Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR,
			D3D11_TEXTURE_ADDRESS_WRAP,
			D3D11_COMPARISON_ALWAYS))
			return false;

		if (!m_wvpb.Create())
			return false;

		return true;
	}

	void TestShader::UpdateWVP(const WVPBuffer& wvpb)
	{
		m_wvpb.Update(wvpb);
	}
}