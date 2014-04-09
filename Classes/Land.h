#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Land:public Ref
{
public:
	Land();
	virtual ~Land();
	virtual bool init();
	CREATE_FUNC(Land);
	void scroll();
protected:
	Point origin;
	Size visibleSize;
	CC_SYNTHESIZE_READONLY(int, count, Count);
	CC_SYNTHESIZE_READONLY(__Array*, lands, Lands);
private:
	
};
