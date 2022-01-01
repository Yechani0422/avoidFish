#include "Enemy.h"
#include "InputHandler.h"
#include <stdlib.h>

Enemy::Enemy(const LoaderParams* pParams,int direction) : SDLGameObject(pParams),m_direction(direction)
{
	speed = rand() % 2 + 1;
	cource = rand() % 2+1;
	//�����Ǵ���ġ
	switch (m_direction)
	{
	case 1://��
		m_position.setX(rand() % 640);
		m_position.setY(-6);

		m_velocity.setY(speed);
		if (cource == 1)
		{
			m_velocity.setX(speed);
		}
		else
		{
			m_velocity.setX(-speed);
		}
		break;
	case 2://�Ʒ�
		m_position.setX(rand() % 640);
		m_position.setY(480);

		m_velocity.setY(-speed);
		if (cource == 1)
		{
			m_velocity.setX(speed);
		}
		else
		{
			m_velocity.setX(-speed);
		}
		break;
	case 3://����
		m_position.setX(-11);
		m_position.setY(rand()%480);

		m_velocity.setX(speed);
		if (cource == 1)
		{
			m_velocity.setY(speed);
		}
		else
		{
			m_velocity.setY(-speed);
		}
		break;
	case 4://������
		m_position.setX(640);
		m_position.setY(rand() % 480);

		m_velocity.setX(-speed);
		if (cource == 1)
		{
			m_velocity.setY(speed);
		}
		else
		{
			m_velocity.setY(-speed);
		}
	}
}

void Enemy::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Enemy::update()
{	
	handleInput();
	
	respawnFish();
	
	SDLGameObject::update();
}

void Enemy::clean()
{
}

void Enemy::handleInput()
{
	
}

void Enemy::respawnFish()
{
	//ȭ������� ������� �ӵ��� �ٲ��� ���´�
	if (m_position.getX() < -11)
	{
		speed = rand() % 2 + 1;
		m_velocity.setX(speed);
	}
	else if (m_position.getX() > 640)
	{
		speed = rand() % 2 + 1;
		m_velocity.setX(-speed);
	}
	else if (m_position.getY() < -6)
	{
		speed = rand() % 2 + 1;
		m_velocity.setY(speed);
	}
	else if (m_position.getY() > 480)
	{
		speed = rand() % 2 + 1;
		m_velocity.setY(-speed);
	}
}