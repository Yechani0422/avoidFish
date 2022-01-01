#pragma once
#include "SDLGameObject.h"

class LoaderParams;

class AnimatedGraphic : public SDLGameObject
{
	int m_animSpeed;
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);
	virtual void update();
};

