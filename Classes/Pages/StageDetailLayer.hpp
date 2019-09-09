//
//  StageDetailLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 13/10/16.
//
//

#ifndef StageDetailLayer_hpp
#define StageDetailLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../HighscoreManager.hpp"
#include "../GameScene/GameScene.hpp"
#include "../GameScene/GameObjects/Boards/InitialParameters/GameSceneInitialParameters.hpp"
using namespace cocos2d;

class StageDetailLayer : public Layer
{
public:
    
    virtual bool init(Vec2 pseudoOrigin);
    
    // implement the "static create()" method manually
    //CREATE_FUNC(GameScene); not using this one because we want to pass the filename as well
    static StageDetailLayer* create(Vec2 pseudoOrigin)
    {
        StageDetailLayer *pRet = new(std::nothrow) StageDetailLayer();
        if (pRet && pRet->init(pseudoOrigin))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    
    int stageNumber;
    LayerColor *layerColor;
    cocos2d::ui::Button *buttonResume;
    Label *difficultyLabel, *numberLabel, *highscoreLabel;
    void startStage();
    
    bool isShowing = false;
    Sprite *backgroundDarkSprite;
    
    //touch event callbacks
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
    void show(int stNum);
    void dismiss();
};

#endif /* StageDetailLayer_hpp */
