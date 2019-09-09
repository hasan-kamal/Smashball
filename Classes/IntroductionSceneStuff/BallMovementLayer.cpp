//
//  BallMovementLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#include "BallMovementLayer.hpp"

#include <iostream>
using namespace std;

bool BallMovementLayer::init(){
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    scheduleUpdate();
    
    //box2d world
    b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
    world = new b2World(gravity);
    
    //create edge shape instead
    b2Vec2 v1(0.0f, 0.0f);
    b2Vec2 v2(widthWorld, 0.0f);
    b2EdgeShape edgeShape;
    edgeShape.Set(v1, v2);
    
    b2FixtureDef boundFixture;
    boundFixture.shape = &edgeShape;
    boundFixture.restitution = 0.5;

    b2BodyDef boundBodyDef;
    boundBodyDef.type = b2_staticBody;
    boundBodyDef.userData = nullptr;
    boundBodyDef.position.Set(0.0, 0.0);

    edgeBody = world->CreateBody(&boundBodyDef);
    edgeBody->CreateFixture(&boundFixture);
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    worldToPixelScale = visibleSize.width/widthWorld;
    ball = new TennisBall(world, this, worldToPixelScale);
    ball->ballBody->SetTransform(b2Vec2(2.5, 4.0), 0.0);
    
    TennisBall *b = (TennisBall *)ball;
    offsetOriginToBeAdded.set(0, (visibleSize.height - worldToPixelScale*heightWorld)/2.0);
    
    return true;
}

void BallMovementLayer::onExit(){
    Layer::onExit();
    
    delete ball;
    
    delete world;
}

void BallMovementLayer::update(float dt){
    int positionIterations = 10;  // Location
    int velocityIterations = 10; // Velocity
    
    
    
    // Simulate the physical movement by time, study here http://www.box2d.org/manual.html and here  http://www.iforce2d.net/b2dtut/worlds
    
    // Each Step happens in dt seconds , this dt in file AppDelegate.cpp is defined by command director->setAnimationInterval(1.0 / 60); you try replacing 1/60 = 1/1 , it falls very slow
    
    timeElapsed+=dt;
    if(timeElapsed>initialDelayTimeForBall){
        world->Step(dt, velocityIterations, positionIterations);
    }
    
    // Navigate all bodies of world
    for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
        // Consider which body is attached to Sprite
        if (body->GetUserData())
        {
            // return the ball sprite
            AbstractGameObject *gameObject = (AbstractGameObject *) body->GetUserData();
            // Set the position again for this Sprite follow the position of body ( body is gradually falling by time), remember to multiply with RATIO to convert into pixel
            gameObject->updateState(dt, worldToPixelScale, this->offsetOriginToBeAdded);
        }
    world->ClearForces(); // Clear forces of Body
    //world->DrawDebugData();  // Draw shapes to check collision in debug mode
}
