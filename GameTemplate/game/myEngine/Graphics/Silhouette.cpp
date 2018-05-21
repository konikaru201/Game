#include "stdafx.h"
#include "Silhouette.h"
#include "Player/Player.h"
#include "Scene/SceneManager.h"

Silhouette::Silhouette()
{
}

Silhouette::~Silhouette()
{
}

bool Silhouette::Start()
{
	return true;
}

void Silhouette::Update()
{

}

void Silhouette::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATER);
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//if (player != nullptr) {
	//	player->SilhouetteRender(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
	//}
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}