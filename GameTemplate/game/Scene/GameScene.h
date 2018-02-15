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
	void StageCreate();

	//解放
	void Release();

	//ゲーム進行の状態
	enum Step {
		step_WaitFadeIn,
		step_WaitGameOver,
		step_normal,
		step_StageLoad,
		step_GameOver,
		step_StageClear,
	};

	//ステージの状態
	enum state_stage {
		en_Stage1,
		en_Stage2,
	};

	//進行状況を返却
	const Step& IsStep()
	{
		return step;
	}

	//現在いるステージを取得
	const state_stage& GetStateStage()
	{
		return currentStage;
	}

	//フェードアウト待ちであるか取得
	bool GetWaitFadeOut()
	{
		return m_waitFadeOut;
	}

private:
	Map* map;								//マップ
	DepthStencilRender* depthStencilRender;	//シルエット
	CSoundSource* bgmSource = nullptr;		//BGM

	Step step = step_StageLoad;				//状態
	state_stage currentStage = en_Stage1;	//現在のステージ番号
	state_stage nextStage = en_Stage2;		//次のステージ番号

	float timer = 0.0f;						//タイマー
	bool m_waitFadeOut = false;				//フェードアウト待ちフラグ
};