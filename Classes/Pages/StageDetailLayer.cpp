//
//  StageDetailLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 13/10/16.
//
//

#include "StageDetailLayer.hpp"
#include "../Colors.hpp"

bool StageDetailLayer::init(Vec2 pseudoOrigin){
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    //background dark sprite
    this->backgroundDarkSprite = Sprite::create("dark_shade.png");
    this->backgroundDarkSprite->setAnchorPoint(Vec2(0.5, 0.5));
    this->backgroundDarkSprite->setScale(visibleSize.width/this->backgroundDarkSprite->getContentSize().width, visibleSize.height/this->backgroundDarkSprite->getContentSize().height);
    this->backgroundDarkSprite->setPosition(Vec2(pseudoOrigin.x + visibleSize.width/2, pseudoOrigin.y + visibleSize.height/2));
    this->backgroundDarkSprite->setOpacity(0);
    this->addChild(this->backgroundDarkSprite);
    
    //layer color
    layerColor = LayerColor::create(Color4B(Colors::clouds), visibleSize.width/2, visibleSize.height/2);
    this->addChild(layerColor);
    layerColor->setPosition(Vec2(pseudoOrigin.x + 0.25*visibleSize.width, pseudoOrigin.y + visibleSize.height));
    
    //create number label
    numberLabel = Label::createWithTTF("number", "fonts/Roboto-Light.ttf", 18);
    numberLabel->setAnchorPoint(Vec2(0.5, 1.0));
    numberLabel->setPosition(Vec2(layerColor->getContentSize().width/2, layerColor->getContentSize().height*92.0/100.0));
    numberLabel->setTextColor(Color4B(Color4F(255-52, 255-73, 255-80, 1.0)));
    layerColor->addChild(numberLabel);
    
    //create difficulty label
    difficultyLabel = Label::createWithTTF("Difficulty: easy", "fonts/Roboto-Light.ttf", 18);
    difficultyLabel->setAnchorPoint(Vec2(0.5, 1.0));
    difficultyLabel->setPosition(Vec2(layerColor->getContentSize().width/2, numberLabel->getPosition().y - numberLabel->getContentSize().height));
    difficultyLabel->setTextColor(Color4B(Color4F(255-52, 255-73, 255-80, 1.0)));
    layerColor->addChild(difficultyLabel);
    
    //create highscore label
    highscoreLabel = Label::createWithTTF("Highscore: easy", "fonts/Roboto-Light.ttf", 18);
    highscoreLabel->setAnchorPoint(Vec2(0.5, 1.0));
    highscoreLabel->setPosition(Vec2(layerColor->getContentSize().width/2,difficultyLabel->getPosition().y - difficultyLabel->getContentSize().height));
    highscoreLabel->setTextColor(Color4B(Color4F(255-52, 255-73, 255-80, 1.0)));
    layerColor->addChild(highscoreLabel);
    
    //buttonResume
    buttonResume = cocos2d::ui::Button::create();
    buttonResume->setTouchEnabled(true);
    buttonResume->loadTextures("resume.png", "resume.png");
    buttonResume->setAnchorPoint(Vec2(0.5, 1.0));
    buttonResume->setScale(visibleSize.height*20.0/100/buttonResume->getContentSize().height);
    buttonResume->setPosition(Vec2(layerColor->getContentSize().width/2,highscoreLabel->getPosition().y - highscoreLabel->getContentSize().height));
    buttonResume->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                startStage();
                break;
            }
            default:
                break;
        }
    });
    layerColor->addChild(buttonResume);
    
    //touch listener
    auto touchEventListener = EventListenerTouchOneByOne::create();
    touchEventListener->onTouchBegan = CC_CALLBACK_2(StageDetailLayer::onTouchBegan, this);
    touchEventListener->onTouchMoved = CC_CALLBACK_2(StageDetailLayer::onTouchMoved, this);
    touchEventListener->onTouchEnded = CC_CALLBACK_2(StageDetailLayer::onTouchEnded, this);
    touchEventListener->setSwallowTouches(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEventListener, this);
    
    return true;
}

void StageDetailLayer::startStage(){
    cout<<"Stage "<<stageNumber<<" selected"<<endl<<endl;
    char file[50];
    sprintf(file, "stagefiles/stage%d.txt", stageNumber );
    
    string contentString = FileUtils::getInstance()->getStringFromFile(file);
    
    GameSceneInitialParameters g;
    auto gameScene = GameScene::createScene(contentString, file, &g);
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, gameScene, Color3B(Color4F(255-236, 255-240, 255-240, 1.0))));
}

void StageDetailLayer::show(int stNum){
    
    if(isShowing)
        return;
    
    isShowing = true;
    this->stageNumber = stNum;
    
    char numberString[50];
    sprintf(numberString, "%d", stageNumber);
    numberLabel->setString(numberString);
    
    char file[50];
    sprintf(file, "stagefiles/stage%d.txt", stageNumber);
    
    char highscoreString[50];
    sprintf(highscoreString, "Highscore: %lld", HighscoreManager::getHighscore(file));
    highscoreLabel->setString(highscoreString);

    auto moveBy = MoveBy::create(0.2, Vec2(0, -1.0*Director::getInstance()->getVisibleSize().height*0.75));
    auto moveByEase = EaseIn::create(moveBy->clone(), 2.0);
    layerColor->runAction(moveByEase);
    
    auto fadeIn = FadeTo::create(0.2, 200);
    auto fadeInEase = EaseIn::create(fadeIn->clone(), 2.0);
    backgroundDarkSprite->runAction(fadeInEase);
}

void StageDetailLayer::dismiss(){
    
    if(!isShowing)
        return;
    
    auto moveBy = MoveBy::create(0.2, Vec2(0, 1.0*Director::getInstance()->getVisibleSize().height*0.75));
    auto moveByEase = EaseIn::create(moveBy->clone(), 2.0);
    layerColor->runAction(moveByEase);
    
    auto fadeOut = FadeTo::create(0.2, 0);
    auto fadeOutEase = EaseIn::create(fadeOut->clone(), 2.0);
    backgroundDarkSprite->runAction(fadeOutEase);
    
    isShowing = false;
}

bool StageDetailLayer::onTouchBegan(Touch *touch, Event *unused_event){
    
    cout<<"StageDetail onTouchBegan"<<endl<<endl<<endl;
    
    if(isShowing){
        this->dismiss();
        return true; //swallow because it was visible
    }
    
    return false; //don't swallow because it wasn't showing
}

void StageDetailLayer::onTouchMoved(Touch *touch, Event *unused_event){
    
}

void StageDetailLayer::onTouchEnded(Touch *touch, Event *unused_event){
    
}
