/*!
 * @brief	コライダー。
 */

#pragma once

/*!
 * @brief	コライダーのインターフェースクラス。
 */
class ICollider {
public:
	virtual btCollisionShape* GetBody() = 0;

	virtual void ConfigHalfSize() = 0;

	//半分のサイズを取得
	const D3DXVECTOR3& GetHalfSize() {
		return halfSize;
	}

protected:
	D3DXVECTOR3 halfSize;	//半分のサイズ
};
