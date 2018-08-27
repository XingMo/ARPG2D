#include "TestMap.h"
#include "Terrain.h"
#include "Hero.h"

Scene * TestMap :: createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0,-600.0f));
	auto layer = TestMap::create();
	scene->addChild(layer);
	return scene;
}

bool TestMap ::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	tSpriteFrameCache->addSpriteFramesWithFile("grass.png");
	tSpriteFrameCache->addSpriteFramesWithFile("brick.png");

	tSpriteFrameCache->addSpriteFramesWithFile("asd.plist");

	auto Map_Bg = Sprite :: create("background_n2.png");
	Map_Bg->setPosition(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height / 2);
	Map_Bg->setScaleX(0.625f);
	Map_Bg->setScaleY(0.8f);
	this->addChild(Map_Bg,0);

	//英雄不能移动区域添加普通块
	for(int i = 0;i < 10;i++)
	{
		auto ground = Sprite :: create("grass.png");
		ground->setPosition((12.5 + 25 * i) ,12.5);
		ground->setScaleX(0.5f);
		ground->setScaleY(0.5f);
		ground->getTexture()->setAliasTexParameters();
		this->addChild(ground,1,i);
	}
	for(int i = 0;i < 14;i++)
	{
		auto ground = Sprite :: create("grass.png");
		ground->setPosition((312.5 + 25 * i) ,12.5);
		ground->setScaleX(0.5f);
		ground->setScaleY(0.5f);
		ground->getTexture()->setAliasTexParameters();
		this->addChild(ground,1,i + 10);
	}
	for(int i = 0;i < 2;i++)
	{
		auto brick = Sprite :: create("brick.png");
		brick->setPosition((175 + 50 * i) ,50);
		brick->getTexture()->setAliasTexParameters();
		this->addChild(brick,1,i + 24);
	}
	for(int i = 0;i < 19;i++)
	{
		auto brick = Sprite :: create("brick.png");
		brick->setPosition(12.5 ,37.5 + 25 * i);
		brick->setScaleX(0.5f);
		brick->setScaleY(0.5f);
		brick->getTexture()->setAliasTexParameters();
		this->addChild(brick,1,i + 31);
	}

	for(int i = 0;i < 19;i++)
	{
		auto brick = Sprite :: create("brick.png");
		brick->setPosition(627.5 ,37.5 + 25 * i);
		brick->setScaleX(0.5f);
		brick->setScaleY(0.5f);
		brick->getTexture()->setAliasTexParameters();
		this->addChild(brick,1,i + 51);
	}

	//英雄可移动区域添加物理特性块
	auto brick1 = Terrain :: create();
	brick1->initSprite("brick.png");
	brick1->initPhysicsBody();
	brick1->setPosition(175 ,50);
	brick1->getTexture()->setAliasTexParameters();
	this->addChild(brick1,1,30);

	auto brick2 = Terrain :: create();
	brick2->initSprite("brick.png");
	brick2->initPhysicsBody();
	brick2->setPosition(225 ,100);
	brick2->getTexture()->setAliasTexParameters();
	this->addChild(brick2,1,30);

	for(int i = 0;i < 2;i++)
	{
		auto brick = Terrain :: create();
		brick->initSprite("brick.png");
		brick->initPhysicsBody();
		brick->setPosition((325 + 50 * i) ,50);
		brick->getTexture()->setAliasTexParameters();
		this->addChild(brick,1,i + 26);
	}

	for(int i = 0;i < 4;i++)
	{
		auto brick = Terrain :: create();
		brick->initSprite("brick.png");
		brick->initPhysicsBody();
		brick->setPosition(12.5 ,37.5 + 25 * i);
		brick->setScaleX(0.5f);
		brick->setScaleY(0.5f);
		brick->getTexture()->setAliasTexParameters();
		this->addChild(brick,1,i + 70);
	}

	for(int i = 0;i < 4;i++)
	{
		auto brick = Terrain :: create();
		brick->initSprite("brick.png");
		brick->initPhysicsBody();
		brick->setPosition(627.5 ,37.5 + 25 * i);
		brick->setScaleX(0.5f);
		brick->setScaleY(0.5f);
		brick->getTexture()->setAliasTexParameters();
		this->addChild(brick,1,i + 70);
	}

	for(int i = 0;i < 5;i++)
	{
		auto ground = Terrain :: create();
		ground->initSprite("grass.png");
		ground->initPhysicsBody();
		ground->setPosition((37.5 + 25 * i) ,12.5);
		ground->setScaleX(0.5f);
		ground->setScaleY(0.5f);
		ground->getTexture()->setAliasTexParameters();
		this->addChild(ground,1,i);
	}

	for(int i = 0;i < 10;i++)
	{
		auto ground = Terrain :: create();
		ground->initSprite("grass.png");
		ground->initPhysicsBody();
		ground->setPosition((412.5 + 25 * i) ,12.5);
		ground->setScaleX(0.5f);
		ground->setScaleY(0.5f);
		ground->getTexture()->setAliasTexParameters();
		this->addChild(ground,1,i);
	}

	//添加英雄
	auto hero = Hero::create("Hero");
	hero->initSprite("YanMo.png");
	hero->setPosition(hero->getContentSize().width / 2,this->getContentSize().height /2 + 25);
	hero->initPhysicsBody();
	this->addChild(hero,1,3);

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