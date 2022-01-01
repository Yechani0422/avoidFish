#pragma once
#include "GameState.h"
class CreditState:public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_creditID; }

	static CreditState* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new CreditState();
		}
		return s_pInstance;
	}
private:
	static const std::string s_creditID;

	CreditState() {};
	static CreditState* s_pInstance;
};

