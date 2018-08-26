#ifndef __DAMAGE_H__
#define __DAMEGE_H__

#include "cocos2d.h"

class Damage : public cocos2d::Sprite {
public:
	
	static bool loadResources(); // resource loader, carried once

private:
	float m_fDamageValue;
};

#endif