#include "Level1Scene.h"
#include "Terrain.h"
#include "Hero.h"

#include "CommonData.h"

USING_NS_CC;

Scene* Level1Scene::createScene()
{
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0,-600.0f));
    auto layer = Level1Scene::create();
    scene->addChild(layer);
    return scene;
}


bool Level1Scene::init()
{
    if ( !Layer::init() ){ return false; }


	tSpriteFrameCache->addSpriteFramesWithFile("HelloWorld.png");
	tSpriteFrameCache->addSpriteFramesWithFile("CloseNormal.png");
	tSpriteFrameCache->addSpriteFramesWithFile("asd.plist");

	auto ground = Terrain::create();
	ground->initSprite("HelloWorld.png");
	ground->setPosition(Director::getInstance()->getVisibleSize().width/2 , 0);
	ground->initPhysicsBody();
	this->addChild(ground);
    
	auto hero = Hero::create("Hero");
	hero->initSprite("YanMo.png");
	hero->setPosition(ground->getPositionX(), ground->getContentSize().height+100);
	hero->initPhysicsBody();
	this->addChild(hero);

	typedef EventKeyboard::KeyCode KeyCode;
	auto kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = [=](KeyCode code, Event* event){
		switch (code) {
		case KeyCode::KEY_LEFT_ARROW:
			hero->setWalking(true, Hero::BTN_LEFT);
			break;
		case KeyCode::KEY_RIGHT_ARROW:
			hero->setWalking(true, Hero::BTN_RIGHT);
			break;
		case KeyCode::KEY_UP_ARROW:
			hero->actJump();
			break;
		default:
			break;
		}
	};

	kbListener->onKeyReleased = [=](KeyCode code, Event* event){
		switch (code) {
		case KeyCode::KEY_LEFT_ARROW:
			hero->setWalking(false, Hero::BTN_LEFT);
			break;
		case KeyCode::KEY_RIGHT_ARROW:
			hero->setWalking(false, Hero::BTN_RIGHT);
			break;
		default:
			break;
		}
	};

	tDirector->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kbListener, this);

    return true;
}

