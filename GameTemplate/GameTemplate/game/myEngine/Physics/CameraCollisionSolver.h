#pragma once

#include "SphereCollider.h"

class CameraCollisionSolver {
public:
	//コンストラクタ
	CameraCollisionSolver();

	//デストラクタ
	~CameraCollisionSolver();

	//初期化
	//radius	カメラのバウンディングスフィアの半径
	void Init(float radius);

	//コリジョン解決の実行
	//result	コリジョン解決を行った結果のカメラの視点の座標が格納される
	//posiiton	カメラの視点
	//target	カメラの注視点
	//return	コリジョン解決を行った場合はtrueが返ってくる
	bool Execute(D3DXVECTOR3& result, const D3DXVECTOR3& position, const D3DXVECTOR3& target);
private:
	SphereCollider	m_collider;		 //コライダー
	float			m_radius = 0.0f; //半径
};