//
//  Vortex.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 29/09/16.
//
//

#ifndef Vortex_hpp
#define Vortex_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "../Balls/AbstractBall.hpp"

using namespace cocos2d;

class Vortex : public AbstractGameObject{
public:
    
    double radius;
    Sprite *sprite;
    b2Vec2 vortexPosition;
    double sensorBodyRadius;
    b2Body *sensorBody;
    float density = 150.0;
    float friction = 0.5;
    float restitution = 0.7;
    double safeRadius; //force will grow only uptill this radius
    
    Vortex(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded);
    ~Vortex();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    
    void vortexApplyForcesOnBalls(AbstractBall *balls[], int numBalls);
};

#endif /* Vortex_hpp */
