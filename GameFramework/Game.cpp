#include "Game.h"
#include <iostream>
#include "GameStateMachine.h"
#include "MenuState.h"
#include "TextManager.h"
#include "BgmManager.h"
#include "InputHandler.h"
#include <SDL_image.h>


Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos,
	int width, int height, bool fullscreen)
{
	if (!TheTextureManager::Instance()->load("assets/animate-alpha.png",
		"animate", m_pRenderer)) {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,
			width, height, fullscreen);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
	}
	else {
		return false; // sdl could not initialize
	}

	//믹서init검사
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_MIXER could nnnot initialize Error:" << Mix_GetError();
	}

	//bgm로드
	BgmManager::Instance()->load("assets/bgm.wav");

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(MenuState::Instance());

	//윈도우창 아이콘 설정
	SDL_Surface* icon;
	icon = IMG_Load("assets/icon.png");
	SDL_SetWindowIcon(m_pWindow, icon);

	m_bRunning = true;
	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	m_pGameStateMachine->update();
	BgmManager::Instance()->playBGM();
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
	TextManager::Instance()->clean();
	BgmManager::Instance()->clean();
	Mix_Quit();
	SDL_Quit();
	TTF_Quit();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}

void Game::quit()
{
	m_bRunning = false;
}