/*!
* @brief	ボックスコライダー。
*/

#include "stdafx.h"
#include "BoxCollider.h"

/*!
* @brief	コンストラクタ。
*/
BoxCollider::BoxCollider() :
	shape(NULL)
{
}

/*!
* @brief	デストラクタ。
*/
BoxCollider::~BoxCollider()
{
	delete shape;
}