//
//  PowerupPopupSelectionLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 02/08/16.
//
//

#include "PowerupPopupSelectionLayer.hpp"
#include "GameScene.hpp"
#include "../Colors.hpp"

bool PowerupPopupSelectionLayer::init()
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
    
    background = DrawNode::create();
    auto diagonalVector = Vec2(visibleSize.width/4, visibleSize.height/4);
    background->drawSolidRect(origin + diagonalVector, origin + 3*diagonalVector, Colors::wet_asphalt);
    
    background->setOpacity(0);
    this->addChild(background);
    this->setVisible(false);
    
    //buttonResume
    float paddingButton = visibleSize.width*1.0/100;
    auto buttonResume = cocos2d::ui::Button::create();
    buttonResume->setTouchEnabled(true);
    buttonResume->loadTextures("button_press_png.png", "button_pressed_already_png.png");
    buttonResume->setTitleColor(Color3B::BLACK);
    buttonResume->setTitleText("Resume");
    buttonResume->setTitleFontSize(20);
    buttonResume->setAnchorPoint(Vec2(0.5, 0));
    buttonResume->setScale(0.5);
    buttonResume->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 + paddingButton));
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
    this->addChild(buttonResume);
    
    //buttonTimeFreezer
    auto buttonQuit = cocos2d::ui::Button::create();
    buttonQuit->setTouchEnabled(true);
    buttonQuit->loadTextures("button_press_png.png", "button_pressed_already_png.png");
    buttonQuit->setTitleColor(Color3B::BLACK);
    buttonQuit->setTitleText("TimeFreezerBird");
    buttonQuit->setTitleFontSize(20);
    buttonQuit->setAnchorPoint(Vec2(0.5, 1.0));
    buttonQuit->setScale(0.5);
    buttonQuit->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - paddingButton));
    buttonQuit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                
                break;
            case ui::Widget::TouchEventType::ENDED:{
                this->dismiss();
                gameScene->resumeGameScene();
                gameScene->instantiateAndApplyPowerup("TimeFreezerBird");
                break;
            }
            default:
                break;
        }
    });
    this->addChild(buttonQuit);
    
    //SelectLabel
    auto labelPause = Label::createWithTTF("Select Powerup", "fonts/Marker Felt.ttf", 20);
    labelPause->setColor(Color3B(255, 255, 255));
    labelPause->setAnchorPoint(Vec2(0.5, 1.0));
    labelPause->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - visibleSize.height/4));
    this->addChild(labelPause);
    
    return true;
}


void PowerupPopupSelectionLayer::show(){
    this->setVisible(true);
}


void PowerupPopupSelectionLayer::dismiss(){
    this->setVisible(false);
}
