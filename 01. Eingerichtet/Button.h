#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
class Button
{
private:
	Sprite sprite;
	Texture texture;
	Vector2f size;
	Button();
public:
	Button(Vector2f size, Vector2f position,  std::string image);
	bool isClicked(Vector2i mouse);
	Sprite getSprite();
};

