#pragma once

#include "myEngine/Physics/PlayerController.h"
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

	//�e��`��
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	void DepthStencilRender(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);

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
		if (playerController.IsOnGround()
			|| playerController.IsOnMoveFloor()
			|| playerController.IsOnMoveFloor2()
			|| playerController.IsOnJumpBlock()
			|| playerController.IsOnBlock())
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

	//�v���C���[��Y�������擾
	D3DXVECTOR3 GetPlayerDirY()
	{
		D3DXMATRIX matrix = model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[1][0];
		direction.y = matrix.m[1][1];
		direction.z = matrix.m[1][2];
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

	//�e�̃��[���h�s���ݒ�
	void SetParentWorldMatrix(D3DXMATRIX worldMatrix)
	{
		parentWorldMatrix = worldMatrix;
	}
	//�e�̉�]�s���ݒ�
	void SetParentRotationMatrix(D3DXMATRIX rotationMatrix)
	{
		parentRotationMatrix = rotationMatrix;
	}
private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	Animation animation;							//�A�j���[�V����
	PlayerController playerController;				//�v���C���[�R���g���[���[

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
	float angle = 0.0f;
	bool parentFirstHit = true;

	bool isDead = false;
	bool isOnWall = false;
	bool wallJump = false;
	bool wallJumpExecute = false;
	float timer = 0.0f;

	D3DXMATRIX parentWorldMatrix;								//�e�̃��[���h�s��
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };				//�e�̃��[�J�����W����݂��v���C���[�̍��W
	D3DXMATRIX parentRotationMatrix;							//�e�̉�]�s��
	D3DXQUATERNION childRotation = { 0.0f,0.0f,0.0f,1.0f };		//�e�̉�]���W����݂��v���C���[�̉�]

	LPDIRECT3DTEXTURE9 specularMap = NULL;			//�X�y�L�����}�b�v
};

extern Player* g_player;