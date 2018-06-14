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
	*@param[in]		changeStage		ステージ変更フラグ
	*@param[in]		number			ステージ番号
	*/
	void SetChangeStage(bool changeStage, int number) 
	{
		m_changeStage = changeStage;
		m_stageNumber = number;
	}
	/*!
	*@brief	表示するAボタンを設定
	*@param[in]		bottonRender	Aボタンを表示するか	
	*@param[in]		number	ステージの番号
	*/
	void SetBottonReneder(bool bottonRender, int number)
	{
		m_bottonRender[number] = bottonRender;
	}
	/*!
	*@brief	Aボタンを表示しているか
	*/
	bool GetBottonRender()
	{
		for (int i = 0; i < 3; i++) {
			if (m_bottonRender[i] == true) {
				return true;
			}
		}
		return false;
	}

private:
	Silhouette*		silhouette;				//シルエット
	Step			m_step = step_WaitFadeOut;	//状態
	CSoundSource*	bgmSource = nullptr;		//BGM
	bool			m_waitFadeOut = false;		//フェードアウト待ちフラグ
	int				m_stageNumber = 0;			//ステージ番号
	bool			m_changeStage = false;		//ステージを変更するか
	bool			m_bottonRender[3];			//ボタンを表示するか
};