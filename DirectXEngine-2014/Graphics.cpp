#include "Graphics.h"
#include "EventPoller.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	return DXEngine::TheEventPoller::Instance()->WndProc(hwnd, umessage, wparam, lparam);
}

namespace DXEngine
{
	Graphics::Graphics(): m_width(0),
		m_height(0),
		m_fullscreen(false),
		m_handle(0),
		m_instance(0),
		m_driverType(D3D_DRIVER_TYPE_NULL),
		m_featureLevel(D3D_FEATURE_LEVEL_11_0),
		m_device(NULL),
		m_context(NULL),
		m_swapChain(NULL),
		m_depthStencil(NULL),
		m_depthStencilView(NULL)
	{

	}

	Graphics::~Graphics()
	{
		if (m_context) m_context->ClearState();
		if (m_depthStencil) m_depthStencil->Release();
		if (m_depthStencilView) m_depthStencilView->Release();
		if (m_swapChain) m_swapChain->Release();
		if (m_context) m_context->Release();
		if (m_device) m_device->Release();
	}

	bool Graphics::Initialize(unsigned int width, unsigned int height, bool fullscreen, const std::wstring &title)
	{
		m_width = width;
		m_height = height;
		m_fullscreen = fullscreen;
		m_title = title;


		if (!InitializeWin())
			return false;

		if (!InitializeDX())
			return false;


		return true;
	}

	void Graphics::SetAsCurrentRenderTargetView()
	{
		m_renderTargetView.SetAsCurrentRenderTargetView();
	}

	// Either way all COM objects are relased by the dtor anyway
	//void Graphics::Shutdown()
	//{

	//}
	 
	void Graphics::ClearBackBuffer()
	{
		// Clearing the back buffer
		m_renderTargetView.Clear(&m_colour);

		// Clearing the Z-buffer/depth buffer
		m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	
	void Graphics::FlipBuffer()
	{
		// Flipping/swapping the buffers
		m_swapChain->Present(0, 0);
	}


	bool Graphics::InitializeDX()
	{
		HRESULT hr = S_OK;

		UINT createDeviceFlags = 0;

		#ifdef _DEBUG
			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
		    D3D_DRIVER_TYPE_HARDWARE,
		    D3D_DRIVER_TYPE_WARP,
		    D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT numDriverTypes = ARRAYSIZE( driverTypes );

		D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;

		//D3D_FEATURE_LEVEL featureLevels[] =
		//{
		//    D3D_FEATURE_LEVEL_11_0,
		//    D3D_FEATURE_LEVEL_10_1,
		//    D3D_FEATURE_LEVEL_10_0,
		//};
		//UINT numFeatureLevels = ARRAYSIZE( featureLevels );
		
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof( sd ) );
		sd.BufferCount = 1;
		sd.BufferDesc.Width = m_width;
		sd.BufferDesc.Height = m_height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = m_handle;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = m_fullscreen ? FALSE : TRUE;

		for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
		    m_driverType = driverTypes[driverTypeIndex];
			hr = D3D11CreateDeviceAndSwapChain( NULL, m_driverType, NULL, createDeviceFlags, &featureLevels, 1,
		                                        D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device, NULL, &m_context);
		    if(SUCCEEDED(hr))
		        break;
		}

		if(FAILED(hr))
			return false;

		// Create a render target view
		ID3D11Texture2D* bb = NULL;
		hr = m_swapChain ->GetBuffer( 0, __uuidof(ID3D11Texture2D), ( LPVOID* )&bb);
		if(FAILED(hr))
		    return false;
		
		// Creating backbuffer using render target view
		SharedTexture backBuffer(new Texture(bb));
		if(!m_renderTargetView.Create(backBuffer))
			return false;
		
		// Create depth stencil texture
		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory( &descDepth, sizeof(descDepth) );
		descDepth.Width = m_width;
		descDepth.Height = m_height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		
		hr = m_device ->CreateTexture2D( &descDepth, NULL, &m_depthStencil);
		if(FAILED(hr))
			return false;

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory( &descDSV, sizeof(descDSV) );
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		hr = m_device ->CreateDepthStencilView( m_depthStencil, &descDSV, &m_depthStencilView);
		if(FAILED(hr))
			return false;
		
		m_renderTargetView.SetAsCurrentRenderTargetView(m_depthStencilView);

		// Setup the viewport
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)m_width;
		vp.Height = (FLOAT)m_height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_context ->RSSetViewports(1, &vp);
		return true;
	}
	

	bool Graphics::InitializeWin()
	{
		// Register class
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof( WNDCLASSEX );
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_instance;
		wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
		wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = m_title.c_str();
		wcex.hIconSm = wcex.hIcon;

		if( !RegisterClassEx(&wcex))
        return false;

		// Create window
		m_instance = GetModuleHandle(NULL);

		RECT rc = { 0, 0, m_width, m_height};
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		m_handle = CreateWindow(m_title.c_str(), m_title.c_str(),
								WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, 
								rc.bottom - rc.top, NULL, NULL, m_instance, NULL);
		if(!m_handle)
		    return false;
		
		ShowWindow(m_handle, SW_SHOW);
		return true;
	}

	int Graphics::GetScreenWidth()
	{
		return m_width;
	}

	int Graphics::GetScreenHeight()
	{
		return m_height;
	}
}