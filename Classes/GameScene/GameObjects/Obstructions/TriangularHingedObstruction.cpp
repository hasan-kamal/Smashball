//
//  TriangularHingedObstruction.cpp
//  SmashballBox2dPreBeta
//
//  Created by Hasan Kamal on 10/10/16.
//
//

#include "TriangularHingedObstruction.hpp"

TriangularHingedObstruction::TriangularHingedObstruction(b2World *world, Layer *parentCocosLayer, float worldToPixelScale, Vec2 offsetOriginToBeAdded, TriangularHingedObstructionInitialParameters *initialParameters){
    
    //save and copy configuration info from initalParameters object first
    this->baseWidth = initialParameters->baseWidth;
    this->height = initialParameters->height;
    this->initialPosition = initialParameters->initialPosition;
    this->angleInclinationInitial = initialParameters->angleInclinationInitial;
    this->density = initialParameters->density;
    this->restitution = initialParameters->restitution;
    this->amplitudeOscillationX = initialParameters->amplitudeOscillationX;
    this->frequencyOscillationX = initialParameters->frequencyOscillationX;
    this->amplitudeOscillationY = initialParameters->amplitudeOscillationY;
    this->frequencyOscillationY = initialParameters->frequencyOscillationY;
    this->maxMotorTorque = initialParameters->maxMotorTorque;
    this->motorSpeed = initialParameters->motorSpeed;
    
    //hinge physics initialization
    b2CircleShape hingeShape;
    hingeShape.m_radius = this->radiusHinge;
    
    b2FixtureDef hingeFixture;
    hingeFixture.shape = &hingeShape;
    
    b2BodyDef hingeBodyDef;
    hingeBodyDef.type = b2_kinematicBody;
    //hingeBodyDef.userData = this;
    //we can avoid unnecessary update calls by not setting hinge's userData
    //because board's update method also updates hinge anyways
    //because world's update method would update a body's position only if its userdata is not null
    hingeBodyDef.position.Set(this->initialPosition.x, this->initialPosition.y);
    
    bodyHinge = world->CreateBody(&hingeBodyDef);
    bodyHinge->CreateFixture(&hingeFixture);
    
    //triangular body initialization
    b2Vec2 vertices[3];
    vertices[0].Set(0.0 - baseWidth/2, 0.0 - height/2);
    vertices[1].Set(0.0 + baseWidth/2, 0.0 - height/2);
    vertices[2].Set(0.0, 0.0 + height/2);
    b2PolygonShape triangularShape;
    triangularShape.Set(vertices, 3);
    
    b2FixtureDef triangleFixtureDef;
    triangleFixtureDef.shape = &triangularShape;
    triangleFixtureDef.density = this->density;
    triangleFixtureDef.restitution = this->restitution;
    
    b2BodyDef triangleBodyDef;
    triangleBodyDef.type = b2_dynamicBody;
    triangleBodyDef.userData = this;
    triangleBodyDef.position.Set(initialPosition.x, initialPosition.y);
    
    triangularBody = world->CreateBody(&triangleBodyDef);
    this->triangularFixture = triangularBody->CreateFixture(&triangleFixtureDef);
    triangularBody->SetTransform(triangularBody->GetPosition(), this->angleInclinationInitial);
    triangularBody->SetLinearVelocity(b2Vec2(0, 0));
    
    //revolute joint
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = this->bodyHinge;
    jointDef.bodyB = this->triangularBody;
    jointDef.collideConnected = false;
    jointDef.localAnchorA.Set(this->bodyHinge->GetLocalCenter().x, this->bodyHinge->GetLocalCenter().y);
    jointDef.localAnchorB.Set(this->triangularBody->GetLocalCenter().x, this->triangularBody->GetLocalCenter().y);
    jointDef.enableMotor = true;
    jointDef.maxMotorTorque = this->maxMotorTorque;
    jointDef.motorSpeed = this->motorSpeed;
    revoluteJoint = (b2RevoluteJoint *)world->CreateJoint(&jointDef);

    //hinge sprite initialization
    this->spriteHinge = Sprite::create("nut.png");
    this->spriteHinge->setScale(2*this->radiusHinge/1.33*worldToPixelScale/this->spriteHinge->getContentSize().width);
    parentCocosLayer->addChild(this->spriteHinge, 2);
    
    //sprite initialization
    this->triangularSprite = Sprite::create("triangle_obstruction.png");
    this->triangularSprite->setScale(this->baseWidth*worldToPixelScale/this->triangularSprite->getContentSize().width, this->height*worldToPixelScale/this->triangularSprite->getContentSize().height);
    this->triangularSprite->setAnchorPoint(Vec2(0.5, 0.5));
    
    parentCocosLayer->addChild(this->triangularSprite, 1);
    
    //shadow initialization
    this->shadowSprite = Sprite::create("shadow.png");
    this->shadowSprite->setAnchorPoint(Vec2(0.0, 1.0));
    parentCocosLayer->addChild(this->shadowSprite);
}

