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
	Loadup* load = new Loadup(&window);

	sf::Thread* thread = new sf::Thread(&Loadup::run, load); // Erstellt einen Thread mit Loadup::run als Einstiegspunkt
	window.setActive(false); // Nimmt dem Hauptthread die Rechte an dem Fenster (wie die lock-Variable)
	thread->launch(); // Startet den Thread
	
	while (window.isOpen() && !Mouse::isButtonPressed(Mouse::Left))
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
	}
	thread->terminate();
	delete thread;
	delete load;
	window.setActive(true);

	HomeMenu::getInstance()->setWindow(&window); //Das Fenster wird an das HomeMenu übergeben
	HomeMenu::getInstance()->HomeMenuStart(); //Das HomeMenu wird aufgerufen/gestartet

	window.close();
	return 0;
}