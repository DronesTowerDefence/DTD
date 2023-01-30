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

	Loadup* load = new Loadup(&window);
	load->start();

	HomeMenu::getInstance()->setWindow(&window); //Das Fenster wird an das HomeMenu übergeben
	HomeMenu::getInstance()->HomeMenuStart(); //Das HomeMenu wird aufgerufen/gestartet

	window.close();
	return 0;
}