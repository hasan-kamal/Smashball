//
//  TriangularHingedObstructionInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#ifndef TriangularHingedObstructionInitialParameters_hpp
#define TriangularHingedObstructionInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class TriangularHingedObstructionInitialParameters{
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
    double motorSpeed;
    double maxMotorTorque;
    
    TriangularHingedObstructionInitialParameters();
    TriangularHingedObstructionInitialParameters(char s[]);
};

#endif /* TriangularHingedObstructionInitialParameters_hpp */
