#include "WelcomeScene.h"
#include "Background.h"
#include "R.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{
	_land = NULL;
	_batchNode = NULL;
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
		bRet = true;
	} while (0);
	return bRet;
}

