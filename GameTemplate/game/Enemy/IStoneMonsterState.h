/*!
*@brief	ストーンモンスターのステートのインターフェース
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"

class StoneMonster;
class StoneMonsterStateMachine;

class IStoneMonsterState : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	stoneMonster	ストーンモンスター
	* @param[in]	sms				ステートマシン
	*/
	IStoneMonsterState(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		m_stoneMonster(stoneMonster),
		m_sms(sms)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~IStoneMonsterState() {};
	/*!
	*@brief	更新
	*/
	virtual void Update() = 0;
	/*!
	*@brief	発見したか判定
	*/
	virtual bool GetIsFind() const
	{
		return m_isFind;
	}
	/*!
	*@brief	発見フラグを立てる
	*/
	void SetIsFind(bool isFind)
	{
		m_isFind = isFind;
	}
protected:
	bool m_isFind = false;						//発見フラグ
	StoneMonster* m_stoneMonster = nullptr;		//ストーンモンスター
	StoneMonsterStateMachine* m_sms = nullptr;	//ステートマシン
};