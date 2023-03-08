#pragma once
class Controls
{
private:

	static Clock mouseWheelMoveCooldownClock;
	static Clock buttonPressedCooldownClock;
	static Time mouseWheelMoveCooldownTime;
	static Time buttonPressedCooldownTime; // Je niedriger, desto weniger kann man mit z.B. backspace löschen

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
	static bool altGrIsPressed;
	static bool rightMouseIsClicked;
	static bool leftMouseIsClicked;
	static bool middleMouseIsClicked;
	static int mouseWheel;
	static std::string enteredString;

	static bool initialized;
	static Thread* thread;
	static Event* event;
	static void run();

	static Vector2i checkMouseClick(Event*);
	static void checkControls();

public:
	static std::string checkKeyboardInput(Event*);


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
	static bool getAltGrIsPressed();
	static bool getRightMouseIsClicked();
	static bool getLeftMouseIsClicked();
	static bool getMiddleMouseIsClicked();
	static int getMouseWheel();

	static Event* getEvent();

	/// <summary>
	/// Normalerweise ein einzelner char, außer bei strg+v
	/// </summary>
	/// <returns></returns>
	static std::string getEnteredString();

	/// <summary>
	/// Starten der Controls, aufrufen nachdem das HomeMenu erstellt wurde
	/// </summary>
	/// <returns>Ob erfolgreich</returns>
	static bool initializeControls();

};