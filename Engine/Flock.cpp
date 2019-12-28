#include "Flock.h"
#include <Math.h>



Flock::Flock()
	:
	rng(rd()),
	xDist(0, 770),
	yDist(0, 570)
{
	
	std::uniform_real_distribution<float> vDist(-2.0f, 2.0f);
	
	for (int i = 0; i < birds; ++i)
	{
		b[i].init(Vec2(xDist(rng), yDist(rng)), Vec2(vDist(rng), vDist(rng)), Colors::Cyan);

	}
	
	//b[0].init(Vec2(550,290), Vec2(-2,0));
	//b[1].init(Vec2(550,270), Vec2(-2,0));
	//o[0].initObstacles(Vec2(400,300), 40);
	
	std::uniform_int_distribution<int> rDist(20, 40);
	for (int i = 0; i < obstacles; ++i)
	{
		o[i].initObstacles(Vec2(xDist(rng),yDist(rng)), rDist(rng));
	}
	
}

Vec2 Flock::align(Bird & birdA)
{
	Vec2 x = {0.0f,0.0f};
	int count = 0;
	for (int i = 0; i < birds; i++)
	{
		if (&birdA != &b[i] )
		{
			if (neighbourFound(birdA, b[i]) == true)
			{
				x += b[i].getVel();
				count++;
			}
		}
	}
	
	if(count == 0)
	{ 
		return { 0.0f,0.0f };
	}
	x /= float(count);
	return x;
}

Vec2 Flock::Cohesion(Bird & birdA)
{
	Vec2 x = { 0.0f,0.0f };
	int count = 0;
	for (int i = 0; i < birds; i++)
	{
		if (&birdA != &b[i])
		{
			if (neighbourFound(birdA, b[i]) == true)
			{
				x += b[i].getPos();
				count++;
			}
		}
	}
	
	if (count == 0)
	{
		return { 0.0f,0.0f };
	}
	
	x = (x / float(count));
	x = x.GetNormalized();

	return x;
}

Vec2 Flock::Seperation(Bird& birdA)
{
	Vec2 x = { 0,0 };
	Vec2 y = { 0,0 };
	int count = 0;

	for (int i = 0; i < birds; i++)
	{
		if (&birdA != &b[i])
		{
			if (moveAway(birdA, b[i]) == true)
			{
				y = birdA.getPos() - b[i].getPos();
				x += (y * ( 1 / y.GetLength() ));
				count++;
			}
		}
	}

	if (count == 0)
	{
		return { 0.0f,0.0f };
	}

	x = x.GetNormalized();
	return x;
}

Vec2 Flock::avoidObstacle(Bird & birdA)
{
	Vec2 a = { 0,0 };
	Vec2 b = { 0,0 };
	Vec2 x = { 0,0 };
	float angle = 0.0f;
	int count = 0;

	for (int i = 0; i < obstacles; i++)
	{
		if (detectObstacle(birdA, o[i]) == true)
		{
			oDetected = true;
			a = o[i].getPos() - birdA.getPos();
			a=a.GetNormalized();
			b = birdA.getSensorPos() - birdA.getPos();
			b=b.GetNormalized();
			float dot = a.x * b.x + a.y * b.y;
			float cross = a.x * b.y - a.y * b.x;
			angle = atan2f(cross,dot);
			if (angle < 0)
			{
				angle -= 30 * float(std::_Pi / 180);
			}
			else
			{
				angle += 30 * float(std::_Pi/ 180);
			}
			count++;
		}
		else
		{
			oDetected = false;
		}
	}


	x = birdA.getVel();
	x = x.rotate(angle);
	return x;
}

bool Flock::neighbourFound(Bird & birdA, Bird & birdB)
{
	Vec2 x = birdA.getPos();
	Vec2 y = birdB.getPos();
	if (((y.x - x.x) * (y.x - x.x)) + ((y.y - x.y) * (y.y - x.y)) <= outerRing * outerRing)
	{
		return true;
	}
	
	return false;
}

bool Flock::moveAway(Bird & birdA, Bird & birdB)
{
	Vec2 x = birdA.getPos();
	Vec2 y = birdB.getPos();
	if (((y.x - x.x) * (y.x - x.x)) + ((y.y - x.y) * (y.y - x.y)) <= innerRing * innerRing)
	{
		return true;
	}

	return false;
}

bool Flock::detectObstacle(Bird & bird, Obstacle & obst)
{
	Vec2 x = bird.getSensorPos();
	Vec2 y = obst.getPos();
	if (((y.x - x.x) * (y.x - x.x)) + ((y.y - x.y) * (y.y - x.y)) <= (obst.getRadius() + outerRing) * (obst.getRadius()+ outerRing))
	{
		return true;
	}
	return false;
}

void Flock::updatePos()
{
	
	for (int i = 0; i < birds; i++)
	{
		steer = { 0,0 };
		steer += avoidObstacle(b[i]);
		if (oDetected == false)
		{
			steer += align(b[i]);
			steer += Cohesion(b[i]);
			steer += Seperation(b[i]);
			b[i].UpdateSteer(steer);
		}
		else
		{
			steer += align(b[i]);
			steer += Cohesion(b[i]);
			steer += Seperation(b[i]);
			b[i].UpdateSteer(steer);
		}
	}
	for (int i = 0; i < birds; i++)
	{
		b[i].UpdatePos();
		b[i].updateSensor();
	}
}

void Flock::drawBirds(Graphics& gfx)
{
	for (int i = 0; i < birds; i++)
	{
		b[i].DrawBird(gfx);
	}
}

void Flock::drawObstacles(Graphics & gfx)
{
	for (int i = 0; i < obstacles; i++)
	{
		o[i].drawObstacle(gfx);
	}
}


