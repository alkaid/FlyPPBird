#include "GameLayer.h"
#include "R.h"

USING_NS_CC;

GameLayer::GameLayer()
{
	_land = NULL;
	_batchNode = NULL;
	_bird = nullptr;
	_status = ready;
}

GameLayer::~GameLayer()
{
	CC_SAFE_RELEASE_NULL(_land);
}

bool GameLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!BaseLayer::init());
		//init land
		_land = Land::create();
		_land->retain();
		Ref* obj = NULL;
		_batchNode = SpriteBatchNode::createWithTexture(TextureCache::getInstance()->getTextureForKey(R::main_png));
		_batchNode->setPosition(origin);
		this->addChild(_batchNode, 0);
		CCARRAY_FOREACH(_land->getLands(), obj){
			Sprite* sprite = (Sprite*)obj;
			_batchNode->addChild(sprite);
		};
		//init GroundBody
		float landHeight = _land->getOneLandSize().height;
		Node* groundNode = Node::create();
		PhysicsBody* groundBody = PhysicsBody::createBox(Size(visibleSize.width,landHeight));
		groundBody->setDynamic(false);
		groundBody->setLinearDamping(0);
		groundBody->setContactTestBitmask(-1);
		groundNode->setPhysicsBody(groundBody);
		groundNode->setPosition(origin.x + visibleSize.width/2, origin.y + landHeight / 2);
		this->addChild(groundNode);
		//init bird
		_bird = Bird::creat();
		_bird->setPosition(origin.x + visibleSize.width /3, origin.y + visibleSize.height / 2);
		_batchNode->addChild(_bird);
		_bird->idle();
		PhysicsBody* birdBody = PhysicsBody::create();
		birdBody->addShape(PhysicsShapeCircle::create(Bird::BIRD_RADIUS));
		birdBody->setDynamic(true);
		birdBody->setLinearDamping(0);
		birdBody->setContactTestBitmask(-1);
		birdBody->setGravityEnable(false);
		_bird->setPhysicsBody(birdBody);
		//

		this->scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}

void GameLayer::update(float dt)
{
	_land->scroll();
}

void GameLayer::onTouch()
{
	switch (_status)
	{
	case ready:
		_delegate->onGameStart();
		_status = start;
		_bird->fly();
		_bird->getPhysicsBody()->setGravityEnable(true);
		_bird->getPhysicsBody()->setVelocity(Vect(0, 260));
		break;
	case start:
		_bird->getPhysicsBody()->setVelocity(Vect(0, 260));
		break;
	case end:
		break;
	default:
		break;
	}
}

