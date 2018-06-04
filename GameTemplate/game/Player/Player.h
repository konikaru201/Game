#pragma once

#include "myEngine/Physics/PlayerController.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "PlayerStateMachine.h"
#include "IPlayerState.h"

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

	//座標の取得
	const D3DXVECTOR3& GetPosition() {
		return position;
	}

	//座標の設定
	void SetPosition(const D3DXVECTOR3& pos) 
	{
		position = pos;
	}

	//移動速度を取得
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return playerController.GetMoveSpeed();
	}

	//移動速度を設定
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		moveSpeed = speed;
	}

	//回転を取得
	const D3DXQUATERNION& GetRotation()
	{
		return rotation;
	}

	//回転を設定
	void SetRotation(const D3DXQUATERNION& rot)
	{
		rotation = rot;
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

	//ジャンプ中か判定
	bool GetIsJump()
	{
		return playerController.IsJump();
	}

	void SetIsJump()
	{
		playerController.Jump();
	}

	//アニメーション中か判定
	bool GetAnimationIsPlay()
	{
		return animation.IsPlay();
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

	void SetStarAnimationEnd(bool flag)
	{
		animationEnd = flag;
	}

	//敵を踏みつけ時のフラグを設定
	void SetTreadOnEnemy(bool treadOnEnemy)
	{
		m_treadOnEnemy = treadOnEnemy;
	}

	//バネを踏みつけ時のフラグを設定
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

	//プレイヤーが落下したフラグを取得
	bool GetFallPlayer()
	{
		return m_fallPlayer;
	}

	//プレイヤーの死亡フラグを設定
	void SetPlayerDead(bool playerDead)
	{
		m_playerDead = playerDead;
	}

	//プレイヤーの死亡フラグを取得
	bool GetPlayerDead()
	{
		return m_playerDead;
	}

	//スター獲得フラグを取得
	bool GetStar()
	{
		return getStar;
	}

	//スター獲得フラグを設定
	void SetGetStar(bool getstar)
	{
		getStar = getstar;
	}

	//現在のアニメーションを設定
	void SetCurrentAnim(IPlayerState::AnimationNo anim)
	{
		m_currentAnim = anim;
	}

	//現在のアニメーションを取得
	IPlayerState::AnimationNo GetCurrentAnim()
	{
		return m_currentAnim;
	}

	//1フレーム前のアニメーションを更新
	void SetPrevAnim(IPlayerState::AnimationNo anim)
	{
		m_prevAnim = anim;
	}

	//1フレーム前のアニメーションを取得
	IPlayerState::AnimationNo GetPrevAnim()
	{
		return m_prevAnim;
	}


private:
	SkinModel model;												//スキンモデル
	SkinModelData modelData;										//スキンモデルデータ
	Animation animation;											//アニメーション
	Light light;													//ライト
	PlayerController playerController;								//プレイヤーコントローラー
	D3DXVECTOR3	position;											//座標
	D3DXQUATERNION rotation;										//回転
	IPlayerState::AnimationNo m_currentAnim;						//現在のアニメーション
	IPlayerState::AnimationNo m_prevAnim;							//前のアニメーション
	D3DXVECTOR3 moveSpeed = { 0.0f,0.0f,0.0f };						//移動速度
	bool parentFirstHit = true;										//親との最初の当たり判定フラグ
	bool secondParentFirstHit = true;								//親との最初の当たり判定フラグ
	bool getStar = false;											//スター獲得フラグ
	bool animationEnd = false;										//スター獲得時のアニメーション終了フラグ
	bool m_treadOnEnemy = false;									//敵を踏んだフラグ
	float jumpSpeed = 10.0f;										//ジャンプ時の速度
	bool m_hitEnemy = false;										//敵に当たったフラグ
	bool m_fallPlayer = false;
	bool m_playerDead = false;										//プレイヤーの死亡フラグ
	bool m_treadOnSpring = false;									//スプリングを踏んだフラグ
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

	D3DXMATRIX parentWorldMatrix;									//親のワールド行列
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };					//親のローカル座標からみたプレイヤーの座標

	D3DXMATRIX secondParentWorldMatrix;								//親のワールド行列
	D3DXVECTOR3 secondChildPosition = { 0.0f,0.0f,0.0f };			//親のローカル座標からみたプレイヤーの座標

	LPDIRECT3DTEXTURE9 specularMap = NULL;							//スペキュラマップ
	LPDIRECT3DTEXTURE9 normalMap = NULL;							//法線マップ

	PlayerStateMachine m_playerStateMachine;						//ステートマシン
};

extern Player* player;