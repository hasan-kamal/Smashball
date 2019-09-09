//
//  TriangularObstruction.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#include "TriangularObstruction.hpp"

#include <iostream>
using namespace std;

TriangularObstruction::TriangularObstruction(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, TriangularObstructionInitialParameters *initialParameters){
    
    //save and copy configuration info from initalParameters object first
    this->baseWidth = initialParameters->baseWidth;
    this->height = initialParameters->height;
    this->initialPosition = initialParameters->initialPosition;
    this->angleInclinationInitial = initialParameters->angleInclinationInitial;
    this->density = initialParameters->density;
    this->restitution = initialParameters->restitution;
    this->amplitudeOscillationX = initialParameters->amplitudeOscillationX;
    this->frequencyOscillationX = initialParameters->frequencyOscillationX;
    this->amplitudeOscillationY = initialParameters->amplitudeOscillationY;
    this->frequencyOscillationY = initialParameters->frequencyOscillationY;

    //triangular body initialization
    b2Vec2 vertices[3];
    vertices[0].Set(0.0 - baseWidth/2, 0.0 - height/2);
    vertices[1].Set(0.0 + baseWidth/2, 0.0 - height/2);
    vertices[2].Set(0.0, 0.0 + height/2);
    b2PolygonShape triangularShape;
    triangularShape.Set(vertices, 3);
    
    b2FixtureDef triangleFixtureDef;
    triangleFixtureDef.shape = &triangularShape;
    triangleFixtureDef.density = this->density;
    triangleFixtureDef.restitution = this->restitution;
    
    b2BodyDef triangleBodyDef;
    triangleBodyDef.type = b2_kinematicBody;
    triangleBodyDef.userData = this;
    triangleBodyDef.position.Set(initialPosition.x, initialPosition.y);
    
    triangularBody = world->CreateBody(&triangleBodyDef);
    triangularBody->CreateFixture(&triangleFixtureDef);
    triangularBody->SetTransform(triangularBody->GetPosition(), this->angleInclinationInitial);
    triangularBody->SetLinearVelocity(b2Vec2(0, 0));
    
    //sprite initialization
    this->triangularSprite = Sprite::create("triangle_obstruction.png");
    this->triangularSprite->setScale(this->baseWidth*worldToPixelScale/this->triangularSprite->getContentSize().width, this->height*worldToPixelScale/this->triangularSprite->getContentSize().height);
    this->triangularSprite->setAnchorPoint(Vec2(0.5, 0.5));
    
    parentCocosLayer->addChild(this->triangularSprite, 1);
    
    //shadow initialization
    this->shadowSprite = Sprite::create("shadow.png");
    this->shadowSprite->setAnchorPoint(Vec2(0.5, 1.0));
    this->shadowRadius = max(fabs(height/2*sin(triangularBody->GetAngle())), baseWidth) + 0.10;
    
    this->shadowSprite->setScale(2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width, this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height);
    this->shadowSprite->setOpacity(100);
    
    this->shadowScaleOriginal.x = 2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width;
    this->shadowScaleOriginal.y = this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height;
    
    parentCocosLayer->addChild(this->shadowSprite);
}

TriangularObstruction::~TriangularObstruction(){
    
}

void TriangularObstruction::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->triangularSprite->setPosition(Point(this->triangularBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->triangularBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->triangularSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->triangularBody->GetAngle()));
    
    this->shadowSprite->setPosition(Point(this->triangularBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    
    shadowScaleNew.x = 1.0 + (this->triangularBody->GetPosition().y-0.25)/10.0;
    shadowScaleNew.y = 1.0 + (this->triangularBody->GetPosition().y-0.25)/5.0;
    
    this->shadowSprite->setScaleX(this->shadowScaleOriginal.x*shadowScaleNew.x);
    this->shadowSprite->setScaleY(this->shadowScaleOriginal.y*shadowScaleNew.y);
    
    this->shadowSprite->setOpacity(100/(1.5*shadowScaleNew.y));
    
    timeElapsed+=dt;
    if(timeElapsed<0)
        timeElapsed = 0;
    this->triangularBody->SetLinearVelocity(b2Vec2(amplitudeOscillationX*frequencyOscillationX*cos(frequencyOscillationX*timeElapsed), amplitudeOscillationY*frequencyOscillationY*cos(frequencyOscillationY*timeElapsed)));
}
