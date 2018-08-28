#include "JoyStick.h"
#include "Hero.h"
#include "CommonData.h"
USING_NS_CC;

bool JoyStick::init()
{

	if (!Layer::init()) {
		return false;
	}

	/*1. 创建摇杆的背景*/
	this->rocker_bg = Sprite::create("yaogancir1.png");
	rocker_bg->setPosition(Point(150, 150));
	addChild(rocker_bg,99,10);
	this->setVisible(false);

	/*2. 创建摇杆*/
	this->rocker = Sprite::create("yaogandot1.png");
	rocker->setPosition(Point(150, 150));
	addChild(rocker,99,11);
	this->setVisible(false);
	touchsucceed = false;

	return true;
}

void JoyStick::onEnter()
{
	/*首先调用父类的onEnter方法*/
	Layer::onEnter();

	/*开启单点触摸的监听, 可以用auto*/
	listener = EventListenerTouchOneByOne::create();

	/*可以使用lambda表达式来创建，但那样看起来太乱, 这里我们还是使用回调函数*/
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);

	/*注册监听*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

/*当前对象从父类上移除时会调用该方法*/
void JoyStick::onExit()
{
	/*从分发中心移除注册的监听*/
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	/*最后调用父类的onExit()方法*/
	Layer::onExit();
}

bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (touch->getLocation().x < VISIBLE_SIZE.width / 2){
		this->setVisible(true);
		/*当触摸开始的时候， 如果触摸点的位置和我们中心点位置的距离 < 圆的半径 我们才能Move*/
		/*获取触摸点位置*/
		Point touch_pos = touch->getLocation();
		//获取圆心点
		Point center = touch_pos;
		center_x = touch_pos.x;
		center_y = touch_pos.y;
		//摇杆半径
		radius = rocker_bg->getContentSize().width / 2;
		rocker->setPosition(touch_pos);
		this->getChildByTag(11)->setPosition(center);
		this->getChildByTag(10)->setPosition(center);
		touchsucceed = true;
		return true;
	}

}

void JoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (touchsucceed){
		/*当触摸移动的时候， 如果触摸点的位置和我们中心点位置的距离 < 圆的半径 */
		/*获取触摸点位置*/
		Point touch_pos = touch->getLocation();
		/*获取圆心点*/
		float dis = sqrt(pow((touch->getLocation().x - center_x), 2) + pow((touch->getLocation().y - center_y), 2));
		float angle = acos((touch_pos.x - center_x) / dis);

		if (dis <= radius) {
			rocker->setPosition(Point(touch_pos));
		}
		else {
			/*如果在上半圆*/
			if (touch_pos.y >  center_y) {
				rocker->setPosition(Point(center_x + radius*cos(angle), center_y + radius*sin(angle)));
			}
			else {
				rocker->setPosition(Point(center_x + radius*cos(angle), center_y - radius*sin(angle)));
			}
		}
		if (touch_pos.x > center_x){
			hero->setWalking(false, Hero::BTN_LEFT);
			hero->setWalking(true, Hero::BTN_RIGHT);
		}
		else{
			hero->setWalking(false, Hero::BTN_RIGHT);
			hero->setWalking(true, Hero::BTN_LEFT);

		}
	}

}

void JoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*在结束触摸时，摇杆消失*/
	this->setVisible(false);
	touchsucceed = false;
	hero->setWalking(false, Hero::BTN_RIGHT);
	hero->setWalking(false, Hero::BTN_LEFT);
}

void JoyStick::setHero(Hero* h){
	this->hero = h;
}

