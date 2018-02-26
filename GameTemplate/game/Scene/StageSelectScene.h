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

class CStageSelectScene : public GameObject
{
public:
	//コンストラクタ
	CStageSelectScene();

	//デストラクタ
	~CStageSelectScene();

	//更新される前に一度だけ呼ばれる関数
	bool Start();

	//更新
	void Update();

	//描画
	void Render();

	//ステージ作成
	void StageCreate();

	//解放
	void Release();

	//ゲーム進行の状態
	enum Step {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_normal,		//通常時
		step_StageLoad,		//ステージをロード
	};

	//フェードアウト待ちであるか取得
	bool GetWaitFadeOut()
	{
		return m_waitFadeOut;
	}

	//ステージ番号を取得
	int GetStageNumber()
	{
		return stageNumber;
	}

private:
	Map* map;									//マップ
	DepthStencilRender* depthStencilRender;		//シルエット
	Step step = step_WaitFadeOut;				//状態
	CSoundSource* bgmSource = nullptr;			//BGM
	bool m_waitFadeOut = false;					//フェードアウト待ちフラグ
	int stageNumber = 0;
};