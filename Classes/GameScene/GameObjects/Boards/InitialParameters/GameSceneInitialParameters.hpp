//
//  GameSceneInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 07/10/16.
//
//

#ifndef GameSceneInitialParameters_hpp
#define GameSceneInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class GameSceneInitialParameters{
public:
    double gravityX;
    double gravityY;
    bool hasLeftWall;
    bool hasRightWall;
    bool hasUpWall;
    bool hasBottomWall;
    
    GameSceneInitialParameters();
    GameSceneInitialParameters(string s);
};

#endif /* GameSceneInitialParameters_hpp */
