//
//  IntroductionScene.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 03/07/16.
//
//

#include "IntroductionScene.hpp"
#include "../GameScene/GameScene.hpp"
#include "../Colors.hpp"
#include "../LevelTesting/LevelTestingDesigner.hpp"
#include "../GlobalConfigs.hpp"

USING_NS_CC;
#include <iostream>
using namespace std;

Scene* IntroductionScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IntroductionScene::create();
    //Hasan:: this create method in itself invokes the init method defined below
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroductionScene::init()
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
    
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    float closeItemPadding = 0.05;
    auto closeItem = MenuItemImage::create(
                                           "close_thin.png",
                                           "close_thin.png",
                                           CC_CALLBACK_1(IntroductionScene::menuCloseCallback, this));
    
    closeItem->setAnchorPoint(Vec2(1.0, 0.0));
    float x = 8.0/100*visibleSize.height/closeItem->getContentSize().height;
    closeItem->setScale(x, x/1.1);
    closeItem->setPosition(Vec2(origin.x + visibleSize.width -closeItemPadding*visibleSize.width/5.0 , origin.y +closeItemPadding*visibleSize.width/5.0));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
        
    auto background = DrawNode::create();
    background->drawSolidRect(origin, Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height), Colors::clouds);
    this->addChild(background);
    
    //buttonRollLeft
    buttonRollLeft = cocos2d::ui::Button::create();
    buttonRollLeft->setTouchEnabled(true);
    buttonRollLeft->loadTextures("left_angle.png", "left_angle.png");
    buttonRollLeft->setAnchorPoint(Vec2(0.5, 0.5));
    buttonRollLeft->setScale(visibleSize.height*8.0/100/buttonRollLeft->getContentSize().height);
    buttonRollLeft->setPosition(Vec2(origin.x + visibleSize.width*10.0/100.0, origin.y + visibleSize.height*50.0/100.0));
    buttonRollLeft->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                rollableLayer->rollLeft();
                break;
            }
            default:
                break;
        }
    });
    this->addChild(buttonRollLeft);
    
    //buttonRollRight
    buttonRollRight = cocos2d::ui::Button::create();
    buttonRollRight->setTouchEnabled(true);
    buttonRollRight->loadTextures("right_angle.png", "right_angle.png");
    buttonRollRight->setAnchorPoint(Vec2(0.5, 0.5));
    buttonRollRight->setScale(visibleSize.height*10.0/100/buttonRollRight->getContentSize().height);
    buttonRollRight->setPosition(Vec2(origin.x + visibleSize.width*92.0/100.0, origin.y + visibleSize.height*50.0/100.0));
    buttonRollRight->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                rollableLayer->rollRight();
                break;
            }
            default:
                break;
        }
    });
    this->addChild(buttonRollRight);
    
    //buttonEdit
    buttonEdit = cocos2d::ui::Button::create();
    buttonEdit->setTouchEnabled(true);
    buttonEdit->loadTextures("pen_icon.png", "pen_icon.png");
    buttonEdit->setAnchorPoint(Vec2(0.0, 0.0));
    buttonEdit->setScale(visibleSize.height*6.0/100/buttonEdit->getContentSize().height);
    buttonEdit->setPosition(origin + closeItemPadding*visibleSize.width/5.0*Vec2(1.0, 1.0));
    buttonEdit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                auto level_testing_scene = LevelTestingDesigner::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(1.0, level_testing_scene, Color3B(Color4F(255-236, 255-240, 255-240, 1.0))));
                break;
            }
            default:
                break;
        }
    });
    this->addChild(buttonEdit);
    
    //buttonPlay
    buttonPlay = cocos2d::ui::Button::create();
    buttonPlay->setTouchEnabled(true);
    buttonPlay->loadTextures("resume.png", "resume.png");
    buttonPlay->setAnchorPoint(Vec2(0.0, 0.0));
    buttonPlay->setScale(visibleSize.height*8.0/100/buttonPlay->getContentSize().height);
    buttonPlay->setPosition(buttonEdit->getPosition() + Vec2(buttonEdit->getContentSize().width*buttonEdit->getScale(), 0) - Vec2(0, visibleSize.height*1.0/100));
    buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                
                GameSceneInitialParameters g;
                auto gameScene = GameScene::createScene(FileOperation::readFile(GlobalConfigs::CUSTOM_STAGE_FILENAME), GlobalConfigs::CUSTOM_STAGE_FILENAME, &g);
                Director::getInstance()->replaceScene(TransitionFade::create(1.0, gameScene, Color3B(Color4F(255-236, 255-240, 255-240, 1.0))));
                
                break;
            }
            default:
                break;
        }
    });
    this->addChild(buttonPlay);
    
    //ball movement layer
    ballMovementLayer = BallMovementLayer::create();
    this->addChild(ballMovementLayer);
    
    //rollable layer
    rollableLayer = RollableLayer::create();
    this->addChild(rollableLayer);
    
    
    return true;
}

void IntroductionScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
