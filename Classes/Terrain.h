#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "cocos2d.h"

class Terrain : public cocos2d::Sprite {
public:
	
	static bool Terrain::loadResources(); // resource loader, carried once
	
	CREATE_FUNC(Terrain);

	void initPhysicsBody();

	bool initSprite(std::string);

private:

	std::string m_sType; // Terrain type

	bool Terrain::init();
};

#endif