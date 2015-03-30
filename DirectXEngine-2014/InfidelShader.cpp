#include "InfidelShader.h"


namespace DXEngine
{
	ID3DBlob* InfidelShader::GetVSBlob()
	{
		return m_vs.GetBlob();
	}

	ID3DBlob* InfidelShader::GetPSBlob()
	{
		return m_ps.GetBlob();
	}

	void InfidelShader::SetAsCurrentShader()
	{
		m_vs.SetAsCurrentVertexShader();
		m_ps.SetAsCurrentPixelShader();
		m_wvpb.SetAsVSConstantBuffer(0);	// Setting the address of the constant buffer in the VS
	}

	bool InfidelShader::Load(const std::string &VSfilename, const std::string &PSfilename)
	{
		if (!m_vs.Load(VSfilename))
			return false;

		if (!m_ps.Load(PSfilename))
			return false;

		if(!m_wvpb.Create())
			return false;

		return true;
	}

	void InfidelShader::UpdateWVP(const WVPBuffer& wvpb)
	{
		m_wvpb.Update(wvpb);
	}
}