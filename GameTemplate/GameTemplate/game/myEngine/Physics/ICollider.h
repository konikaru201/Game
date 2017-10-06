/*!
 * @brief	�R���C�_�[�B
 */

#pragma once

/*!
 * @brief	�R���C�_�[�̃C���^�[�t�F�[�X�N���X�B
 */
class ICollider {
public:
	virtual btCollisionShape* GetBody() = 0;

	virtual void ConfigHalfSize() = 0;

	//�����̃T�C�Y���擾
	const D3DXVECTOR3& GetHalfSize() {
		return halfSize;
	}

protected:
	D3DXVECTOR3 halfSize;	//�����̃T�C�Y
};
