//
//  GameOverLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/07/16.
//
//

#include "GameOverLayer.hpp"
#include "GameScene.hpp"
#include "../Colors.hpp"

#include <iostream>
using namespace std;

bool GameOverLayer::init()
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
    background->drawSolidRect(origin, Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height), Colors::cloudsFuzzy);
    this->addChild(background);
    
    float paddingVertical = visibleSize.height*5.0/100;
    
    //lastHighscoreLabel
    lastHighscoreLabel = Label::createWithTTF("", "fonts/Roboto-Light.ttf", 20);
    lastHighscoreLabel->setColor(Color3B(52, 73, 80));
    lastHighscoreLabel->setAnchorPoint(Vec2(0.5, 0.5));
    lastHighscoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                         origin.y + visibleSize.height/2));
    this->addChild(lastHighscoreLabel, 1);
    
    //scoreLabel
    scoreLabel = Label::createWithTTF("", "fonts/Roboto-Light.ttf", 20);
    scoreLabel->setColor(Color3B(52, 73, 80));
    scoreLabel->setAnchorPoint(Vec2(0.5, 0.0));
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/2 + paddingVertical));
    this->addChild(scoreLabel, 1);
    
    //buttonRestart
    buttonRestart = cocos2d::ui::Button::create();
    buttonRestart->setTouchEnabled(true);
    buttonRestart->loadTextures("restart.png", "restart.png");
    buttonRestart->setAnchorPoint(Vec2(1.0, 1.0));
    buttonRestart->setScale(visibleSize.height*15.0/100/buttonRestart->getContentSize().height);
    buttonRestart->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - paddingVertical));
    buttonRestart->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                if(gameScene){
                    gameScene->restartGame();
                }
                break;
            }
            default:
                break;
        }
    });
    this->addChild(buttonRestart);
    
    //buttonQuit
    buttonQuit = cocos2d::ui::Button::create();
    buttonQuit->setTouchEnabled(true);
    buttonQuit->loadTextures("close_thin.png", "close_thin.png");
    buttonQuit->setAnchorPoint(Vec2(0.0, 1.0));
    buttonQuit->setScale(visibleSize.height*15.0/100/buttonQuit->getContentSize().height);
    buttonQuit->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - paddingVertical));
    buttonQuit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                if(gameScene){
                    gameScene->quitGame();
                }
                break;
            }
            default:
                break;
        }
    });
    this->addChild(buttonQuit);
    
    return true;
}

void GameOverLayer::show(long long score, string stageDesc){
    sprintf(scoreString, "New Score: %lld", score);
    scoreLabel->setString(scoreString);
    
    sprintf(lastHighscoreString, "Last Highscore: %lld", HighscoreManager::getHighscore(stageDesc));
    lastHighscoreLabel->setString(lastHighscoreString);
    
    auto moveDown = MoveTo::create(0.5f, Vec2(0, 0));
    auto moveDownEase = EaseIn::create(moveDown->clone(), 2.0);
    this->runAction(moveDownEase);
}


void GameOverLayer::dismiss(){
    auto moveUp = MoveTo::create(0.5f, Vec2(0, Director::getInstance()->getVisibleSize().height));
    auto moveUpEase = EaseIn::create(moveUp->clone(), 2.0);
    this->runAction(moveUpEase);
}
