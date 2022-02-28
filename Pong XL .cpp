#include <SFML/Graphics.hpp> //Einbinden von Library (SFML-Graphics) nur für Grafiken
#include <iostream>
//SFML 2.5.1

int windowSizeX = 750, windowSizeY = 450;
int pongSizeX = 40, pongSizeY = 40;
int pongMinSize = 10;
int pongStdSize = 40;
int player1SizeX = 20, player1SizeY = 100, player2SizeX = 20, player2SizeY = 100;
bool started = false; //Gibt an ob das Spiel gestartet wurde
float pongVelocity = 0; //Ball Geschwindigkeit
float pongStdVelocity = 400;
float acceleration = 15;
float playerVelocity = 800; //Spieler Geschwindigkeit
int player1Score = 0; 
int player2Score = 0;
int collisions = 0;
float pongVelX = pongStdVelocity;
float pongVelY = pongStdVelocity;


sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Ping-Pong");
sf::RectangleShape pong(sf::Vector2f(pongSizeX, pongSizeY));
sf::RectangleShape player1(sf::Vector2f(player1SizeX, player1SizeY));
sf::RectangleShape player2(sf::Vector2f(player2SizeX, player2SizeY));
sf::RectangleShape borderTop(sf::Vector2f(0, 0));
sf::RectangleShape borderBot(sf::Vector2f(0, 0));
sf::RectangleShape borderLeft(sf::Vector2f(0, 0));
sf::RectangleShape borderRight(sf::Vector2f(0, 0));
sf::Text score;
sf::Text collisionsText;
float dt = 0;
sf::Font stdFont;

//Kollisonsabfrage zwischen zwei Rechtecken
bool collisionRect(sf::RectangleShape p1, sf::RectangleShape p2) {
	if (p1.getPosition().x < p2.getPosition().x + p2.getSize().x) {
		if (p1.getPosition().y < p2.getPosition().y + p2.getSize().y) {
			if (p1.getPosition().x + p1.getSize().x > p2.getPosition().x) {
				if (p1.getPosition().y + p1.getSize().y > p2.getPosition().y) {
					//sobald sie in eineinader liegen würden wird true zurückgegeben
					return true;
				}
			}
		}
	}
	return false;
}

