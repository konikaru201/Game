#pragma once

class GameObject 
{
public:
	//コンストラクタ
	GameObject();

	//デストラクタ
	virtual ~GameObject();

	//初期化
	virtual bool Start() { return true; }

	//更新
	virtual void Update() = 0;
	virtual void PreUpdate() {}
	virtual void PostUpdate() {}
	//描画
	virtual void Render(){}

	//影の描画
	virtual void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow){}

	//Start関数がすでに呼ばれたか
	virtual bool IsStart()
	{
		return m_isStart;
	}

	//Start関数が呼ばれたらフラグを設定
	void SetStart()
	{
		m_isStart = true;
	}

	//死亡フラグを返却
	bool GetisDead()
	{
		return m_isDead;
	}

	//死亡フラグを立てる
	void SetisDead()
	{
		m_isDead = true;
	}

	//影の描画フラグを返却
	bool GetShadowToRender()
	{
		return m_renderToShadow;
	}

	//影の描画フラグを立てる
	void SetRenderToShadow()
	{
		m_renderToShadow = true;
	}

protected:
	bool m_isStart = false;			//Start関数のフラグ
	bool m_isDead = false;			//死亡フラグ
	bool m_renderToShadow = false;	//影の描画フラグ
};