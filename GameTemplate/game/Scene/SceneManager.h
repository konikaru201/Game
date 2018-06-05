/*!
*@brief	�V�[���}�l�[�W���[�N���X
*/
#pragma once
#include "myEngine/GameObject/GameObject.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "Scene/GameScene.h"
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
	const SceneState& GetScene() {
		return m_state;
	}
	/*!
	*@brief	�V�[���؂�ւ��t���O���擾
	*/
	bool GetChangeSceneFlag()
	{
		return m_changeScene;
	}
	/*!
	*@brief	�X�e�[�W�Z���N�g�V�[�����擾
	*@return	�X�e�[�W�Z���N�g�V�[��
	*/
	CStageSelectScene* GetstageSelectScene()
	{
		return m_stageSelectScene;
	}
private:
	SceneState			m_state;						//���݂̃V�[��
	FadeStep			m_step;							//�t�F�[�h�̏��
	TitleScene*			m_titleScene = nullptr;			//�^�C�g���V�[��
	CStageSelectScene*	m_stageSelectScene = nullptr;	//�X�e�[�W�Z���N�g�V�[��
	GameScene*			m_gameScene = nullptr;			//�Q�[���V�[��
	bool				m_changeScene = false;			//�V�[���؂�ւ��t���O
	int					m_gameOverSceneStateNumber = 0;	//�Q�[���I�[�o�[�V�[���̃X�e�[�g�ԍ�
	int					m_stageNumber = 1;
};

extern SceneManager* sceneManager;