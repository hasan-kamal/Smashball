//
//  PowerupPopupSelectionLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 02/08/16.
//
//

#ifndef PowerupPopupSelectionLayer_hpp
#define PowerupPopupSelectionLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d;

class GameScene;

class PowerupPopupSelectionLayer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PowerupPopupSelectionLayer);
    
    DrawNode *background;
    
    GameScene *gameScene;
    void show();
    void dismiss();
};

#endif /* PowerupPopupSelectionLayer_hpp */
