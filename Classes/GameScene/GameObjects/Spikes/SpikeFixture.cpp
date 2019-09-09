//
//  SpikeFixture.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 05/08/16.
//
//

#include "SpikeFixture.hpp"
#include <iostream>
using namespace std;

SpikeFixture::SpikeFixture(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, b2Body *parentBodyPointer, float offsetWidthHalf, float offsetHeightHalf, SpikeFixtureInitialParameters *initialParameters){
    
    //save inital config info from initialParameters objects
    this->leftOriented = initialParameters->leftOriented;
    this->baseWidth = initialParameters->baseWidth;
    this->baseHeight = initialParameters->baseHeight;
    this->distanceFromCenter = initialParameters->distanceFromCenter;
    this->restitution = initialParameters->restitution;
    this->friction = initialParameters->friction;
    
    this->parentBody = parentBodyPointer; //store for future access needed in updateState
    
    this->spriteSpike = Sprite::create("triangle.png");
    this->spriteSpike->setScale(baseHeight*worldToPixelScale/this->spriteSpike->getContentSize().width, baseWidth*worldToPixelScale/this->spriteSpike->getContentSize().height);
    parentCocosLayer->addChild(this->spriteSpike, 0);
    if(!leftOriented)
        spriteSpike->setFlippedX(true);
    
    b2Vec2 vertices[3];
    
    if(leftOriented){
        vertices[0].Set(0 - offsetWidthHalf,  0 + distanceFromCenter);
        vertices[1].Set(0 - offsetWidthHalf,  0 + distanceFromCenter - baseWidth);
        vertices[2].Set(0 - offsetWidthHalf - baseHeight, 0 + distanceFromCenter - baseWidth/2.0);
    }else{
        //remember, in clockwise order!
        vertices[1].Set(0 + offsetWidthHalf,  0 + distanceFromCenter);
        vertices[0].Set(0 + offsetWidthHalf,  0 + distanceFromCenter - baseWidth);
        vertices[2].Set(0 + offsetWidthHalf + baseHeight, 0 + distanceFromCenter - baseWidth/2.0);
    }
        
    b2PolygonShape spikeShape;
    spikeShape.Set(vertices, 3);
    
    b2FixtureDef spikeFixtureDef;
    spikeFixtureDef.shape = &spikeShape;
    this->spikeFixture = parentBody->CreateFixture(&spikeFixtureDef);

}

SpikeFixture::~SpikeFixture(){
    
}

//implement interface
void SpikeFixture::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    auto shape = (b2PolygonShape *)this->spikeFixture->GetShape();
    b2Vec2 v1 = this->parentBody->GetWorldPoint(shape->GetVertex(0));
    b2Vec2 v2 = this->parentBody->GetWorldPoint(shape->GetVertex(1));
    b2Vec2 v3 = this->parentBody->GetWorldPoint(shape->GetVertex(2));

    b2Vec2 spikeSpritePosition;
    spikeSpritePosition.Set((v1.x+v2.x+v3.x)/3.0, (v1.y+v2.y+v3.y)/3.0);

    this->spriteSpike->setPosition(Point(spikeSpritePosition.x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, spikeSpritePosition.y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->spriteSpike->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->parentBody->GetAngle()));
}

