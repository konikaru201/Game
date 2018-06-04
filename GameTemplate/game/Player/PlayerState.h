#pragma once

class PlayerState {
public:
	enum PlState {
		plState_Idle,		//待機
		plState_Move,		//移動
		plState_Dead,		//死亡
		plState_GetStar,	//スター獲得
		plState_Invald,		//何もない
	};
};