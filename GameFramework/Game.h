#pragma once
#include "TextureManager.h"
#include <vector>

class GameStateMachine;

class Game {
public:
	~Game() {}
	bool init(const char* title, int xpos, int ypos,
		int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	void quit();
	bool running() { return m_bRunning; }

	static Game* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	GameStateMachine* m_pGameStateMachine;

	GameStateMachine* getStateMachine()
	{
		return m_pGameStateMachine;
	}
private:
	Game() {};
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
};
typedef Game TheGame;