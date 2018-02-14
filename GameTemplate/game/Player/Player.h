#pragma once

#include "myEngine/Physics/PlayerController.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

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

	void DepthStencilRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);

	//�ړ�
	//�߂�l�@�ړ����x��Ԃ�
	D3DXVECTOR3 Move();

	void Reset();

	//���W�̎擾
	const D3DXVECTOR3& GetPosition() {
		return position;
	}

	//�R�C���̊l���������擾
	int GetCoinCount()
	{
		return CoinCount;
	}

	//�X�^�[�l���t���O��ݒ�
	void SetGetStar(bool getstar)
	{
		getStar = getstar;
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
			|| playerController.IsOnSpring()
			|| playerController.IsOnBlock()
			|| playerController.IsOnBlock2()
			|| playerController.IsOnBox())
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

	//�u���b�N�P
	//�e�̃��[���h�s���ݒ�
	void SetParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		parentWorldMatrix = worldMatrix;
	}
	//�e�̉�]�s���ݒ�
	void SetParentRotationMatrix(const D3DXMATRIX& rotationMatrix)
	{
		parentRotationMatrix = rotationMatrix;
	}

	//�u���b�N�Q
	//�e�̃��[���h�s���ݒ�
	void SetSecondParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		secondParentWorldMatrix = worldMatrix;
	}
	//�e�̉�]�s���ݒ�
	void SetSecondParentRotationMatrix(const D3DXMATRIX& rotationMatrix) 
	{
		secondParentRotationMatrix = rotationMatrix;
	}

	//�X�^�[�l�����̃A�j���[�V�����I���t���O���擾
	bool GetStarAnimationEnd()
	{
		return animationEnd;
	}

	//�G�𓥂݂����̃t���O��ݒ�
	void SetTreadOnEnemy(bool treadOnEnemy)
	{
		m_treadOnEnemy = treadOnEnemy;
	}

	//�X�v�����O�𓥂݂����̃t���O��ݒ�
	void SetTreadOnSpring(bool treadOnSpring) 
	{
		m_treadOnSpring = treadOnSpring;
	}

	//�G�ɓ����������̃t���O��ݒ�
	void SetHitEnemy(bool hitEnemy)
	{
		m_hitEnemy = hitEnemy;
	}

	//�v���C���[�̎��S�t���O���擾
	bool GetPlayerDead()
	{
		return m_playerDead;
	}

	//�v���C���[�̏��
	enum State {
		State_Move,				//�ړ�
		State_Dead,				//���S
		State_WallJump,			//�ǃW�����v
		State_GetStar,			//�X�^�[���l��
	};

	//��Ԃ��擾�@
	State GetState()
	{
		return state;
	}

	//�A�j���[�V�����̏��
	enum AnimationNo {
		AnimationStand,	//����
		AnimationWalk,	//����
		AnimationRun,	//����
		AnimationJump,	//�W�����v
		AnimationPose,
	};

private:
	SkinModel model;												//�X�L�����f��
	SkinModelData modelData;										//�X�L�����f���f�[�^
	Animation animation;											//�A�j���[�V����
	Light light;													//���C�g
	PlayerController playerController;								//�v���C���[�R���g���[���[
	D3DXVECTOR3	position;											//���W
	D3DXQUATERNION rotation;										//��]
	D3DXVECTOR3 dir = { 0.0f,0.0f,0.0f };							//����
	AnimationNo currentAnim;										//���݂̃A�j���[�V����
	AnimationNo prevAnim;											//�O�̃A�j���[�V����
	D3DXVECTOR3 playerDir;											//�L�����N�^�[��Z����
	int JumpCount = 0;												//�W�����v�̉�
	int JumpFrameCount = 0;											//���̃W�����v������܂ł̃t���[��
	int CoinCount = 0;												//�R�C���̊l������
	float angle = 0.0f;												//��]�p�x
	float timer = 0.0f;												//�^�C�}�[
	D3DXVECTOR3 moveSpeed = { 0.0f,0.0f,0.0f };						//�ړ����x
	float acceleration = 0.0f;										//�����x
	const float speedLimit = 6.0f;									//���E���x
	D3DXVECTOR3 currentDir = { 0.0f,0.0f,0.0f };					//1�t���[���O��Z����
	bool parentFirstHit = true;										//�e�Ƃ̍ŏ��̓����蔻��t���O
	bool secondParentFirstHit = true;								//�e�Ƃ̍ŏ��̓����蔻��t���O
	bool getStar = false;											//�X�^�[�l���t���O
	State state = State_Move;										//���
	bool animationEnd = false;										//�X�^�[�l�����̃A�j���[�V�����I���t���O
	bool m_treadOnEnemy = false;									//�G�𓥂񂾃t���O
	float jumpSpeed = 10.0f;										//�W�����v���̑��x
	bool m_hitEnemy = false;										//�G�ɓ��������t���O
	bool m_playerDead = false;										//�v���C���[�̎��S�t���O
	bool m_treadOnSpring = false;									//�X�v�����O�𓥂񂾃t���O

	bool isOnWall = false;
	bool wallJump = false;
	bool wallJumpExecute = false;

	D3DXMATRIX parentWorldMatrix;									//�e�̃��[���h�s��
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };					//�e�̃��[�J�����W����݂��v���C���[�̍��W
	D3DXMATRIX parentRotationMatrix;								//�e�̉�]�s��
	D3DXQUATERNION childRotation = { 0.0f,0.0f,0.0f,1.0f };			//�e�̉�]���W����݂��v���C���[�̉�]

	D3DXMATRIX secondParentWorldMatrix;								//�e�̃��[���h�s��
	D3DXVECTOR3 secondChildPosition = { 0.0f,0.0f,0.0f };			//�e�̃��[�J�����W����݂��v���C���[�̍��W
	D3DXMATRIX secondParentRotationMatrix;							//�e�̉�]�s��
	D3DXQUATERNION secondChildRotation = { 0.0f,0.0f,0.0f,1.0f };	//�e�̉�]���W����݂��v���C���[�̉�]

	LPDIRECT3DTEXTURE9 specularMap = NULL;							//�X�y�L�����}�b�v
	LPDIRECT3DTEXTURE9 normalMap = NULL;							//�@���}�b�v
};

extern Player* player;