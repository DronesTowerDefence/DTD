#pragma once
#include "Ressources.h"

class PopUpMessage
{
private:
	static Font* font;
	static std::list<PopUpMessage*> allPopUpMessages;
	Thread* thread;
	Sprite* sprite;
	Text* text;
	Clock* clock;
	Time* time;
	bool isDone;

	PopUpMessage(); // Nicht benutzen
	void run(); // Für Thread
public:
	/// <summary>
	/// Erstellt eine PopUp-Nachricht als Thread
	/// </summary>
	/// <param name="_message">Anzuzeigende Nachricht (max. 34 chars)</param>
	/// <param name="_time">Wie lange die Nachricht angezeigt werden soll</param>
	PopUpMessage(std::string _message, Time _time);
	~PopUpMessage();

	/// <summary>
	/// Alle vorhandenen PopUp-Nachrichten werden gedrawt
	/// </summary>
	/// <param name="window"></param>
	static void draw(RenderWindow* window);

	/// <summary>
	/// Zum initialisieren der statischen Variablen
	/// </summary>
	static void initializePopUpMessages();
};

