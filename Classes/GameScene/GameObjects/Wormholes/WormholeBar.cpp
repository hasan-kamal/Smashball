//
//  WormholeBar.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 30/09/16.
//
//

#include "WormholeBar.hpp"

WormholeBar::WormholeBar(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, WormholeBarInitialParameters *initialParameters){
    
    //save configuration from initialParameters
    this->orientation = initialParameters->orientation; // 0 denotes left-oriented
    this->heightHalf = initialParameters->heightHalf;
    this->widthHalf = initialParameters->widthHalf;
    this->sensorBodyWidthToTotalWidthRatio = initialParameters->sensorBodyWidthToTotalWidthRatio;
    this->lightGlowWidth = initialParameters->lightGlowWidth;
    this->lightPaddingWidth = initialParameters->lightPaddingWidth;
    this->heightTopSeparatorInWorld = initialParameters->heightTopSeparatorInWorld;
    this->initialPosition.x = initialParameters->initialPosition.x;
    this->initialPosition.y = initialParameters->initialPosition.y;
    this->density = initialParameters->density;
    this->restitution = initialParameters->restitution;

    
    this->spriteGlow = Sprite::create("wormhole_light.png");
    this->spriteGlow->setScale(lightGlowWidth*worldToPixelScale/this->spriteGlow->getContentSize().width, 2*(heightHalf*1.08)*worldToPixelScale/this->spriteGlow->getContentSize().height);
    if(orientation==1){
        //flip about x-axis if right oriented
        this->spriteGlow->setFlippedX(true);
    }
    if(orientation==0)
        this->spriteGlow->setAnchorPoint(Vec2(1.0, 0.5));
    else
        this->spriteGlow->setAnchorPoint(Vec2(0.0, 0.5));
    parentCocosLayer->addChild(this->spriteGlow, 1);
    
    //continuous fadeOut and fadeIn of glow light
    auto fadeOut = FadeTo::create(0.5f, 100);
    auto fadeIn = FadeTo::create(0.5f, 255);
    auto seq = Sequence::create(fadeOut, fadeIn, NULL);
    auto repeatSeq = RepeatForever::create(seq);
    repeatSeq->setTag(100);
    this->spriteGlow->runAction(repeatSeq);
    
    this->spriteMain = Sprite::create("wormhole_main.png");
    this->spriteMain->setScale(2*widthHalf*worldToPixelScale/this->spriteMain->getContentSize().width, 2*heightHalf*worldToPixelScale/this->spriteMain->getContentSize().height);
    parentCocosLayer->addChild(this->spriteMain, 1);
    
    //bottom separator body physics initialization
    b2PolygonShape bottomBodyShape;
    bottomBodyShape.SetAsBox(widthHalf, 0.5*heightTopSeparatorInWorld);
    
    b2FixtureDef bottomBodyFixtureDef;
    bottomBodyFixtureDef.shape = &bottomBodyShape;
    bottomBodyFixtureDef.density = this->density;
    bottomBodyFixtureDef.restitution = this->restitution;
    
    b2BodyDef bottomBodyDef;
    bottomBodyDef.type = b2_staticBody;
    bottomBodyDef.userData = this;
    bottomBodyDef.position.Set(initialPosition.x, initialPosition.y-heightHalf+heightTopSeparatorInWorld/2.0);
    
    bottomSeparatorBody = world->CreateBody(&bottomBodyDef);
    bottomSeparatorBody->CreateFixture(&bottomBodyFixtureDef);
    
    
    //top separator body physics initialization
    b2PolygonShape topBodyShape;
    topBodyShape.SetAsBox(widthHalf, 0.5*heightTopSeparatorInWorld);
    
    b2FixtureDef topBodyFixtureDef;
    topBodyFixtureDef.shape = &topBodyShape;
    topBodyFixtureDef.density = this->density;
    topBodyFixtureDef.restitution = this->restitution;
    
    b2BodyDef topBodyDef;
    topBodyDef.type = b2_staticBody;
    topBodyDef.userData = this;
    topBodyDef.position.Set(initialPosition.x, initialPosition.y+heightHalf-heightTopSeparatorInWorld/2.0);
    
    topSeparatorBody = world->CreateBody(&topBodyDef);
    topSeparatorBody->CreateFixture(&topBodyFixtureDef);
    
    //concrete body physics initialization
    b2PolygonShape concreteBodyShape;
    concreteBodyShape.SetAsBox(widthHalf*(1.0-sensorBodyWidthToTotalWidthRatio), heightHalf - heightTopSeparatorInWorld);
    
    b2FixtureDef concreteBodyFixtureDef;
    concreteBodyFixtureDef.shape = &concreteBodyShape;
    concreteBodyFixtureDef.density = this->density;
    concreteBodyFixtureDef.restitution = this->restitution;
    
    b2BodyDef concreteBodyDef;
    concreteBodyDef.type = b2_staticBody;
    concreteBodyDef.userData = this;
    if(orientation==0){
        //left oriented
        b2Vec2 partition;
        partition.Set(initialPosition.x-widthHalf+sensorBodyWidthToTotalWidthRatio*2.0*widthHalf, initialPosition.y);
        concreteBodyDef.position.Set(partition.x + 0.5*(1.0-sensorBodyWidthToTotalWidthRatio)*2.0*widthHalf, initialPosition.y);
    }else{
        //right oriented
        b2Vec2 partition;
        partition.Set(initialPosition.x+widthHalf-sensorBodyWidthToTotalWidthRatio*2.0*widthHalf, initialPosition.y);
        concreteBodyDef.position.Set(partition.x - 0.5*(1.0-sensorBodyWidthToTotalWidthRatio)*2.0*widthHalf, initialPosition.y);
    }
    
    concreteBody = world->CreateBody(&concreteBodyDef);
    concreteBody->CreateFixture(&concreteBodyFixtureDef);

    
    //sensorBody physics initialization
    b2PolygonShape sensorBodyShape;
    sensorBodyShape.SetAsBox(widthHalf*sensorBodyWidthToTotalWidthRatio, heightHalf - heightTopSeparatorInWorld);
    
    b2FixtureDef sensorBodyFixtureDef;
    sensorBodyFixtureDef.shape = &sensorBodyShape;
    sensorBodyFixtureDef.density = this->density;
    sensorBodyFixtureDef.restitution = this->restitution;
    //sensorBodyFixtureDef.isSensor = true;
    //NOT PUTTING IT AS SENSOR BECAUSE CONTINUOUS COLLISION DETECTION DOES NOT WORK
    //ON SENSOR BODIES, AND ANYWAYS IT WASNT HELPING EITHER
    
    b2BodyDef sensorBodyDef;
    sensorBodyDef.type = b2_staticBody;
    sensorBodyDef.userData = this;
    if(orientation==0){
        //left oriented
        b2Vec2 partition;
        partition.Set(initialPosition.x-widthHalf+sensorBodyWidthToTotalWidthRatio*2.0*widthHalf, initialPosition.y);
        sensorBodyDef.position.Set(partition.x - 0.5*sensorBodyWidthToTotalWidthRatio*2.0*widthHalf, initialPosition.y);
    }else{
        //right oriented
        b2Vec2 partition;
        partition.Set(initialPosition.x+widthHalf-sensorBodyWidthToTotalWidthRatio*2.0*widthHalf, initialPosition.y);
        sensorBodyDef.position.Set(partition.x + 0.5*sensorBodyWidthToTotalWidthRatio*2.0*widthHalf, initialPosition.y);
    }
        
    sensorBody = world->CreateBody(&sensorBodyDef);
    sensorBody->CreateFixture(&sensorBodyFixtureDef);
    
//    sensorBody->SetTransform(sensorBody->GetPosition(), 1.0);
//    concreteBody->SetTransform(concreteBody->GetPosition(), 1.0);
//    topSeparatorBody->SetTransform(topSeparatorBody->GetPosition(), 1.0);
//    bottomSeparatorBody->SetTransform(bottomSeparatorBody->GetPosition(), 1.0);
}

