//
//  AbstractPowerup.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 02/08/16.
//
//

#ifndef AbstractPowerup_hpp
#define AbstractPowerup_hpp
#include "cocos2d.h"

class AbstractPowerup{
public:
    virtual void updateState(float dt, float worldToPixelScale) = 0;
    virtual ~AbstractPowerup();
    
    virtual void startPowerup() = 0;
};

#endif /* AbstractPowerup_hpp */
