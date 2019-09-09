//
//  SpikyBoardInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 25/09/16.
//
//

#ifndef SpikyBoardInitialParameters_hpp
#define SpikyBoardInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SpikeFixtureInitialParameters.hpp"
#include <vector>

using namespace std;
using namespace cocos2d;

class SpikyBoardInitialParameters{
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

    vector<SpikeFixtureInitialParameters*> params_for_spikes;
    
    SpikyBoardInitialParameters();
    ~SpikyBoardInitialParameters();
    SpikyBoardInitialParameters(char s[], const vector<SpikeFixtureInitialParameters*>& spikeFixtureP);
};

#endif /* SpikyBoardInitialParameters_hpp */
