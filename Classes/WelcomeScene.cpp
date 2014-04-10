#include "WelcomeScene.h"
#include "Background.h"
#include "R.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{
	_land = NULL;
	_batchNode = NULL;
	_bird = nullptr;
}

WelcomeLayer::~WelcomeLayer()
{
	CC_SAFE_RELEASE_NULL(_land);
}

Scene* WelcomeLayer::scene()
{
	WelcomeLayer* layer = WelcomeLayer::create();
	Scene* scene = Scene::create();
	scene->addChild(layer);
	Background* backgroundLayer = Background::create();
	scene->addChild(backgroundLayer,-1);
	return scene;
}

bool WelcomeLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		//init land
		_land = Land::create();
		_land->retain();
		Ref* obj=NULL;
		_batchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey(R::main_png));
		_batchNode->setPosition(origin);
		this->addChild(_batchNode);
		CCARRAY_FOREACH(_land->getLands(), obj){
			Sprite* sprite = (Sprite*)obj;
			_batchNode->addChild(sprite);
		};
		//init bird
		_bird = Bird::creat();
		_bird->setPosition(origin.x + visibleSize.width / 2, origin.y + _land->getOneLandSize().height + (visibleSize.height - _land->getOneLandSize().height) / 2);
		_batchNode->addChild(_bird);
		_bird->idle();
		//init logo
		Sprite* logo = Sprite::createWithSpriteFrameName(R::text_game_name);
		logo->setPosition(_bird->getPositionX(), _bird->getPositionY() + 80);
		_batchNode->addChild(logo);
		//init menu
		/*Sprite* btnRate = Sprite::createWithSpriteFrameName(R::btn_rate);
		Sprite* btnPlay = Sprite::createWithSpriteFrameName(R::btn_play);
		Sprite* btnRank = Sprite::createWithSpriteFrameName(R::btn_rank);
		auto itemRate = MenuItemSprite::create()*/

		this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void WelcomeLayer::update(float dt)
{
	_land->scroll();
}

