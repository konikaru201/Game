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
	* @brief	�R���X�g���N�^�B
	*/
	GameScene();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~GameScene();
	/*!
	* @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	*/
	bool Start();
	/*!
	* @brief	�X�V�B
	*/
	void Update();
	/*!
	* @brief	�`��B
	*/
	void Render();

	//�X�e�[�W�쐬
	void StageCreate();

	//���
	void Release();

	//�Q�[���i�s�̏��
	enum Step {
		step_WaitFadeIn,
		step_WaitGameOver,
		step_normal,
		step_StageLoad,
		step_GameOver,
		step_StageClear,
	};

	//�X�e�[�W�̏��
	enum state_stage {
		en_Stage1,
		en_Stage2,
	};

	//�i�s�󋵂�ԋp
	const Step& IsStep()
	{
		return step;
	}

	//���݂���X�e�[�W���擾
	const state_stage& GetStateStage()
	{
		return currentStage;
	}

	//�t�F�[�h�A�E�g�҂��ł��邩�擾
	bool GetWaitFadeOut()
	{
		return m_waitFadeOut;
	}

private:
	Map* map;								//�}�b�v
	DepthStencilRender* depthStencilRender;	//�V���G�b�g
	CSoundSource* bgmSource = nullptr;		//BGM

	Step step = step_StageLoad;				//���
	state_stage currentStage = en_Stage1;	//���݂̃X�e�[�W�ԍ�
	state_stage nextStage = en_Stage2;		//���̃X�e�[�W�ԍ�

	float timer = 0.0f;						//�^�C�}�[
	bool m_waitFadeOut = false;				//�t�F�[�h�A�E�g�҂��t���O
};