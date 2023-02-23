#include "ShopContent.h"
#include "HomeMenu.h"
#include <fstream>


ShopContentData::ShopContentData(int id, int cost, std::string name, int size)
{
	m_id = id;
	m_cost = cost;
	m_name = name;
	m_size = size;
	allShopContentData.push_back(this);
	new ShopContentTexture(this);
}

bool ShopContentData::createShopContentDataFromFile()
{
	std::ifstream file;
	file.open("data/shopContent.sav");
	if (file.fail())
	{
		std::cout << " Fehler beim Laden der Shop-Daten, Datei nicht gefunden.\n";
		return false;
	}

	int _id = 0, _cost = 0, _textureSize = 0, pos1 = 0, pos2 = 0;
	std::string _name, str;
	char buffer[50];

	for (int i = 0; i < shopContentCount; i++, pos1 = 0, pos2 = 0, _id = 0, _name = "", _textureSize = 0, _cost = 0)
	{
		file.getline(buffer, 50);
		str = buffer;

		pos1 = str.find(';');
		_id = stoi(str.substr(0, pos1));

		pos2 = str.find(';', pos1 + 1);
		_name = str.substr(pos1 + 1, pos2 - pos1 - 1);

		pos1 = str.find(';', pos2 + 1);
		_textureSize = stoi(str.substr(pos2 + 1, pos1 - pos2 - 1));

		pos2 = str.find(';', pos1 + 1);
		_cost = stoi(str.substr(pos1 + 1, pos2 - pos1 - 1));

		new ShopContentData(_id, _cost, _name, _textureSize);
	}

	file.close();

	return true;
}

int ShopContentData::getCost()
{
	return m_cost;
}

std::string ShopContentData::getName()
{
	return m_name;
}



ShopContentTexture::ShopContentTexture(ShopContentData* scd)
{
	p_shopContentData = scd;

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	headlineText = new Text();
	headlineText->setFont(*font);
	headlineText->setPosition(100, 50);
	headlineText->setString(p_shopContentData->getName());
	headlineText->setCharacterSize(30);
	headlineText->setFillColor(Color::White);
	headlineText->setOutlineThickness(3);
	headlineText->setOutlineColor(Color::Black);

	costText = new Text();
	costText->setFont(*font);
	costText->setPosition(100, 350);
	costText->setString(std::to_string(p_shopContentData->getCost()) + " Coins");
	costText->setCharacterSize(30);
	costText->setFillColor(Color::White);
	costText->setOutlineThickness(3);
	costText->setOutlineColor(Color::Black);

	spriteTexture = new Texture();
	spriteTexture->loadFromFile("img/tower0/tower0_0.png"); //TODO

	contentSprite = new Sprite();
	contentSprite->setTexture(*spriteTexture);
	contentSprite->setPosition(50, 100);


	texture = new RenderTexture;
	texture->create(800, 400);

	texture->draw(*headlineText);
	texture->draw(*costText);
	texture->draw(*contentSprite);
	texture->display();

	sprite = new Sprite();
	sprite->setTexture(texture->getTexture());
	sprite->setPosition(0, 0);

	HomeMenu::getInstance()->getShopGUI()->addShopContent(this);
}

Sprite* ShopContentTexture::getSprite()
{
	return sprite;
}
