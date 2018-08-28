#include "LoadingScene.h"
#include "Level1Scene.h"
#include "TestMap.h"

Scene * LoadingScene :: createScene()
{
	auto scene = Scene :: create();
	auto layer = LoadingScene :: create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene :: init ()
{
	if ( !Layer::init() )
	{
		return false;
	}
	FileUtils::getInstance()->addSearchPath("backgroud");
	FileUtils::getInstance()->addSearchPath("hero");

	tSpriteFrameCache->addSpriteFramesWithFile("asd.plist");

	auto Loading_Bg = Sprite :: create("startbackground.png");
	Loading_Bg->setPosition(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height / 2);
	Loading_Bg->setScaleX(0.6f);
	this->addChild(Loading_Bg,0);

	//int Type = rand() % 2;
	auto animation = Animation :: create();
	auto icon = Sprite::createWithSpriteFrameName("YanMo.png");
	icon->setPosition(VISIBLE_SIZE.width -50,60);
	this->addChild(icon,1);
	animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo.png"));
	animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo_hit1.png"));
	animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo_hit2.png"));
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(2);
	
	auto callFunc = CallFunc::create([=]()
	{
		//跳转场景的代码
		auto scene = TestMap :: createScene();
		Director::getInstance()->replaceScene(scene);
	});
	auto animate  = Animate :: create(animation);
	//icon->runAction(animate);
	icon->runAction(Sequence :: create(animate,callFunc,nullptr));
	return true;
	/*
	if(Type == 0)
	{
		icon->setSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
		icon->setPosition(visiblesize.width - 30,40);
		this->addChild(icon,1);
		animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
		animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero2.png"));
		animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_run.png"));
		animation->setLoops(4);
		icon->runAction(Animate::create(animation));
	}
	*/
}