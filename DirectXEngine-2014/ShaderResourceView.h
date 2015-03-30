#pragma once

#include <d3d11.h>
#include <string>
#include "Texture.h"


namespace DXEngine
{
	class ShaderResourceView
	{
	public:
		ShaderResourceView();
		~ShaderResourceView();

		bool Load(const std::string &filename);
		bool Create(SharedTexture tex);

		void SetAsCurrentResourceView(UINT loc);

	private:
		ID3D11ShaderResourceView* m_shaderResourceView;

	};

}