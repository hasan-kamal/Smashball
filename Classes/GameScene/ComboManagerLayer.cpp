//
//  ComboManagerLayer.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 31/07/16.
//
//

#include "ComboManagerLayer.hpp"
#include <stdio.h>

bool ComboManagerLayer::init()
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
    
    //combo label
    comboLabel = Label::createWithTTF("1x", "fonts/Roboto-Light.ttf", 20);
    comboLabel->setColor(Color3B(52, 73, 80));
    comboLabel->setAnchorPoint(Vec2(0.5, 1.0));
    comboLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height*3.0/4.0));
    this->addChild(comboLabel);

    comboLabel->setOpacity(0);
    
    double timeElapsedSinceLastPlusFifty;
    int numHitsInLoop;
    bool isLoopRunning = false; //very important variable
    
    void startLoop();
    void endLoop();
    
    void updateTimeElapsed(float dt);
    long long getComboMultiplier(long long deltaScore);
    
    return true;
}

void ComboManagerLayer::updateTimeElapsed(float dt){
    if(isLoopRunning)
        timeElapsedSinceLastPlusFifty+=dt; //increment time if loop is running already
    
    if(isLoopRunning && timeElapsedSinceLastPlusFifty>thresholdTime)
        this->endLoop(); //end the loop when it has taken too much time already
    
    if(isLoopRunning){
        //if loop is running, update the multiplier label on screen
        sprintf(comboLabelString, "%dX", 1 + numHitsInLoop/thresholdCount);
        comboLabel->setString(comboLabelString);
    }
}

long long ComboManagerLayer::getComboMultiplier(long long deltaScore){
    if(deltaScore>=50){
        //+50 hit
        if(isLoopRunning==false){
            //first +50 of the loop
            this->startLoop();
        }else{
            //must have happened within thresholdTime otherwise loop would have been ended by upDateTimeElapsed
            numHitsInLoop++;
            timeElapsedSinceLastPlusFifty = 0.0;
        }
    }else{
        //+10 hit
        if(isLoopRunning)
            this->endLoop();
    }
    
    return 1 + numHitsInLoop/thresholdCount;
}

void ComboManagerLayer::startLoop(){
    isLoopRunning = true;
    numHitsInLoop = 1;
    
    //fade in
    auto fadeInAction = FadeIn::create(0.2);
    comboLabel->runAction(fadeInAction);
    
    timeElapsedSinceLastPlusFifty = 0.0;
}

void ComboManagerLayer::endLoop(){
    isLoopRunning = false;
    
    //fade out
    auto fadeOutAction = FadeOut::create(0.2);
    comboLabel->runAction(fadeOutAction);
    
    numHitsInLoop = 0;
}
