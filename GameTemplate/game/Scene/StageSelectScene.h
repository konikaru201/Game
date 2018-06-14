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
	*@param[in]		changeStage		�X�e�[�W�ύX�t���O
	*@param[in]		number			�X�e�[�W�ԍ�
	*/
	void SetChangeStage(bool changeStage, int number) 
	{
		m_changeStage = changeStage;
		m_stageNumber = number;
	}
	/*!
	*@brief	�\������A�{�^����ݒ�
	*@param[in]		bottonRender	A�{�^����\�����邩	
	*@param[in]		number	�X�e�[�W�̔ԍ�
	*/
	void SetBottonReneder(bool bottonRender, int number)
	{
		m_bottonRender[number] = bottonRender;
	}
	/*!
	*@brief	A�{�^����\�����Ă��邩
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
	Silhouette*		silhouette;				//�V���G�b�g
	Step			m_step = step_WaitFadeOut;	//���
	CSoundSource*	bgmSource = nullptr;		//BGM
	bool			m_waitFadeOut = false;		//�t�F�[�h�A�E�g�҂��t���O
	int				m_stageNumber = 0;			//�X�e�[�W�ԍ�
	bool			m_changeStage = false;		//�X�e�[�W��ύX���邩
	bool			m_bottonRender[3];			//�{�^����\�����邩
};