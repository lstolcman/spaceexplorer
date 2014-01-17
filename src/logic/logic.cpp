#include "stdafx.hpp"
#include "logic.hpp"






CLogic::CLogic(SData *data)
{
	this->data = data;
}


CLogic::~CLogic()
{

}


/*
1. detect collision between vehicle and last collided object(sphere-sphere check) - for better performance
2. if sp-sp == true - detect collsion between every vertice of asteroid
*/


/*
This small operation calcuates the distance between two points. The routine can work in any number of dimensions, so you cold apply it to 2D or 3D.
In 3D - Define your two points. Point 1 at (x1, y1, z1) and Point 2 at (x2, y2, z2).

xd = x2-x1
yd = y2-y1
zd = z2-z1
Distance = SquareRoot(xd*xd + yd*yd + zd*zd)

As you can see, this requires that you perform a square root. Square roots should be avoided like the plague if you want to write fast code. Only perform a Square Root if you really need to.

Ways to avoid Square Roots:
If you don't need a very accurate distance, you can use a lookup table to calculate it.
If, for example, you are performing collision detection between spheres, and all you want to know is whether or not two have collided, then you do not need to use a square root. Simply change the piece of code from:

if SquareRoot(xd*xd + yd*yd) < Diameter

to:

if (xd*xd + yd*yd) < (Diameter*Diameter)


*/
void CLogic::detectCollision(void)
{

	for (std::vector<SAsteroid>::iterator i = data->asteroids->begin(); i != data->asteroids->end(); ++i)
	{

		asteroidPos = i->pos;
		vehiclePos = data->camera->pos+data->camera->view;
		distanceVec = asteroidPos - vehiclePos;

		i->distance = sqrt(distanceVec.x*distanceVec.x + distanceVec.y*distanceVec.y + distanceVec.z*distanceVec.z);
	}

	for (std::vector<SAsteroid>::iterator i = data->asteroids->begin(); i != data->asteroids->end(); ++i)
	{
		if (i->distance < 1.5)
		{
			i->collision = true;
			data->debugCollision = true;
		}
		else
		{
			i->collision = false;
			data->debugCollision = false;
		}
	}

}











