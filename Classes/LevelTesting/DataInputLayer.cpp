//
//  DataInputLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/01/17.
//
//

#include "DataInputLayer.hpp"
#include "../Colors.hpp"
#include "LevelTestingDesigner.hpp"

USING_NS_CC;
#include <iostream>
using namespace std;

// on "init" you need to initialize your instance
bool DataInputLayer::init(LevelTestingDesigner *l)
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->level_testing_designer = l;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto winSize = Director::getInstance()->getWinSize();
    
    auto background = DrawNode::create();
    background->drawSolidRect(origin, Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height), Colors::cloudsFuzzy);
    this->addChild(background);
    
    //format_label
    format_label = Label::create();
    format_label->setString("format_label");
    format_label->setAnchorPoint(Vec2(0.5, 1.0));
    format_label->setPosition(Vec2(origin.x + visibleSize.width/2.0, origin.y + visibleSize.height));
    format_label->setColor(Color3B(Colors::peter_river));
    this->addChild(format_label);
    
    //example_label
    example_label = Label::create();
    example_label->setString("example_label");
    example_label->setAnchorPoint(Vec2(0.5, 1.0));
    example_label->setColor(Color3B(Colors::pomegranate));
    example_label->setPosition(format_label->getPosition()-Vec2(0, format_label->getContentSize().height));
    this->addChild(example_label);
    
    //regex_label
    regex_label = Label::create();
    regex_label->setString("regex_label");
    regex_label->setAnchorPoint(Vec2(0.5, 1.0));
    regex_label->setPosition(example_label->getPosition()-Vec2(0, example_label->getContentSize().height));
    regex_label->setColor(Color3B(Colors::orange));
    this->addChild(regex_label);
    
    //text_field
    text_field = cocos2d::ui::TextField::create();
    text_field->setString("text_field");
    text_field->setAnchorPoint(Vec2(0.5, 1.0));
    text_field->setPosition(regex_label->getPosition()-Vec2(0, regex_label->getContentSize().height));
    this->addChild(text_field);
    
    //button_done
    button_done = cocos2d::ui::Button::create();
    button_done->setTouchEnabled(true);
    button_done->loadTextures("tick.png", "tick.png");
    button_done->setAnchorPoint(Vec2(0.5, 1.0));
    button_done->setScale(visibleSize.height*10.0/100/button_done->getContentSize().height);
    button_done->setPosition(text_field->getPosition()-Vec2(0, text_field->getContentSize().height));
    button_done->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                this->done_clicked();
                break;
            case ui::Widget::TouchEventType::ENDED:{
                break;
            }
            default:
                break;
        }
    });
    this->addChild(button_done, 1);
    
    //touch listener
    auto touchEventListener = EventListenerTouchOneByOne::create();
    touchEventListener->onTouchBegan = CC_CALLBACK_2(DataInputLayer::onTouchBegan, this);
    touchEventListener->onTouchMoved = CC_CALLBACK_2(DataInputLayer::onTouchMoved, this);
    touchEventListener->onTouchEnded = CC_CALLBACK_2(DataInputLayer::onTouchEnded, this);
    touchEventListener->setSwallowTouches(true);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEventListener, this);
    
    is_showing = true;
    this->dismiss(); //initially not visible as is_showing = false;
    
    return true;
}

void DataInputLayer::done_clicked(){
    regex r(last_regex);
    if(regex_match(text_field->getString(), r)){
        level_testing_designer->add_object(text_field->getString());
        this->dismiss();
    }
}

void DataInputLayer::take_input(string format_for_user, string example, string reg_exp){
    if(is_showing)
        return;
    
    text_field->setString("enter here");
    format_label->setString("format:\n" + format_for_user);
    example_label->setString("example:\n" + example);
    regex_label->setString("regex:\n" + reg_exp);
    
    example_label->setPosition(format_label->getPosition()-Vec2(0, format_label->getContentSize().height));
    regex_label->setPosition(example_label->getPosition()-Vec2(0, example_label->getContentSize().height));
    text_field->setPosition(regex_label->getPosition()-Vec2(0, regex_label->getContentSize().height));
    button_done->setPosition(text_field->getPosition()-Vec2(0, text_field->getContentSize().height));
    last_regex = reg_exp;
    
    this->setVisible(true);
    is_showing = true;
}

void DataInputLayer::dismiss(){
    if(!is_showing)
        return;
    
    this->setVisible(false);
    is_showing = false;
}

bool DataInputLayer::onTouchBegan(Touch *touch, Event *unused_event){
    
    if(is_showing){
        this->dismiss();
        return true; //swallow because it was visible
    }
    
    return false; //don't swallow because it wasn't showing
}

void DataInputLayer::onTouchMoved(Touch *touch, Event *unused_event){
    
}

void DataInputLayer::onTouchEnded(Touch *touch, Event *unused_event){
    
}
