/*!
*@brief	�����N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"

class Number{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Number();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Number();
	/*!
	*@brief	������
	* @param[in]	numPos		���W
	* @param[in]	numSize		�T�C�Y
	*/
	void Init(D3DXVECTOR2 numPos, D3DXVECTOR2 numSize);
	/*!
	*@brief	���l��ݒ�
	* @param[in]	n		����
	*/
	void NumSet(int n);
	/*!
	*@brief	�`��
	*/
	void Render();
private:
	std::unique_ptr<Sprite> m_number[10];	//0�`9�̐����̃X�v���C�g
	int						m_num = 0;		//������ێ�����ϐ�
};