#include "StatusLayer.h"
#include "R.h"

StatusLayer::StatusLayer()
{
	_batchNode = nullptr;
	_readyTitleSprite = nullptr;
	_readyTipSprite = nullptr;
	_isNewScore = false;
	_scoreLabel = nullptr;
	_score = 0;
}

StatusLayer::~StatusLayer()
{

}

bool StatusLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		_batchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey(R::main_png));
		_batchNode->setPosition(origin);
		this->addChild(_batchNode, 0);
		_scoreLabel = LabelAtlas::create("0", R::number_l, 24, 36, '0');
		_scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height* 4 / 5);
		this->addChild(_scoreLabel);
		bRet = true;
	} while (0);
	return bRet;
}

void StatusLayer::showReady()
{
	_readyTipSprite = Sprite::createWithSpriteFrameName(R::tip_fly);
	_readyTipSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	_batchNode->addChild(_readyTipSprite);
	_readyTitleSprite = Sprite::createWithSpriteFrameName(R::text_ready);
	_readyTitleSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + _readyTipSprite->getPositionY()+_readyTipSprite->getContentSize().height/2+_readyTitleSprite->getContentSize().height/2+10);
	_batchNode->addChild(_readyTitleSprite);
	_scoreLabel->setString("0");
}

void StatusLayer::onGameStart()
{
	_scoreLabel->setString("0");
	_readyTitleSprite->runAction(FadeOut::create(1.0));
	_readyTipSprite->runAction(FadeOut::create(1.0));
}

void StatusLayer::onGamePlaying(int score)
{
	_scoreLabel->setString(__String::createWithFormat("%d",score)->getCString());
}

void StatusLayer::onGameReady()
{

}

void StatusLayer::onGameEnd()
{

}

