//
//  RollableLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#ifndef RollableLayer_hpp
#define RollableLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "../Pages/Page.hpp"
#include "../Pages/IntroductionPage.hpp"
#include "../Pages/ChapterPage.hpp"
#include "../Pages/ClassicPage.hpp"
#include <iostream>
#include <vector>
using namespace cocos2d;
using namespace std;

class IntroductionScene;
class RollableLayer : public cocos2d::Layer
{
public:
    
    vector<Page*> pages;
    int currentPageNumber;
    int minPageNumber = -1;
    int maxPageNumber;
    int num_stages;
    
    void rollLeft();
    void rollRight();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(RollableLayer);
};


#endif /* RollableLayer_hpp */
