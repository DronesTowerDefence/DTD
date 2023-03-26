#include "SkinsGUI.h"
#include "Service.h"
#include "HomeMenu.h"
#include "Controls.h"

void SkinsGUI::createEquipedSprite(SkinsGUIDisplayedSkin* sgds)
{
	Sprite* sprite = new Sprite();

	sprite->setTexture(*Ressources::getInstance()->getSkinEquipedIconTexture());
	sprite->setPosition(sgds->getSprite()->getPosition());
	sprite->setScale
	(
		sgds->getSprite()->getTexture()->getSize().x / sprite->getTexture()->getSize().x, // X-Scale
		sgds->getSprite()->getTexture()->getSize().y / sprite->getTexture()->getSize().y // Y-Scale
	);

	allEquipedSprites.push_back(sprite);
}

Sprite* SkinsGUI::getEquipedSprite(SkinsGUIDisplayedSkin* sgds)
{
	for (auto i : allEquipedSprites)
	{
		if (i->getPosition() == sgds->getSprite()->getPosition())
			return i;
	}
	return nullptr;
}

bool SkinsGUI::checkClicked()
{
	if (!window->hasFocus())
		return true;

	Vector2i mouse = Mouse::getPosition();

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		Vector2f pos, pos2;
		isClicked = false;

		//Close
		if (closeButton->checkHover(mouse))
		{
			isOpen = false;
			return true;
		}

		//Skin
		for (auto i : allSkinsGUIDisplayedSkins)
		{
			pos = Service::getInstance()->getObjectPosition(i->getSprite()->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(i->getSprite()->getPosition() + Vector2f(i->getSprite()->getTexture()->getSize()));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				ShopContentData* scd = i->getShopContentData();
				if (scd->getIsEquiped())
				{
					scd->setIsEquiped(false);
					allEquipedSprites.remove(getEquipedSprite(i));
					if (scd->getType() == 0)
					{
						Ressources::getInstance()->setDefaultTowerTexture(scd->getTypeType());
					}
					else if (scd->getType() == 3)
					{
						Ressources::getInstance()->setDefaultTowerSpawnTexture(scd->getTypeType());
					}
				}
				else
				{
					scd->setIsEquiped(true);
					createEquipedSprite(i);
					if (scd->getType() == 0)
					{
						Ressources::getInstance()->updateTowerTexture(scd->getTypeType(), scd->getTexture());
					}
					else if (scd->getType() == 3)
					{
						Ressources::getInstance()->updateTowerSpawnTexture(scd->getTypeType(), **scd->getTexture());
					}
				}
				return true;
			}
		}
	}

	closeButton->checkHover(mouse);

	return false;
}

void SkinsGUI::draw()
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();
	window->draw(*Ressources::getInstance()->getBlackBackgroundSprite());
	window->draw(*background);
	window->draw(*closeButton);
	window->draw(*headlineText);

	if (allSkinsGUIDisplayedSkins.size() > 0)
	{
		for (auto i : allSkinsGUIDisplayedSkins)
		{
			window->draw(*i->getSprite());
		}

		for (auto i : allEquipedSprites)
		{
			window->draw(*i);
		}
	}
	else
	{
		window->draw(*emptyText);
	}

	window->display();
}

void SkinsGUI::initialize()
{
	updateAllBoughtShopContent();

	int index = 0;
	for (auto i : allSkinsGUIDisplayedSkins)
	{
		i->updatePosition(index);
		index++;
	}

	for (auto i : allSkinsGUIDisplayedSkins)
	{
		if (i->getShopContentData()->getIsEquiped())
		{
			createEquipedSprite(i);
		}
	}
}

SkinsGUI::SkinsGUI(RenderWindow* _window)
{
	window = _window;
	isOpen = false;
	isClicked = false;

	background = new Sprite();
	background->setPosition(100, 50);
	background->setTexture(*Ressources::getInstance()->getAccountLoginBackground());
	background->setScale(2.15, 1.11);

	closeButton = new Button(Vector2f(1720, 50), Ressources::getInstance()->getButtonCloseTexture());

	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	emptyText = new Text();
	emptyText->setFont(*font);
	emptyText->setCharacterSize(50);
	emptyText->setFillColor(Color::White);
	emptyText->setOutlineThickness(5);
	emptyText->setOutlineColor(Color::Black);
	emptyText->setPosition(500, 400);
	emptyText->setString("Du hast momentan noch keine Skins\nBesuche doch den Shop um neue zu kaufen");

	headlineText = new Text();
	headlineText->setFont(*font);
	headlineText->setCharacterSize(80);
	headlineText->setFillColor(Color::White);
	headlineText->setOutlineThickness(8);
	headlineText->setOutlineColor(Color::Black);
	headlineText->setPosition(900, 100);
	headlineText->setString("Skins");
	headlineText->setStyle(sf::Text::Underlined);


	for (auto i : ShopContentData::getAllShopContentData())
	{
		if (i->getIsBought())
		{
			allSkinsGUIDisplayedSkins.push_back(new SkinsGUIDisplayedSkin(font, i));
		}
	}
}

bool SkinsGUI::openGUI()
{
	isOpen = true;

	initialize();

	Event* event = Controls::getEvent();

	while (window->isOpen() && isOpen)
	{
		while (window->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				window->close();
				exit(0);
			}
			checkClicked();
		}
		draw();


	}

	return isOpen;
}

void SkinsGUI::updateAllBoughtShopContent()
{
	allSkinsGUIDisplayedSkins.clear();
	for (auto i : ShopContentData::getAllShopContentData())
	{
		if (i->getIsBought())
		{
			allSkinsGUIDisplayedSkins.push_back(new SkinsGUIDisplayedSkin(font, i));
		}
	}
}

SkinsGUI::SkinsGUIDisplayedSkin::SkinsGUIDisplayedSkin(Font* font, ShopContentData* scd)
{
	p_scd = scd;

	title = new Text();
	title->setFont(*font);
	title->setPosition(20, 10);
	title->setString(scd->getName());
	title->setCharacterSize(30);
	title->setFillColor(Color::White);
	title->setOutlineThickness(3);
	title->setOutlineColor(Color::Black);
	title->setStyle(sf::Text::Underlined);

	contentPreview = new Sprite();
	contentPreview->setTexture(*scd->getPreviewTexture());
	contentPreview->setPosition(0, 50);
	contentPreview->setScale(4, 4);


	texture = new RenderTexture();
	texture->create(300, 300);

	texture->draw(*title);
	texture->draw(*contentPreview);
	texture->display();

	sprite = new Sprite();
	sprite->setTexture(texture->getTexture());
	sprite->setPosition(startPositionX, startPositionY);

}

void SkinsGUI::SkinsGUIDisplayedSkin::updatePosition(int index)
{
	sprite->setPosition
	(
		startPositionX + texture->getSize().x * (index % contentsPerRow) + distanceToNextSprite, // X-Position
		index / contentsPerRow * (texture->getSize().y + distanceToNextSprite) + startPositionY // Y-Position
	);
}

ShopContentData* SkinsGUI::SkinsGUIDisplayedSkin::getShopContentData()
{
	return p_scd;
}

Sprite* SkinsGUI::SkinsGUIDisplayedSkin::getSprite()
{
	return sprite;
}
