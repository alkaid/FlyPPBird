#pragma once
#include "cocos2d.h"
#include "BaseLayer.h"
#include "GameLayer.h"

USING_NS_CC;

class StatusLayer:public BaseLayer,public StatusDelegate
{
public:
	StatusLayer();
	virtual ~StatusLayer();
	virtual bool init();
	CREATE_FUNC(StatusLayer);
	void showReady();
	virtual void onGameStart();
	virtual void onGamePlaying(int score);
	virtual void onGameReady();
	virtual void onGameEnd();
private:
	bool _isNewScore;
	int _score;
	SpriteBatchNode* _batchNode;
	Sprite* _readyTitleSprite;
	Sprite* _readyTipSprite;
	LabelAtlas* _scoreLabel;

	
};
