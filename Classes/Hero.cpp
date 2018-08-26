#include "Hero.h"
#include "CommonData.h"
USING_NS_CC;

bool Hero::loadResources() {
	static bool done = false;
	if(done) return 0;
	// load resources here

	done = 1;
	return 1;
}

Hero* Hero::create(std::string type) {
	auto hero = new Hero();
	if(hero && hero->init(type)) {
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

bool Hero::init(std::string type) {
	Hero::loadResources();
	// data init
	this->m_sType = type;
	this->m_fHpt = 10.0f;
	this->m_fAtk = 10.0f;
	this->m_iActionStat = Hero::NORMAL;
	this->m_bAttacking = false;
	this->m_iWalking = 0;
	this->m_bDirection = Hero::DIREC_LEFT;
	this->m_vcWalkingVect = Vect(0,0);

	this->scheduleUpdate();
	return 1;
}

void Hero::initPhysicsBody() {
	auto body = PhysicsBody::createBox(this->getContentSize());
	body->getShape(0)->setRestitution(0.0f);
	body->getShape(0)->setFriction(0.0f);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
}

bool Hero::initSprite(std::string name) {
	if( this->initWithSpriteFrameName(name) ){
		this->setContentSize(this->getTextureRect().size);
		return 1;
	}
	return 0;
}

void Hero::setWalking(bool stat, int btn) {
	this->m_iWalking ^= btn;
	CCLOG("stat:%d btn:%d iWalk:%d\n", stat, btn, m_iWalking);
	if( stat ){
		if(btn==Hero::BTN_LEFT) this->m_bDirection = Hero::DIREC_LEFT;
		else this->m_bDirection = Hero::DIREC_RIGHT;
		CCLOG("direc %s\n", stat?"Left":"Right");
		this->setFlippedX(m_bDirection);
	}
	
}

int Hero::isWalking() {
	// have speed in x-direction
	return this->m_iWalking;
}

void Hero::setAttacking(bool b) { this->m_bAttacking = b; }

bool Hero::isAttacking() {return this->m_bAttacking; }

void Hero::actJump() {
	if(!this->m_bOnGround) return;
	Vect v = this->getPhysicsBody()->getVelocity() + Vect(0, 300);
	this->getPhysicsBody()->setVelocity(v);
}

void Hero::actWalk(bool b, int walkMask) {
	static bool m_isWalk = 0;
	static int m_walkMask=0;
	static Vect v;
	if(b==m_isWalk && walkMask == m_walkMask) return;

	v = this->getPhysicsBody()->getVelocity() - this->m_vcWalkingVect;
	this->getPhysicsBody()->setVelocity(v);
	if(b) {
		this->m_vcWalkingVect = Vect(0,0);
		if(this->m_iWalking & Hero::BTN_LEFT ) this->m_vcWalkingVect += Vect(-100,0);
		if(this->m_iWalking & Hero::BTN_RIGHT ) this->m_vcWalkingVect += Vect(100,0);
		v = this->getPhysicsBody()->getVelocity() + this->m_vcWalkingVect;
		this->getPhysicsBody()->setVelocity(v);
	}
	else {
		this->m_vcWalkingVect = Vect(0,0);
	}
	m_isWalk = b;
	m_walkMask = walkMask;
}

void Hero::actAttack(bool b){

}

int Hero::getGroup() { return this->m_iGroup; }

void Hero::setGroup(int group) { this->m_iGroup = group; }


void Hero::updateAction() {
	this->stopAllActions();
	auto anim = Animation::create();
	switch (this->m_iActionStat)
	{
	case Hero::NORMAL:
		this->initWithSpriteFrameName("YanMo.png");
		this->setFlippedX(m_bDirection);
		if(this->m_bOnGround){
			//hero on ground normal
		} else { 
			//hero on air normal
		}
		break;
	case Hero::WALK:
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo_DieandRun.png"));
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo.png"));
		anim->setDelayPerUnit(0.15f);
		anim->setLoops(-1);
		this->runAction(Animate::create(anim));
		if(this->m_bOnGround) {
			// play walking
		}
		else {
			// play normal(on air)
		}
		break;
	case Hero::ATTACK:
		// play attack (cant move)
		break;
	default:
		break;
	}
	return;
}

void Hero::update(float) {
	bool actionShiftFlag = false;

	//check on ground stat
	if(abs(this->getPhysicsBody()->getVelocity().y)>0.01f)
		this->m_bOnGround = false;
	else
		this->m_bOnGround = true;
		// on ground shift -> updateAction

	// place in action priority
	int oldStat = m_iActionStat;
	m_iActionStat = Hero::NORMAL;
	if(this->m_iWalking) m_iActionStat = Hero::WALK;
	if(this->m_bAttacking) m_iActionStat = Hero::ATTACK;
	actionShiftFlag |= (oldStat!=m_iActionStat);
	
	// action update
	if(actionShiftFlag) {
		this->updateAction();
	}

	// control actual moving
	if(this->m_iWalking) {
		if(!this->m_bOnGround) actWalk(true, m_iWalking);
		else {
			if(this->m_iActionStat == Hero::WALK)
				actWalk(true, m_iWalking);
			else 
				actWalk(false, m_iWalking);
		}
	}
	else {
		actWalk(false, m_iWalking);
	}
}