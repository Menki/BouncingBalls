//
//  HelloWorldScene.cpp
//  BouncingBalls
//
//  Created by Augusto Souza on 8/21/11.
//  Copyright Menki Mobile 2011. All rights reserved.
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

HelloWorld::~HelloWorld()
{
	if (world)
	{
		delete world;
		world = NULL;
	}

    if (body)
	{
		body = NULL;
	}
    
	// cpp don't need to call super dealloc
	// virtual destructor will do this
}

HelloWorld::HelloWorld()
:world(NULL)
,body(NULL)
,ball(NULL)
,ptmRatio(0)
{
}

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    this->setIsAccelerometerEnabled(true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    ptmRatio = winSize.width / 10;
    
    // create a sprite and add it to the layer
    ball = CCSprite::spriteWithFile("Ball.jpg");
    CCSize ballSize = ball->getTextureRect().size;
    ball->setPosition(ccp(ballSize.width*0.5f, winSize.height - ballSize.height*0.5f));    
    this->addChild(ball);

    // create a world
    b2Vec2 gravity = b2Vec2(0.0f, -30.0f);
    bool doSleep = false;
    world = new b2World(gravity, doSleep);
    
    // create edges around the entire screen
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    b2Body *groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    b2FixtureDef boxShapeDef;
    boxShapeDef.shape = &groundBox;
    // bottom
    groundBox.SetAsEdge(b2Vec2(0, 0), b2Vec2(winSize.width/ptmRatio, 0));
    groundBody->CreateFixture(&boxShapeDef);
    // left
    groundBox.SetAsEdge(b2Vec2(0, 0), b2Vec2(0, winSize.height/ptmRatio));
    groundBody->CreateFixture(&boxShapeDef);
    // top
    groundBox.SetAsEdge(b2Vec2(0, winSize.height/ptmRatio), b2Vec2(winSize.width/ptmRatio, winSize.height/ptmRatio));
    groundBody->CreateFixture(&boxShapeDef);    
    // right
    groundBox.SetAsEdge(b2Vec2(winSize.width/ptmRatio, winSize.height/ptmRatio), b2Vec2(winSize.width/ptmRatio, 0));
    groundBody->CreateFixture(&boxShapeDef);
    
    // create ball body and shape
    // Density is mass per unit volume. So the more dense an object is, the more mass it has, and the harder it is to move.
    // Friction is a measure of how hard it is for objects to slide against each other. This should be in the range of 0 to 1. 0 means there is no friction, and 1 means there is a lot of friction.
    // Restitution is a measure of how “bouncy” an object is. This should usually be in the range of 0 to 1. 0 means the object will not bounce, and 1 means the bounce is perfectly elastic, meaning it will bounce away with the same velocity that it impacted an object.    
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    CCPoint ballPos = ball->getPosition();
    ballBodyDef.position.Set(ballPos.x/ptmRatio, ballPos.y/ptmRatio);
    ballBodyDef.userData = ball;
    body = world->CreateBody(&ballBodyDef);
    
    b2CircleShape circle;
    circle.m_radius = ballSize.width*0.5f / ptmRatio;
    
    CCLog("raio = %.2f", circle.m_radius);
    
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.2f;
    ballShapeDef.restitution = 0.8f;
    body->CreateFixture(&ballShapeDef);
    
    this->schedule(schedule_selector(HelloWorld::tick));
    
	return true;
}

void HelloWorld::tick(cocos2d::ccTime delta) 
{
    // velocity iterations and position iterations should usually be setted in the range of 8-10
    int velocityIterations = 10;
    int positionIterations = 10;
    world->Step(delta, velocityIterations, positionIterations);
    
    for (b2Body *b = world->GetBodyList(); b != NULL; b = b->GetNext()) 
    {
        if (b->GetUserData()) 
        {
            CCSprite *ballData = (CCSprite *)b->GetUserData();
            ballData->setPosition(ccp(b->GetPosition().x * ptmRatio, b->GetPosition().y * ptmRatio));
            ballData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}

void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
    b2Vec2 gravity(-pAccelerationValue->y * 15, pAccelerationValue->x * 15);
    world->SetGravity(gravity);
}
