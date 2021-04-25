#include "../include/Timer.h"

Timer::Timer(int _timer) {
	start = SDL_GetTicks();
	timePassed = 0;
	timer = _timer;
	reserveTime = 0;
	isPaused = false;
}

Timer::~Timer() {

}

int Timer::getTimePassed() {
	uint32_t time = SDL_GetTicks() - start + reserveTime;
	return time / 1000;
}

void Timer::reset() {
	start = SDL_GetTicks();
	timePassed = 0;
}

bool Timer::end() {
	if (timePassed >= timer) return true;
	return false;
}

void Timer::pause() {
	reserveTime += SDL_GetTicks() - start;
	isPaused = true;
}

void Timer::resume() {
	start = SDL_GetTicks();
	isPaused = false;
}

void Timer::addBonusTime(int second) {
	timer += second;
}

int Timer::getTimeLeft() {
	return timer - getTimePassed();
}