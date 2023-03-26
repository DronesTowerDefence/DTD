#include "Multiplayer.h"
#include "PauseMenu.h"
#include "Controls.h"
#include <iostream>


PauseMenu* PauseMenu::instance = nullptr;

#pragma region Konstruktor
PauseMenu::PauseMenu() {

	window = Game::getInstance()->getWindow();

	res = Ressources::getInstance();

	//Ich kann nicht auf die Font in Game zugreifen (unerkl�rbarer Error mit wherenode) also deklariere ich die Font nochmal selbst
	font.loadFromFile("fonts/arial.ttf");

	//Rahmen f�r das Pause-Menu
	edge.setFillColor(Color::Blue);
	edge.setSize(Vector2f(690.f, 700.f));
	edge.setPosition(548.f, 148.f);

	musicSlider.setFillColor(Color::Green);
	musicSlider.setSize(Vector2f(400.f, 15.f));
	musicSlider.setPosition(Vector2f(565.f, 390.f));

	sfxSlider.setFillColor(Color::Green);
	sfxSlider.setSize(Vector2f(400.f, 15.f));
	sfxSlider.setPosition(565.f, 640.f); // +150 auf der y-Achse


	//Anfangslautst�rke betr�gt 50%
	sliderHelperMusic = 50.f;
	sliderHelperSound = 50.f;

	//f�r Maus-Click
	isClicked = false;
	play = false;
	mute = false;
	multiplayerIsPaused = false;

	background.setTexture(*res->getPauseScreenBackgroundTexture());
	background.setPosition(530.f, 150.f);
	background.setScale(Vector2f(float(1.36), float(0.7)));

	//Socials
	twitter = new Button(Vector2f(1130.f, 175.f), res->getSocialsTwitterTexture(), Vector2f(0.15f, 0.15f));

	socialsBorder.setFillColor(Color::Transparent);
	socialsBorder.setOutlineColor(Color::Black);
	socialsBorder.setOutlineThickness(float(0.77));
	socialsBorder.setSize(Vector2f(100.f, 100.f));
	socialsBorder.setPosition(1120.f, 165.f);

	//Buttons
	homebtn = new Button(Vector2f(630.f, 750.f), res->getButtonHomeTexture());
	playbtn = new Button(Vector2f(1030.f, 750.f), res->getButtonStartTexture());
	mutebtnTexture = res->getButtonVolume(2);
	mutebtn = new Button(Vector2f(1050.f, 475.f), mutebtnTexture);

	//�berschriften
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

	btnoutlines[0].setPosition(homebtn->getPosition());
	btnoutlines[1].setPosition(playbtn->getPosition());
	btnoutlines[2].setPosition(mutebtn->getPosition());

	//

	musicOutline.setFillColor(Color::Transparent);
	musicOutline.setOutlineColor(Color::Black);
	musicOutline.setOutlineThickness(float(1));
	musicOutline.setSize(Vector2f(402.f, 15.f));
	musicOutline.setPosition(musicSlider.getPosition() - Vector2f(1.f, 0.f));

	sfxOutline.setFillColor(Color::Transparent);
	sfxOutline.setOutlineColor(Color::Black);
	sfxOutline.setOutlineThickness(float(1));
	sfxOutline.setSize(Vector2f(402.f, 15.f));
	sfxOutline.setPosition(sfxSlider.getPosition() - Vector2f(1.f, 0.f));

}
#pragma endregion

