#pragma once

#include "Map/Map.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "Scene/ResultScene.h"
#include "Number/DisplayCoin.h"
#include "myEngine/Physics/Physics.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"

namespace {
	//コインのスプライトのサイズと座標
	const D3DXVECTOR2 CoinSize = { 250.0f,160.0f };
	const D3DXVECTOR2 CoinPos = { 800.0f,-550.0f };
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

	//プレイヤーのインスタンス取得
	Player* GetPlayer()
	{
		return player;
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
	D3DXVECTOR2 GetCoinPos()
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
	Step IsStep()
	{
		return step;
	}
private:
	Light light;					//ライト
	Map* map;						//マップ
	Player* player;					//プレイヤー
	GameCamera* gameCamera;			//ゲームカメラ
	DisplayCoin* displayCoin;		//コイン枚数のスプライト
	Sprite* CoinNum;				//コインのスプライト

	Step step = step_WaitFadeOut;
	state_stage currentStage = en_Stage1;	//現在のステージ番号
	state_stage nextStage = en_Stage2;		//次のステージ番号

	bool ChengeStage;			
	float timer = 0.0f;
	bool finishFadeOut = false;
};

extern GameScene* gameScene;