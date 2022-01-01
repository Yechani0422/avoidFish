#include "Timer.h"
#include <SDL.h>


Timer::Timer()
{
	flag = false;
	startTick = 0;
	interval = 0;
}

void Timer::setInterval(int interval)//���ʸ��� ����ɰ��� �������ִ��Լ�
{
	this->interval = interval;
}

void Timer::Start()//Ÿ�̸� �����Լ�.
{
	startTick = SDL_GetTicks();
	flag = true;
}

bool Timer::Done()//������ �ð����� true�� �������ش�
{
	if (flag) {
		if (SDL_GetTicks() - startTick >= interval) {
			startTick = SDL_GetTicks();
			return true;
		}
	}
	return false;
}