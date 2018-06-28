/*!
*@brief	�V�[���}�l�[�W���[�N���X
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
	*@brief	�R���X�g���N�^
	*/
	SceneManager();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~SceneManager();
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	UI��`��
	*/
	void UIRender();
	/*!
	*@brief	�V�[���̏��
	*/
	enum SceneState {
		stateTitle,			//�^�C�g��
		stateGame,			//�Q�[��
		stateGameOver,		//�Q�[���I�[�o�[
		stateStageSelect,	//�X�e�[�W�Z���N�g
	};
	/*!
	*@brief	�t�F�[�h�̏��
	*/
	enum FadeStep {
		step_WaitFadeIn,	//�t�F�[�h�C��
		step_WaitFadeOut,	//�t�F�[�h�A�E�g
		step_normal,		//�����Ȃ�
	};
	/*!
	*@brief	���݂̃V�[�����擾
	*@return	���݂̃V�[��
	*/
	const SceneState& GetScene() const
	{
		return m_state;
	}
	/*!
	*@brief	�V�[���؂�ւ��t���O���擾
	*/
	bool GetChangeSceneFlag() const
	{
		return m_changeScene;
	}
	/*!
	*@brief	�X�e�[�W�Z���N�g�V�[�����擾
	*@return	�X�e�[�W�Z���N�g�V�[��
	*/
	CStageSelectScene* GetstageSelectScene() const
	{
		return m_stageSelectScene;
	}
	/*!
	*@brief	�R�C��UI�̃C���X�^���X���擾
	*@return	�R�C��UI�̃C���X�^���X
	*/
	DisplayCoin* GetCoinUI() const
	{
		return m_coinUI;
	}
	/*!
	*@brief	�c�@���̃C���X�^���X���擾
	*@return	�c�@���̃C���X�^���X
	*/
	RemainNumber* GetRemainNumber() const
	{
		return m_remainNumber;
	}
private:
	SceneState					m_state;						//���݂̃V�[��
	FadeStep					m_step;							//�t�F�[�h�̏��
	TitleScene*					m_titleScene = nullptr;			//�^�C�g���V�[��
	CStageSelectScene*			m_stageSelectScene = nullptr;	//�X�e�[�W�Z���N�g�V�[��
	GameScene*					m_gameScene = nullptr;			//�Q�[���V�[��
	bool						m_changeScene = false;			//�V�[���؂�ւ��t���O
	int							m_gameOverSceneStateNumber = 0;	//�Q�[���I�[�o�[�V�[���̃X�e�[�g�ԍ�
	int							m_stageNumber = 1;
	DisplayCoin*				m_coinUI = nullptr;				//�R�C�������̃X�v���C�g
	RemainNumber*				m_remainNumber = nullptr;		//�c�@���̃X�v���C�g
	std::unique_ptr<Sprite>		m_coin = nullptr;				//�R�C���̊G�̃X�v���C�g
	std::unique_ptr<Sprite>		m_remain = nullptr;				//�c�@�̃X�v���C�g
	std::unique_ptr<Sprite>		m_kakeru = nullptr;				//�~�L���̃X�v���C�g
	std::unique_ptr<Sprite>		m_kakeru2 = nullptr;
};

extern SceneManager* sceneManager;