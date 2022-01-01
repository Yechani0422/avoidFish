#include "BgmManager.h"

BgmManager* BgmManager::s_pInstance=NULL;

void BgmManager::load(const char* fileName)
{
	bgm = Mix_LoadMUS(fileName);//음악 파일을 불러온다
}

void BgmManager::playBGM()
{
	if (Mix_PlayingMusic() == 0)//음악이 재생중이지않으면
	{
		Mix_PlayMusic(bgm, -0);//재생한다
	}
}

void BgmManager::clean()
{
	Mix_FreeMusic(bgm);//음악해제
}