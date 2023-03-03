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
	Sprite* close;
	Sprite* ProfilePicture;
	Friends* friends;
	
public:
	Sprite* getTexture();
	FriendTexture(Friends* friends);
	Friends* getFriend();
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
	Sprite* close;
	Sprite* closeEingabe;
	Sprite* eingabeBackground;
	Sprite* anfrageSenden;

	AccountServer* accServer;
	Sprite* addFriend;
	Sprite* openFriendsRequest;
	int menuArt;

	Text* AnzeigeText;
	Font* font;
	std::string text;
	bool Eingabe;
	
	

public:
	void loadFriends();
	FriendsGUI(RenderWindow* window , int menuArt);
};