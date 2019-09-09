//
//  AbstractGameObject.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 05/07/16.
//
//

#ifndef AbstractGameObject_hpp
#define AbstractGameObject_hpp
#include "Box2D/Box2D.h"
#include "cocos2d.h"

class AbstractGameObject{
public:
    bool isAlreadyIntroduced;
    virtual void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) = 0;
    virtual ~AbstractGameObject();
    //virtual void gotCollided(b2Contact *contact) = 0;
};

#endif /* AbstractGameObject_hpp */
