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
	void StageCreate(int number);

	//���
	void Release();

	//�X�e�[�W�ԍ���ݒ�
	void SetStageNumber(int number);

	//�Q�[���i�s�̏��
	enum Step {
		step_WaitFadeIn,
		step_WaitGameOver,
		step_normal,
		step_StageLoad,
		step_GameOver,
		step_StageClear,
	};

	//�i�s�󋵂�ԋp
	const Step& IsStep()
	{
		return step;
	}

	//�X�e�[�W�N���A�t���O���擾
	bool GetStageClearFlag()
	{
		return m_stageClearFlag;
	}

	//�Q�[���I�[�o�[�V�[���̏I���t���O���擾
	bool GetGameOverEnd()
	{
		return m_gameOverSceneEnd;
	}

	//�Q�[���I�[�o�[�V�[���̏�Ԃ𐔎��Ŏ擾�B
	int GetGameOverSceneStateNumber()
	{
		return m_gameOverSceneStateNumber;
	}
private:
	GameOverScene* gameOverScene = nullptr;
	//Map* map;								//�}�b�v
	DepthStencilRender* depthStencilRender;	//�V���G�b�g
	CSoundSource* bgmSource = nullptr;		//BGM

	Step step = step_StageLoad;				//���

	float timer = 0.0f;						//�^�C�}�[
	bool m_gameOverSceneEnd = false;		//�Q�[���I�[�o�[�V�[���̏I���t���O
	bool m_stageClearFlag = false;			//�X�e�[�W�N���A�t���O
	int m_gameOverSceneStateNumber = 0;		//�Q�[���I�[�o�[�V�[���̃X�e�[�g�ԍ�
	int m_stageNumber = 0;
};