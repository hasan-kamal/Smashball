//
//  Page.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#ifndef Page_hpp
#define Page_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include <iostream>
using namespace cocos2d;
using namespace std;

class Page : public cocos2d::Layer
{
public:
    
    int pageNumber;
    Vec2 pseudoOrigin;
};

#endif /* Page_hpp */
