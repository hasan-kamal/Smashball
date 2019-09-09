//
//  WormholePairInitialParameters.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 11/10/16.
//
//

#include "WormholePairInitialParameters.hpp"

WormholePairInitialParameters::WormholePairInitialParameters(WormholeBarInitialParameters *parameter1, WormholeBarInitialParameters *parameter2){
    this->p1 = parameter1;
    this->p2 = parameter2;
}
