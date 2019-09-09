//
//  TriangularObstruction.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#ifndef TriangularObstruction_hpp
#define TriangularObstruction_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "../Boards/InitialParameters/TriangularObstructionInitialParameters.hpp"
#include "AbstractObstruction.hpp"

using namespace cocos2d;

class TriangularObstruction : public AbstractObstruction{
public:
    
    b2Body *triangularBody;
    Sprite *triangularSprite;
    
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
    
    TriangularObstruction(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, TriangularObstructionInitialParameters *initialParameters);
    ~TriangularObstruction();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    
    //shadow properties
    Sprite *shadowSprite;
    float shadowRadius;
    float shadowLength = 0.05;
    Vec2 shadowScaleOriginal;
    Vec2 shadowScaleNew;
    
    double timeElapsed = 0;
};


#endif /* TriangularObstruction_hpp */
