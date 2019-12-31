#pragma once
#include "Bird.h"
#include "Obstacle.h"
#include "Vec2.h"
#include <random>
#include "Graphics.h"
#include <vector>



class Flock
{
public:
	Flock();
	Vec2 Flocking(Bird& birdA, Bird birds[]);
	Vec2 Flock::avoidOtherFlock(Bird& birdA, Bird OtherBirds[]);
	bool neighbourFound(Bird& birdA, Bird& birdB);
	bool moveAway(Bird& birdA, Bird& birdB);
	void updatePos();
	void drawBirds(Graphics& gfx);


private:
	static constexpr float outerRing = 50.0f;
	static constexpr float innerRing = 30.0f;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist;
	std::uniform_real_distribution<float> yDist;
	static constexpr int birds = 100;
	Bird b[birds];
	Bird b2[birds];
	Bird b3[birds];
	Vec2 steer = { 0,0 };
};


