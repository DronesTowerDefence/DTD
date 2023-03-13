#include "Daily.h"

Daily::Daily()
{
	bis = 0;
	von = 0;
	leben = 0;
	geld = 0;
	isDaily = false;
	isTowerAllowed[0] = false;
	isTowerAllowed[1] = false;
	isTowerAllowed[2] = false;
	isTowerAllowed[3] = false;
	isTowerAllowed[4] = false;
	isTowerAllowed[5] = false;
	isTowerAllowed[6] = false;

}

int Daily::getBis()
{
	return bis;
}

int Daily::getLeben()
{
	return leben;
}

int Daily::getGeld()
{
	return geld;
}

void Daily::setIsDaily(bool _isDaily)
{
	isDaily = _isDaily;
}

void Daily::setIsTowerAllowed(int index, bool isAllowed)
{
	isTowerAllowed[index] = isAllowed;
}

void Daily::setBis(int _bis)
{
	bis = _bis;
}

void Daily::setVon(int _von)
{
	von = _von;
}

void Daily::setGeld(int _geld)
{
	geld = _geld;
}

void Daily::setLeben(int _leben)
{
	leben = _leben;
}


bool Daily::getIsDaily()
{
	return isDaily;
}

bool Daily::getIsTowerAllowed(int index)
{
	return isTowerAllowed[index];
}

int Daily::getVon()
{
	return von;
}

