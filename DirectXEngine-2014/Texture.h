#pragma once 

#include <d3d11.h>
#include <string>
#include <memory>


namespace DXEngine
{
	class Texture
	{
	public:
		Texture();
		Texture(ID3D11Texture2D* tex2D);
		~Texture();

		bool Create(unsigned int width, unsigned int height, bool alpha, bool readOnly);

		DXGI_FORMAT GetFormat() const
		{
			return m_format;
		}

		ID3D11Texture2D* GetTexture()
		{
			return m_texture;
		}

	private:
		ID3D11Texture2D* m_texture;
		DXGI_FORMAT m_format;
	};

	typedef std::shared_ptr<Texture> SharedTexture;
}