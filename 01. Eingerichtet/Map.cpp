#include "Map.h"

/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
void Map::chekChanceRichtung(RectangleShape* drohne, int* x, int* y, float v) // x , y , v in Drohne
{
	Vector2f pos = drohne->getPosition();
	for (Waypoint* p : points)
	{
		Vector2f koa = p->getKooadinaten();
		if (!p->getPass())
		{

			switch (p->getCondition())
			{
			case 1:
				if (pos.y == koa.y && pos.x >= koa.x)
				{
					move(drohne, x, y, v, p, true);
					return;
				}
				break;

			case 2:
				if (pos.y == koa.y && pos.x <= koa.x)
				{
					move(drohne, x, y, v, p, true);
					return;
				}
				break;
			case 3:
				if (pos.y >= koa.y && pos.x == koa.x)
				{
					move(drohne, x, y, v, p, true);
					return;
				}
				break;
			case 4:
				if (pos.y <= koa.y && pos.x == koa.x)
				{
					move(drohne, x, y, v, p, true);
					return;
				}
				break;
			default:
				break;
			}
		}



	}
	move(drohne, x, y, v, nullptr, false);

}

void Map::move(RectangleShape* drohne, int* x, int* y, float v, Waypoint* kp, bool change = false)
{
	if (change)
	{
		drohne->setPosition(kp->getKooadinaten());
		kp->setPass(true);
		Vector2f direction = kp->getNewMove();
		*x = direction.x;
		*y = direction.y;

	}
	else

		drohne->move(*x * v, *y * v);


}

Vector2f Map::getStart()
{
	return start;
}

Vector2f Map::getStartMove()
{
	return startMove;
}
/// <summary>
/// Create Map
/// </summary>
Map::Map()
{
	points.push_back(new Waypoint(Vector2f(4 * 40-20,  4 * 40), Vector2f(1, 0), 4));
	points.push_back(new Waypoint(Vector2f(12 * 40 - 20, 4 * 40), Vector2f(0, 1), 1));
	points.push_back(new Waypoint(Vector2f(12 * 40 - 20, 22 * 40), Vector2f(1, 0), 3));
	points.push_back(new Waypoint(Vector2f(20 * 40 - 20, 22 * 40), Vector2f(0, -1), 1));
	points.push_back(new Waypoint(Vector2f(20 * 40 - 20,  4* 40), Vector2f(1, 0), 4));
	points.push_back(new Waypoint(Vector2f(28 * 40 - 20, 4 * 40), Vector2f(0, 1), 1));
	points.push_back(new Waypoint(Vector2f(28 * 40 - 20, 22 * 40), Vector2f(1, 0), 3));
	points.push_back(new Waypoint(Vector2f(36 * 40 - 20, 22 * 40), Vector2f(0, -1), 1));
	points.push_back(new Waypoint(Vector2f(36 * 40 - 20, 4 * 40), Vector2f(1, 0), 4));
	points.push_back(new Waypoint(Vector2f(44 * 40 - 20, 4 * 40), Vector2f(0, 1), 1));

	start = Vector2f(4 * 40-20, 27 * 40);
	startMove = Vector2f(0, -1);
	
}
