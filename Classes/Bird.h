#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum BirdState
{
	IDLE,FLY,DIE
};

class Bird:public Sprite
{
public:
	static const float BIRD_RADIUS;
	Bird();
	virtual ~Bird();
	virtual bool init();
	static Bird* creat();
	void idle();
	void fly();
	void die();
protected:
	BirdState _state;
	Action* _idleAction;
	Action* _swingAction;
private:
};
