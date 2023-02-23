#pragma once
#include <fstream>
#include <vector>
#include <list>
#include "Ressources.h"


class ShopFileHandler
{
private:

	ShopFileHandler();

	// id, texture
	static std::map<int, Texture*> textures;
public:
	static bool loadShopTextures();
	static Texture* getTexture(int index);
};

