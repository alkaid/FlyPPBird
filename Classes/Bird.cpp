#include "Bird.h"
#include "R.h"

USING_NS_CC;

Bird::Bird()
{
	_state = IDLE;
	_idleAction = nullptr;
	_swingAction = nullptr;
}

Bird::~Bird()
{

}

bool Bird::init()
{
	bool bRet = false;
	do 
	{
		//random color for a new bird
		int type = rand() % 3;
		CC_BREAK_IF(!Sprite::initWithSpriteFrameName(__String::createWithFormat(R::bird_fmt,type,0)->getCString()));
		//create idle action
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(1.0 / 10.0);
		for (int i = 0; i < 3; i++){
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(__String::createWithFormat(R::bird_fmt, type, i)->getCString());
			animation->addSpriteFrame(frame);
		}
		_idleAction = RepeatForever::create(Animate::create(animation));
		//create swing action
		ActionInterval* up = MoveBy::create(0.4f, Point(0, 8));
		ActionInterval* back = up->reverse();
		_swingAction = RepeatForever::create(Sequence::create(up, back,NULL));
		bRet = true;
	} while (0);
	return bRet;
}

Bird* Bird::creat()
{
	Bird *sprite = new Bird();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Bird::idle()
{
	_state = IDLE;
	this->runAction(_idleAction);
	this->runAction(_swingAction);
}

void Bird::fly()
{
	_state = FLY;
	this->stopAction(_swingAction);
}

void Bird::die()
{
	_state = DIE;
	this->stopAllActions();
}

