//
//  VirtualRod.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 23/07/16.
//
//

#ifndef VirtualRod_hpp
#define VirtualRod_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"

using namespace cocos2d;

class VirtualRod : public AbstractGameObject{
public:
    Sprite *spriteHorizontal;
    Texture2D *texture;
    
    VirtualRod(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, b2Vec2 jointPosInWorld, Vec2 offsetOriginToBeAdded, bool orientationRight);
    ~VirtualRod();
    
    
    //visual properties
    float thickness = 0.04;
    float rightEndInWorld = 5.0;
    float opacity = 100; //out of 255
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
};

#endif /* VirtualRod_hpp */
