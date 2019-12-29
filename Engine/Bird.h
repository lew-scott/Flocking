#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include <cmath>


class Bird 
{
public:
	void init(const Vec2& pos_in, const Vec2& vel_in, const Color& col_in);
	void DrawBird(Graphics& gfx) const;
	void UpdatePos();
	void UpdateSteer(Vec2 steer);
	void updateSensor();
	Vec2 getVel();
	Vec2 getPos();
	Vec2 getSensorPos();

private:

	Vec2 vel;
	Vec2 pos;
	Vec2 sensor;
	Vec2 steer = { 0,0 };
	Color c;
	const float Vmax = 3.0f;
	bool initialised = false;



};

