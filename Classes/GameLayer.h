#pragma once
#include "cocos2d.h"
#include "Land.h"
#include "Bird.h"
#include "BaseLayer.h"
#include "PlayLayer.h"

USING_NS_CC;

enum GameStatus
{
	ready,start,end
};

class StatusDelegate
{
public:
	virtual void onGameStart() = 0;
	virtual void onGameReady() = 0;
	virtual void onGameEnd() = 0;
	virtual void onGamePlaying(int score) = 0;
};

class GameLayer :public BaseLayer,public PlayDelegate
{
public:
	GameLayer();
	virtual ~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);
	virtual void update(float dt) override;
	CC_SYNTHESIZE(StatusDelegate*, _delegate, Delegate);
	virtual void onTouch() override;
	CC_SYNTHESIZE(PhysicsWorld*, _world, PhyWorld);
private:
	Land* _land;
	SpriteBatchNode* _batchNode;
	Bird* _bird;
	GameStatus _status;
};
