/*!
*@brief	�V���G�b�g�N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"

class Silhouette : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Silhouette();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Silhouette();
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();
};