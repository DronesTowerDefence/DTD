#pragma once
class Money_Health
{
private:
	int money;
	int health;
public:
	Money_Health() {
		money = 0;
		health = 0;
	}
	void addMoney(int _money) {
		money += _money;
	}
	bool submoney(int _money) {
		if (money < _money)
			return 0;
		money -= _money;
		
	}
	int getMoney() {
		return money;
	}
	bool setMoney(int _money) {
		if (_money < 0)
			return 0;
		money = _money;
	}
	void addHealth(int _health) {
		health += _health;
	}
	bool subhealth(int _health) {
		if (health < _health)
			return 0;
		health -= _health;

	}
	int getHealth() {
		return health;
	}
	bool setHealth(int _health) {
		if (_health < 0)
			return 0;
		health = _health;
	}
};

