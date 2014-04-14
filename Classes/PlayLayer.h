#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"

class PlayDelegate
{
public:
	virtual void onTouch() = 0;
private:

};

class PlayLayer:public Layer
{
public:
	PlayLayer();
	virtual ~PlayLayer();
	CC_SYNTHESIZE(PlayDelegate*, _delegate, Delegate);
	virtual bool init();
	CREATE_FUNC(PlayLayer);
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
private:
};
