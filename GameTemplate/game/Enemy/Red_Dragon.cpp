#include "stdafx.h"
#include "Red_Dragon.h"
#include "Scene/SceneManager.h"
#include "myEngine/Timer/Timer.h"

Red_Dragon::Red_Dragon()
{
}

Red_Dragon::~Red_Dragon()
{
}

void Red_Dragon::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//���f���̏�����
	modelData.LoadModelData("Assets/modelData/Red_Dragon.x", &animation);
	model.Init(&modelData);
	//���C�g��ݒ�
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	model.SetLight(&light);

	model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	matrix = modelData.FindBoneWorldMatrix("B_bip01");

	position = pos;
	rotation = rot;
	initPosition = pos;

	state = State_Wait;
	currentAnim = AnimationWait;

	animation.SetAnimationLoopflg(AnimationDead, false);
	animation.PlayAnimation(AnimationWait, 0.3f);

	//���̂̍쐬
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.5f, 1.5f);

	//���̂̏���ݒ�
	RigidBodyInfo rbinfo;
	rbinfo.collider = coll;
	rbinfo.mass = 0.0f;
	rbinfo.pos = position;
	rbinfo.rot = rotation;
	//���̂��쐬
	rigidBody.Create(rbinfo);

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);

	//�p�[�e�B�N���̏�����
	SParticleEmitParameter param;
	param.texturePath = "Assets/sprite/FireParticleGlow.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	param.position = position;
	param.alpha = 1.0f;
	particleEmitter.Init(param);
}

void Red_Dragon::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	D3DXVECTOR3 moveSpeed = Move();
	position += moveSpeed / 60.0f;

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	//�A�j���[�V�������ς���Ă�����ύX
	if (currentAnim != prevAnim) {
		animation.PlayAnimation(currentAnim, 0.3f);
	}

	//�O�̃A�j���[�V������ۑ�
	prevAnim = currentAnim;

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3( 1.0f,1.0f,1.0f ));
}

void Red_Dragon::Render()
{
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}

