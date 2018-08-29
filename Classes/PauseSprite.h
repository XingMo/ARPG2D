#ifndef	_PAUSESPRITE__H_
#define _PAUSESPRITE__H_

#include "CommonData.h"
#include "Level1Scene.h"
#include "GameOverScene.h"

USING_NS_CC;

class  PauseScene: public Layer {
public:
     PauseScene();

	~PauseScene();

    static PauseScene* create();

	static Scene* createScene(RenderTexture*);

    bool init();

};

#endif