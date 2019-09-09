//
//  ChapterPage.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#ifndef ChapterPage_hpp
#define ChapterPage_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "Page.hpp"
#include "../HighscoreManager.hpp"
#include "../GameScene/GameObjects/Boards/InitialParameters/GameSceneInitialParameters.hpp"
#include "../GameScene/GameScene.hpp"
#include <iostream>
#include "StageDetailLayer.hpp"
#include <vector>
using namespace cocos2d;
using namespace std;

class ChapterPage : public Page
{
public:
    
    virtual bool init(int pageNumber, Vec2 pseudoOrigin, int startNum, int stopNum);
    virtual void onExit();
    
    // implement the "static create()" method manually
    //CREATE_FUNC(GameScene); not using this one because we want to pass the filename as well
    static ChapterPage* create(int pageNumber, Vec2 pseudoOrigin, int startNumberStage, int stopNumberStage)
    {
        ChapterPage *pRet = new(std::nothrow) ChapterPage();
        if (pRet && pRet->init(pageNumber, pseudoOrigin, startNumberStage, stopNumberStage))
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
    
    int startNumberStage;
    int stopNumberStage;
    
    float paddingRatio = 1/100.0; //1 percent of screen is the padding between consecutive nodes
    float widthGridRatio = 75/100.0; //90 percent of screen's width is taken up by grid
    
    StageDetailLayer *stageDetailLayer;
    
    void showDetailsOfStage(int stageNumber);
        
    //aggregations of selection nodes - START
    void createSelectionNode(Layer *parentCocosLayer, Vec2 position, int snum, float radius, const Color4F *backgroundColor, const Color4F *textColor);
    vector<ui::Button*> buttons;
    vector<Label*> labels;
    //aggregation of selection nodes - END
    
};


#endif /* ChapterPage_hpp */
