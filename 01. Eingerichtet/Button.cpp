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
	Service* service = Service::getInstance();
	Vector2f pos = service->getObjectPosition(Vector2f(1920, 991), sprite.getPosition());
	if (mouse.x >= pos.x && mouse.x <= service->getXPosition(1920, sprite.getPosition().x + size.x) &&
		mouse.y >= pos.y && mouse.y <= service->getYPosition(991, sprite.getPosition().y + size.y))
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