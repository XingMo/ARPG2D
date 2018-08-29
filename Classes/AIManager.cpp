#include "AIManager.h"

#include "hero.h"

USING_NS_CC;

AIManager::AIManager() {
}

AIManager::~AIManager() {
	delete freeEnemies;
	delete busyEnemies;
}

bool AIManager::init() {
	if (!Node::init())	return false;
	this->freeEnemies = new Vector<Hero *>;
	this->busyEnemies = new Vector<Hero *>;

	this->schedule(schedule_selector(AIManager::updateStatus), 0.4f);

	this->schedule(schedule_selector(AIManager::patrol), 2.0f);
	this->schedule(schedule_selector(AIManager::trackAndAttack), 0.5f);

	return true;
}

void AIManager::addChara(Hero * Chara) {
	this->freeEnemies->pushBack(Chara);
}

void AIManager::setHero(Hero * hero) {
	this->hero = hero;
}

float AIManager::calcDis(Hero * enemy) {
	auto ePos = enemy->getPosition();
	auto disX = this->hero->getPosition().x - ePos.x;
	auto disY = this->hero->getPosition().y - ePos.y;
	return sqrt(disX*disX+disY*disY);
}

void AIManager::updateStatus(float delta) {
	for (int i = 0; i < this->freeEnemies->size(); ++i) {
		auto dis = this->calcDis(this->freeEnemies->at(i));
		if (dis < 200) {
			this->busyEnemies->pushBack(this->freeEnemies->at(i));
			this->freeEnemies->erase(freeEnemies->begin()+i);
		}
	}
	for (int i = 0; i < busyEnemies->size(); ++i) {
		auto dis = this->calcDis(this->busyEnemies->at(i));
		if (dis > 200) {
			this->freeEnemies->pushBack(this->busyEnemies->at(i));
			this->busyEnemies->erase(busyEnemies->begin()+i);
		}
	}
}

void AIManager::patrol(float delta) {
	for (auto e : *(this->freeEnemies)) {
		int randNum = rand()%2;
		e->resetAction();
		e->setWalking(false, Hero::BTN_LEFT);
		e->setWalking(false, Hero::BTN_RIGHT);
		e->runAction(Sequence::create(
			CallFunc::create([e, randNum]() {e->setWalking(true, randNum ? Hero::BTN_LEFT : Hero::BTN_RIGHT);}),
			DelayTime::create(1.9f),
			CallFunc::create([e, randNum]() {e->setWalking(false, randNum ? Hero::BTN_LEFT : Hero::BTN_RIGHT);}),
			nullptr
		));
		// CCLOG("%d", randNum);
	}
	/*if (freeEnemies->empty())	CCLOG("busy");
	else CCLOG("free");*/
}

void AIManager::trackAndAttack(float delta) {
	/*auto detectCallBack = [](PhysicsWorld& world, PhysicsShape& shape, void* userData) -> bool {
		auto nodeA = shape.getBody()->getNode();
		if (nodeA) {
			if (nodeA->getTag() == 16) {
				auto hero =  static_cast<Hero *>(userData);
				auto dis = nodeA->getPosition().x - hero->getPosition().x;
				hero->setWalking(true, dis < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
				Director::getInstance()->getScheduler()->schedule(
					[dis, hero](float delta) {
						hero->setWalking(false, dis < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
					},
					hero->getParent(), 1.0f, 1, 0.5, false, "stopRunning"
				);
				return false;
			}
		}
		return true;
	};*/
	for (auto e : *(this->busyEnemies)) {
		e->resetAction();
		e->setWalking(false, Hero::BTN_LEFT);
		e->setWalking(false, Hero::BTN_RIGHT);
		auto ePos = e->getPosition();
		auto disX = hero->getPosition().x - ePos.x;
			e->setWalking(true, disX < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
		if (abs(disX) < 120) {
			e->setWalking(false, disX < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
			// log("%f", disX);
			// Attack Here
			// if (dis >= 200)	e->setAttacking(false, Hero::ATTACK);
			// if (dis < 120)	e->setAttacking(true, Hero::ATTACK);
		}
		
	}
}
