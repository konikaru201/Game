#pragma once

#include "myEngine/Physics/PlayerController.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

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

	void SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);

	//移動
	//戻り値　移動速度を返す
	D3DXVECTOR3 Move();

	//座標の取得
	const D3DXVECTOR3& GetPosition() {
		return position;
	}

	//移動速度を取得
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return moveSpeed;
	}

	//スター獲得フラグを設定
	void SetGetStar(bool getstar)
	{
		getStar = getstar;
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

	//移動床１
	//移動床の速度を設定
	void SetMoveFloorSpeed(const D3DXVECTOR3& speed)
	{
		m_moveFloorSpeed = speed;
	}

	//移動床２
	//移動床の速度を設定
	void SetMoveFloor2Speed(const D3DXVECTOR3& speed)
	{
		m_moveFloor2Speed = speed;
	}

	//ブロック１
	//親のワールド行列を設定
	void SetParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		parentWorldMatrix = worldMatrix;
	}

	//ブロック２
	//親のワールド行列を設定
	void SetSecondParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		secondParentWorldMatrix = worldMatrix;
	}

	//スター獲得時のアニメーション終了フラグを取得
	bool GetStarAnimationEnd()
	{
		return animationEnd;
	}

	//敵を踏みつけ時のフラグを設定
	void SetTreadOnEnemy(bool treadOnEnemy)
	{
		m_treadOnEnemy = treadOnEnemy;
	}

	//スプリングを踏みつけ時のフラグを設定
	void SetTreadOnSpring(bool treadOnSpring) 
	{
		m_treadOnSpring = treadOnSpring;
	}

	//敵に当たった時のフラグを設定
	void SetHitEnemy(bool hitEnemy)
	{
		m_hitEnemy = hitEnemy;
	}

	//敵に当たった時のフラグを取得
	bool GetHitEnemy()
	{
		return m_hitEnemy;
	}

	//プレイヤーの死亡フラグを取得
	bool GetPlayerDead()
	{
		return m_playerDead;
	}

	//スター獲得フラグ
	bool GetStar()
	{
		return getStar;
	}

	//プレイヤーの状態
	enum State {
		State_Walk,				//移動
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
		AnimationPose,	//ポーズ
		AnimationDead,	//死亡
	};

private:
	SkinModel model;												//スキンモデル
	SkinModelData modelData;										//スキンモデルデータ
	Animation animation;											//アニメーション
	Light light;													//ライト
	PlayerController playerController;								//プレイヤーコントローラー
	D3DXVECTOR3	position;											//座標
	D3DXQUATERNION rotation;										//回転
	D3DXVECTOR3 dir = { 0.0f,0.0f,0.0f };							//方向
	AnimationNo currentAnim;										//現在のアニメーション
	AnimationNo prevAnim;											//前のアニメーション
	D3DXVECTOR3 playerDir;											//キャラクターのZ方向
	float angle = 0.0f;												//回転角度
	float timer = 0.0f;												//タイマー
	D3DXVECTOR3 moveSpeed = { 0.0f,0.0f,0.0f };						//移動速度
	float acceleration = 0.0f;										//加速度
	const float speedLimit = 6.0f;									//限界速度
	D3DXVECTOR3 currentDir = { 0.0f,0.0f,0.0f };					//1フレーム前のZ方向
	bool parentFirstHit = true;										//親との最初の当たり判定フラグ
	bool secondParentFirstHit = true;								//親との最初の当たり判定フラグ
	bool getStar = false;											//スター獲得フラグ
	State state = State_Walk;										//状態
	bool animationEnd = false;										//スター獲得時のアニメーション終了フラグ
	bool m_treadOnEnemy = false;									//敵を踏んだフラグ
	float jumpSpeed = 10.0f;										//ジャンプ時の速度
	bool m_hitEnemy = false;										//敵に当たったフラグ
	bool m_playerDead = false;										//プレイヤーの死亡フラグ
	bool m_treadOnSpring = false;									//スプリングを踏んだフラグ
	int m_rotationFrameCount = 0;									//回転フレームカウント
	bool m_moveFloorInertia = false;								//移動床の慣性
	bool m_moveFloor2Inertia = false;								//移動床２の慣性
	D3DXVECTOR3 m_airResistance = { 0.0f,0.0f,0.0f };				//空気抵抗
	float m_ineltiaTime = 0.0f;

	D3DXMATRIX moveFloorWorldMatrix;
	D3DXVECTOR3 moveFloorChildPosition = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_moveFloorSpeed = { 0.0f,0.0f,0.0f };

	D3DXMATRIX moveFloor2WorldMatrix;
	D3DXVECTOR3 moveFloor2ChildPosition = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_moveFloor2Speed = { 0.0f,0.0f,0.0f };

	bool isOnWall = false;
	bool wallJump = false;
	bool wallJumpExecute = false;

	D3DXMATRIX parentWorldMatrix;									//親のワールド行列
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };					//親のローカル座標からみたプレイヤーの座標

	D3DXMATRIX secondParentWorldMatrix;								//親のワールド行列
	D3DXVECTOR3 secondChildPosition = { 0.0f,0.0f,0.0f };			//親のローカル座標からみたプレイヤーの座標

	LPDIRECT3DTEXTURE9 specularMap = NULL;							//スペキュラマップ
	LPDIRECT3DTEXTURE9 normalMap = NULL;							//法線マップ
};

extern Player* player;