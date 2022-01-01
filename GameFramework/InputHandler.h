#pragma once
#include "SDL.h"
#include "Game.h"
#include "Vector2D.h"
#include <vector>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
	bool isKeyDown(SDL_Scancode key);
	bool isKeyOneDown(SDL_Scancode key);
	bool getMouseButtonState(int buttonNumber);
	Vector2D* getMousePosition();
	void onMouseMove(SDL_Event event) ;
	void onMouseButtonDown(SDL_Event event) ;
	void onMouseButtonUp(SDL_Event event) ;
	void onKeyDown();
	void onKeyUp();
	void update();
	void clean();  // 디바이스 관련 초기화된 부분을 clear 
private:
	InputHandler();
	~InputHandler() {};
	static InputHandler* s_pInstance;
	const Uint8* m_keystates;
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
};
typedef InputHandler TheInputHandler;
