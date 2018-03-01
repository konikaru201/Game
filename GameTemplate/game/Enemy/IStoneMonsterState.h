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

	//��������������
	virtual bool GetIsFind() const
	{
		return m_isFind;
	}

	//�����t���O�𗧂Ă�
	void SetIsFind(bool isFind)
	{
		m_isFind = isFind;
	}

protected:
	bool m_isFind = false;
	StoneMonster* m_stoneMonster = nullptr;
	StoneMonsterStateMachine* m_sms = nullptr;
};