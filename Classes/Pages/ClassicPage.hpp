//
//  ClassicPage.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#ifndef ClassicPage_hpp
#define ClassicPage_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "Page.hpp"
#include "../HighscoreManager.hpp"
#include "../GameScene/GameObjects/Boards/InitialParameters/GameSceneInitialParameters.hpp"
#include "../GameScene/GameScene.hpp"
#include <iostream>
using namespace cocos2d;
using namespace std;

class ClassicPage : public Page
{
public:
    
    Label *label;
    cocos2d::ui::Button *buttonClassic;
    
    virtual bool init(int pageNumber, Vec2 pseudoOrigin);
    
    // implement the "static create()" method manually
    //CREATE_FUNC(IntroductionPage);
    // implement the "static create()" method manually
    //CREATE_FUNC(GameScene); not using this one because we want to pass the filename as well
    static ClassicPage* create(int pageNumber, Vec2 pseudoOrigin)
    {
        ClassicPage *pRet = new(std::nothrow) ClassicPage();
        if (pRet && pRet->init(pageNumber, pseudoOrigin))
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
};


#endif /* ClassicPage_hpp */