WormholeBar::~WormholeBar(){
    
}

void WormholeBar::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->spriteMain->setPosition(Point(initialPosition.x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, initialPosition.y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    
    //this->spriteMain->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->sensorBody->GetAngle()));
    
    b2Vec2 spriteGlowPositionInWorld;
    if(orientation==0)
        spriteGlowPositionInWorld.Set(initialPosition.x - widthHalf - lightPaddingWidth, initialPosition.y);
    else
        spriteGlowPositionInWorld.Set(initialPosition.x + widthHalf + lightPaddingWidth, initialPosition.y);
    this->spriteGlow->setPosition(Point(spriteGlowPositionInWorld.x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, spriteGlowPositionInWorld.y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    
    //this->spriteGlow->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->sensorBody->GetAngle()));
}

void WormholeBar::enable(){
    //continuous fadeOut and fadeIn of glow light
    spriteGlow->setOpacity(255);
    auto fadeOut = FadeTo::create(0.5f, 100);
    auto fadeIn = FadeTo::create(0.5f, 255);
    auto seq = Sequence::create(fadeOut, fadeIn, NULL);
    auto repeatSeq = RepeatForever::create(seq);
    repeatSeq->setTag(100);
    this->spriteGlow->runAction(repeatSeq);
}

void WormholeBar::disable(){
    spriteGlow->stopActionByTag(100);
    spriteGlow->setOpacity(0);
}
