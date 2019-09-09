//
//  Wormhole.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 26/09/16.
//
//

#ifndef Wormhole_hpp
#define Wormhole_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "../Balls/AbstractBall.hpp"

using namespace cocos2d;

class Wormhole : public AbstractGameObject{
public:
    
    Wormhole(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded);
    ~Wormhole();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    
    b2Vec2 pos1, pos2;
    b2Body *body1, *body2;
    double outerRadius, innerRadius;
    double initialScale;
    Sprite *sprite1, *sprite2;
    
    //fixture properties and their values
    //float radius = 0.12;
    float density = 150.0;
    float friction = 0.5;
    float restitution = 0.7;
    
    b2Vec2 getTeleportDestination(AbstractBall *ballTouched, b2Contact *contact);
    
    void fadeInNow();
    void fadeOutNow();
    
    void followBall(AbstractBall *ball);
};

#endif /* Wormhole_hpp */
