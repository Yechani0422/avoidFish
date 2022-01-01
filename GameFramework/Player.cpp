#include "Player.h"
#include "Game.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{

}

void Player::draw()
{
	if (IsFlip==false) {
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(),
			(Uint32)m_position.getY(),
			m_width, m_height,
			m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer(),
			SDL_FLIP_HORIZONTAL);
	}
	else {
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(),
			(Uint32)m_position.getY(),
			m_width, m_height,
			m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer());
	}

	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput();	

	m_currentFrame = int(((SDL_GetTicks() / 100) % 4));
	SDLGameObject::update();
}

void Player::clean()
{
	SDLGameObject::clean();
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
		if (m_position.getX() < 618)
		{
			m_velocity.setX(2.5);
		}
		IsFlip = true;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
		if (m_position.getX() > 0)
		{
			m_velocity.setX(-2.5);
		}
		IsFlip = false;
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
		if (m_position.getY() > 0)
		{
			m_velocity.setY(-2.5);
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
		if (m_position.getY() < 454)
		{
			m_velocity.setY(2.5);
		}
	}
}
