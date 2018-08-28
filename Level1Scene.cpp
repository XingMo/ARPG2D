#include "Level1Scene.h"
#include "Terrain.h"
#include "Hero.h"
#include "Damage.h"
#include "CommonData.h"
#include "JoyStick.h"

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

	tSpriteFrameCache->addSpriteFramesWithFile("asd.plist");
	tSpriteFrameCache->addSpriteFramesWithFile("HelloWorld.png");
	tSpriteFrameCache->addSpriteFramesWithFile("yeyan.png");
	
	auto ground = Terrain::create();
	ground->initSprite("HelloWorld.png");
	ground->setPosition(Director::getInstance()->getVisibleSize().width/2 , 0);
	ground->initPhysicsBody();
	this->addChild(ground);

	auto ground2 = Terrain::create();
	ground2->initSprite("HelloWorld.png");
	ground2->setPosition(ground->getPositionX() + ground->getContentSize().width , 
		ground->getPositionY() + ground->getContentSize().height);
	ground2->initPhysicsBody();
	this->addChild(ground2);

	auto hero = Hero::create("Hero");
	hero->initSprite("YanMo.png");
	hero->setPosition(ground->getPositionX(), ground->getContentSize().height + 100);
	hero->initPhysicsBody();
	this->addChild(hero, 0, 101);

	auto damage=Damage::create(1,8);
	damage->initSprite("yeyan.png");
	damage->setPosition(ground->getPositionX(),ground->getPositionY()+ground->getContentSize().height);
	damage->initPhysicsBody();
	this->addChild(damage, 1, 120);
	
	JoyStick* rocker = JoyStick::create();
	rocker->setPosition(Point::ZERO);
	rocker->setHero(hero);
	addChild(rocker, 99);

	auto spriteBoom = Sprite::create("CloseSelected.png");
	auto menuItemBoom = MenuItemSprite::create(spriteBoom, spriteBoom, [=](Ref *){
		hero->actJump();
	});
	menuItemBoom->setPosition(VISIBLE_SIZE.width*2 / 3, VISIBLE_SIZE.height / 3);
	menuItemBoom->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

	auto menu = Menu::create();
	menu->addChild(menuItemBoom, 99, 100);
	//Ä¬ÈÏ²Ëµ¥×ø±êÖÃÁã
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 99, 101);

	typedef EventKeyboard::KeyCode KeyCode;
	auto kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = [=](KeyCode code, Event* event){
		//hero_lastPosition_1 = hero->getPositionX();
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
		//hero_lastPosition_2 = hero->getPositionX();
		//Level1Scene::ScreenMove();
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

//void Level1Scene::ScreenMove(){
//	auto hero = this->getChildByTag(2);
//	float x = hero->getPosition().x;
//	float y = hero->getPosition().y;
//	auto targetPosition = Point(m_LastPositionX - x, 0);
//
	//auto child = this->getChildByTag(1);
	////x = MAX(x, VISIBLE_SIZE.width / 2);
	////y = MAX(y, VISIBLE_SIZE.height / 2);
	////x = min(x, mapsize.width*maptilesize.width - screensize.width / 2);
	////y = min(y, mapsize.height*maptilesize.height - screensize.height / 2);
	//
	//child->runAction(MoveBy::create(0.1f, Point(targetPosition)));
	//this->getScene()->setPosition(targetPosition);

//}