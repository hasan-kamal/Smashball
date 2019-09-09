//
//  Vortex.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 29/09/16.
//
//

#include "Vortex.hpp"
#include <iostream>
using namespace std;

Vortex::Vortex(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded){
    
    this->radius = 0.5;
    this->safeRadius = 0.1;
    vortexPosition.Set(1.0, 1.5);
    
    //sprite initialization
    this->sprite = Sprite::create("wormhole.png");
    this->sprite->setScale(2*this->radius*worldToPixelScale/this->sprite->getContentSize().width);
    parentCocosLayer->addChild(this->sprite, 1);
    
    //physics initialization, although it is only a sensor body, putting only for the sake of it
    this->sensorBodyRadius = 0.01;
    b2CircleShape sensorBodyShape;
    sensorBodyShape.m_radius = this->sensorBodyRadius;
    
    b2FixtureDef sensorBodyFixture;
    sensorBodyFixture.density = this->density;
    sensorBodyFixture.friction = this->friction;
    sensorBodyFixture.restitution = this->restitution;
    sensorBodyFixture.shape = &sensorBodyShape;
    sensorBodyFixture.isSensor = true;
    
    b2BodyDef sensorBodyDef;
    sensorBodyDef.type = b2_kinematicBody;
    sensorBodyDef.userData = this;
    sensorBodyDef.position.Set(this->vortexPosition.x, this->vortexPosition.y);
    
    this->sensorBody = world->CreateBody(&sensorBodyDef);
    this->sensorBody->CreateFixture(&sensorBodyFixture);
}

Vortex::~Vortex(){
    
}


void Vortex::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->sprite->setPosition(Point(this->sensorBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->sensorBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->sensorBody->GetAngle()));
    
}

void Vortex::vortexApplyForcesOnBalls(AbstractBall *balls[], int numBalls){
    b2Vec2 distanceToBall, force;
    double scalingFactor = 0.1;
    
    for(int i=0; i<numBalls; i++){
        distanceToBall = balls[i]->ballBody->GetPosition() - this->sensorBody->GetPosition();
        
        if(distanceToBall.Length()<this->safeRadius){
            distanceToBall.operator*=(this->safeRadius/distanceToBall.Length());
        }
        
        if(distanceToBall.Length()<this->radius){
            //within coverage area, so apply force
            force.Set(-1*distanceToBall.x, -1*distanceToBall.y);
            force.operator*=(scalingFactor/distanceToBall.LengthSquared()/force.Length());
            balls[i]->ballBody->ApplyLinearImpulse(force, balls[i]->ballBody->GetWorldCenter(), true);
        }
    }
}
