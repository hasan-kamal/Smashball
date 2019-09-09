//
//  IntroductionPage.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#include "IntroductionPage.hpp"
#include "../GlobalConfigs.hpp"
#include "../Colors.hpp"

bool IntroductionPage::init(int pageNum, Vec2 pseudoOrg){
    
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
    
    //label
    auto label = Label::createWithTTF("Smashball", "fonts/Trirong-Light.ttf", 35);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    label->setAnchorPoint(Vec2(0.5, 0.0));
    label->setPosition(Vec2(pseudoOrigin.x + visibleSize.width/2,
                            pseudoOrigin.y + visibleSize.height/2));
    label->setTextColor(Color4B(Color4F(255-52, 255-73, 255-80, 1.0)));
    label->setOpacity(0);
    auto fadeIn = FadeIn::create(1.0);
    label->runAction(fadeIn);
    this->addChild(label, 1);
    
    //label version
    auto label_version = Label::createWithTTF(GlobalConfigs::APP_VERSION, "fonts/Trirong-Light.ttf", 10);
    label_version->setAnchorPoint(Vec2(0.5, 1.0));
    label_version->setPosition(label->getPosition());
    label_version->setTextColor(Color4B(Colors::silver));
    this->addChild(label_version, 1);
    
    return true;
}
