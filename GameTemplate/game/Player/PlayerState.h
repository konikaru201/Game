/*!
*@brief	�v���C���[�̏�ԃN���X
*/

#pragma once

class PlayerState {
public:
	enum PlState {
		plState_Idle,			//�ҋ@
		plState_Move,			//�ړ�
		plState_Dead,			//���S
		plState_ChangeStage,	//�X�e�[�W�ύX
		plState_Invald,			//�����Ȃ�
	};
};