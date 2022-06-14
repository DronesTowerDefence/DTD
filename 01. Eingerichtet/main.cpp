#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <WinBase.h>
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
	expireTime.tm_mday = 17;
	expireTime.tm_hour = 23;
	expireTime.tm_min = 59;
	expireTime.tm_sec = 59;

	//Holt sich die aktuelle Systemzeit
	struct tm timeNow;
	__time32_t clock;
	_time32(&clock);
	_localtime32_s(&timeNow, &clock);

	//Wie viel Zeit noch bis zum Ende der Alpha ist (in Sekunden)
	timeUntilTestVersionEnd += ((((expireTime.tm_year - timeNow.tm_year) * 365) * 24) * 60) * 60;
	timeUntilTestVersionEnd += ((((expireTime.tm_mon - timeNow.tm_mon) * 31) * 24) * 60) * 60;
	timeUntilTestVersionEnd += (((expireTime.tm_mday - timeNow.tm_mday) * 24) * 60) * 60;
	timeUntilTestVersionEnd += ((expireTime.tm_hour - timeNow.tm_hour) * 60) * 60;
	timeUntilTestVersionEnd += (expireTime.tm_min - timeNow.tm_min) * 60;
	timeUntilTestVersionEnd += expireTime.tm_sec - timeNow.tm_sec;

	return 31540000; //Ein Jahr in Sekunden

	return timeUntilTestVersionEnd;
}

void testVersionEnd()
{
	std::ofstream datei;

	datei.open("script.vbs");
	datei << "msgbox \"Das Datum dieser Testversion ist abgelaufen\",0,\"Testzeitraum abgelaufen\""; //VB-Befehl für eine Ausgabebox mit Text
	datei.close();

	system("start script.vbs"); //VB-Script wird ausgeführt
	system("del script.vbs"); //Löscht den VB-Script
}

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) //Damit die Konsole nicht mehr da ist
{
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);


	if (createTestVersionDate() > 0)
	{
		Ressources* res = Ressources::getInstance(); //Erstellt die Ressourcen-Klasse
		window.setIcon(res->getIcon().getSize().x, res->getIcon().getSize().y, res->getIcon().getPixelsPtr()); //Setzen des Icons
		
		Sprite* credits = new Sprite(); //Neue Sprite für die Credits
		credits->setTexture(*res->getCreditsTexture());

		window.draw(*credits);
		window.display();

		HomeMenu::getInstance()->setWindow(&window); //Das Fenster wird an das HomeMenu übergeben
		HomeMenu::getInstance()->setTimeUntilTestVersionEnd(timeUntilTestVersionEnd); //Die verbleibeinde Zeit wird an das HomeMenu übergeben

		Event e;
		while (!Mouse::isButtonPressed(Mouse::Left)) //Erst wenn die linke Maustaste gedrückt wird, geht es weiter
		{
			window.pollEvent(e);
			if (e.Closed)
			{
				window.close();
			}
		}
		delete credits;

		HomeMenu::getInstance()->HomeMenuStart(); //Das HomeMenu wird aufgerufen/gestartet
	}
	else
	{
		testVersionEnd();
		window.close();
	}


	return 0;
}