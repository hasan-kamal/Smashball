//
//  RectangularHingedObstruction.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#ifndef RectangularHingedObstruction_hpp
#define RectangularHingedObstruction_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "../Boards/InitialParameters/RectangularHingedObstructionInitialParameters.hpp"
#include "AbstractObstruction.hpp"

using namespace cocos2d;

class RectangularHingedObstruction : public AbstractObstruction{
public:
    
    b2Body *rectangularBody;
    Sprite *rectangularSprite;
    
    Sprite *spriteHinge;
    b2Body *bodyHinge;
    
    //joint properties
    b2RevoluteJoint *revoluteJoint;
    float maxMotorTorque;
    float motorSpeed;
    
    //hinge fixture properties
    float radiusHinge = 0.04;
    
    //fixture properties and their values
    double heightHalf;
    double widthHalf;
    Vec2 initialPosition;
    double angleInclinationInitial;
    double boardDensity;
    double boardRestitution;
    double amplitudeOscillationX;
    double frequencyOscillationX;
    double amplitudeOscillationY;
    double frequencyOscillationY;
    
    RectangularHingedObstruction(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, RectangularHingedObstructionInitialParameters *initialParameters);
    ~RectangularHingedObstruction();
    
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
};


#endif /* RectangularHingedObstruction_hpp */
