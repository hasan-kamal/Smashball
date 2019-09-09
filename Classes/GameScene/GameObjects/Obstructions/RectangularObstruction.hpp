//
//  RectangularObstruction.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#ifndef RectangularObstruction_hpp
#define RectangularObstruction_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "../Boards/InitialParameters/RectangularObstructionInitialParameters.hpp"
#include "AbstractObstruction.hpp"

using namespace cocos2d;

class RectangularObstruction : public AbstractObstruction{
public:
    
    b2Body *rectangularBody;
    Sprite *rectangularSprite;
    
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
    
    RectangularObstruction(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, RectangularObstructionInitialParameters *initialParameters);
    ~RectangularObstruction();
    
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


#endif /* RectangularObstruction_hpp */
