#pragma once

#include "myEngine/Physics/ICollider.h"


class SphereCollider : ICollider
{
public:
	//�R���X�g���N�^
	SphereCollider();

	//�f�X�g���N�^
	~SphereCollider();

	//���̃R���C�_�[���쐬
	void Create(const float radius);
	btCollisionShape* GetBody() override
	{
		return shape;
	}

	void ConfigHalfSize() override
	{

	}
private:
	btSphereShape*		shape;
};