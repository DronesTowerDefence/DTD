#include "ShopContent.h"
#include "HomeMenu.h"
#include <fstream>

std::list<ShopContentData*> ShopContentData::allShopContentData;

ShopContentData::ShopContentData(int id, int cost, std::string name, int type, int typeType, Texture* _texture)
{
	if (_texture->getSize().x == 0 && _texture->getSize().y == 0)
	{
		delete this;
		return;
	}
	m_isBought = false;
	m_isEquiped = false;
	m_id = id;
	m_cost = cost;
	m_name = name;
	m_typ = type;
	m_typTypID = typeType;
	texture = _texture;
	allShopContentData.push_back(this);
	new ShopContentTexture(this);
}

bool ShopContentData::createShopContentDataFromFile()
{
	std::ifstream file;
	file.open("data/shopContent.dronestd");
	if (file.fail())
	{
		std::cout << " Fehler beim Laden der Shop-Daten, Datei nicht gefunden.\n";
		return false;
	}

	bool loadTextureSuccessfull = false;
	int _id = 0, _cost = 0, _type = 0, _typeType = 0, pos1 = 0, pos2 = 0;
	std::string _name, str;
	char buffer[50];
	Texture* _texture = nullptr;

	for (int i = 0; i < shopContentCount; i++, pos1 = 0, pos2 = 0, _id = 0, _name = "", _texture = nullptr, _cost = 0)
	{
		file.getline(buffer, 50);
		str = buffer;

		pos1 = str.find(';');
		_id = stoi(str.substr(0, pos1));

		pos2 = str.find(';', pos1 + 1);
		_name = str.substr(pos1 + 1, pos2 - pos1 - 1);

		pos1 = str.find(';', pos2 + 1);
		_cost = stoi(str.substr(pos2 + 1, pos1 - pos2 - 1));

		pos2 = str.find(';', pos1 + 1);
		_type = stoi(str.substr(pos1 + 1, pos2 - pos1 - 1));

		pos1 = str.find(';', pos2 + 1);
		_typeType = stoi(str.substr(pos2 + 1, pos1 - pos2 - 1));

		_texture = new Texture();
		if (_type == 0) // Tower
		{
			loadTextureSuccessfull = _texture->loadFromFile("img/shop/shopContentTextures/content" + std::to_string(i) + "/tower_preview.png");
		}
		else if (_type == 1) // Drone
		{
			loadTextureSuccessfull = _texture->loadFromFile("img/shop/shopContentTextures/content" + std::to_string(i) + "/drone_1.png");
		}
		else if (_type == 2) // Projectile
		{
			loadTextureSuccessfull = _texture->loadFromFile("img/shop/shopContentTextures/content" + std::to_string(i) + "/projectile.png");
		}

		if (loadTextureSuccessfull)
		{
			new ShopContentData(_id, _cost, _name, _type, _typeType, _texture);
		}
	}

	file.close();

	return (ShopContentData::allShopContentData.size() == shopContentCount);
}

bool ShopContentData::loadBoughtFromServerString(std::string str)
{
	if (str != "0" && str != "-1")
	{
		int _id = 0, pos1 = 0, pos2 = 0;
		while (str.length() > pos2)
		{
			pos1++;
			pos1 = str.find('&', pos1);
			_id = stoi(str.substr(pos2, pos1 - pos2));
			pos2 = pos1 + 1;

			for (auto i : allShopContentData)
			{
				if (i->m_id == _id)
				{
					i->setIsBought(true);
					break;
				}
			}

		}

		ShopGUI::removeBoughtContent();
		return true;
	}
	else return false;
}

void ShopContentData::setIsBought(bool b)
{
	m_isBought = b;
}

void ShopContentData::setIsEquiped(bool b)
{
	m_isEquiped = b;
}

bool ShopContentData::getIsBought()
{
	return m_isBought;
}

bool ShopContentData::getIsEquiped()
{
	return m_isEquiped;
}

int ShopContentData::getCost()
{
	return m_cost;
}

int ShopContentData::getID()
{
	return m_id;
}

int ShopContentData::getType()
{
	return m_typ;
}

int ShopContentData::getTypeType()
{
	return m_typTypID;
}

std::string ShopContentData::getName()
{
	return m_name;
}

Texture* ShopContentData::getTexture()
{
	return texture;
}

std::list<ShopContentData*> ShopContentData::getAllShopContentData()
{
	return allShopContentData;
}



ShopContentTexture::ShopContentTexture(ShopContentData* scd)
{
	p_shopContentData = scd;

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	headlineText = new Text();
	headlineText->setFont(*font);
	headlineText->setPosition(10, 0);
	headlineText->setString(p_shopContentData->getName());
	headlineText->setCharacterSize(30);
	headlineText->setFillColor(Color::White);
	headlineText->setOutlineThickness(3);
	headlineText->setOutlineColor(Color::Black);

	costText = new Text();
	costText->setFont(*font);
	costText->setPosition(20, 260);
	costText->setString(std::to_string(p_shopContentData->getCost()) + " Coins");
	costText->setCharacterSize(30);
	costText->setFillColor(Color::White);
	costText->setOutlineThickness(3);
	costText->setOutlineColor(Color::Black);

	boughtSprite = new Sprite();
	boughtSprite->setPosition(0, 50);
	if (scd->getIsBought())
	{
		boughtSprite->setTexture(*Ressources::getInstance()->getAchievementEarnedNotSymbolTexture());
	}

	//boughtSprite->setTexture(*Ressources::getInstance()->getAchievementEarnedYesSymbolTexture());


	contentSprite = new Sprite();
	contentSprite->setTexture(*p_shopContentData->getTexture());
	contentSprite->setPosition(0, 50);
	contentSprite->setScale(4, 4);


	texture = new RenderTexture();
	texture->create(300, 300);

	texture->draw(*headlineText);
	if (scd->getIsBought())
	{
		texture->draw(*boughtSprite);
	}
	else
	{
		texture->draw(*costText);
	}
	texture->draw(*contentSprite);
	texture->display();

	sprite = new Sprite();
	sprite->setTexture(texture->getTexture());
	sprite->setPosition
	(
		startPositionX + texture->getSize().x * (scd->getID() % contentsPerRow) + distanceToNextSprite, // X-Position
		scd->getID() / contentsPerRow * (texture->getSize().y + distanceToNextSprite) + startPositionY // Y-Position
	);

	HomeMenu::getInstance()->getShopGUI()->addShopContent(this);
}

void ShopContentTexture::updateSpritePosition(int listIndex)
{
	sprite->setPosition
	(
		startPositionX + texture->getSize().x * (listIndex % contentsPerRow) + distanceToNextSprite, // X-Position
		listIndex / contentsPerRow * (texture->getSize().y + distanceToNextSprite) + startPositionY // Y-Position
	);
}

Sprite* ShopContentTexture::getSprite()
{
	return sprite;
}

ShopContentData* ShopContentTexture::getShopContentData()
{
	return p_shopContentData;
}
