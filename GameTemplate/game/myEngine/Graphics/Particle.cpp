//パーティクル

#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "../../Scene/GameScene.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

//座標とUV座標
struct SShapeVertex_PT {
	float		pos[4];
	float		uv[2];
};

static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
	{ 0, 0,  D3DDECLTYPE_FLOAT4 , D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0, 16, D3DDECLTYPE_FLOAT2 , D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
	D3DDECL_END()
};

CParticle::CParticle() :
	texture(nullptr),
	shaderEffect(nullptr)
{
}

CParticle::~CParticle()
{
	if (shaderEffect != nullptr) {
		shaderEffect->Release();
	}
	if (texture != nullptr) {
		texture->Release();
	}
}

void CParticle::Init(const SParticleEmitParameter& param)
{
	float halfW = param.w * 0.5f;
	float halfH = param.h * 0.5f;

	D3DXVECTOR4 uv (0.0f, 0.0f, 1.0f, 1.0f);
	moveSpeed = param.initSpeed;

	position = param.position;
	alpha = param.alpha;
	float add = ((rand() % 255) - 128) / 128.0f;
	moveSpeed.x += add * 0.3f;
	moveSpeed.y += add * 0.3f;
	moveSpeed.z += add * 0.3f;

	SShapeVertex_PT vb[] = {
		{
			-halfW, halfH, 0.0f, 1.0f,
			uv.x, uv.y
		},
		{
			halfW, halfH, 0.0f, 1.0f,
			uv.z, uv.y
		},
		{
			-halfW, -halfH, 0.0f, 1.0f,
			uv.x, uv.w
		},
		{
			halfW, -halfH, 0.0f, 1.0f,
			uv.z, uv.w
		},
	};

	short index[]{
		0,1,2,3
	};

	primitive.Create(
		CPrimitive::eTriangleStrip,
		4,
		sizeof(SShapeVertex_PT),
		scShapeVertex_PT_Element,
		vb,
		4,
		D3DFMT_INDEX16,
		index
	);

	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, param.texturePath, &texture);

	LPD3DXBUFFER compileErrorBuffer = NULL;
	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/ColorTexPrim.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&shaderEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

void CParticle::Update()
{
	float deltaTime = 1.0f / 60.0f;
	D3DXVECTOR3 add = moveSpeed * deltaTime;
	position += add;

	timer += deltaTime;
	switch (state) {
	case State_Run:
		if (timer >= life) {
			state = State_FadeOut;
			timer = 0.0f;
		}
		break;
	case State_FadeOut:
		{
			float t = timer / fadeTime;
			timer += deltaTime;
			alpha = initAlpha + (-initAlpha) * t;
			if (alpha <= 0.0f) {
				alpha = 0.0f;
				state = State_Dead;
			}
		}
		break;
	case State_Dead:
		this->SetisDead();
		break;
	}
}

void CParticle::Render()
{
	D3DXMATRIX viewMatrix = gameCamera->GetViewMatrix();
	D3DXMATRIX projMatrix = gameCamera->GetProjectionMatrix();

	D3DXMATRIX m, mTrans;
	D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);

	//カメラの回転行列を求める
	D3DXMATRIX viewMatrixInv;
	D3DXMatrixInverse(&viewMatrixInv, NULL, &viewMatrix);
	viewMatrixInv.m[3][0] = 0.0f;
	viewMatrixInv.m[3][1] = 0.0f;
	viewMatrixInv.m[3][2] = 0.0f;
	viewMatrixInv.m[3][3] = 1.0f;

	//回転行列をワールド行列に乗算する
	mTrans = viewMatrixInv * mTrans;
	m = mTrans * viewMatrix * projMatrix;

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	shaderEffect->SetTechnique("ColorTexPrimAdd");

	shaderEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shaderEffect->BeginPass(0);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	shaderEffect->SetValue("g_mWVP", &m, sizeof(m));
	shaderEffect->SetTexture("g_texture", texture);
	shaderEffect->SetFloat("g_alpha", alpha);
	shaderEffect->CommitChanges();

	g_pd3dDevice->SetStreamSource(0, primitive.GetVertexBuffer()->GetBody(), 0, primitive.GetVertexBuffer()->GetStride());
	g_pd3dDevice->SetIndices(primitive.GetIndexBuffer()->GetBody());
	g_pd3dDevice->SetVertexDeclaration(primitive.GetVertexDecl());
	g_pd3dDevice->DrawIndexedPrimitive(primitive.GetD3DPrimitiveType(), 0, 0, primitive.GetNumVertex(), 0, primitive.GetNumPolygon());
	shaderEffect->EndPass();
	shaderEffect->End();
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}