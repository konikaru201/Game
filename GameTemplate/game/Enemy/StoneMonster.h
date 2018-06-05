/*!
*@brief	�X�g�[�������X�^�[�N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
#include "StoneMonsterStateMachine.h"

class StoneMonster : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	StoneMonster();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~StoneMonster();
	/*!
	*@brief	������
	* @param[in]	pos		���W
	* @param[in]	rot		��]
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
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
	* @brief	�X�g�[�������X�^�[�̍��W�̎擾
	*@return	�X�g�[�������X�^�[�̍��W
	*/
	const D3DXVECTOR3& GetPosition()
	{
		return m_position;
	}
	/*!
	*@brief	���W�̐ݒ�
	* @param[in]	position		���W
	*/
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
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
	* @param[in]	rotation		��]
	*/
	void SetRotation(const D3DXQUATERNION& rotation)
	{
		m_rotation = rotation;
	}
	/*!
	* @brief	�X�g�[�������X�^�[�̌������擾
	*@return	�X�g�[�������X�^�[�̌���
	*/
	const D3DXVECTOR3& GetDirection()
	{
		D3DXMATRIX matrix = m_model.GetWorldMatrix();
		m_direction.x = matrix.m[2][0];
		m_direction.y = matrix.m[2][1];
		m_direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&m_direction, &m_direction);
		return m_direction;
	}
	/*!
	* @brief	�ړ����x���擾
	*@return	�ړ����x
	*/
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return m_characterController.GetMoveSpeed();
	}
	/*!
	*@brief	�ړ����x��ݒ�
	* @param[in]	moveSpeed	�ړ����x
	*/
	void SetMoveSpeed(const D3DXVECTOR3& moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	/*!
	*@brief	���܂ꂽ�t���O���擾
	*/
	bool GetIsStepOn()
	{
		return m_isStepOn;
	}
	/*!
	*@brief	�ړ����P�̏�ɂ��邩����
	*/
	bool GetIsOnMoveFloor()
	{
		return m_moveFloorHit;
	}
	/*!
	*@brief	�ړ����Q�̏�ɂ��邩����
	*/
	bool GetIsOnMoveFloor2()
	{
		return m_moveFloor2Hit;
	}
	/*!
	* @brief	�ړ����P�̍��W���擾
	*@return	�ړ����P�̍��W
	*/
	const D3DXVECTOR3& GetMoveFloorPosition()
	{
		return m_moveFloorPosition;
	}
	/*!
	* @brief	�ړ����Q�̍��W���擾
	*@return	�ړ����Q�̍��W
	*/
	const D3DXVECTOR3& GetMoveFloor2Position()
	{
		return m_moveFloor2Position;
	}
private:
	SkinModel					m_model;							//�X�L�����f��
	SkinModelData				m_modelData;						//�X�L�����f���f�[�^
	Light						m_light;							//���C�g
	D3DXVECTOR3					m_position;							//���W
	D3DXQUATERNION				m_rotation;							//��]
	D3DXVECTOR3					m_scale;							//�g��
	D3DXVECTOR3					m_direction;						//����
	Animation					m_animation;						//�A�j���[�V����
	D3DXVECTOR3					m_moveSpeed = { 0.0f,0.0f,0.0f };	//�ړ����x
	CharacterController			m_characterController;				//�L�����N�^�[�R���g���[���[
	StoneMonsterStateMachine	m_stoneMonsterStateMachine;			//�X�e�[�g�}�V��

	D3DXMATRIX					m_parentWorldMatrix;						//�ړ����P�̃��[���h�s��
	D3DXVECTOR3					m_childPosition = { 0.0f,0.0f,0.0f };		//�ړ����P�̃��[�J�����W����݂����W
	bool						m_moveFloorHit = false;						//�ړ����P�̏�ɂ��邩
	D3DXVECTOR3					m_moveFloorPosition = { 0.0f,0.0f,0.0f };	//�ړ����P�̍��W

	D3DXMATRIX					m_secondParentWorldMatrix;					//�ړ����Q�̃��[���h�s��
	D3DXVECTOR3					m_secondChildPosition = { 0.0f,0.0f,0.0f };	//�ړ����Q�̃��[�J�����W����݂��v���C���[�̍��W
	bool						m_moveFloor2Hit = false;					//�ړ����Q�̏�ɂ��邩
	D3DXVECTOR3					m_moveFloor2Position = { 0.0f,0.0f,0.0f };	//�ړ����Q�̍��W

	float						m_deadTimer = 0.0f;					//���S���Ă���̃^�C�}�[
	bool						m_isStepOn = false;					//���܂ꂽ�t���O
	bool						m_isHitPlaer = false;				//�v���C���[�ɓ���������
};