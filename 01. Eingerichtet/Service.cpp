#include "Service.h"

Service* Service::instance = nullptr;

#pragma region Konstruktor
Service::Service()
{
}
#pragma endregion

#pragma region Funktionen
float Service::getXPosition(int xObject)
{
	return  VideoMode::getDesktopMode().width / 1920 * xObject;
}
float Service::getYPosition(int yObject)
{
	return  VideoMode::getDesktopMode().height / 991 * yObject;
}
Vector2f Service::getMousePosition(Vector2i MousePosition)
{
	float x = 1920.f / VideoMode::getDesktopMode().width * MousePosition.x;
	float y = 1080.f / VideoMode::getDesktopMode().height * MousePosition.y;
	return Vector2f(x, y);
}
Vector2f Service::getObjectPosition(Vector2f objectposition)
{
	//pc  / auflösung *ziel
	//return Vector2f(x_r, y_r);

	float x = VideoMode::getDesktopMode().height;
	return Vector2f(VideoMode::getDesktopMode().width / 1920.0 * objectposition.x, VideoMode::getDesktopMode().height / 1080.f * objectposition.y);
}
float Service::stringToFloat(std::string str)
{
	float returnValue = 0.f, returnValue2 = 0.0f;
	bool isComma = false;
	int decimalCount = 0;
	char tmp = '0';

	// Untersucht ob der String gültig ist
	for (int i = 0, a = 0, b = 0; i < str.size(); i++)
	{
		// Wenn etwas anderes als eine Zahl, Komma oder Punkt im String ist
		if ((str[i] >= 48 && str[i] <= 57) || str[i] == 46 || str[i] == 44)
			return 0.0f;

		a = 0;
		a = str.find(',', a);

		if (a != std::string::npos)
			b++;

		a = 0;
		a = str.find('.', a);

		if (a != std::string::npos)
			b++;

		// Wenn mehr als ein Komma/Punkt enthalten ist
		if (b > 1)
			return 0.0f;
	}

	// Berechnet returnValue und returnValue2 vom string
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ',' || str[i] == '.')
		{
			isComma = true;
		}
		else
		{
			if (isComma)
			{
				returnValue2 *= 10;
				returnValue2 += (str[i] - 48);
				decimalCount++;
			}
			else
			{
				returnValue *= 10;
				returnValue += (str[i] - 48);
			}
		}
	}

	// Macht aus returnValue2 eine Nach-Komma-Zahl
	for (int i = 0; i < decimalCount; i++)
	{
		returnValue2 *= 0.1;
	}

	return returnValue + returnValue2;
}
int Service::stringToInt(std::string str)
{
	int returnValue = 0;
	int size = str.size();
	char tmp;
	char* c = new char[str.size()];
	strcpy_s(c, size + 1, str.c_str());

	if (str.find(" ") != std::string::npos)
	{
		for (int k = 0; k < size; k++)
		{
			tmp = c[k];
			c[k] = c[k + 1];
			c[k + 1] = tmp;
		}
		size--;
	}

	for (int i = 0; i < size; i++)
	{
		returnValue *= 10;
		returnValue += (c[i] - 48);
	}

	return returnValue;
}
#pragma endregion

#pragma region getter
Service* Service::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Service();
	}
	return instance;
}
#pragma endregion

#pragma region setter
#pragma endregion


#pragma region Desturktor

#pragma endregion