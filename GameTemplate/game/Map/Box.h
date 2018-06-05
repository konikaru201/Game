/*!
*@brief	ボックスクラス
*/
#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Box : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Box();
	/*!
	*@brief	デストラクタ
	*/
	~Box();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	*@brief	Render関数より後に呼ばれる描画関数
	*/
	void PostRender();
private:
	enum State {
		Entity,		//実体
		Clear		//透明
	};
	State			m_state = Entity;		//状態

	SkinModel		m_model;				//スキンモデル
	SkinModelData	m_modelData;			//スキンモデルデータ
	RigidBody		m_rigidBody;			//剛体
	Light			m_light;				//ライト
	D3DXVECTOR3		m_position;				//座標
	D3DXQUATERNION	m_rotation;				//回転
	float			m_timer = 0.0f;			//タイマー(透明になるまで)
	float			m_alpha = 1.0f;			//不透明度。0.0で透明
	const float		ALPHA_TIME = 0.5f;		//透明になるまでの時間
	float			m_alphaTimer = 0.0f;	//タイマー(実体になるまで)
};