#pragma once
class Timer
{
public:
	Timer();
	void setInterval(int interval);
	void Start();
	bool Done();
private:
	int startTick;
	int interval;
	bool flag;
};

