/*!
 * @brief	カプセルコライダー。
 */

#pragma once

#include "myEngine/Physics/ICollider.h"

class CapsuleCollider : public ICollider
{
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	CapsuleCollider();
	/*!
	 * @brief	デストラクタ。
	 */
	~CapsuleCollider();
	/*!
	* @brief	作成。
	*/
	void Create(float radius, float height)
	{
		shape = new btCapsuleShape(radius, height);
		ConfigHalfSize();	
	}

	// 半分のサイズをベクトルで取得。
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
