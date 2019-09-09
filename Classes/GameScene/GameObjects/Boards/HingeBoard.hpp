//
//  HingeBoard.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 05/07/16.
//
//

#ifndef HingeBoard_hpp
#define HingeBoard_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AbstractBoard.hpp"
#include "../Rods/VirtualRod.hpp"
#include "InitialParameters/HingeBoardInitialParameters.hpp"

using namespace cocos2d;
using namespace std;

class HingeBoard : public AbstractBoard{
public:
    Sprite *spriteHinge;
    b2Body *bodyHinge;
    
    //initial fixture and configuration properties
    bool isOriented;
    bool orientation; //0-denotes left-oriented
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
    
    //joint properties
    b2RevoluteJoint *revoluteJoint;
    float maxMotorTorque;
    float motorSpeed;
    
    //hinge fixture properties
    float radiusHinge = 0.04;
    
    //VirtualRod
    VirtualRod *virtualRod;
    
    //score delta properties
    Label *scoreDeltaLabel;
    char scoreDeltaString[50];
    void showScoreUpdate(long long deltaScore, float worldToPixelScale, Vec2 offsetOriginToBeAdded);
    
    HingeBoard(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, HingeBoardInitialParameters *initialParameters);
    ~HingeBoard();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    long long boardCollidedReturnScoreUpdate(b2Contact *contact, float worldToPixelScale, Vec2 offsetOriginToBeAdded, const vector<AbstractBall*>& balls_in_game) override;
    
    //shadow properties
    Sprite *shadowSprite;
    float shadowLength = 0.05;
    double clip(double x);
    
    double timeElapsed = 0;
};


#endif /* HingeBoard_hpp */
