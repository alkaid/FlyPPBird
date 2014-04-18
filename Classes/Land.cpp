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
	_landSize = measureLand->getContentSize();
	count = (visibleSize.width * 2 - 1) / _landSize.width+1;	//保证滚动连续
	lands = __Array::createWithCapacity(count);
	lands->retain();
	for (int i = 0; i < count; i++){
		Sprite* land = Sprite::createWithSpriteFrameName(R::land);
		land->setAnchorPoint(Point::ZERO);
		land->setPosition(origin.x + land->getContentSize().width*i, origin.y);
		land->getTexture()->setAliasTexParameters();
		lands->addObject(land);
	}
	return true;
}

void Land::scroll(float speed)
{
	Ref* obj = NULL;
	CCARRAY_FOREACH(lands, obj){
		Sprite* land = (Sprite*)obj;
		land->setPositionX(land->getPositionX() - speed);
	}
	for (int i = 0; i < count; i++){
		Sprite* land = (Sprite*)(lands->getObjectAtIndex(i));
		if (land->getPositionX() < origin.x - land->getContentSize().width){
			int last = i - 1 < 0 ? count - 1 : i - 1;
			Sprite* lastLand = (Sprite*)(lands->getObjectAtIndex(last));
			land->setPositionX(lastLand->getPositionX() + lastLand->getContentSize().width);
		}
	}
}

Size Land::getOneLandSize()
{
	return _landSize;
}

