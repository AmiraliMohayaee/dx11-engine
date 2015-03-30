#pragma once

#include <Windows.h>

#include "Singleton.h"
#include <string>

#include <d3d11.h>
#include <d3dx11.h>
#include <xnamath.h>
#include "RenderTargetView.h"

#define WIN32_LEAN_AND_MEAN


namespace DXEngine
{

	class Graphics : public NonCopyable
	{
	public:
		bool Initialize(unsigned int width, unsigned int height, bool fullscreen, const std::wstring &title);

		ID3D11Device* GetDevice() { return m_device; }
		ID3D11DeviceContext* GetContext() { return m_context; }
		
		void SetClearColour(const Colour &colour) { m_colour = colour; }
		void SetAsCurrentRenderTargetView();		// Setting backbuffer as current render target view

		void ClearBackBuffer();
		void FlipBuffer();

		void Shutdown();

		int GetScreenWidth();
		int GetScreenHeight();

	private:
		bool InitializeDX();
		bool InitializeWin();


	private:
		Graphics();
		~Graphics();
		friend class Singleton<Graphics>;

		Colour m_colour;
		unsigned int m_width;
		unsigned int m_height;
		bool m_fullscreen;
		std::wstring m_title;
		
		HWND m_handle;
		HINSTANCE m_instance;
		D3D_DRIVER_TYPE m_driverType;
		D3D_FEATURE_LEVEL m_featureLevel;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_context;
		IDXGISwapChain* m_swapChain;
		RenderTargetView m_renderTargetView;
		ID3D11Texture2D* m_depthStencil;
		ID3D11DepthStencilView* m_depthStencilView;
	};

	typedef Singleton<Graphics> TheGraphics;

}