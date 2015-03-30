#include "ShadowMapShader.h"
#include "Colour.h"


namespace DXEngine
{
	ID3DBlob* ShadowMapShader::GetVSBlob()
	{
		return m_vs.GetBlob();
	}

	ID3DBlob* ShadowMapShader::GetPSBlob()
	{
		return m_ps.GetBlob();
	}

	void ShadowMapShader::SetAsCurrentShader()
	{

	}

	bool ShadowMapShader::Load(const std::string &FPVSfilename, const std::string &FPPSfilename,
			const std::string &SPVSfilename, const std::string &SPPSfilename)
	{
		// Will set back to normal later on
		//SharedTexture texture(new Texture);
		m_sharedTex.reset(new Texture);

		// Setting alpha channels to true due to DX not liking alpha turned off
		// with the current vertex buffer size
		if (!m_sharedTex->Create(TheGraphics::Instance()->GetScreenWidth(), 
			TheGraphics::Instance()->GetScreenHeight(), true, false))
			return false;

		// Loading First Pass shader files
		if (!m_vs.Load(FPVSfilename))
			return false;

		if (!m_ps.Load(FPPSfilename))
			return false;

		// Loading Second Pass shader files
		if (!m_spvs.Load(SPVSfilename))
			return false;

		if (!m_spps.Load(SPPSfilename))
			return false;

		if (!m_sampler.Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR,
			D3D11_TEXTURE_ADDRESS_CLAMP,
			D3D11_COMPARISON_ALWAYS))
			return false;

		if (!m_wvpb.Create())
			return false;

		if (!m_lightBuffer.Create())
			return false;

		if (!m_shadowMapShaderResView.Create(m_sharedTex))
			return false;

		if (!m_renderTargetView.Create(m_sharedTex))
			return false;

		return true;
	}

	// Only used for testing the shadowmap
	//ShaderResourceView* ShadowMapShader::GetShadowMapShader()
	//{
	//	return &m_shadowMapShaderResView;
	//}

	void ShadowMapShader::UpdateWVP(const WVPBuffer& wvpb)
	{
		m_wvpb.Update(wvpb);
	}

	void ShadowMapShader::UpdateLight(const LightBuffer& lightBuffer)
	{
		m_lightBuffer.Update(lightBuffer);
	}

	void ShadowMapShader::SetLight(Light *light)
	{
		m_light = light;
	}

	// In charge of rendering the light's view source to a texture
	void ShadowMapShader::FirstPassBegin()
	{
		m_vs.SetAsCurrentVertexShader();
		m_ps.SetAsCurrentPixelShader();
		m_wvpb.SetAsVSConstantBuffer(0);	// Setting the address of the constant buffer in the VS
		m_lightBuffer.SetAsVSConstantBuffer(1);		// Setting the light constbuff to the VS light buffer

		// Setting to default black background
		Colour color(1, 1, 1, 1);
		//m_renderTargetView.Clear(&colour);
		//m_renderTargetView.SetAsCurrentRenderTargetView();
		LightBuffer lightBuff;
		//lightBuff.LightProj = m_light->GetProj();
		lightBuff.LightProj = XMMatrixTranspose(m_light->GetProj());
		//lightBuff.LightView = m_light->GetView();
		lightBuff.LightView = XMMatrixTranspose(m_light->GetView());
		m_lightBuffer.Update(lightBuff);
	}

	void ShadowMapShader::FirstPassEnd()
	{
		// Setting to a default null render target view
		///ID3D11RenderTargetView* nulltargetview = NULL;

		//float color[4] = { 1, 1, 1, 1 };
		//TheGraphics::Instance()->GetContext()->OMSetRenderTargets(1, &(m_renderTargetView.m_renderTargetView), NULL);
		//TheGraphics::Instance()->GetContext()->ClearRenderTargetView((m_renderTargetView.m_renderTargetView), color);
	}


	void ShadowMapShader::SecondPassBegin()
	{
		// Changing render target veiw
		m_spvs.SetAsCurrentVertexShader();
		m_spps.SetAsCurrentPixelShader();
		m_sampler.SetAsCurrentSampler(1);
		m_shadowMapShaderResView.SetAsCurrentResourceView(0);	// Accessing the Shadowmap
		m_wvpb.SetAsVSConstantBuffer(0);	// Setting the address of the constant buffer in the VS
		m_lightBuffer.SetAsVSConstantBuffer(1);		// Setting the light constbuff to the VS light buffer

		// Setting backbuffer as current render target view
		TheGraphics::Instance()->SetAsCurrentRenderTargetView();

		// Updaing Light buffer
		LightBuffer lightBuff;
		lightBuff.LightProj = XMMatrixTranspose(m_light->GetProj());
		lightBuff.LightView = XMMatrixTranspose(m_light->GetView());
		m_lightBuffer.Update(lightBuff);

		WVPBuffer testBuff;
		testBuff.World = XMMatrixIdentity();
		testBuff.World = XMMatrixTranspose(testBuff.World);
		testBuff.Proj = XMMatrixLookAtLH(XMVectorSet(0, 1.0, 0.5, 1),
			XMVectorSet(0, 0, 0, 1),
			XMVectorSet(0, -1, 0, 1));

		testBuff.Proj = XMMatrixTranspose(testBuff.Proj);
		testBuff.View = XMMatrixPerspectiveLH(60.0f, 
			(TheGraphics::Instance()->GetScreenWidth() / TheGraphics::Instance()->GetScreenHeight()),
			0.1, 100.0);
		testBuff.View = XMMatrixTranspose(testBuff.View);
		m_wvpb.Update(testBuff);
	}
	
	
	void ShadowMapShader::SecondPassEnd()
	{
		// Setting to a default null render target view
		//ID3D11RenderTargetView* nulltargetview = NULL;

		//float color[4] = { 1, 1, 1, 1 };
		//TheGraphics::Instance()->GetContext()->OMSetRenderTargets(1, &(m_renderTargetView.m_renderTargetView), NULL);
		//TheGraphics::Instance()->GetContext()->ClearRenderTargetView((m_renderTargetView.m_renderTargetView), color);

		//TheGraphics::Instance()->GetContext()->OMSetRenderTargets(1, &nulltargetview, NULL);
		//TheGraphics::Instance()->SetAsCurrentRenderTargetView();
	}
}