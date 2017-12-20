/*!
 *@brief	�Q�[���e���v���[�g�B
 */
#include "stdafx.h"
#include "Scene/SceneManager.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/HID/Pad.h"
#include "Fade/Fade.h"
#include "myEngine/Graphics/RenderTarget.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "Scene/GameScene.h"
#include "Player/Player.h"
#include "myEngine/Graphics/Primitive.h"
#include "myEngine/Graphics/Bloom.h"
//#include "myEngine/Sound/SoundEngine.h"

GameObjectManager* goMgr = nullptr;
Pad* pad = nullptr;
SceneManager* sceneManager = nullptr;
Fade* g_fade = nullptr;
//CSoundEngine* soundEngine = nullptr;

CShadowMap g_shadowMap;	//�V���h�E�}�b�v�B
Bloom* bloom = nullptr;	//�u���[��

CRenderTarget* mainRenderTarget;	//���C�������_�����O�^�[�Q�b�g
CPrimitive* quadPrimitive;			//�l�p�`�̔|���v���~�e�B�u
LPD3DXEFFECT copyEffect;			//�R�s�[���s���V�F�[�_�[
LPD3DXEFFECT monochromeEffect;		//���m�N���t�B���^�[��������V�F�[�_�[

void InitMainRenderTarget();
void InitQuadPrimitive();
void LoadShaders();
void CopyMainRTToCurrentRT();
void DrawQuadPrimitive();

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	//�����_�����O�^�[�Q�b�g���쐬����
	InitMainRenderTarget();
	//�l�p�`�̔|���v���~�e�B�u���쐬
	InitQuadPrimitive();
	//�V�F�[�_�[�����[�h
	LoadShaders();

	g_shadowMap.Init();

	bloom = new Bloom;

	goMgr = new GameObjectManager;

	g_fade = new Fade;
	g_fade->Start();

	pad = goMgr->NewGameObject<Pad>();

	sceneManager = goMgr->NewGameObject<SceneManager>();
}
//-----------------------------------------------------------------------------
// Name: �`�揈���B��
//-----------------------------------------------------------------------------
VOID Render()
{
	if (g_player != nullptr) {
		D3DXVECTOR3 target = g_player->GetPosition();
		D3DXVECTOR3 viewPos = target;
		viewPos.y += 30.0f;
		g_shadowMap.SetLightViewPosition(viewPos);
		g_shadowMap.SetLightViewTarget(target);
	}
	else {
		g_shadowMap.SetLightViewPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
		g_shadowMap.SetLightViewTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//if (g_coin != nullptr) {
	//	D3DXVECTOR3 target = g_coin->GetPosition();
	//	D3DXVECTOR3 viewPos = target;
	//	viewPos.y += 10.0f;
	//	g_shadowMap.SetLightViewPosition(viewPos);
	//	g_shadowMap.SetLightViewTarget(target);
	//}
	//else {
	//	g_shadowMap.SetLightViewPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	//	g_shadowMap.SetLightViewTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}

	g_shadowMap.Update();

	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���o�b�t�@�̃o�b�N�A�b�v���Ƃ�
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);

	//�����_�����O�^�[�Q�b�g���t���[���o�b�t�@����ύX����
	g_pd3dDevice->SetRenderTarget(
		0,										//���Ԗڂ̃����_�����O�^�[�Q�b�g��ݒ肷�邩�̈����B����͂O
		mainRenderTarget->GetRenderTarget()		//�ύX���郌���_�����O�^�[�Q�b�g
	);
	//�f�v�X�X�e���V���o�b�t�@���ύX����
	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());
	// �����_�����O�^�[�Q�b�g���N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//�V���h�E�}�b�v�Ƀ����_�����O�B
	g_shadowMap.Draw();

	goMgr->Render();

	//�|�X�g�G�t�F�N�g
	bloom->Render();

	//�����_�����O�^�[�Q�b�g��߂�
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);

	//�Q�ƃJ�E���^���P���炷
	frameBufferRT->Release();
	frameBufferDS->Release();

	//�I�t�X�N���[�������_�����O�����G���t���[���o�b�t�@�ɓ\��t����
	CopyMainRTToCurrentRT();

	if (gameScene != nullptr) {
		gameScene->Render();
	}

	//�t�F�[�h�̃����_�����O
	g_fade->Render();

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

	
}
/*!-----------------------------------------------------------------------------
 *@brief	�X�V�����B
 -----------------------------------------------------------------------------*/
void Update()
{
	goMgr->Update();
	g_fade->Update();
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	delete goMgr;
	delete g_fade;
	delete g_effectManager;
}

//�I�u�W�F�N�g���f���[�g���鏈��
void Delete()
{
	goMgr->DeleteGameObject();
}

void InitMainRenderTarget()
{
	//���C�������_�����O�^�[�Q�b�g��������
	mainRenderTarget = new CRenderTarget;
	mainRenderTarget->Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0
	);
}

