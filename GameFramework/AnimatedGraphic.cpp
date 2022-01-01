#include "AnimatedGraphic.h"
#include "Game.h"

AnimatedGraphic::AnimatedGraphic(
	const LoaderParams* pParams, int animSpeed)
	: SDLGameObject(pParams), m_animSpeed(animSpeed)
{
}


void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_animSpeed));
}

