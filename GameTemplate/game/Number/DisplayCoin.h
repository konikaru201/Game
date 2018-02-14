#pragma once

#include "Number.h"

class DisplayCoin : public GameObject
{
public:
	//�R���X�g���N�^
	DisplayCoin();

	//�f�X�g���N�^
	~DisplayCoin();

	//������
	void Init(D3DXVECTOR2 position);

	//�X�V����O�ɌĂ΂��֐�
	bool Start();

	//�X�V
	void Update();

	//�폜
	void DeleteNum();

	//�`��
	void Render();

	//�R�C���̖������J�E���g
	void CoinCount(int count)
	{
		m_coinNum += count;
	}
private:
	Number*		num[2];						//����
	D3DXVECTOR2 m_position = { 0.0f,0.0f }; //���W
	int			m_coinNum = 0;				//�R�C���̖���
};

extern DisplayCoin* displayCoin;