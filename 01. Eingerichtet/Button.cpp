#include "Button.h"
using namespace sf;
Button::Button(Vector2f size, Vector2f position, std::string image)
{

	sprite = Sprite();
	texture = Texture();
	texture.loadFromFile(image);
	this->size = size; 
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

bool Button::isClicked(Vector2i mouse)
{
	auto a = sprite.getPosition();
	if (mouse.x >= sprite.getPosition().x && mouse.x <= sprite.getPosition().x + size.x &&
		mouse.y >= sprite.getPosition().y && mouse.y <= sprite.getPosition().y + size.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Sprite Button::getSprite()
{
	return sprite;
}
