#include "Button.h"
#include "Service.h"

#pragma region Konstruktor/Destruktor
Button::Button(Vector2f _position, Texture* _texture, Vector2f _textureScale)
{
	texture = new Texture(*_texture);

	sprite = new Sprite(*texture);
	sprite->setScale(_textureScale);
	sprite->setPosition(_position);

	hoverColor = new Color(0, 0, 0, 80);

	hoverShape = new RectangleShape();
	hoverShape->setFillColor(*hoverColor);
	hoverShape->setPosition(sprite->getPosition());
	hoverShape->setSize(Vector2f(texture->getSize()));

	drawHover = false;
}
Button::Button(Vector2f position, Vector2f size, Color color)
{
	texture = new Texture();
	texture->create(size.x, size.y);

	sprite = new Sprite(*texture);
	sprite->setPosition(position);
	sprite->setColor(color);

	hoverColor = new Color(0, 0, 0, 80);

	hoverShape = new RectangleShape();
	hoverShape->setFillColor(*hoverColor);
	hoverShape->setPosition(sprite->getPosition());
	hoverShape->setSize(Vector2f(texture->getSize()));

	drawHover = false;
}
Button::~Button()
{
	delete texture;
	delete sprite;
	delete hoverShape;
	delete hoverColor;
}
#pragma endregion

#pragma region Funktionen
bool Button::checkHover(Vector2i mousePosition)
{
	Vector2f pos = Service::getInstance()->getObjectPosition(sprite->getPosition()),
		pos2 = Service::getInstance()->getObjectPosition(sprite->getPosition() + Vector2f(sprite->getTexture()->getSize().x * sprite->getScale().x, sprite->getTexture()->getSize().y * sprite->getScale().y));

	drawHover = ((mousePosition.x >= pos.x && mousePosition.x <= pos2.x) && (mousePosition.y >= pos.y && mousePosition.y <= pos2.y));
	return drawHover;
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
	if (drawHover)
	{
		target.draw(*hoverShape, states);
	}
}
#pragma endregion

#pragma region getter/setter
void Button::setTexture(Texture* _texture, Vector2f _textureScale)
{
	delete texture;
	texture = new Texture(*_texture);

	Vector2f pos = sprite->getPosition();

	delete sprite;
	sprite = new Sprite(*texture);
	sprite->setScale(_textureScale);
	sprite->setPosition(pos);
}
bool Button::getIsHover()
{
	return drawHover;
}
Vector2f Button::getPosition()
{
	return sprite->getPosition();
}
#pragma endregion