/*!
*@brief	�X�g�[�������X�^�[�̃X�e�[�g�̃C���^�[�t�F�[�X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"

class StoneMonster;
class StoneMonsterStateMachine;

class IStoneMonsterState : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	stoneMonster	�X�g�[�������X�^�[
	* @param[in]	sms				�X�e�[�g�}�V��
	*/
	IStoneMonsterState(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		m_stoneMonster(stoneMonster),
		m_sms(sms)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~IStoneMonsterState() {};
	/*!
	*@brief	�X�V
	*/
	virtual void Update() = 0;
	/*!
	*@brief	��������������
	*/
	virtual bool GetIsFind() const
	{
		return m_isFind;
	}
	/*!
	*@brief	�����t���O�𗧂Ă�
	*/
	void SetIsFind(bool isFind)
	{
		m_isFind = isFind;
	}
protected:
	bool m_isFind = false;						//�����t���O
	StoneMonster* m_stoneMonster = nullptr;		//�X�g�[�������X�^�[
	StoneMonsterStateMachine* m_sms = nullptr;	//�X�e�[�g�}�V��
};