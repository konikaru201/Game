/*!
*@brief	数字クラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"

class Number{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Number();
	/*!
	*@brief	デストラクタ
	*/
	~Number();
	/*!
	*@brief	初期化
	* @param[in]	numPos		座標
	* @param[in]	numSize		サイズ
	*/
	void Init(D3DXVECTOR2 numPos, D3DXVECTOR2 numSize);
	/*!
	*@brief	数値を設定
	* @param[in]	n		数字
	*/
	void NumSet(int n);
	/*!
	*@brief	描画
	*/
	void Render();
private:
	std::unique_ptr<Sprite> m_number[10];	//0～9の数字のスプライト
	int						m_num = 0;		//数字を保持する変数
};