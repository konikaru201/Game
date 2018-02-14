//�p�[�e�B�N�������@

#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

CParticleEmitter::CParticleEmitter()
{

}

CParticleEmitter::~CParticleEmitter()
{
}

void CParticleEmitter::Init(const SParticleEmitParameter& param)
{
	this->param = param;
	timer = 0.0f;
}

void CParticleEmitter::Update()
{
	if (timer >= param.intervalTime) {
		//�p�[�e�B�N������
		CParticle* p = goMgr->NewGameObject<CParticle>();
		p->Init(param);
		timer = 0.0f;
	}
	timer += 1.0f / 60.0f;
}