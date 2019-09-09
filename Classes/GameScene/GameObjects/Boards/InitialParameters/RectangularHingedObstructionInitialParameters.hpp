//
//  RectangularHingedObstructionInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#ifndef RectangularHingedObstructionInitialParameters_hpp
#define RectangularHingedObstructionInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class RectangularHingedObstructionInitialParameters{
public:
    double heightHalf;
    double widthHalf;
    Vec2 initialPosition;
    double angleInclinationInitial;
    double boardDensity;
    double boardRestitution;
    double amplitudeOscillationX;
    double frequencyOscillationX;
    double amplitudeOscillationY;
    double frequencyOscillationY;
    float maxMotorTorque;
    float motorSpeed;
    
    RectangularHingedObstructionInitialParameters();
    RectangularHingedObstructionInitialParameters(char s[]);
};

#endif /* RectangularHingedObstructionInitialParameters_hpp */
