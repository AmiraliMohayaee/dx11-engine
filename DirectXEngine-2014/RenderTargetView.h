// The backbuffer (well, generally speaking)
#pragma once


#include "Texture.h"
#include "Colour.h"


namespace DXEngine
{
	class RenderTargetView
	{
	public: 
		RenderTargetView();
		~RenderTargetView();

		bool Create(SharedTexture sharedTex, bool desc = true);
		
		void SetAsCurrentRenderTargetView(ID3D11DepthStencilView* depthStencilView = NULL);
		 
		// Setting the texture to the colour passed in
		void Clear(Colour* c);

		ID3D11RenderTargetView* m_renderTargetView;

	private:
		SharedTexture m_sharedTexture;
	};
}