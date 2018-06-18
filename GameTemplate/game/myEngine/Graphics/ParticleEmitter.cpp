//パーティクル生成機

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
	if (timer >= param.intervalTime && m_particleNum < param.particleNum) {
		//パーティクル生成
		CParticle* p = goMgr->NewGameObject<CParticle>();
		p->Init(param);
		m_particleList.push_back(p);
		timer = 0.0f;
		m_particleNum++;
	}

	if (m_particleNum >= param.particleNum) {
		for (auto& particle : m_particleList) {
			if (particle->GetState() == particle->State_Dead) {
				particle->Init(param);
			}
		}
	}

	timer += 1.0f / 60.0f;
}