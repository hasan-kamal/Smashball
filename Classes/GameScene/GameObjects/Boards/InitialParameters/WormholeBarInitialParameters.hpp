//
//  WormholeBarInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 11/10/16.
//
//

#ifndef WormholeBarInitialParameters_hpp
#define WormholeBarInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class WormholeBarInitialParameters{
public:
    
    bool orientation; // 0 denotes left-oriented
    double heightHalf;
    double widthHalf;
    double sensorBodyWidthToTotalWidthRatio;
    double lightGlowWidth;
    double lightPaddingWidth;
    double heightTopSeparatorInWorld;
    Vec2 initialPosition;
    double density;
    double restitution;
    
    WormholeBarInitialParameters();
    WormholeBarInitialParameters(char s[]);
};


#endif /* WormholeBarInitialParameters_hpp */
