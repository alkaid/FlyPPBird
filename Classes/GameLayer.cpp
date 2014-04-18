#include "GameLayer.h"
#include "R.h"

USING_NS_CC;

const float GameLayer::PLAYER_READY_DISTANCE = 600;
const float GameLayer::PIPE_SPACING_HORIZON = 140;
const float GameLayer::PIPE_SPACING_VERTICAL = 100;
const float GameLayer::PIPE_SHOW_MIN = 50;

GameLayer::GameLayer()
{
	_land = NULL;
	_batchNode = NULL;
	_bird = nullptr;
	_status = ready;
	_pipeNodes = nullptr;
}

GameLayer::~GameLayer()
{
	CC_SAFE_RELEASE_NULL(_land);
	CC_SAFE_RELEASE_NULL(_pipeNodes);
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
		//init pipes
		_pipeSize = Sprite::createWithSpriteFrameName(R::pipe_green_bottom)->getContentSize();
		_pipeNodesCount = visibleSize.width / PIPE_SPACING_HORIZON + 1;
		_pipeNodes = __Array::createWithCapacity(_pipeNodesCount);
		for (int i = 0; i < _pipeNodesCount; i++){
			_isNews.push_back(true);
		}
		_pipeNodes->retain();
		createPipes();

		this->scheduleUpdate();

		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = [this](PhysicsContact& contact)->bool
		{
			log("onContactBegin!!");
			return true;
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
		bRet = true;
	} while (0);
	return bRet;
}

void GameLayer::update(float dt)
{
	float speed = 2;
	_land->scroll(speed);
	if (_status == start){
		Ref* obj = nullptr;
		CCARRAY_FOREACH(_pipeNodes, obj){
			Node* pipeNode = (Node*)obj;
			pipeNode->setPositionX(pipeNode->getPositionX() - speed);
		}
		for (int i = 0; i < _pipeNodesCount; i++){
			Node* pipeNode = (Node*)(_pipeNodes->getObjectAtIndex(i));
			if (pipeNode->getPositionX() < origin.x ){
				int last = i - 1 < 0 ? _pipeNodesCount - 1 : i - 1;
				Node* lastLand = (Node*)(_pipeNodes->getObjectAtIndex(last));
				pipeNode->setPosition(lastLand->getPositionX() + PIPE_SPACING_HORIZON,getRandomHeight()+origin.y);
			}
		}
	}
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

void GameLayer::createPipes()
{
	float x = origin.x + visibleSize.width / 2 + PLAYER_READY_DISTANCE;
	for (int i = 0; i < _pipeNodesCount; i++)
	{
		Node* pipeNode = Node::create();
		Sprite* pipeTop = Sprite::createWithSpriteFrameName(R::pipe_green_top);
		Sprite* pipeBottom = Sprite::createWithSpriteFrameName(R::pipe_green_bottom);
		pipeTop->setPosition(0, PIPE_SPACING_VERTICAL / 2 + _pipeSize.height / 2);
		pipeBottom->setPosition(0, -PIPE_SPACING_VERTICAL / 2 - _pipeSize.height / 2);
		pipeNode->addChild(pipeTop);
		pipeNode->addChild(pipeBottom);

		PhysicsBody* pipeBody = PhysicsBody::create();
		pipeBody->addShape(PhysicsShapeBox::create(_pipeSize, PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIPE_SPACING_VERTICAL / 2 + _pipeSize.height / 2)));
		pipeBody->addShape(PhysicsShapeBox::create(_pipeSize, PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, -PIPE_SPACING_VERTICAL / 2 - _pipeSize.height / 2)));
		pipeBody->setDynamic(false);
		pipeBody->setLinearDamping(0);
		pipeBody->setContactTestBitmask(-1);
		pipeBody->setGravityEnable(false);
		pipeNode->setPhysicsBody(pipeBody);

		pipeNode->setPosition(x, getRandomHeight()+origin.y);
		//_batchNode->addChild(pipeNode);	//TODO 这里没找到合适的方法添加进batchNode，直接添加会报错
		this->addChild(pipeNode,-1);
		x += PIPE_SPACING_HORIZON;
		_pipeNodes->addObject(pipeNode);
	}
	
}

float GameLayer::getRandomHeight()
{
	float landHeight = _land->getOneLandSize().height;
	float rangeMin = landHeight + PIPE_SPACING_VERTICAL / 2 + PIPE_SHOW_MIN;
	float rangeMax = visibleSize.height - PIPE_SPACING_VERTICAL / 2 - PIPE_SHOW_MIN;
	return rand() % (int)(rangeMax - rangeMin) + rangeMin;
}

void GameLayer::rotateBird() {
	float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
	//log("vY=%f,max=%f,min=%f", verticalSpeed, max(-90, (verticalSpeed*0.2 + 60)), min(max(-90, (verticalSpeed*0.2 + 60)), 30));
	this->bird->setRotation(-1 * min(max(-90, (verticalSpeed*0.2 + 60)), 30));
}