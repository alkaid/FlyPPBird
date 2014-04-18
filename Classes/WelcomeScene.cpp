#include "WelcomeScene.h"
#include "Background.h"
#include "GameScene.h"
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
		this->addChild(_batchNode,0);
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
		logo->setPosition(_bird->getPositionX(), _bird->getPositionY() + _bird->getContentSize().height/2+40);
		_batchNode->addChild(logo);
		//init menu
		Sprite* btnRate = Sprite::createWithSpriteFrameName(R::btn_rate);
		Sprite* btnPlay = Sprite::createWithSpriteFrameName(R::btn_play);
		Sprite* btnPlaySelected = Sprite::createWithSpriteFrameName(R::btn_play);
		Sprite* btnRank = Sprite::createWithSpriteFrameName(R::btn_rank);
		auto itemRate = MenuItemSprite::create(btnRate, btnRate);
		auto itemRank = MenuItemSprite::create(btnRank, btnRank);
		auto itemPlay = MenuItemSprite::create(btnPlay, btnPlaySelected, NULL, [](Ref* obj){
			log("onStartButton click....");
			TransitionScene* scene = TransitionFade::create(0.5f, GameScene::create());
			Director::getInstance()->replaceScene(scene);
		});
		itemRate->setAnchorPoint(Point(0.5, 0));
		itemRank->setAnchorPoint(Point(0.5, 0));
		itemPlay->setAnchorPoint(Point(0.5, 0));
		itemRate->setPosition(_bird->getPositionX(), _bird->getPositionY() - _bird->getContentSize().height/2 - 40);
		itemPlay->setPosition(itemRate->getPositionX() - itemPlay->getContentSize().width / 2 - 20, itemRate->getPositionY() - itemRate->getContentSize().height - 40);
		itemRank->setPosition(itemRate->getPositionX() + itemRank->getContentSize().width / 2 + 20, itemPlay->getPositionY() );
		Menu* menu = Menu::create(itemPlay,itemRank,itemRate,NULL);
		menu->setPosition(origin);
		this->addChild(menu,1);

		this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void WelcomeLayer::update(float dt)
{
	_land->scroll(2);
}