void updatePlayer() {
	//Überprüft die Kollision zwischen Spieler und dem oberen bzw. unteren Rand
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { //Überprüft ob die Taste (UP bzw. Pfeil nach oben) gedrückt wurde
		if (false == collisionRect(player2, borderTop)) {
			player2.move(sf::Vector2f(0.f, -playerVelocity) * dt);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (false == collisionRect(player2, borderBot)) {
			player2.move(sf::Vector2f(0.f, playerVelocity) * dt);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (false == collisionRect(player1, borderTop)) {
			player1.move(sf::Vector2f(0.f, -playerVelocity) * dt);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (false == collisionRect(player1, borderBot)) {
			player1.move(sf::Vector2f(0.f, playerVelocity) * dt);
		}
	}
}

void updatePong() {
	sf::Event anyKeyPressed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		started = true; //Spiel startet erst sobald man die Leertaste drückt
	}
	if (started == true) {
		//anpassen der Geschwindigkeit
		pong.move(pongVelX * dt, pongVelY * dt);
		//Abfrage der Kollision zwischen den einzelnen der Wand und dem Ball(Pong)
		if (collisionRect(pong, player1) == true) {
			//Je nach dem aus welcher richtung der Ball kommt wird dieser in die entgegen gesetzte zurückgelenkt, indem die Geschwindigkeit negativ gesetzt wird.
			pongVelX = pongVelocity;
			collisions++;
			//std::cout << collisions << std::endl;
			//std::cout << pongVelocity << std::endl;
			//std::cout << pongSizeX << std::endl;
			pong.setPosition(sf::Vector2f(pong.getPosition().x + 21, pong.getPosition().y + 21));
			pongVelocity = pongVelocity + acceleration;
			if (pongSizeX >= pongMinSize && pongSizeX >= pongMinSize) {
				pongSizeX--;
				pongSizeY--;
				pong.setSize(sf::Vector2f(pongSizeX, pongSizeY));
			}
		}
		if (collisionRect(pong, player2) == true) {
			pongVelX = -pongVelocity;
			collisions++;
			//std::cout << collisions << std::endl;
			//std::cout << pongVelocity << std::endl;
			//std::cout << pongSizeX << std::endl;
			pong.setPosition(sf::Vector2f(pong.getPosition().x - 21, pong.getPosition().y - 21));
			pongVelocity = pongVelocity + acceleration;
			if (pongSizeX >= pongMinSize && pongSizeX >= pongMinSize) {
				pongSizeX--;
				pongSizeY--;
				pong.setSize(sf::Vector2f(pongSizeX, pongSizeY));
			}
		}
		if (collisionRect(pong, borderTop) == true) {
				pongVelY = pongVelocity;
		}
		if (collisionRect(pong, borderBot) == true) {
				pongVelY = -pongVelocity;
		}
		//Kollision mit Linken und Rechten Rand
		//Bei aufprall reset vom Ball und Punkt für den jeweiligen Spieler
		if (collisionRect(pong, borderLeft) == true) {
			player2Score = player2Score + 1;
			pongVelocity = pongStdVelocity;
			pongVelX = pongVelocity;
			pongVelY = pongVelocity;
			collisions = 0;
			collisionsText.setString("Bounces: " + std::to_string(collisions));
			pong.setSize(sf::Vector2f(pongStdSize, pongStdSize));
			pongSizeX = pongStdSize;
			pongSizeY = pongStdSize;
			pong.setPosition(sf::Vector2f(windowSizeX / 2 - pongSizeX / 2, windowSizeY / 2 - pongSizeY / 2));
			started = false;
		}
		if (collisionRect(pong, borderRight) == true) {
			player1Score = player1Score + 1;
			pongVelocity = pongStdVelocity;
			pongVelX = -pongVelocity;
			pongVelY = -pongVelocity;
			pongSizeX = pongStdSize;
			pongSizeY = pongStdSize;
			collisions = 0;
			collisionsText.setString("Bounces: " + std::to_string(collisions));
			pong.setSize(sf::Vector2f(pongStdSize, pongStdSize));
			pong.setPosition(sf::Vector2f(windowSizeX / 2 - pongSizeX / 2, windowSizeY / 2 - pongSizeY / 2));
			started = false;
		}
	}
}

int main()
{
	//Deklaration aller Parameter
	player1Score = 0;
	player2Score = 0;
	sf::Clock clock;
	sf::Time time;
	

	player1.setPosition(sf::Vector2f(windowSizeX/20 - player1SizeX, windowSizeY / 2 - player1SizeY/2)); //Position der Spieler wird relativ zur Fenstergrößen festgelegt
	player2.setPosition(sf::Vector2f(windowSizeX - windowSizeX / 20, windowSizeY / 2 - player2SizeY / 2));
	pong.setPosition(sf::Vector2f(windowSizeX / 2 - pongSizeX/2, windowSizeY / 2 - pongSizeY/2)); //Ball wird zentriert
	borderTop.setSize(sf::Vector2f(windowSizeX, 50));
	borderBot.setSize(sf::Vector2f(windowSizeX, 50));
	borderTop.setPosition(sf::Vector2f(0, -50));
	borderBot.setPosition(sf::Vector2f(0, windowSizeY));

	pongVelocity = pongStdVelocity;

	borderLeft.setSize(sf::Vector2f(50, windowSizeY));
	borderRight.setSize(sf::Vector2f(50, windowSizeY));
	borderLeft.setPosition(sf::Vector2f(-50, 0));
	borderRight.setPosition(sf::Vector2f(windowSizeX, 0));

	
	score.setFont(stdFont);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::White);
	score.setStyle(sf::Text::Bold);
	score.setPosition(sf::Vector2f(windowSizeX / 2 - windowSizeX / 25, windowSizeY / 20));

	collisionsText.setFont(stdFont);
	collisionsText.setCharacterSize(20);
	collisionsText.setFillColor(sf::Color::White);
	collisionsText.setStyle(sf::Text::Bold);
	collisionsText.setPosition(sf::Vector2f(windowSizeX / 2 - windowSizeX / 12, windowSizeY / 8));

	stdFont.loadFromFile("assets/standartFont.ttf");

	while (window.isOpen())//Wenn Fenster offen ist
	{
		sf::Event eventClose;//jegliches Event z.B Tastatur Eingabe
		while (window.pollEvent(eventClose)) //Abfrage Event in while schleife
		{
			if (eventClose.type == sf::Event::Closed)//Abfrage X-Button gedrückt; Closed ist ein Enum
				window.close();//Fenster schließen
		}
		//Update Methoden in Delta Time
		
		updatePlayer();
		updatePong();
		
		time = clock.restart();
		dt = time.asSeconds();

		score.setString(std::to_string(player1Score) + ":" + std::to_string(player2Score));
		collisionsText.setString("Bounces: " + std::to_string(collisions));

		window.clear();//Fenster wird geleert 
		//Einzelne Shapes werden gezeichnet
		window.draw(score);
		window.draw(collisionsText);
		window.draw(pong);
		window.draw(player1);
		window.draw(player2);
		window.draw(borderTop);
		window.draw(borderBot);
		window.draw(borderLeft);
		window.draw(borderRight);

		//Fenster wird angezeigt
		window.display();
	}	


	return 0;
}

