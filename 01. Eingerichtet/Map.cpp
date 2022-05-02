#include "Map.h"
#include "Round.h"

/// <summary>
/// Create Map
/// </summary>
Map::Map(int index)
{

	this->index = index; //Muss bei mehreren Maps angepasst werden. Mit einem �bergabe Parameter

		Round::getInstance()->setP_map(this);
		texture.loadFromFile("img/maps/map"+std::to_string(index)+".png");
		background.setSize(Vector2f(1920, 991));
		background.setTexture(&texture);
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
		points.push_back(new Waypoint(Vector2f(39 * 40 - 20, 73 * 40 + 31), Vector2f(0, 1),3));
		
		
		start = Vector2f(4 * 40 - 20, 27 * 40);
		startMove = Vector2f(0, -1);
		break;

	case 1:
		points.push_back(new Waypoint(Vector2f(1470, 210), Vector2f(0, 1), 1));
		points.push_back(new Waypoint(Vector2f(1470, 830), Vector2f(-1, 0), 3));
		points.push_back(new Waypoint(Vector2f(330, 830), Vector2f(0, -1), 2));
		points.push_back(new Waypoint(Vector2f(330, 390), Vector2f(1, 0), 4));
		points.push_back(new Waypoint(Vector2f(1270, 390), Vector2f(0, 1),1));
		points.push_back(new Waypoint(Vector2f(1270, 570), Vector2f(-1, 0), 3));
		points.push_back(new Waypoint(Vector2f(0, 570), Vector2f(-1, 0), 2));
		
		start = Vector2f(-50,210);
		startMove = Vector2f(1, 0);

		break;
	}
}
/// <summary>
/// 
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

int Map::getIndex()
{
	return index;
}

RectangleShape* Map::getBackround()
{
	return &background;
}
