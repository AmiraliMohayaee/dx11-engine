#pragma once

#include <d3d11.h>

namespace DXEngine
{
	class Sampler
	{
	public:
		Sampler();

		bool Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texaddr, D3D11_COMPARISON_FUNC compfunc);
		void Release();

		void SetAsCurrentSampler(UINT addr);

	private:
		ID3D11SamplerState* m_samplerState;
	};
}