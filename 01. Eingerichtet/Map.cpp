#include "Map.h"

/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
void Map::chekChanceRichtung(Drone* drohne) // x , y , v in Drohne
{
	//Waypoint* np = 
	int np_index = drohne->getNextPoint();
	Vector2f pos = drohne->getPosition();

	Vector2f koa;//= np->getKooadinaten();

	Waypoint* nextWayPoint = getWaypoint(np_index);
	switch (nextWayPoint->getCondition())
	{
	case 1:
		if (pos.y == koa.y && pos.x >= koa.x)
		{
			move(drohne, nextWayPoint, true);
			return;
		}
		break;

	case 2:
		if (pos.y == koa.y && pos.x <= koa.x)
		{
			move(drohne, nextWayPoint, true);
			return;
		}
		break;
	case 3:
		if (pos.y >= koa.y && pos.x == koa.x)
		{
			move(drohne, nextWayPoint, true);
			return;
		}
		break;
	case 4:
		if (pos.y <= koa.y && pos.x == koa.x)
		{
			move(drohne, nextWayPoint, true);
			return;
		}
		break;
	default:
		break;
	}
	move(drohne, nextWayPoint, false);

}

void Map::move(Drone* drohne, Waypoint* wp, bool change)
{
	if (change)
	{

		drohne->setMove(wp->getNewMove());
		if (getWaypoint(drohne->getNextPoint() + 1) != nullptr)
		{
			drohne->pass();
		}
		else
		{
			//TODO:: Drohne l�schen
		}

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
std::list<Waypoint*>& Map::getPoints()
{
	return points;
}
Waypoint* Map::getWaypoint(int index)
{
	int i = 0;
	for (auto curser : points)
	{
		if (i == index)
		{
			return curser;
		}
		i++;
	}
	return nullptr;
}
/// <summary>
/// Create Map
/// </summary>
Map::Map()
{

	points.push_back(new Waypoint(Vector2f(4 * 40 - 20, 4 * 40 + 31), Vector2f(1, 0), 4));
	//points.push_back(new Waypoint(Vector2f(11 * 40 - 20, 4 * 40 + 31), Vector2f(0, 1), 1));
	//points.push_back(new Waypoint(Vector2f(11 * 40 - 20, 19 * 40 + 31), Vector2f(1, 0), 3));
	//points.push_back(new Waypoint(Vector2f(18 * 40 - 20, 19 * 40 + 31), Vector2f(0, -1), 1));
	//points.push_back(new Waypoint(Vector2f(18 * 40 - 20, 4 * 40 + 31), Vector2f(1, 0), 4));
	//points.push_back(new Waypoint(Vector2f(25 * 40 - 20, 4 * 40 + 31), Vector2f(0, 1), 1));
	//points.push_back(new Waypoint(Vector2f(25 * 40 - 20, 19 * 40 + 31), Vector2f(1, 0), 3));
	//points.push_back(new Waypoint(Vector2f(32 * 40 - 20, 19 * 40 + 31), Vector2f(0, -1), 1));
	//points.push_back(new Waypoint(Vector2f(32 * 40 - 20, 4 * 40 + 31), Vector2f(1, 0), 4));
	//points.push_back(new Waypoint(Vector2f(39 * 40 - 20, 4 * 40 + 31), Vector2f(0, 1), 1));
	//points.push_back(new Waypoint(Vector2f(39 * 40 - 20, 27 * 40), Vector2f(0, 1), 1)); // endVektor

	start = Vector2f(4 * 40 - 20, 27 * 40);
	startMove = Vector2f(0, -1);

}
