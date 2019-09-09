//
//  GameOverLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/07/16.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "../HighscoreManager.hpp"
using namespace cocos2d;
using namespace std;

class GameScene;

class GameOverLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverLayer);
    
    Label *scoreLabel;
    char scoreString[50];
    cocos2d::ui::Button *restartButton;
    
    Label *lastHighscoreLabel;
    char lastHighscoreString[50];
    
    cocos2d::ui::Button *buttonRestart;
    cocos2d::ui::Button *buttonQuit;
    
    GameScene *gameScene;
    
    void show(long long score, string stageDesc);
    void dismiss();
};

#endif /* GameOverLayer_hpp */
