#include "PlayState.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Enemy.h"
#include "GameStateMachine.h"
#include "PauseState.h"
#include "SDLGameObject.h"
#include "GameOverState.h"
#include "TextManager.h"
#include "InputHandler.h"
#include "Player.h"
#include <string>

const std::string PlayState::s_playID = "PLAY";

PlayState* PlayState::s_pInstance = NULL;

void PlayState::update()
{
	//텍스트
	std::string str_fishQuantity;
	str_fishQuantity = std::to_string(fishQuantity);//물고기 수를 폰트로 표현하기위해 스트링으로 변환해준다.
	std::string str_Time;
	str_Time = std::to_string(time);//시간을 폰트로 표현하기위해 스트링으로 변환해준다.
	TextManager::Instance()->update(10, 10, "물고기수:" + str_fishQuantity + "       " + 
		str_Time.substr(0, str_Time.find(".") + 3)+"초");//텍스트 업데이트 함수에 문자열을 넘겨준다

	if (TheInputHandler::Instance()->isKeyDown(
		SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->changeState(PauseState::Instance());
	}
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	//충돌처리
	for (int i = 2; i < m_gameObjects.size(); i++)
	{
		if (checkCollision(
			dynamic_cast<SDLGameObject*>(m_gameObjects[1]),
			dynamic_cast<SDLGameObject*>(m_gameObjects[i])))
		{
			GameOverState::Instance()->setScore(str_Time.substr(0, str_Time.find(".") + 3));
			TheGame::Instance()->getStateMachine()
				->changeState(GameOverState::Instance());
		}
	}
	//물고기생성
	makeFish();
	//플레이시간
	if (playTime.Done() == true)
	{
		time += 0.01666666666666667f;
	}
}
void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		TextManager::Instance()->draw();
		m_gameObjects[i]->draw();
	}
}



bool PlayState::onEnter()
{
	m_gameObjects.clear();
	std::cout << "entering PlayState\n";
	if (!TheTextureManager::Instance()->load(
		"Assets/bg.png",
		"bg",
		TheGame::Instance()->getRenderer())) {
		return false;
	}
	GameObject* bg = new SDLGameObject(
		new LoaderParams(0, 0, 640, 480, "bg"));
	if (!TheTextureManager::Instance()->load(
		"assets/peng.png", "peng",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* player = new Player(
		new LoaderParams(309, 227, 22, 26, "peng"));
	if (!TheTextureManager::Instance()->load(
		"assets/fish2.png", "fish",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	m_gameObjects.push_back(bg);
	m_gameObjects.push_back(player);

	TextManager::Instance()->load(30, "assets/batang.ttc", TheGame::Instance()->getRenderer());

	fishQuantity = 0;
	time = 0.0f;

	makeFishTimer.setInterval(2000);//물고기를 2초에 한번씩생성할수있도록 타이머의 시간을 2초로 설정해준다
	makeFishTimer.Start();

	playTime.setInterval(10);
	playTime.Start();

	return true;
}

bool PlayState::onExit()
{
	std::cout << "exiting PlayState\n";
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("bg");
	TheTextureManager::Instance()->clearFromTextureMap("peng");
	TheTextureManager::Instance()->clearFromTextureMap("fish");
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();
	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}



void PlayState::makeFish()//물고기를 생성해준다
{
	if (fishQuantity < 50)
	{
		m_gameObjects.push_back(new Enemy(
			new LoaderParams(-500, -500, 11, 6, "fish"), rand() % 4 + 1));
		fishQuantity += 1;
	}
	else if (fishQuantity >= 50)//50개부터 물고기를 2초에 한개씩 생성한다
	{
		if (makeFishTimer.Done()==true)
		{
			m_gameObjects.push_back(new Enemy(
				new LoaderParams(-500, -500, 11, 6, "fish"), rand() % 4 + 1));
			fishQuantity += 1;
		}
	}
}

