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
	//�R���X�g���N�^
	CStageSelectScene();

	//�f�X�g���N�^
	~CStageSelectScene();

	//�X�V�����O�Ɉ�x�����Ă΂��֐�
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();

	//�X�e�[�W�쐬
	void StageCreate();

	//���
	void Release();

	//�Q�[���i�s�̏��
	enum Step {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_normal,		//�ʏ펞
		step_StageLoad,		//�X�e�[�W�����[�h
	};

	//�t�F�[�h�A�E�g�҂��ł��邩�擾
	bool GetWaitFadeOut()
	{
		return m_waitFadeOut;
	}

	//�X�e�[�W�ԍ����擾
	int GetStageNumber()
	{
		return stageNumber;
	}

private:
	Map* map;									//�}�b�v
	DepthStencilRender* depthStencilRender;		//�V���G�b�g
	Step step = step_WaitFadeOut;				//���
	CSoundSource* bgmSource = nullptr;			//BGM
	bool m_waitFadeOut = false;					//�t�F�[�h�A�E�g�҂��t���O
	int stageNumber = 0;
};