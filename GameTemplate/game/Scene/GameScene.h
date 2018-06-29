/*!
*@brief	�Q�[���V�[���N���X
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
	* @brief	�X�V����O�Ɉ�x�����Ă΂��֐��B
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
	/*!
	* @brief	�X�e�[�W�쐬
	* @param[in]	number		�ԍ�
	*/
	void StageCreate(int number);
	/*!
	* @brief	���
	*/
	void Release();
	/*!
	* @brief	�X�e�[�W�ԍ���ݒ�
	* @param[in]	number		�ԍ�
	*/
	void SetStageNumber(int number);
	/*!
	* @brief	�Q�[���i�s�̏��
	*/
	enum Step {
		step_WaitFadeIn,
		step_WaitGameOver,
		step_normal,
		step_StageLoad,
		step_GameOver,
		step_StageClear,
	};
	/*!
	* @brief	��Ԃ�ԋp
	* @return	���
	*/
	const Step& IsStep() const
	{
		return m_step;
	}
	/*!
	* @brief	�X�e�[�W�N���A�t���O���擾
	*/
	bool GetStageClearFlag() const
	{
		return m_stageClearFlag;
	}
	/*!
	* @brief	�Q�[���I�[�o�[�V�[���̏I���t���O���擾
	*/
	bool GetGameOverEnd() const
	{
		return m_gameOverSceneEnd;
	}
	/*!
	* @brief	�Q�[���I�[�o�[�V�[���̏�Ԃ𐔎��Ŏ擾
	*/
	int GetGameOverSceneStateNumber() const
	{
		return m_gameOverSceneStateNumber;
	}
private:
	GameOverScene*	m_gameOverScene = nullptr;		//�Q�[���I�[�o�[�V�[��
	Silhouette*		m_silhouette;					//�V���G�b�g
	CSoundSource*	m_bgmSource = nullptr;			//BGM

	Step			m_step = step_StageLoad;		//���

	float			m_timer = 0.0f;					//�^�C�}�[
	bool			m_gameOverSceneEnd = false;		//�Q�[���I�[�o�[�V�[���̏I���t���O
	bool			m_stageClearFlag = false;		//�X�e�[�W�N���A�t���O
	int				m_gameOverSceneStateNumber = 0;	//�Q�[���I�[�o�[�V�[���̃X�e�[�g�ԍ�
	int				m_stageNumber = 0;				//�X�e�[�W�ԍ�
	bool			m_restart = true;				//���X�^�[�g���邩
};