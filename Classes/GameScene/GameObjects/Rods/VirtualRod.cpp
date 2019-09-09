//
//  VirtualRod.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 23/07/16.
//
//

#include "VirtualRod.hpp"

#include <iostream>
using namespace std;

VirtualRod::VirtualRod(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, b2Vec2 jointPosInWorld, Vec2 offsetOriginToBeAdded, bool orientationRight){
    
    //rod-horizontal sprite initialization
    texture = Director::getInstance()->getTextureCache()->addImage("slant 1.png"); //File's dimensions must be POT that is power of two, otherwise error. Limitation of OpenGL
    Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT}; //minFilter, magFilter, wrapS, wrapT
    //S means X, T means Y
    texture->setTexParameters(tp);
    
    spriteHorizontal = Sprite::createWithTexture(texture);
    spriteHorizontal->setScale(0.5, 1.0);
    
    spriteHorizontal->setTextureRect(Rect(0, 0, 1/spriteHorizontal->getScaleX()*2.0*(Director::getInstance()->getVisibleSize().width-jointPosInWorld.x*worldToPixelScale), spriteHorizontal->getContentSize().height));
    this->spriteHorizontal->setScale(spriteHorizontal->getScaleX(), this->thickness*worldToPixelScale/this->spriteHorizontal->getContentSize().height);
    if(orientationRight)
        this->spriteHorizontal->setAnchorPoint(Vec2(0, 0.5));
    else
        this->spriteHorizontal->setAnchorPoint(Vec2(1, 0.5));
    this->spriteHorizontal->setPosition(Point(jointPosInWorld.x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, jointPosInWorld.y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->spriteHorizontal->setOpacity(this->opacity);
    parentCocosLayer->addChild(this->spriteHorizontal);
    
}

void VirtualRod::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
}

VirtualRod::~VirtualRod(){
    
}
