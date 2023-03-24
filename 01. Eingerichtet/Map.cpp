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
		points.push_back(new Waypoint(Vector2f(4 * 40, 4 * 40 + 31 + 20), Vector2f(1, 0), 4));
		points.push_back(new Waypoint(Vector2f(11 * 40, 4 * 40 + 31 + 20), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(11 * 40, 19 * 40 + 31 + 20), Vector2f(1, 0), 3));
		points.push_back(new Waypoint(Vector2f(18 * 40, 19 * 40 + 31 + 20), Vector2f(0, -1), 1));
		points.push_back(new Waypoint(Vector2f(18 * 40, 4 * 40 + 31 + 20), Vector2f(1, 0), 4));
		points.push_back(new Waypoint(Vector2f(25 * 40, 4 * 40 + 31 + 20), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(25 * 40, 19 * 40 + 31 + 20), Vector2f(1, 0), 3));
		points.push_back(new Waypoint(Vector2f(32 * 40, 19 * 40 + 31 + 20), Vector2f(0, -1), 1));
		points.push_back(new Waypoint(Vector2f(32 * 40, 4 * 40 + 31 + 20), Vector2f(1, 0), 4));
		points.push_back(new Waypoint(Vector2f(39 * 40, 4 * 40 + 31 + 20), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(39 * 40, 991 + 20), Vector2f(0, 1), 3));
		wayPointCount = 11;

		start = Vector2f(4 * 40, 27 * 40 + 20);
		startMove = Vector2f(0, -1);
		break;

	case 1:
		points.push_back(new Waypoint(Vector2f(1470 + 20, 210 + 20), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(1470 + 20, 830 + 20), Vector2f(-1, 0), 3));
		points.push_back(new Waypoint(Vector2f(350 , 830 + 20), Vector2f(0, -1), 2));
		points.push_back(new Waypoint(Vector2f(330 + 20, 410), Vector2f(1, 0), 4));
		points.push_back(new Waypoint(Vector2f(1270 + 20, 410), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(1270 + 20, 570 + 20), Vector2f(-1, 0), 3));
		points.push_back(new Waypoint(Vector2f(-50 + 20, 570 + 20), Vector2f(-1, 0), 2));
		start = Vector2f(-50 +20, 210 + 20);
		startMove = Vector2f(1, 0);
		wayPointCount = 7;
		break;
	case 2:
 		points.push_back(new Waypoint(Vector2f(435 + 20, 66 + 20), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(435 + 20, 507 + 20), Vector2f(1, 0), 3));
		points.push_back(new Waypoint(Vector2f(877 + 20, 507 + 20), Vector2f(0, -1), 1));
		points.push_back(new Waypoint(Vector2f(877 + 20, 66 + 20), Vector2f(1, 0), 4));
		points.push_back(new Waypoint(Vector2f(1318 + 20, 66 + 20), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(1318 + 20, 799 + 20), Vector2f(-1, 0), 3));
		points.push_back(new Waypoint(Vector2f(685, 799 + 20), Vector2f(0, -1), 2));
		points.push_back(new Waypoint(Vector2f(685, 189 + 30), Vector2f(1, 0), 4));
		points.push_back(new Waypoint(Vector2f(1720 + 20, 189 + 20), Vector2f(1, 0), 1));
		start = Vector2f(-50+20, 66 + 20);
		startMove = Vector2f(1, 0);
		wayPointCount = 9;
		break;
	case 3:
		points.push_back(new Waypoint(Vector2f(130, 450 + 20), Vector2f(1, 0), 3));
		points.push_back(new Waypoint(Vector2f(370 , 450 + 20), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(370 , 660 + 20), Vector2f(1, 0), 3));
		points.push_back(new Waypoint(Vector2f(1530 , 660 + 20), Vector2f(0, -1), 1));
		points.push_back(new Waypoint(Vector2f(1530 , 160 + 20), Vector2f(-1, 0), 4));
		points.push_back(new Waypoint(Vector2f(930 , 160 + 20), Vector2f(0, 1), 2));
		points.push_back(new Waypoint(Vector2f(930 , 660 + 20), Vector2f(1, 0), 3));
		points.push_back(new Waypoint(Vector2f(1530, 660 + 20), Vector2f(0, -1), 1));
		points.push_back(new Waypoint(Vector2f(1530, 160 + 20), Vector2f(-1, 0), 4));
		points.push_back(new Waypoint(Vector2f(930 , 160 + 20), Vector2f(0, 1), 2));
		points.push_back(new Waypoint(Vector2f(930 , 830 + 20), Vector2f(-1, 0), 3));
		points.push_back(new Waypoint(Vector2f(224 , 830 + 20), Vector2f(0, -1), 2));
		points.push_back(new Waypoint(Vector2f(224 , -50 + 20), Vector2f(0, -1), 4));
		start = Vector2f(130 , -50 + 20);
		startMove = Vector2f(0, 1);
		wayPointCount = 13;
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
