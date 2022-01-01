#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include <iostream>
#include "GameStateMachine.h"
#include "TextManager.h"
#include "InputHandler.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";
GameOverState* GameOverState::s_pInstance = NULL;

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(
		MenuState::Instance());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(
		PlayState::Instance());
}

bool GameOverState::onEnter()
{
	std::cout << score << std::endl;
	if (!TheTextureManager::Instance()->load("assets/gameover2.png",
		"gameovertext", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/main.png",
		"mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/restart.png",
		"restartbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* gameOverText = new AnimatedGraphic(
		new  LoaderParams(0, 0, 640, 480, "gameovertext"), 3);

	GameObject* button1 = new MenuButton(
		new LoaderParams(219.5, 300, 201, 80, "mainbutton"),
		s_gameOverToMain);

	GameObject* button2 = new MenuButton(
		new LoaderParams(219.5, 200, 201, 80, "restartbutton"),
		s_restartPlay);

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering PauseState\n";
	return true;
}

void GameOverState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(
		SDL_SCANCODE_SPACE))
	{
		TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	TextManager::Instance()->update(270, 150, score+"초");
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		TextManager::Instance()->draw();
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()
		->clearFromTextureMap("gameovertext");
	TheTextureManager::Instance()
		->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()
		->clearFromTextureMap("restartbutton");
	std::cout << "exiting PauseState\n";
	return true;
}

//PlayState에서 생존시간을 받아오기위한 함수
void GameOverState::setScore(std::string _score)
{
	score = _score;
}