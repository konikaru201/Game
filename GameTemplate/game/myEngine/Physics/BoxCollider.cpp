/*!
* @brief	�{�b�N�X�R���C�_�[�B
*/

#include "stdafx.h"
#include "BoxCollider.h"

/*!
* @brief	�R���X�g���N�^�B
*/
BoxCollider::BoxCollider() :
	shape(NULL)
{
}

/*!
* @brief	�f�X�g���N�^�B
*/
BoxCollider::~BoxCollider()
{
	delete shape;
}