#pragma once

#include "Map/Map.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "Scene/GameOverScene.h"
#include "Number/DisplayCoin.h"
#include "myEngine/Physics/Physics.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/Graphics/DepthStencilRender.h"
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
	* @brief	ゲームが起動してから一度だけ呼ばれる関数。
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

	//ステージ作成
	void StageCreate(int number);

	//解放
	void Release();

	//ステージ番号を設定
	void SetStageNumber(int number);

	//ゲーム進行の状態
	enum Step {
		step_WaitFadeIn,
		step_WaitGameOver,
		step_normal,
		step_StageLoad,
		step_GameOver,
		step_StageClear,
	};

	//進行状況を返却
	const Step& IsStep()
	{
		return step;
	}

	//ステージクリアフラグを取得
	bool GetStageClearFlag()
	{
		return m_stageClearFlag;
	}

	//ゲームオーバーシーンの終了フラグを取得
	bool GetGameOverEnd()
	{
		return m_gameOverSceneEnd;
	}

	//ゲームオーバーシーンの状態を数字で取得。
	int GetGameOverSceneStateNumber()
	{
		return m_gameOverSceneStateNumber;
	}
private:
	GameOverScene* gameOverScene = nullptr;
	//Map* map;								//マップ
	DepthStencilRender* depthStencilRender;	//シルエット
	CSoundSource* bgmSource = nullptr;		//BGM

	Step step = step_StageLoad;				//状態

	float timer = 0.0f;						//タイマー
	bool m_gameOverSceneEnd = false;		//ゲームオーバーシーンの終了フラグ
	bool m_stageClearFlag = false;			//ステージクリアフラグ
	int m_gameOverSceneStateNumber = 0;		//ゲームオーバーシーンのステート番号
	int m_stageNumber = 0;
};