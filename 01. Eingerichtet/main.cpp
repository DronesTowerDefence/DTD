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
#include "Loadup.h"
#include "HomeMenu.h"
using namespace sf;


// int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) //Damit die Konsole nicht mehr da ist
int main()
{
	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);

	Event event;
	Sprite sprite;
	Loadup* load = new Loadup();

	sf::Thread* thread = new sf::Thread(&Loadup::run, load); // Erstellt einen Thread mit Loadup::run als Einstiegspunkt
	thread->launch(); // Startet den Thread

	while (window.isOpen() && (!load->getDone() || !Mouse::isButtonPressed(Mouse::Left)))
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
		sprite.setTexture(load->getRenderTexture()->getTexture());
		window.clear();
		window.draw(sprite);
		window.display();
	}
	thread->terminate();
	delete thread;
	delete load;

	HomeMenu::getInstance()->setWindow(&window); //Das Fenster wird an das HomeMenu übergeben
	HomeMenu::getInstance()->HomeMenuStart(); //Das HomeMenu wird aufgerufen/gestartet

	window.close();
	return 0;
}