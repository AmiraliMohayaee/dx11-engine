#pragma once

#include "GameState.h"
#include "Singleton.h"
#include "Shader.h"
#include "InfidelShader.h"
#include "MurikaVertex.h"
#include "GenericVertex.h"
#include "Camera.h"
#include "ShadowMapShader.h"
//#include "TestShader.h"
#include "Texture.h"
#include "Light.h"


namespace DXEngine
{
	class TestState : public GameState, public NonCopyable
	{
	public:
		TestState();
		~TestState() {}
		virtual void Draw();
		virtual void Update();
		virtual void OnActivated() override;
		virtual void OnDeActivated() override;
		virtual void OnKeyboardEvent();

		void ShadowInit();
		void DrawShadowMap();	// Draws the Shadowmap
		void DrawShadow();
		void DrawScene(bool flag);	

	private:		
		InfidelShader m_shader;
		MurikaVertexBuffer m_vertexBuffer;
		GenericVertexBuffer m_genericVertexBuff;
		GenericVertexBuffer m_x;
		GenericVertexBuffer m_y;
		GenericVertexBuffer m_z;
		GenericVertexBuffer m_quadBuffer;
		ShadowMapShader m_shadowMapShader;
		//TestShader m_testShader;
		Camera m_camera;
		Texture m_texture;
		Light m_light;
	};

	typedef Singleton<TestState> TheTestState;
}