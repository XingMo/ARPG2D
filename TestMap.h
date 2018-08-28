#ifndef __TEST_MAP_H__
#define __TEST_MAP_H__

#include "CommonData.h"
USING_NS_CC;

class TestMap : public Layer
{
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(TestMap);
};

#endif
