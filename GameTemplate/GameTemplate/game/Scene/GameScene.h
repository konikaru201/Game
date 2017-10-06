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
	//�R�C���̃X�v���C�g�̃T�C�Y�ƍ��W
	const D3DXVECTOR2 CoinSize = { 250.0f,160.0f };
	const D3DXVECTOR2 CoinPos = { 800.0f,-550.0f };
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

	//�v���C���[�̃C���X�^���X�擾
	Player* GetPlayer()
	{
		return player;
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
	D3DXVECTOR2 GetCoinPos()
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
	Step IsStep()
	{
		return step;
	}
private:
	Light light;					//���C�g
	Map* map;						//�}�b�v
	Player* player;					//�v���C���[
	GameCamera* gameCamera;			//�Q�[���J����
	DisplayCoin* displayCoin;		//�R�C�������̃X�v���C�g
	Sprite* CoinNum;				//�R�C���̃X�v���C�g

	Step step = step_WaitFadeOut;
	state_stage currentStage = en_Stage1;	//���݂̃X�e�[�W�ԍ�
	state_stage nextStage = en_Stage2;		//���̃X�e�[�W�ԍ�

	bool ChengeStage;			
	float timer = 0.0f;
	bool finishFadeOut = false;
};

extern GameScene* gameScene;