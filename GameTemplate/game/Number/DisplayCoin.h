#pragma once

#include "Number.h"

class DisplayCoin : public GameObject
{
public:
	//�R���X�g���N�^
	DisplayCoin();

	//�f�X�g���N�^
	~DisplayCoin();

	//�X�V����O�ɌĂ΂��֐�
	bool Start();

	//�X�V
	void Update();

	//�폜
	void DeleteNum();

	//�`��
	void Render();
private:
	Number* num[2];
};