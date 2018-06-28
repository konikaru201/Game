/*!
*@brief	シーンマネージャークラス
*/
#pragma once
#include "myEngine/GameObject/GameObject.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "Scene/GameScene.h"
#include "Number/RemainNumber.h"
#include "Number/DisplayCoin.h"
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
	*@brief	UIを描画
	*/
	void UIRender();
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
	const SceneState& GetScene() const
	{
		return m_state;
	}
	/*!
	*@brief	シーン切り替えフラグを取得
	*/
	bool GetChangeSceneFlag() const
	{
		return m_changeScene;
	}
	/*!
	*@brief	ステージセレクトシーンを取得
	*@return	ステージセレクトシーン
	*/
	CStageSelectScene* GetstageSelectScene() const
	{
		return m_stageSelectScene;
	}
	/*!
	*@brief	コインUIのインスタンスを取得
	*@return	コインUIのインスタンス
	*/
	DisplayCoin* GetCoinUI() const
	{
		return m_coinUI;
	}
	/*!
	*@brief	残機数のインスタンスを取得
	*@return	残機数のインスタンス
	*/
	RemainNumber* GetRemainNumber() const
	{
		return m_remainNumber;
	}
private:
	SceneState					m_state;						//現在のシーン
	FadeStep					m_step;							//フェードの状態
	TitleScene*					m_titleScene = nullptr;			//タイトルシーン
	CStageSelectScene*			m_stageSelectScene = nullptr;	//ステージセレクトシーン
	GameScene*					m_gameScene = nullptr;			//ゲームシーン
	bool						m_changeScene = false;			//シーン切り替えフラグ
	int							m_gameOverSceneStateNumber = 0;	//ゲームオーバーシーンのステート番号
	int							m_stageNumber = 1;
	DisplayCoin*				m_coinUI = nullptr;				//コイン枚数のスプライト
	RemainNumber*				m_remainNumber = nullptr;		//残機数のスプライト
	std::unique_ptr<Sprite>		m_coin = nullptr;				//コインの絵のスプライト
	std::unique_ptr<Sprite>		m_remain = nullptr;				//残機のスプライト
	std::unique_ptr<Sprite>		m_kakeru = nullptr;				//×記号のスプライト
	std::unique_ptr<Sprite>		m_kakeru2 = nullptr;
};

extern SceneManager* sceneManager;