/*!
*@brief	�X�e�[�W�Z���N�g�V�[���N���X
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
	*@brief	�R���X�g���N�^
	*/
	CStageSelectScene();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~CStageSelectScene();
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	*@brief	�ォ��`��
	*/
	void PostRender();
	/*!
	*@brief	�X�e�[�W�쐬
	*/
	void StageCreate();
	/*!
	*@brief	���
	*/
	void Release();
	/*!
	*@brief	�Q�[���i�s�̏��
	*/
	enum Step {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_normal,		//�ʏ펞
		step_StageLoad,		//�X�e�[�W�����[�h
	};
	/*!
	*@brief	�t�F�[�h�A�E�g�҂��ł��邩�擾
	*/
	bool GetWaitFadeOut()
	{
		return m_waitFadeOut;
	}
	/*!
	*@brief	�X�e�[�W�ԍ����擾
	*/
	int GetStageNumber()
	{
		return m_stageNumber;
	}
	/*!
	*@brief	�X�e�[�W�ԍ���ݒ�
	*@param[in]		number			�X�e�[�W�ԍ�
	*/
	void SetStageNumber(int number)
	{
		m_stageNumber = number;
	}
	/*!
	*@brief	�X�e�[�W�ύX�t���O���擾
	*/
	int GetChangeStageFlag()
	{
		return m_changeStage;
	}
	/*!
	*@brief	�X�e�[�W�ύX�t���O��ݒ�
	*@param[in]		changeStage		�X�e�[�W�ύX�t���O
	*/
	void SetChangeStage(bool changeStage)
	{
		m_changeStage = changeStage;
	}
private:
	Silhouette*		m_silhouette;				//�V���G�b�g
	Step			m_step = step_WaitFadeOut;	//���
	CSoundSource*	m_bgmSource = nullptr;		//BGM
	Sprite*			m_stage1;					//�X�e�[�W�P
	Sprite*			m_stage2;					//�X�e�[�W�Q
	Sprite*			m_stage3;					//�X�e�[�W�R
	Sprite*			m_aBotton = nullptr;		//A�{�^���\���̃X�v���C�g
	bool			m_waitFadeOut = false;		//�t�F�[�h�A�E�g�҂��t���O
	int				m_stageNumber = 0;			//�X�e�[�W�ԍ�
	bool			m_changeStage = false;		//�X�e�[�W��ύX���邩
	bool			m_bottonRender[3];			//�{�^����\�����邩
};