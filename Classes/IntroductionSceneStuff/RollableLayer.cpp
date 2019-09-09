//
//  RollableLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#include "RollableLayer.hpp"
#include "../GlobalConfigs.hpp"

bool RollableLayer::init(){
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //set configuration variables
    currentPageNumber = 0;
    string contentString = FileUtils::getInstance()->getStringFromFile("stagefiles/stage-all.txt");
    stringstream content(contentString);
    content>>num_stages; //sets number of stages
    maxPageNumber = (num_stages%GlobalConfigs::NUM_STAGES_PER_CHAPTER==0)?(num_stages/GlobalConfigs::NUM_STAGES_PER_CHAPTER):(num_stages/GlobalConfigs::NUM_STAGES_PER_CHAPTER + 1);

    //add classic page
    pages.push_back(ClassicPage::create(-1, Vec2(Director::getInstance()->getVisibleOrigin().x - Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleOrigin().y)));
    
    //add introduction page
    pages.push_back(IntroductionPage::create(0, Director::getInstance()->getVisibleOrigin()));
    
    //add chapter pages
    std::cout<<"max page number "<<maxPageNumber<<endl;
    for(int i=1; i<maxPageNumber; i++)
        pages.push_back(ChapterPage::create(i, Vec2(Director::getInstance()->getVisibleOrigin().x + i*Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleOrigin().y), GlobalConfigs::NUM_STAGES_PER_CHAPTER*(i-1)+1, GlobalConfigs::NUM_STAGES_PER_CHAPTER*i));
    pages.push_back(ChapterPage::create(maxPageNumber, Vec2(Director::getInstance()->getVisibleOrigin().x + maxPageNumber*Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleOrigin().y), num_stages-(num_stages%GlobalConfigs::NUM_STAGES_PER_CHAPTER-1), num_stages));
    
    for(auto page : pages)
        this->addChild(page);
    
    return true;
}

void RollableLayer::rollLeft(){
    if(currentPageNumber<=minPageNumber)
        return;
    
    auto moveBy = MoveBy::create(0.5, Vec2(Director::getInstance()->getVisibleSize().width, 0));
    
    auto moveEaseBy = EaseInOut::create(moveBy->clone(), 3.0);
    
    this->runAction(moveEaseBy);
    currentPageNumber--;
}

void RollableLayer::rollRight(){
    if(currentPageNumber>=maxPageNumber)
        return;
    
    auto moveBy = MoveBy::create(0.5, Vec2(-1*Director::getInstance()->getVisibleSize().width, 0));
    
    auto moveEaseBy = EaseInOut::create(moveBy->clone(), 3.0);
    
    this->runAction(moveEaseBy);
    currentPageNumber++;
}
