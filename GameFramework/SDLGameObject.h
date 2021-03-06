#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject :public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {};
	Vector2D getPosition() const { return m_position; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int m_numFrames;

protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

};
