//
//  AbstractBall.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 15/07/16.
//
//

#ifndef AbstractBall_hpp
#define AbstractBall_hpp

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "../AbstractGameObject.hpp"
#include "../../../GlobalConfigs.hpp"

using namespace cocos2d;

class AbstractBall : public AbstractGameObject{
public:
    //we need to define body here because in case we have multiple balls, then
    //GameScene has to decide which ball to apply impulse on
    //and for that GameScene will need to have access to all the bodies of balls
    b2Body *ballBody;
    Sprite *sprite;
    b2Fixture *ballFixture;
    int health = GlobalConfigs::INITIAL_BALL_HEALTH;
    
    void reduce_health(int amount);
    
    virtual void gotHitApplyImpulse(b2Vec2 impulse) = 0;
    virtual void deflateBall() = 0;
    virtual void inflateBall(b2World *world) = 0;
    virtual void teleportToWithDelay(b2Vec2 ballTeleportDestination, double delayForBallToReappear, b2Vec2 ballVelocityPreSolve) = 0;
};

#endif /* AbstractBall_hpp */
