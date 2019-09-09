//
//  GamePauseLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 30/07/16.
//
//

#ifndef GamePauseLayer_hpp
#define GamePauseLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d;

class GameScene;

class GamePauseLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePauseLayer);
    
    LayerColor *layerColor;
    cocos2d::ui::Button *buttonResume;
    cocos2d::ui::Button *buttonQuit;
    
    GameScene *gameScene;
    void show();
    void dismiss();
};


#endif /* GamePauseLayer_hpp */
