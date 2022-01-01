#pragma once
#include <SDL_mixer.h>

class BgmManager
{
public:
	void load(const char* fileName);
	void playBGM();
	void clean();
	static BgmManager* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new BgmManager();
		}
		return s_pInstance;
	}
private:
	BgmManager() {};
	static BgmManager* s_pInstance;
	Mix_Music* bgm;
};

