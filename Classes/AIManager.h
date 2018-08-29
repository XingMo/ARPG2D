#pragma once

#include "cocos2d.h"

class Hero;

class AIManager : public cocos2d::Node
{
public:
	AIManager();
	~AIManager();
	
	bool init();
	
	void addChara(Hero * Chara);

	void setHero(Hero * hero);

	CREATE_FUNC(AIManager);

private:
	Hero * hero;

	cocos2d::Vector<Hero *> * freeEnemies;
	cocos2d::Vector<Hero *> * busyEnemies;	// Enemies that found hero

	float calcDis(Hero * enemy);

	void updateStatus(float delta);

	void patrol(float delta);

	void trackAndAttack(float delta);
};

