//
//  WormholePair.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 30/09/16.
//
//

#include "WormholePair.hpp"

#include <iostream>
using namespace std;

WormholePair::WormholePair(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, WormholePairInitialParameters *initialParameters){
    
    bar1 = new WormholeBar(world, parentCocosLayer, worldToPixelScale, offsetOriginToBeAdded, initialParameters->p1);
    bar2 = new WormholeBar(world, parentCocosLayer, worldToPixelScale, offsetOriginToBeAdded,initialParameters->p2);
    
}

WormholePair::~WormholePair(){
    delete bar1;
    delete bar2;
}

void WormholePair::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
}

//if any teleportation has been scheduled in the past, perform it here
//this is called by GameScene's update method
void WormholePair::updateStateForTeleportation(float dt, vector<AbstractBall*>& balls_in_game){
    
    //if teleport is disabled, keep track of time
    if(!teleportEnabled){
        timeElapsedSinceLastTeleport+=dt;
        if(timeElapsedSinceLastTeleport>minimumTimeBetweenConsecutiveTeleports)
            enableWormhole();
    }
    
    //see if a teleport has been scheduled already
    //if yes, perform
    if(teleportScheduled){
        ballScheduledForTeleportation->teleportToWithDelay(ballTeleportDestination, delayForBallToReappear, ballVelocityPreSolve);
        teleportScheduled = false;
    }
}

//this is called by GameScene whenever a contact happens, so if of interest, schedule teleportation here
//this is called by GameScene's BeginContact() callback, so can't teleport here itself - can only schedule it for next timestep
void WormholePair::checkIfContactWithWormhole(b2Contact *contact, const vector<AbstractBall*>& balls_in_game){
    
    if(!teleportEnabled)
        return; //no point in checking if teleport is disabled right now
    
    bool b1, b2, b3, b4, b5;
    
    //check if this wormhole has collided with something
    b1 = contact->GetFixtureA()->GetBody()==this->bar1->sensorBody;
    b2 = contact->GetFixtureA()->GetBody()==this->bar2->sensorBody;
    b3 = contact->GetFixtureB()->GetBody()==this->bar1->sensorBody;
    b4 = contact->GetFixtureB()->GetBody()==this->bar2->sensorBody;
    
    //make sure the other body is a ball which has collided with this wormhole
    b5 = false;
    for(int i=0; i<balls_in_game.size(); i++){
        if( (balls_in_game[i]==contact->GetFixtureA()->GetBody()->GetUserData()) || (balls_in_game[i]==contact->GetFixtureB()->GetBody()->GetUserData())){
            b5 = true;
            break;
        }
    }
    
    if(b5 && (b1||b2||b3||b4)){
        //now we know the contact has happened between this wormhole and a ball
        //so we will now try to schedule it
        //cout<<"HIT WORMHOLE"<<endl;
        AbstractBall *ballTouched = (AbstractBall *)((b1||b2)?contact->GetFixtureB()->GetBody()->GetUserData():contact->GetFixtureA()->GetBody()->GetUserData());
        ballVelocityPreSolve = ballTouched->ballBody->GetLinearVelocity();
        scheduleTeleport(ballTouched, b1||b3);
        contact->SetEnabled(false);
    }
}

//private helper function
void WormholePair::scheduleTeleport(AbstractBall *ballToBeTeleported, bool bar1Collided){
    disableWormhole();
    timeElapsedSinceLastTeleport = 0.0;
    
    //we're scheduling teleportation now
    teleportScheduled = true;
    this->ballScheduledForTeleportation = ballToBeTeleported;
    
    //calculate ballTeleportDestination vector that will be used in the next time step for teleporting the ball
    b2Vec2 alpha;
    if(bar1Collided){
        alpha = ballToBeTeleported->ballBody->GetPosition() - bar1->initialPosition;
        alpha.Set(alpha.x*-1, alpha.y);
        ballTeleportDestination = bar2->initialPosition + alpha;
    }else{
        alpha = ballToBeTeleported->ballBody->GetPosition() - bar2->initialPosition;
        alpha.Set(alpha.x*-1, alpha.y);
        ballTeleportDestination = bar1->initialPosition + alpha;
    }
    
}

void WormholePair::enableWormhole(){
    teleportEnabled = true;
    bar1->enable();
    bar2->enable();
}

void WormholePair::disableWormhole(){
    teleportEnabled = false;
    bar1->disable();
    bar2->disable();
}
