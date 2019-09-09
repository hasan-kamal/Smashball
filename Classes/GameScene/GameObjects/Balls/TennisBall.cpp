//
//  TennisBall.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 05/07/16.
//
//

#include "TennisBall.hpp"
#include <iostream>
using namespace std;

TennisBall::TennisBall(b2World *world, Layer *parentCocosLayer, float worldToPixelScale){
    //shadow initialization
    this->shadowSprite = Sprite::create("shadow.png");
    this->shadowSprite->setAnchorPoint(Vec2(0.5, 1.0));
    
    this->shadowScaleOriginal.x = 2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width;
    this->shadowScaleOriginal.y = this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height;
    
    this->shadowSprite->setScale(2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width, this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height);
    this->shadowSprite->setOpacity(100);
    parentCocosLayer->addChild(this->shadowSprite);
    
    //sprite initialization
    this->sprite = Sprite::create("ball_flat_spritesheet_2.png");
    this->sprite->setScale(2*this->radius*worldToPixelScale/this->sprite->getContentSize().width);
    initialScale = 2*this->radius*worldToPixelScale/this->sprite->getContentSize().width;
    parentCocosLayer->addChild(this->sprite, 1);
    
    //physics initialization
    b2CircleShape ballShape;
    ballShape.m_radius = this->radius;
    
    b2FixtureDef ballFixture;
    ballFixture.density = this->density;
    ballFixture.friction = this->friction;
    ballFixture.restitution = this->restitution;
    ballFixture.shape = &ballShape;
    
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.bullet = true;
    ballBodyDef.userData = this;
    ballBodyDef.position.Set(this->initialPosition.x, this->initialPosition.y);
    
    this->ballBody = world->CreateBody(&ballBodyDef);
    this->ballFixture = this->ballBody->CreateFixture(&ballFixture);

    this->sprite->setPosition(Point(this->ballBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x, this->ballBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y));    
}

//implement interface
void TennisBall::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->sprite->setPosition(Point(this->ballBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->ballBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->ballBody->GetAngle()));
    
    this->shadowSprite->setPosition(Point(this->ballBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    
    shadowScaleNew.x = 1.0 + (this->ballBody->GetPosition().y-0.25)/10.0;
    shadowScaleNew.y = 1.0 + (this->ballBody->GetPosition().y-0.25)/5.0;
    
    this->shadowSprite->setScaleX(this->shadowScaleOriginal.x*shadowScaleNew.x);
    this->shadowSprite->setScaleY(this->shadowScaleOriginal.y*shadowScaleNew.y);
    
    this->shadowSprite->setOpacity(100/(1.5*shadowScaleNew.y));
    
    //teleport check
    if(isInTeleportState){
        timeElapsedSinceTeleportStarted+=dt;
        
        if(timeElapsedSinceTeleportStarted>delayToWaitFor){
            isInTeleportState = false;
            bringTeleportedBallInView();
        }
    }
}

void TennisBall::gotHitApplyImpulse(b2Vec2 impulse){
    if(!isInTeleportState)
        this->ballBody->ApplyLinearImpulse(impulse, this->ballBody->GetWorldCenter(), true);
}

void TennisBall::deflateBall(){
    sprite->setOpacity(0);
}

void TennisBall::inflateBall(b2World *world){
    sprite->setOpacity(255);
    
    //physics initialization
    b2CircleShape ballShape;
    ballShape.m_radius = this->radius;
    
    b2FixtureDef ballFixture;
    ballFixture.density = this->density;
    ballFixture.friction = this->friction;
    ballFixture.restitution = this->restitution;
    ballFixture.shape = &ballShape;
    
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.bullet = true;
    ballBodyDef.userData = this;
    ballBodyDef.position.Set(this->initialPosition.x, this->initialPosition.y);
    
    this->health = GlobalConfigs::INITIAL_BALL_HEALTH;
    
    this->ballBody = world->CreateBody(&ballBodyDef);
    this->ballBody->CreateFixture(&ballFixture);
}

TennisBall::~TennisBall(){
    
}

void TennisBall::teleportToWithDelay(b2Vec2 ballTeleportDestinationVector, double delayForBallToReappear, b2Vec2 ballVelocityPreSolve){
    
    //set flags appropriately
    delayToWaitFor = delayForBallToReappear;
    isInTeleportState = true;
    timeElapsedSinceTeleportStarted = 0.0;
    ballTeleportDestination = ballTeleportDestinationVector;
    
    velocityAtTimeOfTeleport = ballVelocityPreSolve;
    this->ballBody->SetLinearVelocity(b2Vec2(0, 0));
    this->sprite->setVisible(false);
    
    this->ballBody->SetTransform(temporaryTeleportedPosition, 0);
    
}

void TennisBall::bringTeleportedBallInView(){
    this->ballBody->SetTransform(ballTeleportDestination, 0);
    this->ballBody->SetLinearVelocity(velocityAtTimeOfTeleport);
    this->sprite->setVisible(true);
}
