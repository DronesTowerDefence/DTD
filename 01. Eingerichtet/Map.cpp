#include "Map.h"

/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
void Map::chekChanceRichtung(Drone* drohne) // x , y , v in Drohne
{
	Waypoint* np = *drohne->getNextPoint();
	Vector2f pos = drohne->getPosition();

	Vector2f koa = np->getKooadinaten();


	switch (np->getCondition())
	{
	case 1:
		if (pos.y == koa.y && pos.x >= koa.x)
		{
			move(drohne , np , true);
			return;
		}
		break;

	case 2:
		if (pos.y == koa.y && pos.x <= koa.x)
		{
			move(drohne , np, true);
			return;
		}
		break;
	case 3:
		if (pos.y >= koa.y && pos.x == koa.x)
		{
			move(drohne , np, true);
			return;
		}
		break;
	case 4:
		if (pos.y <= koa.y && pos.x == koa.x)
		{
			move(drohne , np, true);
			return;
		}
		break;
	default:
		break;
	}
	move(drohne, np, false);

}

void Map::move(Drone* drohne, Waypoint* wp, bool change)
{
	if (change)
	{
		drohne->setMove(wp->getNewMove());
	}
	else

		drohne->move();


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

	points.push_back(new Waypoint(Vector2f(4 * 40 - 20, 4 * 40 + 31), Vector2f(1, 0), 4));
	points.push_back(new Waypoint(Vector2f(11 * 40 - 20, 4 * 40 + 31), Vector2f(0, 1), 1));
	points.push_back(new Waypoint(Vector2f(11 * 40 - 20, 19 * 40 + 31), Vector2f(1, 0), 3));
	points.push_back(new Waypoint(Vector2f(18 * 40 - 20, 19 * 40 + 31), Vector2f(0, -1), 1));
	points.push_back(new Waypoint(Vector2f(18 * 40 - 20, 4 * 40 + 31), Vector2f(1, 0), 4));
	points.push_back(new Waypoint(Vector2f(25 * 40 - 20, 4 * 40 + 31), Vector2f(0, 1), 1));
	points.push_back(new Waypoint(Vector2f(25 * 40 - 20, 19 * 40 + 31), Vector2f(1, 0), 3));
	points.push_back(new Waypoint(Vector2f(32 * 40 - 20, 19 * 40 + 31), Vector2f(0, -1), 1));
	points.push_back(new Waypoint(Vector2f(32 * 40 - 20, 4 * 40 + 31), Vector2f(1, 0), 4));
	points.push_back(new Waypoint(Vector2f(39 * 40 - 20, 4 * 40 + 31), Vector2f(0, 1), 1));

	start = Vector2f(4 * 40 - 20, 27 * 40);
	startMove = Vector2f(0, -1);

}
