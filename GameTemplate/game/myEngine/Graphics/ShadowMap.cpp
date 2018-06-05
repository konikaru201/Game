#include "stdafx.h"
#include "ShadowMap.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "../GameObject/GameObjectManager.h"

CShadowMap::CShadowMap()
{
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		D3DXMatrixIdentity(&m_lightViewMatrix[i]);
		D3DXMatrixIdentity(&m_lightProjMatrix[i]);
	}
	m_viewPosition = { 0.0f,0.0f,0.0f };
	m_viewTarget = { 0.0f,0.0f,0.0f };
	m_lightDirection = { 0.0f,-1.0f,0.0f };
}
CShadowMap::~CShadowMap()
{
}

//初期化。
void CShadowMap::Init()
{
	int w = 2048;	//幅
	int h = 2048;	//高さ
	//レンダリングターゲットを初期化。
	for (int i = 0; i < 3; i++) {
		m_renderTarget[i].Create(
			w,
			h,
			1,						
			D3DFMT_R32F,			
			D3DFMT_D16,				
			D3DMULTISAMPLE_NONE,	
			0						
		);

		w /= 2;
		h /= 2;
	}
}


//更新。
void CShadowMap::Update()
{
	//カメラの前方向を取得
	D3DXVECTOR3 cameraDirXZ = gameCamera->GetForward();
	cameraDirXZ.y = 0.0f;
	D3DXVec3Normalize(&cameraDirXZ, &cameraDirXZ);

	//影を落とす範囲を設定
	float shadowAreaTable[] = {
		20.0f,
		40.0f,
		80.0f
	};

	D3DXVECTOR3 lightPos;	//ライトの座標
	float nearPlaneZ = 0.0f;	//近平面までの距離
	float farPlaneZ;			//遠平面までの距離
	D3DXVECTOR3 cameraUp;		//カメラの上方向
	D3DXVec3Cross(&cameraUp, &gameCamera->GetRight(), &gameCamera->GetForward());
	//ライトのビュープロジェクション行列をシャドウマップの枚数分計算する。
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		farPlaneZ = nearPlaneZ + shadowAreaTable[i];
		//画角の半分を計算
		float halfViewAngle = gameCamera->GetAngle() * 0.5f;
		//視推台の8頂点をライト空間に変換してAABBを求めて、正射影の幅と高さを求める。
		float w, h;		//平行投影する幅と高さ
		D3DXVECTOR3 v[8];	//8頂点の座標
		{
			float t = tan(halfViewAngle);
			//近平面と遠平面の中心座標から端までのベクトルを計算。
			D3DXVECTOR3 toUpperNear, toUpperFar;
			toUpperNear = cameraUp * t * nearPlaneZ;
			toUpperFar = cameraUp * t * farPlaneZ;
			t *= gameCamera->GetAspect();
			//近平面の中心座標を計算。
			D3DXVECTOR3 vWk = gameCamera->GetPosition() + cameraDirXZ * nearPlaneZ;
			lightPos = vWk;
			v[0] = vWk + gameCamera->GetRight() * t * nearPlaneZ + toUpperNear;
			v[1] = v[0] - toUpperNear * 2.0f;

			v[2] = vWk + gameCamera->GetRight() * -t * nearPlaneZ + toUpperNear;
			v[3] = v[2] - toUpperNear * 2.0f;

			//遠平面の中心座標を計算。
			vWk = gameCamera->GetPosition() + cameraDirXZ * farPlaneZ;
			lightPos += vWk;
			v[4] = vWk + gameCamera->GetRight() * t * farPlaneZ + toUpperFar;
			v[5] = v[4] - toUpperFar * 2.0f;

			v[6] = vWk + gameCamera->GetRight() * -t * farPlaneZ + toUpperFar;
			v[7] = v[6] - toUpperFar * 2.0f;

			//ライトの座標を計算。
			lightPos *= 0.5f;
			lightPos += m_lightDirection * -m_lightHeight;

			//ライトの注視点を計算。
			D3DXVECTOR3 lightTarget = lightPos;
			lightTarget.y = -50.0f;

			//ライトビュー行列を計算。
			D3DXMatrixLookAtLH(&m_lightViewMatrix[i], &lightPos, &lightTarget, &cameraDirXZ);

			//視推台を構成する8頂点が計算できたので、ライト空間に座標変換して、AABBを求める。
			D3DXVECTOR3 vMax = { -FLT_MAX , -FLT_MAX , -FLT_MAX };
			D3DXVECTOR3 vMin = {  FLT_MAX ,  FLT_MAX ,  FLT_MAX };
			for (auto& vInLight : v) {
				//ワールド空間の座標からライト空間の座標に変換
				D3DXVec3TransformCoord(&vInLight, &vInLight, &m_lightViewMatrix[i]);
				D3DXVec3Maximize(&vMax, &vMax, &vInLight);
				D3DXVec3Minimize(&vMin, &vMin, &vInLight);
			}
			w = vMax.x - vMin.x;
			h = vMax.y - vMin.y;
		}

		//プロジェクション行列を計算。
		D3DXMatrixOrthoLH(
			&m_lightProjMatrix[i],
			w,
			h,
			0.1f,
			1000.0f
		);

		//ライトビュープロジェクション行列を作成。
		D3DXMatrixMultiply(&m_LVPMatrix[i], &m_lightViewMatrix[i], &m_lightProjMatrix[i]);

		//近平面を更新
		nearPlaneZ = farPlaneZ;
	}
}
//シャドウマップに書き込み。
void CShadowMap::Draw()
{
	LPDIRECT3DSURFACE9 renderTargetBackup;
	LPDIRECT3DSURFACE9 depthBufferBackup;
	g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);		//元々のレンダリングターゲットを保存。後で戻す必要があるので。
	g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);	//元々のデプスステンシルバッファを保存。後で戻す必要があるので。

	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		//レンダリングターゲットを変更する。
		g_pd3dDevice->SetRenderTarget(0, m_renderTarget[i].GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(m_renderTarget[i].GetDepthStencilBuffer());
		//書き込み先を変更したのでクリア。
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		goMgr->RenderToShadow(&m_lightViewMatrix[i], &m_lightProjMatrix[i], true, false);
	}
	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);		//戻す。
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);	//戻す。
}
