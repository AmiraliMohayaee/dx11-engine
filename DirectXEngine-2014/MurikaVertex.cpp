#include "MurikaVertex.h"
#include "Graphics.h"
#include <iostream>


namespace DXEngine
{
	bool MurikaVertexBuffer::CreateInputLayout(Shader* shader)
	{
		D3D11_INPUT_ELEMENT_DESC InputLayout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		HRESULT hr = TheGraphics::Instance()->GetDevice()->CreateInputLayout(InputLayout,
			ARRAYSIZE(InputLayout),
			shader->GetVSBlob()->GetBufferPointer(),
			shader->GetVSBlob()->GetBufferSize(),
			&m_inputLayout);

		if (FAILED(hr))
		{
			std::cout << "Error setting up Vertex Buffer";
			return false;
		}

		return true;
	}
}