//
//  SpikeFixture.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 05/08/16.
//
//

#ifndef SpikeFixture_hpp
#define SpikeFixture_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "../Boards/InitialParameters/SpikeFixtureInitialParameters.hpp"

using namespace cocos2d;

class SpikeFixture : public AbstractGameObject{
public:
    Sprite *spriteSpike;
    b2Body *parentBody;
    b2Fixture *spikeFixture;
    
    //initial configuration info to be saved
    bool leftOriented;
    double baseWidth;
    double baseHeight;
    double distanceFromCenter;
    double restitution;
    double friction;
    
    SpikeFixture(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, b2Body *parentBody, float offsetWidthHalf, float offsetHeightHalf, SpikeFixtureInitialParameters *initialParameters);
    ~SpikeFixture();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
};


#endif /* SpikeFixture_hpp */
