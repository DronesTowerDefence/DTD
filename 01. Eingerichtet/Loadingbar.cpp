#include "Loadingbar.h"
#include <iostream>

Loadingbar::Loadingbar(sf::Vector2f startPos, sf::Vector2f endPos, sf::Color outlineColor, int outlineThickness, sf::Color fillColor)
{
	outline.setPosition(startPos);
	outline.setSize(endPos - startPos);
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineColor(outlineColor);
	outline.setOutlineThickness(outlineThickness);

	loadingShape.setPosition(outline.getPosition());
	loadingShape.setFillColor(fillColor);
	loadingShape.setSize(sf::Vector2f(0, endPos.y - startPos.y));

	percentage = 0.f;

	font = nullptr;
	text = nullptr;
}

void Loadingbar::updateBar()
{
	loadingShape.setSize(sf::Vector2f(percentage / 100 * outline.getSize().x, loadingShape.getSize().y));
	if (text != nullptr)
	{
		text->setString(std::to_string(int(percentage)) + " %");
	}
}

void Loadingbar::draw(sf::RenderTarget* render)
{
	render->draw(outline);
	render->draw(loadingShape);
	if (text != nullptr)
	{
		render->draw(*text);
	}
}

void Loadingbar::setTextStyle(int style, int charSize, sf::Color textColor, sf::Font* textFont)
{
	switch (style)
	{
	case 0:
		if (text != nullptr)
		{
			delete text;
			text = nullptr;
		}
		break;
	case 1:
		font = textFont;
		text = new sf::Text();
		text->setFont(*font);
		text->setCharacterSize(charSize);
		text->setFillColor(textColor);
		text->setString(std::to_string(int(percentage)) + " %");
		text->setPosition(sf::Vector2f((outline.getPosition().x + (outline.getSize().x / 2)) * 0.95, outline.getPosition().y * 1.025));
		break;
	}
}

void Loadingbar::correctTextAlignment(sf::Vector2f correction)
{
	if (text != nullptr)
	{
		if (correction.x != 0)
		{
			text->setPosition(sf::Vector2f((outline.getPosition().x + (outline.getSize().x / 2)) * correction.x, text->getPosition().y));
		}
		if (correction.y != 0)
		{
			text->setPosition(text->getPosition().x, outline.getPosition().y * correction.y);
		}
	}
}

bool Loadingbar::addPercentage(float _percentage)
{
	return setPercentage(percentage + _percentage);
}

bool Loadingbar::setPercentage(float _percentage)
{
	if (_percentage >= 0 && _percentage <= 100)
	{
		percentage = _percentage;
		updateBar();
		return true;
	}
	else return false;
}

float Loadingbar::getPercentage()
{
	return percentage;
}