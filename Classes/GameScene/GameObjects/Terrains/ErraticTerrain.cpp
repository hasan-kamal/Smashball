//
//  ErraticTerrain.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 15/07/16.
//
//

#include "ErraticTerrain.hpp"

ErraticTerrain::ErraticTerrain(b2World *world, Layer *parentCocosLayer, float worldToPixelScale){
    const int numPoints = 11;
    b2Vec2 gameBounds[numPoints];
    assignValues(gameBounds, numPoints);
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    int i;
    
    //corresponding world coordinate vector
    Vec2 inWorld[numPoints];
    for(i = 0; i<numPoints; i++)
        inWorld[i].set(origin.x + gameBounds[i].x*worldToPixelScale, origin.y + gameBounds[i].y*worldToPixelScale);
    
    b2ChainShape chainShapeBound;
    chainShapeBound.CreateLoop(gameBounds, numPoints);
    
    b2FixtureDef boundFixture;
    boundFixture.shape = &chainShapeBound;
    boundFixture.friction = this->friction;
    boundFixture.restitution = this->restitution;
    
    b2BodyDef boundBodyDef;
    boundBodyDef.type = b2_staticBody;
    boundBodyDef.userData = this;
    boundBodyDef.position.Set(0.0, 0.0);
    
    this->body = world->CreateBody(&boundBodyDef);
    this->body->CreateFixture(&boundFixture);

    node = DrawNode::create();
    auto peterRiver = Color4F(255-52, 255-152, 255-208, 1.0);
    auto belizeHole = Color4F(255-41, 255-128, 255-176, 1.0);
    for(i=1; i<numPoints; i++){
        //node->drawLine(inWorld[i-1], inWorld[i], Color4F::BLACK);
        Vec2 x[5];
        x[0].set(inWorld[i-1].x, origin.y);
        x[1].set(inWorld[i-1].x, inWorld[i-1].y);
        x[2].set(inWorld[i].x, inWorld[i].y);
        x[3].set(inWorld[i].x, origin.y);
        node->drawSolidPoly(x, 5, belizeHole);
    }
    parentCocosLayer->addChild(node, 1);
}

//actually sets the values for terrain vertices in world coordinates
void ErraticTerrain::assignValues(b2Vec2 *gameBounds, int numPoints){
    int i;
    float xDistanceBetweenConsecutivePoints = numPoints>1?5.0/(numPoints-1):5.0;
    
    //first point is origin
    gameBounds[0].Set(0.0, 0.0);
    
    float temp1 = 0.05;
    float temp2 = 0.15;
    bool toggle = true;
    for(i=1; i<(numPoints-1); i++){
        gameBounds[i].Set(gameBounds[i-1].x + xDistanceBetweenConsecutivePoints, toggle?temp2:temp1);
        toggle = !toggle;
    }
    
    //last point is the bottom-right point
    gameBounds[numPoints-1].Set(5.0, 0.0);
}

//implement interface
void ErraticTerrain::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
}

ErraticTerrain::~ErraticTerrain(){
    
}
