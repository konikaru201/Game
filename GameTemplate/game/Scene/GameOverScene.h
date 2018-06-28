/*!
*@brief	�Q�[���I�[�o�[�V�[���N���X
*/
#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"

/*!
*@brief	�X�v���C�g�̍��W
*/
namespace {
	const D3DXVECTOR2 gameOverPos = { 0.0f,  200.0f };
	const D3DXVECTOR2 continuePos = { 0.0f, -200.0f };
	const D3DXVECTOR2 stageSelectReturnPos = { 0.0f, -350.0f };
	const D3DXVECTOR2 titleReturnPos = { 0.0f, -500.0f };
	const D3DXVECTOR2 trianglePos = { -580.0f, -200.0f };
}

class GameOverScene : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	GameOverScene();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~GameOverScene();
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
	*@brief	Render�֐�����ɌĂ΂��`��֐�
	*/
	void PostRender();
	/*!
	*@brief	�Q�[���I�[�o�[�V�[���I���t���O���擾
	*/
	bool GetGameOverSceneEnd() const
	{
		return m_gameOverSceneEnd;
	}
	/*!
	*@brief	���
	*/
	enum State {
		state_Continue, //������
		state_return,	//�X�e�[�W�Z���N�g�V�[���ɖ߂�
		state_End,		//�I��
	};
	/*!
	*@brief	��Ԃ𐔎��Ŏ擾
	*@detail	0�̓R���e�B�j���[�B1�̓X�e�[�W�I���ɖ߂�B2�̓^�C�g���ɖ߂�B
	*/
	int GetStateNumber() const
	{
		return m_stateNumber;
	}

private:
	//�X�v���C�g
	std::unique_ptr<Sprite>		m_gameOver;					//�Q�[���I�[�o�[
	std::unique_ptr<Sprite>		m_continue;					//�R���e�B�j���[
	std::unique_ptr<Sprite>		m_stageSelectReturn;		//�X�e�[�W�I��������
	std::unique_ptr<Sprite>		m_titleReturn;				//�^�C�g���ɖ߂�
	std::unique_ptr<Sprite>		m_triangle;					//�O�p
	std::unique_ptr<Sprite>		m_background;				//�w�i

	const float FADE_TIME = 1.0f;			//�t�F�[�h���鎞��
	float		m_alpha = 0.0f;				//�s�����x�B1.0�͍�
	float		m_timer = 0.0f;				//�^�C�}�[
	bool		m_gameOverSceneEnd = false;	//�Q�[���I�[�o�[�V�[���I���t���O
	State		m_state = state_Continue;	//���
	int			m_stateNumber = 0;			//��Ԃ̔ԍ��B0�̓R���e�B�j���[�B1�̓X�e�[�W�I���ɖ߂�B2�̓^�C�g���ɖ߂�B
	D3DXVECTOR2 m_preGameOverPos;			//�Q�[���I�[�o�[�̃X�v���C�g���W�ۑ��p�ϐ�
	D3DXVECTOR2 m_preTrianglePos;			//�O�p�̃X�v���C�g���W�ۑ��p�ϐ�
	bool		m_gameOverSet = false;		//�Q�[���I�[�o�[���\�����ꂽ��
};