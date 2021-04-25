#pragma once
#include <SDL.h>

class Timer {
public:
	Timer(int _timer); // count down from _timer
	~Timer();
	int getTimePassed();  //in second(s)
	int getTimeLeft(); // in second(s)
	void reset();
	void pause();
	void resume();
	void addBonusTime(int second);
	bool end();
	bool isPaused;
private:
	uint32_t start;
	uint32_t reserveTime;
	int timePassed;
	int timer;
};