TriangularHingedObstruction::~TriangularHingedObstruction(){
    
}

void TriangularHingedObstruction::updateState(float dt, float worldToPixelScale, cocos2d::Vec2 offsetOriginToBeAdded){
    
    this->triangularBody->SetLinearVelocity(b2Vec2(0, 0));
    
    this->triangularSprite->setPosition(Point(this->triangularBody->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->triangularBody->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->triangularSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->triangularBody->GetAngle()));
    
    //update hinge
    this->spriteHinge->setPosition(Point(this->bodyHinge->GetPosition().x * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, this->bodyHinge->GetPosition().y*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    this->spriteHinge->setRotation(-1 * CC_RADIANS_TO_DEGREES(this->bodyHinge->GetAngle()));
    
    //shadow
    auto shape = (b2PolygonShape *)this->triangularFixture->GetShape();
    b2Vec2 v1 = this->triangularBody->GetWorldPoint(shape->GetVertex(0));
    b2Vec2 v2 = this->triangularBody->GetWorldPoint(shape->GetVertex(1));
    b2Vec2 v3 = this->triangularBody->GetWorldPoint(shape->GetVertex(2));
    
    shadowRadius = max(max(v1.x, v2.x), v3.x) - min(min(v1.x, v2.x), v3.x);
    shadowRadius = shadowRadius/2.0*1.4;
    
    this->shadowSprite->setPosition(Point(min(min(v1.x, v2.x), v3.x) * worldToPixelScale + Director::getInstance()->getVisibleOrigin().x + offsetOriginToBeAdded.x, 0.03*worldToPixelScale + Director::getInstance()->getVisibleOrigin().y + offsetOriginToBeAdded.y));
    
    this->shadowSprite->setScale(2*this->shadowRadius*worldToPixelScale/this->shadowSprite->getContentSize().width, this->shadowLength*worldToPixelScale/this->shadowSprite->getContentSize().height);
    this->shadowSprite->setOpacity(clip(fabs(this->height/2*cos(this->triangularBody->GetAngle()))*255));
    
    timeElapsed+=dt;
    if(timeElapsed<0)
        timeElapsed = 0;
    this->bodyHinge->SetLinearVelocity(b2Vec2(amplitudeOscillationX*frequencyOscillationX*cos(frequencyOscillationX*timeElapsed), amplitudeOscillationY*frequencyOscillationY*cos(frequencyOscillationY*timeElapsed)));
}

double TriangularHingedObstruction::clip(double x){
    //clips input double between min and max
    double min = 70.0;
    double max = 100.0;
    
    if(x>max)
        x = max;
    else if(x<min)
        x = min;
    
    return x;
}

double TriangularHingedObstruction::max(double x, double y){
    return x>y?x:y;
}

double TriangularHingedObstruction::min(double x, double y){
    return x<y?x:y;
}
