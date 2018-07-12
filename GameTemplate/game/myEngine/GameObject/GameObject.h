#pragma once

class GameObject 
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	GameObject();
	/*!
	*@brief	�f�X�g���N�^
	*/
	virtual ~GameObject();
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	virtual bool Start() { return true; }
	/*!
	*@brief	�X�V
	*/
	virtual void Update() = 0;
	virtual void PreUpdate() {}
	virtual void PostUpdate() {}
	/*!
	*@brief	�`��
	*/
	virtual void Render(){}
	virtual void PreRender(){}
	virtual void PostRender(){}
	/*!
	* @brief	�e��`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	* @param[in]	isDrawShadowMap	�V���h�E�}�b�v��`���t���O
	* @param[in]	isRecieveShadow	�V���h�E���V�[�o�[���ǂ���
	*/
	virtual void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow){}
	/*!
	*@brief	�[�x�l��`��
	*/
	virtual void RenderDepthValue() {}
	/*!
	*@brief	Start�֐������łɌĂ΂ꂽ��
	*/
	virtual bool IsStart() const
	{
		return m_isStart;
	}
	/*!
	*@brief	Start�֐����Ă΂ꂽ��t���O��ݒ�
	*/
	void SetStart()
	{
		m_isStart = true;
	}
	/*!
	*@brief	���S�t���O��ԋp
	*/
	bool GetisDead() const
	{
		return m_isDead;
	}
	/*!
	*@brief	���S�t���O�𗧂Ă�
	*/
	void SetisDead()
	{
		m_isDead = true;
	}
	/*!
	*@brief	�e�̕`��t���O��ԋp
	*/
	bool GetShadowToRender() const
	{
		return m_renderToShadow;
	}
	/*!
	*@brief	�e�̕`��t���O�𗧂Ă�
	*/
	void SetRenderToShadow()
	{
		m_renderToShadow = true;
	}
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�ɓo�^����Ă��邩
	*/
	bool GetIsRegist() const
	{
		return m_isRegist;
	}
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�ɓo�^����t���O��ݒ�
	*/
	void SetIsRegist(bool isRegist)
	{
		m_isRegist = isRegist;
	}
	/*!
	*@brief	�X�e�[�g��ύX���邩
	*/
	bool GetIsChangeState() const
	{
		return m_isChangeState;
	}
	/*!
	*@brief	�X�e�[�g�ύX�t���O��ݒ�
	*/
	void SetIsChangeState(bool isChangeState)
	{
		m_isChangeState = isChangeState;
	}

protected:
	bool m_isStart = false;			//Start�֐��̃t���O
	bool m_isDead = false;			//���S�t���O
	bool m_renderToShadow = false;	//�e�̕`��t���O
	bool m_isRegist = false;		//�Q�[���I�u�W�F�N�g�ɓo�^����Ă��邩
	bool m_isChangeState = false;	//�X�e�[�g��ύX���邩
};