#pragma once

class PlayerState {
public:
	enum PlState {
		plState_Idle,		//�ҋ@
		plState_Move,		//�ړ�
		plState_Dead,		//���S
		plState_GetStar,	//�X�^�[�l��
		plState_Invald,		//�����Ȃ�
	};
};