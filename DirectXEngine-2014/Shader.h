#pragma once

#include <d3d11.h>
#include "Singleton.h"

namespace DXEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = 0 {}
		virtual ID3DBlob* GetVSBlob() = 0;
		virtual ID3DBlob* GetPSBlob() = 0;
		virtual void SetAsCurrentShader() = 0;
	};
}