/*!
*@brief	シーンマネージャークラス
*/
#pragma once
#include "myEngine/GameObject/GameObject.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"

class SceneManager : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	SceneManager();
	/*!
	*@brief	デストラクタ
	*/
	~SceneManager();
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	シーンの状態
	*/
	enum SceneState {
		stateTitle,			//タイトル
		stateGame,			//ゲーム
		stateGameOver,		//ゲームオーバー
		stateStageSelect,	//ステージセレクト
	};
	/*!
	*@brief	フェードの状態
	*/
	enum FadeStep {
		step_WaitFadeIn,	//フェードイン
		step_WaitFadeOut,	//フェードアウト
		step_normal,		//何もない
	};
	/*!
	*@brief	現在のシーンを取得
	*@return	現在のシーン
	*/
	const SceneState& GetScene() {
		return m_state;
	}
	/*!
	*@brief	シーン切り替えフラグを取得
	*/
	bool GetChangeSceneFlag()
	{
		return m_changeScene;
	}
	/*!
	*@brief	ステージセレクトシーンを取得
	*@return	ステージセレクトシーン
	*/
	CStageSelectScene* GetstageSelectScene()
	{
		return m_stageSelectScene;
	}
private:
	SceneState			m_state;						//現在のシーン
	FadeStep			m_step;							//フェードの状態
	TitleScene*			m_titleScene = nullptr;			//タイトルシーン
	CStageSelectScene*	m_stageSelectScene = nullptr;	//ステージセレクトシーン
	GameScene*			m_gameScene = nullptr;			//ゲームシーン
	bool				m_changeScene = false;			//シーン切り替えフラグ
	int					m_gameOverSceneStateNumber = 0;	//ゲームオーバーシーンのステート番号
	int					m_stageNumber = 1;
};

extern SceneManager* sceneManager;