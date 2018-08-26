#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
typedef unsigned int uint;

class Hero : public cocos2d::Sprite {

public:
	
	static bool loadResources(); // resource loader, carried once

	// m_iDirection parm
	static const int BTN_LEFT = 1;
	static const int BTN_RIGHT = 2;
	static const bool DIREC_LEFT = 0;
	static const bool DIREC_RIGHT = 1;

	// m_iActionStat parm, in order of priority
	static const uint BUSY = -1;
	static const uint NORMAL = 0; // normal
	static const uint WALK = 1; // walking
	static const uint ATTACK = 2; // attacking

	// group
	static const uint ALLY = 0;
	static const uint ENEMY = 1;

	static Hero* create(std::string);
	
	void initPhysicsBody(); // load a physics body

	bool initSprite(std::string);

	//group (assit damage judging)
	int getGroup();
	void setGroup(int);

	// set button continous pressed stat
	void setWalking(bool,int);
	int isWalking();
	void setAttacking(bool);
	bool isAttacking();
	
	// set actual movement
	void actJump();
	void actWalk(bool, int);
	void actAttack(bool);

	// update only action func
	void updateAction();

private:
	
	std::string m_sType; // character type
	
	std::string m_sName; // name displayed

	int m_iGroup;
	
	float m_fHpt; // health point
	
	float m_fAtk; // attack point
	
	int m_iActionStat; // current action
	bool m_bOnGround; // is onGround
	cocos2d::Vect m_vcWalkingVect; // walking vector
	bool m_bAttacking; // attack button pressed
	int m_iWalking;
	bool m_bDirection; // facing direction
	
	bool init(std::string); // init function
	
	void update(float); // update func (frame)
};

#endif