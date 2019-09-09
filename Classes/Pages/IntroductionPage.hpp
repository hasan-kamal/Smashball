//
//  IntroductionPage.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#ifndef IntroductionPage_hpp
#define IntroductionPage_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "Page.hpp"
#include "../HighscoreManager.hpp"
#include "../GameScene/GameScene.hpp"
#include <iostream>
using namespace cocos2d;
using namespace std;

class IntroductionPage : public Page
{
public:
    
    virtual bool init(int pageNumber, Vec2 pseudoOrigin);
    
    // implement the "static create()" method manually
    //CREATE_FUNC(GameScene); not using this one because we want to pass the filename as well
    static IntroductionPage* create(int pageNumber, Vec2 pseudoOrigin)
    {
        IntroductionPage *pRet = new(std::nothrow) IntroductionPage();
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

#endif /* IntroductionPage_hpp */
