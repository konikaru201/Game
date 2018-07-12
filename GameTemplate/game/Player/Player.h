/*!
*@brief	プレイヤークラス
*/

#pragma once

#include "myEngine/Physics/PlayerController.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "PlayerStateMachine.h"
#include "IPlayerState.h"

class Player : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Player();
	/*!
	*@brief	デストラクタ
	*/
	~Player();
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	* @brief	影を描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	* @param[in]	isDrawShadowMap	シャドウマップを描くフラグ
	* @param[in]	isRecieveShadow	シャドウレシーバーかどうか
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	シルエットの描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	*/
	void SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);
	/*!
	*@brief	深度値を描画
	*/
	void RenderDepthValue();
	/*!
	* @brief	プレイヤーの座標の取得
	*@return	プレイヤーの座標
	*/
	const D3DXVECTOR3& GetPosition() const {
		return m_position;
	}
	/*!
	*@brief	座標の設定
	* @param[in]	pos		座標
	*/
	void SetPosition(const D3DXVECTOR3& pos) 
	{
		m_position = pos;
	}
	/*!
	* @brief	移動速度を取得
	*@return	移動速度
	*/
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_playerController.GetMoveSpeed();
	}
	/*!
	*@brief	移動速度を設定
	* @param[in]	speed	移動速度
	*/
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		m_moveSpeed = speed;
	}
	/*!
	* @brief	回転を取得
	*@return	回転
	*/
	const D3DXQUATERNION& GetRotation() const
	{
		return m_rotation;
	}
	/*!
	*@brief	回転を設定
	* @param[in]	rot		回転
	*/
	void SetRotation(const D3DXQUATERNION& rot)
	{
		m_rotation = rot;
	}
	/*!
	* @brief	地面の上か判定
	*/
	bool GetIsOnGround() const
	{
		if (m_playerController.IsOnGround()
			|| m_playerController.IsOnMoveFloor()
			|| m_playerController.IsOnMoveFloor2()
			|| m_playerController.IsOnSpring()
			|| m_playerController.IsOnBlock()
			|| m_playerController.IsOnBlock2()
			|| m_playerController.IsOnBox())
		{
			return true;
		}
		return false;
	}
	/*!
	* @brief	ジャンプ中か判定
	*/
	bool GetIsJump() const
	{
		return m_playerController.IsJump();
	}
	/*!
	*@brief	プレイヤーをジャンプさせる
	*/
	void SetIsJump()
	{
		m_playerController.Jump();
	}
	/*!
	* @brief	アニメーション中か判定
	*/
	bool GetAnimationIsPlay() const
	{
		return m_animation.IsPlay();
	}
	/*!
	* @brief	プレイヤーの向きを取得
	*@return	プレイヤーの向き
	*/
	D3DXVECTOR3 GetPlayerDir()
	{
		D3DXMATRIX matrix = m_model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[2][0];
		direction.y = matrix.m[2][1];
		direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}
	/*!
	* @brief	移動床１の速度を設定
	* @param[in]	speed		移動速度
	*/
	void SetMoveFloorSpeed(const D3DXVECTOR3& speed)
	{
		m_moveFloorSpeed = speed;
	}
	/*!
	* @brief	移動床２の速度を設定
	* @param[in]	speed		移動速度
	*/
	void SetMoveFloor2Speed(const D3DXVECTOR3& speed)
	{
		m_moveFloor2Speed = speed;
	}
	/*!
	* @brief	ブロック１のワールド行列を設定
	* @param[in]	worldMatrix		ワールド行列
	*/
	void SetParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		m_parentWorldMatrix = worldMatrix;
	}
	/*!
	* @brief	ブロック２のワールド行列を設定
	* @param[in]	worldMatrix		ワールド行列
	*/
	void SetSecondParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		m_secondParentWorldMatrix = worldMatrix;
	}
	/*!
	* @brief	ステージ変更時のアニメーション終了フラグを取得
	*/
	bool GetAnimationEnd() const
	{
		return m_animationEnd;
	}
	/*!
	* @brief	ステージ変更時のアニメーション終了フラグを設定
	* @param[in]	flag		ステージ変更時のアニメーションが終了したか
	*/
	void SetAnimationEnd(bool flag)
	{
		m_animationEnd = flag;
	}
	/*!
	* @brief	敵を踏みつけ時のフラグを設定
	* @param[in]	treadOnEnemy		敵を踏みつけたか
	*/
	void SetTreadOnEnemy(bool treadOnEnemy)
	{
		m_treadOnEnemy = treadOnEnemy;
	}
	/*!
	* @brief	バネを踏みつけ時のフラグを設定
	* @param[in]	treadOnSpring		バネを踏みつけたか
	*/
	void SetTreadOnSpring(bool treadOnSpring) 
	{
		m_treadOnSpring = treadOnSpring;
	}
	/*!
	* @brief	敵に当たった時のフラグを設定
	* @param[in]	hitEnemy		敵に当たったか
	*/
	void SetHitEnemy(bool hitEnemy)
	{
		m_hitEnemy = hitEnemy;
	}
	/*!
	* @brief	敵に当たった時のフラグを取得
	*/
	bool GetHitEnemy() const
	{
		return m_hitEnemy;
	}
	/*!
	* @brief	プレイヤーが落下したフラグを取得
	*/
	bool GetFallPlayer() const
	{
		return m_fallPlayer;
	}
	/*!
	* @brief	プレイヤーの死亡フラグを設定
	* @param[in]	playerDead		プレイヤーの死亡フラグ
	*/
	void SetPlayerDead(bool playerDead)
	{
		m_playerDead = playerDead;
	}
	/*!
	* @brief	プレイヤーの死亡フラグを取得
	*/
	bool GetPlayerDead() const
	{
		return m_playerDead;
	}
	/*!
	* @brief	ステージ変更フラグを取得
	*/
	bool GetChangeStage() const
	{
		return m_changeStage;
	}
	/*!
	* @brief	ステージ変更フラグを設定
	* @param[in]	changeStage		ステージ変更フラグ
	*/
	void SetChangeStage(bool changeStage)
	{
		m_changeStage = changeStage;
	}
	/*!
	* @brief	現在のアニメーションを設定
	* @param[in]	anim		現在のアニメーション
	*/
	void SetCurrentAnim(IPlayerState::AnimationNo anim)
	{
		m_currentAnim = anim;
	}
	/*!
	* @brief	現在のアニメーションを取得
	*@return	現在のアニメーション
	*/
	IPlayerState::AnimationNo GetCurrentAnim() const
	{
		return m_currentAnim;
	}
	/*!
	* @brief	1つ前のアニメーションを更新
	* @param[in]	anim		1つ前のアニメーション
	*/
	void SetPrevAnim(IPlayerState::AnimationNo anim)
	{
		m_prevAnim = anim;
	}
	/*!
	* @brief	1つ前のアニメーションを取得
	*@return	1つ前のアニメーション
	*/
	IPlayerState::AnimationNo GetPrevAnim() const
	{
		return m_prevAnim;
	}
	/*!
	* @brief	ステージセレクトシーンか判定
	*/
	bool GetSceneSelectFlag() const
	{
		return m_sceneSelect;
	}
	/*!
	* @brief	タイトルシーンか判定
	*/
	bool GetSceneTitleFlag() const
	{
		return m_sceneTitle;
	}
