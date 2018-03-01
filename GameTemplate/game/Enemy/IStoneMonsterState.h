#pragma once

#include "myEngine/GameObject/GameObject.h"

class StoneMonster;
class StoneMonsterStateMachine;

class IStoneMonsterState : public GameObject
{
public:
	IStoneMonsterState(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		m_stoneMonster(stoneMonster),
		m_sms(sms)
	{
	}

	~IStoneMonsterState() {};

	virtual void Update() = 0;

	//発見したか判定
	virtual bool GetIsFind() const
	{
		return m_isFind;
	}

	//発見フラグを立てる
	void SetIsFind(bool isFind)
	{
		m_isFind = isFind;
	}

protected:
	bool m_isFind = false;
	StoneMonster* m_stoneMonster = nullptr;
	StoneMonsterStateMachine* m_sms = nullptr;
};