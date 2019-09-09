//
//  MetalRod.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 15/07/16.
//
//

#include "MetalRod.hpp"
#include <iostream>
using namespace std;

MetalRod::MetalRod(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, b2Vec2 jointPosInWorld, float heightCeilingInWorld, Vec2 offsetOriginToBeAdded, bool orientationLeft, float extraHeightForOscillationAdjustment){
    
    //rod-horizontal sprite initialization
    this->spriteHorizontal = Sprite::create("metal_rod_horizontal.png");
    this->spriteHorizontal->setScale(this->horizontalLength*worldToPixelScale/this->spriteHorizontal->getContentSize().width, this->thickness*worldToPixelScale/this->spriteHorizontal->getContentSize().height);
    parentCocosLayer->addChild(this->spriteHorizontal);
    
    //rod-horizontal box initilization
    b2PolygonShape rodHorizontalShape;
    rodHorizontalShape.SetAsBox(this->horizontalLength/2, this->thickness/2);
    
    b2FixtureDef rodHorizontalFixtureDef;
    rodHorizontalFixtureDef.shape = &rodHorizontalShape;
    rodHorizontalFixtureDef.restitution = this->restitution;
    rodHorizontalFixtureDef.friction = this->friction;
    
    b2BodyDef rodHorizontalBodyDef;
    rodHorizontalBodyDef.type = b2_kinematicBody;
    rodHorizontalBodyDef.userData = this;
    if(orientationLeft)
        rodHorizontalBodyDef.position.Set(jointPosInWorld.x + this->horizontalLength/2, jointPosInWorld.y);
    else
        rodHorizontalBodyDef.position.Set(jointPosInWorld.x - this->horizontalLength/2, jointPosInWorld.y);
    
    bodyHorizontal = world->CreateBody(&rodHorizontalBodyDef);
    bodyHorizontal->CreateFixture(&rodHorizontalFixtureDef);
    bodyHorizontal->SetLinearVelocity(b2Vec2(0, 0));
    
    float heightRodInWorld =  (heightCeilingInWorld-jointPosInWorld.y) + (offsetOriginToBeAdded.y*1.0/worldToPixelScale) + extraHeightForOscillationAdjustment;
    
    //rod-vertical box initilization
    b2PolygonShape rodVerticalShape;
    rodVerticalShape.SetAsBox(this->thickness/2.0, heightRodInWorld/2.0);
    
    b2FixtureDef rodVerticalFixtureDef;
    rodVerticalFixtureDef.shape = &rodVerticalShape;
    rodVerticalFixtureDef.restitution = this->restitution;
    rodVerticalFixtureDef.friction = this->friction;
    
    b2BodyDef rodVerticalBodyDef;
    rodVerticalBodyDef.type = b2_kinematicBody;
    //not setting vertical's user data to prevent unnecessary update calls
    //rodVerticalBodyDef.userData = this;
    if(orientationLeft)
        rodVerticalBodyDef.position.Set(jointPosInWorld.x + this->horizontalLength - this->thickness/2, jointPosInWorld.y + heightRodInWorld/2.0);
    else
        rodVerticalBodyDef.position.Set(jointPosInWorld.x - this->horizontalLength + this->thickness/2, jointPosInWorld.y + heightRodInWorld/2.0);
    
    bodyVertical = world->CreateBody(&rodVerticalBodyDef);
    bodyVertical->CreateFixture(&rodVerticalFixtureDef);
    bodyVertical->SetLinearVelocity(b2Vec2(0, 0));
    
    //rod-vertical sprite initialization
    this->spriteVertical = Sprite::create("metal_rod_vertical.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->spriteVertical->setScale(this->thickness*worldToPixelScale/this->spriteVertical->getContentSize().width, (heightRodInWorld)*worldToPixelScale/this->spriteVertical->getContentSize().height);
    this->spriteVertical->setAnchorPoint(Vec2(0.5, 0.5));
    parentCocosLayer->addChild(this->spriteVertical);

}

void MetalRod::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    //update rod, though unnecessary if static
    this->spriteHorizontal->setPosition(Point(this->bodyHorizontal->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->bodyHorizontal->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->spriteHorizontal->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->bodyHorizontal->GetAngle()));
    
    
    this->spriteVertical->setPosition(Point(this->bodyVertical->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->bodyVertical->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->spriteVertical->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->bodyVertical->GetAngle()));
    
}

MetalRod::~MetalRod(){
}
