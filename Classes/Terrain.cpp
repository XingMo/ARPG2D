#include "Terrain.h"
USING_NS_CC;

bool Terrain::loadResources() {
	static bool done = false;
	if(done) return 0;
	// load resources here

	done = 1;
	return 1;
}

bool Terrain::init() {
	Terrain::loadResources();
	
	return 1;
}

void Terrain::initPhysicsBody() {
	auto body = PhysicsBody::createEdgeBox(this->getContentSize());
	body->setGravityEnable(false); // Terrain cant afforded by gravity
	body->setDynamic(false);
	this->setPhysicsBody(body);
}

bool Terrain::initSprite(std::string name) {
	return this->initWithFile(name);
}