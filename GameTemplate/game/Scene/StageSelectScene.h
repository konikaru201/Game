/*!
*@brief	ステージセレクトシーンクラス
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

class CStageSelectScene : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	CStageSelectScene();
	/*!
	*@brief	デストラクタ
	*/
	~CStageSelectScene();
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
	*@brief	後から描画
	*/
	void PostRender();
	/*!
	*@brief	ステージ作成
	*/
	void StageCreate();
	/*!
	*@brief	解放
	*/
	void Release();
	/*!
	*@brief	ゲーム進行の状態
	*/
	enum Step {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_normal,		//通常時
		step_StageLoad,		//ステージをロード
	};
	/*!
	*@brief	フェードアウト待ちであるか取得
	*/
	bool GetWaitFadeOut()
	{
		return m_waitFadeOut;
	}
	/*!
	*@brief	ステージ番号を取得
	*/
	int GetStageNumber()
	{
		return m_stageNumber;
	}
	/*!
	*@brief	ステージ番号を設定
	*@param[in]		number			ステージ番号
	*/
	void SetStageNumber(int number)
	{
		m_stageNumber = number;
	}
	/*!
	*@brief	ステージ変更フラグを取得
	*/
	int GetChangeStageFlag()
	{
		return m_changeStage;
	}
	/*!
	*@brief	ステージ変更フラグを設定
	*@param[in]		changeStage		ステージ変更フラグ
	*/
	void SetChangeStage(bool changeStage)
	{
		m_changeStage = changeStage;
	}
private:
	Silhouette*		m_silhouette;				//シルエット
	Step			m_step = step_WaitFadeOut;	//状態
	CSoundSource*	m_bgmSource = nullptr;		//BGM
	Sprite*			m_stage1;					//ステージ１
	Sprite*			m_stage2;					//ステージ２
	Sprite*			m_stage3;					//ステージ３
	Sprite*			m_aBotton = nullptr;		//Aボタン表示のスプライト
	bool			m_waitFadeOut = false;		//フェードアウト待ちフラグ
	int				m_stageNumber = 0;			//ステージ番号
	bool			m_changeStage = false;		//ステージを変更するか
	bool			m_bottonRender[3];			//ボタンを表示するか
};