#include "CreditState.h"
#include "Game.h"
#include <iostream>
#include "GameStateMachine.h"
#include "TextManager.h"
#include "MenuState.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

const std::string CreditState::s_creditID = "CREDIT";

CreditState* CreditState::s_pInstance = NULL;

void CreditState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(
		SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
	}

	TextManager::Instance()->update(200, 220, "제작:김예찬");
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void CreditState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		
		m_gameObjects[i]->draw();
	}
	TextManager::Instance()->draw();
}

bool CreditState::onEnter()
{
	std::cout << "entering CreditState\n";
	if (!TheTextureManager::Instance()->load(
		"Assets/bg.png", "bg", TheGame::Instance()->getRenderer())) {
		return false;
	}

	GameObject* bg = new SDLGameObject(
		new LoaderParams(0, 0, 640, 480, "bg"));

	m_gameObjects.push_back(bg);

	TextManager::Instance()->load(50, "assets/batang.ttc", TheGame::Instance()->getRenderer());
	TextManager::Instance()->setRGBAlpha(0, 0, 0, 255);

	return true;
}

bool CreditState::onExit()
{
	std::cout << "exiting CreditState\n";
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("bg");
	return true;
}