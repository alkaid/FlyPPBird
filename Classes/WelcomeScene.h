#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
#include "Land.h"

USING_NS_CC;

class WelcomeLayer:public BaseLayer
{
public:
	WelcomeLayer();
	virtual ~WelcomeLayer();
	static Scene*  scene();
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);
protected:
	
private:

};
