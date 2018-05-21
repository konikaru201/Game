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

	void SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);

	//�ړ�
	//�߂�l�@�ړ����x��Ԃ�
	D3DXVECTOR3 Move();

	//���W�̎擾
	const D3DXVECTOR3& GetPosition() {
		return position;
	}

	//�ړ����x���擾
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return moveSpeed;
	}

	//�X�^�[�l���t���O��ݒ�
	void SetGetStar(bool getstar)
	{
		getStar = getstar;
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

	//�ړ����P
	//�ړ����̑��x��ݒ�
	void SetMoveFloorSpeed(const D3DXVECTOR3& speed)
	{
		m_moveFloorSpeed = speed;
	}

	//�ړ����Q
	//�ړ����̑��x��ݒ�
	void SetMoveFloor2Speed(const D3DXVECTOR3& speed)
	{
		m_moveFloor2Speed = speed;
	}

	//�u���b�N�P
	//�e�̃��[���h�s���ݒ�
	void SetParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		parentWorldMatrix = worldMatrix;
	}

	//�u���b�N�Q
	//�e�̃��[���h�s���ݒ�
	void SetSecondParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		secondParentWorldMatrix = worldMatrix;
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

	//�G�ɓ����������̃t���O���擾
	bool GetHitEnemy()
	{
		return m_hitEnemy;
	}

	//�v���C���[�̎��S�t���O���擾
	bool GetPlayerDead()
	{
		return m_playerDead;
	}

	//�X�^�[�l���t���O
	bool GetStar()
	{
		return getStar;
	}

	//�v���C���[�̏��
	enum State {
		State_Walk,				//�ړ�
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
		AnimationPose,	//�|�[�Y
		AnimationDead,	//���S
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
	float angle = 0.0f;												//��]�p�x
	float timer = 0.0f;												//�^�C�}�[
	D3DXVECTOR3 moveSpeed = { 0.0f,0.0f,0.0f };						//�ړ����x
	float acceleration = 0.0f;										//�����x
	const float speedLimit = 6.0f;									//���E���x
	D3DXVECTOR3 currentDir = { 0.0f,0.0f,0.0f };					//1�t���[���O��Z����
	bool parentFirstHit = true;										//�e�Ƃ̍ŏ��̓����蔻��t���O
	bool secondParentFirstHit = true;								//�e�Ƃ̍ŏ��̓����蔻��t���O
	bool getStar = false;											//�X�^�[�l���t���O
	State state = State_Walk;										//���
	bool animationEnd = false;										//�X�^�[�l�����̃A�j���[�V�����I���t���O
	bool m_treadOnEnemy = false;									//�G�𓥂񂾃t���O
	float jumpSpeed = 10.0f;										//�W�����v���̑��x
	bool m_hitEnemy = false;										//�G�ɓ��������t���O
	bool m_playerDead = false;										//�v���C���[�̎��S�t���O
	bool m_treadOnSpring = false;									//�X�v�����O�𓥂񂾃t���O
	int m_rotationFrameCount = 0;									//��]�t���[���J�E���g
	bool m_moveFloorInertia = false;								//�ړ����̊���
	bool m_moveFloor2Inertia = false;								//�ړ����Q�̊���
	D3DXVECTOR3 m_airResistance = { 0.0f,0.0f,0.0f };				//��C��R
	float m_ineltiaTime = 0.0f;

	D3DXMATRIX moveFloorWorldMatrix;
	D3DXVECTOR3 moveFloorChildPosition = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_moveFloorSpeed = { 0.0f,0.0f,0.0f };

	D3DXMATRIX moveFloor2WorldMatrix;
	D3DXVECTOR3 moveFloor2ChildPosition = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_moveFloor2Speed = { 0.0f,0.0f,0.0f };

	bool isOnWall = false;
	bool wallJump = false;
	bool wallJumpExecute = false;

	D3DXMATRIX parentWorldMatrix;									//�e�̃��[���h�s��
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };					//�e�̃��[�J�����W����݂��v���C���[�̍��W

	D3DXMATRIX secondParentWorldMatrix;								//�e�̃��[���h�s��
	D3DXVECTOR3 secondChildPosition = { 0.0f,0.0f,0.0f };			//�e�̃��[�J�����W����݂��v���C���[�̍��W

	LPDIRECT3DTEXTURE9 specularMap = NULL;							//�X�y�L�����}�b�v
	LPDIRECT3DTEXTURE9 normalMap = NULL;							//�@���}�b�v
};

extern Player* player;