#include "Ressources.h"
#include "Controls.h"

Time Controls::mouseWheelMoveCooldownTime = milliseconds(120);
Clock Controls::mouseWheelMoveCooldownClock;
Thread* Controls::thread = new Thread(&Controls::run);
Event* Controls::event = new Event();
bool Controls::initialized = false;

bool Controls::arrowUpIsPressed = false;
bool Controls::arrowDownIsPressed = false;
bool Controls::escIsPressed = false;
bool Controls::spaceIsPressed = false;
bool Controls::shiftIsPressed = false;
bool Controls::ctrlIsPressed = false;
bool Controls::altIsPressed = false;
bool Controls::enterIsPressed = false;
bool Controls::tabIsPressed = false;
bool Controls::backSpaceIsPressed = false;
bool Controls::rightMouseIsClicked = false;
bool Controls::leftMouseIsClicked = false;
bool Controls::middleMouseIsClicked = false;
int Controls::mouseWheel = 0;

#pragma region Funktionen
bool Controls::initializeControls()
{
	thread->launch();
	return initialized;
}
char Controls::checkKeyboardInput(Event* event)
{
	char c = '\0';

	if (event->type == Event::KeyPressed)
	{
		switch (event->key.code)
		{
		case Keyboard::Up:
			arrowUpIsPressed = true;
			break;
		case Keyboard::Down:
			arrowDownIsPressed = true;
			break;
		case Keyboard::LShift:
			shiftIsPressed = true;
			break;
		case Keyboard::Space:
			spaceIsPressed = true;
			break;
		case Keyboard::LControl:
			ctrlIsPressed = true;
			break;
		case Keyboard::LAlt:
			altIsPressed = true;
			break;
		case Keyboard::Enter:
			enterIsPressed = true;
			break;
		case Keyboard::Tab:
			tabIsPressed = true;
			break;
		case Keyboard::BackSpace:
			backSpaceIsPressed = true;
			break;
		case Keyboard::Escape:
			escIsPressed = true;
			break;
		}
	}
	else if (event->type == Event::KeyReleased)
	{
		switch (event->key.code)
		{
		case Keyboard::Up:
			arrowUpIsPressed = false;
			break;
		case Keyboard::Down:
			arrowDownIsPressed = false;
			break;
		case Keyboard::LShift:
			shiftIsPressed = false;
			break;
		case Keyboard::LControl:
			ctrlIsPressed = false;
			break;
		case Keyboard::LAlt:
			altIsPressed = false;
			break;
		case Keyboard::Enter:
			enterIsPressed = false;
			break;
		case Keyboard::Space:
			c = ' ';
			spaceIsPressed = false;
			break;
		case Keyboard::Tab:
			tabIsPressed = false;
			break;
		case Keyboard::BackSpace:
			backSpaceIsPressed = false;
			break;
		case Keyboard::Escape:
			escIsPressed = false;
			break;
		case Keyboard::Period:
			c = '.';
			break;
		case Keyboard::Add:
			c = '+';
			break;
		case Keyboard::Comma:
			c = ',';
			break;
		case Keyboard::Dash:
			c = '-';
			break;
		case Keyboard::Divide:
			c = '/';
			break;
		case Keyboard::Equal:
			c = '=';
			break;
		case Keyboard::Multiply:
			c = '*';
			break;
		case Keyboard::Quote:
			c = '"';
			break;
		case Keyboard::Semicolon:
			c = ';';
			break;
		case Keyboard::Slash:
			c = '#';
			break;
		case Keyboard::Subtract:
			c = '-';
			break;
		case Keyboard::Tilde:
			c = '~';
			break;
		case Keyboard::Num0:
		case Keyboard::Numpad0:
			c = '0';
			break;
		case Keyboard::Num1:
		case Keyboard::Numpad1:
			c = '1';
			break;
		case Keyboard::Num2:
		case Keyboard::Numpad2:
			c = '2';
			break;
		case Keyboard::Num3:
		case Keyboard::Numpad3:
			c = '3';
			break;
		case Keyboard::Num4:
		case Keyboard::Numpad4:
			c = '4';
			break;
		case Keyboard::Num5:
		case Keyboard::Numpad5:
			c = '5';
			break;
		case Keyboard::Num6:
		case Keyboard::Numpad6:
			c = '6';
			break;
		case Keyboard::Num7:
		case Keyboard::Numpad7:
			c = '7';
			break;
		case Keyboard::Num8:
		case Keyboard::Numpad8:
			c = '8';
			break;
		case Keyboard::Num9:
		case Keyboard::Numpad9:
			c = '9';
			break;
		case Keyboard::A:
			c = 'a';
			break;
		case Keyboard::B:
			c = 'b';
			break;
		case Keyboard::C:
			c = 'c';
			break;
		case Keyboard::D:
			c = 'd';
			break;
		case Keyboard::E:
			c = 'e';
			break;
		case Keyboard::F:
			c = 'f';
			break;
		case Keyboard::G:
			c = 'g';
			break;
		case Keyboard::H:
			c = 'h';
			break;
		case Keyboard::I:
			c = 'i';
			break;
		case Keyboard::J:
			c = 'j';
			break;
		case Keyboard::K:
			c = 'k';
			break;
		case Keyboard::L:
			c = 'l';
			break;
		case Keyboard::M:
			c = 'm';
			break;
		case Keyboard::N:
			c = 'n';
			break;
		case Keyboard::O:
			c = 'o';
			break;
		case Keyboard::P:
			c = 'p';
			break;
		case Keyboard::Q:
			c = 'q';
			break;
		case Keyboard::R:
			c = 'r';
			break;
		case Keyboard::S:
			c = 's';
			break;
		case Keyboard::T:
			c = 't';
			break;
		case Keyboard::U:
			c = 'u';
			break;
		case Keyboard::V:
			c = 'v';
			break;
		case Keyboard::W:
			c = 'w';
			break;
		case Keyboard::X:
			c = 'x';
			break;
		case Keyboard::Y:
			c = 'y';
			break;
		case Keyboard::Z:
			c = 'z';
			break;


		default:
			c = '\0';
		}
	}

	if (shiftIsPressed)
	{
		return std::toupper(c);
	}
	else if (ctrlIsPressed && altIsPressed && std::toupper(c) == 'Q')
	{
		return '@';
	}
	else return c;
}
Vector2i Controls::checkMouseClick(Event* event)
{
	if (event->type == Event::MouseButtonPressed)
	{
		if (event->key.code == Mouse::Left)
		{
			leftMouseIsClicked = true;
		}
		else if (event->key.code == Mouse::Right)
		{
			rightMouseIsClicked = true;
		}
		else if (event->key.code == Mouse::Middle)
		{
			middleMouseIsClicked = true;
		}
	}
	else if (event->type == Event::MouseButtonReleased)
	{
		if (event->key.code == Mouse::Left)
		{
			leftMouseIsClicked = false;
		}
		else if (event->key.code == Mouse::Right)
		{
			rightMouseIsClicked = false;
		}
		else if (event->key.code == Mouse::Middle)
		{
			middleMouseIsClicked = false;
		}
	}
	else if (event->type == Event::MouseWheelMoved)
	{
		mouseWheel = event->mouseWheel.delta;
		mouseWheelMoveCooldownClock.restart();
	}

	return Mouse::getPosition();
}
void Controls::checkControls()
{
	if (mouseWheelMoveCooldownClock.getElapsedTime() >= mouseWheelMoveCooldownTime)
	{
		mouseWheel = 0;
		mouseWheelMoveCooldownClock.restart();
	}
	backSpaceIsPressed = false;
	enterIsPressed = false;
	escIsPressed = false;
	arrowUpIsPressed = false;
	arrowDownIsPressed = false;
}
void Controls::run()
{
	while (event->type != Event::Closed)
	{
		checkKeyboardInput(event);
		checkMouseClick(event);
		checkControls();
	}
}
#pragma endregion

