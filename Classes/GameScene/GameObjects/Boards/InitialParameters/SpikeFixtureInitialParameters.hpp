//
//  SpikeFixtureInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 25/09/16.
//
//

#ifndef SpikeFixtureInitialParameters_hpp
#define SpikeFixtureInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class SpikeFixtureInitialParameters{
public:
    bool leftOriented;
    double baseWidth;
    double baseHeight;
    double distanceFromCenter;
    double restitution;
    double friction;
    
    SpikeFixtureInitialParameters();
    SpikeFixtureInitialParameters(char s[]);
};


#endif /* SpikeFixtureInitialParameters_hpp */
