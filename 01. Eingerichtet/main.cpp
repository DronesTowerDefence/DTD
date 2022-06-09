#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include "Ressources.h"
#include "HomeMenu.h"
using namespace sf;

unsigned long long timeUntilTestVersionEnd = 0;

int createTestVersionDate()
{
	//Festgelegte Zeit
	struct tm expireTime;
	expireTime.tm_year = 122;
	expireTime.tm_mon = 5;
	expireTime.tm_mday = 30;
	expireTime.tm_hour = 23;
	expireTime.tm_min = 59;
	expireTime.tm_sec = 59;

	//Holt sich die aktuelle Systemzeit
	struct tm timeNow;
	__time32_t clock;
	_time32(&clock);
	_localtime32_s(&timeNow, &clock);


	//Überprüfung ob die festgelegte Zeit größer als die aktuelle Zeit ist
	if (expireTime.tm_year >= timeNow.tm_year && expireTime.tm_mon >= timeNow.tm_mon && expireTime.tm_mday >= timeNow.tm_mday)
	{
		timeUntilTestVersionEnd += ((((expireTime.tm_year - timeNow.tm_year) * 365) * 24) * 60) * 60;
		timeUntilTestVersionEnd += ((((expireTime.tm_mon - timeNow.tm_mon) * 31) * 24) * 60) * 60;
		timeUntilTestVersionEnd += (((expireTime.tm_mday - timeNow.tm_mday) * 24) * 60) * 60;

		if (expireTime.tm_hour >= timeNow.tm_hour && expireTime.tm_min >= timeNow.tm_min && expireTime.tm_sec >= timeNow.tm_sec)
		{
			timeUntilTestVersionEnd += ((expireTime.tm_hour - timeNow.tm_hour) * 60) * 60;
			timeUntilTestVersionEnd += (expireTime.tm_min - timeNow.tm_min) * 60;
			timeUntilTestVersionEnd += expireTime.tm_sec - timeNow.tm_sec;
		}
	}

	return timeUntilTestVersionEnd;
}

int main()
{
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);

	if (createTestVersionDate() > 0)
	{
		Ressources* ressources = Ressources::getInstance();

		window.setIcon(ressources->getIcon().getSize().x, ressources->getIcon().getSize().y, ressources->getIcon().getPixelsPtr());

		HomeMenu::getInstance()->setWindow(&window);
		HomeMenu::getInstance()->setTimeUntilTestVersionEnd(timeUntilTestVersionEnd);
		HomeMenu::getInstance()->HomeMenuStart();
	}
	else
	{
		window.close();
		std::cout << "The max date for this testing version is expired" << std::endl;
	}


	return 0;
}