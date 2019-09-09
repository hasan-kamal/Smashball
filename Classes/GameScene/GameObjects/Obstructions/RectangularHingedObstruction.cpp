//
//  RectangularHingedObstruction.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#include "RectangularHingedObstruction.hpp"

RectangularHingedObstruction::RectangularHingedObstruction(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, RectangularHingedObstructionInitialParameters *initialParameters){
    
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
    this->maxMotorTorque = initialParameters->maxMotorTorque;
    this->motorSpeed = initialParameters->motorSpeed;
    
    //hinge physics initialization
    b2CircleShape hingeShape;
    hingeShape.m_radius = this->radiusHinge;
    
    b2FixtureDef hingeFixture;
    hingeFixture.shape = &hingeShape;
    
    b2BodyDef hingeBodyDef;
    hingeBodyDef.type = b2_kinematicBody;
    //hingeBodyDef.userData = this;
    //we can avoid unnecessary update calls by not setting hinge's userData
    //because board's update method also updates hinge anyways
    //because world's update method would update a body's position only if its userdata is not null
    hingeBodyDef.position.Set(this->initialPosition.x, this->initialPosition.y);
    
    bodyHinge = world->CreateBody(&hingeBodyDef);
    bodyHinge->CreateFixture(&hingeFixture);
    bodyHinge->SetLinearVelocity(b2Vec2(0, 0));
    
    //board physics initialization
    b2PolygonShape boardShape;
    boardShape.SetAsBox(this->widthHalf, this->heightHalf);
    
    b2FixtureDef boardFixtureDef;
    boardFixtureDef.shape = &boardShape;
    boardFixtureDef.density = this->boardDensity;
    boardFixtureDef.restitution = this->boardRestitution;
    
    b2BodyDef boardBodyDef;
    boardBodyDef.type = b2_dynamicBody;
    boardBodyDef.userData = this;
    boardBodyDef.position.Set(this->initialPosition.x, this->initialPosition.y);
    
    this->rectangularBody = world->CreateBody(&boardBodyDef);
    this->rectangularBody->CreateFixture(&boardFixtureDef);
    
    //revolute joint
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = this->bodyHinge;
    jointDef.bodyB = this->rectangularBody;
    jointDef.collideConnected = false;
    jointDef.localAnchorA.Set(this->bodyHinge->GetLocalCenter().x, this->bodyHinge->GetLocalCenter().y);
    jointDef.localAnchorB.Set(this->rectangularBody->GetLocalCenter().x, this->rectangularBody->GetLocalCenter().y);
    jointDef.enableMotor = true;
    jointDef.maxMotorTorque = this->maxMotorTorque;
    jointDef.motorSpeed = this->motorSpeed;
    revoluteJoint = (b2RevoluteJoint *)world->CreateJoint(&jointDef);
    
    //hinge sprite initialization
    this->spriteHinge = Sprite::create("nut.png");
    this->spriteHinge->setScale(2*this->radiusHinge/1.33*worldToPixelScale/this->spriteHinge->getContentSize().width);
    parentCocosLayer->addChild(this->spriteHinge, 2);
    
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

RectangularHingedObstruction::~RectangularHingedObstruction(){
    
}

void RectangularHingedObstruction::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->rectangularBody->SetLinearVelocity(b2Vec2(0, 0));
    
    //update board
    this->rectangularSprite->setPosition(Point(this->rectangularBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->rectangularBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->rectangularSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->rectangularBody->GetAngle()));
    
    //update hinge
    this->spriteHinge->setPosition(Point(this->bodyHinge->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->bodyHinge->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->spriteHinge->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->bodyHinge->GetAngle()));

    //shadow
    this->shadowSprite->setPosition(Point(this->rectangularBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    
    //shadow
    this->shadowSprite->setScale(2*(fabs(this->heightHalf*sin(this->rectangularBody->GetAngle()))+0.20)*worldToPixelScale/this->shadowSprite->getContentSize().width, this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height);
    this->shadowSprite->setOpacity(clip(fabs(this->heightHalf*cos(this->rectangularBody->GetAngle()))*255));
    
    //SHM motion
    timeElapsed+=dt;
    if(timeElapsed<0)
        timeElapsed = 0;
    this->bodyHinge->SetLinearVelocity(b2Vec2(amplitudeOscillationX*frequencyOscillationX*cos(frequencyOscillationX*timeElapsed), amplitudeOscillationY*frequencyOscillationY*cos(frequencyOscillationY*timeElapsed)));
}

double RectangularHingedObstruction::clip(double x){
    //clips input double between min and max
    double min = 70.0;
    double max = 100.0;
    
    if(x>max)
        x = max;
    else if(x<min)
        x = min;
    
    return x;
}
