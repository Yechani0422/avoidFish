#include "Timer.h"
#include <SDL.h>


Timer::Timer()
{
	flag = false;
	startTick = 0;
	interval = 0;
}

void Timer::setInterval(int interval)//몇초마다 실행될건지 설정해주는함수
{
	this->interval = interval;
}

void Timer::Start()//타이머 시작함수.
{
	startTick = SDL_GetTicks();
	flag = true;
}

bool Timer::Done()//설정된 시간마다 true를 리턴해준다
{
	if (flag) {
		if (SDL_GetTicks() - startTick >= interval) {
			startTick = SDL_GetTicks();
			return true;
		}
	}
	return false;
}