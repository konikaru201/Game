#include "stdafx.h"
#include "Player.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"

#define SPEED 8.0f

Player* player;

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Start()
{
	//スペキュラマップをロード
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_spec.tga",
		&specularMap
	);

	if (specularMap != NULL) {
		model.SetSpecularMap(specularMap);
	}

	//モデルデータをロードして初期化
	modelData.LoadModelData("Assets/modelData/Unity.x", &animation);
	model.Init(&modelData);
	//ライトを設定
	model.SetLight(&gameScene->GetLight());

	//座標と向きを初期化
	position = { 0.0f,0.0f,0.0f };
	rotation = { 0.0f,0.0f,0.0f,1.0f };

	//キャラクターコントローラーを初期化
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.3f, 1.0f);
	characterController.Init(coll, position);
	characterController.SetGravity(-20.0f);	//重力強め

	animation.PlayAnimation(AnimationStand, 0.3f);
	animation.SetAnimationEndTime(AnimationRun, 0.8f);
	animation.SetAnimationLoopflg(AnimationJump, false);

	return true;
}

void Player::Update()
{
	if (gameScene == nullptr) { return; }

	//移動速度を設定
	characterController.SetMoveSpeed(Move());
	//キャラクターコントローラーを実行
	characterController.Execute();
	//座標を設定
	position = characterController.GetPosition();

	if (pad->GetLStickXF() != 0.0f || pad->GetLStickYF() != 0.0f) {
		//移動しているなら向きを変える
		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), atan2f(dir.x, dir.z));
		if (characterController.IsJump() == false) {
			currentAnim = AnimationRun;
		}
	}
	else {
		if (characterController.IsJump() == false) {
			currentAnim = AnimationStand;
		}
	}

	//移動床の上いるなら移動床についていく
	if (characterController.IsOnMoveFloor() == true || characterController.IsOnMoveFloor2() == true)
	{
		//移動床が止まっているならついていかない
		if (gameScene->GetMap()->GetMoveFloor() != nullptr 
			&& gameScene->GetMap()->GetMoveFloor2() != nullptr
			&& gameScene->GetMap()->GetMoveFloor()->GetMoveFlag() == true
			|| gameScene->GetMap()->GetMoveFloor2()->GetMoveFlag() == true) {
			D3DXVECTOR3 AddPos;
			if (characterController.IsOnMoveFloor() == true)
			{
				AddPos = gameScene->GetMap()->GetMoveFloor()->GetMoveSpeed();
			}
			else
			{
				AddPos = gameScene->GetMap()->GetMoveFloor2()->GetMoveSpeed();
			}
			position += AddPos;
			characterController.SetPosition(position);
		}
	}

	//ジャンプブロックに当たったとき
	if (gameScene->GetMap()->GetJumpBlock() != nullptr 
		&& characterController.IsOnJumpBlock() == true)
	{
		D3DXVECTOR3 AddPos = gameScene->GetMap()->GetJumpBlock()->GetMoveSpeed();
		characterController.SetMoveSpeed(AddPos);
	}

	//落ちたら死亡フラグを立てる
	if (position.y <= -20.0f)
	{
		isDead = true;
		//position = { 0.0f,0.0f,0.0f };
		//characterController.SetPosition(position);
	}

	//アニメーションが変わっていたら変更
	if (currentAnim != prevAnim) {
		animation.PlayAnimation(currentAnim, 0.3f);
	}

	//前のアニメーションを保存
	prevAnim = currentAnim;

	//2，3回目のジャンプは一定時間経つとできなくする
	//2回目のジャンプ
	if (JumpCount == 1 && GetIsOnGround()) 
	{
		JumpFrameCount++;
		if (JumpFrameCount % 10 == 0) {
			JumpCount = 0;
			JumpFrameCount = 0;
		}
	}
	//3回目のジャンプ
	else if (JumpCount == 2 && GetIsOnGround()) 
	{
		JumpFrameCount++;
		if (JumpFrameCount % 8 == 0) {
			JumpCount = 0;
			JumpFrameCount = 0;
		}
	}

	//アニメーションの更新
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Player::Render()
{
	if (gameScene == nullptr) { return; }
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}

//void Player::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
//{
//	model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
//	model.Draw(viewMatrix, projMatrix);
//}

D3DXVECTOR3 Player::Move()
{
	//移動速度を取得
	D3DXVECTOR3 move = characterController.GetMoveSpeed();

	//スティックの入力量を取得
	D3DXVECTOR3 moveDir;
	moveDir.y = 0.0f;
	moveDir.x = pad->GetLStickXF();
	moveDir.z = pad->GetLStickYF();

	//カメラの逆行列を作成
	D3DXMATRIX ViewMatrix = gameScene->GetGameCamera()->GetViewMatrix();
	D3DXMATRIX ViewMatrixInv;
	D3DXMatrixInverse(&ViewMatrixInv, 0, &ViewMatrix);

	//カメラ空間から見た奥方向のベクトル
	D3DXVECTOR3 cameraVecZ;
	cameraVecZ.x = ViewMatrixInv.m[2][0];
	cameraVecZ.y = 0.0f;
	cameraVecZ.z = ViewMatrixInv.m[2][2];
	D3DXVec3Normalize(&cameraVecZ, &cameraVecZ);

	//カメラ空間から見た横方向のベクトル
	D3DXVECTOR3 cameraVecX;
	cameraVecX.x = ViewMatrixInv.m[0][0];
	cameraVecX.y = 0.0f;
	cameraVecX.z = ViewMatrixInv.m[0][2];
	D3DXVec3Normalize(&cameraVecX, &cameraVecX);

	//キャラクターの向きを計算
	dir.x = cameraVecX.x * moveDir.x + cameraVecZ.x * moveDir.z;
	dir.y = 0.0f;
	dir.z = cameraVecX.z * moveDir.x + cameraVecZ.z * moveDir.z;

	//移動速度を計算
	move.x = dir.x * SPEED;
	move.z = dir.z * SPEED;

	//Aボタンが押されたらジャンプ
	if (pad->IsTrigger(pad->enButtonA)
		&& !characterController.IsJump()
		&& GetIsOnGround())
	{
		if (JumpCount == 0) {
			move.y = 8.0f;
			//move.y = 12.0f;
			JumpCount++;
		}
		//走りながら2,3回目のジャンプができる
		else if (move.x != 0.0f || move.z != 0.0f) {
			if (JumpCount == 1) {
				move.y = 12.0f;
				JumpCount++;
			}
			else if (JumpCount == 2) {
				move.y = 16.0f;
				JumpCount = 0;
			}
		}
		characterController.Jump();
		currentAnim = AnimationJump;
	}

	return move;
}

void Player::Reset()
{
	//座標と向きを初期化
	position = { 0.0f,0.0f,0.0f };
	rotation = { 0.0f,0.0f,0.0f,1.0f };
	characterController.SetPosition(position);

	isDead = false;

	//アニメーションの更新
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}