private:
	SkinModel			m_model;								//スキンモデル
	SkinModelData		m_modelData;							//スキンモデルデータ
	Animation			m_animation;							//アニメーション
	Light				m_light;								//ライト
	PlayerController	m_playerController;						//プレイヤーコントローラー
	D3DXVECTOR3			m_position;								//座標
	D3DXQUATERNION		m_rotation;								//回転
	IPlayerState::AnimationNo m_currentAnim;					//現在のアニメーション
	IPlayerState::AnimationNo m_prevAnim;						//前のアニメーション
	D3DXVECTOR3			m_moveSpeed = { 0.0f,0.0f,0.0f };		//移動速度
	bool				m_parentFirstHit = true;				//親との最初の当たり判定フラグ
	bool				m_secondParentFirstHit = true;			//親との最初の当たり判定フラグ
	bool				m_changeStage = false;					//ステージ変更フラグ
	bool				m_animationEnd = false;					//スター獲得時のアニメーション終了フラグ
	bool				m_treadOnEnemy = false;					//敵を踏んだフラグ
	const float			m_jumpSpeed = 10.0f;					//ジャンプ時の速度
	bool				m_hitEnemy = false;						//敵に当たったフラグ
	bool				m_fallPlayer = false;					//プレイヤーの落下フラグ
	bool				m_playerDead = false;					//プレイヤーの死亡フラグ
	bool				m_treadOnSpring = false;				//スプリングを踏んだフラグ
	bool				m_moveFloorInertia = false;				//移動床の慣性
	bool				m_moveFloor2Inertia = false;			//移動床２の慣性
	D3DXVECTOR3			m_airResistance = { 0.0f,0.0f,0.0f };	//空気抵抗
	float				m_ineltiaTime = 0.0f;					//慣性が働く時間
	bool				m_sceneSelect = false;					//ステージセレクトシーンかどうか
	bool				m_sceneTitle = false;

	D3DXMATRIX			m_moveFloorWorldMatrix;							//移動床１のワールド行列
	D3DXVECTOR3			m_moveFloorChildPosition = { 0.0f,0.0f,0.0f };	//移動床１から見たプレイヤーのローカル座標
	D3DXVECTOR3			m_moveFloorSpeed = { 0.0f,0.0f,0.0f };			//移動床１の移動速度
	D3DXMATRIX			m_moveFloor2WorldMatrix;						//移動床２のワールド行列
	D3DXVECTOR3			m_moveFloor2ChildPosition = { 0.0f,0.0f,0.0f };	//移動床２から見たプレイヤーのローカル座標
	D3DXVECTOR3			m_moveFloor2Speed = { 0.0f,0.0f,0.0f };			//移動床２の移動速度

	D3DXMATRIX			m_parentWorldMatrix;							//ブロック１のワールド行列
	D3DXVECTOR3			m_childPosition = { 0.0f,0.0f,0.0f };			//ブロック１のローカル座標からみたプレイヤーの座標

	D3DXMATRIX			m_secondParentWorldMatrix;						//ブロック２のワールド行列
	D3DXVECTOR3			m_secondChildPosition = { 0.0f,0.0f,0.0f };		//ブロック２のローカル座標からみたプレイヤーの座標

	LPDIRECT3DTEXTURE9	m_specularMap = NULL;					//スペキュラマップ
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;						//法線マップ

	PlayerStateMachine	m_playerStateMachine;					//ステートマシン
};

extern Player* player;