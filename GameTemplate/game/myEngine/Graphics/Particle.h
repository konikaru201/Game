#pragma once

#include "Primitive.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/GameObject/GameObjectManager.h"

struct SParticleEmitParameter;

//�p�[�e�B�N��
class CParticle :  public GameObject{
public:
	//�R���X�g���N�^
	CParticle();

	//�f�X�g���N�^
	~CParticle();

	//������
	void Init(const SParticleEmitParameter& param);
	
	//�X�V
	void Update();

	//�`��
	void Render();

	enum State {
		State_Run,
		State_FadeOut,
		State_Dead,
	};

	State GetState()
	{
		return state;
	}
private:
	State				state;				//���
	CPrimitive			primitive;			//�v���~�e�B�u
	LPDIRECT3DTEXTURE9	texture;			//�e�N�X�`��
	ID3DXEffect*		shaderEffect;		//�V�F�[�_�[�G�t�F�N�g
	D3DXVECTOR3			moveSpeed;			//���x
	D3DXVECTOR3			position;			//���W
	float				life = 1.5f;		//����
	float				timer;				//�^�C�}�[
	float				alpha = 1.0f;		//�����x
	float				initAlpha = 1.0f;	//���������x
	const float			fadeTime = 1.0f;	//�t�F�[�h�^�C��
};