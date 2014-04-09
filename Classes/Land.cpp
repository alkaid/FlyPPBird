#include "Land.h"
#include "R.h"

USING_NS_CC;

Land::Land()
{
	count = 0;
	lands = NULL;
}

Land::~Land()
{
	CC_SAFE_RELEASE_NULL(lands);
}

bool Land::init()
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* measureLand = Sprite::createWithSpriteFrameName(R::land);
	count = (visibleSize.width * 2 - 1) / measureLand->getContentSize().width;
	lands = __Array::createWithCapacity(count);
	lands->retain();
	for (int i = 0; i < count; i++){
		Sprite* land = Sprite::createWithSpriteFrameName(R::land);
		land->setAnchorPoint(Point::ZERO);
		land->setPosition(origin.x + land->getContentSize().width*i, origin.y);
		lands->addObject(land);
	}
	return true;
}

