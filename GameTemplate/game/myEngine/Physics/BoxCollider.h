/*!
* @brief	�{�b�N�X�R���C�_�[�B
*/

#pragma once

#include "myEngine/Physics/ICollider.h"

class BoxCollider : public ICollider
{
public:
	//�R���X�g���N�^
	BoxCollider();

	//�f�X�g���N�^
	~BoxCollider();

	//�{�b�N�X�R���C�_�[���쐬
	void Create(const D3DXVECTOR3& boxHarfSize)
	{
		shape = new btBoxShape(btVector3(boxHarfSize.x, boxHarfSize.y, boxHarfSize.z));
	}

	btCollisionShape* GetBody() override
	{
		return shape;
	}

	void ConfigHalfSize() override
	{
		
	}
private:
	btBoxShape*		shape;
};