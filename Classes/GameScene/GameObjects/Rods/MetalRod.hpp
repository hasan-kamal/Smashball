//
//  MetalRod.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 15/07/16.
//
//

#ifndef MetalRod_hpp
#define MetalRod_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"

using namespace cocos2d;

class MetalRod : public AbstractGameObject{
public:
    Sprite *spriteHorizontal;
    Sprite *spriteVertical;
    b2Body *bodyHorizontal;
    b2Body *bodyVertical;
    
    MetalRod(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, b2Vec2 jointPosInWorld, float heightCeilingInWorld, Vec2 offsetOriginToBeAdded, bool orientationLeft, float extraHeightForOscillationAdjustment);
    ~MetalRod();
    
    //fixture properties
    float restitution = 0.5;
    float friction = 0.5;
    
    //visual properties
    float thickness = 0.04;
    float horizontalLength = 0.5;
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
};

#endif /* MetalRod_hpp */
