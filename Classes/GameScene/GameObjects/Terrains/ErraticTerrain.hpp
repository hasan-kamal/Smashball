//
//  ErraticTerrain.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 15/07/16.
//
//

#ifndef ErraticTerrain_hpp
#define ErraticTerrain_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"

using namespace cocos2d;

class ErraticTerrain : public AbstractGameObject{
public:
    DrawNode *node;
    b2Body *body;
    
    //fixture properties and their values
    float friction = 0.5;
    float restitution = 0.3;
    
    ErraticTerrain(b2World *world, Layer *parentCocosLayer, float worldToPixelScale);
    ~ErraticTerrain();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    
    //helper function
    void assignValues(b2Vec2 *gameBounds, int numPoints);
};


#endif /* ErraticTerrain_hpp */
