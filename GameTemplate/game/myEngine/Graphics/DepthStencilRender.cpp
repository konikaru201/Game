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
	if (g_player != nullptr) {
		g_player->DepthStencilRender(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
	}
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}