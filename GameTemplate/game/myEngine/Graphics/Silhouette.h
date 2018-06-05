/*!
*@brief	シルエットクラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"

class Silhouette : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Silhouette();
	/*!
	*@brief	デストラクタ
	*/
	~Silhouette();
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render();
};