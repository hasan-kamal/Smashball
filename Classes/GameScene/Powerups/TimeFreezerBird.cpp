//
//  TimeFreezerBird.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 02/08/16.
//
//

#include "TimeFreezerBird.hpp"
#include <iostream>
using namespace std;

TimeFreezerBird::TimeFreezerBird(Layer *parentCocosLayer, float worldToPixelScale, Vec2 haltPositionVector, GameScene *gameSceneCaller){
    
    this->gameScene = gameSceneCaller;
    this->stopPos = haltPositionVector;
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("bird_left_spritesheet.png");
    
    // load the Sprite Sheet
    auto spritecache = SpriteFrameCache::getInstance();
    
    // the .plist file can be generated with any of the tools mentioned below
    spritecache->addSpriteFramesWithFile("bird_left_spritesheet.plist");
    
    mysprite = Sprite::createWithSpriteFrameName("bird1.png");
    mysprite->setAnchorPoint(Vec2(0, 1.0));
    mysprite->setPosition(Vec2(origin.x+visibleSize.width, stopPos.y));
    mysprite->setScale(this->heightInWorld*worldToPixelScale/mysprite->getContentSize().height);
    spritebatch->addChild(mysprite);
    parentCocosLayer->addChild(spritebatch, 6);
    
    cocos2d::Vector<SpriteFrame*> animFrames(8);
    
    char str[100] = {0};
    for(int i = 1; i < 8; i++)
    {
        sprintf(str, "bird%d.png", i);
        SpriteFrame* frame = spritecache->getSpriteFrameByName( str );
        animFrames.pushBack(frame);
    }
    
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.10f);
    mysprite->runAction( RepeatForever::create( Animate::create(animation) ) );
}

TimeFreezerBird::~TimeFreezerBird(){
    cout<<"TimeFreezerBird has been destructed"<<endl;
}

void TimeFreezerBird::updateState(float dt, float worldToPixelScale){
    
}

void TimeFreezerBird::startPowerup(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    float speed = (visibleSize.width-stopPos.x)/3.0;
    auto moveInAction = MoveTo::create(3.0, stopPos);
    this->mysprite->runAction(moveInAction);
    
    auto callbackHalt = CallFunc::create([this](){
        this->gameScene->haltTimerForSeconds(5.0);
    });
    
    auto moveOutAction = MoveBy::create((mysprite->getContentSize().width+stopPos.x-origin.x)/speed, Vec2(-1*(mysprite->getContentSize().width+stopPos.x-origin.x), 0));
    
    auto delay = DelayTime::create(5.0);
    
    auto seq = Sequence::create(moveInAction, callbackHalt, delay, moveOutAction, nullptr);
    mysprite->runAction(seq);

}