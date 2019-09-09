//
//  Wormhole.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 26/09/16.
//
//

#include "Wormhole.hpp"

#include <iostream>
using namespace std;

Wormhole::Wormhole(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded){
    
    //positions of the wormhole pair
    pos1.Set(3.5, 1.0);
    pos2.Set(1.0, 0.5);
    
    //radius initialization
    innerRadius = 0.05;
    outerRadius = innerRadius + 0.12; //innerRadius + ballRadius
    
    //sprite initialization
    this->sprite1 = Sprite::create("wormhole_new.png");
    this->sprite1->setScale(2*this->outerRadius*worldToPixelScale/this->sprite1->getContentSize().width);
    initialScale = this->sprite1->getScale();
    parentCocosLayer->addChild(this->sprite1, 1);
    
    this->sprite2 = Sprite::create("wormhole_new.png");
    this->sprite2->setScale(2*this->outerRadius*worldToPixelScale/this->sprite2->getContentSize().width);
    parentCocosLayer->addChild(this->sprite2, 1);
    
    //physics initialization for body1
    b2CircleShape body1Shape;
    body1Shape.m_radius = this->innerRadius;
    
    b2FixtureDef body1Fixture;
    body1Fixture.density = this->density;
    body1Fixture.friction = this->friction;
    body1Fixture.restitution = this->restitution;
    body1Fixture.shape = &body1Shape;
    body1Fixture.isSensor = true;
    
    b2BodyDef body1Def;
    body1Def.type = b2_kinematicBody;
    body1Def.bullet = true;
    body1Def.userData = this;
    body1Def.position.Set(pos1.x, pos1.y);
    
    this->body1 = world->CreateBody(&body1Def);
    this->body1->CreateFixture(&body1Fixture);
    this->body1->SetLinearVelocity(b2Vec2(0, 0));

    
    //physics initialization for body2
    b2CircleShape body2Shape;
    body2Shape.m_radius = this->innerRadius;
    
    b2FixtureDef body2Fixture;
    body2Fixture.density = this->density;
    body2Fixture.friction = this->friction;
    body2Fixture.restitution = this->restitution;
    body2Fixture.shape = &body2Shape;
    body2Fixture.isSensor = true;
    
    b2BodyDef body2Def;
    body2Def.type = b2_kinematicBody;
    body2Def.bullet = true;
    body2Def.userData = this;
    body2Def.position.Set(pos2.x, pos2.y);
    
    this->body2 = world->CreateBody(&body2Def);
    this->body2->CreateFixture(&body2Fixture);
    this->body2->SetLinearVelocity(b2Vec2(0, 0));

}

Wormhole::~Wormhole(){
    
}

b2Vec2 Wormhole::getTeleportDestination(AbstractBall *ballTouched, b2Contact *contact){
    b2Vec2 difference;
    
    if(contact->GetFixtureA()->GetBody()==body1 || contact->GetFixtureB()->GetBody()==body1){
        //collided with pos1=body1 circle
        difference.Set((pos1 - ballTouched->ballBody->GetPosition()).x, (pos1 - ballTouched->ballBody->GetPosition()).y);
        //difference.Set(0-difference.x, 0-difference.y);
        //difference.operator*=(outerRadius/difference.Length());
        return pos2+difference;
    }else{
        //collided with pos2=body2 circle
        difference.Set((pos2 - ballTouched->ballBody->GetPosition()).x, (pos2 - ballTouched->ballBody->GetPosition()).y);
        //difference.Set(0-difference.x, 0-difference.y);
        //if(difference.Length()<innerRadius)
        //    difference.operator*=(outerRadius/difference.Length());
        return pos1+difference;
    }
}

void Wormhole::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    this->sprite1->setPosition(Point(this->body1->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->body1->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    //this->sprite1->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->body1->GetAngle()));
    
    this->sprite2->setPosition(Point(this->body2->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->body2->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    //this->sprite2->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->body2->GetAngle()));
}

void Wormhole::fadeInNow(){
    auto tintBy = TintBy::create(0.5f/2, 100.0f, 0.0, 0.0);
    sprite1->runAction(tintBy->reverse());
    sprite2->runAction(tintBy->reverse()->clone());
}

void Wormhole::fadeOutNow(){
    auto tintBy = TintBy::create(0.5f/2, 100.0f, 0.0, 0.0);
    sprite1->runAction(tintBy);
    sprite2->runAction(tintBy->clone());
}

void Wormhole::followBall(AbstractBall *ball){
    //double checkRadius = 1.0;
    double PI = 3.14159;
    
    b2Vec2 v;
    v.Set(ball->ballBody->GetPosition().x-3.5, ball->ballBody->GetPosition().y-1.0);
    
    Vec2 u;
    u.set(v.x, v.y);
    
    //if(v.Length()<checkRadius)
        this->sprite1->setRotation(-1 * CC_RADIANS_TO_DEGREES(u.getAngle()-PI/2));
    
    b2Vec2 v2;
    v2.Set(ball->ballBody->GetPosition().x-1.0, ball->ballBody->GetPosition().y-0.5);
    
    Vec2 u2;
    u2.set(v2.x, v2.y);
    
    //if(v.Length()<checkRadius)
    this->sprite2->setRotation(-1 * CC_RADIANS_TO_DEGREES(u2.getAngle()-PI/2));
    
    
}
