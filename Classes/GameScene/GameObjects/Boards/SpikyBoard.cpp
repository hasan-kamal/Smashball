//
//  SpikyBoard.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 05/08/16.
//
//

#include "SpikyBoard.hpp"
#include "../../GameScene.hpp"
#include <math.h>

#include <iostream>
using namespace std;

SpikyBoard::SpikyBoard(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, GameScene *gameSceneMain, SpikyBoardInitialParameters *initialParameters){
    
    this->gameScene = gameSceneMain;
    
    //save and take intial configuration info from initialParameters objects
    this->isOriented = initialParameters->isOriented;
    this->orientation = initialParameters->orientation; //0-denotes left-oriented
    this->heightHalf = initialParameters->heightHalf;
    this->widthHalf = initialParameters->widthHalf;
    this->initialPosition = initialParameters->initialPosition;
    this->angleInclinationInitial = initialParameters->angleInclinationInitial;
    this->bonusRadius = initialParameters->bonusRadius;
    this->boardDensity = initialParameters->boardDensity;
    this->boardRestitution = initialParameters->boardRestitution;
    this->paddingGap = initialParameters->paddingGap;
    this->motorSpeed = initialParameters->motorSpeed;
    this->maxMotorTorque = initialParameters->maxMotorTorque;
    //this->numSpikesInBoard = initialParameters->numSpikes;
    this->amplitudeOscillationX = initialParameters->amplitudeOscillationX;
    this->frequencyOscillationX = initialParameters->frequencyOscillationX;
    this->amplitudeOscillationY = initialParameters->amplitudeOscillationY;
    this->frequencyOscillationY = initialParameters->frequencyOscillationY;
    
    //hinge sprite initialization
    this->spriteHinge = Sprite::create();
    this->spriteHinge->setColor(Color3B(0, 0, 0));
    this->spriteHinge->setScale(2*this->radiusHinge*worldToPixelScale/this->spriteHinge->getContentSize().width);
    parentCocosLayer->addChild(this->spriteHinge, 1);
    
    //board sprite initialization partwise
    
    //upper part
    if(this->isOriented)
        this->boardSpriteUpper = Sprite::create("board_modern_hinge_blue_upper_oriented.png");
    else
        this->boardSpriteUpper = Sprite::create("board_modern_hinge_blue_upper.png");
    this->boardSpriteUpper->setScale(2*this->widthHalf*worldToPixelScale/this->boardSpriteUpper->getContentSize().width, (this->heightHalf-this->bonusRadius-this->paddingGap)*worldToPixelScale/this->boardSpriteUpper->getContentSize().height);
    this->boardSpriteUpper->setAnchorPoint(Vec2(0.5, -1*(bonusRadius+paddingGap)/(heightHalf-bonusRadius-paddingGap)));
    if(orientation)
        this->boardSpriteUpper->setFlippedX(true);
    
    //middle part
    if(this->isOriented)
        this->boardSpriteMiddle = Sprite::create("board_modern_hinge_blue_middle.png");
    else
        this->boardSpriteMiddle = Sprite::create("board_modern_hinge_blue_middle.png");
    this->boardSpriteMiddle->setScale(2*this->widthHalf*worldToPixelScale/this->boardSpriteMiddle->getContentSize().width, 2*this->bonusRadius*worldToPixelScale/this->boardSpriteMiddle->getContentSize().height);
    this->boardSpriteMiddle->setAnchorPoint(Vec2(0.5, 0.5));
    if(orientation)
        this->boardSpriteMiddle->setFlippedX(true);
    
    
    //lower part
    if(this->isOriented)
        this->boardSpriteLower = Sprite::create("board_modern_hinge_blue_lower_oriented.png");
    else
        this->boardSpriteLower = Sprite::create("board_modern_hinge_blue_lower.png");
    this->boardSpriteLower->setScale(2*this->widthHalf*worldToPixelScale/this->boardSpriteLower->getContentSize().width, (this->heightHalf-this->bonusRadius-this->paddingGap)*worldToPixelScale/this->boardSpriteLower->getContentSize().height);
    this->boardSpriteLower->setAnchorPoint(Vec2(0.5, 1.0 + (bonusRadius+paddingGap)/(heightHalf-bonusRadius-paddingGap)));
    if(orientation)
        this->boardSpriteLower->setFlippedX(true);
    
    
    parentCocosLayer->addChild(this->boardSpriteMiddle, 1);
    parentCocosLayer->addChild(this->boardSpriteLower, 1);
    parentCocosLayer->addChild(this->boardSpriteUpper, 1);
    
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
    
    this->boardBody = world->CreateBody(&boardBodyDef);
    this->boardBody->CreateFixture(&boardFixtureDef);
    
    //revolute joint
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = this->bodyHinge;
    jointDef.bodyB = this->boardBody;
    jointDef.collideConnected = false;
    jointDef.localAnchorA.Set(this->bodyHinge->GetLocalCenter().x, this->bodyHinge->GetLocalCenter().y);
    jointDef.localAnchorB.Set(this->boardBody->GetLocalCenter().x, this->boardBody->GetLocalCenter().y);
    jointDef.enableMotor = true;
    jointDef.maxMotorTorque = this->maxMotorTorque;
    jointDef.motorSpeed = this->motorSpeed;
    revoluteJoint = (b2RevoluteJoint *)world->CreateJoint(&jointDef);
    
    //score delta label
    this->scoreDeltaLabel = Label::createWithTTF("0", "fonts/Roboto-Light.ttf", 20);
    this->scoreDeltaLabel->setColor(Color3B(189, 195, 192));
    this->scoreDeltaLabel->setPosition(Vec2(Director::getInstance()->getVisibleOrigin().x + this->boardBody->GetPosition().x*worldToPixelScale, Director::getInstance()->getVisibleOrigin().y + (this->boardBody->GetPosition().y + this->heightHalf + 0.15)*worldToPixelScale));
    this->scoreDeltaLabel->setOpacity(0);
    parentCocosLayer->addChild(this->scoreDeltaLabel, 1);
    
    //rod initialization
    virtualRod = new VirtualRod(world, parentCocosLayer, worldToPixelScale, this->boardBody->GetPosition(), offsetOriginToBeAdded, (this->initialPosition.x>2.5)==true);
    
    //shadow initialization
    this->shadowSprite = Sprite::create("shadow.png");
    this->shadowSprite->setAnchorPoint(Vec2(0.5, 1.0));
    
    this->shadowSprite->setScale(2*(fabs(this->heightHalf*sin(this->boardBody->GetAngle()))+0.20)*worldToPixelScale/this->shadowSprite->getContentSize().width, this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height);
    this->shadowSprite->setOpacity(100);
    
    this->shadowSprite->setPosition(Point( this->boardBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    
    parentCocosLayer->addChild(this->shadowSprite);
    
    
    for(int i=0; i<initialParameters->params_for_spikes.size(); i++){
        spikes.push_back(new SpikeFixture(world, parentCocosLayer, worldToPixelScale, this->boardBody, this->widthHalf, this->heightHalf, initialParameters->params_for_spikes[i]));
    }
}

SpikyBoard::~SpikyBoard(){
    for(int i=0; i<spikes.size(); i++)
        delete spikes[i];
    delete virtualRod;
}

//implement interface
void SpikyBoard::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->boardBody->SetLinearVelocity(b2Vec2(0, 0));
    
    //update board
    this->boardSpriteUpper->setPosition(Point(this->boardBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->boardBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->boardSpriteUpper->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->boardBody->GetAngle()));
    
    this->boardSpriteMiddle->setPosition(Point(this->boardBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->boardBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->boardSpriteMiddle->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->boardBody->GetAngle()));
    
    this->boardSpriteLower->setPosition(Point(this->boardBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->boardBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->boardSpriteLower->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->boardBody->GetAngle()));
    
    //update hinge
    this->spriteHinge->setPosition(Point(this->bodyHinge->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->bodyHinge->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->spriteHinge->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->bodyHinge->GetAngle()));
    
    //shadow
    this->shadowSprite->setPosition(Point(this->boardBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));

    this->shadowSprite->setScale(2*(fabs(this->heightHalf*sin(this->boardBody->GetAngle()))+0.20)*worldToPixelScale/this->shadowSprite->getContentSize().width, this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height);
    this->shadowSprite->setOpacity(clip(fabs(this->heightHalf*cos(this->boardBody->GetAngle()))*255));

   //spike
    for(int i=0; i<spikes.size(); i++)
        spikes[i]->updateState(dt, worldToPixelScale, offsetOriginToBeAdded);
    
    //SHM movement
    timeElapsed+=dt;
    if(timeElapsed<0)
        timeElapsed = 0;
    this->bodyHinge->SetLinearVelocity(b2Vec2(amplitudeOscillationX*frequencyOscillationX*cos(frequencyOscillationX*timeElapsed), amplitudeOscillationY*frequencyOscillationY*cos(frequencyOscillationY*timeElapsed)));
    
    virtualRod->spriteHorizontal->setPosition(Point(this->bodyHinge->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->bodyHinge->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
}

double SpikyBoard::clip(double x){
    //clips input double between min and max
    double min = 70.0;
    double max = 100.0;
    
    if(x>max)
        x = max;
    else if(x<min)
        x = min;
    
    return x;
}

long long SpikyBoard::boardCollidedReturnScoreUpdate(b2Contact *contact, float worldToPixelScale, Vec2 offsetOriginToBeAdded, const vector<AbstractBall*>& balls_in_game){
    
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
    
    for(int i=0; i<spikes.size(); i++){
        
        if(contact->GetFixtureA()==spikes[i]->spikeFixture){
            for(int j=0; j<balls_in_game.size(); j++){
                if(contact->GetFixtureB()==balls_in_game[j]->ballFixture){
                    //we know a ball has collided with a spike
                    balls_in_game[j]->reduce_health(GlobalConfigs::SPIKE_DAMAGE);
                    gameScene->ball_health_label_update();
                    if(balls_in_game[j]->health<=0)
                        gameScene->destroyBallWithBody(contact->GetFixtureB()->GetBody());
                    return 0;
                }
            }
            
        }else if(contact->GetFixtureB()==spikes[i]->spikeFixture){
            for(int j=0; j<balls_in_game.size(); j++){
                if(contact->GetFixtureA()==balls_in_game[j]->ballFixture){
                    //we know a ball has collided with a spike
                    balls_in_game[j]->reduce_health(GlobalConfigs::SPIKE_DAMAGE);
                    gameScene->ball_health_label_update();
                    if(balls_in_game[j]->health<=0)
                        gameScene->destroyBallWithBody(contact->GetFixtureB()->GetBody());
                    return 0;
                }
            }
            
        }
    }

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);
    b2Vec2 localPoint = bodyHinge->GetLocalPoint(worldManifold.points[0]);
    
    b2Vec2 normalUnitVector;
    normalUnitVector.Set(-1*cos(this->boardBody->GetAngle()), -1*sin(this->boardBody->GetAngle()));
    float distanceImpactFromHinge = localPoint.Normalize();
    
    //side 1: magnitude of smaller angle between localPoint vector and normalUnitVector is <PI/2
    //side 2: otherwise
    
    Vec2 u1 = Vec2(localPoint.x, localPoint.y);
    Vec2 u2 = Vec2(normalUnitVector.x, normalUnitVector.y);
    float x = u1.getAngle()-u2.getAngle();
    double PI = 3.1415926;
    if(x<0)
        x = -1*x;
    if(x>PI)
        x = 2*PI - x;
    cout<<x<<endl;
    
    if( (isOriented==false) || (isOriented==true && orientation==false && x<PI/2.0) || (isOriented==true && orientation==true && x>PI/2.0) ){
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

void SpikyBoard::showScoreUpdate(long long deltaScore, float worldToPixelScale, Vec2 offsetOriginToBeAdded){
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