#pragma region Funktionen
void PauseMenu::click() //WIP (WORK IN PROGRESS), noch nicht in Benutzung
{
	if (!window->hasFocus())
		return;

	mouse = Mouse::getPosition(*window);

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = false;

		//twitter
		if (twitter->checkHover(mouse))
		{
			system("start www.twitter.com/DronesTD");
		}

		//Home Button
		if (homebtn->checkHover(mouse))
		{
			Game::getInstance()->mainMenu();
		}

		//Resume - Button Weiter
		if (playbtn->checkHover(mouse))
		{
			play = true;
			Multiplayer::send(2, false);
		}

		//mute button
		if (mutebtn->checkHover(mouse))
		{
			if (mute == true)
			{
				mute = false;
				return;
			}
			mute = true;
		}
	}

	twitter->checkHover(mouse);
	homebtn->checkHover(mouse);
	playbtn->checkHover(mouse);
	mutebtn->checkHover(mouse);
}
void PauseMenu::draw()
{
	//window->draw(edge);
	//window->draw(*res->getBlackBackgroundSprite());
	window->draw(background);
	window->draw(text1);
	window->draw(text2);
	window->draw(*twitter);
	window->draw(socialsBorder);
	window->draw(*homebtn);
	window->draw(*playbtn);

	window->draw(*mutebtn);

	for (int i = 0; i < 3; i++) {
		window->draw(btnoutlines[i]);
	}


	window->draw(musicSlider);

	window->draw(sfxSlider);

	window->draw(musicOutline);

	window->draw(sfxOutline);

	window->display();

}
void PauseMenu::checkPause(Event* event1)
{
	/*Vector2i mousePos;*/
	if (event1->type == Event::KeyReleased && event1->key.code == Keyboard::Escape) { //�bergebenes Event wird gepr�ft auf ESC-Druck

		Multiplayer::send(2, true);

		while (window->isOpen())  //Fenster wird schon im Konstruktor �bergeben und als Pointer gespeichert
		{

			Event* event = Controls::getEvent();
			while (window->pollEvent(*event))
			{
				if (event->type == Event::Closed)
				{
					window->close();
					exit(0);
				}
				if (event->type == Event::KeyReleased && event->key.code == Keyboard::Escape) // Mit erneutem ESC-Druck wieder in Anfangs-whileschleife in Game.cpp
				{
					Multiplayer::send(2, false);
					return;
				}


			}
			//Hier wird der Text angezeigt, text1 ist �berschrift, text2 ist Beschreibung (sliderHelperMusic ist die float-Variable f�r den Slider)
			text1.setString("Pause Menu : \n\n\nMusiklautst�rke : " + std::to_string(int(sliderHelperMusic)) + " % \n\n\n\n\nSoundlautst�rke : " + std::to_string(int(sliderHelperSound)) + "%");
			text2.setString("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Twitter:\n\n\n\n\n\n (Mit Pfeiltasten �ndern, links = leiser, rechts = lauter)\n\n\n\n\n\n\n\n(Mit Pfeiltasten �ndern, runter = leiser, hoch = lauter)"); //Die Text-Variablen sind von der Position her gleich angeordnet, oben links im Pause-Fenster, deswegen die ganzen "\n"'s

			if (play == true) {
				play = false;
				return;
			}


			//Pfeiltasten Druck = �nderung Lautst�rke
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if (sliderHelperMusic == 0.f)
				{
					sliderHelperMusic = 1.f;
				}
				sliderHelperMusic--;
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (sliderHelperMusic == 100.f)
				{
					sliderHelperMusic = 99.f;
				}
				sliderHelperMusic++;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (sliderHelperSound == 0.f)
				{
					sliderHelperSound = 1.f;
				}
				sliderHelperSound--;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (sliderHelperSound == 100.f)
				{
					sliderHelperSound = 99.f;
				}
				sliderHelperSound++;
			}

			if (mute == false) {

				if ((sliderHelperMusic + sliderHelperSound) / 2 < 33) {
					mutebtnTexture = res->getButtonVolume(1);
				}
				else if ((sliderHelperMusic + sliderHelperSound) / 2 > 33 && (sliderHelperMusic + sliderHelperSound) / 2 < 66) {
					mutebtnTexture = res->getButtonVolume(2);
				}
				else if ((sliderHelperMusic + sliderHelperSound) / 2 > 66) {
					mutebtnTexture = res->getButtonVolume(3);

				}
			}
			else if (mute == true) {
				mutebtnTexture = res->getButtonVolume(0);
				res->setSfxVolumeRessources(0.0f);
				res->setMusicVolume(0.0f);
			}
			mutebtn->setTexture(mutebtnTexture);

			/*mousePos = Mouse::getPosition();
			mouse.setPosition(Vector2f(float(mousePos.x),float(mousePos.y)));*/
			if (mute == false) {
				res->setSfxVolumeRessources(sliderHelperSound);
				res->setMusicVolume(sliderHelperMusic);
			}
			musicSlider.setSize(Vector2f(sliderHelperMusic / 100 * 400.f, 14.f));//Hier berechne ich mit Prozentrechnung aus dem Grundwert und dem Prozentsatz den Prozentwert
			sfxSlider.setSize(Vector2f(sliderHelperSound / 100 * 400.f, 14.f));//""
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
		while (window->isOpen())  //Fenster wird schon im Konstruktor �bergeben und als Pointer gespeichert
		{
			Multiplayer::receive();

			if (!multiplayerIsPaused)
				return;

			Event* event = Controls::getEvent();
			while (window->pollEvent(*event))
			{
				if (event->type == Event::Closed)
				{
					window->close();
					exit(0);
				}
				//if (event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) // Mit erneutem ESC-Druck wieder in Anfangs-whileschleife in Game.cpp
				//{
				//	return;
				//}


			}


			//Hier wird der Text angezeigt, text1 ist �berschrift, text2 ist Beschreibung (sliderHelperMusic ist die float-Variable f�r den Slider)
			text1.setString("Pause Menu : \n\n\nMusiklautst�rke : " + std::to_string(int(sliderHelperMusic)) + " % \n\n\n\n\nSoundlautst�rke : " + std::to_string(int(sliderHelperSound)) + "%");
			text2.setString("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Twitter:\n\n\n\n\n\n (Mit Pfeiltasten �ndern, links = leiser, rechts = lauter)\n\n\n\n\n\n\n\n(Mit Pfeiltasten �ndern, runter = leiser, hoch = lauter)"); //Die Text-Variablen sind von der Position her gleich angeordnet, oben links im Pause-Fenster, deswegen die ganzen "\n"'s

			if (play == true) {
				play = false;
				return;
			}


			//Pfeiltasten Druck = �nderung Lautst�rke
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				if (sliderHelperMusic == 0.f)
				{
					sliderHelperMusic = 1.f;
				}
				sliderHelperMusic--;
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				if (sliderHelperMusic == 100.f)
				{
					sliderHelperMusic = 99.f;
				}
				sliderHelperMusic++;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				if (sliderHelperSound == 0.f)
				{
					sliderHelperSound = 1.f;
				}
				sliderHelperSound--;
			}

			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (sliderHelperSound == 100.f)
				{
					sliderHelperSound = 99.f;
				}
				sliderHelperSound++;
			}

			if (mute == false) {

				if ((sliderHelperMusic + sliderHelperSound) / 2 < 33) {
					mutebtnTexture = res->getButtonVolume(1);
				}
				else if ((sliderHelperMusic + sliderHelperSound) / 2 > 33 && (sliderHelperMusic + sliderHelperSound) / 2 < 66) {
					mutebtnTexture = res->getButtonVolume(2);
				}
				else if ((sliderHelperMusic + sliderHelperSound) / 2 > 66) {
					mutebtnTexture = res->getButtonVolume(3);

				}
			}
			else if (mute == true) {
				mutebtnTexture = res->getButtonVolume(0);
				res->setSfxVolumeRessources(0.0f);
				res->setMusicVolume(0.0f);
			}
			mutebtn->setTexture(mutebtnTexture);

			/*mousePos = Mouse::getPosition();
			mouse.setPosition(Vector2f(float(mousePos.x),float(mousePos.y)));*/
			if (mute == false) {
				res->setSfxVolumeRessources(sliderHelperSound);
				res->setMusicVolume(sliderHelperMusic);
			}
			musicSlider.setSize(Vector2f(sliderHelperMusic / 100 * 400.f, 14.f));//Hier berechne ich mit Prozentrechnung aus dem Grundwert und dem Prozentsatz den Prozentwert
			sfxSlider.setSize(Vector2f(sliderHelperSound / 100 * 400.f, 14.f));//""
			Game::getInstance()->changeBackgroundMusic(); //Da die Musik weiterlaufen soll, muss man die hier auch aufrufen
			click();
			draw(); //Texte und Objekte werden gezeichnet

		}
	}

	return;

}
void PauseMenu::checkPause()
{
	while (window->isOpen())  //Fenster wird schon im Konstruktor �bergeben und als Pointer gespeichert
	{

		Event* event = Controls::getEvent();
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			if (event->type == Event::KeyReleased && event->key.code == Keyboard::Escape) { // Mit erneutem ESC-Druck wieder in Anfangs-whileschleife in Game.cpp
				return;
			}



		}
		//Hier wird der Text angezeigt, text1 ist �berschrift, text2 ist Beschreibung (sliderHelperMusic ist die float-Variable f�r den Slider)
		text1.setString("Pause Menu : \n\n\nMusiklautst�rke : " + std::to_string(int(sliderHelperMusic)) + " % \n\n\n\n\nSoundlautst�rke : " + std::to_string(int(sliderHelperSound)) + "%");
		text2.setString("\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   Twitter:\n\n\n\n\n\n (Mit Pfeiltasten �ndern, links = leiser, rechts = lauter)\n\n\n\n\n\n\n\n(Mit Pfeiltasten �ndern, runter = leiser, hoch = lauter)"); //Die Text-Variablen sind von der Position her gleich angeordnet, oben links im Pause-Fenster, deswegen die ganzen "\n"'s

		if (play == true) {
			play = false;
			return;
		}


		//Pfeiltasten Druck = �nderung Lautst�rke
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (sliderHelperMusic == 0.f)
			{
				sliderHelperMusic = 1.f;
			}
			sliderHelperMusic--;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (sliderHelperMusic == 100.f)
			{
				sliderHelperMusic = 99.f;
			}
			sliderHelperMusic++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (sliderHelperSound == 0.f)
			{
				sliderHelperSound = 1.f;
			}
			sliderHelperSound--;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (sliderHelperSound == 100.f)
			{
				sliderHelperSound = 99.f;
			}
			sliderHelperSound++;
		}

		if (mute == false) {
			if ((sliderHelperMusic + sliderHelperSound) / 2 < 33) {
				mutebtnTexture = res->getButtonVolume(1);
			}
			else if ((sliderHelperMusic + sliderHelperSound) / 2 > 33 && (sliderHelperMusic + sliderHelperSound) / 2 < 66) {
				mutebtnTexture = res->getButtonVolume(2);
			}
			else if ((sliderHelperMusic + sliderHelperSound) / 2 > 66) {
				mutebtnTexture = res->getButtonVolume(3);

			}
		}
		else if (mute == true) {
			mutebtnTexture = res->getButtonVolume(0);
			res->setSfxVolumeRessources(0.0f);
			res->setMusicVolume(0.0f);
		}
		mutebtn->setTexture(mutebtnTexture);

		/*mousePos = Mouse::getPosition();
		mouse.setPosition(Vector2f(float(mousePos.x),float(mousePos.y)));*/
		if (mute == false) {
			res->setSfxVolumeRessources(sliderHelperSound);
			res->setMusicVolume(sliderHelperMusic);
		}
		musicSlider.setSize(Vector2f(sliderHelperMusic / 100 * 400.f, 14.f));//Hier berechne ich mit Prozentrechnung aus dem Grundwert und dem Prozentsatz den Prozentwert
		sfxSlider.setSize(Vector2f(sliderHelperSound / 100 * 400.f, 14.f));//""
		Game::getInstance()->changeBackgroundMusic(); //Da die Musik weiterlaufen soll, muss man die hier auch aufrufen
		click();
		draw(); //Texte und Objekte werden gezeichnet

	}



}
#pragma endregion

#pragma region getter
PauseMenu* PauseMenu::getInstance() {

	if (instance == nullptr) {

		instance = new PauseMenu();

	}

	return instance;

}
float PauseMenu::getsliderHelperMusic()
{
	return sliderHelperMusic;
}
float PauseMenu::getSliderHelperSound()
{
	return sliderHelperSound;
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
void PauseMenu::setsliderHelperMusic(float a)
{
	if (a >= 0 && a <= 100)
	{
		sliderHelperMusic = a;
	}
}
void PauseMenu::setSliderHelperSound(float a)
{
	if (a >= 0 && a <= 100)
	{
		sliderHelperSound = a;
	}
}
#pragma endregion

#pragma region Desturktor

#pragma endregion