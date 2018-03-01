#pragma once

class StoneMonsterState {
public:
	//モンスターの状態
	enum EnState {
		enState_Idle,		//待機ステート
		enState_Follow,		//追従ステート
		enState_Invald,		//何もない
	};
};