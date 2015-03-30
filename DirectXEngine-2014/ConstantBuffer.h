#pragma once

#include "Graphics.h"


namespace DXEngine
{
	template <typename T>
	class ConstantBuffer
	{
	public: 
		ConstantBuffer() : m_buffer ( NULL ) {}
		~ConstantBuffer() 
		{
			if (m_buffer) m_buffer->Release();
		}

		bool Create()
		{
			D3D11_BUFFER_DESC desc;
			ZeroMemory(&desc, sizeof(desc));

			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = sizeof(T);
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = 0;

			if (FAILED(TheGraphics::Instance()->GetDevice()->CreateBuffer(&desc, NULL, &m_buffer)))
			{
				if (m_buffer) m_buffer->Release();
				return false;
			}

			return true;
		}

		void Update(const T& constBuffer)
		{
			TheGraphics::Instance()->GetContext()->UpdateSubresource(m_buffer, 0, NULL, &constBuffer, 0, 0);
		}

		void SetAsVSConstantBuffer(unsigned int location)
		{
			TheGraphics::Instance()->GetContext()->VSSetConstantBuffers(location, 1, &m_buffer);
		}

		void SetAsPSConstantBuffer(unsigned int location)
		{
			TheGraphics::Instance()->GetContext()->PSSetConstantBuffers(location, 1, &m_buffer);
		}

	private:
		ID3D11Buffer* m_buffer; 
	};
}