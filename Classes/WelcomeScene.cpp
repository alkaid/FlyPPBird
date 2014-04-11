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
		//_batchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey(R::main_png));
		//_batchNode->setPosition(origin);
		//this->addChild(_batchNode,0);
		//CCARRAY_FOREACH(_land->getLands(), obj){
		//	Sprite* sprite = (Sprite*)obj;
		//	_batchNode->addChild(sprite);
		//};
		////init bird
		//_bird = Bird::creat();
		//_bird->setPosition(origin.x + visibleSize.width / 2, origin.y + _land->getOneLandSize().height + (visibleSize.height - _land->getOneLandSize().height) / 2);
		//_batchNode->addChild(_bird);
		//_bird->idle();
		////init logo
		//Sprite* logo = Sprite::createWithSpriteFrameName(R::text_game_name);
		//logo->setPosition(_bird->getPositionX(), _bird->getPositionY() + _bird->getContentSize().height/2+40);
		//_batchNode->addChild(logo);
		////init menu
		//Sprite* btnRate = Sprite::createWithSpriteFrameName(R::btn_rate);
		//Sprite* btnPlay = Sprite::createWithSpriteFrameName(R::btn_play);
		//Sprite* btnPlaySelected = Sprite::createWithSpriteFrameName(R::btn_play);
		//Sprite* btnRank = Sprite::createWithSpriteFrameName(R::btn_rank);
		//auto itemRate = MenuItemSprite::create(btnRate, btnRate);
		//auto itemRank = MenuItemSprite::create(btnRank, btnRank);
		//auto itemPlay = MenuItemSprite::create(btnPlay, btnPlaySelected, NULL, CC_CALLBACK_1(WelcomeLayer::onStart, this)); /*[](Ref* obj){
		//	TransitionScene* scene = TransitionScene::create(0.5f, GameScene::create());
		//	Director::getInstance()->replaceScene(scene);
		//	});*/
		//itemRate->setAnchorPoint(Point(0.5, 0));
		//itemRank->setAnchorPoint(Point(0.5, 0));
		//itemPlay->setAnchorPoint(Point(0.5, 0));
		//itemRate->setPosition(_bird->getPositionX(), _bird->getPositionY() - _bird->getContentSize().height/2 - 40);
		//itemPlay->setPosition(itemRate->getPositionX() - itemPlay->getContentSize().width / 2 - 20, itemRate->getPositionY() - itemRate->getContentSize().height - 40);
		//itemRank->setPosition(itemRate->getPositionX() + itemRank->getContentSize().width / 2 + 20, itemPlay->getPositionY() );
		/*Menu* menu = Menu::create(itemPlay,NULL);
		menu->setPosition(origin);
		this->addChild(menu,1);*/

		//add the start-menu to the current scene
		Sprite *startButton = Sprite::createWithSpriteFrameName(R::btn_play);
		Sprite *activeStartButton = Sprite::createWithSpriteFrameName(R::btn_play);
		activeStartButton->setPositionY(5);
		auto menuItem = MenuItemSprite::create(startButton, activeStartButton, NULL, CC_CALLBACK_1(WelcomeLayer::onStart, this));
		menuItem->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 5));

		auto menu = Menu::create(menuItem, NULL);
		menu->setPosition(Point(origin.x, origin.y));
		this->addChild(menu, 1);

		this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void WelcomeLayer::update(float dt)
{
	_land->scroll();
}

void WelcomeLayer::onStart(Ref* sender)
{
	TransitionScene* scene = TransitionScene::create(0.5f, GameScene::create());
	Director::getInstance()->replaceScene(scene);
}

