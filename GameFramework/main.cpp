#include "Game.h"
#include <iostream>
#include <time.h>
#include <Windows.h>

int main(int argc, char* argv[])
{
	srand(time(NULL));
	const int FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;
	Uint32 frameStart, frameTime;

	//utf-8형식으로 인코딩해야 한글이 깨지지않는다.
	wchar_t wTitle[100] = L"물고기 피하기!";
	char mTitle[100];
	WideCharToMultiByte(CP_UTF8, 0, wTitle ,- 1, mTitle, 100, NULL, NULL);

	std::cout << "game init attempt...\n";
	if (TheGame::Instance()->init(mTitle,
		100, 100, 640, 480, false))
	{
		std::cout << "game init success!\n";
		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else {
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}
	std::cout << "game closing...\n";
	TheGame::Instance()->clean();
	return 0;
}