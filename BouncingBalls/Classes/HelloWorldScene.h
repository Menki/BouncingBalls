//
//  HelloWorldScene.h
//  BouncingBalls
//
//  Created by Augusto Souza on 8/21/11.
//  Copyright Menki Mobile 2011. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"

class HelloWorld : public cocos2d::CCLayer {
public:
    HelloWorld();
	~HelloWorld();
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);

private:
    virtual void didAccelerate(cocos2d::CCAcceleration *pAccelerationValue);
    void tick(cocos2d::ccTime delta);
    
    b2World *world;
    b2Body *body;
    cocos2d::CCSprite *ball;
    int ptmRatio;
};

#endif // __HELLO_WORLD_H__
