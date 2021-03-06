#pragma once

/*!
 *@brief	カメラクラス。
 */
class Camera {
private:
	D3DXMATRIX				viewMatrix;			//!<ビュー行列。カメラ行列とも言う。
	D3DXMATRIX				projectionMatrix;	//!<プロジェクション行列。ビュー空間から射影空間に変換する行列。
	D3DXVECTOR3				vEyePt;				//!<カメラクラスを作るためのヒント。カメラの視点。この辺りはメンバ変数に変更する。
	D3DXVECTOR3				vLookatPt;			//!<カメラクラスを作るためのヒント。カメラの注視点。どこを見ているかという情報。この辺りはメンバ変数に変更する。
	D3DXVECTOR3				vUpVec;				//!<カメラクラスを作るためのヒント。カメラの上方向。基本的にY方向でかまわない。基本的には・・・。この辺りはメンバ変数に変更する。
	D3DXVECTOR3				vForward;			//!<前方向。
	D3DXVECTOR3				vRight;				//!<右方向。
	float					Far;				//!<遠平面。
	float					Near;				//!<近平面。
	float					aspect;				//!<アスペクト比
	float					angle;				//!<画角
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	Camera();
	/*!
	 *@brief	デストラクタ
	 */
	~Camera();
	/*!
	 *@brief	アスペクト比を設定。
	 */
	void SetAspect(float _aspect);
	/*!
	 *@brief	アスペクト比を取得。
	 */
	float GetAspect() const;
	/*!
	*@brief		画角を設定。
	*/
	void SetAngle(float _angle);
	/*!
	*@brief		画角を取得。
	*/
	float GetAngle() const;
	/*!
	 *@brief	ファーを設定。
	 */
	void SetFar(float _far);
	/*!
	 *@brief	ニアを取得。
	 */
	float GetNear() const;
	/*!
	 *@brief	ファーを取得。
	 */
	float GetFar() const;
	/*!
	 *@brief	ニアを設定。
	 */
	void SetNear(float _near);
	/*!
	 *@brief	視点を設定。
	 */
	void SetEyePt(const D3DXVECTOR3& pt);
	/*!
	 *@brief	視点を取得。
	 */
	const D3DXVECTOR3& GetEyePt() const;
	/*!
	 *@brief	注視点を設定。
	 */
	void SetLookatPt(const D3DXVECTOR3& pt);
	/*!
	 *@brief	注視点の取得。
	 */
	const D3DXVECTOR3& GetLookatPt() const;
	/*!
	*@brief		前方向の設定。
	*/
	void SetForwardVec(const D3DXVECTOR3& forward);
	/*!
	*@brief		前方向の取得。
	*/
	const D3DXVECTOR3& GetForwardVec() const;
	/*!
	*@brief		右方向の設定。
	*/
	void SetRightVec(const D3DXVECTOR3& right);
	/*!
	*@brief		右方向の取得。
	*/
	const D3DXVECTOR3& GetRightVec() const;
	/*!
	 *@brief	上方向の設定。
	 */
	void SetUpVec(const D3DXVECTOR3& up);
	/*!
	 *@brief	上方向の取得。
	 */
	const D3DXVECTOR3& GetUpVec() const;
	/*!
	 *@brief	ビュー行列の設定。
	 */
	void SetViewMatrix(const D3DXMATRIX& mView);
	/*!
	 *@brief	ビュー行列の取得。
	 */
	const D3DXMATRIX& GetViewMatrix() const;
	/*!
	 *@brief	プロジェクション行列の設定。
	 */
	void SetProjectionMatrix(const D3DXMATRIX& mProj);
	/*!
	 *@brief	プロジェクション行列の取得。
	 */
	const D3DXMATRIX& GetProjectionMatrix() const;
	/*!
	 *@brief	カメラの更新処理。
	 */
	void Update();
	/*!
	 *@brief	カメラの初期化。
	 */
	void Init();
};