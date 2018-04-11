#pragma once

class Sprite {
public:
	//コンストラクタ
	Sprite();

	//デストラクタ
	~Sprite();

	//初期化
	void Initialize(char *filpath);

	//テクスチャ読み込み
	void LoadTexture(char *filePath);

	//描画
	void Render();

	//エフェクト読み込み
	LPD3DXEFFECT LoadEffect(char *filePath);

	//解放
	void Release();

	//頂点バッファ
	struct Vertex {
		float vertex[4];
		float uv[2];
	};

	//座標を設定
	//pos	座標
	void SetPosition(const D3DXVECTOR2& pos)
	{
		m_position = pos;
	}

	//座標を取得
	const D3DXVECTOR2& GetPosition()
	{
		return m_position;
	}

	//サイズを設定
	//scale		サイズ
	void SetSize(const D3DXVECTOR2& size)
	{
		m_size = size;
	}

	//不透明度を設定
	//alpha		不透明度。0.0で完全に透明
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//不透明度を取得
	float GetAlpha()
	{
		return m_alpha;
	}

	//UVを動かすフラグを設定
	void SetUVMove(bool uvMove)
	{
		m_uvMove = uvMove;
	}

	//カメラ空間に変換するフラグ
	void SetIsTrans(bool isTrans)
	{
		m_isTrans = isTrans;
	}
private:
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャ
	D3DXIMAGE_INFO m_imginfo;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	LPD3DXEFFECT m_pEffect;
	D3DXVECTOR2 m_position;
	D3DXVECTOR2 m_size;
	float m_alpha = 1.0f;
	bool m_uvMove = false;				//UVを動かすフラグ
	float uvPos = 0.0f;
	bool m_isTrans = false;
};
