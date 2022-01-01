#include "TextManager.h"
#include "han2unicode.h"

TextManager* TextManager::s_pInstance = NULL;

void TextManager::load(int _size, const char* ttf_name, SDL_Renderer* pRenderer)
{
	size = _size;//��Ʈũ��
	Renderer = pRenderer;

	font = TTF_OpenFont(ttf_name, size);//��Ʈ������.

	//��Ʈ����
	color.r = 255;//����
	color.g = 255;//�׸�
	color.b = 255;//���
	color.a = 255;//����
}

void TextManager::update(int x, int y, std::string input)
{
	rect.x = x;
	rect.y = y;
	rect.w = 0;
	rect.h = 0;

	char* cstr = new char[input.length() + 1];
	strcpy(cstr, input.c_str());

	han2unicode(cstr, dest);//���ڿ��� ���ڵ��ϱ����� �Լ�(���ڵ����������� ���ڰ�������)
	msg = TTF_RenderUNICODE_Blended(font, dest, color);//32��Ʈ ���ǽ�, ���� ������, ǰ�� ����
	texture = SDL_CreateTextureFromSurface(Renderer, msg);//Surface�� �����ϰ� �� Surface�� �̹���ó�� ����Ѵ�.
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

//��Ʈ����� ������ �������ִ��Լ�
void TextManager::setRGBAlpha(int r, int g, int b,int alpha)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = alpha;
}