//
//  GamePauseLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 30/07/16.
//
//

#include "GamePauseLayer.hpp"
#include "GameScene.hpp"
#include "../Colors.hpp"

#include <iostream>
using namespace std;

bool GamePauseLayer::init()
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
    
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(Vec2(0, 0));
    
    //layerColor
    layerColor = LayerColor::create(Color4B(Colors::cloudsFuzzy), visibleSize.width, visibleSize.height);
    this->addChild(layerColor);
    layerColor->setPosition(origin);
    layerColor->setOpacity(0);
    
    //buttonResume
    buttonResume = cocos2d::ui::Button::create();
    buttonResume->setTouchEnabled(true);
    buttonResume->loadTextures("resume.png", "resume.png");
    buttonResume->setAnchorPoint(Vec2(1.0, 0.5));
    buttonResume->setScale(visibleSize.height*20.0/100/buttonResume->getContentSize().height);
    buttonResume->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    buttonResume->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                this->dismiss();
                gameScene->resumeGameScene();
                break;
            }
            default:
                break;
        }
    });
    buttonResume->setOpacity(0);
    this->addChild(buttonResume);
    
    //buttonQuit
    buttonQuit = cocos2d::ui::Button::create();
    buttonQuit->setTouchEnabled(true);
    buttonQuit->loadTextures("close_thin.png", "close_thin.png");
    buttonQuit->setAnchorPoint(Vec2(0.0, 0.5));
    buttonQuit->setScale(visibleSize.height*20.0/100/buttonQuit->getContentSize().height);
    buttonQuit->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    buttonQuit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                this->dismiss();
                gameScene->quitGame();
                break;
            }
            default:
                break;
        }
    });
    buttonQuit->setOpacity(0);
    this->addChild(buttonQuit);
    
    return true;
}


void GamePauseLayer::show(){
    
    auto fadeInButton = FadeTo::create(0.2, 255);
    auto fadeInButtonEase = EaseIn::create(fadeInButton->clone(), 2.0);
    buttonResume->runAction(fadeInButtonEase);
    buttonQuit->runAction(fadeInButtonEase->clone());
    
    auto fadeInLayer = FadeTo::create(0.2, 200);
    auto fadeInLayerEase = EaseIn::create(fadeInLayer->clone(), 2.0);
    layerColor->runAction(fadeInLayerEase);
}


void GamePauseLayer::dismiss(){
    auto fadeInButton = FadeTo::create(0.2, 0);
    auto fadeInButtonEase = EaseIn::create(fadeInButton->clone(), 2.0);
    buttonResume->runAction(fadeInButtonEase);
    buttonQuit->runAction(fadeInButtonEase->clone());
    
    auto fadeInLayer = FadeTo::create(0.2, 0);
    auto fadeInLayerEase = EaseIn::create(fadeInLayer->clone(), 2.0);
    layerColor->runAction(fadeInLayerEase);
}
