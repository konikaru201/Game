/*!
* @brief	ボックスコライダー。
*/

#pragma once

#include "myEngine/Physics/ICollider.h"

class BoxCollider : public ICollider
{
public:
	//コンストラクタ
	BoxCollider();

	//デストラクタ
	~BoxCollider();

	//ボックスコライダーを作成
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