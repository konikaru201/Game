#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(){}
Sprite::~Sprite()
{
	Release();
}

void Sprite::Initialize(char *filePath)
{
	Release();
	//テクスチャを読み込み
	LoadTexture(filePath);
	
	SetPosition({ 0.0f,0.0f });

	m_pEffect = LoadEffect("Assets/Shader/sprite.fx");

	//頂点バッファを作成
	Vertex mVertex[4] = { { -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},
						  {  1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
						  {  1.0f,-1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
						  { -1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1.0f}
	};

	//インデックスバッファを作成
	WORD indexBuffer[6] = { 0,1,2, 0,2,3 };

	g_pd3dDevice->CreateVertexBuffer(
		sizeof(Vertex) * 4,
		0,
		D3DFVF_XYZ | D3DFVF_DIFFUSE,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		NULL
	);
	
	void* pVertex;
	m_pVertexBuffer->Lock(0, 0, &pVertex, 0);
	memcpy(pVertex, mVertex, 4 * sizeof(Vertex));
	m_pVertexBuffer->Unlock();

	g_pd3dDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_pIndexBuffer,
		NULL
	);

	void* pIndex;
	m_pIndexBuffer->Lock(0, 0, &pIndex, 0);
	memcpy(pIndex, indexBuffer, sizeof(WORD) * 6);
	m_pIndexBuffer->Unlock();

	m_size.x = m_imginfo.Width;
	m_size.y = m_imginfo.Height;
}

void Sprite::LoadTexture(char *filePath) 
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		filePath,
		0,
		0,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&m_imginfo,
		NULL,
		&m_pTexture
	);
}

void Sprite::Render()
{
	float windowWidth = FRAME_BUFFER_WIDTH;
	float windowHeight = FRAME_BUFFER_HEIGHT;
	D3DXVECTOR3 position;
	position.x = m_position.x / windowWidth;
	position.y = m_position.y / windowHeight;
	position.z = 0.0f;
	D3DXVECTOR3 size;
	size.x = m_size.x / windowWidth;
	size.y = m_size.y / windowHeight;
	size.z = 0.0f;

	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, size.x, size.y, size.z);
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &scale);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &trans);

	//uvPos += 0.005f;
	m_pEffect->SetTechnique("Sprite");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);
	m_pEffect->SetTexture("g_texture", m_pTexture);
	m_pEffect->SetMatrix("g_world", &worldMatrix);
	m_pEffect->SetFloat("g_alpha", m_alpha);
	m_pEffect->SetFloat("g_uvPos", uvPos);
	m_pEffect->SetBool("g_uvMove", m_uvMove);
	m_pEffect->CommitChanges();

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pd3dDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(Vertex));
	g_pd3dDevice->SetIndices(m_pIndexBuffer);
	g_pd3dDevice->SetFVF(D3DFVF_XYZW | D3DFVF_TEX1);
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	m_pEffect->EndPass();
	m_pEffect->End();
}

LPD3DXEFFECT Sprite::LoadEffect(char *filePath)
{
	LPD3DXEFFECT effect = nullptr;

	LPD3DXBUFFER compileErrorBuffer = nullptr;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		filePath,
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&effect,
		&compileErrorBuffer);
	if (FAILED(hr))
	{
		MessageBox(nullptr, reinterpret_cast<char*>(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		//読み込み失敗
		std::abort();
	}

	return effect;
}

void Sprite::Release()
{
	if (m_pTexture != nullptr) {
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
	if (m_pIndexBuffer != nullptr)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = nullptr;
	}
	if (m_pVertexBuffer != nullptr)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}
}