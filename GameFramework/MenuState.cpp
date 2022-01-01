#include "MenuState.h"
#include <iostream>
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "CreditState.h"

const std::string MenuState::s_menuID = "MENU";

MenuState* MenuState::s_pInstance = NULL;


void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	std::cout << "entering MenuState\n";
	if (!TheTextureManager::Instance()->load(
		"Assets/bg.png","bg",TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load(
		"Assets/title.png", "title", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load(
		"Assets/start.png",
		"playbutton",
		TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load(
		"Assets/exit.png",
		"exitbutton",
		TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load(
		"Assets/credit.png",
		"creditbutton",
		TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* bg = new SDLGameObject(
		new LoaderParams(0, 0, 640, 480, "bg"));

	GameObject* title = new SDLGameObject(
		new LoaderParams(45, 60, 560, 92, "title"));

	GameObject* button1 = new MenuButton(
		new LoaderParams(219.5, 200, 201, 80, "playbutton"),
		s_menuToPlay);

	GameObject* button2 = new MenuButton(
		new LoaderParams(219.5, 300, 201, 80, "exitbutton"),
		s_exitFromMenu);

	GameObject* button3 = new MenuButton(
		new LoaderParams(620, 460, 20, 20, "creditbutton"),
		s_menuToCredit);

	m_gameObjects.push_back(bg);
	m_gameObjects.push_back(title);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);

	return true;
}

bool MenuState::onExit()
{
	std::cout << "exiting MenuState\n";
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()
		->clearFromTextureMap("bg");
	TheTextureManager::Instance()
		->clearFromTextureMap("title");
	TheTextureManager::Instance()
		->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("exitbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("creditbutton");
	return true;
}

void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());

}

void MenuState::s_exitFromMenu()
{
	std::cout << "Exit button clicked\n";
	TheGame::Instance()->quit();
}

void MenuState::s_menuToCredit()
{
	std::cout << "Credit button clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(CreditState::Instance());
}