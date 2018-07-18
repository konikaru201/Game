#include "stdafx.h"
#include "Red_Dragon.h"
#include "Scene/SceneManager.h"
#include "myEngine/Timer/Timer.h"
#include "myEngine/Sound/SoundSource.h"

Red_Dragon::Red_Dragon()
{
}

Red_Dragon::~Red_Dragon()
{
}

void Red_Dragon::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//���f���̏�����
	m_modelData.LoadModelData("Assets/modelData/Red_Dragon.x", &m_animation);
	m_model.Init(&m_modelData);
	//���C�g��ݒ�
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	m_model.SetLight(&m_light);

	m_model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	m_matrix = m_modelData.FindBoneWorldMatrix("B_bip01");

	m_position = pos;
	m_rotation = rot;
	m_initPosition = pos;

	m_state = State_Wait;
	m_currentAnim = AnimationWait;

	m_animation.SetAnimationLoopflg(AnimationDead, false);
	m_animation.PlayAnimation(AnimationWait, 0.3f);

	//���̂̍쐬
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.5f, 1.5f);

	//���̂̏���ݒ�
	RigidBodyInfo rbinfo;
	rbinfo.collider = coll;
	rbinfo.mass = 0.0f;
	rbinfo.pos = m_position;
	rbinfo.rot = m_rotation;
	//���̂��쐬
	m_rigidBody.Create(rbinfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&m_rigidBody);

	//�e��`�悷��t���O�𗧂Ă�
	SetRenderToShadow();

	//�p�[�e�B�N���̏�����
	SParticleEmitParameter param;
	param.texturePath = "Assets/sprite/FireParticleGlow.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	param.position = m_position;
	param.alpha = 1.0f;
	m_particleEmitter.Init(param);
}

void Red_Dragon::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	D3DXVECTOR3 moveSpeed = Move();
	m_position += moveSpeed / 60.0f;

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	//�A�j���[�V�������ς���Ă�����ύX
	if (m_currentAnim != m_prevAnim) {
		m_animation.PlayAnimation(m_currentAnim, 0.3f);
	}

	//�O�̃A�j���[�V������ۑ�
	m_prevAnim = m_currentAnim;

	m_animation.Update(1.0f / 60.0f);
	m_model.UpdateWorldMatrix(m_position, m_rotation, D3DXVECTOR3( 1.0f,1.0f,1.0f ));
}

void Red_Dragon::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

