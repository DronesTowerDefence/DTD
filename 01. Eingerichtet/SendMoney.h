#pragma once
#include "ressources.h"

class SendMoney
{
private:

	static SendMoney* instance;

	Ressources* res;
	RenderWindow* window;
	
	Font font;

	Text inputText;

	Sprite background;
	Sprite buttonOpen;
	Sprite buttonClose;

	std::string input;

	int inputAsInt;
	int maxSize;

	bool isOpen;
	bool mouseClicked;

	SendMoney();

	void checkClicked();
	bool send();

public:

	bool checkInput(Event);
	void checkSendMoney();
	void draw();

	static SendMoney* getInstance();
	bool getIsOpen();
};

