#ifndef __LEVEL1_SCENE_H__
#define __LEVEL1_SCENE_H__

#include "cocos2d.h"

class Level1Scene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Level1Scene);
};

#endif
