#include "ShaderResourceView.h"
#include <iostream>
#include "Graphics.h"
#include "ReportError.h"


namespace DXEngine
{
	ShaderResourceView::ShaderResourceView()
	{
		m_shaderResourceView = NULL;
	}

	ShaderResourceView::~ShaderResourceView()
	{
		if (m_shaderResourceView != NULL)
			m_shaderResourceView->Release();
	}

	bool ShaderResourceView::Load(const std::string &filename)
	{
		HRESULT result = D3DX11CreateShaderResourceViewFromFileA(TheGraphics::Instance()->GetDevice(), filename.c_str(), NULL, NULL,
			&m_shaderResourceView, NULL);

		if (FAILED(result))
		{
			ReportError("Failed to load in Shader resource.");
			return false;
		}

		return true;
	}

	bool ShaderResourceView::Create(SharedTexture tex)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC rtvdesc;
		ZeroMemory(&rtvdesc, sizeof(rtvdesc));

		rtvdesc.Format = tex->GetFormat();
		rtvdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		rtvdesc.Texture2D.MostDetailedMip = 0;
		rtvdesc.Texture2D.MipLevels = 1;


		if (FAILED(TheGraphics::Instance()->
			GetDevice()->CreateShaderResourceView(tex->GetTexture(), &rtvdesc, &m_shaderResourceView)))
		{
			if (m_shaderResourceView != NULL)
				m_shaderResourceView->Release();

			return false;
		}
		
		return true;
	}

	void ShaderResourceView::SetAsCurrentResourceView(UINT loc)
	{
		TheGraphics::Instance()->GetContext()->PSSetShaderResources(loc, 1, &m_shaderResourceView);
	}
}