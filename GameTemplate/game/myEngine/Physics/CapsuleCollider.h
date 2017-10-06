/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#pragma once

#include "myEngine/Physics/ICollider.h"

class CapsuleCollider : public ICollider
{
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	CapsuleCollider();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~CapsuleCollider();
	/*!
	* @brief	�쐬�B
	*/
	void Create(float radius, float height)
	{
		shape = new btCapsuleShape(radius, height);
		ConfigHalfSize();	
	}

	// �����̃T�C�Y���x�N�g���Ŏ擾�B
	void ConfigHalfSize() override {
		btVector3 size = shape->getImplicitShapeDimensions();
		halfSize = D3DXVECTOR3(size.getX(), size.getY() + size.getZ(), size.getZ());
	}

	btCollisionShape* GetBody() override
	{
		return shape;
	}
private:
	btCapsuleShape*		shape;
};

// X
//halfSize = D3DXVECTOR3(size.getX() + size.getY(), size.getY(), size.getZ());

// Z
//halfSize = D3DXVECTOR3(size.getX(), size.getY(), size.getZ() + size.getY());
