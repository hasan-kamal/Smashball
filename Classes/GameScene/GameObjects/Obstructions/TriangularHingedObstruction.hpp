//
//  TriangularHingedObstruction.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#ifndef TriangularHingedObstruction_hpp
#define TriangularHingedObstruction_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "../Boards/InitialParameters/TriangularHingedObstructionInitialParameters.hpp"
#include "AbstractObstruction.hpp"

using namespace cocos2d;

class TriangularHingedObstruction : public AbstractObstruction{
public:
    
    b2Body *triangularBody;
    Sprite *triangularSprite;
    
    Sprite *spriteHinge;
    b2Body *bodyHinge;
    
    //for being able to access vertices of triangles to create proper shadow
    b2Fixture *triangularFixture;
    
    //hinge fixture properties
    float radiusHinge = 0.04;
    
    //fixture properties and their values
    double baseWidth;
    double height;
    Vec2 initialPosition;
    double angleInclinationInitial;
    double density;
    double restitution;
    double amplitudeOscillationX;
    double frequencyOscillationX;
    double amplitudeOscillationY;
    double frequencyOscillationY;
    
    //joint properties
    b2RevoluteJoint *revoluteJoint;
    float maxMotorTorque;
    float motorSpeed;
    
    TriangularHingedObstruction(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, TriangularHingedObstructionInitialParameters *initialParameters);
    ~TriangularHingedObstruction();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    
    //shadow properties
    Sprite *shadowSprite;
    float shadowRadius;
    float shadowLength = 0.05;
    Vec2 shadowScaleOriginal;
    Vec2 shadowScaleNew;
    
    double timeElapsed = 0;
    double clip(double x);
    double max(double x, double y);
    double min(double x, double y);
};


#endif /* TriangularHingedObstruction_hpp */
