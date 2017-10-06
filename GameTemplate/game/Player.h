#pragma once

#include "myEngine/Physics/CharacterController.h"

class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
	D3DXVECTOR3 GetPosition()
	{
		return characterController.GetPosition();
	}
private:
	SkinModel model;
	SkinModelData modelData;
	Animation animation;
	Light light;
	CharacterController characterController;	//�L�����N�^�R���g���[���B
};

