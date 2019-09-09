//
//  StaticBoardInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 25/09/16.
//
//

#ifndef StaticBoardInitialParameters_hpp
#define StaticBoardInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class StaticBoardInitialParameters{
public:
    bool orientation; // 0 denotes left-oriented
    double heightHalf;
    double widthHalf;
    Vec2 initialPosition;
    double angleInclinationInitial;
    double bonusRadius;
    double boardDensity;
    double boardRestitution;
    double paddingGap;
    double amplitudeOscillationX;
    double frequencyOscillationX;
    double amplitudeOscillationY;
    double frequencyOscillationY;
    
    StaticBoardInitialParameters();
    StaticBoardInitialParameters(char s[]);
};


#endif /* StaticBoardInitialParameters_hpp */
