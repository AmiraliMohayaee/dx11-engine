#include "VertexShader.h"
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <D3DX11async.h>
#include "StringUtility.h"
#include "ReportError.h"
#include "Graphics.h"


namespace DXEngine
{
	VertexShader::VertexShader()
	{
		m_vertexShader = NULL;
		m_blob = NULL;
	}


	VertexShader::~VertexShader()
	{
		if (m_vertexShader) m_vertexShader->Release();
		if (m_blob) m_blob->Release();
	}

	bool VertexShader::Load(const std::string& fileName)
	{
		HRESULT hr = S_OK;

		// Shader flags
		DWORD shaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;

		// pre-processor macro for enabling shader debug mode
		#if defined( DEBUG ) || defined ( _DEBUG )
		shaderFlag |= D3DCOMPILE_DEBUG;
		#endif

		ID3DBlob* errorBlob = NULL;

		std::wstring wideString = ConvertToWideString(fileName);

		hr = D3DX11CompileFromFile(wideString.c_str(), NULL, NULL, "VS", "vs_4_0", shaderFlag, 0, NULL, &m_blob, &errorBlob,
			NULL);


		if (FAILED(hr))
		{
			if (errorBlob) 
			{
					ReportError(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
					errorBlob->Release();
			}
			return false;
		}

		hr = TheGraphics::Instance()->GetDevice()->CreateVertexShader(m_blob->GetBufferPointer(), m_blob->GetBufferSize(),
			NULL, &m_vertexShader);

		if (FAILED(hr))
		{
			ReportError("Unable to create a Vertex Shader for " + fileName + "!");
			return false;
		}

		return true;
	}


	void VertexShader::SetAsCurrentVertexShader()
	{
		TheGraphics::Instance()->GetContext()->VSSetShader(m_vertexShader, 0, NULL);
	}
}