void InitQuadPrimitive()
{
	quadPrimitive = new CPrimitive;
	//���_�̍\����
	struct SVertex {
		float pos[4];		//���_���W
		float uv[2];		//UV���W
	};
	//���_�o�b�t�@
	SVertex vertexBuffer[] = {
		{
			-1.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f
		},
		{
			1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f
		},
		{
			-1.0f, -1.0f, 0.0f, 1.0f,
			0.0f, 1.0f
		},
		{
			1.0f, -1.0f, 0.0f, 1.0f,
			1.0f, 1.0f
		},
	};

	//���_���C�A�E�g�B���_�o�b�t�@�̍\�����ǂ̂悤�ɂȂ��Ă��邩��GPU�ɋ����邽�߂̂���
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//���_�X�g���[����0�Ԗڂ�0�o�C�g�ڂ���float�^��4���̃f�[�^�͍��W(D3DDECLUSAGE_POSITION)�ł��邱�Ƃ������Ă���B
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//���_�X�g���[����0�Ԗڂ�16�o�C�g�ڂ���float�^��2���̃f�[�^��UV���W(D3DDECLUSAGE_TEXCOORD)�ł��邱�Ƃ������Ă���B
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};
	//�C���f�b�N�X�o�b�t�@�B
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };
	quadPrimitive->Create(
		CPrimitive::eTriangleStrip,	//����̓v���~�e�B�u�̎�ނ̓g���C�A���O���X�g���b�v�B
		4,							//���_�̐��B�l�p�`�̔|���Ńg���C�A���O���X�g���b�v�Ȃ̂łS�B
		sizeof(SVertex),			//���_�X�g���C�h�B��̒��_�̑傫���B�P�ʂ̓o�C�g�B
		scShapeVertex_PT_Element,	//���_���C�A�E�g�B
		vertexBuffer,				//���_�o�b�t�@�B
		4,							//�C���f�b�N�X�̐��B
		D3DFMT_INDEX16,				//�C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g�B�����16bit�t�H�[�}�b�g���w�肷��B
									//�C���f�b�N�X�̐���65536�ȉ��̏ꍇ��16bit�ł������A����𒴂���ꍇ��D3DFMT_INDEX32���w�肷��B
		indexBuffer					//�C���f�b�N�X�o�b�t�@�B
	);
}

//�V�F�[�_�[�����[�h
void LoadShaders()
{
	LPD3DXBUFFER compileErrorBuffer = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/Copy.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALISATION,
#endif 
		NULL,
		&copyEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}

	//���m�N���t�B���^�[���s���V�F�[�_�[�����[�h
	hr = D3DXCreateEffectFromFile(
		g_pd3dDevice,
		"Assets/Shader/monochromeFilter.fx",
		NULL,
		NULL,
#ifdef _DEBUG
		D3DXSHADER_DEBUG,
#else
		D3DXSHADER_SKIPVALIDATION,
#endif
		NULL,
		&monochromeEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

//���C�������_�����O�^�[�Q�b�g�̓��e�����݂̃����_�����O�^�[�Q�b�g�ɃR�s�[
void CopyMainRTToCurrentRT()
{
	// Z�e�X�g�Ŏ��s���Ă�������獢��̂ŁAZ�e�X�g�͖����ɂ��Ă����B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// ���u�����h������Ȃ��B
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	LPD3DXEFFECT shader = copyEffect;			//�R�s�[���s���V�F�[�_�[���g���ꍇ�͂�����B
	//LPD3DXEFFECT shader = monochromeEffect;	//���m�N���t�B���^�[��������ꍇ�͂�������g�p����B
	//�V�F�[�_�[��ݒ�B
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//�V�[���e�N�X�`����ݒ肷��
	shader->SetTexture("g_tex",  mainRenderTarget->GetTexture());
	//�萔���W�X�^�ւ̕ύX���R�~�b�g����B
	shader->CommitChanges();

	DrawQuadPrimitive();
	shader->EndPass();
	shader->End();
	// �ύX���������_�����O�X�e�[�g�����ɖ߂��B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

//�|����`��
void DrawQuadPrimitive()
{
	// ���_�X�g���[��0�Ԃɔ|���̒��_�o�b�t�@��ݒ肷��B
	g_pd3dDevice->SetStreamSource(
		0,												//���_�X�g���[���̔ԍ��B
		quadPrimitive->GetVertexBuffer()->GetBody(),	//���_�o�b�t�@�B
		0,												//���_�o�b�t�@�̓ǂݍ��݂��J�n����I�t�Z�b�g�̃o�C�g���B
		quadPrimitive->GetVertexBuffer()->GetStride()	//���_����̃T�C�Y�B�P�ʂ̓o�C�g�B
	);
	// �C���f�b�N�X�o�b�t�@��ݒ�B
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// ���_��`��ݒ肷��B
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//�@�������������̂ŕ`��B
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//�v���~�e�B�u�̎�ނ��w�肷��B
		0,										//�x�[�X���_�C���f�b�N�X�B
		0,										//�ŏ��̒��_�C���f�b�N�X�B
		quadPrimitive->GetNumVertex(),			//���_�̐��B
		0,										//�J�n�C���f�b�N�X�B
		quadPrimitive->GetNumPolygon()			//�v���~�e�B�u�̐��B
	);
}