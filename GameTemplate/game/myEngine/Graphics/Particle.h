#pragma once

#include "Primitive.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/GameObject/GameObjectManager.h"

struct SParticleEmitParameter;

//パーティクル
class CParticle :  public GameObject{
public:
	//コンストラクタ
	CParticle();

	//デストラクタ
	~CParticle();

	//初期化
	void Init(const SParticleEmitParameter& param);
	
	//更新
	void Update();

	//描画
	void Render();

	enum State {
		State_Run,
		State_FadeOut,
		State_Dead,
	};

	State GetState()
	{
		return state;
	}
private:
	State				state;				//状態
	CPrimitive			primitive;			//プリミティブ
	LPDIRECT3DTEXTURE9	texture;			//テクスチャ
	ID3DXEffect*		shaderEffect;		//シェーダーエフェクト
	D3DXVECTOR3			moveSpeed;			//速度
	D3DXVECTOR3			position;			//座標
	float				life = 1.5f;		//寿命
	float				timer;				//タイマー
	float				alpha = 1.0f;		//透明度
	float				initAlpha = 1.0f;	//初期透明度
	const float			fadeTime = 1.0f;	//フェードタイム
};