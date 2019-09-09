//
//  WormholePairInitialParameters.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 11/10/16.
//
//

#ifndef WormholePairInitialParameters_hpp
#define WormholePairInitialParameters_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "WormholeBarInitialParameters.hpp"

using namespace std;
using namespace cocos2d;

class WormholePairInitialParameters{
public:
    
    WormholeBarInitialParameters *p1, *p2;
    
    WormholePairInitialParameters(WormholeBarInitialParameters *parameter1, WormholeBarInitialParameters *parameter2);
};

#endif /* WormholePairInitialParameters_hpp */
