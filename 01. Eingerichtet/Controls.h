#pragma once
class Controls
{
private:

	static Clock mouseWheelMoveCooldownClock;
	static Time mouseWheelMoveCooldownTime;

	static bool arrowUpIsPressed;
	static bool arrowDownIsPressed;
	static bool escIsPressed;
	static bool spaceIsPressed;
	static bool shiftIsPressed;
	static bool ctrlIsPressed;
	static bool altIsPressed;
	static bool enterIsPressed;
	static bool tabIsPressed;
	static bool backSpaceIsPressed;
	static bool rightMouseIsClicked;
	static bool leftMouseIsClicked;
	static bool middleMouseIsClicked;
	static int mouseWheel;

	static bool initialized;
	static Thread* thread;
	static Event* event;
	static void run();

public:


	static bool getArrowUpIsPressed();
	static bool getArrowDownIsPressed();
	static bool getEscIsPressed();
	static bool getSpaceIsPressed();
	static bool getShiftIsPressed();
	static bool getCtrlIsPressed();
	static bool getAltIsPressed();
	static bool getEnterIsPressed();
	static bool getTabIsPressed();
	static bool getBackSpaceIsPressed();
	static bool getRightMouseIsClicked();
	static bool getLeftMouseIsClicked();
	static bool getMiddleMouseIsClicked();
	static int getMouseWheel();

	static Event* getEvent();

	/// <summary>
	/// Starten der Controls, aufrufen nachdem das HomeMenu erstellt wurde
	/// </summary>
	/// <returns>Ob erfolgreich</returns>
	static bool initializeControls();
	static char checkKeyboardInput(Event*);
	static Vector2i checkMouseClick(Event*);
	static void checkControls();

};