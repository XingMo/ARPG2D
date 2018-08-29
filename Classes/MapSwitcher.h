#pragma once

#include "cocos2d.h"

class Hero;
class JoyStick;

class MapSwitcher
{
public:
	static MapSwitcher * getInstance();
	~MapSwitcher();

	void init();

	void setHero(Hero *);
	Hero * getHero();

	void setSwitching(bool isSwitching);

	cocos2d::Scene * getCurMap();
	void setCurMap(int mapType);

	void update(float delta);
	
private:
	static MapSwitcher * instance;

	std::vector<cocos2d::Scene *> * maps;

	Hero * hero;

	bool isSwitching;
	cocos2d::Scene * curMap;
	int curMapNum;

	cocos2d::EventListenerKeyboard * KBListener;
	JoyStick * rocker;

	MapSwitcher();
	MapSwitcher(const MapSwitcher &) {};

	void initMaps();

};

