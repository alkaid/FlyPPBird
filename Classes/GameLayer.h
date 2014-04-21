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
	/*��ҵȴ����پ����ʼ*/
	static const float PLAYER_READY_DISTANCE;
	/*�ܵ�֮���ˮƽ����*/
	static const float PIPE_SPACING_HORIZON;
	/*���¹ܵ�֮�����*/
	static const float PIPE_SPACING_VERTICAL;
	/*�ϻ��¹ܵ�������ʾ�ĳ��� */
	static const float PIPE_SHOW_MIN;
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
	Size _pipeSize;
	__Array* _pipeNodes;
	int _pipeNodesCount;
	int _score;
	bool _isNewRecord;
	std::vector<bool> _isNews;
	void createPipes();
	float getRandomHeight();
	void rotateBird();
	void checkHit();
	void gameOver();
};