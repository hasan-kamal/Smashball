//
//  RectangularObstruction.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#include "RectangularObstruction.hpp"

RectangularObstruction::RectangularObstruction(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, RectangularObstructionInitialParameters *initialParameters){
    
    //save and copy configuration info from initalParameters object first
    this->heightHalf = initialParameters->heightHalf;
    this->widthHalf = initialParameters->widthHalf;
    this->initialPosition = initialParameters->initialPosition;
    this->angleInclinationInitial = initialParameters->angleInclinationInitial;
    this->boardDensity = initialParameters->boardDensity;
    this->boardRestitution = initialParameters->boardRestitution;
    this->amplitudeOscillationX = initialParameters->amplitudeOscillationX;
    this->frequencyOscillationX = initialParameters->frequencyOscillationX;
    this->amplitudeOscillationY = initialParameters->amplitudeOscillationY;
    this->frequencyOscillationY = initialParameters->frequencyOscillationY;
    
    //board physics initialization
    b2PolygonShape boardShape;
    boardShape.SetAsBox(this->widthHalf, this->heightHalf);
    
    b2FixtureDef boardFixtureDef;
    boardFixtureDef.shape = &boardShape;
    boardFixtureDef.density = this->boardDensity;
    boardFixtureDef.restitution = this->boardRestitution;
    
    b2BodyDef boardBodyDef;
    boardBodyDef.type = b2_kinematicBody;
    boardBodyDef.userData = this;
    boardBodyDef.position.Set(initialPosition.x, initialPosition.y);
    
    rectangularBody = world->CreateBody(&boardBodyDef);
    rectangularBody->CreateFixture(&boardFixtureDef);
    rectangularBody->SetTransform(rectangularBody->GetPosition(), this->angleInclinationInitial);
    rectangularBody->SetLinearVelocity(b2Vec2(0, 0));
    
    //sprite initialization
    this->rectangularSprite = Sprite::create("wormhole_main.png");
    this->rectangularSprite->setScale(2*this->widthHalf*worldToPixelScale/this->rectangularSprite->getContentSize().width, 2*this->heightHalf*worldToPixelScale/this->rectangularSprite->getContentSize().height);
    this->rectangularSprite->setAnchorPoint(Vec2(0.5, 0.5));
    
    parentCocosLayer->addChild(this->rectangularSprite, 1);
    
    //shadow initialization
    this->shadowSprite = Sprite::create("shadow.png");
    this->shadowSprite->setAnchorPoint(Vec2(0.5, 1.0));
    this->shadowRadius = ( max(1.0*heightHalf*std::abs(sin(angleInclinationInitial)), widthHalf + 0.05) )*1.40;
    
    this->shadowSprite->setScale(2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width, this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height);
    this->shadowSprite->setOpacity(100);
    
    this->shadowScaleOriginal.x = 2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width;
    this->shadowScaleOriginal.y = this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height;
    
    parentCocosLayer->addChild(this->shadowSprite);
}

RectangularObstruction::~RectangularObstruction(){
    
}

void RectangularObstruction::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->rectangularSprite->setPosition(Point(this->rectangularBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->rectangularBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->rectangularSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->rectangularBody->GetAngle()));
    
    this->shadowSprite->setPosition(Point(this->rectangularBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    
    shadowScaleNew.x = 1.0 + (this->rectangularBody->GetPosition().y-0.25)/10.0;
    shadowScaleNew.y = 1.0 + (this->rectangularBody->GetPosition().y-0.25)/5.0;
    
    this->shadowSprite->setScaleX(this->shadowScaleOriginal.x*shadowScaleNew.x);
    this->shadowSprite->setScaleY(this->shadowScaleOriginal.y*shadowScaleNew.y);
    
    this->shadowSprite->setOpacity(100/(1.5*shadowScaleNew.y));
    
    timeElapsed+=dt;
    if(timeElapsed<0)
        timeElapsed = 0;
    this->rectangularBody->SetLinearVelocity(b2Vec2(amplitudeOscillationX*frequencyOscillationX*cos(frequencyOscillationX*timeElapsed), amplitudeOscillationY*frequencyOscillationY*cos(frequencyOscillationY*timeElapsed)));
}
