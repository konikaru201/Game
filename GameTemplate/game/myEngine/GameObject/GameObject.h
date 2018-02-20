#pragma once

class GameObject 
{
public:
	//�R���X�g���N�^
	GameObject();

	//�f�X�g���N�^
	virtual ~GameObject();

	//������
	virtual bool Start() { return true; }

	//�X�V
	virtual void Update() = 0;
	virtual void PreUpdate() {}
	virtual void PostUpdate() {}
	//�`��
	virtual void Render(){}

	//�e�̕`��
	virtual void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow){}

	//Start�֐������łɌĂ΂ꂽ��
	virtual bool IsStart()
	{
		return m_isStart;
	}

	//Start�֐����Ă΂ꂽ��t���O��ݒ�
	void SetStart()
	{
		m_isStart = true;
	}

	//���S�t���O��ԋp
	bool GetisDead()
	{
		return m_isDead;
	}

	//���S�t���O�𗧂Ă�
	void SetisDead()
	{
		m_isDead = true;
	}

	//�e�̕`��t���O��ԋp
	bool GetShadowToRender()
	{
		return m_renderToShadow;
	}

	//�e�̕`��t���O�𗧂Ă�
	void SetRenderToShadow()
	{
		m_renderToShadow = true;
	}

protected:
	bool m_isStart = false;			//Start�֐��̃t���O
	bool m_isDead = false;			//���S�t���O
	bool m_renderToShadow = false;	//�e�̕`��t���O
};