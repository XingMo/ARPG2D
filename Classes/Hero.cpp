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
	this->m_iAttacking = 0;
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
	body->setCategoryBitmask(2);
	body->setContactTestBitmask(1);
	body->setCollisionBitmask(1);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);

	EventListenerPhysicsContact* evListener = EventListenerPhysicsContact::create();
	evListener->onContactBegin = [this] (PhysicsContact& contact) { return true;};
	evListener->onContactPreSolve = [this] (PhysicsContact& contact, PhysicsContactPreSolve& presolve) {
		this->actWalk(false, this->m_iWalking);
		return true;
	};
	evListener->onContactSeperate = [this](PhysicsContact& contact){
		//this->m_iWall = 0;
		this->actWalk(true, this->m_iWalking);
	};
	tDirector->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evListener, this);
}

bool Hero::initSprite(std::string name) {
	SpriteFrame* spFrame = nullptr;
	if( spFrame = tSpriteFrameCache->getSpriteFrameByName(name) ){
		this->initWithSpriteFrame(spFrame);
		this->setContentSize(this->getTextureRect().size);
		return 1;
	}
	CCLOG("SpriteFrameName Fail");
	//if( this->initWithFile(name) ){
	//	this->setContentSize(this->getTextureRect().size);
	//	return 1;
	//}
	return 0;
}

void Hero::setWalking(bool stat, int btn) {

	if(stat) while(!(m_iWalking&btn)) m_iWalking ^= btn;
	if(!stat) while(m_iWalking&btn) m_iWalking ^= btn;
	//CCLOG("stat:%d btn:%d iWalk:%d\n", stat, btn, m_iWalking);
	
	if(m_iWalking&Hero::BTN_LEFT) m_bDirection = Hero::DIREC_LEFT;
	if(m_iWalking&Hero::BTN_RIGHT) m_bDirection = Hero::DIREC_RIGHT;
	if((m_iWalking&Hero::BTN_LEFT) && (m_iWalking&Hero::BTN_RIGHT))
		m_bDirection = btn==Hero::BTN_LEFT ?  Hero::DIREC_LEFT : Hero::DIREC_RIGHT;
	this->setFlippedX(!m_bDirection);
	
}

int Hero::isWalking() {
	// have speed in x-direction
	return this->m_iWalking;
}

void Hero::setAttacking(bool stat, int btn) {
	//if(stat) while(!(this->m_iAttacking&btn)) this->m_iAttacking ^= btn;
	//if(!stat) while(this->m_iAttacking&btn) this->m_iAttacking ^= btn;
	if(stat) this->m_iAttacking = 1;
	else this->m_iAttacking = 0;
}

int Hero::isAttacking() { return this->m_iAttacking; }

void Hero::resetAction() {
	this->m_iActionStat = Hero::NORMAL;
}

void Hero::actJump() {
	if(!this->m_bOnGround) return;
	Vect v = this->getPhysicsBody()->getVelocity() + Vect(0, 300);
	this->getPhysicsBody()->setVelocity(v);
}

void Hero::actWalk(bool b, int walkMask) {
	Vect &v = this->m_vcWalkingVect;
	v.x = 0;
	if(b) {
		if(walkMask & Hero::BTN_LEFT) v.x += -100;
		if(walkMask & Hero::BTN_RIGHT) v.x += 100;
	}
	this->getPhysicsBody()->setVelocity(Vect(v.x, this->getPhysicsBody()->getVelocity().y) );
}

void Hero::actAttack(bool b, int){
	// create Damage here
}

int Hero::getGroup() { return this->m_iGroup; }

void Hero::setGroup(int group) { this->m_iGroup = group; }


void Hero::updateAction() {
	this->stopAllActions();
	auto anim = Animation::create();
	switch (this->m_iActionStat)
	{
	case Hero::NORMAL:
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
		anim->setDelayPerUnit(0.5f);
		anim->setLoops(-1);
		this->runAction(Animate::create(anim));
		if(this->m_bOnGround){
			//hero on ground normal
		} else { 
			//hero on air normal
		}
		break;
	case Hero::WALK:
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_run.png"));
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
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
		log("attacking");
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

	// execute in action priority
	int oldStat = m_iActionStat;
	m_iActionStat = Hero::NORMAL;
	if(this->m_iWalking) m_iActionStat = Hero::WALK;
	if(this->m_iAttacking) m_iActionStat = Hero::ATTACK;
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