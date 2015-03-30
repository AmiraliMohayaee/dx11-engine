#pragma once

#include <d3d11.h>
#include <string>

namespace DXEngine
{
	class PixelShader
	{
	public: 
		PixelShader();
		~PixelShader();

		bool Load(const std::string& fileName);

		void SetAsCurrentPixelShader();

		ID3DBlob* GetBlob() { return m_blob; }


	private:
		ID3D11PixelShader* m_pixelShader;
		ID3DBlob* m_blob;
	};
}