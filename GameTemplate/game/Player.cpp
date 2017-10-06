#include "stdafx.h"
#include "game.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::Init()
{
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	modelData.LoadModelData("Assets/modelData/Unity.X", &animation);
	model.Init(&modelData);
	model.SetLight(&light);
	animation.PlayAnimation(0);
	//�L�����N�^�R���g���[�����������B
	D3DXVECTOR3 pos = D3DXVECTOR3(10.0f, 5.0f, 0.0f);
	characterController.Init(0.3f, 1.0f, pos);
	characterController.SetGravity(-20.0f);	//�d�͋��߁B
}
void Player::Update()
{
	//�p�b�h�̓��͂œ������B
	D3DXVECTOR3 moveSpeed = characterController.GetMoveSpeed();
	float fMoveSpeed = 8.0f;
	moveSpeed.x = 0.0f; 
	moveSpeed.z = 0.0f;
	if (GetAsyncKeyState(VK_LEFT) != 0) {
		moveSpeed.x = fMoveSpeed;
	}
	if (GetAsyncKeyState(VK_RIGHT) != 0) {
		moveSpeed.x = -fMoveSpeed;
	}
	if (GetAsyncKeyState(VK_UP) != 0) {
	
		moveSpeed.z = -fMoveSpeed;
	}
	if (GetAsyncKeyState(VK_DOWN) != 0) {
		moveSpeed.z = fMoveSpeed;
	}
	if (GetAsyncKeyState('J') != 0) {
		//�W�����v
		moveSpeed.y = 10.0f;
		//�W�����v�������Ƃ��L�����N�^�R���g���[���[�ɒʒm�B
		characterController.Jump();
	}
	//�L�����N�^���������x��ݒ�B
	characterController.SetMoveSpeed(moveSpeed);
	//�L�����N�^�R���g���[���[�����s�B
	characterController.Execute();	

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(characterController.GetPosition(), D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}
void Player::Draw()
{
	model.Draw(&game->GetCamera()->GetViewMatrix(), &game->GetCamera()->GetProjectionMatrix());
}
