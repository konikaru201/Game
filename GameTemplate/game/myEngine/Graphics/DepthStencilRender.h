#pragma once

#include "myEngine/GameObject/GameObject.h"

class DepthStencilRender : public GameObject
{
public:
	DepthStencilRender();
	~DepthStencilRender();

	bool Start();

	void Update();

	void Render();
};