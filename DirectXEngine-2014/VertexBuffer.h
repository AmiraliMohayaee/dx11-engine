#pragma once

#include "Graphics.h"
#include <vector>
#include "Shader.h"


namespace DXEngine
{
	template <typename T>
	class VertexBuffer
	{		
	protected:
		unsigned int m_shaderId;
		D3D11_PRIMITIVE_TOPOLOGY m_primitiveTapology;
		ID3D11InputLayout* m_inputLayout;
		ID3D11Buffer* m_buffer;
		unsigned int m_numVertex;


	public:
		VertexBuffer() : 
			m_shaderId(0),
			m_buffer ( NULL ),
			m_inputLayout( NULL ),
			m_numVertex(0),
			m_primitiveTapology( D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED )
		{}

		~VertexBuffer() 
		{
			if (m_buffer) m_buffer->Release();
		}

		void SetPrimitiveTapology(D3D11_PRIMITIVE_TOPOLOGY pt)
		{
			m_primitiveTapology = pt;
		}


		bool Load(const std::vector <T>& vec)
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));

			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(T) * vec.size();
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA resData;

			resData.pSysMem = vec.data();
			resData.SysMemPitch = 0;
			resData.SysMemSlicePitch = 0;

			m_numVertex = vec.size();

			if (FAILED(TheGraphics::Instance()->GetDevice()->CreateBuffer(&desc, &resData, &m_buffer)))
			{
				if (m_buffer) m_buffer->Release();
				return false;
			}

			return true;
		}

		UINT GetNumberOfVertex() const
		{
			return m_numVertex;
		}

		void Update(const T& vertexBuffer)
		{
			TheGraphics::Instance()->GetContext()->UpdateSubresource(m_buffer, 0, NULL, &vertexBuffer, 0, 0);
		}

		//void SetAsVSConstantBuffer(unsigned int location)
		//{
		//	TheGraphics::Instance()->GetContext()->VSSetVertexBuffers(location, 1, &m_buffer);
		//}

		//void SetAsPSConstantBuffer(unsigned int location)
		//{
		//	TheGraphics::Instance()->GetContext()->PSSetVertexBuffers(location, 1, &m_buffer);
		//}

		void SetAsCurrentBuffer()
		{
			TheGraphics::Instance()->GetContext()->IASetPrimitiveTopology(m_primitiveTapology);

			UINT stride = sizeof(T);
			UINT offset = 0;
			TheGraphics::Instance()->GetContext()->IASetVertexBuffers(0, 1, &m_buffer, &stride, &offset);
			TheGraphics::Instance()->GetContext()->IASetInputLayout(m_inputLayout);
		}

		void Draw(unsigned int vertexNum, unsigned int startIndex)
		{
			TheGraphics::Instance()->GetContext()->Draw(vertexNum, startIndex);
		}

		virtual bool CreateInputLayout(Shader* shader) = 0;
	};
}