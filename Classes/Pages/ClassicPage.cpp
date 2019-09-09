//
//  ClassicPage.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#include "ClassicPage.hpp"
#include "../Colors.hpp"

bool ClassicPage::init(int pageNum, Vec2 pseudoOrg){
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //save origin info
    this->pageNumber = pageNum;
    this->pseudoOrigin.x = pseudoOrg.x;
    this->pseudoOrigin.y = pseudoOrg.y;
    
    //create label
    char chapterString[50];
    sprintf(chapterString, "Leaderboard");
    auto label = Label::createWithTTF(chapterString, "fonts/Trirong-Light.ttf", 24);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float padding = visibleSize.height*5.0/100;
    label->setAnchorPoint(Vec2(0.5, 1.0));
    label->setPosition(Vec2(pseudoOrigin.x + visibleSize.width/2,
                            pseudoOrigin.y + visibleSize.height - padding));
    label->setTextColor(Color4B(Color4F(255-52, 255-73, 255-80, 1.0)));
    this->addChild(label, 1);
    
    //create Classic label
    auto classicLabel = Label::createWithTTF("Classic", "fonts/Roboto-Light.ttf", 18);
    classicLabel->setAnchorPoint(Vec2(0.5, 0.5));
    classicLabel->setPosition(Vec2(pseudoOrigin.x + visibleSize.width/2,
                            pseudoOrigin.y + visibleSize.height/2));
    classicLabel->setTextColor(Color4B(Color4F(255-52, 255-73, 255-80, 1.0)));
    this->addChild(classicLabel, 1);
    
    //buttonClassic
    float paddingButton = visibleSize.width*1.0/100;
    buttonClassic = cocos2d::ui::Button::create();
    buttonClassic->setTouchEnabled(true);
    buttonClassic->loadTextures("button_press_png.png", "button_pressed_already_png.png");
    buttonClassic->setTitleColor(Color3B::BLACK);
    buttonClassic->setTitleFontName("Roboto-Light");
    char classicTitle[50];
    sprintf(classicTitle, "Classic %lld", HighscoreManager::getHighscore("stagefiles/stage-classic.txt"));

    buttonClassic->setTitleText(classicTitle);
    buttonClassic->setTitleFontSize(20);
    buttonClassic->setAnchorPoint(Vec2(0.5, 1.0));
    buttonClassic->setScale(0.5);
    buttonClassic->setPosition(Vec2(pseudoOrigin.x + visibleSize.width/2, pseudoOrigin.y + visibleSize.height/2 - paddingButton));
    buttonClassic->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                GameSceneInitialParameters g;
                string file = "stagefiles/stage-classic.txt";
                string contentString = FileUtils::getInstance()->getStringFromFile(file);
                auto gameScene = GameScene::createScene(contentString, file, &g);
                Director::getInstance()->replaceScene(TransitionFade::create(1.0, gameScene, Color3B(Color4F(255-236, 255-240, 255-240, 1.0))));
                break;
            }
            default:
                break;
        }
    });
    buttonClassic->setColor(Color3B(Colors::silver));
    //this->addChild(buttonClassic);
    
    return true;
}
