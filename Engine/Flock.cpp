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
		b2[i].init(Vec2(xDist(rng), yDist(rng)), Vec2(vDist(rng), vDist(rng)), Colors::Red);
		b3[i].init(Vec2(xDist(rng), yDist(rng)), Vec2(vDist(rng), vDist(rng)), Colors::Yellow);
	}
}

Vec2 Flock::Flocking(Bird & birdA, Bird b[])
{
	Vec2 Align = { 0.0f,0.0f }; // alignment 
	Vec2 Coh = { 0.0f, 0.0f }; // cohesion
	Vec2 SepX = { 0.0f, 0.0f }; // seperation
	Vec2 SepY = { 0.0f, 0.0f };
	int countA = 0; // count birds in larger radius

	for (int i = 0; i < birds; i++)
	{
		if (&birdA != &b[i]) // check address of self, so not to include in calculation
		{
			if (neighbourFound(birdA, b[i]) == true)
			{
				Coh += b[i].getPos() - birdA.getPos(); // return vector towards neighbour
				Align += b[i].getVel();
				countA++;
			}

			if (moveAway(birdA, b[i]) == true)
			{
				SepY = birdA.getPos() - b[i].getPos(); // return vector facing toward the bird 
				SepX += (SepY * (1 / SepY.GetLength())); // vector is inversely proportional to distance
			}
		}
	}
	
	if (countA == 0) // catch if no birds are nearby
	{
		return { 0.0f,0.0f };
	}
	
	Align = (Align / float(countA)); // calculate average velocity of birds nearby 
	Coh = Coh.GetNormalized(); // normalise average position to a force which can be added 
	SepX = SepX.GetNormalized();


	return Align + Coh * 0.9 + SepX * 1.1 ; // return vector as steering velocity
											// +/- cohesion and seperation for better visual flocking
}



Vec2 Flock::avoidOtherFlock(Bird& birdA, Bird otherBirds[])
{
	Vec2 a = { 0,0 };
	Vec2 b = { 0,0 };
	Vec2 x = { 0,0 };
	float angle = 0.0f;
	int count = 0;

	for (int i = 0; i < birds; i++)
	{
		if (neighbourFound(birdA, otherBirds[i]) == true)
		{
			a = otherBirds[i].getPos() - birdA.getPos();
			a=a.GetNormalized();

			b = birdA.getVel();
			b=b.GetNormalized();

			float dot = a.x * b.x + a.y * b.y;
			float cross = a.x * b.y - a.y * b.x;
			angle = atan2f(cross,dot);

			if (angle < 0)
			{
				angle -= 10 * float(std::_Pi / 180);
			}
			else
			{
				angle += 10 * float(std::_Pi/ 180);
			}
			count++;
			
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

void Flock::updatePos()
{
	
	for (int i = 0; i < birds; i++)
	{
		steer = Flocking(b[i], b);
		steer += avoidOtherFlock(b[i], b2);
		steer += avoidOtherFlock(b[i], b3);
		b[i].UpdateSteer(steer);

		steer = Flocking(b2[i], b2);
		steer += avoidOtherFlock(b2[i], b);
		steer += avoidOtherFlock(b2[i], b3);
		b2[i].UpdateSteer(steer);

		steer = Flocking(b3[i], b3);
		steer += avoidOtherFlock(b3[i], b);
		steer += avoidOtherFlock(b3[i], b2);
		b3[i].UpdateSteer(steer);
		
	}
	for (int i = 0; i < birds; i++)
	{
		b[i].UpdatePos();
		b2[i].UpdatePos();
		b3[i].UpdatePos();
	}
}

void Flock::drawBirds(Graphics& gfx)
{
	for (int i = 0; i < birds; i++)
	{
		b[i].DrawBird(gfx);
		b2[i].DrawBird(gfx);
		b3[i].DrawBird(gfx);
	}
}




