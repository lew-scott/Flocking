#include "Graphics.h"
#include "Vec2.h"
#include <cmath>

class Obstacle
{

public:
	void initObstacles(const Vec2& position, const int& radius);
	int getRadius();
	Vec2 getPos();
	void drawObstacle(Graphics& gfx);

private:
	 int rad;
	 Vec2 pos;
	 bool initialised = false;
};
