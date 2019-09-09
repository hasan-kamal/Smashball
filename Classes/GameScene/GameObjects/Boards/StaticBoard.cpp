//
//  StaticBoard.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 15/07/16.
//
//

#include "StaticBoard.hpp"
#include <iostream>
using namespace std;

#include <math.h>

StaticBoard::StaticBoard(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, float heightInWorld, Vec2 offsetOriginToBeAdded, StaticBoardInitialParameters *initialParameters){
    
    //save and copy configuration info from initalParameters object first
    this->orientation = initialParameters->orientation;
    this->heightHalf = initialParameters->heightHalf;
    this->widthHalf = initialParameters->widthHalf;
    this->initialPosition = initialParameters->initialPosition;
    this->angleInclinationInitial = initialParameters->angleInclinationInitial;
    this->bonusRadius = initialParameters->bonusRadius;
    this->boardDensity = initialParameters->boardDensity;
    this->boardRestitution = initialParameters->boardRestitution;
    this->paddingGap = initialParameters->paddingGap;
    this->amplitudeOscillationX = initialParameters->amplitudeOscillationX;
    this->frequencyOscillationX = initialParameters->frequencyOscillationX;
    this->amplitudeOscillationY = initialParameters->amplitudeOscillationY;
    this->frequencyOscillationY = initialParameters->frequencyOscillationY;
    
    this->boardSpriteUpper = Sprite::create("board_modern_static_red_upper.png");
    this->boardSpriteUpper->setScale(2*this->widthHalf*worldToPixelScale/this->boardSpriteUpper->getContentSize().width, (this->heightHalf-this->bonusRadius-this->paddingGap)*worldToPixelScale/this->boardSpriteUpper->getContentSize().height);
    this->boardSpriteUpper->setAnchorPoint(Vec2(0.5, -1*(bonusRadius+paddingGap)/(heightHalf-bonusRadius-paddingGap)));
    if(orientation)
        this->boardSpriteUpper->setFlippedX(true);
    
    this->boardSpriteMiddle = Sprite::create("board_modern_static_red_middle.png");
    this->boardSpriteMiddle->setScale(2*this->widthHalf*worldToPixelScale/this->boardSpriteMiddle->getContentSize().width, 2*this->bonusRadius*worldToPixelScale/this->boardSpriteMiddle->getContentSize().height);
    this->boardSpriteMiddle->setAnchorPoint(Vec2(0.5, 0.5));
    if(orientation)
        this->boardSpriteMiddle->setFlippedX(true);
    
    this->boardSpriteLower = Sprite::create("board_modern_static_red_lower.png");
    this->boardSpriteLower->setScale(2*this->widthHalf*worldToPixelScale/this->boardSpriteLower->getContentSize().width, (this->heightHalf-this->bonusRadius-this->paddingGap)*worldToPixelScale/this->boardSpriteLower->getContentSize().height);
    this->boardSpriteLower->setAnchorPoint(Vec2(0.5, 1.0 + (bonusRadius+paddingGap)/(heightHalf-bonusRadius-paddingGap)));
    if(orientation)
        this->boardSpriteLower->setFlippedX(true);
    
    parentCocosLayer->addChild(this->boardSpriteMiddle, 1);
    parentCocosLayer->addChild(this->boardSpriteLower, 1);
    parentCocosLayer->addChild(this->boardSpriteUpper, 1);
    
    //board physics initialization
    b2PolygonShape boardShape;
    //boardShape.SetAsBox(this->widthHalf, this->heightHalf);
    boardShape.SetAsBox(initialParameters->widthHalf, initialParameters->heightHalf);
    
    b2FixtureDef boardFixtureDef;
    boardFixtureDef.shape = &boardShape;
    boardFixtureDef.density = this->boardDensity;
    boardFixtureDef.restitution = this->boardRestitution;
    
    b2BodyDef boardBodyDef;
    boardBodyDef.type = b2_kinematicBody;
    boardBodyDef.userData = this;
    boardBodyDef.position.Set(initialParameters->initialPosition.x, initialParameters->initialPosition.y);
    
    boardBody = world->CreateBody(&boardBodyDef);
    boardBody->CreateFixture(&boardFixtureDef);
    boardBody->SetTransform(boardBody->GetPosition(), this->angleInclinationInitial);
    boardBody->SetLinearVelocity(b2Vec2(0, 0));
    
    //score delta label
    this->scoreDeltaLabel = Label::createWithTTF("0", "fonts/Roboto-Light.ttf", 20);
    this->scoreDeltaLabel->setColor(Color3B(189, 195, 192));
    this->scoreDeltaLabel->setPosition(Vec2(offsetOriginToBeAdded.x + Director::getInstance()->getVisibleOrigin().x + this->boardBody->GetPosition().x*worldToPixelScale, offsetOriginToBeAdded.y + Director::getInstance()->getVisibleOrigin().y + (this->boardBody->GetPosition().y + initialParameters->heightHalf + 0.15)*worldToPixelScale));
    this->scoreDeltaLabel->setOpacity(0);
    parentCocosLayer->addChild(this->scoreDeltaLabel, 1);

    //rod initialization
    metalRod = new MetalRod(world, parentCocosLayer, worldToPixelScale, this->boardBody->GetPosition(),heightInWorld, offsetOriginToBeAdded, !orientation, 2*amplitudeOscillationY);
    
    //shadow initialization
    this->shadowSprite = Sprite::create("shadow.png");
    this->shadowSprite->setAnchorPoint(Vec2(0.5, 1.0));
    this->shadowRadius = (max(2*heightHalf*abs(sin(angleInclinationInitial)), 2*widthHalf+metalRod->horizontalLength))/2 + 0.20;
    
    this->shadowScaleOriginal.x = 2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width;
    this->shadowScaleOriginal.y = this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height;
    
    this->shadowSprite->setScale(2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width, this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height);
    this->shadowSprite->setOpacity(100);
    
    if(2*heightHalf*abs(sin(angleInclinationInitial))<2*widthHalf+metalRod->horizontalLength){
        //the rod's horizontal length adds to the shadow, so choose center accordingly
        if(!orientation)
            this->shadowSprite->setPosition(Point( (this->boardBody->GetPosition().x+(2*initialParameters->widthHalf+metalRod->horizontalLength)/2.0) * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
        else
            this->shadowSprite->setPosition(Point( (this->boardBody->GetPosition().x-(2*initialParameters->widthHalf+metalRod->horizontalLength)/2.0) * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    }else{
        //the rod is not contributing to shadow because angle of board is such
        //that it spans over the rod's width, so choose center accordingly
        this->shadowSprite->setPosition(Point( (this->boardBody->GetPosition().x) * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    }
    
    parentCocosLayer->addChild(this->shadowSprite);
    
}

StaticBoard::~StaticBoard(){
    delete metalRod;
}

//implement interface
void StaticBoard::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->boardSpriteMiddle->setPosition(Point(this->boardBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->boardBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->boardSpriteMiddle->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->boardBody->GetAngle()));
    
    this->boardSpriteUpper->setPosition(Point(this->boardBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->boardBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->boardSpriteUpper->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->boardBody->GetAngle()));
    
    this->boardSpriteLower->setPosition(Point(this->boardBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->boardBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->boardSpriteLower->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->boardBody->GetAngle()));
    
    timeElapsed+=dt;
    if(timeElapsed<0)
        timeElapsed = 0;
    this->boardBody->SetLinearVelocity(b2Vec2(amplitudeOscillationX*frequencyOscillationX*cos(frequencyOscillationX*timeElapsed), amplitudeOscillationY*frequencyOscillationY*cos(frequencyOscillationY*timeElapsed)));
    this->metalRod->bodyHorizontal->SetLinearVelocity(b2Vec2(amplitudeOscillationX*frequencyOscillationX*cos(frequencyOscillationX*timeElapsed), amplitudeOscillationY*frequencyOscillationY*cos(frequencyOscillationY*timeElapsed)));
    this->metalRod->bodyVertical->SetLinearVelocity(b2Vec2(amplitudeOscillationX*frequencyOscillationX*cos(frequencyOscillationX*timeElapsed), amplitudeOscillationY*frequencyOscillationY*cos(frequencyOscillationY*timeElapsed)));
    
    if(!orientation)
        this->shadowSprite->setPosition(Point( (this->boardBody->GetPosition().x+(2*this->widthHalf+metalRod->horizontalLength)/2.0) * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    else
        this->shadowSprite->setPosition(Point( (this->boardBody->GetPosition().x-(2*this->widthHalf+metalRod->horizontalLength)/2.0) * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
}

long long StaticBoard::boardCollidedReturnScoreUpdate(b2Contact *contact, float worldToPixelScale, Vec2 offsetOriginToBeAdded, const vector<AbstractBall*>& balls_in_game){
    
    //return if ball is not collided
    bool ballCollided = false;
    for(int i=0; i<balls_in_game.size(); i++){
        if(contact->GetFixtureA()==balls_in_game[i]->ballFixture || contact->GetFixtureB()==balls_in_game[i]->ballFixture){
            ballCollided = true;
            break;
        }
    }
    if(!ballCollided)
        return 0;
    
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    b2Vec2 localPoint = this->boardBody->GetLocalPoint(worldManifold.points[0]);
    
    if( (orientation==false && localPoint.x<0) || (orientation==true && localPoint.x>0) ){
        float distanceImpactFromHinge = localPoint.Normalize();
        if(distanceImpactFromHinge<=this->bonusRadius){
            showScoreUpdate(50, worldToPixelScale, offsetOriginToBeAdded);
            return 50;
        }else{
            showScoreUpdate(10, worldToPixelScale, offsetOriginToBeAdded);
            return 10;
        }
    }else
        return 0;
}

void StaticBoard::showScoreUpdate(long long deltaScore, float worldToPixelScale, Vec2 offsetOriginToBeAdded){
    sprintf(scoreDeltaString, "+%lld", deltaScore);
    if(deltaScore<0)
        sprintf(scoreDeltaString, "-%lld", deltaScore);
    scoreDeltaLabel->setString(scoreDeltaString);
    
    scoreDeltaLabel->setOpacity(255);
    auto fadeOut = FadeOut::create(1.0f);
    
    auto moveBy = MoveBy::create(1.0f, Vec2(0, 0.10*worldToPixelScale));
    auto moveByEaseOut = EaseOut::create(moveBy->clone(), 2.0f);
    
    scoreDeltaLabel->runAction(fadeOut);
    scoreDeltaLabel->runAction(moveByEaseOut);
    
    scoreDeltaLabel->setPosition(Vec2(offsetOriginToBeAdded.x + Director::getInstance()->getVisibleOrigin().x + this->boardBody->GetPosition().x*worldToPixelScale, offsetOriginToBeAdded.y + Director::getInstance()->getVisibleOrigin().y + (this->boardBody->GetPosition().y + this->heightHalf + 0.15)*worldToPixelScale));
    scoreDeltaLabel->setOpacity(0);
}
