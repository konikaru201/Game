/*!
*@brief	�R�C��UI�N���X
*/
#pragma once

#include "Number.h"

class DisplayCoin : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	DisplayCoin();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~DisplayCoin();
	/*!
	*@brief	������
	*@param[in] position	���W
	*/
	void Init(D3DXVECTOR2 position);
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��֐�
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
	/*!
	*@brief	�R�C���̖������J�E���g
	*/
	void CoinCount()
	{
		m_coinNum++;
	}
private:
	std::unique_ptr<Number>		m_num[2];					//����
	D3DXVECTOR2					m_position = { 0.0f,0.0f }; //���W
	int							m_coinNum = 0;				//�R�C���̖���
};