#include "PlayLayer.h"


PlayLayer::PlayLayer()
{
	_delegate = nullptr;
}

PlayLayer::~PlayLayer()
{

}

bool PlayLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = [this](const std::vector<Touch*>& touches, Event *unused_event)->void
		{
			this->_delegate->onTouch();
		};
		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);
	return bRet;
}

void PlayLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	_delegate->onTouch();
}

