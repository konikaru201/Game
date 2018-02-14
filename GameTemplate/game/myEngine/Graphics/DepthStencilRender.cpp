#include "stdafx.h"
#include "DepthStencilRender.h"
#include "Player/Player.h"
#include "Scene/GameScene.h"

DepthStencilRender::DepthStencilRender()
{
}

DepthStencilRender::~DepthStencilRender()
{
}

bool DepthStencilRender::Start()
{
	return true;
}

void DepthStencilRender::Update()
{

}

void DepthStencilRender::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	if (player != nullptr) {
		player->DepthStencilRender(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
	}
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}