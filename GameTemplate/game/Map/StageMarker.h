/*!
*@brief	ステージマーカークラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Graphics/ParticleEmitter.h"

class StageMarker : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	StageMarker();
	/*!
	*@brief	デストラクタ
	*/
	~StageMarker();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);
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
	* @brief	座標の取得
	*@return	座標
	*/
	const D3DXVECTOR3& GetPosition() {
		return m_position;
	}
	/*!
	*@brief	UI描画フラグを取得
	*/
	bool GetUIRenderFlag()
	{
		return m_UIRender;
	}
	/*!
	*@brief	ステージ変更フラグを取得
	*/
	bool GetStageChangeFlag()
	{
		return m_stageChange;
	}
	/*!
	* @brief	ステージ番号の取得
	*@return	ステージ番号
	*/
	int GetStageNumber() {
		return m_stageNumber;
	}
	/*!
	*@brief	決定フラグを取得
	*/
	bool GetDecisionFlag()
	{
		return m_decision;
	}
private:
	SkinModel			m_model;				//スキンモデル
	SkinModelData		m_modelData;			//スキンモデルデータ
	MeshCollider		m_meshCollider;			//メッシュコライダー
	RigidBody			m_rigidBody;			//剛体
	Light				m_light;				//ライト
	D3DXVECTOR3			m_position;				//座標
	D3DXQUATERNION		m_rotation;				//回転
	D3DXMATRIX			m_parentWorldMatrix;	//親のワールド行列
	D3DXVECTOR3			m_childPosition;		//親から見た座標
	D3DXQUATERNION		m_childRotation;		//親から見た回転
	const int			m_stageNumber = 1;		//ステージ番号
	bool				m_decision = false;		//決定を押したか
	bool				m_UIRender = false;		//UIを描画するフラグ
	bool				m_stageChange = false;	//ステージ変更フラグ
	CParticleEmitter	m_particleEmitter;		//パーティクル生成
};
