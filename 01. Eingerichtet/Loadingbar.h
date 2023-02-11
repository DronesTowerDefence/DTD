#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Ein Ladebalken
/// </summary>
class Loadingbar
{
private:
	sf::RectangleShape outline;
	sf::RectangleShape loadingShape;
	sf::Font* font;
	sf::Text* text;
	float percentage;

	void updateBar();
public:

	/// <summary>
	/// Erstellt einen Ladebalken
	/// </summary>
	/// <param name="startPos">Punkt/Ecke oben Links</param>
	/// <param name="endPos">Punkt/Ecke oben Rechts</param>
	/// <param name="outlineColor">Farbe der Umrandung</param>
	/// <param name="outlineThickness">Dicke des Randes</param>
	/// <param name="fillColor">Farbe des Ladebalkens</param>
	Loadingbar(sf::Vector2f startPos, sf::Vector2f endPos, sf::Color outlineColor, int outlineThickness, sf::Color fillColor);

	/// <summary>
	/// Zeichnet den Ladebalken in das angegebene Fenster
	/// </summary>
	/// <param name=""></param>
	void draw(sf::RenderTarget*);

	/// <summary>
	/// Erstellt einen Text im Ladebalken
	/// </summary>
	/// <param name="style">0:Kein Text; 1:Prozentzahl;</param>
	/// <param name="charSize">Buchstaben Größe</param>
	/// <param name="textColor">Farbe des Textes</param>
	/// <param name="textFont">Schriftart des Textes</param>
	void setTextStyle(int style, int charSize, sf::Color textColor, sf::Font* textFont);

	/// <summary>
	/// Passt die Position des Textes um den angegebenen Wert an
	/// </summary>
	/// <param name="correction"></param>
	void correctTextAlignment(sf::Vector2f correction);

	bool addPercentage(float _percentage);
	bool setPercentage(float _percentage);
	float getPercentage();

};

