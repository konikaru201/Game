#pragma once

#include "Map/Map.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "Scene/ResultScene.h"
#include "Number/DisplayCoin.h"
#include "myEngine/Physics/Physics.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"
#include "../myEngine/Graphics/DepthStencilRender.h"

namespace {
	//コインのスプライトのサイズと座標
	const D3DXVECTOR2 CoinSize = { 128.0f,72.0f };
	const D3DXVECTOR2 CoinPos = { 1000.0f, 600.0f };
}

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

	//スプライトの初期化
	void InitSprite();

	//解放
	void Release();

	//リセット
	void Reset();

	//ステージ作成
	void StageCreate();

	//カメラのインスタンスを取得
	GameCamera* GetGameCamera()
	{
		return gameCamera;
	}

	//ライトのインスタンス取得
	Light& GetLight()
	{
		return light;
	}

	//マップのインスタンスを取得
	Map* GetMap()
	{
		return map;
	}

	//スプライトの座標を取得
	const D3DXVECTOR2& GetCoinPos()
	{
		return CoinPos;
	}

	//ゲーム進行の状態
	enum Step {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_WaitGameOver,
		step_normal,
		step_StageLoad,
		step_GameOver,
		step_GameClear,
	};

	//ステージの状態
	enum state_stage {
		en_Stage1,
		en_Stage2,
	};

	//ステージ変更フラグを返却
	bool GetChengeStage()
	{
		return ChengeStage;
	}

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

private:
	Light light;					//ライト
	Map* map;						//マップ
	GameCamera* gameCamera;			//ゲームカメラ
	DisplayCoin* displayCoin;		//コイン枚数のスプライト
	Sprite* CoinNum;				//コインのスプライト
	DepthStencilRender* depthStencilRender;

	Step step = step_WaitFadeOut;
	state_stage currentStage = en_Stage1;	//現在のステージ番号
	state_stage nextStage = en_Stage2;		//次のステージ番号

	bool ChengeStage;			
	float timer = 0.0f;
	bool finishFadeOut = false;
};

extern GameScene* gameScene;