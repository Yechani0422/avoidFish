#pragma once
#include "Game.h"
#include <SDL_ttf.h>
#include <string>

class TextManager
{
public:
	void load(int _size,const char* ttf_name, SDL_Renderer* pRenderer);
	void update(int x, int y,std::string input);
	void draw();
	void clean();
	void setRGBAlpha(int r, int g, int b,int alpha);

	static TextManager* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new TextManager();
		}
		return s_pInstance;
	}
private:
	TextManager() { TTF_Init(); };
	static TextManager* s_pInstance;
	int size;
	char* message;

	TTF_Font* font;
	SDL_Color color;
	Uint16 dest[70];
	SDL_Surface* msg;
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Renderer* Renderer;
};

