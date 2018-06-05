/*!
*@brief	ゲームカメラクラス
*/
#pragma once

#include "myEngine/Graphics/Camera.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Physics/CameraCollisionSolver.h"

class GameCamera : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	GameCamera();
	/*!
	*@brief	デストラクタ
	*/
	~GameCamera();
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	移動
	*/
	void Move();
	/*!
	*@brief	リセット
	*/
	void Reset();
	/*!
	*@brief	注視点を設定
	* @param[in]	target		注視点
	*/
	void SetTarget(const D3DXVECTOR3& target)
	{
		m_camera.SetLookatPt(target);
	}
	/*!
	*@brief	視点を設定
	* @param[in]	position	視点
	*/
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_camera.SetEyePt(position);
	}
	/*!
	*@brief	遠平面を設定
	* @param[in]	_far		遠平面
	*/
	void SetFar(const float& _far)
	{
		m_camera.SetFar(_far);
	}
	/*!
	*@brief	アスペクト比を取得
	* @return アスペクト比
	*/
	float GetAspect()
	{
		return m_camera.GetAspect();
	}
	/*!
	*@brief	画角を取得
	* @return 画角
	*/
	float GetAngle()
	{
		return m_camera.GetAngle();
	}
	/*!
	*@brief	注視点を取得
	* @return 注視点
	*/
	const D3DXVECTOR3& GetTarget()
	{
		return m_camera.GetLookatPt();
	}
	/*!
	*@brief	視点を取得
	* @return 視点
	*/
	const D3DXVECTOR3& GetPosition()
	{
		return m_camera.GetEyePt();
	}
	/*!
	*@brief	前方向を取得
	* @return 前方向
	*/
	const D3DXVECTOR3& GetForward()
	{
		return m_camera.GetForwardVec();
	}
	/*!
	*@brief	右方向を取得
	* @return 右方向
	*/
	const D3DXVECTOR3& GetRight()
	{
		return m_camera.GetRightVec();
	}
	/*!
	*@brief	ビュー行列を取得
	* @return ビュー行列
	*/
	const D3DXMATRIX& GetViewMatrix()
	{
		return m_camera.GetViewMatrix();
	}
	/*!
	*@brief	プロジェクション行列を取得
	* @return プロジェクション行列
	*/
	const D3DXMATRIX& GetProjectionMatrix()
	{
		return m_camera.GetProjectionMatrix();
	}
	/*!
	*@brief	カメラのリセットフラグを取得
	*/
	bool GetCameraReset()
	{
		return m_cameraReset;
	}
private:
	Camera					m_camera;					//カメラインスタンス
	CameraCollisionSolver	m_cameraCollisionSolver;	//カメラコリジョンインスタンス
	D3DXVECTOR3				m_toCameraPos;				//注視点から視点へのベクトル
	D3DXVECTOR3				m_currentEyePos;			//プレイヤー死亡時のカメラの座標
	int						m_rotationFrameCount = 0;	//回転フレームカウント
	bool					m_stopRotation = false;		//回転ストップフラグ
	bool					m_cameraReset = false;		//カメラリセットフラグ
};

extern GameCamera* gameCamera;