D3DXVECTOR3 Red_Dragon::Move()
{
	//�ړ����x���擾
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	//���f����Z�������擾
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];
	//���f���̒��S���W���擾
	D3DXVECTOR3 modelPosition;
	modelPosition.x = matrix->m[3][0];
	modelPosition.y = matrix->m[3][1];
	modelPosition.z = matrix->m[3][2];

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 playerPos = player->GetPosition();
	//�v���C���[�ւ̃x�N�g�����v�Z
	D3DXVECTOR3 toPlayer = playerPos - modelPosition;
	
	//������
	float length = D3DXVec3Length(&toPlayer);
	float angle = 0.0f;
	D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };
	D3DXVECTOR3 toInitPosition = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 Cross = { 0.0f,0.0f,0.0f };
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);

	if (state != State_Dead && state != State_Hit) {
		//�v���C���[�Ƃ̓����蔻��𒲂ׂ�
		CollisionDetection(length, toPlayer);
	}

	toPlayer.y = 0.0f;

	switch (state)
	{
		//�ҋ@��
	case State_Wait:
		//�v���C���[�Ƃ̋����Ǝ���p�Ŕ������ꂽ������
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);
		//�������ꂽ
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			state = State_Find;
			timer = 0.0f;
			break;
		}

		timer += Timer::GetFrameDeltaTime();
		if (timer > 5.0f){
			state = State_Move;
			timer = 0.0f;
			break;
		}
		currentAnim = AnimationWait;
		break;

		//�ړ���
	case State_Move:
		//�v���C���[�Ƃ̋����Ǝ���p�Ŕ������ꂽ������
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);
		//�������ꂽ
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			state = State_Find;
			break;
		}

		move = moveSpeed * XDir;

		//�ړ������Ɍ�����ς���
		angle = D3DXVec3Dot(&direction, &XDir);
		angle = acosf(angle);
		D3DXVec3Cross(&Cross, &direction, &XDir);
		//�x�N�g����������������
		if (Cross.y < 0.0f) {
			angle *= -1.0f;
		}
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);

		//���݂̍��W���珉�����W�̋������v�Z
		toInitPosition = position - initPosition;
		toInitPosition += move / 60.0f;
		length = D3DXVec3Length(&toInitPosition);
		//�ړ��͈͂𒴂�����ҋ@
		if (length > 8.0f) {
			state = State_Wait;
			XDir *= -1.0f;
			break;
		}

		currentAnim = AnimationRun;
		break;

		//�������
	case State_Find:
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &AxisZ);
		angle = acos(angle);
		if (toPlayer.x <= 0.0f) {
			angle *= -1.0f;
		}
		toPlayer *= moveSpeed;
		move = toPlayer;
		move.y = 0.0f;

		//�v���C���[�Ƃ̋����������ƌ�����
		if (length > 20.0f) {
			state = State_Miss;
			break;
		}
		//�v���C���[�Ƃ̋������߂���΍U���Ɉڍs
		else if(length < 2.0f){
			state = State_Attack;
			break;
		}

		D3DXQuaternionRotationAxis(&rotation, &up, angle);

		currentAnim = AnimationRun;
		break;

		//�����������
	case State_Miss:
		changeDir = true;
		currentAnim = AnimationWait;
		timer += Timer::GetFrameDeltaTime();
		//�v���C���[�Ƃ̋����Ǝ���p�Ŕ������ꂽ������
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);
		//�������ꂽ
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			state = State_Find;
			timer = 0.0f;
			break;
		}

		//��莞�Ԍo�Ə������W�ɖ߂�
		if (timer > 3.0f) {
			//���݂̍��W���珉�����W�ւ̋����ƕ������v�Z
			toInitPosition = initPosition - position;
			length = D3DXVec3Length(&toInitPosition);
			D3DXVec3Normalize(&toInitPosition, &toInitPosition);

			if (changeDir) {
				//�ړ������Ɍ�����ς���
				angle = D3DXVec3Dot(&direction, &toInitPosition);
				if (angle < -1.0f)
				{
					angle = -1.0f;
				}
				if (angle > 1.0f)
				{
					angle = 1.0f;
				}
				angle = acosf(angle);
				D3DXVec3Cross(&Cross, &direction, &toInitPosition);
				//�x�N�g����������������
				if (Cross.y < 0.0f) {
					angle *= -1.0f;
				}
				D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
				D3DXQuaternionMultiply(&rotation, &rotation, &rot);

				changeDir = false;
			}

			//�ړ����x���v�Z
			toInitPosition *= moveSpeed;
			move = toInitPosition;
			move.y = 0.0f;

			//�������W�ɖ߂�����ҋ@���
			if (length < 0.2f) {
				state = State_Wait;
				timer = 0.0f;
				break;
			}
			currentAnim = AnimationRun;
		}
		break;

		//�U����
	case State_Attack:
		particleEmitter.SetSpeed(GetDirection() * 1.5f);
		particleEmitter.SetPosition(modelPosition);
		particleEmitter.Update();
		timer += Timer::GetFrameDeltaTime();

		attackTimer += Timer::GetFrameDeltaTime();
		if (attackTimer >= 0.5f) {
			length = D3DXVec3Length(&toPlayer);
			D3DXVec3Normalize(&toPlayer, &toPlayer);
			angle = D3DXVec3Dot(&toPlayer, &direction);
			angle = acos(angle);
			//�U������������
			if (fabsf(angle) < D3DXToRadian(15.0f) && length < 5.0f) {
				if (attackTimer >= 0.8f) {
					//�v���C���[�����S
					m_hitPlayer = true;
					player->SetHitEnemy(m_hitPlayer);
					state = State_Hit;
				}
			}
			else {
				attackTimer = 0.0f;
			}
		}

		if (timer > 2.5f) {
			length = D3DXVec3Length(&toPlayer);
			D3DXVec3Normalize(&toPlayer, &toPlayer);
			angle = D3DXVec3Dot(&toPlayer, &direction);
			angle = acos(angle);
			//�������ꂽ
			if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
				findAgainFlag = true;
			}

			if (findAgainFlag) {
				state = State_Find;
				findAgainFlag = false;
			}
			else if (!findAgainFlag && length > 2.0f) {
				state = State_Miss;
			}
			timer = 0.0f;
		}

		currentAnim = AnimationAttack;

		soundTimer += Timer::GetFrameDeltaTime();
		if (soundTimer >= 1.0f) {
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Fire.wav");
			SE->Play(false);
			soundTimer = 0.0f;
			SE->SetisDead();
		}

		break;
		//���S��
	case State_Dead:
		move = { 0.0f,0.0f,0.0f };
		currentAnim = AnimationDead;
		if (!animation.IsPlay()) {
			SetisDead();
			//���̂��폜
			g_physicsWorld->RemoveRigidBody(&rigidBody);
		}

		break;
		//�v���C���[�Ƀq�b�g
	case State_Hit:
		timer += Timer::GetFrameDeltaTime();
		move = { 0.0f,0.0f,0.0f };
		if (timer >= 5.0f) {
			isDead = true;
			timer = 0.0f;
		}
		break;
	}

	return move;
}

void Red_Dragon::CollisionDetection(float Length, const D3DXVECTOR3& ToPlayer)
{
	if (Length <= 1.5f) {
		D3DXVECTOR3 toPlayerXZ = { ToPlayer.x,0.0f,ToPlayer.z };
		float lengthXZ = D3DXVec3Length(&toPlayerXZ);

		D3DXVECTOR3 toPlayerY = { 0.0f,ToPlayer.y,0.0f };
		float lengthY = D3DXVec3Length(&toPlayerY);

		//Y�����ɓ�������
		if (toPlayerY.y > 0.0f && lengthY <= 0.5f) {
			//�h���S�������S
			player->SetTreadOnEnemy(true);
			state = State_Dead;
		}
		//XZ�����ɓ�������
		else if (lengthY <= 0.8f && lengthXZ <= 1.1f) {
			//�v���C���[�����S
			m_hitPlayer = true;
			player->SetHitEnemy(m_hitPlayer);
			state = State_Hit;
		}
	}
}