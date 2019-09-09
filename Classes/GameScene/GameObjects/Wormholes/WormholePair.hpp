//
//  WormholePair.hpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 30/09/16.
//
//

#ifndef WormholePair_hpp
#define WormholePair_hpp

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../AbstractGameObject.hpp"
#include "WormholeBar.hpp"
#include "../Balls/AbstractBall.hpp"
#include "../Boards/InitialParameters/WormholePairInitialParameters.hpp"

using namespace cocos2d;

class WormholePair : public AbstractGameObject{
public:
    
    WormholeBar *bar1, *bar2;
    
    WormholePair(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, WormholePairInitialParameters *initialParameters);
    ~WormholePair();
    
    //implement interface
    void updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded) override;
    
    //methods that will be called by GameScene on this Wormhole object
    void updateStateForTeleportation(float dt, vector<AbstractBall*>& balls_in_game);
    void checkIfContactWithWormhole(b2Contact *contact, const vector<AbstractBall*>& balls_in_game);
    
    //const variable that determines fow how long the wormhole is disabled after each teleport
    const double minimumTimeBetweenConsecutiveTeleports = 1.0; //set it to 0.5 seconds

private:
    void scheduleTeleport(AbstractBall *ballToBeTeleported, bool bar1Collided); //helper function to be used inside this class only
    
    //variables that keep track of wormhole's state
    bool teleportEnabled = true;
    bool teleportScheduled = false;
    double timeElapsedSinceLastTeleport = 0.0;
    double delayForBallToReappear = 0.5; //set to 0.5 seconds for now
    AbstractBall *ballScheduledForTeleportation;
    b2Vec2 ballTeleportDestination;
    b2Vec2 ballVelocityPreSolve;
    
    //methods that run when wormhole is enabled/disabled
    //use these to perform visual changes
    void enableWormhole();
    void disableWormhole();
};

#endif /* WormholePair_hpp */
