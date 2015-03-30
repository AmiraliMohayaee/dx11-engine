#pragma once

#include <d3d11.h>
#include <string>

namespace DXEngine
{
	class VertexShader
	{
	public: 
		VertexShader();
		~VertexShader();

		bool Load(const std::string& fileName);

		void SetAsCurrentVertexShader();

		ID3DBlob* GetBlob() { return m_blob; }


	private:
		ID3D11VertexShader* m_vertexShader;
		ID3DBlob* m_blob;
	};
}