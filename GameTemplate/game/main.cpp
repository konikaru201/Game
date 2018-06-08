/*!
 *@brief	ゲームテンプレート。
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
#include "Number/RemainNumber.h"
#include "Fade/WipeEffect.h"

GameObjectManager* goMgr = nullptr;		//ゲームオブジェクト
Pad* pad = nullptr;						//パッド
SceneManager* sceneManager = nullptr;	//シーンマネージャー
Fade* g_fade = nullptr;					//フェード
WipeEffect* wipeEffect;					//ワイプエフェクト
CShadowMap g_shadowMap;					//シャドウマップ。
Bloom* bloom = nullptr;					//ブルーム

DisplayCoin* CoinUI = nullptr;			//コイン枚数のスプライト
Sprite* Coin = nullptr;					//コインの絵のスプライト
Sprite* m_aBotton = nullptr;			//Aボタン表示のスプライト
Sprite* remain = nullptr;				//残機のスプライト
RemainNumber* remainNumber = nullptr;	//残機数のスプライト
Sprite* kakeru = nullptr;				//×記号のスプライト
Sprite* kakeru2 = nullptr;

CRenderTarget* mainRenderTarget;		//メインレンダリングターゲット
CPrimitive* quadPrimitive;				//四角形の板ポリプリミティブ
LPD3DXEFFECT copyEffect;				//コピーを行うシェーダー
LPD3DXEFFECT monochromeEffect;			//モノクロフィルターをかけるシェーダー

void InitMainRenderTarget();
void InitQuadPrimitive();
void LoadShaders();
void CopyMainRTToCurrentRT();
void DrawQuadPrimitive();

namespace {
	//コインのスプライトのサイズと座標
	const D3DXVECTOR2 coinSize = { 128.0f,72.0f };
	const D3DXVECTOR2 coinPos = { 920.0f, 600.0f };
	//Aボタン表示のサイズ
	const D3DXVECTOR2 bottonSize = { 320.0f,180.0f };
	//残機のスプライトのサイズと座標
	const D3DXVECTOR2 remainSize = { 320.0f,240.0f };
	const D3DXVECTOR2 remainPos = { 900.0f,400.0f };
	//×記号のスプライトのサイズと座標
	const D3DXVECTOR2 kakeruSize = { 320.0f,160.0f };
	const D3DXVECTOR2 kakeruPos = { 1030.0f,600.0f };
	const D3DXVECTOR2 kakeru2Pos = { 1030.0f,400.0f };
}

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//レンダリングターゲットを作成する
	InitMainRenderTarget();
	//四角形の板ポリプリミティブを作成
	InitQuadPrimitive();
	//シェーダーをロード
	LoadShaders();

	//シャドウマップを初期化
	g_shadowMap.Init();

	//ブルーム生成
	bloom = new Bloom;

	//物理ワールドを初期化
	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();

	//フェードを初期化
	g_fade = new Fade;
	g_fade->Start();

	//ワイプエフェクトを初期化
	wipeEffect = new WipeEffect;
	wipeEffect->Start();

	//ゲームオブジェクト生成
	goMgr = new GameObjectManager;

	//ゲームパッド生成
	pad = goMgr->NewGameObject<Pad>();

	//シーンマネージャー生成
	sceneManager = goMgr->NewGameObject<SceneManager>();

	//スプライトの初期化
	//コインの絵
	Coin = new Sprite();
	Coin->Initialize("Assets/sprite/Coin2.png");
	Coin->SetPosition(coinPos);
	Coin->SetSize(coinSize);
	//コインの枚数
	CoinUI = new DisplayCoin();
	CoinUI->Init(kakeruPos);
	CoinUI->Start();
	//Aボタン
	m_aBotton = new Sprite;
	m_aBotton->Initialize("Assets/sprite/ABotton.png");
	//残機
	remain = new Sprite;
	remain->Initialize("Assets/sprite/unityChan.png");
	remain->SetPosition(remainPos);
	remain->SetSize(remainSize);
	//残機数
	remainNumber = new RemainNumber;
	remainNumber->Init(kakeru2Pos);
	remainNumber->Start();
	//×記号
	kakeru = new Sprite;
	kakeru->Initialize("Assets/sprite/×.png");
	kakeru->SetPosition(kakeruPos);
	kakeru->SetSize(kakeruSize);
	kakeru2 = new Sprite;
	kakeru2->Initialize("Assets/sprite/×.png");
	kakeru2->SetPosition(kakeru2Pos);
	kakeru2->SetSize(kakeruSize);
}
//-----------------------------------------------------------------------------
// Name: 描画処理。％
//-----------------------------------------------------------------------------
VOID Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL,  D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	//レンダリングターゲットとデプスステンシルバッファのバックアップをとる
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);

	//レンダリングターゲットをフレームバッファから変更する
	g_pd3dDevice->SetRenderTarget(
		0,										//何番目のレンダリングターゲットを設定するかの引数。今回は０
		mainRenderTarget->GetRenderTarget()		//変更するレンダリングターゲット
	);
	//デプスステンシルバッファも変更する
	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());
	// レンダリングターゲットをクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//シャドウマップにレンダリング
	g_shadowMap.Draw();

	//ゲームオブジェクトをレンダリング
	goMgr->Render();

	//ポストエフェクト
	bloom->Render();

	//レンダリングターゲットを戻す
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);

	//参照カウンタを１減らす
	frameBufferRT->Release();
	frameBufferDS->Release();

	//オフスクリーンレンダリングした絵をフレームバッファに貼り付ける
	CopyMainRTToCurrentRT();

	if (sceneManager->GetScene() == sceneManager->stateStageSelect
		|| sceneManager->GetScene() == sceneManager->stateGame)
	{
		//アルファブレンディングを有効にする。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//コインの絵と枚数を描画
		Coin->Render();
		CoinUI->Render();
		//残機の描画
		remain->Render();
		remainNumber->Render();
		//×記号の描画
		kakeru->Render();
		kakeru2->Render();
		//アルファブレンディングを無効にする。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	if (sceneManager->GetstageSelectScene() != nullptr
		&& sceneManager->GetstageSelectScene()->GetBottonRender())
	{
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//Aボタン表示
		m_aBotton->SetSize(bottonSize);
		m_aBotton->SetIsTrans(true);
		m_aBotton->Render();

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	//ワイプエフェクトの描画
	wipeEffect->Render();

	//フェードの描画
	g_fade->Render();

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	goMgr->Update();
	CoinUI->Update();
	remainNumber->Update();
	wipeEffect->Update();
	g_fade->Update();

	if (gameCamera != nullptr) {
		g_shadowMap.Update();
	}
	g_soundEngine->Update();
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	delete goMgr;
	delete g_fade;
	delete wipeEffect;
	delete g_effectManager;
	delete g_physicsWorld;
	delete Coin;
	delete CoinUI;
	delete m_aBotton;
	delete remain;
	delete remainNumber;
	delete kakeru;
	delete kakeru2;
}

//オブジェクトをデリートする処理
void Delete()
{
	goMgr->DeleteGameObject();
}

void InitMainRenderTarget()
{
	//メインレンダリングターゲットを初期化
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
	//頂点の構造体
	struct SVertex {
		float pos[4];		//頂点座標
		float uv[2];		//UV座標
	};
	//頂点バッファ
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

	//頂点レイアウト。頂点バッファの構造がどのようになっているかをGPUに教えるためのもの
	static const D3DVERTEXELEMENT9 scShapeVertex_PT_Element[] = {
		//頂点ストリームの0番目の0バイト目からfloat型の4つ分のデータは座標(D3DDECLUSAGE_POSITION)であることを示している。
		{ 0, 0 ,   D3DDECLTYPE_FLOAT4		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION	, 0 },
		//頂点ストリームの0番目の16バイト目からfloat型の2つ分のデータはUV座標(D3DDECLUSAGE_TEXCOORD)であることを示している。
		{ 0, 16 ,  D3DDECLTYPE_FLOAT2		, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD	, 0 },
		D3DDECL_END()
	};

	//インデックスバッファ。
	unsigned short indexBuffer[] = { 0, 1, 2, 3 };

	quadPrimitive->Create(
		CPrimitive::eTriangleStrip,	//今回はプリミティブの種類はトライアングルストリップ。
		4,							//頂点の数。四角形の板ポリでトライアングルストリップなので４。
		sizeof(SVertex),			//頂点ストライド。一つの頂点の大きさ。単位はバイト。
		scShapeVertex_PT_Element,	//頂点レイアウト。
		vertexBuffer,				//頂点バッファ。
		4,							//インデックスの数。
		D3DFMT_INDEX16,				//インデックスバッファのフォーマット。今回は16bitフォーマットを指定する。
									//インデックスの数が65536以下の場合は16bitでいいが、それを超える場合はD3DFMT_INDEX32を指定する。
		indexBuffer					//インデックスバッファ。
	);
}

//シェーダーをロード
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
		D3DXSHADER_SKIPVALIDATION,
#endif 
		NULL,
		&copyEffect,
		&compileErrorBuffer
	);
	if (FAILED(hr)) {
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}

	//モノクロフィルターを行うシェーダーをロード
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

//メインレンダリングターゲットの内容を現在のレンダリングターゲットにコピー
void CopyMainRTToCurrentRT()
{
	// Zテストで失敗してもらったら困るので、Zテストは無効にしておく。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// αブレンドもいらない。
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	LPD3DXEFFECT shader = copyEffect;			//コピーを行うシェーダーを使う場合はこちら。
	//LPD3DXEFFECT shader = monochromeEffect;	//モノクロフィルターをかける場合はこちらを使用する。
	//シェーダーを設定。
	shader->SetTechnique("Default");
	shader->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	shader->BeginPass(0);
	//シーンテクスチャを設定する
	shader->SetTexture("g_tex",  mainRenderTarget->GetTexture());
	//定数レジスタへの変更をコミットする。
	shader->CommitChanges();

	DrawQuadPrimitive();
	shader->EndPass();
	shader->End();
	// 変更したレンダリングステートを元に戻す。
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

//板ポリを描画
void DrawQuadPrimitive()
{
	// 頂点ストリーム0番に板ポリの頂点バッファを設定する。
	g_pd3dDevice->SetStreamSource(
		0,												//頂点ストリームの番号。
		quadPrimitive->GetVertexBuffer()->GetBody(),	//頂点バッファ。
		0,												//頂点バッファの読み込みを開始するオフセットのバイト数。
		quadPrimitive->GetVertexBuffer()->GetStride()	//頂点一つ分のサイズ。単位はバイト。
	);
	// インデックスバッファを設定。
	g_pd3dDevice->SetIndices(quadPrimitive->GetIndexBuffer()->GetBody());
	// 頂点定義を設定する。
	g_pd3dDevice->SetVertexDeclaration(quadPrimitive->GetVertexDecl());
	//　準備が整ったので描画。
	g_pd3dDevice->DrawIndexedPrimitive(
		quadPrimitive->GetD3DPrimitiveType(),	//プリミティブの種類を指定する。
		0,										//ベース頂点インデックス。
		0,										//最小の頂点インデックス。
		quadPrimitive->GetNumVertex(),			//頂点の数。
		0,										//開始インデックス。
		quadPrimitive->GetNumPolygon()			//プリミティブの数。
	);
}