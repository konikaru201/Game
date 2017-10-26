#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine/GameObject/GameObject.h"

class Player : public GameObject
{
public:
	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//������
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();

	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//�ړ�
	//�߂�l�@�ړ����x��Ԃ�
	D3DXVECTOR3 Move();

	void Reset();

	//���W�̎擾
	D3DXVECTOR3 GetPosition() {
		return position;
	}

	//���S�������ǂ���
	bool GetIsDead()
	{
		return isDead;
	}

	//�R�C���̊l���������擾
	int GetCoinCount()
	{
		return CoinCount;
	}

	//�R�C���̊l���������X�V
	void SetCoinCount(int Count)
	{
		CoinCount = Count;
	}

	//�n�ʂ̏ォ����
	bool GetIsOnGround()
	{
		if (characterController.IsOnGround()
			|| characterController.IsOnMoveFloor()
			|| characterController.IsOnMoveFloor2()
			|| characterController.IsOnJumpBlock())
		{
			return true;
		}
		return false;
	}

	//�v���C���[�̌������擾
	D3DXVECTOR3 GetPlayerDir()
	{
		D3DXMATRIX matrix = model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[2][0];
		direction.y = matrix.m[2][1];
		direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}

	//�A�j���[�V�����̏��
	enum AnimationNo {
		AnimationStand,	//����
		AnimationWalk,	//����
		AnimationRun,	//����
		AnimationJump,	//�W�����v
	};
private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	Animation animation;							//�A�j���[�V����
	CharacterController characterController;		//�L�����N�^�[�R���g���[���[

	D3DXVECTOR3 MoveSpeed = { 0.0f,0.0f,0.0f };		//�ړ����x

	D3DXVECTOR3	position;							//���W
	D3DXQUATERNION rotation;						//��]
	D3DXVECTOR3 dir = { 0.0f,0.0f,1.0f };			//Z���̕���
	AnimationNo currentAnim;						//���݂̃A�j���[�V����
	AnimationNo prevAnim;							//�O�̃A�j���[�V����
	D3DXVECTOR3 playerDir;							
	int JumpCount = 0;								//�W�����v�̉�
	int JumpFrameCount = 0;							//���̃W�����v������܂ł̃t���[��
	int CoinCount = 0;								//�R�C���̊l������
	bool isDead = false;
	bool isOnWall = false;
	bool wallJump = false;
	bool wallJumpExecute = false;
	float timer = 0.0f;

	LPDIRECT3DTEXTURE9 specularMap = NULL;			//�X�y�L�����}�b�v
};

extern Player* g_player;