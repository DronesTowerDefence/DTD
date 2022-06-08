#include "Multiplayer.h"
#include "PauseMenu.h"
#include <iostream>


PauseMenu* PauseMenu::instance = nullptr;

#pragma region Konstruktor
PauseMenu::PauseMenu() {

	window = Game::getInstance()->getWindow();

	res = Ressources::getInstance();

	//Ich kann nicht auf die Font in Game zugreifen (unerklärbarer Error mit wherenode) also deklariere ich die Font nochmal selbst
	font.loadFromFile("fonts/arial.ttf");

	//Rahmen für das Pause-Menu
	edge.setFillColor(Color::Blue);
	edge.setSize(Vector2f(690.f, 700.f));
	edge.setPosition(548.f, 148.f);

	volumeSlider.setFillColor(Color::Green);
	volumeSlider.setSize(Vector2f(400.f, 15.f));
	volumeSlider.setPosition(Vector2f(565.f, 390.f));


	//Anfangslautstärke beträgt 50%
	sliderHelper = 50.f;

	//für Maus-Click
	isClicked = false;
	play = false;
	mute = false;
	multiplayerIsPaused = false;

	background.setTexture(*res->getPauseScreenBackgroundTexture());
	background.setPosition(530.f, 150.f);
	background.setScale(Vector2f(float(1.36), float(0.7)));



	//Socials
	twitter.setTexture(*res->getSocialsTwitterTexture());
	twitter.setScale(Vector2f(float(0.15), float(0.15)));
	twitter.setPosition(Vector2f(1130.f, 175.f));

	socialsBorder.setFillColor(Color::Transparent);
	socialsBorder.setOutlineColor(Color::Black);
	socialsBorder.setOutlineThickness(float(0.77));
	socialsBorder.setSize(Vector2f(100.f, 100.f));
	socialsBorder.setPosition(1120.f, 165.f);

	//Buttons
	homebtn.setTexture(*res->getButtonHomeTexture());
	homebtn.setPosition(Vector2f(630.f, 750.f));


	playbtn.setTexture(*res->getButtonStartTexture());
	playbtn.setPosition(Vector2f(1030.f, 750.f));

	mutebtnTexture = res->getButtonVolume(2);
	mutebtn.setTexture(*mutebtnTexture);
	mutebtn.setPosition(Vector2f(1050.f, 340.f));

	//Überschriften
	text1.setFont(font);
	text1.setCharacterSize(unsigned(40));
	text1.setPosition(Vector2f(565.f, 171.f));
	text1.setFillColor(Color::Black);
	text1.setOutlineThickness(float(0.3));


	//Beschreibungen
	text2.setFont(font);
	text2.setCharacterSize(unsigned(25));
	text2.setPosition(Vector2f(565.f, 177.f));
	text2.setFillColor(Color::Black);
	/*text2.setOutlineThickness(float(0.6));
	text2.setOutlineColor(Color::White);*/


	for (int i = 0; i < 3; i++) {

		btnoutlines[i].setFillColor(Color::Transparent);
		btnoutlines[i].setSize(Vector2f(100.f, 100.f));
		btnoutlines[i].setOutlineColor(Color::Black);
		btnoutlines[i].setOutlineThickness(1.f);

	}

	btnoutlines[0].setPosition(homebtn.getPosition());
	btnoutlines[1].setPosition(playbtn.getPosition());
	btnoutlines[2].setPosition(mutebtn.getPosition());

	//

	volumeOutline.setFillColor(Color::Transparent);
	volumeOutline.setOutlineColor(Color::Black);
	volumeOutline.setOutlineThickness(float(1));
	volumeOutline.setSize(Vector2f(402.f, 15.f));
	volumeOutline.setPosition(volumeSlider.getPosition() - Vector2f(1.f, 0.f));



}
#pragma endregion