D3DXVECTOR3 Red_Dragon::Move()
{
	//�ړ����x���擾
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	//���f����Z�������擾
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = m_model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];
	//���f���̒��S���W���擾
	D3DXVECTOR3 modelPosition;
	modelPosition.x = m_matrix->m[3][0];
	modelPosition.y = m_matrix->m[3][1];
	modelPosition.z = m_matrix->m[3][2];

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 playerPos = player->GetPosition();
	playerPos.y += 0.5f;
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

	if (m_state != State_Dead && m_state != State_Hit) {
		//�v���C���[�Ƃ̓����蔻��𒲂ׂ�
		CollisionDetection(length, toPlayer);
	}

	toPlayer.y = 0.0f;

	switch (m_state)
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
			m_state = State_Find;
			m_timer = 0.0f;
			break;
		}

		m_timer += Timer::GetFrameDeltaTime();
		if (m_timer > 5.0f){
			m_state = State_Move;
			m_timer = 0.0f;
			break;
		}
		m_currentAnim = AnimationWait;
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
			m_state = State_Find;
			break;
		}

		move = m_moveSpeed * m_XDir;

		//�ړ������Ɍ�����ς���
		angle = D3DXVec3Dot(&direction, &m_XDir);
		angle = acosf(angle);
		D3DXVec3Cross(&Cross, &direction, &m_XDir);
		//�x�N�g����������������
		if (Cross.y < 0.0f) {
			angle *= -1.0f;
		}
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);

		//���݂̍��W���珉�����W�̋������v�Z
		toInitPosition = m_position - m_initPosition;
		toInitPosition += move / 60.0f;
		length = D3DXVec3Length(&toInitPosition);
		//�ړ��͈͂𒴂�����ҋ@
		if (length > 8.0f) {
			m_state = State_Wait;
			m_XDir *= -1.0f;
			break;
		}

		m_currentAnim = AnimationRun;
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
		toPlayer *= m_moveSpeed;
		move = toPlayer;
		move.y = 0.0f;

		//�v���C���[�Ƃ̋������߂���΍U���Ɉڍs
		if (length < 2.0f) {
			m_state = State_Attack;
			break;
		}

		//���݂̍��W���珉�����W�̋������v�Z
		toInitPosition = m_position - m_initPosition;
		toInitPosition += move / 60.0f;
		length = D3DXVec3Length(&toInitPosition);

		//�����ʒu���痣���ƒǂ������Ȃ�
		if (length > 10.0f) {
			m_state = State_Miss;
			break;
		}

		D3DXQuaternionRotationAxis(&m_rotation, &m_up, angle);

		m_currentAnim = AnimationRun;
		break;

		//�����������
	case State_Miss:
		m_changeDir = true;
		m_currentAnim = AnimationWait;
		m_timer += Timer::GetFrameDeltaTime();
		//�v���C���[�Ƃ̋����Ǝ���p�Ŕ������ꂽ������
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);
		//�������ꂽ
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			m_state = State_Find;
			m_timer = 0.0f;
			break;
		}

		//��莞�Ԍo�Ə������W�ɖ߂�
		if (m_timer > 3.0f) {
			//���݂̍��W���珉�����W�ւ̋����ƕ������v�Z
			toInitPosition = m_initPosition - m_position;
			length = D3DXVec3Length(&toInitPosition);
			D3DXVec3Normalize(&toInitPosition, &toInitPosition);

			if (m_changeDir) {
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
				D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);

				m_changeDir = false;
			}

			//�ړ����x���v�Z
			toInitPosition *= m_moveSpeed;
			move = toInitPosition;
			move.y = 0.0f;

			//�������W�ɖ߂�����ҋ@���
			if (length < 0.2f) {
				m_state = State_Wait;
				m_timer = 0.0f;
				break;
			}
			m_currentAnim = AnimationRun;
		}
		break;

		//�U����
	case State_Attack:
		m_particleEmitter.SetSpeed(GetDirection() * 1.5f);
		m_particleEmitter.SetPosition(modelPosition);
		m_particleEmitter.Update();
		m_timer += Timer::GetFrameDeltaTime();

		m_attackTimer += Timer::GetFrameDeltaTime();
		if (m_attackTimer >= 0.5f) {
			length = D3DXVec3Length(&toPlayer);
			D3DXVec3Normalize(&toPlayer, &toPlayer);
			angle = D3DXVec3Dot(&toPlayer, &direction);
			angle = acos(angle);
			//�U������������
			if (fabsf(angle) < D3DXToRadian(15.0f) && length < 5.0f) {
				if (m_attackTimer >= 0.8f) {
					//�v���C���[�����S
					m_hitPlayer = true;
					player->SetHitEnemy(m_hitPlayer);
					m_state = State_Hit;
				}
			}
			else {
				m_attackTimer = 0.0f;
			}
		}

		if (m_timer > 2.5f) {
			length = D3DXVec3Length(&toPlayer);
			D3DXVec3Normalize(&toPlayer, &toPlayer);
			angle = D3DXVec3Dot(&toPlayer, &direction);
			angle = acos(angle);
			//�������ꂽ
			if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
				m_findAgainFlag = true;
			}

			if (m_findAgainFlag) {
				m_state = State_Find;
				m_findAgainFlag = false;
			}
			else if (!m_findAgainFlag && length > 2.0f) {
				m_state = State_Miss;
			}
			m_timer = 0.0f;
		}

		m_currentAnim = AnimationAttack;

		m_soundTimer += Timer::GetFrameDeltaTime();
		if (m_soundTimer >= 1.0f) {
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Fire.wav");
			SE->Play(false);
			m_soundTimer = 0.0f;
			SE->SetisDead();
		}

		break;
		//���S��
	case State_Dead:
		move = { 0.0f,0.0f,0.0f };
		m_currentAnim = AnimationDead;
		if (!m_animation.IsPlay()) {
			SetisDead();
			//���̂��폜
			g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		}

		break;
		//�v���C���[�Ƀq�b�g
	case State_Hit:
		m_timer += Timer::GetFrameDeltaTime();
		move = { 0.0f,0.0f,0.0f };
		if (m_timer >= 5.0f) {
			m_isDead = true;
			m_timer = 0.0f;
		}
		break;
	}

	return move;
}

void Red_Dragon::CollisionDetection(float length, const D3DXVECTOR3& toPlayer)
{
	if (length <= 1.5f) {
		D3DXVECTOR3 toPlayerXZ = { toPlayer.x,0.0f,toPlayer.z };
		float lengthXZ = D3DXVec3Length(&toPlayerXZ);

		D3DXVECTOR3 toPlayerY = { 0.0f,toPlayer.y,0.0f };
		float lengthY = D3DXVec3Length(&toPlayerY);

		//Y�����ɓ�������
		if (toPlayerY.y > 0.0f && lengthY <= 0.95f && lengthXZ <= 0.7f) {
			//�h���S�������S
			player->SetTreadOnEnemy(true);
			m_state = State_Dead;

			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Humituke.wav");
			SE->Play(false);
		}
		//XZ�����ɓ�������
		else if (lengthY <= 0.3f && lengthXZ <= 0.9f) {
			//�v���C���[�����S
			m_hitPlayer = true;
			player->SetHitEnemy(m_hitPlayer);
			m_state = State_Hit;
		}
	}
}

void Red_Dragon::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
