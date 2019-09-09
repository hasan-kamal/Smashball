//
//  PrematureGameOverLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 13/08/16.
//
//

#include "PrematureGameOverLayer.hpp"
#include "GameScene.hpp"
#include "../Colors.hpp"

bool PrematureGameOverLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto winSize = Director::getInstance()->getWinSize();
    
    //set it above screen initially
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(Vec2(0, visibleSize.height));
    
    auto background = DrawNode::create();
    background->drawSolidRect(origin, Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height), Colors::clouds);
    this->addChild(background);
    
    scoreLabel = Label::createWithTTF("", "fonts/Roboto-Light.ttf", 20);
    scoreLabel->setColor(Color3B(52, 73, 80));
    scoreLabel->setAnchorPoint(Vec2(0.5, 0.5));
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/2));
    this->addChild(scoreLabel, 1);
    
    //buttonClassic
    restartButton = cocos2d::ui::Button::create();
    restartButton->setTouchEnabled(true);
    restartButton->loadTextures("button_pressed_already_png.png", "button_disabled.png");
    restartButton->setTitleColor(Color3B::BLACK);
    restartButton->setTitleText("Watch a video");
    restartButton->setTitleFontSize(20);
    restartButton->setAnchorPoint(Vec2(0.5, 0.5));
    restartButton->setScale(0.5);
    restartButton->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - restartButton->getContentSize().height));
    restartButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                if(gameScene){
                    gameScene->prematureRestart();
                }
                break;
            }
            default:
                break;
        }
    });
    this->addChild(restartButton);
    
    return true;
}

void PrematureGameOverLayer::show(long long score){
    sprintf(scoreString, "%lld", score);
    scoreLabel->setString(scoreString);
    auto moveDown = MoveTo::create(0.5f, Vec2(0, 0));
    this->runAction(moveDown);
}


void PrematureGameOverLayer::dismiss(){
    auto moveUp = MoveTo::create(0.5f, Vec2(0, Director::getInstance()->getVisibleSize().height));
    this->runAction(moveUp);
}