#pragma region Funktionen
void PauseMenu::click() //WIP (WORK IN PROGRESS), noch nicht in Benutzung
{

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = false;
		mouse = Mouse::getPosition(*window);


		//twitter
		pos = Service::getInstance()->getObjectPosition(twitter.getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(twitter.getPosition() + Vector2f(77.f, 77.f)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			system("start www.twitter.com/DronesTD");
		}


		//Home Button
		pos = Service::getInstance()->getObjectPosition(homebtn.getPosition());
		pos2 = Service::getInstance()->getObjectPosition(homebtn.getPosition() + Vector2f(100.f, 100.f));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			Game::getInstance()->mainMenu();
		}

		//Resume - Button Weiter
		pos = Service::getInstance()->getObjectPosition(playbtn.getPosition());
		pos2 = Service::getInstance()->getObjectPosition(playbtn.getPosition() + Vector2f(100.f, 100.f));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
		{
			play = true;
			Multiplayer::send(2, false);
		}
		//mute button

		pos = Service::getInstance()->getObjectPosition(mutebtn.getPosition());
		pos2 = Service::getInstance()->getObjectPosition(mutebtn.getPosition() + Vector2f(100.f, 100.f));

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) {
			if (mute == true) {
				mute = false;
				return;
			}
			mute = true;
		}
	}
}
void PauseMenu::draw()
{

	//window->draw(edge);
	window->draw(background);
	window->draw(text1);
	window->draw(text2);
	window->draw(twitter);
	window->draw(socialsBorder);
	window->draw(homebtn);
	window->draw(playbtn);
	window->draw(mutebtn);

	for (int i = 0; i < 3; i++) {
		window->draw(btnoutlines[i]);
	}


	window->draw(volumeSlider);

	window->draw(volumeOutline);

	window->display();

}
void PauseMenu::checkPause(Event event1)
{
	/*Vector2i mousePos;*/
	if (event1.type == Event::KeyReleased && event1.key.code == Keyboard::Escape) { //Übergebenes Event wird geprüft auf ESC-Druck

		Multiplayer::send(2, true);

		while (window->isOpen())  //Fenster wird schon im Konstruktor übergeben und als Pointer gespeichert
		{

			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window->close();
				}
				if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) // Mit erneutem ESC-Druck wieder in Anfangs-whileschleife in Game.cpp
				{
					Multiplayer::send(2, false);
					return;
				}


			}
			//Hier wird der Text angezeigt, text1 ist Überschrift, text2 ist Beschreibung (sliderHelper ist die float-Variable für den Slider)
			text1.setString("Pause Menu : \n\n\nLautstärke : " + std::to_string(int(sliderHelper)) + " % \n");
			text2.setString("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Twitter:\n\n\n\n\n\n (Mit Pfeiltasten ändern, links = leiser, rechts = lauter)"); //Die Text-Variablen sind von der Position her gleich angeordnet, oben links im Pause-Fenster, deswegen die ganzen "\n"'s

			if (play == true) {
				play = false;
				return;
			}


			//Pfeiltasten Druck = Änderung Lautstärke
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if (sliderHelper == 0.f)
				{
					sliderHelper = 1.f;
				}
				sliderHelper--;
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (sliderHelper == 100.f)
				{
					sliderHelper = 99.f;
				}
				sliderHelper++;
			}

			if (mute == false) {

				if (sliderHelper < 33) {
					mutebtnTexture = res->getButtonVolume(1);
				}
				else if (sliderHelper > 33 && sliderHelper < 66) {
					mutebtnTexture = res->getButtonVolume(2);
				}
				else if (sliderHelper > 66) {
					mutebtnTexture = res->getButtonVolume(3);

				}
			}
			else if (mute == true) {
				mutebtnTexture = res->getButtonVolume(0);
				Game::getInstance()->setMusicVolume(0.f);
			}
			mutebtn.setTexture(*mutebtnTexture);

			/*mousePos = Mouse::getPosition();
			mouse.setPosition(Vector2f(float(mousePos.x),float(mousePos.y)));*/
			if (mute == false) {
				Game::getInstance()->setMusicVolume(sliderHelper);
			}
			volumeSlider.setSize(Vector2f(sliderHelper / 100 * 400.f, 14.f)); //Hier berechne ich mit Prozentrechnung aus dem Grundwert und dem Prozentsatz den Prozentwert
			Game::getInstance()->changeBackgroundMusic(); //Da die Musik weiterlaufen soll, muss man die hier auch aufrufen
			click();
			draw(); //Texte und Objekte werden gezeichnet

		}
	}

	return;

}
void PauseMenu::checkPause(bool isPaused)
{
	if (multiplayerIsPaused)
	{
		while (window->isOpen())  //Fenster wird schon im Konstruktor übergeben und als Pointer gespeichert
		{
			while (Multiplayer::receive());

			if (!multiplayerIsPaused)
				return;

			Event event;
			while (window->pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window->close();
				}
				//if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) // Mit erneutem ESC-Druck wieder in Anfangs-whileschleife in Game.cpp
				//{
				//	return;
				//}


			}


			//Hier wird der Text angezeigt, text1 ist Überschrift, text2 ist Beschreibung (sliderHelper ist die float-Variable für den Slider)
			text1.setString("Pause Menu : \n\n\nLautstärke : " + std::to_string(int(sliderHelper)) + " % \n");
			text2.setString("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Twitter:\n\n\n\n\n\n (Mit Pfeiltasten ändern, links = leiser, rechts = lauter)"); //Die Text-Variablen sind von der Position her gleich angeordnet, oben links im Pause-Fenster, deswegen die ganzen "\n"'s

			if (play == true) {
				play = false;
				return;
			}
			//Pfeiltasten Druck = Änderung Lautstärke
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if (sliderHelper == 0.f)
				{
					sliderHelper = 1.f;
				}
				sliderHelper--;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (sliderHelper == 100.f)
				{
					sliderHelper = 99.f;
				}
				sliderHelper++;
			}
			if (mute == false) {

				if (sliderHelper < 33) {
					mutebtnTexture = res->getButtonVolume(1);
				}
				else if (sliderHelper > 33 && sliderHelper < 66) {
					mutebtnTexture = res->getButtonVolume(2);
				}
				else if (sliderHelper > 66) {
					mutebtnTexture = res->getButtonVolume(3);

				}
			}
			else if (mute == true) {
				mutebtnTexture = res->getButtonVolume(0);
				Game::getInstance()->setMusicVolume(0.f);
			}
			mutebtn.setTexture(*mutebtnTexture);

			/*mousePos = Mouse::getPosition();
			mouse.setPosition(Vector2f(float(mousePos.x),float(mousePos.y)));*/
			if (mute == false) {
				Game::getInstance()->setMusicVolume(sliderHelper);
			}
			volumeSlider.setSize(Vector2f(sliderHelper / 100 * 400.f, 14.f)); //Hier berechne ich mit Prozentrechnung aus dem Grundwert und dem Prozentsatz den Prozentwert
			Game::getInstance()->changeBackgroundMusic(); //Da die Musik weiterlaufen soll, muss man die hier auch aufrufen
			click();
			draw(); //Texte und Objekte werden gezeichnet

		}
	}
}
void PauseMenu::checkPause()
{
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
		text1.setString("Pause Menu : \n\n\nLautstärke : " + std::to_string(int(sliderHelper)) + " % \n");
		text2.setString("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Twitter:\n\n\n\n\n\n (Mit Pfeiltasten ändern, links = leiser, rechts = lauter)"); //Die Text-Variablen sind von der Position her gleich angeordnet, oben links im Pause-Fenster, deswegen die ganzen "\n"'s

		if (play == true) {
			play = false;
			return;
		}

		//Pfeiltasten Druck = Änderung Lautstärke
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (sliderHelper == 0.f)
			{
				sliderHelper = 1.f;
			}
			sliderHelper--;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (sliderHelper == 100.f)
			{
				sliderHelper = 99.f;
			}
			sliderHelper++;
		}

		if (mute == false) {

			if (sliderHelper < 33) {
				mutebtnTexture = res->getButtonVolume(1);
			}
			else if (sliderHelper > 33 && sliderHelper < 66) {
				mutebtnTexture = res->getButtonVolume(2);
			}
			else if (sliderHelper > 66) {
				mutebtnTexture = res->getButtonVolume(3);

			}
		}
		else {
			mutebtnTexture = res->getButtonVolume(0);
			Game::getInstance()->setMusicVolume(0.f);
		}
		mutebtn.setTexture(*mutebtnTexture);

		/*mousePos = Mouse::getPosition();
		mouse.setPosition(Vector2f(float(mousePos.x),float(mousePos.y)));*/
		if (mute == false) {
			Game::getInstance()->setMusicVolume(sliderHelper);
		}
		volumeSlider.setSize(Vector2f(sliderHelper / 100 * 400.f, 14.f)); //Hier berechne ich mit Prozentrechnung aus dem Grundwert und dem Prozentsatz den Prozentwert
		Game::getInstance()->changeBackgroundMusic(); //Da die Musik weiterlaufen soll, muss man die hier auch aufrufen
		click();
		draw(); //Texte und Objekte werden gezeichnet

	}


	return;

}
#pragma endregion

#pragma region getter
PauseMenu* PauseMenu::getInstance() {

	if (instance == nullptr) {

		instance = new PauseMenu();

	}

	return instance;

}
float PauseMenu::getSliderHelper()
{
	return sliderHelper;
}
void PauseMenu::setMultiplayerIsPaused(bool a)
{
	multiplayerIsPaused = a;
}
bool PauseMenu::getMultiplayerIsPaused()
{
	return multiplayerIsPaused;
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
#pragma endregion

#pragma region setter
void PauseMenu::setSliderHelper(float i)
{
	sliderHelper = i;
}
#pragma endregion

#pragma region Desturktor

#pragma endregion