#pragma region getter

bool Controls::getArrowUpIsPressed()
{
	return arrowUpIsPressed;
}

bool Controls::getArrowDownIsPressed()
{
	return arrowDownIsPressed;
}

bool Controls::getEscIsPressed()
{
	return escIsPressed;
}

bool Controls::getSpaceIsPressed()
{
	return spaceIsPressed;
}

bool Controls::getShiftIsPressed()
{
	return shiftIsPressed;
}

bool Controls::getCtrlIsPressed()
{
	return ctrlIsPressed;
}

bool Controls::getAltIsPressed()
{
	return altIsPressed;
}

bool Controls::getEnterIsPressed()
{
	return enterIsPressed;
}

bool Controls::getTabIsPressed()
{
	return tabIsPressed;
}

bool Controls::getBackSpaceIsPressed()
{
	return backSpaceIsPressed;
}

bool Controls::getRightMouseIsClicked()
{
	return rightMouseIsClicked;
}

bool Controls::getLeftMouseIsClicked()
{
	return leftMouseIsClicked;
}

bool Controls::getMiddleMouseIsClicked()
{
	return middleMouseIsClicked;
}

int Controls::getMouseWheel()
{
	return mouseWheel;
}

Event* Controls::getEvent()
{
	return event;
}

#pragma endregion