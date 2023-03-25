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
#include "Controls.h"
using namespace sf;


int main()
{
	//::ShowWindow(::GetConsoleWindow(), SW_HIDE); // Damit die Konsole nicht mehr da ist. Bleibt jetzt auch bei system() weg.
	::ShowWindow(::GetConsoleWindow(), SW_SHOW); // Damit die Konsole wieder da ist.

	RenderWindow window(VideoMode(1920, 991), "DronesTowerDefence");

	window.setPosition(Vector2i(0, 0));
	window.setFramerateLimit(60);

	Event* event = Controls::getEvent();
	Loadup* load = new Loadup(&window);
	Sprite* credits = new Sprite();

	sf::Thread* thread = new sf::Thread(&Loadup::run, load); // Erstellt einen Thread mit Loadup::run als Einstiegspunkt
	thread->launch(); // Startet den Thread

	while (window.isOpen() && (!load->getDone() || !Mouse::isButtonPressed(Mouse::Left)))
	{
		while (window.pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
		window.clear();
		window.draw(load->getLoadingbarShapes()[0]);
		window.draw(load->getLoadingbarShapes()[1]);
		window.draw(*load->getLoadingbarText());
		window.draw(*credits);
		window.display();

		if (load->getDone())
		{
			credits->setTexture(*Ressources::getInstance()->getCreditsTexture());
			window.setIcon(Ressources::getInstance()->getIcon().getSize().x, Ressources::getInstance()->getIcon().getSize().y, Ressources::getInstance()->getIcon().getPixelsPtr()); //Setzen des Icons
		}
	}
	thread->terminate();
	delete thread;
	delete load;

	HomeMenu::getInstance()->HomeMenuStart(); //Das HomeMenu wird aufgerufen/gestartet

	window.close();
	return 0;
}