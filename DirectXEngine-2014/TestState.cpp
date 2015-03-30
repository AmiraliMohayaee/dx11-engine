#include "TestState.h"
#include "Game.h"
#include "ReportError.h"
#include <assert.h>
#include <cmath>
#include <iostream>
#include "WVPBuffer.h"


namespace DXEngine
{
	void TestState::OnActivated()
	{
		GameState::OnActivated();

		ShadowInit();

		// First camera
		m_camera.LookAt(XMVectorSet(5, 3.0, 1, 1),
			XMVectorSet(0, 0, 0, 0),
			XMVectorSet(0, -1, 0, 0));
		m_camera.SetLens(60.0f,
			(TheGraphics::Instance()->GetScreenWidth() / TheGraphics::Instance()->GetScreenHeight()),
			0.1f,
			100.0f);
	}


	// Draws the shadowmap and the depth value
	void TestState::DrawShadowMap()
	{
		// Setting up light
		m_light.SetLookAt(XMVectorSet(5, 3.0, 1, 1),
			XMVectorSet(0, 0, 0, 0),
			XMVectorSet(0, -1, 0, 0));
		m_light.SetLightPerspective(60.0f, 
			(TheGraphics::Instance()->GetScreenWidth() / TheGraphics::Instance()->GetScreenHeight()),
			0.1,
			100.0);

		WVPBuffer wvp;
		wvp.World = XMMatrixIdentity();
		wvp.World = XMMatrixTranspose(wvp.World);	// Transposing the world matrix before passing it into DX
		wvp.Proj = m_camera.GetProj();
		wvp.Proj = XMMatrixTranspose(wvp.Proj);	// Transposing the projecion matrix before passing it into DX
		wvp.View = m_camera.GetView();
		wvp.View = XMMatrixTranspose(wvp.View);	// Transposing the view matrix before passing it into DX

		m_shadowMapShader.UpdateWVP(wvp);

		// Setting to true would draw the shadow map's depth value
		// Set to false in normal circumstances
		DrawScene(false);
	}


	// For Second pass
	void TestState::DrawShadow()
	{
		// Setting up light
		m_light.SetLookAt(XMVectorSet(0, 1.0, 0.5, 1),
			XMVectorSet(0, 0, 0, 0),
			XMVectorSet(0, -1, 0, 0));

		m_light.SetLightPerspective(60.0f, 
			(TheGraphics::Instance()->GetScreenWidth() / TheGraphics::Instance()->GetScreenHeight()),
			0.1,
			100.0);

		// Creating WorldViewPojection Buffer and updating it later on after mapping the shadow
		WVPBuffer wvp;
		wvp.World = XMMatrixIdentity();
		wvp.World = XMMatrixTranspose(wvp.World);	// Transposing the world matrix before passing it into DX

		wvp.Proj = m_camera.GetProj();
		wvp.Proj = XMMatrixTranspose(wvp.Proj);	// Transposing the projecion matrix before passing it into DX
		wvp.View = m_camera.GetView();
		wvp.View = XMMatrixTranspose(wvp.View);	// Transposing the view matrix before passing it into DX

		m_shadowMapShader.UpdateWVP(wvp);

		DrawScene(true);
	}



	void TestState::OnDeActivated()
	{
		GameState::OnDeActivated();
	}

	TestState::TestState()
	{
	}

