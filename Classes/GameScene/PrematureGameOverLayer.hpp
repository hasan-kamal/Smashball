//
//  PrematureGameOverLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 13/08/16.
//
//

#ifndef PrematureGameOverLayer_hpp
#define PrematureGameOverLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d;

class GameScene;

class PrematureGameOverLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PrematureGameOverLayer);
    
    Label *scoreLabel;
    char scoreString[50];
    cocos2d::ui::Button *restartButton;
    
    GameScene *gameScene;
    
    void show(long long score);
    void dismiss();
};

#endif /* PrematureGameOverLayer_hpp */
