//
//  TriangularObstructionInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#ifndef TriangularObstructionInitialParameters_hpp
#define TriangularObstructionInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class TriangularObstructionInitialParameters{
public:
    double baseWidth;
    double height;
    Vec2 initialPosition;
    double angleInclinationInitial;
    double density;
    double restitution;
    double amplitudeOscillationX;
    double frequencyOscillationX;
    double amplitudeOscillationY;
    double frequencyOscillationY;
    
    TriangularObstructionInitialParameters();
    TriangularObstructionInitialParameters(char s[]);
};


#endif /* TriangularObstructionInitialParameters_hpp */
