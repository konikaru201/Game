/*!
*@brief	ゲームシーンクラス
*/
#pragma once

#include "Map/Map.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "Scene/GameOverScene.h"
#include "Number/DisplayCoin.h"
#include "myEngine/Physics/Physics.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/Graphics/Silhouette.h"
#include "myEngine/Sound/SoundSource.h"


class GameScene : public GameObject {
public:
	/*!
	* @brief	コンストラクタ。
	*/
	GameScene();
	/*!
	* @brief	デストラクタ。
	*/
	~GameScene();
	/*!
	* @brief	更新する前に一度だけ呼ばれる関数。
	*/
	bool Start();
	/*!
	* @brief	更新。
	*/
	void Update();
	/*!
	* @brief	描画。
	*/
	void Render();
	/*!
	* @brief	ステージ作成
	* @param[in]	number		番号
	*/
	void StageCreate(int number);
	/*!
	* @brief	解放
	*/
	void Release();
	/*!
	* @brief	ステージ番号を設定
	* @param[in]	number		番号
	*/
	void SetStageNumber(int number);
	/*!
	* @brief	ゲーム進行の状態
	*/
	enum Step {
		step_WaitFadeIn,
		step_WaitGameOver,
		step_normal,
		step_StageLoad,
		step_GameOver,
		step_StageClear,
	};
	/*!
	* @brief	状態を返却
	* @return	状態
	*/
	const Step& IsStep() const
	{
		return m_step;
	}
	/*!
	* @brief	ステージクリアフラグを取得
	*/
	bool GetStageClearFlag() const
	{
		return m_stageClearFlag;
	}
	/*!
	* @brief	ゲームオーバーシーンの終了フラグを取得
	*/
	bool GetGameOverEnd() const
	{
		return m_gameOverSceneEnd;
	}
	/*!
	* @brief	ゲームオーバーシーンの状態を数字で取得
	*/
	int GetGameOverSceneStateNumber() const
	{
		return m_gameOverSceneStateNumber;
	}
private:
	GameOverScene*	m_gameOverScene = nullptr;		//ゲームオーバーシーン
	Silhouette*		m_silhouette;					//シルエット
	CSoundSource*	m_bgmSource = nullptr;			//BGM

	Step			m_step = step_StageLoad;		//状態

	float			m_timer = 0.0f;					//タイマー
	bool			m_gameOverSceneEnd = false;		//ゲームオーバーシーンの終了フラグ
	bool			m_stageClearFlag = false;		//ステージクリアフラグ
	int				m_gameOverSceneStateNumber = 0;	//ゲームオーバーシーンのステート番号
	int				m_stageNumber = 0;				//ステージ番号
	bool			m_restart = true;				//リスタートするか
};