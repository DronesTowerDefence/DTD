#include "HomeMenu.h"
HomeMenu* HomeMenu::instance = nullptr;

HomeMenu* HomeMenu::getInstance(RenderWindow* win)
{
	if (instance == nullptr)
	{
		instance = new HomeMenu(win);
	}
	return instance;
}

HomeMenu::HomeMenu(RenderWindow* win)
{
	isClicked = false;
	window = win;
	startButton = new Sprite;
	font = new Font();
	titel = new Sprite;
	backround = new Sprite();
	drone = new Sprite();
	textureStartButton = new Texture();
	textureTitel = new Texture();
	textureBackround = new Texture();
	textureDrone = new Texture();
	pointer = new RectangleShape;

	textureStartButton->loadFromFile("img/buttons/startButton.png");
	textureTitel->loadFromFile("img/titleText.png");
	textureDrone->loadFromFile("img/drone0/drone0.png");
	font->loadFromFile("fonts/arial.ttf");
	startButton->setTexture(*textureStartButton);
	titel->setTexture(*textureTitel);
	textureBackround->loadFromFile("img/backround.jpg");
	backround->setTexture(*textureBackround);
	drone->setTexture(*textureDrone);;

	choseIndex = -1;

	startButton->setPosition(Vector2f(900, 600));
	titel->setPosition(Vector2f(0, 0));
	drone->setPosition(Vector2f(0, 300));

	drone->setScale(2, 2);
	//
	for (int i = 0; i < 1; i++)
	{
		map[i] = new Sprite;
		textureMap[i] = new Texture();
		map[i]->setScale(0.1, 0.1);
		textureMap[i]->loadFromFile("img/maps/Map" + std::to_string(i + 1) + ".png");
		map[i]->setTexture(*textureMap[i]);
		map[0]->setPosition(Vector2f(500, 500));
		positionMap[0] = Vector2f(400, 500);

	}
	positionTower[0] = Vector2f(100, 400);
	positionTower[1] = Vector2f(300, 500);
	positionTower[2] = Vector2f(700, 800);
	positionTower[3] = Vector2f(1400, 200);
	positionTower[4] = Vector2f(1570, 400);
	for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
	{

		for (int x = 0; x < 4; x++)
		{
			textureTower[i][x] = new Texture();
		}
	}
	textureTower[0][0]->loadFromFile("img/tower0/tower0_0.png");
	textureTower[0][1]->loadFromFile("img/tower0/tower0_1.png");
	textureTower[0][2]->loadFromFile("img/tower0/tower0_2.png");
	textureTower[0][3]->loadFromFile("img/tower0/tower0_1.png");

	textureTower[1][0]->loadFromFile("img/tower1/tower1_0.png");
	textureTower[1][1]->loadFromFile("img/tower1/tower1_0.png");
	textureTower[1][2]->loadFromFile("img/tower1/tower1_0.png");
	textureTower[1][3]->loadFromFile("img/tower1/tower1_0.png");

	textureTower[2][0]->loadFromFile("img/tower2/tower2_0.png");
	textureTower[2][1]->loadFromFile("img/tower2/tower2_1.png");
	textureTower[2][2]->loadFromFile("img/tower2/tower2_2.png");
	textureTower[2][3]->loadFromFile("img/tower2/tower2_1.png");

	textureTower[3][0]->loadFromFile("img/tower3/tower3_0.png");
	textureTower[3][1]->loadFromFile("img/tower3/tower3_0.png");
	textureTower[3][2]->loadFromFile("img/tower3/tower3_0.png");
	textureTower[3][3]->loadFromFile("img/tower3/tower3_0.png");

	textureTower[4][0]->loadFromFile("img/tower4/tower4_0.png");
	textureTower[4][1]->loadFromFile("img/tower4/tower4_1.png");
	textureTower[4][2]->loadFromFile("img/tower4/tower4_2.png");
	textureTower[4][3]->loadFromFile("img/tower4/tower4_3.png");
	
	for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
	{
		towers[i] = new Sprite();

		towers[i]->setTexture(*textureTower[i][0]);
		towers[i]->setPosition(positionTower[i]);
		towers[i]->setScale(2, 2);

	}
	animationIndex = 0;
	animation = new Clock();
	animation->restart();
	pointer->setSize(Vector2f(1920 * 0.1, 991 * 0.1));
	pointer->setOutlineThickness(10);
	pointer->setOutlineColor(Color::Magenta);
	pointer->setFillColor(Color::Transparent);
	choseText = new Text("Waehle eine Karte aus", *font, 40);
	choseText->setPosition(Vector2f(500, 450));
}

void HomeMenu::HomeMenuStart()
{
	while (window->isOpen())
	{
		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				//saveGame();
				window->close();
			}
		}
		drone->move(2, 0);
		setTowerTexture();
		if (drone->getPosition().x > 1920)
		{
			drone->setPosition(Vector2f(0, 300));
		}
		if (CheckClicked() && choseIndex != -1)
		{
			Game::getInstance()->setWindow(&*window);
			Game::getInstance()->startGame();
		}
		draw();

	}
}

void HomeMenu::draw()
{
	window->clear();
	window->draw(*backround);
	window->draw(*titel);
	window->draw(*startButton);
	window->draw(*drone);
	window->draw(*choseText);
	for (int i = 0; i < 1; i++)
	{
		window->draw(*map[i]);
	}

	for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
	{
		window->draw(*towers[i]);
	}
	if (choseIndex > -1)
	{
		window->draw(*pointer);
	}

	window->display();
}

bool  HomeMenu::CheckClicked()
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		isClicked = true;
	}
	if (isClicked && !Mouse::isButtonPressed(Mouse::Left))
	{
		//map clicked;
		isClicked = false;
		Vector2i mouse = Mouse::getPosition(*window);
		Vector2f pos, pos2;
		for (int i = 0; i < 1; i++)
		{

			pos = Service::getInstance()->getObjectPosition(map[i]->getPosition()); //Holt sich die Position des Turmes i
			pos2 = Service::getInstance()->getObjectPosition(map[i]->getPosition() + Vector2f(150, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

			if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
			{
				pointer->setPosition(Vector2f(map[i]->getPosition().x , map[i]->getPosition().y ));
				choseIndex = i;
			}
		}
		//startclicked
		mouse = Mouse::getPosition(*window);
		pos, pos2;

		pos = Service::getInstance()->getObjectPosition(startButton->getPosition()); //Holt sich die Position des Turmes i
		pos2 = Service::getInstance()->getObjectPosition(startButton->getPosition() + Vector2f(100, 100)); //Holt sich die Position des Turmes i + 50 wegen der Größe

		if ((mouse.x >= pos.x && mouse.x <= pos2.x) && (mouse.y >= pos.y && mouse.y <= pos2.y)) //Ob der Turm i geklickt wurde
		{
			return true;
		}
	}
	return false;


}

void HomeMenu::setTowerTexture()
{
	if (animation->getElapsedTime().asMilliseconds() >= 300)
	{
		animationIndex++;
		if (animationIndex > 3)
			animationIndex = 0;

		for (int i = 0; i < Ressources::getInstance()->getTowerCount(); i++)
		{
			towers[i]->setTexture(*textureTower[i][animationIndex]);
		}
		animation->restart();
	}

}
