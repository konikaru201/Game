#pragma once

#include "Number.h"

class RemainNumber : public GameObject
{
public:
	//�R���X�g���N�^
	RemainNumber();

	//�f�X�g���N�^
	~RemainNumber();

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

	void RemainCount(int count)
	{
		m_remainNum += count;
	}

	//�c�@�����l��
	int GetRemainNum()
	{
		return m_remainNum;
	}
private:
	Number*		num[3];						//����
	D3DXVECTOR2 m_position = { 0.0f,0.0f }; //���W
	int			m_remainNum = 3;			//�c�@��
};

extern RemainNumber* remainNumber;