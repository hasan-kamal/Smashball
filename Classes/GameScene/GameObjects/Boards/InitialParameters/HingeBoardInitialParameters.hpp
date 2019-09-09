//
//  HingeBoardInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 25/09/16.
//
//

#ifndef HingeBoardInitialParameters_hpp
#define HingeBoardInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class HingeBoardInitialParameters{
public:
    bool isOriented;
    bool orientation; //0-denotes left-oriented
    double heightHalf;
    double widthHalf;
    Vec2 initialPosition;
    double angleInclinationInitial;
    double bonusRadius;
    double boardDensity;
    double boardRestitution;
    double paddingGap;
    double motorSpeed;
    double maxMotorTorque;
    double amplitudeOscillationX;
    double frequencyOscillationX;
    double amplitudeOscillationY;
    double frequencyOscillationY;
    
    HingeBoardInitialParameters();
    HingeBoardInitialParameters(char s[]);
};


#endif /* HingeBoardInitialParameters_hpp */
