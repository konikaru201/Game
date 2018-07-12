/*!
*@brief	コインUIクラス
*/
#pragma once

#include "Number.h"

class DisplayCoin : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	DisplayCoin();
	/*!
	*@brief	デストラクタ
	*/
	~DisplayCoin();
	/*!
	*@brief	初期化
	*@param[in] position	座標
	*/
	void Init(D3DXVECTOR2 position);
	/*!
	*@brief	更新する前に一度だけ呼ばれる関数
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
	/*!
	*@brief	コインの枚数をカウント
	*/
	void CoinCount()
	{
		m_coinNum++;
	}
private:
	std::unique_ptr<Number>		m_num[2];					//数字
	D3DXVECTOR2					m_position = { 0.0f,0.0f }; //座標
	int							m_coinNum = 0;				//コインの枚数
};