#pragma once
#include "Ressources.h"

class Button : public sf::Drawable
{
private:
	Texture* texture;
	Sprite* sprite;
	RectangleShape* hoverShape;
	Color* hoverColor;

	bool drawHover;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = RenderStates::Default) const;

	Button();
public:
	Button(Vector2f position, Texture* texture, Vector2f textureScale = Vector2f(1, 1));
	~Button();

	bool checkHover(Vector2i mousePosition);

	void setTexture(Texture* texture, Vector2f textureScale = Vector2f(1,1));
	bool getIsHover();
	Vector2f getPosition();
};

