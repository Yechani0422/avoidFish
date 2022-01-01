#include "PauseState.h"
#include "Game.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "GameStateMachine.h"
#include <iostream>

const std::string PauseState::s_pauseID = "PAUSE";

PauseState* PauseState::s_pInstance = NULL;


void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if (!TheTextureManager::Instance()->load(
		"Assets/bg.png","bg",TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/restart.png",
		"rstartbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main.png",
		"mainbutton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* bg = new SDLGameObject(
		new LoaderParams(0, 0, 640, 480, "bg"));
	GameObject* button1 = new MenuButton(new
		LoaderParams(219.5, 300, 201, 80, "mainbutton"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new
		LoaderParams(219.5, 200, 201, 80, "rstartbutton"), s_resumePlay);
	m_gameObjects.push_back(bg);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("bg");
	TheTextureManager::Instance()
		->clearFromTextureMap("resumebutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("mainbutton");
	std::cout << "exiting PauseState\n";
	return true;
}
