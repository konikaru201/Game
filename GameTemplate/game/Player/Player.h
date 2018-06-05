/*!
*@brief	�v���C���[�N���X
*/

#pragma once

#include "myEngine/Physics/PlayerController.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "PlayerStateMachine.h"
#include "IPlayerState.h"

class Player : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Player();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Player();
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
	* @brief	�e��`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	* @param[in]	isDrawShadowMap	�V���h�E�}�b�v��`���t���O
	* @param[in]	isRecieveShadow	�V���h�E���V�[�o�[���ǂ���
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	�V���G�b�g�̕`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	*/
	void SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);
	/*!
	* @brief	�v���C���[�̍��W�̎擾
	*@return	�v���C���[�̍��W
	*/
	const D3DXVECTOR3& GetPosition() {
		return m_position;
	}
	/*!
	*@brief	���W�̐ݒ�
	* @param[in]	pos		���W
	*/
	void SetPosition(const D3DXVECTOR3& pos) 
	{
		m_position = pos;
	}
	/*!
	* @brief	�ړ����x���擾
	*@return	�ړ����x
	*/
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return m_playerController.GetMoveSpeed();
	}
	/*!
	*@brief	�ړ����x��ݒ�
	* @param[in]	speed	�ړ����x
	*/
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		m_moveSpeed = speed;
	}
	/*!
	* @brief	��]���擾
	*@return	��]
	*/
	const D3DXQUATERNION& GetRotation()
	{
		return m_rotation;
	}
	/*!
	*@brief	��]��ݒ�
	* @param[in]	rot		��]
	*/
	void SetRotation(const D3DXQUATERNION& rot)
	{
		m_rotation = rot;
	}
	/*!
	* @brief	�n�ʂ̏ォ����
	*/
	bool GetIsOnGround()
	{
		if (m_playerController.IsOnGround()
			|| m_playerController.IsOnMoveFloor()
			|| m_playerController.IsOnMoveFloor2()
			|| m_playerController.IsOnSpring()
			|| m_playerController.IsOnBlock()
			|| m_playerController.IsOnBlock2()
			|| m_playerController.IsOnBox())
		{
			return true;
		}
		return false;
	}
	/*!
	* @brief	�W�����v��������
	*/
	bool GetIsJump()
	{
		return m_playerController.IsJump();
	}
	/*!
	*@brief	�v���C���[���W�����v������
	*/
	void SetIsJump()
	{
		m_playerController.Jump();
	}
	/*!
	* @brief	�A�j���[�V������������
	*/
	bool GetAnimationIsPlay()
	{
		return m_animation.IsPlay();
	}
	/*!
	* @brief	�v���C���[�̌������擾
	*@return	�v���C���[�̌���
	*/
	D3DXVECTOR3 GetPlayerDir()
	{
		D3DXMATRIX matrix = m_model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[2][0];
		direction.y = matrix.m[2][1];
		direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}
	/*!
	* @brief	�ړ����P�̑��x��ݒ�
	* @param[in]	speed		�ړ����x
	*/
	void SetMoveFloorSpeed(const D3DXVECTOR3& speed)
	{
		m_moveFloorSpeed = speed;
	}
	/*!
	* @brief	�ړ����Q�̑��x��ݒ�
	* @param[in]	speed		�ړ����x
	*/
	void SetMoveFloor2Speed(const D3DXVECTOR3& speed)
	{
		m_moveFloor2Speed = speed;
	}
	/*!
	* @brief	�u���b�N�P�̃��[���h�s���ݒ�
	* @param[in]	worldMatrix		���[���h�s��
	*/
	void SetParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		m_parentWorldMatrix = worldMatrix;
	}
	/*!
	* @brief	�u���b�N�Q�̃��[���h�s���ݒ�
	* @param[in]	worldMatrix		���[���h�s��
	*/
	void SetSecondParentWorldMatrix(const D3DXMATRIX& worldMatrix)
	{
		m_secondParentWorldMatrix = worldMatrix;
	}
	/*!
	* @brief	�X�^�[�l�����̃A�j���[�V�����I���t���O���擾
	*/
	bool GetStarAnimationEnd()
	{
		return m_animationEnd;
	}
	/*!
	* @brief	�X�^�[�l�����̃A�j���[�V�����I���t���O��ݒ�
	* @param[in]	flag		�X�^�[�l�����̃A�j���[�V�������I��������
	*/
	void SetStarAnimationEnd(bool flag)
	{
		m_animationEnd = flag;
	}
	/*!
	* @brief	�G�𓥂݂����̃t���O��ݒ�
	* @param[in]	treadOnEnemy		�G�𓥂݂�����
	*/
	void SetTreadOnEnemy(bool treadOnEnemy)
	{
		m_treadOnEnemy = treadOnEnemy;
	}
	/*!
	* @brief	�o�l�𓥂݂����̃t���O��ݒ�
	* @param[in]	treadOnSpring		�o�l�𓥂݂�����
	*/
	void SetTreadOnSpring(bool treadOnSpring) 
	{
		m_treadOnSpring = treadOnSpring;
	}
	/*!
	* @brief	�G�ɓ����������̃t���O��ݒ�
	* @param[in]	hitEnemy		�G�ɓ���������
	*/
	void SetHitEnemy(bool hitEnemy)
	{
		m_hitEnemy = hitEnemy;
	}
	/*!
	* @brief	�G�ɓ����������̃t���O���擾
	*/
	bool GetHitEnemy()
	{
		return m_hitEnemy;
	}
	/*!
	* @brief	�v���C���[�����������t���O���擾
	*/
	bool GetFallPlayer()
	{
		return m_fallPlayer;
	}
	/*!
	* @brief	�v���C���[�̎��S�t���O��ݒ�
	* @param[in]	playerDead		�v���C���[�̎��S�t���O
	*/
	void SetPlayerDead(bool playerDead)
	{
		m_playerDead = playerDead;
	}
	/*!
	* @brief	�v���C���[�̎��S�t���O���擾
	*/
	bool GetPlayerDead()
	{
		return m_playerDead;
	}
	/*!
	* @brief	�X�^�[�l���t���O���擾
	*/
	bool GetStar()
	{
		return m_getStar;
	}
	/*!
	* @brief	�X�^�[�l���t���O��ݒ�
	* @param[in]	getstar		�X�^�[�l���t���O
	*/
	void SetGetStar(bool getStar)
	{
		m_getStar = getStar;
	}
	/*!
	* @brief	���݂̃A�j���[�V������ݒ�
	* @param[in]	anim		���݂̃A�j���[�V����
	*/
	void SetCurrentAnim(IPlayerState::AnimationNo anim)
	{
		m_currentAnim = anim;
	}
	/*!
	* @brief	���݂̃A�j���[�V�������擾
	*@return	���݂̃A�j���[�V����
	*/
	IPlayerState::AnimationNo GetCurrentAnim()
	{
		return m_currentAnim;
	}
	/*!
	* @brief	1�t���[���O�̃A�j���[�V�������X�V
	* @param[in]	anim		1�t���[���O�̃A�j���[�V����
	*/
	void SetPrevAnim(IPlayerState::AnimationNo anim)
	{
		m_prevAnim = anim;
	}
	/*!
	* @brief	1�t���[���O�̃A�j���[�V�������擾
	*@return	1�t���[���O�̃A�j���[�V����
	*/
	IPlayerState::AnimationNo GetPrevAnim()
	{
		return m_prevAnim;
	}
private:
	SkinModel			m_model;								//�X�L�����f��
	SkinModelData		m_modelData;							//�X�L�����f���f�[�^
	Animation			m_animation;							//�A�j���[�V����
	Light				m_light;								//���C�g
	PlayerController	m_playerController;						//�v���C���[�R���g���[���[
	D3DXVECTOR3			m_position;								//���W
	D3DXQUATERNION		m_rotation;								//��]
	IPlayerState::AnimationNo m_currentAnim;					//���݂̃A�j���[�V����
	IPlayerState::AnimationNo m_prevAnim;						//�O�̃A�j���[�V����
	D3DXVECTOR3			m_moveSpeed = { 0.0f,0.0f,0.0f };		//�ړ����x
	bool				m_parentFirstHit = true;				//�e�Ƃ̍ŏ��̓����蔻��t���O
	bool				m_secondParentFirstHit = true;			//�e�Ƃ̍ŏ��̓����蔻��t���O
	bool				m_getStar = false;						//�X�^�[�l���t���O
	bool				m_animationEnd = false;					//�X�^�[�l�����̃A�j���[�V�����I���t���O
	bool				m_treadOnEnemy = false;					//�G�𓥂񂾃t���O
	const float			m_jumpSpeed = 10.0f;					//�W�����v���̑��x
	bool				m_hitEnemy = false;						//�G�ɓ��������t���O
	bool				m_fallPlayer = false;					//�v���C���[�̗����t���O
	bool				m_playerDead = false;					//�v���C���[�̎��S�t���O
	bool				m_treadOnSpring = false;				//�X�v�����O�𓥂񂾃t���O
	bool				m_moveFloorInertia = false;				//�ړ����̊���
	bool				m_moveFloor2Inertia = false;			//�ړ����Q�̊���
	D3DXVECTOR3			m_airResistance = { 0.0f,0.0f,0.0f };	//��C��R
	float				m_ineltiaTime = 0.0f;					//��������������

	D3DXMATRIX			m_moveFloorWorldMatrix;							//�ړ����P�̃��[���h�s��
	D3DXVECTOR3			m_moveFloorChildPosition = { 0.0f,0.0f,0.0f };	//�ړ����P���猩���v���C���[�̃��[�J�����W
	D3DXVECTOR3			m_moveFloorSpeed = { 0.0f,0.0f,0.0f };			//�ړ����P�̈ړ����x
	D3DXMATRIX			m_moveFloor2WorldMatrix;						//�ړ����Q�̃��[���h�s��
	D3DXVECTOR3			m_moveFloor2ChildPosition = { 0.0f,0.0f,0.0f };	//�ړ����Q���猩���v���C���[�̃��[�J�����W
	D3DXVECTOR3			m_moveFloor2Speed = { 0.0f,0.0f,0.0f };			//�ړ����Q�̈ړ����x

	D3DXMATRIX			m_parentWorldMatrix;							//�u���b�N�P�̃��[���h�s��
	D3DXVECTOR3			m_childPosition = { 0.0f,0.0f,0.0f };			//�u���b�N�P�̃��[�J�����W����݂��v���C���[�̍��W

	D3DXMATRIX			m_secondParentWorldMatrix;						//�u���b�N�Q�̃��[���h�s��
	D3DXVECTOR3			m_secondChildPosition = { 0.0f,0.0f,0.0f };		//�u���b�N�Q�̃��[�J�����W����݂��v���C���[�̍��W

	LPDIRECT3DTEXTURE9	m_specularMap = NULL;					//�X�y�L�����}�b�v
	LPDIRECT3DTEXTURE9	m_normalMap = NULL;						//�@���}�b�v

	PlayerStateMachine	m_playerStateMachine;					//�X�e�[�g�}�V��
};

extern Player* player;