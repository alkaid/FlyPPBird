#include "WelcomeScene.h"
#include "Background.h"

USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{

}

WelcomeLayer::~WelcomeLayer()
{

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
		bRet = true;
	} while (0);
	return bRet;
}

