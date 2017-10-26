/*!
 * @brief	�L�����N�^�R���g���[���[�B
 */

#pragma once

#include "CapsuleCollider.h"
#include "myEngine/Physics/RigidBody.h"

class ICollider;

static const float cPI = 3.14159265358979323846f;
/*!
	* @brief	�L�����N�^�R���g���[���[�B
	*/
class CharacterController{
public:
	CharacterController() {
		m_position = {0.0f, 0.0f, 0.0f};
		m_moveSpeed = {0.0f, 0.0f, 0.0f};
	}
	~CharacterController()
	{
		if (m_collider != nullptr) {
			delete m_collider;
			m_collider = nullptr;
		}
	}
	/*!
		* @brief	�������B
		*/
	void Init(ICollider* collider, const D3DXVECTOR3& position);
	/*!
		* @brief	���s�B
		*/
	void Execute();
	/*!
		* @brief	���W���擾�B
		*/
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}
	/*!
		* @brief	���W��ݒ�B
		*/
	void SetPosition(const D3DXVECTOR3& pos)
	{
		m_position = pos;
	}
	/*!
		* @brief	�ړ����x��ݒ�B
		*/
	void SetMoveSpeed(const D3DXVECTOR3& speed )
	{
		m_moveSpeed = speed;
	}
	/*!
		* @brief	�ړ����x���擾�B
		*/
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/*!
		* @brief	�W�����v������B
		*/
	void Jump( )
	{
		m_isJump = true;
		m_isOnGround = false;
		m_isOnMoveFloor = false;
		m_isOnMoveFloor2 = false;
		m_isOnJumpBlock = false;
	}
	/*!
		* @brief	�W�����v��������
		*/
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	�n�ʏ�ɂ��邩����B
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	�ǂɓ������Ă��邩����B
	*/
	bool IsOnWall() const
	{
		return m_isOnWall;
	}
	/*!
	* @brief	�ړ�����ɂ��邩����B
	*/
	bool IsOnMoveFloor() const
	{
		return m_isOnMoveFloor;
	}
	/*!
	* @brief	�ړ�����ɂ��邩����B
	*/
	bool IsOnMoveFloor2() const
	{
		return m_isOnMoveFloor2;
	}
	/*!
	* @brief	�W�����v�u���b�N��ɂ��邩����B
	*/
	bool IsOnJumpBlock() const
	{
		return m_isOnJumpBlock;
	}
	/*!
	* @brief	�R���C�_�[���擾�B
	*/
	ICollider* GetCollider()
	{
		return m_collider;
	}
	/*!
	* @brief	�d�͂��擾�B
	*/
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}
	/*!
	* @brief	�ǂ̖@�����擾�B
	*/
	D3DXVECTOR3 GethitNormal()
	{
		return m_hitNormal;
	}
	/*!
	* @brief	���̂��擾�B
	*/
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
private:
	D3DXVECTOR3 		m_position;						//���W�B
	D3DXVECTOR3 		m_moveSpeed;					//�ړ����x�B
	bool 				m_isJump = false;				//�W�����v���H
	bool				m_isOnGround = true;			//�n�ʂ̏�ɂ���H
	bool				m_isOnMoveFloor = false;		//�ړ����̏�ɂ���H
	bool				m_isOnMoveFloor2 = false;		//�ړ����̏�ɂ���H
	bool				m_isOnJumpBlock = false;		//�W�����v�u���b�N�̏�ɂ���H
	bool				m_isOnWall = false;
	ICollider*			m_collider = nullptr;			//�R���C�_�[�B
	//float				m_radius = 0.0f;
	//float				m_height = 0.0f;		
	RigidBody			m_rigidBody;					//���́B
	float				m_gravity = -9.8f;				//�d�́B
	D3DXVECTOR3			m_hitNormal = { 0.0f,0.0f,0.0f };
	bool				m_hitceiling = false;
};
