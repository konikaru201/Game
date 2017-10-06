#pragma once

#include "myEngine/Physics/ICollider.h"


class SphereCollider : ICollider
{
public:
	//コンストラクタ
	SphereCollider();

	//デストラクタ
	~SphereCollider();

	//球体コライダーを作成
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