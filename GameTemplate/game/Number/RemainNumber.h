/*!
*@brief	�c�@�N���X
*/
#pragma once

#include "Number.h"

class RemainNumber : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	RemainNumber();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~RemainNumber();
	/*!
	*@brief	������
	* @param[in]	position		���W
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
	*@brief	�폜
	*/
	void DeleteNum();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	*@brief	�`��
	*@param[in]		count	�c�@�𑝂₷��
	*/
	void RemainCount(int count)
	{
		m_remainNum += count;
	}
	/*!
	*@brief	�c�@�����l��
	*@return	�c�@��
	*/
	int GetRemainNum()
	{
		return m_remainNum;
	}
private:
	Number*		m_num[3];						//����
	D3DXVECTOR2 m_position = { 0.0f,0.0f }; //���W
	int			m_remainNum = 3;			//�c�@��
};