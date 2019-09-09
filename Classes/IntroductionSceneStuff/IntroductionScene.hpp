//
//  IntroductionScene.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 03/07/16.
//
//

#ifndef IntroductionScene_hpp
#define IntroductionScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BallMovementLayer.hpp"
#include "RollableLayer.hpp"
#include "../FileOperation.h"
using namespace cocos2d;

class IntroductionScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(IntroductionScene);
    
    cocos2d::ui::Button *buttonRollRight;
    cocos2d::ui::Button *buttonRollLeft;
    cocos2d::ui::Button *buttonEdit;
    cocos2d::ui::Button *buttonPlay;
    
    BallMovementLayer *ballMovementLayer;
    RollableLayer *rollableLayer;
};

#endif /* IntroductionScene_hpp */
