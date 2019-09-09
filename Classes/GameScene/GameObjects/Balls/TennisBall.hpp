//
//  TennisBall.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 05/07/16.
//
//

#ifndef TennisBall_hpp
#define TennisBall_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AbstractBall.hpp"

using namespace cocos2d;

class TennisBall : public AbstractBall{
public:
    //fixture properties and their values
    float radius = 0.12;
    float density = 150.0;
    float friction = 0.5;
    float restitution = 0.7;
    
    //body initial properties
    Vec2 initialPosition = Vec2(2.5, 0.5);
    //Vec2 initialPosition = Vec2(3.8, 2.5);
    
    TennisBall(b2World *world, Layer *parentCocosLayer, float worldToPixelScale);
    ~TennisBall();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    void gotHitApplyImpulse(b2Vec2 impulse) override;
    void deflateBall() override;
    void inflateBall(b2World *world) override;
    
    //shadow properties
    Sprite *shadowSprite;
    float shadowRadius = 0.15;
    float shadowLength = 0.05;
    Vec2 shadowScaleOriginal;
    Vec2 shadowScaleNew;
    
    //this will be called by a wormhole
    //this would hide the ball away, wait for delayForBallToReappear seconds, then replace
    //the ball at ballTeleportDestination
    void teleportToWithDelay(b2Vec2 ballTeleportDestinationVector, double delayForBallToReappear, b2Vec2 ballVelocityPreSolve) override;
    bool isInTeleportState = false;
    double timeElapsedSinceTeleportStarted;
    double delayToWaitFor;
    b2Vec2 ballTeleportDestination;
    b2Vec2 velocityAtTimeOfTeleport;
    b2Vec2 temporaryTeleportedPosition = b2Vec2(10.0, 10.0);
    void bringTeleportedBallInView();
    double initialScale;
};

#endif /* TennisBall_hpp */
