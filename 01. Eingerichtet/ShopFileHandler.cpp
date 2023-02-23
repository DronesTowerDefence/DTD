#include "ShopFileHandler.h"
#include "ShopContent.h"

std::map<int, Texture*> ShopFileHandler::textures;

bool ShopFileHandler::loadShopTextures()
{
	int size[shopContentCount] = { 0 }; // Bild-Größe
	char c; // Buffer
	std::ifstream input("data/shopContent.sav");
	std::ifstream input2("data/shopTextures.dat", std::ios::binary);
	std::ofstream output;
	char buffer[40];
	std::vector<unsigned char> buffer2;
	Texture* tex;

	for (int i = 0; i < shopContentCount; i++)
	{
		// Aus Datei lesen, um Größe von Bild zu bekommen



		input.close();

		/*------------------------------------------------------------------------------------*/
		// Aus gemeinsamer Datei lesen
		buffer2.clear();
		for (int j = 0; j < size[i]; j++)
		{
			input2.read(&c, 1);
			buffer2.push_back(c);
		}

		/*------------------------------------------------------------------------------------*/
		// In Datei und in Texture speichern
		buffer2.clear();
		output.open("saves/shopContent/picture.png", std::ios::binary);
		for (auto j : buffer2)
		{
			c = j;
			output.write(&c, 1);
		}
		output.close();
		tex = new Texture();
		tex->loadFromFile("saves/shopContent/picture.png");
		textures.insert({ i, tex });
		system("del saves\\shopContent\\picture.png");
	}


	input2.close();

	return true;
}

Texture* ShopFileHandler::getTexture(int index)
{
	if (index >= 0 && index < textures.size())
	{
		return textures.find(index)->second;
	}
	return nullptr;
}
