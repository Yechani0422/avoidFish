#pragma once
#include "GameState.h"
#include "Timer.h"

class SDLGameObject;

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_playID; }
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	static PlayState* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new PlayState();
		}
		return s_pInstance;
	}

private:
	static const std::string s_playID;


	PlayState() {};
	static PlayState* s_pInstance;

	void makeFish();//물고기생성함수

	int fishQuantity = 0;//물고기갯수

	Timer makeFishTimer;
	Timer playTime;

	float time;
};



