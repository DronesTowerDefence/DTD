#pragma once
#include "AccountServer.h"

class Friends
{
private:
	std::string name;
	Image* image;

public:
	std::string getName();
	Image* getImage();
	Friends(std::string freund, Image* image);
};

class FriendTexture
{
private:

	RenderTexture* texture;
	Texture* imageTexture;
	Font* font;
	Text* name;
	Sprite* sprite;
	Sprite* background;
	Sprite* ProfilePicture;
	Friends* friends;
public:
	Sprite* getTexture();
	FriendTexture(Friends* friends);
};

class FriendsGUI {
private:
	std::list<FriendTexture*> allTexture;
	Sprite* displayFriends[5];
	Sprite* background;
	void start(RenderWindow* window);
	void draw(RenderWindow* window);
	int firstIndex;
	void updateDrawSprite();
	void Scroll();


	AccountServer* accServer;

public: FriendsGUI(RenderWindow* window);
};