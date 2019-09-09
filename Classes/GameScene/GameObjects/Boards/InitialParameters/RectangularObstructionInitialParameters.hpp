//
//  RectangularObstructionInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#ifndef RectangularObstructionInitialParameters_hpp
#define RectangularObstructionInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class RectangularObstructionInitialParameters{
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
    
    RectangularObstructionInitialParameters();
    RectangularObstructionInitialParameters(char s[]);
};


#endif /* RectangularObstructionInitialParameters_hpp */
