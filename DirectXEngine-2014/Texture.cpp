#include "Texture.h"
#include "Graphics.h"

namespace DXEngine
{
	Texture::Texture() :  m_texture (NULL),
		m_format(DXGI_FORMAT_UNKNOWN)
	{

	}

	Texture::Texture(ID3D11Texture2D* tex2D) : m_texture(tex2D), m_format(DXGI_FORMAT_UNKNOWN)
	{

	}

	Texture::~Texture()
	{
		// If com object for Texture does exist, then release
		if (!m_texture)
			m_texture->Release();
	}


	bool Texture::Create(unsigned int width, unsigned int height, bool alpha, bool readOnly)
	{
		// Checking format of image (with or without alpha)
		m_format = alpha ? DXGI_FORMAT_R32G32B32A32_FLOAT : DXGI_FORMAT_R32G32B32_FLOAT ;

		// 
		unsigned int flag;

		flag = D3D11_BIND_SHADER_RESOURCE;

		if (!readOnly)
			flag |= D3D11_BIND_RENDER_TARGET;

		D3D11_TEXTURE2D_DESC desc;

		ZeroMemory(&desc, sizeof(desc));

		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = m_format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		// Setting flags
		desc.BindFlags = flag;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		HRESULT hres = TheGraphics::Instance()->GetDevice()->CreateTexture2D(&desc, 0, &m_texture);

		// Checking if a Tex2D device is created
		int error = FAILED(hres);

		if (error != S_OK)
		{
			if (m_texture != NULL)
				m_texture->Release();

			return false;
		}


		return true;
	}
}