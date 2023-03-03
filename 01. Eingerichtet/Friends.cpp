#include "Friends.h"
#include "Controls.h"
#include "HomeMenu.h"

Sprite* FriendTexture::getTexture()
{
	return sprite;
}

FriendTexture::FriendTexture(Friends* friends)
{
	this->friends = friends;

	background = new Sprite;
	background->setTexture(*Ressources::getInstance()->getSendMoneyBackgroundTexture());
	background->setPosition(0, 0);
	background->setScale(3, 1);

	imageTexture = new Texture();
	imageTexture->loadFromImage(*(friends->getImage()));

	ProfilePicture = new Sprite();
	ProfilePicture->setTexture(*imageTexture);
	ProfilePicture->setScale(Vector2f(75.f / float(imageTexture->getSize().x), 75.f / float(imageTexture->getSize().y)));
	ProfilePicture->setPosition(1000, 50);
	font = new Font();
	font->loadFromFile("fonts/arial.ttf");

	name = new Text();
	name->setCharacterSize(40);
	name->setFillColor(Color::White);
	name->setOutlineThickness(4);
	name->setOutlineColor(Color::Black);
	name->setFont(*font);
	name->setPosition(100, 60);
	name->setString(friends->getName());





	texture = new RenderTexture();
	texture->create(1300, 200);

	texture->draw(*background);
	texture->draw(*ProfilePicture);
	texture->draw(*name);
	texture->display();

	sprite = new Sprite(texture->getTexture());
	background->setPosition(100, 50);
	background->setScale(2.15, 1.11);
}

std::string Friends::getName()
{
	return name;
}

Image* Friends::getImage()
{
	return image;
}

Friends::Friends(std::string freund, Image* image)
{
	this->name = freund;
	this->image = image;
}

void FriendsGUI::start(RenderWindow* window)
{
	bool isClicked = false;
	Event event;
	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window->close();
				exit(0);
			}
		}
		Scroll();
		draw(window);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			isClicked = true;
		}
		if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2f pos, pos2;
			Vector2i mouse = Mouse::getPosition();
			isClicked = false;

			//Close
			pos = Service::getInstance()->getObjectPosition(close->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(close->getPosition() + Vector2f(close->getTexture()->getSize()));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				return;

			}	// FriendsRrequest
			pos = Service::getInstance()->getObjectPosition(openFriendsRequest->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(openFriendsRequest->getPosition() + Vector2f(openFriendsRequest->getTexture()->getSize()));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				FriendsGUI* gui = new FriendsGUI(window, 1);

			}

			pos = Service::getInstance()->getObjectPosition(addFriend->getPosition());
			pos2 = Service::getInstance()->getObjectPosition(addFriend->getPosition() + Vector2f(addFriend->getTexture()->getSize()));
			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y))
			{
				FriendsGUI* gui = new FriendsGUI(window, 1);

			}


		}
	}

}

void FriendsGUI::draw(RenderWindow* window)
{
	window->clear();
	HomeMenu::getInstance()->drawPublic();
	window->draw(*background);
	for (int i = 0; i < 5 && i < allTexture.size(); i++)
	{
		window->draw(*displayFriends[i]);
	}
	if (menuArt == 0) window->draw(*openFriendsRequest);
	window->draw(*addFriend);
	window->draw(*close);
	window->display();
}

void FriendsGUI::updateDrawSprite()
{
	int counter = 0, index = 0;
	for (auto tmp : allTexture)
	{
		if (counter == firstIndex + index)
		{
			displayFriends[index]->setTexture(*tmp->getTexture()->getTexture());
			index++;
		}
		counter++;
	}
}

void FriendsGUI::Scroll()
{
	if (Controls::getArrowUpIsPressed())
	{
		if (firstIndex > 0)
		{
			firstIndex--;
			updateDrawSprite();
		}
	}
	else if (Controls::getArrowDownIsPressed())
	{
		if (firstIndex < allTexture.size() - 4)
		{
			firstIndex++;
			updateDrawSprite();
		}
	}
}

FriendsGUI::FriendsGUI(RenderWindow* window, int menuArt)
{
	this->menuArt = menuArt;
	addFriend = new Sprite();
	addFriend->setTexture(*Ressources::getInstance()->getAccountFriendsButtonTexture());
	addFriend->setPosition(1600, 50);

	openFriendsRequest = new Sprite();
	openFriendsRequest->setTexture(*Ressources::getInstance()->getOpenChatButtonTexture());
	openFriendsRequest->setPosition(1600, 150);

	close = new Sprite();
	close->setTexture(*Ressources::getInstance()->getButtonCloseTexture());
	close->setPosition(100, 50);

	accServer = new AccountServer();
	background = new Sprite();
	background->setPosition(100, 50);
	background->setTexture(*Ressources::getInstance()->getAccountLoginBackground());
	background->setScale(2.15, 1.11);
	firstIndex = 0;

	displayFriends[0] = new Sprite();
	displayFriends[1] = new Sprite();
	displayFriends[2] = new Sprite();
	displayFriends[3] = new Sprite();
	displayFriends[4] = new Sprite();
	int i = 0;
	for (int i = 0; i < 5; i++)
	{
		displayFriends[i]->setPosition(350, 150 * (i + 1) - 50);
	}
	std::string freude = "";
	switch (menuArt)
	{
	case 0:
		freude = accServer->getFriends(Account::getAccName());
		break;
	case 1:
		freude = accServer->getIncomingFriendRequests(Account::getAccName());
		break;
	default:
		break;
	};

	std::size_t found = freude.find("&");
	int counter = 0, pos = 0;
	std::string username = "";
	while (found != std::string::npos)
	{
		username = freude.substr(pos, found - pos);
		allTexture.push_back(new FriendTexture(new Friends(username, accServer->getProfilePicture(username))));
		pos = found + 1;
		found = freude.find("&", pos);
	}
	updateDrawSprite();
	start(window);

}
