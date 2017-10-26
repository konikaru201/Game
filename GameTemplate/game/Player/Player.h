#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine/GameObject/GameObject.h"

class Player : public GameObject
{
public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//初期化
	bool Start();

	//更新
	void Update();

	//描画
	void Render();

	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//移動
	//戻り値　移動速度を返す
	D3DXVECTOR3 Move();

	void Reset();

	//座標の取得
	D3DXVECTOR3 GetPosition() {
		return position;
	}

	//死亡したかどうか
	bool GetIsDead()
	{
		return isDead;
	}

	//コインの獲得枚数を取得
	int GetCoinCount()
	{
		return CoinCount;
	}

	//コインの獲得枚数を更新
	void SetCoinCount(int Count)
	{
		CoinCount = Count;
	}

	//地面の上か判定
	bool GetIsOnGround()
	{
		if (characterController.IsOnGround()
			|| characterController.IsOnMoveFloor()
			|| characterController.IsOnMoveFloor2()
			|| characterController.IsOnJumpBlock())
		{
			return true;
		}
		return false;
	}

	//プレイヤーの向きを取得
	D3DXVECTOR3 GetPlayerDir()
	{
		D3DXMATRIX matrix = model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[2][0];
		direction.y = matrix.m[2][1];
		direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}

	//アニメーションの状態
	enum AnimationNo {
		AnimationStand,	//立ち
		AnimationWalk,	//歩く
		AnimationRun,	//走る
		AnimationJump,	//ジャンプ
	};
private:
	SkinModel model;								//スキンモデル
	SkinModelData modelData;						//スキンモデルデータ
	Animation animation;							//アニメーション
	CharacterController characterController;		//キャラクターコントローラー

	D3DXVECTOR3 MoveSpeed = { 0.0f,0.0f,0.0f };		//移動速度

	D3DXVECTOR3	position;							//座標
	D3DXQUATERNION rotation;						//回転
	D3DXVECTOR3 dir = { 0.0f,0.0f,1.0f };			//Z軸の方向
	AnimationNo currentAnim;						//現在のアニメーション
	AnimationNo prevAnim;							//前のアニメーション
	D3DXVECTOR3 playerDir;							
	int JumpCount = 0;								//ジャンプの回数
	int JumpFrameCount = 0;							//次のジャンプをするまでのフレーム
	int CoinCount = 0;								//コインの獲得枚数
	bool isDead = false;
	bool isOnWall = false;
	bool wallJump = false;
	bool wallJumpExecute = false;
	float timer = 0.0f;

	LPDIRECT3DTEXTURE9 specularMap = NULL;			//スペキュラマップ
};

extern Player* g_player;