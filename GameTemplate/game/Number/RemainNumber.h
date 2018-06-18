/*!
*@brief	残機クラス
*/
#pragma once

#include "Number.h"

class RemainNumber : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	RemainNumber();
	/*!
	*@brief	デストラクタ
	*/
	~RemainNumber();
	/*!
	*@brief	初期化
	* @param[in]	position		座標
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
	*@brief	削除
	*/
	void DeleteNum();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	*@brief	描画
	*@param[in]		count	残機を増やす数
	*/
	void RemainCount(int count)
	{
		m_remainNum += count;
	}
	/*!
	*@brief	残機数を獲得
	*@return	残機数
	*/
	int GetRemainNum()
	{
		return m_remainNum;
	}
private:
	Number*		m_num[3];						//数字
	D3DXVECTOR2 m_position = { 0.0f,0.0f }; //座標
	int			m_remainNum = 3;			//残機数
};