#include "PauseMenu.h"
#include <iostream>


PauseMenu* PauseMenu::instance = nullptr;


PauseMenu* PauseMenu::getInstance() {

	if (instance == nullptr) {

		instance = new PauseMenu();

	}

	return instance;

}

PauseMenu::PauseMenu() {

	window = Game::getInstance()->getWindow();

	//Ich kann nicht auf die Font in Game zugreifen (unerklärbarer Error mit wherenode) also deklariere ich die Font nochmal selbst
	font.loadFromFile("fonts/arial.ttf");

	//Rahmen für das Pause-Menu
	edge.setFillColor(Color::Blue);
	edge.setSize(Vector2f(690.f,700.f));
	edge.setPosition(548.f, 148.f);
	

	volumeSlider.setFillColor(Color::Green);
	volumeSlider.setSize(Vector2f(400.f, 14.f));
	volumeSlider.setPosition(Vector2f(565.f, 370.f));

	//Anfangslautstärke beträgt 50%
	sliderHelper = 50.f;

	backgroundTexture.loadFromFile("img/backround.jpg");
	background.setTexture(backgroundTexture);
	background.setPosition(553.f, 150.f);
	background.setScale(Vector2f(float(0.3555), float(0.5405)));
	
	//Überschriften
	text1.setFont(font);
	text1.setCharacterSize(unsigned(40));
	text1.setPosition(Vector2f(565.f, 170.f));
	text1.setFillColor(Color::Black);
	text1.setOutlineThickness(float(0.3));

	//Beschreibungen
	text2.setFont(font);
	text2.setCharacterSize(unsigned(25));
	text2.setPosition(Vector2f(565.f, 170.f));
	text2.setFillColor(Color::Black);

}


void PauseMenu::checkPause(Event event1)
{

	if (event1.type == Event::KeyReleased && event1.key.code == Keyboard::Escape) { //Übergebenes Event wird geprüft auf ESC-Druck

		while (window->isOpen())  //Fenster wird schon im Konstruktor übergeben und als Pointer gespeichert
		{

			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window->close();
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) { // Mit erneutem ESC-Druck wieder in Anfangs-whileschleife in Game.cpp
					return;
				}

				

			}
			//Hier wird der Text angezeigt, text1 ist Überschrift, text2 ist Beschreibung (sliderHelper ist die float-Variable für den Slider)
			text1.setString("Pause Menu : \n\n\nLautstärke : " + std::to_string(int(sliderHelper)) + " % ");
			text2.setString("\n\n\n\n\n\n\n\n (Mit Pfeiltasten ändern, links = leiser, rechts = lauter)");

			//Pfeiltasten Druck = Änderung Lautstärke
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				if (sliderHelper == 0.f) {
					sliderHelper = 1.f;
				}
				sliderHelper--;
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				if (sliderHelper == 100.f) {
					sliderHelper = 99.f;
				}
				sliderHelper++;
			}

			Game::getInstance()->setMusicVolume(sliderHelper); 
			volumeSlider.setSize(Vector2f(sliderHelper/100*400.f, 14.f)); //Hier berechne ich mit Prozentrechnung aus dem Grundwert und dem Prozentsatz den Prozentwert
			Game::getInstance()->changeBackgroundMusic(); //Da die Musik weiterlaufen soll, muss man die hier auch aufrufen
			draw(); //Texte und Objekte werden gezeichnet

		}
	}

	return;

}

void PauseMenu::draw()
{

	window->draw(edge);
	window->draw(background);
	window->draw(text1);
	window->draw(text2);

	window->draw(volumeSlider);

	window->display();

}

RectangleShape PauseMenu::getEdge()
{
	return edge;
}

Sprite PauseMenu::getBackground()
{
	return background;
}

Text PauseMenu::getText()
{
	return text1;
}

void PauseMenu::click() //WIP (WORK IN PROGRESS), noch nicht in Benutzung
{
}
