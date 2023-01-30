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


int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) //Damit die Konsole nicht mehr da ist
{
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);

	Ressources* res = Ressources::getInstance(); //Erstellt die Ressourcen-Klasse
	window.setIcon(res->getIcon().getSize().x, res->getIcon().getSize().y, res->getIcon().getPixelsPtr()); //Setzen des Icons

	// TODO Account

	Sprite* credits = new Sprite(); //Neue Sprite für die Credits
	credits->setTexture(*res->getCreditsTexture());

	window.draw(*credits);
	window.display();

	HomeMenu::getInstance()->setWindow(&window); //Das Fenster wird an das HomeMenu übergeben

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

	window.close();
	return 0;
}