#ifndef __COMMON_DATA_H__
#define __COMMON_DATA_H__

#include "cocos2d.h"

#define VISIBLE_SIZE (cocos2d::Director::getInstance()->getVisibleSize())

#define tDirector (cocos2d::Director::getInstance())
#define tSpriteFrameCache (cocos2d::SpriteFrameCache::getInstance())
#define tAnimationCache (cocos2d::AnimationCache::getInstance())

namespace Setting{
};

namespace PhysicsMask{
	static const int terrain=1;
	static const int hero=2;
	static const int damage=4;
	static const int item=8;
};

#endif