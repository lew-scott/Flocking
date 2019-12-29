#include "Bird.h"
#include <assert.h>

void Bird::init(const Vec2 & pos_in, const Vec2 & vel_in, const Color& col_in)
{
	assert(initialised == false);
	pos = pos_in;
	vel = vel_in;
	c = col_in;
	initialised = true;
}

void Bird::DrawBird(Graphics& gfx) const
{
	// initiate at origin
	Vec2 p1(0.0f,-6.0f);
	Vec2 p2(2.0f, 2.0f);
	Vec2 p3(0.0f, 1.0f);
	Vec2 p4(-2.0f, 2.0f);

	// rotate
	float angle = float(std::atan2(vel.x,-vel.y));
	p1.rotate(angle);
	p2.rotate(angle);
	p3.rotate(angle);
	p4.rotate(angle);

	// translate
	p1 += pos;
	p2 += pos;
	p3 += pos;
	p4 += pos;

	//draw
	gfx.Drawline(p1, p2, c);
	gfx.Drawline(p2, p3, c);
	gfx.Drawline(p3, p4, c);
	gfx.Drawline(p4, p1, c);
	//gfx.Drawline(p1, sensor, Colors::Red);
	//gfx.DrawCircle(sensor.x, sensor.y, 2, Colors::Red);
}



void Bird::UpdatePos()
{

	vel += steer * 0.1;

	if (vel.GetLengthSq() >= Vmax * Vmax)
	{
		vel = vel.GetNormalized() * Vmax;
	}

	pos += vel;
	if (pos.x < 0)
	{
		pos.x += 800.0f;
	}
	else if (pos.x >= 800.0f)
	{
		pos.x -= 800.0f;
	}
	if (pos.y < 0)
	{
		pos.y += 600.0f;
	}
	else if (pos.y >= 600.0f)
	{
		pos.y -= 600.0f;
	}

}



void Bird::UpdateSteer(Vec2 str)
{
	steer = str;
}

void Bird::updateSensor()
{
	Vec2 s = { 0,-100 };
	float angle = float(std::atan2(vel.x, -vel.y));
	s.rotate(angle);
	sensor = s + pos;
	if (sensor.x < 0)
	{
		sensor.x += 800.0f;
	}
	else if (sensor.x >= 800.0f)
	{
		sensor.x -= 800.0f;
	}
	if (sensor.y < 0)
	{
		sensor.y += 600.0f;
	}
	else if (sensor.y >= 600.0f)
	{
		sensor.y -= 600.0f;
	}
}

Vec2 Bird::getVel()
{
	return vel;
}

Vec2 Bird::getPos()
{
	return pos;
}

Vec2 Bird::getSensorPos()
{
	return sensor;
}


