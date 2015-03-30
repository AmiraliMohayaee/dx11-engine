#include "RenderTargetView.h"
#include "Graphics.h"
#include "Colour.h"

namespace DXEngine
{
	RenderTargetView::RenderTargetView() : m_renderTargetView(NULL)
	{

	}

	RenderTargetView::~RenderTargetView()
	{
		if (m_renderTargetView != NULL)
			m_renderTargetView->Release();
	}

	bool RenderTargetView::Create(SharedTexture sharedTex, bool desc)
	{
		if (desc == true)
		{
			D3D11_RENDER_TARGET_VIEW_DESC rtvdesc;
			ZeroMemory(&rtvdesc, sizeof(rtvdesc));

			rtvdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtvdesc.Format = sharedTex->GetFormat();
			rtvdesc.Texture2D.MipSlice = 0;


			if (FAILED(TheGraphics::Instance()->
				GetDevice()->CreateRenderTargetView(sharedTex->GetTexture(), &rtvdesc, &m_renderTargetView)))
			{
				if (m_renderTargetView != NULL)
					m_renderTargetView->Release();

				return false;
			}
		}

		else
		{
			if (FAILED(TheGraphics::Instance()->
				GetDevice()->CreateRenderTargetView(sharedTex->GetTexture(), NULL, &m_renderTargetView)))
			{
				if (m_renderTargetView != NULL)
					m_renderTargetView->Release();

				return false;
			}
		}

		m_sharedTexture = sharedTex;

		return true;
	}

	void RenderTargetView::SetAsCurrentRenderTargetView(ID3D11DepthStencilView* depthStencilView)
	{
		TheGraphics::Instance()->GetContext()->OMSetRenderTargets(1, &m_renderTargetView, depthStencilView);
	}

	void RenderTargetView::Clear(Colour* c)
	{
		TheGraphics::Instance()->GetContext()->ClearRenderTargetView(m_renderTargetView, c->ToArray());
	}
}