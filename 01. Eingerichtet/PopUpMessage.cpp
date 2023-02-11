#include "PopUpMessage.h"

sf::Font* PopUpMessage::font = new Font();
std::list<PopUpMessage*> PopUpMessage::allPopUpMessages;

void PopUpMessage::run()
{
	while (clock->getElapsedTime() <= *time);
	isDone = true;
	delete this;
}

PopUpMessage::PopUpMessage(std::string _message, Time _time)
{
	if (_message.length() >= 34)
	{
		//_message = _message.substr(0, 34);
		_message = _message.substr(0, 33);
		_message.append("...");
	}

	isDone = false;

	sprite = new Sprite();
	sprite->setTexture(*Ressources::getInstance()->getSendMoneyBackgroundTexture());
	sprite->setPosition(660.f, 100.f);
	sprite->setScale(1.5f, 0.6f);

	text = new Text();
	text->setFont(*font);
	text->setCharacterSize(30);
	text->setFillColor(Color::White);
	text->setOutlineThickness(3);
	text->setOutlineColor(Color::Black);
	text->setPosition(715.f, 125.f);
	text->setString(_message);

	thread = new Thread(&PopUpMessage::run, this);
	clock = new Clock();
	time = new Time(_time);

	allPopUpMessages.push_back(this);
	thread->launch();
}

PopUpMessage::~PopUpMessage()
{
	for (auto i : allPopUpMessages)
	{
		if (i == this)
		{
			allPopUpMessages.remove(this);
			break;
		}
	}

	if (!isDone && thread != nullptr)
		thread->terminate();
	if (clock != nullptr)
		delete clock;
	if (time != nullptr)
		delete time;
	delete sprite;
	delete text;
}

void PopUpMessage::draw(RenderWindow* window)
{
	if (allPopUpMessages.size() > 0)
	{
		for (auto i : allPopUpMessages)
		{
			window->draw(*i->sprite);
			window->draw(*i->text);
		}
	}
}

void PopUpMessage::initializePopUpMessages()
{
	font->loadFromFile("fonts/arial.ttf");
}
