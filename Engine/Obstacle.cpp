#include "Obstacle.h"
#include <assert.h>

void Obstacle::initObstacles(const Vec2 & position, const int & radius)
{
	assert(initialised == false);
	pos = position;
	rad = radius;
	initialised = true;
}

int Obstacle::getRadius()
{
	return rad;
}

Vec2 Obstacle::getPos()
{
	return pos;
}

void Obstacle::drawObstacle(Graphics& gfx)
{
	Vec2 p = pos;
	gfx.DrawLineCircle(int(p.x), int(p.y), rad-1, rad, Colors::Gray);
}
