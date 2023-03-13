#include "Projectile.h"
#include "Round.h"
#include <iostream>
#include <random>
#include "Multiplayer.h"




#pragma region Konstruktor
Projectile::Projectile(Tower* _tower, Vector2f _targetstill)
{
	speed = _tower->getProjectileSpeed();
	tower = _tower;
	collided = 0;
	res = Ressources::getInstance();
	Round::getInstance()->addProjectile(this);
	projectilesprite.setTexture(*res->getProjectileTexture(2));//Nagelwerfer
	projectilesprite.setPosition(tower->getTowerPos());
	targetstill = _targetstill;
	dronetarget = nullptr;
	style = res->getTowerProjectileIndex(1);
	homing();


}
Projectile::Projectile(Drone* _target, Tower* _tower, TowerSpawn* _towerspawn, int _style, Vector2f _targetstill,Vector2f _blitzpos)
{
	//Setzen der Attribute
	speed = _tower->getProjectileSpeed();
	tower = _tower;
	collided = 0;
	res = Ressources::getInstance();
	Round::getInstance()->addProjectile(this);
	style = _style;
	dronetarget = _target;
	towerspawn = _towerspawn;
	blitzcheck = true;

	if (style == 0) {
		move.x = _targetstill.x;
		move.y = _targetstill.y;
	}

	//Setzt die typspezifische Textur
	switch (_style)
	{
	case 0: {
		if (tower->getIndex()==5) {
			projectilesprite.setTexture(*res->getProjectileTexture(3));
		}
		else {
		projectilesprite.setTexture(*res->getProjectileTexture(0));//Feuerturm
		}
		break;
	}
	case 1:
		projectilesprite.setTexture(*res->getProjectileTexture(0));
		break;
	case 2:
		projectilesprite.setTexture(*res->getProjectileTexture(0));
		break;
	case 3:
		projectilesprite.setTexture(*res->getProjectileTexture(2));//Nagelwerfer
		break;
	case 4:
		projectilesprite.setTexture(*res->getProjectileTexture(1));
		break;
	case 5:
		projectilesprite.setTexture(*res->getProjectileTexture(3));
	}

	//Wenn Flugzeug
	if (towerspawn != nullptr && style == 0)
	{
		projectilesprite.setTexture(*res->getProjectileTexture(1));
		Vector2f newPos;
		Vector2f towerSpawnSize = Vector2f(_towerspawn->getSpawnTexture()->getSize());
		Vector2f towerSpawnPos = _towerspawn->getSpawnSprite()->getPosition();
		switch (int(_towerspawn->getSpawnSprite()->getRotation())) //Zentrieren vom Schuss
		{
		case 0:
			newPos.x = towerSpawnPos.x + towerSpawnSize.x / 2;
			newPos.y = towerSpawnPos.y + towerSpawnSize.y / 2;
			break;

		case 90:
			newPos.x = towerSpawnPos.x - towerSpawnSize.y / 2;
			newPos.y = towerSpawnPos.y + towerSpawnSize.x / 2;
			break;

		case 180:
			newPos.x = towerSpawnPos.x - towerSpawnSize.x / 2;
			newPos.y = towerSpawnPos.y - towerSpawnSize.y / 2;
			break;

		case 270:
			newPos.x = towerSpawnPos.x + towerSpawnSize.y / 2;
			newPos.y = towerSpawnPos.y - towerSpawnSize.x / 2;
			break;
		}
		projectilesprite.setPosition(newPos);
	}
	else
		projectilesprite.setPosition(tower->getTowerPos().x+(tower->getTowerSpr().getScale().x/2), tower->getTowerPos().y + (tower->getTowerSpr().getScale().y / 2));
	if (style == 0 && tower->getIndex() == 5) {
		speed /= 5;
		projectilesprite.setPosition(_blitzpos);
		blitzcooldown = 2;
	}
	operate(); //Lässt das Projektil losfliegen
}
#pragma endregion

#pragma region Funktionen
void Projectile::operate()
{
	switch (style) {
	case 0: {   //Fliegt einfach gerade
		if (tower->getIndex() == 6) {
			srand((unsigned)time(NULL));
			float k = rand() % 5;
			int r = rand() % 10;
			k /= 10;
			if (r < 5)
				k *= -1;
			std::cout << r << std::endl;
			speed /= 50;
			if (move.x == 0)
				move.x = k;
			else
				move.y = k;
		}
		moveProjectile();
		break;
	}
	case 1: { //Fliegt Richtung Drohne 
		targeting();
		setmove();
		break;
	}
	case 2: {  // Verfolgt Drohne
		homing();
		break;
	}
	case 3: //Für den Nagelwerfer, Schüsse werden auf der Strecke zufällig platziert
		if (!tower->getCoverableArea().empty())
		{
			srand((unsigned)time(NULL));
			int o = rand() % tower->getCoverableArea().size();
			int j = 0;
			for (auto i : tower->getCoverableArea()) {
				if (j == o) {
					targetstill.x = i.x;
					targetstill.y = i.y;
				}
				j++;
			}
			homing();
		break;
		}
	case 5: {
		targeting();
		break;
	}
	}
	
}

