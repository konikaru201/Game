#pragma once

class CParticle;

//�p�[�e�B�N�������p�����[�^
struct SParticleEmitParameter {
	//������
	void Init()
	{
		memset(this, 0, sizeof(SParticleEmitParameter));
	}
	const char* texturePath;		//�e�N�X�`���̃t�@�C���p�X
	float w;						//�p�[�e�B�N���̕�
	float h;						//�p�[�e�B�N���̍���
	float intervalTime;				//�p�[�e�B�N���̔����Ԋu
	D3DXVECTOR3 initSpeed;			//�����x
	D3DXVECTOR3 position;			//���W
	float		alpha;				//�����x
};

//�p�[�e�B�N���̔����@
class CParticleEmitter {
public:
	//�R���X�g���N�^
	CParticleEmitter();

	//�f�X�g���N�^
	~CParticleEmitter();

	//������
	void Init(const SParticleEmitParameter& param);

	//�X�V
	void Update();

	//���W��ݒ�
	void SetPosition(const D3DXVECTOR3 pos)
	{
		param.position = pos;
		param.position += param.initSpeed * 0.5f;
	}

	//���x��ݒ�
	void SetSpeed(const D3DXVECTOR3 speed)
	{
		param.initSpeed = speed;
	}
private:
	SParticleEmitParameter	param;				//�p�����[�^
	float					timer;				//�^�C�}�[
	std::list<CParticle*>	m_particleList;
};