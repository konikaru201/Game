#pragma once

class GameObject 
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	GameObject();
	/*!
	*@brief	デストラクタ
	*/
	virtual ~GameObject();
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	virtual bool Start() { return true; }
	/*!
	*@brief	更新
	*/
	virtual void Update() = 0;
	virtual void PreUpdate() {}
	virtual void PostUpdate() {}
	/*!
	*@brief	描画
	*/
	virtual void Render(){}
	virtual void PreRender(){}
	virtual void PostRender(){}
	/*!
	* @brief	影を描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	* @param[in]	isDrawShadowMap	シャドウマップを描くフラグ
	* @param[in]	isRecieveShadow	シャドウレシーバーかどうか
	*/
	virtual void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow){}
	/*!
	*@brief	深度値を描画
	*/
	virtual void RenderDepthValue() {}
	/*!
	*@brief	Start関数がすでに呼ばれたか
	*/
	virtual bool IsStart() const
	{
		return m_isStart;
	}
	/*!
	*@brief	Start関数が呼ばれたらフラグを設定
	*/
	void SetStart()
	{
		m_isStart = true;
	}
	/*!
	*@brief	死亡フラグを返却
	*/
	bool GetisDead() const
	{
		return m_isDead;
	}
	/*!
	*@brief	死亡フラグを立てる
	*/
	void SetisDead()
	{
		m_isDead = true;
	}
	/*!
	*@brief	影の描画フラグを返却
	*/
	bool GetShadowToRender() const
	{
		return m_renderToShadow;
	}
	/*!
	*@brief	影の描画フラグを立てる
	*/
	void SetRenderToShadow()
	{
		m_renderToShadow = true;
	}
	/*!
	*@brief	ゲームオブジェクトに登録されているか
	*/
	bool GetIsRegist() const
	{
		return m_isRegist;
	}
	/*!
	*@brief	ゲームオブジェクトに登録するフラグを設定
	*/
	void SetIsRegist(bool isRegist)
	{
		m_isRegist = isRegist;
	}
	/*!
	*@brief	ステートを変更するか
	*/
	bool GetIsChangeState() const
	{
		return m_isChangeState;
	}
	/*!
	*@brief	ステート変更フラグを設定
	*/
	void SetIsChangeState(bool isChangeState)
	{
		m_isChangeState = isChangeState;
	}

protected:
	bool m_isStart = false;			//Start関数のフラグ
	bool m_isDead = false;			//死亡フラグ
	bool m_renderToShadow = false;	//影の描画フラグ
	bool m_isRegist = false;		//ゲームオブジェクトに登録されているか
	bool m_isChangeState = false;	//ステートを変更するか
};