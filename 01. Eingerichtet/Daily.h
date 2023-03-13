#pragma once
class Daily
{
private:
	int von;
	int bis;
	int leben;
	int geld;
	bool isDaily;
	bool isTowerAllowed[7];
public:
	Daily();

	bool getIsDaily();
	bool getIsTowerAllowed(int index);
	int getVon();
	int getBis();
	int getLeben();
	int getGeld();


	void setIsDaily(bool _isDaily);
	void setIsTowerAllowed(int index, bool isAllowed);
	void setBis(int _bis);
	void setVon(int _von);
	void setGeld(int _geld);
	void setLeben(int _leben);

};