void Projectile::targeting()
{

		for (auto i : tower->getCoverableArea()) //Geht die Punkte der abdeckbaren Punkte durch
		{
			if (dronetarget->getNextPosition(i.z / speed).x - i.x<20 && dronetarget->getNextPosition(i.z / speed).x - i.x> -20) //Suchen, wo die Drohne und das Projektil sich treffen
			{
				if (dronetarget->getNextPosition(i.z / speed).y - i.y<20 && dronetarget->getNextPosition(i.z / speed).y - i.y > -20)
				{
					target = i;
					return;
				}
			}
		}
		if (style == 5) {
			move.x = -1 * (projectilesprite.getPosition().x - dronetarget->getPosition().x);
			move.y = -1 * (projectilesprite.getPosition().y - dronetarget->getPosition().y);
		}
}
void Projectile::homing()
{
	//Verfolgt die Drohne
	if (style == 3)
	{
		move.x = -1 * (projectilesprite.getPosition().x - targetstill.x);
		move.y = -1 * (projectilesprite.getPosition().y - targetstill.y);
		return;
	}
	move.x = -1 * (projectilesprite.getPosition().x - dronetarget->getPosition().x);
	move.y = -1 * (projectilesprite.getPosition().y - dronetarget->getPosition().y);
}
void Projectile::moveProjectile()
{
	//Bewegt das Projektil, abhängig vom Typ
	if (style == 2 || style == 3)
	{
		homing();
	}
	else if (style == 4)
	{
		for (auto i : Round::getInstance()->getAllDrones())
		{
			if (tower->getRangeShape()->getGlobalBounds().intersects(i->getDroneSprite().getGlobalBounds()))
			{
				i->takeDamage(tower->getDamage());
				tower->addDamageCount();
			}
		}
		delete this;
		return;
	}
	if (style == 5 && !blitzcheck) {

		if (tower->getBlitzCount() == 5) {
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(1, 1), projectilesprite.getPosition());
		}
		if (tower->getBlitzCount() == 6) {
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(1, 1), projectilesprite.getPosition());
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(-1, -1), projectilesprite.getPosition());
		}
		if (tower->getBlitzCount() == 7) {
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(1, 1), projectilesprite.getPosition());
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(-1, -1), projectilesprite.getPosition());
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(-1, 1), projectilesprite.getPosition());
		}
		if (tower->getBlitzCount() == 8) {
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(1, 1), projectilesprite.getPosition());
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(-1, -1), projectilesprite.getPosition());
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(-1, 1), projectilesprite.getPosition());
			new Projectile(nullptr, tower, nullptr, 0, Vector2f(1, -1), projectilesprite.getPosition());
		}
		new Projectile(nullptr, tower, nullptr, 0, Vector2f(1, 0),projectilesprite.getPosition());
		new Projectile(nullptr, tower, nullptr, 0, Vector2f(-1, 0), projectilesprite.getPosition());
		new Projectile(nullptr, tower, nullptr, 0, Vector2f(0, 1), projectilesprite.getPosition());
		new Projectile(nullptr, tower, nullptr, 0, Vector2f(0, -1), projectilesprite.getPosition());
		blitzcheck = true;
	}
	else if(blitzclock.getElapsedTime().asSeconds() > res->getNewProjectilTime(tower->getIndex(),tower->getUpdates()->getIndex1())) {
		blitzcheck = false;
		blitzclock.restart();
	}
	if (style == 5) {
	projectilesprite.setPosition(projectilesprite.getPosition().x + (move.x / (speed*100)), projectilesprite.getPosition().y + (move.y / (speed*100)));
	}
	else
		projectilesprite.setPosition(projectilesprite.getPosition().x + (move.x / speed), projectilesprite.getPosition().y + (move.y / speed));

}
void Projectile::collission()
{
	for (auto i : Round::getInstance()->getAllDrones()) //Überprüft, ob das Projektil auf eine Drohne aus der Liste trifft
	{
		if (!collided)
		{
			if (projectilesprite.getGlobalBounds().intersects(i->getDroneSprite().getGlobalBounds()))
			{
				i->takeDamage(tower->getDamage()); //Drohne nimmt Schaden
				collided = true;
				tower->addDamageCount();
				delete this;
			}
		}
	}


}
#pragma endregion

#pragma region getter
bool Projectile::getcollided()
{
	return collided;
}
Sprite* Projectile::getProjectileSprite()
{
	return &projectilesprite;
}
Vector2f Projectile::getTargetstill()
{
	return targetstill;
}
#pragma endregion

#pragma region setter
void Projectile::setmove()
{
	move.x = -1 * (tower->getTowerPos().x - target.x);
	move.y = -1 * (tower->getTowerPos().y - target.y);
}
void Projectile::setBlitzcooldown(int a)
{
	blitzcooldown = a;
}
#pragma endregion

#pragma region Desturktor
Projectile::~Projectile()
{
	//Entfernt das Projektil aus der Liste in Round
	Round::getInstance()->deleteProjectile(this);
}
#pragma endregion