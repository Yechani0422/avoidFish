#pragma once
#include "SDLGameObject.h"

class Enemy :public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams,int direction);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void handleInput();

	int speed;
	int m_direction;
	int cource;

	void respawnFish();
};