	void TestState::ShadowInit()
	{
		if(!m_shadowMapShader.Load("SMVS.fx", "SMPS.fx", "SPSMVS.fx", "SPSMPS.fx"))
		{
			ReportError("Could not load Shadow Map Shader files.");
			assert(false);
		}

		m_shadowMapShader.SetLight(&m_light);


		// Setting up axis vertex buffers
		//std::vector<GenericVertex> X;
		//X.push_back(GenericVertex(XMFLOAT4(-8.0f, 0.0f, -8.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		//X.push_back(GenericVertex(XMFLOAT4(0.0f, 0.0f, -8.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		//X.push_back(GenericVertex(XMFLOAT4(-8.0f, 1.0f, -8.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		//
		//std::vector<GenericVertex> Y;
		//Y.push_back(GenericVertex(XMFLOAT4(-8.0f, 0.0f, -8.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		//Y.push_back(GenericVertex(XMFLOAT4(-2.0f, 0.0f, -10.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		//Y.push_back(GenericVertex(XMFLOAT4(-8.0f, 1.0f, -8.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		//
		//std::vector<GenericVertex> Z;
		//Z.push_back(GenericVertex(XMFLOAT4(-8.0f, 0.0f, -8.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		//Z.push_back(GenericVertex(XMFLOAT4(-8.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		//Z.push_back(GenericVertex(XMFLOAT4(-8.0f, 1.0f, -8.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));


		// Triangle
		std::vector<GenericVertex> Velma;
		Velma.push_back(GenericVertex(XMFLOAT4(2.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		Velma.push_back(GenericVertex(XMFLOAT4(0.0f, 2.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		Velma.push_back(GenericVertex(XMFLOAT4(-2.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));

		//// Test Triangle used as Plane object
		std::vector<GenericVertex> John;
		John.push_back(GenericVertex(XMFLOAT4(5.0f, 5.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		John.push_back(GenericVertex(XMFLOAT4(0.0f, 5.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));
		John.push_back(GenericVertex(XMFLOAT4(-5.0f, -5.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f)));

		// Passing triangle into vertex buffer
		m_genericVertexBuff.Load(Velma);
		m_genericVertexBuff.CreateInputLayout(&m_shadowMapShader);
		m_genericVertexBuff.SetPrimitiveTapology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Passing Surface into vertex buffer
		m_quadBuffer.Load(John);
		m_quadBuffer.CreateInputLayout(&m_shadowMapShader);
		m_quadBuffer.SetPrimitiveTapology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Testing Axis
		//m_x.Load(X);
		//m_x.CreateInputLayout(&m_shadowMapShader);
		//m_x.SetPrimitiveTapology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//m_y.Load(Y);
		//m_y.CreateInputLayout(&m_shadowMapShader);
		//m_y.SetPrimitiveTapology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//m_z.Load(Z);
		//m_z.CreateInputLayout(&m_shadowMapShader);
		//m_z.SetPrimitiveTapology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		// Used for loading the shadowmap into a test harness
		//m_testShader.SetShadowMapShaderResourceView(m_shadowMapShader.GetShadowMapShader());
	}

	void TestState::DrawScene(bool flag)
	{
		// Flag for setting up the shaded surface
		if (flag)
		{
			m_quadBuffer.SetAsCurrentBuffer();
			m_quadBuffer.Draw(m_quadBuffer.GetNumberOfVertex(), 0);
		}

		// Drawing Axis
		//m_x.SetAsCurrentBuffer();
		//m_x.Draw(m_x.GetNumberOfVertex(), 0);
		//m_y.SetAsCurrentBuffer();
		//m_y.Draw(m_y.GetNumberOfVertex(), 0);
		//m_z.SetAsCurrentBuffer();
		//m_z.Draw(m_z.GetNumberOfVertex(), 0);

		// Triangle
		m_genericVertexBuff.SetAsCurrentBuffer();
		m_genericVertexBuff.Draw(m_genericVertexBuff.GetNumberOfVertex(), 0);
	}



	void TestState::Draw()
	{
		// First Pass
		m_shadowMapShader.FirstPassBegin();

		DrawShadowMap();

		m_shadowMapShader.FirstPassEnd();

		// Second Pass
		m_shadowMapShader.SecondPassBegin();

		DrawShadow();

		m_shadowMapShader.SecondPassEnd();

		// Presenting Scene
		TheGame::Instance()->DrawGameObjects();
	}

	void TestState::Update()
	{
		TheGame::Instance()->UpdateGameObjects();
	}

	void TestState::OnKeyboardEvent()
	{

	}
}






		// Testing Texture creation for debug purposes
		//m_texture.Create(TheGraphics::Instance()->GetScreenWidth(), 
		//	TheGraphics::Instance()->GetScreenHeight(), true, false);


		// Setting up a simple triangle 
		////std::vector<MurikaVertex> Steve;
		////Steve.push_back(MurikaVertex(XMFLOAT4(0.5f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
		////Steve.push_back(MurikaVertex(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
		////Steve.push_back(MurikaVertex(XMFLOAT4(-0.5f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)));
		//
		//m_vertexBuffer.Load(Steve);

		//m_vertexBuffer.CreateInputLayout(&m_shadowMapShader);

		//m_vertexBuffer.SetPrimitiveTapology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



		////
		//// Testing Shadow Map Test Harness. Testing render to texture functionality
		////
		//m_testShader.SetAsCurrentShader();

		//m_testShader.UpdateWVP(wvp);

		//m_quadBuffer.SetAsCurrentBuffer();

		//m_quadBuffer.Draw(m_quadBuffer.GetNumberOfVertex(), 0);



		// Square
		//std::vector<GenericVertex> John;
		//John.push_back(GenericVertex(XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)));
		//John.push_back(GenericVertex(XMFLOAT4(-5.0f, 5.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f)));
		//John.push_back(GenericVertex(XMFLOAT4(0.0f, 5.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)));
		//John.push_back(GenericVertex(XMFLOAT4(-5.0f, 5.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f)));
		//John.push_back(GenericVertex(XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f)));
		//John.push_back(GenericVertex(XMFLOAT4(-5.0f, 0.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f)));
