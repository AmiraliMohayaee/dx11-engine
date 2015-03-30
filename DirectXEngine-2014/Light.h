#pragma once 

#include "WVPBuffer.h"
#include "LightBuffer.h"


namespace DXEngine
{
	class Light
	{
	public:
		// Setting up view and proj for the WVP matrix
		void SetLightPerspective(float fovY, float aspect, float zn, float zf);
		void SetLookAt(XMVECTOR pos, XMVECTOR target, XMVECTOR worldUp);

		// Setting up view and proj Matrix
		XMMATRIX GetView() const;
		XMMATRIX GetProj() const;

	private:
		XMMATRIX m_viewMatrix;
		XMMATRIX m_projMatrix;

		LightBuffer m_lightBuff;
	};
}