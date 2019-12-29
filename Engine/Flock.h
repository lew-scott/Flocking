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
	Vec2 align(Bird& birdA);
	Vec2 Cohesion(Bird& birdA);
	Vec2 Seperation(Bird& birdA);
	bool neighbourFound(Bird& birdA, Bird& birdB);
	bool moveAway(Bird& birdA, Bird& birdB);
	void updatePos();
	void drawBirds(Graphics& gfx);
	//void drawObstacles(Graphics& gfx);

private:
	static constexpr float outerRing = 40.0f;
	static constexpr float innerRing = 15.0f;
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist;
	std::uniform_real_distribution<float> yDist;
	static constexpr int birds = 100;
	Bird b[birds];
	Vec2 steer = { 0,0 };
};


