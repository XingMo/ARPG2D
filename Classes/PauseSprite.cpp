#include "PauseSprite.h"


PauseScene:: PauseScene()
{}

PauseScene::~PauseScene()
{}

Scene* PauseScene::createScene(RenderTexture* sqr)
{
	Scene *scene = Scene::create();

    PauseScene *layer = PauseScene::create();

	scene->addChild(layer,99,125);

	//add Sprite to GamePause

	Sprite *backSprite = Sprite::createWithTexture(sqr->getSprite()->getTexture());  

	backSprite->setPosition(Point(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/2)); 

	backSprite->setFlipY(true);

	backSprite->setColor(ccGRAY);//set the color

	scene->addChild(backSprite,0,111);

	//add pause menu
	/*
	Sprite* back_pause = Sprite::create("back_pause.png");

	back_pause->setPosition(Point(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/2)); 

	scene->addChild(back_pause);
	*/
	return scene;
}


PauseScene* PauseScene::create()
{
    auto pause = new PauseScene();
    if( pause && pause->init() ) {
        pause->autorelease();
        return pause;
    }
    delete pause;
    pause = NULL;
    return NULL;
}


bool PauseScene::init()
{
	if(!Layer::init()) 
		return false;

	//continue game
	auto gameConti = Sprite::create("CloseNormal.png");//createWithSpriteFrameName
	auto menuItemBack = MenuItemSprite::create(gameConti, gameConti, [=](Ref *){
		//this->clearPause();
		Director::getInstance()->popScene();
	});
	menuItemBack->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/1.5-30);
	
	auto menu1 = Menu::create(menuItemBack, NULL);
	menu1->setPosition(Point::ZERO);
	this->addChild(menu1,99,126);

	//restart  game 
	auto gameRestar = Sprite::create("CloseNormal.png");
	auto menuItemBack2 = MenuItemSprite::create(gameRestar, gameRestar, [](Ref *){
		auto scene = Level1Scene::createScene();
		Director::getInstance()->replaceScene(scene);
		//Director::getInstance()->resume();
	});
	menuItemBack2->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/1.5-75);
	auto menu2 = Menu::create(menuItemBack2, NULL);
	menu2->setPosition(Point::ZERO);
	this->addChild(menu2,99,127);

	//setting
	auto gameSet = Sprite::create("CloseNormal.png");
	auto menuItemBack3 = MenuItemSprite::create(gameSet, gameSet, [](Ref *){
		//auto scene = Level1Scene::createScene();
		//Director::getInstance()->replaceScene(scene);
		//Director::getInstance()->resume();
	});
	menuItemBack3->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/1.5-120);
	auto menu3 = Menu::create(menuItemBack3, NULL);
	menu3->setPosition(Point::ZERO);
	this->addChild(menu3,99,128);

	//exit game
	auto gameExit = Sprite::create("CloseNormal.png");
	auto menuItemBack4 = MenuItemSprite::create(gameExit, gameExit, [](Ref *){
		Director::getInstance()->end();
	});
	menuItemBack4->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/1.5-165);
	auto menu4 = Menu::create(menuItemBack4, NULL);
	menu4->setPosition(Point::ZERO);
	this->addChild(menu4,99,129);

	return true;
}

