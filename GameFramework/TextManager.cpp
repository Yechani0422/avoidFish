#include "TextManager.h"
#include "han2unicode.h"

TextManager* TextManager::s_pInstance = NULL;

void TextManager::load(int _size, const char* ttf_name, SDL_Renderer* pRenderer)
{
	size = _size;//폰트크기
	Renderer = pRenderer;

	font = TTF_OpenFont(ttf_name, size);//폰트를연다.

	//폰트색상
	color.r = 255;//레드
	color.g = 255;//그린
	color.b = 255;//블루
	color.a = 255;//투명도
}

void TextManager::update(int x, int y, std::string input)
{
	rect.x = x;
	rect.y = y;
	rect.w = 0;
	rect.h = 0;

	char* cstr = new char[input.length() + 1];
	strcpy(cstr, input.c_str());

	han2unicode(cstr, dest);//문자열을 인코딩하기위한 함수(인코딩하지않으면 글자가깨진다)
	msg = TTF_RenderUNICODE_Blended(font, dest, color);//32비트 서피스, 느린 렌더링, 품질 위주
	texture = SDL_CreateTextureFromSurface(Renderer, msg);//Surface에 렌더하고 그 Surface를 이미지처럼 출력한다.
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

void TextManager::draw()
{
	SDL_RenderCopy(Renderer, texture, NULL, &rect);
}

void TextManager::clean()
{
	SDL_DestroyRenderer(Renderer);
}

//폰트색상과 투명도를 설정해주는함수
void TextManager::setRGBAlpha(int r, int g, int b,int alpha)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = alpha;
}