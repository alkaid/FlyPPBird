#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Scene::init());
		bRet = true;
	} while (0);
	return bRet;
}
