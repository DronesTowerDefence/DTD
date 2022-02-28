#include<SFML/Graphics.hpp>
#include<string>
using namespace sf; // statt std, hat zur Folge, dass bei String etc. std:: vor gesetzt werden muss

int main() {
	// 1. Spielfenster mit allen Objekten anfelgen
	int score = 0; // wie oft wird der Ball getroffen
	int mx = 0;    // Flugrichtung x- Achse >> -5 nach links; +5 nach rechts
	int my = 0;    // Flugrichtung y- Achse >> -5 nach oben;  +5 nach unten
	int speed = 5; // speed vom Ball

	// Spielefenster erstellen
	RenderWindow window(VideoMode(300, 500), "Pong");   // Fenstergröße 300x breit x 500y hoch Pixel
	window.setFramerateLimit(30);                       // Bilder pro Sekunde

	// Schriftart für die Punktzahl festlegen
	Font font;
	font.loadFromFile("fonts/arial.ttf"); // muss in aktuellen Projektordner liegen

    // Label erstellen (Punktzahl anzeigen)
	Text text("", font);
	text.setString(std::to_string(score)); // to_string wandelt int in ein string um 
										   // std:: ist im namensraum sf nicht definiert
	text.setCharacterSize(30);

	// Erstellt ein Kreis, um den Ball darzustellen
	CircleShape ball(5);
	ball.setFillColor(Color::Green);        // Klassenmethode, es muss kein Objekt von der Klasse Color erzeugt werden 
	ball.setPosition(145, 100);             // Standardmäßig werden Objekte relativ zu ihrer oberen linken Ecke positioniert. 

	// Erstellt ein Rechteck, um den Spieler darzustellen
	RectangleShape player(Vector2f(40, 10)); // (x, y) 40 breit, 10 hoch
	player.setFillColor(Color::Red);
	player.setPosition(130, 400);			// 300/2 Bildmitte - 20 Playermitte = 130 Player auf x-Achse

	// Debug >> Positionen auslesen
	Text position("", font);
	position.setCharacterSize(15);

	// 2. Game Loop >> sich wiederholender Spielablauf
	while (window.isOpen()) {     // Game wird beendet, wenn das Fenster geschlossen wird 

		// Ball- und 
		Vector2f ballPos = ball.getPosition();	   // Ball-Position (x,y)
		Vector2f playerPos = player.getPosition(); // Player-Position (x,y)

		// Bildbegrenzung für den Ball
		if (ballPos.x <= 0)	// wenn der Ball die Linke y-Achse trifft
			mx = speed;		// dann ändere speed für die x-Achse von -5 auf +5				
		else if (ballPos.x >= 300 - 5)	// wenn der Ball die Rechte y-Achse trifft
			mx = -speed;				// dann ändere speed für die x-Achsevon +5 auf -5 
		if (ballPos.y <= 0) 
			my = speed;					
		else if (ballPos.y >= 400 - 5) { // wenn der Ball den "Boden" trifft
			my = 0;						 // dann soll er stoppen		
			mx = 0;
		}

		// Ballkollision mit dem Player 
		if (ballPos.x >= playerPos.x		// wenn der Ball links vom Player ist
			&&								// und
			ballPos.x <= playerPos.x + 40)	// wenn der Ball rechts vom Player ist

			if (ballPos.y >= playerPos.y - 5) { // und der Ball am "Boden" ist
				score++;						// Player hat Ball getroffen	
				text.setString(std::to_string(score));
				my = -speed;					// Ball steigt auf -5	
			}
		
		// Debug Ausgabe
		position.setPosition(10, 450); // x, y  Pixel nach recht, Pixle nach unten
		position.setString(	"    Ball: X " + std::to_string((int)ballPos.x) + " Y " + std::to_string((int)ballPos.y) + '\n' +
							"Player: X " + std::to_string((int)playerPos.x) + " Y " + std::to_string((int)playerPos.y) + '\n' +
							"Speed: X " + std::to_string(mx) + " Y " + std::to_string(my)); // Debug-Ausgabe
		
		
		ball.move(mx, my); //Ball Bewegung >> Verschiebt das Objekt um einen bestimmten Offset.

		// Tastatur auslesen
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			mx = speed;
			my = speed;
		}

		// Player-Bedienung über die Tastatur
		if (Keyboard::isKeyPressed(Keyboard::Left))
			if (playerPos.x > 0)		// Bildbegrenzung nach links
				player.move(-speed, 0);	// y-Achse == 0
		if (Keyboard::isKeyPressed(Keyboard::Right))
			if (playerPos.x < 300 - 40) // Bildbegrenzung nach rechts
				player.move(speed, 0);

		// Überprüft, ob das Fenster geschlossen wird
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

		// aktualisiert das Bild
		window.clear();
		window.draw(ball);
		window.draw(player);
		window.draw(text);
		window.draw(position);
		window.display();
	}
	return 0;
}