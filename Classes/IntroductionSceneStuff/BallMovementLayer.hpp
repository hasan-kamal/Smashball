//
//  BallMovementLayer.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 12/10/16.
//
//

#ifndef BallMovementLayer_hpp
#define BallMovementLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Box2D/Box2D.h"
#include "../GameScene/GameObjects/Balls/AbstractBall.hpp"
#include "../GameScene/GameObjects/Balls/TennisBall.hpp"
#include <iostream>
using namespace cocos2d;
using namespace std;

class BallMovementLayer : public cocos2d::Layer
{
public:
    
    b2World *world;
    b2Body *edgeBody;
    AbstractBall *ball;
    
    //scaling ratio
    float worldToPixelScale;
    
    //Offset vector to be added to origin
    Vec2 offsetOriginToBeAdded;
    float widthWorld = 5.0;
    float heightWorld = 2.6;
    
    virtual bool init();
    virtual void onExit();
    void update(float dt);
    
    double initialDelayTimeForBall = 1.5;
    double timeElapsed = 0;
    
    // implement the "static create()" method manually
    CREATE_FUNC(BallMovementLayer);
};

#endif /* BallMovementLayer_hpp */
