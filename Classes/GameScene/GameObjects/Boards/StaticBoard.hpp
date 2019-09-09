//
//  StaticBoard.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 15/07/16.
//
//

#ifndef StaticBoard_hpp
#define StaticBoard_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AbstractBoard.hpp"
#include "../Rods/MetalRod.hpp"
#include "InitialParameters/StaticBoardInitialParameters.hpp"
#include <vector>

using namespace cocos2d;
using namespace std;

class StaticBoard : public AbstractBoard{
public:
    //fixture properties and their values
    bool orientation; // 0 denotes left-oriented
    double heightHalf;
    double widthHalf;
    Vec2 initialPosition;
    double angleInclinationInitial;
    double bonusRadius;
    double boardDensity;
    double boardRestitution;
    double paddingGap;
    double amplitudeOscillationX;
    double frequencyOscillationX;
    double amplitudeOscillationY;
    double frequencyOscillationY;
    
    //score delta properties
    Label *scoreDeltaLabel;
    char scoreDeltaString[50];
    void showScoreUpdate(long long deltaScore, float worldToPixelScale, Vec2 offsetOriginToBeAdded);
    
    //rod properties
    MetalRod *metalRod;
    
    StaticBoard(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, float heightInWorld, Vec2 offsetOriginToBeAdded, StaticBoardInitialParameters *initialParameters);
    ~StaticBoard();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    long long boardCollidedReturnScoreUpdate(b2Contact *contact, float worldToPixelScale, Vec2 offsetOriginToBeAdded, const vector<AbstractBall*>& balls_in_game) override;
    
    //shadow properties
    Sprite *shadowSprite;
    float shadowRadius;
    float shadowLength = 0.05;
    Vec2 shadowScaleOriginal;
    Vec2 shadowScaleNew;
    
    double timeElapsed = 0;
};

#endif /* StaticBoard_hpp */
