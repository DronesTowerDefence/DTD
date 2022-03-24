#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
class Button
{
private:
	Button();
protected:

	Sprite sprite;
	Texture texture;
	Vector2f size;
public:
	Button(Vector2f size, Vector2f position,  std::string image);
	/// <summary>
	/// Checkt ob MausPosition innerhalb des Button liegt
	/// </summary>
	/// <param name="mouse">Kooadinaten des Mauszeigers</param>
	/// <returns>ist angeklickt</returns>
	bool isClicked(Vector2i mouse);
	/// <summary>
	/// Gibt den Sprite des Button zurück
	/// </summary>
	/// <returns>Sprite</returns>
	Sprite getSprite();
};

