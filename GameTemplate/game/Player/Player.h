#pragma once

#include "myEngine/Physics/PlayerController.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "PlayerStateMachine.h"
#include "IPlayerState.h"

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

	//���W�̎擾
	const D3DXVECTOR3& GetPosition() {
		return position;
	}

	//���W�̐ݒ�
	void SetPosition(const D3DXVECTOR3& pos) 
	{
		position = pos;
	}

	//�ړ����x���擾
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return playerController.GetMoveSpeed();
	}

	//�ړ����x��ݒ�
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		moveSpeed = speed;
	}

	//��]���擾
	const D3DXQUATERNION& GetRotation()
	{
		return rotation;
	}

	//��]��ݒ�
	void SetRotation(const D3DXQUATERNION& rot)
	{
		rotation = rot;
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

	//�W�����v��������
	bool GetIsJump()
	{
		return playerController.IsJump();
	}

	void SetIsJump()
	{
		playerController.Jump();
	}

	//�A�j���[�V������������
	bool GetAnimationIsPlay()
	{
		return animation.IsPlay();
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

	void SetStarAnimationEnd(bool flag)
	{
		animationEnd = flag;
	}

	//�G�𓥂݂����̃t���O��ݒ�
	void SetTreadOnEnemy(bool treadOnEnemy)
	{
		m_treadOnEnemy = treadOnEnemy;
	}

	//�o�l�𓥂݂����̃t���O��ݒ�
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

	//�v���C���[�����������t���O���擾
	bool GetFallPlayer()
	{
		return m_fallPlayer;
	}

	//�v���C���[�̎��S�t���O��ݒ�
	void SetPlayerDead(bool playerDead)
	{
		m_playerDead = playerDead;
	}

	//�v���C���[�̎��S�t���O���擾
	bool GetPlayerDead()
	{
		return m_playerDead;
	}

	//�X�^�[�l���t���O���擾
	bool GetStar()
	{
		return getStar;
	}

	//�X�^�[�l���t���O��ݒ�
	void SetGetStar(bool getstar)
	{
		getStar = getstar;
	}

	//���݂̃A�j���[�V������ݒ�
	void SetCurrentAnim(IPlayerState::AnimationNo anim)
	{
		m_currentAnim = anim;
	}

	//���݂̃A�j���[�V�������擾
	IPlayerState::AnimationNo GetCurrentAnim()
	{
		return m_currentAnim;
	}

	//1�t���[���O�̃A�j���[�V�������X�V
	void SetPrevAnim(IPlayerState::AnimationNo anim)
	{
		m_prevAnim = anim;
	}

	//1�t���[���O�̃A�j���[�V�������擾
	IPlayerState::AnimationNo GetPrevAnim()
	{
		return m_prevAnim;
	}


private:
	SkinModel model;												//�X�L�����f��
	SkinModelData modelData;										//�X�L�����f���f�[�^
	Animation animation;											//�A�j���[�V����
	Light light;													//���C�g
	PlayerController playerController;								//�v���C���[�R���g���[���[
	D3DXVECTOR3	position;											//���W
	D3DXQUATERNION rotation;										//��]
	IPlayerState::AnimationNo m_currentAnim;						//���݂̃A�j���[�V����
	IPlayerState::AnimationNo m_prevAnim;							//�O�̃A�j���[�V����
	D3DXVECTOR3 moveSpeed = { 0.0f,0.0f,0.0f };						//�ړ����x
	bool parentFirstHit = true;										//�e�Ƃ̍ŏ��̓����蔻��t���O
	bool secondParentFirstHit = true;								//�e�Ƃ̍ŏ��̓����蔻��t���O
	bool getStar = false;											//�X�^�[�l���t���O
	bool animationEnd = false;										//�X�^�[�l�����̃A�j���[�V�����I���t���O
	bool m_treadOnEnemy = false;									//�G�𓥂񂾃t���O
	float jumpSpeed = 10.0f;										//�W�����v���̑��x
	bool m_hitEnemy = false;										//�G�ɓ��������t���O
	bool m_fallPlayer = false;
	bool m_playerDead = false;										//�v���C���[�̎��S�t���O
	bool m_treadOnSpring = false;									//�X�v�����O�𓥂񂾃t���O
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

	D3DXMATRIX parentWorldMatrix;									//�e�̃��[���h�s��
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };					//�e�̃��[�J�����W����݂��v���C���[�̍��W

	D3DXMATRIX secondParentWorldMatrix;								//�e�̃��[���h�s��
	D3DXVECTOR3 secondChildPosition = { 0.0f,0.0f,0.0f };			//�e�̃��[�J�����W����݂��v���C���[�̍��W

	LPDIRECT3DTEXTURE9 specularMap = NULL;							//�X�y�L�����}�b�v
	LPDIRECT3DTEXTURE9 normalMap = NULL;							//�@���}�b�v

	PlayerStateMachine m_playerStateMachine;						//�X�e�[�g�}�V��
};

extern Player* player;