//
//  SpikyBoard.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 05/08/16.
//
//

#ifndef SpikyBoard_hpp
#define SpikyBoard_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "AbstractBoard.hpp"
#include "../Rods/VirtualRod.hpp"
#include "../Spikes/SpikeFixture.hpp"
#include "InitialParameters/SpikyBoardInitialParameters.hpp"
#include "InitialParameters/SpikeFixtureInitialParameters.hpp"
#include <vector>

using namespace cocos2d;
using namespace std;

class GameScene;

class SpikyBoard : public AbstractBoard{
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
    
    SpikyBoard(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, GameScene *gameScene, SpikyBoardInitialParameters *initialParameters);
    ~SpikyBoard();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    long long boardCollidedReturnScoreUpdate(b2Contact *contact, float worldToPixelScale, Vec2 offsetOriginToBeAdded, const vector<AbstractBall*>& balls_in_game) override;
    
    
    //shadow properties
    Sprite *shadowSprite;
    float shadowLength = 0.05;
    double clip(double x);
    
    //Spikes
    vector<SpikeFixture*> spikes;
    
    //GameScene for ball-destroyed callback
    GameScene *gameScene;
    double timeElapsed = 0;
};


#endif /* SpikyBoard_hpp */
