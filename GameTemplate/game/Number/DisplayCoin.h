#pragma once

#include "Number.h"

class DisplayCoin : public GameObject
{
public:
	DisplayCoin();
	~DisplayCoin();
	bool Start();
	void Update();
	void DeleteNum();
	void Render();
private:
	Number* num[2];
};