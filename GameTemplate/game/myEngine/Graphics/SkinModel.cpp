#include "stdafx.h"
#include "myEngine/Graphics/SkinModel.h"
#include "myEngine/Graphics/SkinModelData.h"
#include "myEngine/Graphics/Light.h"
#include "Scene/GameScene.h"
#include "Scene/TitleScene.h"
#include "ShadowMap.h"

extern UINT                 g_NumBoneMatricesMax;
extern D3DXMATRIXA16*       g_pBoneMatrices ;
namespace {
	void DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice, 
		LPD3DXMESHCONTAINER pMeshContainerBase, 
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		const D3DXMATRIX* viewMatrix,
		const D3DXMATRIX* projMatrix,
		Light* light,
		LPDIRECT3DTEXTURE9 specularMap,
		LPDIRECT3DTEXTURE9 normalMap,
		LPDIRECT3DCUBETEXTURE9 cubeMap,
		bool isDrawShadowMap,
		bool isRecieveShadow,
		bool isDepthStencilRender
	)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
		D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
		UINT iAttrib;
		LPD3DXBONECOMBINATION pBoneComb;

		D3DXMATRIXA16 matTemp;
		D3DCAPS9 d3dCaps;
		pd3dDevice->GetDeviceCaps(&d3dCaps);
		D3DXMATRIX viewProj;
		D3DXMatrixMultiply(&viewProj, viewMatrix, projMatrix);
		
		//テクニックを設定。
		{
			if (pMeshContainer->pSkinInfo != NULL) {
				if (!isDrawShadowMap) {
					pEffect->SetTechnique("SkinModel");
				}
				else {
					pEffect->SetTechnique("SkinModelRenderToShadowMap");
				}
				if (isDepthStencilRender) {
					pEffect->SetTechnique("DepthStencilRender");
				}
			}
			else {
				if (!isDrawShadowMap) {
					pEffect->SetTechnique("NoSkinModel");
				}
				else {
					pEffect->SetTechnique("NoSkinModelRenderToShadowMap");
				}
				if (isDepthStencilRender) {
					pEffect->SetTechnique("NoSkinDepthStencilRender");
				}
			}
		}
		//共通の定数レジスタを設定
		{
			//ビュープロジェクション
			pEffect->SetMatrix("g_mViewProj", &viewProj);
			//ライト
			pEffect->SetValue(
				"g_light",
				light,
				sizeof(Light)
			);
			//シャドウレシーバーフラグを転送
			pEffect->SetBool("g_isShadowReciever", isRecieveShadow);
		}
		if (specularMap != NULL) {
			//スペキュラマップがあるので、シェーダーに転送する。
			pEffect->SetTexture("g_specularTexture", specularMap);
			//スペキュラマップのあり、なしのフラグをtrueにする。
			pEffect->SetBool("g_isHasSpecularMap", true);
		}
		else {
			//スペキュラマップのあり、なしのフラグをfalseにする。
			pEffect->SetBool("g_isHasSpecularMap", false);
		}
		if (normalMap != NULL) {
			//法線マップがあるので、シェーダーに転送する。
			pEffect->SetTexture("g_normalTexture", normalMap);
			//法線マップのあり、なしのフラグをtrueにする。
			pEffect->SetBool("g_isHasNormalMap", true);
		}
		else {
			//法線マップのあり、なしのフラグをfalseにする。
			pEffect->SetBool("g_isHasNormalMap", false);
		}
		if (cubeMap != NULL) {
			//キューブマップがあるので、シェーダーに転送する。
			pEffect->SetTexture("g_cubeTexture", cubeMap);
			pEffect->SetTechnique("NoSkinModelSkyCubeMap");
		}
		if (isRecieveShadow) {
			pEffect->SetTexture("g_shadowMapTexture", g_shadowMap.GetTexture());
			pEffect->SetMatrix("g_lightViewMatrix", &g_shadowMap.GetLightViewMatrix());
			pEffect->SetMatrix("g_lightProjectionMatrix", &g_shadowMap.GetLightProjectionMatrix());
		}
		if (pMeshContainer->pSkinInfo != NULL)
		{
			//スキン情報有り。
			pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
			for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
			{
				// first calculate all the world matrices
				for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
				{
					DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(
							&g_pBoneMatrices[iPaletteEntry],
							&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
						);
						//D3DXMatrixMultiply(&g_pBoneMatrices[iPaletteEntry], &matTemp, &g_matView);
					}
				}
			
				
				pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
				pEffect->SetInt("g_numBone", pMeshContainer->NumInfl);
				// ディフューズテクスチャ。
				pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

				D3DXVECTOR3 cameraPos = gameScene->GetGameCamera()->GetPosition();
				D3DXVECTOR4 vEyePos = { 0.0f,0.0f,0.0f,1.0f };
				vEyePos.x = cameraPos.x;
				vEyePos.y = cameraPos.y;
				vEyePos.z = cameraPos.z;
				pEffect->SetVector("vEyePos", &vEyePos);

				// ボーン数。
				pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
				D3DXMATRIX viewRotInv;
				D3DXMatrixInverse(&viewRotInv, NULL, viewMatrix);
				viewRotInv.m[3][0] = 0.0f;
				viewRotInv.m[3][1] = 0.0f;
				viewRotInv.m[3][2] = 0.0f;
				viewRotInv.m[3][3] = 1.0f;
				D3DXMatrixTranspose(&viewRotInv, &viewRotInv);
				pEffect->SetMatrix("g_viewMatrixRotInv", &viewRotInv);
				pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
				pEffect->BeginPass(0);
				pEffect->CommitChanges();
				// draw the subset with the current world matrix palette and material state
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				pEffect->EndPass();
				pEffect->End();

			}
		}
		else {
						
			D3DXMATRIX mWorld;
			if (pFrame != NULL) {
				mWorld = pFrame->CombinedTransformationMatrix;
			}
			else {
				mWorld = *worldMatrix;
			}
			
			pEffect->SetMatrix("g_worldMatrix", &mWorld);
			pEffect->SetMatrix("g_rotationMatrix", rotationMatrix);
			pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
			pEffect->BeginPass(0);

			for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++) {
				pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
				pEffect->CommitChanges();
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
			}
			pEffect->EndPass();
			pEffect->End();
		}
	}
	void DrawFrame(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXFRAME pFrame,
		ID3DXEffect* pEffect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		const D3DXMATRIX* viewMatrix,
		const D3DXMATRIX* projMatrix,
		Light* light,
		LPDIRECT3DTEXTURE9 specularMap,
		LPDIRECT3DTEXTURE9 normalMap,
		LPDIRECT3DCUBETEXTURE9 cubeMap,
		bool isDrawShadowMap,
		bool isRecieveShadow,
		bool isDepthStencilRender
	)
	{
		LPD3DXMESHCONTAINER pMeshContainer;

		pMeshContainer = pFrame->pMeshContainer;
		while (pMeshContainer != NULL)
		{
			DrawMeshContainer(
				pd3dDevice, 
				pMeshContainer, 
				pFrame, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				specularMap,
				normalMap,
				cubeMap,
				isDrawShadowMap,
				isRecieveShadow,
				isDepthStencilRender
				);

			pMeshContainer = pMeshContainer->pNextMeshContainer;
		}

		if (pFrame->pFrameSibling != NULL)
		{
			DrawFrame(
				pd3dDevice, 
				pFrame->pFrameSibling, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				specularMap,
				normalMap,
				cubeMap,
				isDrawShadowMap,
				isRecieveShadow,
				isDepthStencilRender
				);
		}

		if (pFrame->pFrameFirstChild != NULL)
		{
			DrawFrame(
				pd3dDevice, 
				pFrame->pFrameFirstChild, 
				pEffect,
				worldMatrix,
				rotationMatrix,
				viewMatrix,
				projMatrix,
				light,
				specularMap,
				normalMap,
				cubeMap,
				isDrawShadowMap,
				isRecieveShadow,
				isDepthStencilRender
				);
		}
	}
}
SkinModel::SkinModel() :
	skinModelData(nullptr),
	light(nullptr),
	pEffect(nullptr)
{
}
SkinModel::~SkinModel()
{

}

void SkinModel::Init(SkinModelData* modelData)
{
	pEffect = g_effectManager->LoadEffect("Assets/Shader/Model.fx");
	skinModelData = modelData;
}
void SkinModel::UpdateWorldMatrix(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale)
{
	D3DXMATRIX mTrans, mScale;
	D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&mTrans, trans.x, trans.y, trans.z);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &rot);

	worldMatrix = mScale * rotationMatrix * mTrans;

	if (skinModelData) {
		skinModelData->UpdateBoneMatrix(worldMatrix);	//ボーン行列を更新。
	}
}

void SkinModel::Draw(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	if (skinModelData) {
		DrawFrame(
			g_pd3dDevice, 
			skinModelData->GetFrameRoot(), 
			pEffect,
			&worldMatrix,
			&rotationMatrix,
			viewMatrix,
			projMatrix,
			light,
			specularMap,
			normalMap,
			cubeMap,
			isDrawShadowMap,
			isRecieveShadow,
			isDepthStencilRender
		);
	}
}
LPD3DXMESH SkinModel::GetOrgMeshFirst()
{
	if(skinModelData != nullptr){
		return skinModelData->GetOrgMeshFirst();
	}
	return nullptr;
}