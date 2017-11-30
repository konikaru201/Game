#pragma once

#include "myEngine/Physics/PlayerController.h"
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

	//影を描画
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	void DepthStencilRender(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);

	//移動
	//戻り値　移動速度を返す
	D3DXVECTOR3 Move();

	void Reset();

	//座標の取得
	D3DXVECTOR3 GetPosition() {
		return position;
	}

	//コインの獲得枚数を取得
	int GetCoinCount()
	{
		return CoinCount;
	}

	//スター獲得フラグを設定
	void SetGetStar(bool getstar)
	{
		getStar = getstar;
	}

	//コインの獲得枚数を更新
	void SetCoinCount(int Count)
	{
		CoinCount = Count;
	}

	//地面の上か判定
	bool GetIsOnGround()
	{
		if (playerController.IsOnGround()
			|| playerController.IsOnMoveFloor()
			|| playerController.IsOnMoveFloor2()
			|| playerController.IsOnSpring()
			|| playerController.IsOnBlock()
			|| playerController.IsOnBlock2()
			|| playerController.IsOnBox())
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

	//ブロック１
	//親のワールド行列を設定
	void SetParentWorldMatrix(D3DXMATRIX worldMatrix)
	{
		parentWorldMatrix = worldMatrix;
	}
	//親の回転行列を設定
	void SetParentRotationMatrix(D3DXMATRIX rotationMatrix)
	{
		parentRotationMatrix = rotationMatrix;
	}

	//ブロック２
	//親のワールド行列を設定
	void SetSecondParentWorldMatrix(D3DXMATRIX worldMatrix)
	{
		secondParentWorldMatrix = worldMatrix;
	}
	//親の回転行列を設定
	void SetSecondParentRotationMatrix(D3DXMATRIX rotationMatrix) 
	{
		secondParentRotationMatrix = rotationMatrix;
	}

	//スター獲得時のアニメーション終了フラグを取得
	bool GetStarAnimationEnd()
	{
		return animationEnd;
	}

	//プレイヤーの状態
	enum State {
		State_Move,				//移動
		State_Dead,				//死亡
		State_WallJump,			//壁ジャンプ
		State_GetStar,			//スターを獲得
	};

	//状態を取得　
	State GetState()
	{
		return state;
	}

	//アニメーションの状態
	enum AnimationNo {
		AnimationStand,	//立ち
		AnimationWalk,	//歩く
		AnimationRun,	//走る
		AnimationJump,	//ジャンプ
		AnimationPose,
	};

private:
	SkinModel model;												//スキンモデル
	SkinModelData modelData;										//スキンモデルデータ
	Animation animation;											//アニメーション
	PlayerController playerController;								//プレイヤーコントローラー
	D3DXVECTOR3	position;											//座標
	D3DXQUATERNION rotation;										//回転
	D3DXVECTOR3 dir = { 0.0f,0.0f,0.0f };							//方向
	AnimationNo currentAnim;										//現在のアニメーション
	AnimationNo prevAnim;											//前のアニメーション
	D3DXVECTOR3 playerDir;											//キャラクターのZ方向
	int JumpCount = 0;												//ジャンプの回数
	int JumpFrameCount = 0;											//次のジャンプをするまでのフレーム
	int CoinCount = 0;												//コインの獲得枚数
	float angle = 0.0f;												//回転角度
	float timer = 0.0f;												//タイマー
	D3DXVECTOR3 moveSpeed = { 0.0f,0.0f,0.0f };						//移動速度
	float acceleration = 0.0f;										//加速度
	float speedLimit = 8.0f;										//限界速度
	D3DXVECTOR3 currentDir = { 0.0f,0.0f,0.0f };					//1フレーム前のZ方向
	bool parentFirstHit = true;										//親との最初の当たり判定フラグ
	bool secondParentFirstHit = true;								//親との最初の当たり判定フラグ
	bool getStar = false;											//スター獲得フラグ
	State state = State_Move;
	bool animationEnd = false;

	bool isOnWall = false;
	bool wallJump = false;
	bool wallJumpExecute = false;

	D3DXMATRIX parentWorldMatrix;									//親のワールド行列
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };					//親のローカル座標からみたプレイヤーの座標
	D3DXMATRIX parentRotationMatrix;								//親の回転行列
	D3DXQUATERNION childRotation = { 0.0f,0.0f,0.0f,1.0f };			//親の回転座標からみたプレイヤーの回転

	D3DXMATRIX secondParentWorldMatrix;								//親のワールド行列
	D3DXVECTOR3 secondChildPosition = { 0.0f,0.0f,0.0f };			//親のローカル座標からみたプレイヤーの座標
	D3DXMATRIX secondParentRotationMatrix;							//親の回転行列
	D3DXQUATERNION secondChildRotation = { 0.0f,0.0f,0.0f,1.0f };	//親の回転座標からみたプレイヤーの回転

	LPDIRECT3DTEXTURE9 specularMap = NULL;							//スペキュラマップ
};

extern Player* g_player;