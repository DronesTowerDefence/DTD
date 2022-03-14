#include <SFML/Graphics.hpp> //Einbinden von Library (SFML-Graphics) nur für Grafiken
#include <iostream>
using namespace sf;
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


  RenderWindow window(  VideoMode(windowSizeX, windowSizeY), "Ping-Pong");
  RectangleShape pong(  Vector2f(pongSizeX, pongSizeY));
  RectangleShape player1(  Vector2f(player1SizeX, player1SizeY));
  RectangleShape player2(  Vector2f(player2SizeX, player2SizeY));
  RectangleShape borderTop(  Vector2f(0, 0));
  RectangleShape borderBot(  Vector2f(0, 0));
  RectangleShape borderLeft(  Vector2f(0, 0));
  RectangleShape borderRight(  Vector2f(0, 0));
  Text score;
  Text collisionsText;
float dt = 0;
  Font stdFont;

//Kollisonsabfrage zwischen zwei Rechtecken
bool collisionRect(  RectangleShape p1,   RectangleShape p2) {
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
	if (  Keyboard isKeyPressed(  Keyboard Up)) { //Überprüft ob die Taste (UP bzw. Pfeil nach oben) gedrückt wurde
		if (false == collisionRect(player2, borderTop)) {
			player2.move(  Vector2f(0.f, -playerVelocity) * dt);
		}
	}
	if (  Keyboard isKeyPressed(  Keyboard Down)) {
		if (false == collisionRect(player2, borderBot)) {
			player2.move(  Vector2f(0.f, playerVelocity) * dt);
		}
	}
	if (  Keyboard isKeyPressed(  Keyboard W)) {
		if (false == collisionRect(player1, borderTop)) {
			player1.move(  Vector2f(0.f, -playerVelocity) * dt);
		}
	}
	if (  Keyboard isKeyPressed(  Keyboard S)) {
		if (false == collisionRect(player1, borderBot)) {
			player1.move(  Vector2f(0.f, playerVelocity) * dt);
		}
	}
}

void updatePong() {
	  Event anyKeyPressed;
	if (  Keyboard isKeyPressed(  Keyboard Space)){
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
			//std cout << collisions << std endl;
			//std cout << pongVelocity << std endl;
			//std cout << pongSizeX << std endl;
			pong.setPosition(  Vector2f(pong.getPosition().x + 21, pong.getPosition().y + 21));
			pongVelocity = pongVelocity + acceleration;
			if (pongSizeX >= pongMinSize && pongSizeX >= pongMinSize) {
				pongSizeX--;
				pongSizeY--;
				pong.setSize(  Vector2f(pongSizeX, pongSizeY));
			}
		}
		if (collisionRect(pong, player2) == true) {
			pongVelX = -pongVelocity;
			collisions++;
			//std cout << collisions << std endl;
			//std cout << pongVelocity << std endl;
			//std cout << pongSizeX << std endl;
			pong.setPosition(  Vector2f(pong.getPosition().x - 21, pong.getPosition().y - 21));
			pongVelocity = pongVelocity + acceleration;
			if (pongSizeX >= pongMinSize && pongSizeX >= pongMinSize) {
				pongSizeX--;
				pongSizeY--;
				pong.setSize(  Vector2f(pongSizeX, pongSizeY));
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
			collisionsText.setString("Bounces: " + std to_string(collisions));
			pong.setSize(  Vector2f(pongStdSize, pongStdSize));
			pongSizeX = pongStdSize;
			pongSizeY = pongStdSize;
			pong.setPosition(  Vector2f(windowSizeX / 2 - pongSizeX / 2, windowSizeY / 2 - pongSizeY / 2));
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
			collisionsText.setString("Bounces: " + std to_string(collisions));
			pong.setSize(  Vector2f(pongStdSize, pongStdSize));
			pong.setPosition(  Vector2f(windowSizeX / 2 - pongSizeX / 2, windowSizeY / 2 - pongSizeY / 2));
			started = false;
		}
	}
}

int main()
{
	//Deklaration aller Parameter
	player1Score = 0;
	player2Score = 0;
	  Clock clock;
	  Time time;
	

	player1.setPosition(  Vector2f(windowSizeX/20 - player1SizeX, windowSizeY / 2 - player1SizeY/2)); //Position der Spieler wird relativ zur Fenstergrößen festgelegt
	player2.setPosition(  Vector2f(windowSizeX - windowSizeX / 20, windowSizeY / 2 - player2SizeY / 2));
	pong.setPosition(  Vector2f(windowSizeX / 2 - pongSizeX/2, windowSizeY / 2 - pongSizeY/2)); //Ball wird zentriert
	borderTop.setSize(  Vector2f(windowSizeX, 50));
	borderBot.setSize(  Vector2f(windowSizeX, 50));
	borderTop.setPosition(  Vector2f(0, -50));
	borderBot.setPosition(  Vector2f(0, windowSizeY));

	pongVelocity = pongStdVelocity;

	borderLeft.setSize(  Vector2f(50, windowSizeY));
	borderRight.setSize(  Vector2f(50, windowSizeY));
	borderLeft.setPosition(  Vector2f(-50, 0));
	borderRight.setPosition(  Vector2f(windowSizeX, 0));

	
	score.setFont(stdFont);
	score.setCharacterSize(30);
	score.setFillColor(  Color White);
	score.setStyle(  Text Bold);
	score.setPosition(  Vector2f(windowSizeX / 2 - windowSizeX / 25, windowSizeY / 20));

	collisionsText.setFont(stdFont);
	collisionsText.setCharacterSize(20);
	collisionsText.setFillColor(  Color White);
	collisionsText.setStyle(  Text Bold);
	collisionsText.setPosition(  Vector2f(windowSizeX / 2 - windowSizeX / 12, windowSizeY / 8));

	stdFont.loadFromFile("assets/standartFont.ttf");

	while (window.isOpen())//Wenn Fenster offen ist
	{
		  Event eventClose;//jegliches Event z.B Tastatur Eingabe
		while (window.pollEvent(eventClose)) //Abfrage Event in while schleife
		{
			if (eventClose.type ==   Event Closed)//Abfrage X-Button gedrückt; Closed ist ein Enum
				window.close();//Fenster schließen
		}
		//Update Methoden in Delta Time
		
		updatePlayer();
		updatePong();
		
		time = clock.restart();
		dt = time.asSeconds();

		score.setString(std to_string(player1Score) + ":" + std to_string(player2Score));
		collisionsText.setString("Bounces: " + std to_string(collisions));

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

