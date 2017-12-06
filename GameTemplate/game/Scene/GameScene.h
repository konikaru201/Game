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
	//�R�C���̃X�v���C�g�̃T�C�Y�ƍ��W
	const D3DXVECTOR2 CoinSize = { 128.0f,72.0f };
	const D3DXVECTOR2 CoinPos = { 1000.0f, 600.0f };
}

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

	//�X�v���C�g�̏�����
	void InitSprite();

	//���
	void Release();

	//���Z�b�g
	void Reset();

	//�X�e�[�W�쐬
	void StageCreate();

	//�J�����̃C���X�^���X���擾
	GameCamera* GetGameCamera()
	{
		return gameCamera;
	}

	//���C�g�̃C���X�^���X�擾
	Light& GetLight()
	{
		return light;
	}

	//�}�b�v�̃C���X�^���X���擾
	Map* GetMap()
	{
		return map;
	}

	//�X�v���C�g�̍��W���擾
	const D3DXVECTOR2& GetCoinPos()
	{
		return CoinPos;
	}

	//�Q�[���i�s�̏��
	enum Step {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_WaitGameOver,
		step_normal,
		step_StageLoad,
		step_GameOver,
		step_GameClear,
	};

	//�X�e�[�W�̏��
	enum state_stage {
		en_Stage1,
		en_Stage2,
	};

	//�X�e�[�W�ύX�t���O��ԋp
	bool GetChengeStage()
	{
		return ChengeStage;
	}

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

private:
	Light light;					//���C�g
	Map* map;						//�}�b�v
	GameCamera* gameCamera;			//�Q�[���J����
	DisplayCoin* displayCoin;		//�R�C�������̃X�v���C�g
	Sprite* CoinNum;				//�R�C���̃X�v���C�g
	DepthStencilRender* depthStencilRender;

	Step step = step_WaitFadeOut;
	state_stage currentStage = en_Stage1;	//���݂̃X�e�[�W�ԍ�
	state_stage nextStage = en_Stage2;		//���̃X�e�[�W�ԍ�

	bool ChengeStage;			
	float timer = 0.0f;
	bool finishFadeOut = false;
};

extern GameScene* gameScene;