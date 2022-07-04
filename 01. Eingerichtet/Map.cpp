#include "Map.h"
#include "Round.h"

#pragma region Konstruktor
/// <summary>
/// Create Map
/// </summary>
Map::Map(int index)
{

	this->index = index; //Muss bei mehreren Maps angepasst werden. Mit einem Übergabe Parameter

	background.setSize(Vector2f(1920, 991));
	background.setTexture(Ressources::getInstance()->getMapTexture(index));
	wayPointCount = 0;
	switch (index)
	{
	case 0:
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
		points.push_back(new Waypoint(Vector2f(39 * 40 - 20, 991), Vector2f(0, 1), 3));
		wayPointCount = 11;

		start = Vector2f(4 * 40 - 20, 27 * 40);
		startMove = Vector2f(0, -1);
		break;

	case 1:
		points.push_back(new Waypoint(Vector2f(1470, 210), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(1470, 830), Vector2f(-1, 0), 3));
		points.push_back(new Waypoint(Vector2f(380, 830), Vector2f(0, -1), 2));
		points.push_back(new Waypoint(Vector2f(330, 390), Vector2f(1, 0), 4));
		points.push_back(new Waypoint(Vector2f(1270, 390), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(1270, 570), Vector2f(-1, 0), 3));
		points.push_back(new Waypoint(Vector2f(-50, 570), Vector2f(-1, 0), 2));
		start = Vector2f(-50, 210);
		startMove = Vector2f(1, 0);
		wayPointCount = 7;
		break;
	case 2:
		points.push_back(new Waypoint(Vector2f(435, 66), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(435,507), Vector2f(1, 0), 3));
		points.push_back(new Waypoint(Vector2f(877,507), Vector2f(0, -1), 1));
		points.push_back(new Waypoint(Vector2f(877,66), Vector2f(1,0), 4));
		points.push_back(new Waypoint(Vector2f(1318,66), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(1318, 799), Vector2f(-1,0), 3));
		points.push_back(new Waypoint(Vector2f(715, 799), Vector2f(0, -1), 2));
		points.push_back(new Waypoint(Vector2f(715, 189), Vector2f(1,0), 4));
		points.push_back(new Waypoint(Vector2f(715, 1720), Vector2f(1, 0), 4));
		start = Vector2f(-50, 66);
		startMove = Vector2f(1, 0);
		wayPointCount = 8;
	}
}
#pragma endregion
#pragma region Funktionen
/// <summary>
/// Allgemeine Funktionen 
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
void Map::checkChangeDirection(Drone* drone) // x , y , v in Drohne
{
	//Waypoint* np = 
	int np_index = drone->getNextPoint();
	Vector2f pos = drone->getPosition();

	Waypoint* nextWayPoint = getWaypoint(np_index);
	Vector2f koa = nextWayPoint->getKooadinaten();
	switch (nextWayPoint->getCondition())
	{
	case 1:
		if (pos.y == koa.y && pos.x >= koa.x)
		{
			changeDirection(drone, nextWayPoint);

			return;

		}
		break;

	case 2:
		if (pos.y == koa.y && pos.x <= koa.x)
		{
			changeDirection(drone, nextWayPoint);

			return;
		}
		break;
	case 3:
		if (pos.y >= koa.y && pos.x == koa.x)
		{
			changeDirection(drone, nextWayPoint);

			return;
		}
		break;
	case 4:
		if (pos.y <= koa.y && pos.x == koa.x)
		{
			changeDirection(drone, nextWayPoint);

			return;
		}
		break;
	default:
		break;
	}

}
void Map::changeDirection(Drone* drone, Waypoint* wp)
{
	drone->setPosition(wp->getKooadinaten());
	drone->setMove(wp->getNewMove());
	if (getWaypoint(drone->getNextPoint() + 1) != nullptr)
	{
		drone->pass();
	}
}
#pragma endregion

#pragma region getter
int Map::getIndex()
{
	return index;
}
int Map::getWayPointCount()
{
	return wayPointCount;
}
Vector2f Map::getStart()
{
	return start;
}
Vector2f Map::getStartMove()
{
	return startMove;
}
Vector2f Map::getWaypointAsVector(int index)
{
	int i = 0;
	for (auto curser : points)
	{
		if (i == index)
		{
			return curser->getKooadinaten();
		}
		i++;
	}
	return Vector2f(0, 0);
}
RectangleShape* Map::getBackround()
{
	return &background;
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
std::list<Waypoint*>& Map::getPoints()
{
	return points;
}
#pragma endregion

#pragma region setter

#pragma endregion

#pragma region Desturktor

#pragma endregion
