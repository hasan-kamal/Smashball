//
//  ChapterPage.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#include "ChapterPage.hpp"
#include "../Colors.hpp"
#include "../GlobalConfigs.hpp"

bool ChapterPage::init(int pageNum, Vec2 pseudoOrg, int startNum, int stopNum){
    
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
    this->startNumberStage = startNum;
    this->stopNumberStage = stopNum;
    
    //create label
    char chapterString[50];
    sprintf(chapterString, "Chapter %d", pageNumber);
    auto label = Label::createWithTTF(chapterString, "fonts/Trirong-Light.ttf", 24);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float padding = visibleSize.height*5.0/100;
    label->setAnchorPoint(Vec2(0.5, 1.0));
    label->setPosition(Vec2(pseudoOrigin.x + visibleSize.width/2,
                            pseudoOrigin.y + visibleSize.height - padding));
    label->setTextColor(Color4B(Color4F(255-52, 255-73, 255-80, 1.0)));
    this->addChild(label, 1);
    
    //create selection nodes
    float radiusSelectionNode = (widthGridRatio*visibleSize.width - (GlobalConfigs::NUM_COLS_PER_CHAPTER-1)*padding)/(2*GlobalConfigs::NUM_COLS_PER_CHAPTER);
    Vec2 firstNodePosition(pseudoOrigin.x + (1-widthGridRatio)*visibleSize.width/2.0 + radiusSelectionNode, pseudoOrigin.y + visibleSize.height*60.0/100);
    float deltaX = padding + 2*radiusSelectionNode;
    float deltaY = -1.0*(padding + 2*radiusSelectionNode);
    for(int i = startNumberStage; i<=stopNumberStage; i++){
        Vec2 p(firstNodePosition.x + deltaX*( (i-startNumberStage+1-1)%GlobalConfigs::NUM_COLS_PER_CHAPTER ), firstNodePosition.y + deltaY*( (i-startNumberStage+1-1)/GlobalConfigs::NUM_COLS_PER_CHAPTER ));
        createSelectionNode(this, p, i, radiusSelectionNode, &Colors::silver, &Colors::clouds);
    }
    
    //stageDetailLayer
    this->stageDetailLayer = StageDetailLayer::create(pseudoOrigin);
    this->addChild(stageDetailLayer, 1);
    
    return true;
}

void ChapterPage::createSelectionNode(Layer *parentCocosLayer, Vec2 position, int snum, float radius, const Color4F *backgroundColor, const Color4F *textColor){
    
    //button
    buttons.push_back(cocos2d::ui::Button::create());
    buttons[snum-startNumberStage]->setTouchEnabled(true);
    buttons[snum-startNumberStage]->loadTextures("nut.png", "nut.png");
    buttons[snum-startNumberStage]->setColor(Color3B(*backgroundColor));
    buttons[snum-startNumberStage]->setTitleColor(Color3B(*textColor));
    buttons[snum-startNumberStage]->setAnchorPoint(Vec2(0.5, 0.5));
    buttons[snum-startNumberStage]->setScale(2*radius/buttons[snum-startNumberStage]->getContentSize().width);
    buttons[snum-startNumberStage]->setPosition(position);
    buttons[snum-startNumberStage]->setTag(snum);
    buttons[snum-startNumberStage]->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:{
                showDetailsOfStage(((cocos2d::ui::Button *)sender)->getTag());
                break;
            }
            default:
                break;
        }
    });
    parentCocosLayer->addChild(buttons[snum-startNumberStage]);
    
    //label
    char s[50];
    sprintf(s, "%d", snum);
    labels.push_back(Label::createWithTTF(s, "fonts/Roboto-Light.ttf", 20));
    labels[snum-startNumberStage]->setAnchorPoint(Vec2(0.5, 0.5));
    labels[snum-startNumberStage]->setPosition(position);
    labels[snum-startNumberStage]->setAlignment(TextHAlignment::CENTER);
    labels[snum-startNumberStage]->setTextColor(Color4B(*textColor));
    parentCocosLayer->addChild(labels[snum-startNumberStage]);
}

void ChapterPage::onExit(){
    Layer::onExit();
}

void ChapterPage::showDetailsOfStage(int stageNumber){
    this->stageDetailLayer->show(stageNumber);
}
