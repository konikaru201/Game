/*!
*@brief	���C�v�G�t�F�N�g�N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"

class WipeEffect : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	WipeEffect();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~WipeEffect();
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
	*@brief	���C�v�A�E�g�J�n
	*/
	void StartWipeOut()
	{
		m_isWipe = true;
		m_timer = 0.0f;
		m_back->SetAlpha(1.0f);
		m_state = WipeOut;
	}
	/*!
	*@brief	���C�v�C���J�n
	*/
	void StartWipeIn()
	{
		m_isWipe = true;
		m_timer = 0.0f;
		m_back->SetAlpha(1.0f);
		m_state = WipeIn;
	}
	/*!
	*@brief	���C�v���s����?
	*/
	bool IsExecute()
	{
		return m_isWipe;
	}
private:
	/*!
	*@brief	���C�v�̏��
	*/
	enum State {
		WipeIn,		//���C�v�C��
		WipeOut		//���C�v�A�E�g
	};

	State		m_state = WipeIn;		//���
	Sprite*		m_circle;				//�~�̃X�v���C�g
	Sprite*		m_back;					//���w�i�̃X�v���C�g
	float		m_timer = 0.0f;			//�^�C�}�[
	const float WIPE_TIME = 1.0f;		//���C�v���鎞��
	bool		m_isWipe = false;		//���C�v���Ă��邩
};

extern WipeEffect* wipeEffect;