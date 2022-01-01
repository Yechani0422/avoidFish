#include "BgmManager.h"

BgmManager* BgmManager::s_pInstance=NULL;

void BgmManager::load(const char* fileName)
{
	bgm = Mix_LoadMUS(fileName);//���� ������ �ҷ��´�
}

void BgmManager::playBGM()
{
	if (Mix_PlayingMusic() == 0)//������ ���������������
	{
		Mix_PlayMusic(bgm, -0);//����Ѵ�
	}
}

void BgmManager::clean()
{
	Mix_FreeMusic(bgm);//��������
}